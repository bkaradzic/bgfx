/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "video_player.h"

#include <bx/allocator.h>
#include <bx/bx.h>
#include <bx/debug.h>
#include <bx/endian.h>
#include <bx/file.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <bx/sort.h>
#include <bx/timer.h>

#include <entry/entry.h>

#include <tinystl/vector.h>
namespace stl = tinystl;

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4127) // warning C4127: conditional expression is constant
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4244) // warning C4244: '=': conversion, possible loss of data
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow")
#include "l-smash/lsmash.h"
BX_PRAGMA_DIAGNOSTIC_POP();

#include <h264/h264.h>

struct VideoPlayer::Impl
{
	enum Container
	{
		Mp4,
		AnnexB,
		Obu,
		Ivf,
	};

	Container              container = Mp4;
	bgfx::VideoCodec::Enum codec     = bgfx::VideoCodec::Count;
	uint8_t  chroma   = 0;
	uint8_t  bitDepth = 8;
	uint8_t  profile  = 0;
	uint8_t  level    = 0;
	uint16_t width    = 0;
	uint16_t height   = 0;
	uint8_t  maxDpbSlots         = 16;
	uint8_t  maxActiveReferences = 4;
	stl::vector<uint8_t> parameterSets;

	lsmash_root_t*           root       = NULL;
	lsmash_file_parameters_t fp         = {};
	bool                     fpOpened   = false;
	uint32_t                 trackId    = 0;
	uint32_t                 lengthSize = 4;

	bx::FileReader reader;
	bool           readerOpened = false;
	uint64_t       fileSize     = 0;

	stl::vector<uint8_t> scratch;

	struct Frame
	{
		uint64_t ptsUs;
		uint64_t offset;
		uint32_t size;
		bool     isKeyframe;
	};

	stl::vector<Frame> frames;
	uint64_t           totalBytes = 0;

	~Impl()
	{
		if (NULL != root)
		{
			lsmash_destroy_root(root);
			root = NULL;
		}

		if (fpOpened)
		{
			lsmash_close_file(&fp);
			fpOpened = false;
		}

		if (readerOpened)
		{
			bx::close(&reader);
			readerOpened = false;
		}
	}
};

namespace
{
	typedef VideoPlayer::Impl Impl;

	const uint32_t kMaxSubmitPerCall = 1;
	const int64_t  kLookaheadUs      = 2 * 1000000;
	const int64_t  kCacheWindowUs    = 2 * kLookaheadUs;
	const uint32_t kMinCachedAuBytes = 16u << 20;
	const float    kRateStepFactor   = 1.25892541f;
	const float    kRateMin          = 0.1f;
	const float    kRateMax          = 100.0f;
	const int64_t  kDefaultFrameUs   = 1000000 / 30;
	const uint32_t kProbeSize        = 64;
	const uint32_t kNalPeekSize      = 1024;
	const uint32_t kScanBufferSize   = 1 << 20;
	const uint32_t kBoxHeaderSize    = 8;
	const uint8_t  kH264NalUnitTypeMask = 0x1f;

	namespace hevc
	{
		enum NalUnitType
		{
			BLA_W_LP   = 16,
			BLA_N_LP   = 18,
			IDR_W_RADL = 19,
			IDR_N_LP   = 20,
			CRA_NUT    = 21,
			RSV_IRAP_VCL23 = 23,
			VPS_NUT    = 32,
			SPS_NUT    = 33,
			PPS_NUT    = 34,
			AUD_NUT    = 35,
			PREFIX_SEI_NUT = 39,
			SUFFIX_SEI_NUT = 40,
		};

		const uint32_t kNalHeaderSize   = 2;
		const uint32_t kMaxSpsCount     = 16;
		const uint32_t kMaxPpsCount     = 64;
		const uint32_t kMaxSubLayers    = 7;
		const uint32_t kMaxStRefPicSets = 64;

		inline uint8_t getNalUnitType(const uint8_t* _nal)
		{
			return (_nal[0] >> 1) & 0x3f;
		}

		inline bool isVcl(uint8_t _type)
		{
			return bx::isInRange(_type, 0, CRA_NUT);
		}

		inline bool isIrap(uint8_t _type)
		{
			return bx::isInRange(_type, BLA_W_LP, RSV_IRAP_VCL23);
		}

		inline bool isIdr(uint8_t _type)
		{
			return IDR_W_RADL == _type || IDR_N_LP == _type;
		}

		inline bool isIdrOrBla(uint8_t _type)
		{
			return bx::isInRange(_type, BLA_W_LP, IDR_N_LP);
		}

		inline bool isParameterSet(uint8_t _type)
		{
			return bx::isInRange(_type, VPS_NUT, PPS_NUT);
		}
	}

	namespace av1
	{
		enum ObuType
		{
			OBU_SEQUENCE_HEADER    = 1,
			OBU_TEMPORAL_DELIMITER = 2,
			OBU_FRAME_HEADER       = 3,
			OBU_FRAME              = 6,
		};

		enum FrameType
		{
			KEY_FRAME = 0,
		};

		enum Profile
		{
			PROFILE_MAIN         = 0,
			PROFILE_HIGH         = 1,
			PROFILE_PROFESSIONAL = 2,
		};

		const uint32_t kObuTypeShift          = 3;
		const uint8_t  kObuTypeMask           = 0xf;
		const uint8_t  kObuExtensionFlag      = 0x4;
		const uint8_t  kObuHasSizeField       = 0x2;
		const uint32_t kObuHeaderMaxSize      = 16;
		const uint32_t kMaxLeadingZeros       = 32;
		const uint8_t  kLeb128ValueMask       = 0x7f;
		const uint8_t  kLeb128ContinuationBit = 0x80;
		const uint32_t kAv1CSize              = 4;
	}

	namespace ivf
	{
		const uint32_t kHeaderSize      = 32;
		const uint32_t kFrameHeaderSize = 12;
	}

	template <typename Ty>
	Ty readLe(const uint8_t* _data)
	{
		Ty value;
		bx::memCopy(&value, _data, sizeof(value) );
		return bx::toHostEndian(value, true);
	}

	template <typename Ty>
	Ty readBe(const uint8_t* _data)
	{
		Ty value;
		bx::memCopy(&value, _data, sizeof(value) );
		return bx::toHostEndian(value, false);
	}

	bool isFourCC(const uint8_t* _data, const char* _fourcc)
	{
		return 0 == bx::memCmp(_data, _fourcc, 4);
	}

	void avccToAnnexB(stl::vector<uint8_t>& _out, const uint8_t* _in, uint32_t _size, uint32_t _lengthSize)
	{
		uint32_t pos = 0;

		while (pos + _lengthSize <= _size)
		{
			uint32_t naluLen = 0;

			for (uint32_t ii = 0; ii < _lengthSize; ++ii)
			{
				naluLen = (naluLen << 8) | _in[pos + ii];
			}

			pos += _lengthSize;

			if (pos + naluLen > _size)
			{
				break;
			}

			_out.push_back(0);
			_out.push_back(0);
			_out.push_back(1);
			_out.insert(_out.end(), _in + pos, _in + pos + naluLen);

			pos += naluLen;
		}
	}

	template <typename Fn>
	void visitLengthPrefixedNals(const uint8_t* _data, uint32_t _size, uint32_t _lengthSize, Fn _visit)
	{
		uint32_t pos = 0;

		while (pos + _lengthSize <= _size)
		{
			uint32_t naluLen = 0;

			for (uint32_t ii = 0; ii < _lengthSize; ++ii)
			{
				naluLen = (naluLen << 8) | _data[pos + ii];
			}

			pos += _lengthSize;

			if (pos + naluLen > _size)
			{
				break;
			}

			_visit(_data + pos, naluLen);
			pos += naluLen;
		}
	}

	uint32_t appendNalAsAnnexB(stl::vector<uint8_t>& _out, const uint8_t* _nal, uint32_t _nalLen)
	{
		if (NULL == _nal
		||  0 == _nalLen)
		{
			return 0;
		}

		_out.push_back(0);
		_out.push_back(0);
		_out.push_back(1);
		_out.insert(_out.end(), _nal, _nal + _nalLen);

		return 1;
	}

	uint32_t stripEmulationPrevention(uint8_t* _dst, const uint8_t* _src, uint32_t _size)
	{
		uint32_t dstIdx = 0;
		uint32_t zeros  = 0;

		for (uint32_t ii = 0; ii < _size; ++ii)
		{
			if (zeros >= 2
			&&  0x03 == _src[ii])
			{
				zeros = 0;
				continue;
			}

			zeros = (0 == _src[ii]) ? zeros + 1 : 0;
			_dst[dstIdx++] = _src[ii];
		}

		return dstIdx;
	}

	void stripEmulationPrevention(stl::vector<uint8_t>& _dst, const uint8_t* _src, uint32_t _size)
	{
		_dst.resize(_size);
		_dst.resize(stripEmulationPrevention(_dst.data(), _src, _size) );
	}

	uint8_t chromaFromFormatIdc(uint32_t _chromaFormatIdc)
	{
		return 3 == _chromaFormatIdc ? 4
			:  2 == _chromaFormatIdc ? 2
			:                          0
			;
	}

	int32_t computePoc(
		  int32_t& _prevPocMsb
		, int32_t& _prevPocLsb
		, const h264::SPS& _sps
		, const h264::SliceHeader& _sh
		, const h264::NALHeader& _nal
		, bool _isIdr
		)
	{
		if (2 == _sps.pic_order_cnt_type)
		{
			const int32_t maxFrameNum = 1 << (_sps.log2_max_frame_num_minus4 + 4);
			int32_t frameNumOffset;
			int32_t poc;

			if (_isIdr)
			{
				frameNumOffset = 0;
				poc            = 0;
			}
			else
			{
				frameNumOffset = _prevPocLsb > _sh.frame_num
					? _prevPocMsb + maxFrameNum
					: _prevPocMsb
					;

				poc = 2 * (frameNumOffset + _sh.frame_num);

				if (0 == _nal.idc)
				{
					poc -= 1;
				}
			}

			_prevPocMsb = frameNumOffset;
			_prevPocLsb = _sh.frame_num;

			return poc;
		}

		if (0 != _sps.pic_order_cnt_type)
		{
			return _sh.frame_num * 2;
		}

		const int32_t maxPocLsb = 1 << (_sps.log2_max_pic_order_cnt_lsb_minus4 + 4);
		int32_t prevPocMsb = _isIdr ? 0 : _prevPocMsb;
		int32_t prevPocLsb = _isIdr ? 0 : _prevPocLsb;

		const int32_t pocLsb = _sh.pic_order_cnt_lsb;
		int32_t pocMsb;

		if (pocLsb < prevPocLsb
		&&  prevPocLsb - pocLsb >= maxPocLsb / 2)
		{
			pocMsb = prevPocMsb + maxPocLsb;
		}
		else if (pocLsb > prevPocLsb
		     &&  pocLsb - prevPocLsb > maxPocLsb / 2)
		{
			pocMsb = prevPocMsb - maxPocLsb;
		}
		else
		{
			pocMsb = prevPocMsb;
		}

		if (0 != _nal.idc)
		{
			_prevPocMsb = pocMsb;
			_prevPocLsb = pocLsb;
		}

		return pocMsb + pocLsb;
	}

	struct H264Tables
	{
		H264Tables()
			: prevPocMsb(0)
			, prevPocLsb(0)
		{
			sps.resize(h264::MAX_SPS_ID + 1);
			pps.resize(h264::MAX_PPS_ID + 1);
			bx::memSet(spsValid, 0, sizeof(spsValid) );
			bx::memSet(ppsValid, 0, sizeof(ppsValid) );
		}

		stl::vector<h264::SPS> sps;
		stl::vector<h264::PPS> pps;
		bool    spsValid[h264::MAX_SPS_ID + 1];
		bool    ppsValid[h264::MAX_PPS_ID + 1];
		int32_t prevPocMsb;
		int32_t prevPocLsb;
	};

	void noteH264Sps(Impl& _video, const h264::SPS& _sps, int64_t& _frameUs)
	{
		_video.profile  = uint8_t(_sps.profile_idc);
		_video.level    = uint8_t(_sps.level_idc);
		_video.chroma   = chromaFromFormatIdc(_sps.chroma_format_idc);
		_video.bitDepth = uint8_t(_sps.bit_depth_luma_minus8 + 8);

		const uint32_t frameMbsOnly = 0 != _sps.frame_mbs_only_flag ? 1 : 0;
		const uint32_t codedWidth   = uint32_t(_sps.pic_width_in_mbs_minus1 + 1) * 16;
		const uint32_t codedHeight  = uint32_t(_sps.pic_height_in_map_units_minus1 + 1) * 16 * (2 - frameMbsOnly);

		uint32_t width  = codedWidth;
		uint32_t height = codedHeight;

		if (0 != _sps.frame_cropping_flag)
		{
			const uint32_t cropUnitX = 2;
			const uint32_t cropUnitY = 2 * (2 - frameMbsOnly);
			const uint32_t cropX     = uint32_t(_sps.frame_crop_left_offset + _sps.frame_crop_right_offset) * cropUnitX;
			const uint32_t cropY     = uint32_t(_sps.frame_crop_top_offset  + _sps.frame_crop_bottom_offset) * cropUnitY;

			if (cropX < codedWidth
			&&  cropY < codedHeight)
			{
				width  = codedWidth  - cropX;
				height = codedHeight - cropY;
			}
		}

		_video.width  = uint16_t(width);
		_video.height = uint16_t(height);

		if (0 != _sps.vui_parameters_present_flag
		&&  0 != _sps.vui.timing_info_present_flag
		&&  0 <  _sps.vui.time_scale
		&&  0 <  _sps.vui.num_units_in_tick)
		{
			_frameUs = int64_t(2000000ull * uint64_t(_sps.vui.num_units_in_tick) / uint64_t(_sps.vui.time_scale) );
		}
	}

	bool parseH264ParameterSet(H264Tables& _tables, Impl& _video, int64_t& _frameUs, const uint8_t* _rbsp, uint32_t _size)
	{
		h264::Bitstream bs;
		bs.init(_rbsp, _size);

		h264::NALHeader nal = {};

		if (!h264::read_nal_header(&nal, &bs) )
		{
			return false;
		}

		if (h264::NAL_UNIT_TYPE_SPS == nal.type)
		{
			h264::SPS sps = {};
			h264::read_sps(&sps, &bs);

			if (sps.seq_parameter_set_id < 0
			||  sps.seq_parameter_set_id > h264::MAX_SPS_ID)
			{
				return false;
			}

			_tables.sps[sps.seq_parameter_set_id]      = sps;
			_tables.spsValid[sps.seq_parameter_set_id] = true;
			noteH264Sps(_video, sps, _frameUs);

			return true;
		}

		if (h264::NAL_UNIT_TYPE_PPS == nal.type)
		{
			h264::PPS pps = {};
			h264::read_pps(&pps, &bs);

			if (pps.pic_parameter_set_id < 0
			||  pps.pic_parameter_set_id > h264::MAX_PPS_ID
			||  pps.seq_parameter_set_id < 0
			||  pps.seq_parameter_set_id > h264::MAX_SPS_ID)
			{
				return false;
			}

			_tables.pps[pps.pic_parameter_set_id]      = pps;
			_tables.ppsValid[pps.pic_parameter_set_id] = true;

			return true;
		}

		return false;
	}

	bool h264SlicePoc(H264Tables& _tables, const uint8_t* _rbsp, uint32_t _size, int32_t& _poc)
	{
		h264::Bitstream bs;
		bs.init(_rbsp, _size);

		h264::NALHeader nal = {};

		if (!h264::read_nal_header(&nal, &bs) )
		{
			return false;
		}

		h264::Bitstream peek = bs;
		peek.ue();
		peek.ue();
		const uint32_t ppsId = peek.ue();

		if (ppsId > uint32_t(h264::MAX_PPS_ID)
		||  !_tables.ppsValid[ppsId])
		{
			return false;
		}

		const uint32_t spsId = uint32_t(_tables.pps[ppsId].seq_parameter_set_id);

		if (spsId > uint32_t(h264::MAX_SPS_ID)
		||  !_tables.spsValid[spsId])
		{
			return false;
		}

		h264::SliceHeader sh = {};
		h264::read_slice_header(&sh, &nal, _tables.pps.data(), _tables.sps.data(), &bs);

		const bool isIdr = h264::NAL_UNIT_TYPE_CODED_SLICE_IDR == nal.type;
		_poc = computePoc(_tables.prevPocMsb, _tables.prevPocLsb, _tables.sps[spsId], sh, nal, isIdr);

		return true;
	}

	struct HevcSps
	{
		bool     valid;
		bool     separateColourPlane;
		uint8_t  chromaFormatIdc;
		uint8_t  bitDepth;
		uint8_t  profile;
		uint8_t  level;
		uint16_t width;
		uint16_t height;
		uint32_t log2MaxPocLsb;
		int64_t  frameUs;
	};

	struct HevcPps
	{
		bool     valid;
		bool     dependentSliceSegments;
		bool     outputFlagPresent;
		uint32_t spsId;
		uint32_t numExtraSliceHeaderBits;
	};

	struct HevcTables
	{
		HevcTables()
			: prevPocMsb(0)
			, prevPocLsb(0)
			, firstPicture(true)
		{
			bx::memSet(sps, 0, sizeof(sps) );
			bx::memSet(pps, 0, sizeof(pps) );
		}

		HevcSps sps[hevc::kMaxSpsCount];
		HevcPps pps[hevc::kMaxPpsCount];
		int32_t prevPocMsb;
		int32_t prevPocLsb;
		bool    firstPicture;
	};

	void skipHevcProfileTierLevel(h264::Bitstream& _bs, uint32_t _maxSubLayersMinus1, uint8_t* _profile, uint8_t* _level)
	{
		_bs.u(2);
		_bs.u(1);
		const uint32_t profileIdc = _bs.u(5);
		_bs.u(32);
		_bs.u(32);
		_bs.u(16);
		const uint32_t levelIdc = _bs.u(8);

		if (NULL != _profile)
		{
			*_profile = uint8_t(profileIdc);
			*_level   = uint8_t(levelIdc);
		}

		bool subLayerProfilePresent[hevc::kMaxSubLayers] = {};
		bool subLayerLevelPresent[hevc::kMaxSubLayers]   = {};

		for (uint32_t ii = 0; ii < _maxSubLayersMinus1 && ii < hevc::kMaxSubLayers; ++ii)
		{
			subLayerProfilePresent[ii] = 0 != _bs.u1();
			subLayerLevelPresent[ii]   = 0 != _bs.u1();
		}

		if (0 < _maxSubLayersMinus1)
		{
			for (uint32_t ii = _maxSubLayersMinus1; ii < 8; ++ii)
			{
				_bs.u(2);
			}
		}

		for (uint32_t ii = 0; ii < _maxSubLayersMinus1 && ii < hevc::kMaxSubLayers; ++ii)
		{
			if (subLayerProfilePresent[ii])
			{
				_bs.u(32);
				_bs.u(32);
				_bs.u(24);
			}

			if (subLayerLevelPresent[ii])
			{
				_bs.u(8);
			}
		}
	}

	void skipHevcScalingListData(h264::Bitstream& _bs)
	{
		for (uint32_t sizeId = 0; sizeId < 4; ++sizeId)
		{
			for (uint32_t matrixId = 0; matrixId < 6; matrixId += 3 == sizeId ? 3 : 1)
			{
				if (0 == _bs.u1() )
				{
					_bs.ue();
				}
				else
				{
					const uint32_t coefNum = bx::min<uint32_t>(64, 1u << (4 + (sizeId << 1) ) );

					if (1 < sizeId)
					{
						_bs.se();
					}

					for (uint32_t ii = 0; ii < coefNum; ++ii)
					{
						_bs.se();
					}
				}
			}
		}
	}

	void skipHevcStRefPicSet(h264::Bitstream& _bs, uint32_t _idx, uint32_t* _numDeltaPocs)
	{
		if (0 != _idx
		&&  0 != _bs.u1() )
		{
			_bs.u1();
			_bs.ue();

			const uint32_t refIdx = _idx - 1;
			uint32_t count = 0;

			for (uint32_t jj = 0; jj <= _numDeltaPocs[refIdx]; ++jj)
			{
				const bool used     = 0 != _bs.u1();
				const bool useDelta = used || 0 != _bs.u1();
				count += useDelta ? 1 : 0;
			}

			_numDeltaPocs[_idx] = count;
			return;
		}

		const uint32_t numNegative = _bs.ue();
		const uint32_t numPositive = _bs.ue();

		for (uint32_t ii = 0; ii < numNegative && ii < 64; ++ii)
		{
			_bs.ue();
			_bs.u1();
		}

		for (uint32_t ii = 0; ii < numPositive && ii < 64; ++ii)
		{
			_bs.ue();
			_bs.u1();
		}

		_numDeltaPocs[_idx] = bx::min<uint32_t>(numNegative + numPositive, 64);
	}

	bool parseHevcSps(const uint8_t* _rbsp, uint32_t _size, HevcSps& _out, uint32_t& _spsId)
	{
		h264::Bitstream bs;
		bs.init(_rbsp + hevc::kNalHeaderSize, _size - hevc::kNalHeaderSize);

		_out = {};

		bs.u(4);
		const uint32_t maxSubLayersMinus1 = bs.u(3);
		bs.u1();
		skipHevcProfileTierLevel(bs, maxSubLayersMinus1, &_out.profile, &_out.level);

		_spsId = bs.ue();

		const uint32_t chromaFormatIdc = bs.ue();
		_out.chromaFormatIdc     = uint8_t(chromaFormatIdc);
		_out.separateColourPlane = 3 == chromaFormatIdc && 0 != bs.u1();

		const uint32_t width  = bs.ue();
		const uint32_t height = bs.ue();

		uint32_t cropX = 0;
		uint32_t cropY = 0;

		if (0 != bs.u1() )
		{
			const uint32_t subWidthC  = (1 == chromaFormatIdc || 2 == chromaFormatIdc) ? 2 : 1;
			const uint32_t subHeightC = 1 == chromaFormatIdc ? 2 : 1;
			const uint32_t left   = bs.ue();
			const uint32_t right  = bs.ue();
			const uint32_t top    = bs.ue();
			const uint32_t bottom = bs.ue();
			cropX = (left + right)  * subWidthC;
			cropY = (top  + bottom) * subHeightC;
		}

		_out.bitDepth = uint8_t(bs.ue() + 8);
		bs.ue();
		_out.log2MaxPocLsb = bs.ue() + 4;

		const bool subLayerOrderingInfoPresent = 0 != bs.u1();

		for (uint32_t ii = subLayerOrderingInfoPresent ? 0 : maxSubLayersMinus1; ii <= maxSubLayersMinus1; ++ii)
		{
			bs.ue();
			bs.ue();
			bs.ue();
		}

		bs.ue();
		bs.ue();
		bs.ue();
		bs.ue();
		bs.ue();
		bs.ue();

		if (0 != bs.u1()
		&&  0 != bs.u1() )
		{
			skipHevcScalingListData(bs);
		}

		bs.u1();
		bs.u1();

		if (0 != bs.u1() )
		{
			bs.u(4);
			bs.u(4);
			bs.ue();
			bs.ue();
			bs.u1();
		}

		const uint32_t numStRefPicSets = bs.ue();

		if (hevc::kMaxStRefPicSets < numStRefPicSets)
		{
			return false;
		}

		uint32_t numDeltaPocs[hevc::kMaxStRefPicSets] = {};

		for (uint32_t ii = 0; ii < numStRefPicSets; ++ii)
		{
			skipHevcStRefPicSet(bs, ii, numDeltaPocs);
		}

		if (0 != bs.u1() )
		{
			const uint32_t numLongTerm = bs.ue();

			for (uint32_t ii = 0; ii < numLongTerm && ii < 32; ++ii)
			{
				bs.u(int(_out.log2MaxPocLsb) );
				bs.u1();
			}
		}

		bs.u1();
		bs.u1();

		if (0 != bs.u1() )
		{
			if (0 != bs.u1() )
			{
				if (255 == bs.u(8) )
				{
					bs.u(16);
					bs.u(16);
				}
			}

			if (0 != bs.u1() )
			{
				bs.u1();
			}

			if (0 != bs.u1() )
			{
				bs.u(3);
				bs.u1();

				if (0 != bs.u1() )
				{
					bs.u(8);
					bs.u(8);
					bs.u(8);
				}
			}

			if (0 != bs.u1() )
			{
				bs.ue();
				bs.ue();
			}

			bs.u1();
			bs.u1();
			bs.u1();

			if (0 != bs.u1() )
			{
				bs.ue();
				bs.ue();
				bs.ue();
				bs.ue();
			}

			if (0 != bs.u1() )
			{
				const uint32_t numUnitsInTick = bs.u(32);
				const uint32_t timeScale      = bs.u(32);

				if (0 != numUnitsInTick
				&&  0 != timeScale)
				{
					_out.frameUs = int64_t(1000000ull * uint64_t(numUnitsInTick) / uint64_t(timeScale) );
				}
			}
		}

		if (bs.eof()
		||  0 == width
		||  0 == height
		||  cropX >= width
		||  cropY >= height)
		{
			return false;
		}

		_out.width  = uint16_t(width  - cropX);
		_out.height = uint16_t(height - cropY);
		_out.valid  = true;

		return true;
	}

	bool parseHevcPps(const uint8_t* _rbsp, uint32_t _size, HevcPps& _out, uint32_t& _ppsId)
	{
		h264::Bitstream bs;
		bs.init(_rbsp + hevc::kNalHeaderSize, _size - hevc::kNalHeaderSize);

		_out = {};

		_ppsId      = bs.ue();
		_out.spsId  = bs.ue();
		_out.dependentSliceSegments  = 0 != bs.u1();
		_out.outputFlagPresent       = 0 != bs.u1();
		_out.numExtraSliceHeaderBits = bs.u(3);
		_out.valid = !bs.eof();

		return _out.valid;
	}

	bool parseHevcParameterSet(HevcTables& _tables, const uint8_t* _rbsp, uint32_t _size)
	{
		if (_size <= hevc::kNalHeaderSize)
		{
			return false;
		}

		const uint8_t type = hevc::getNalUnitType(_rbsp);

		if (hevc::SPS_NUT == type)
		{
			HevcSps  sps;
			uint32_t id;

			if (parseHevcSps(_rbsp, _size, sps, id)
			&&  id < hevc::kMaxSpsCount)
			{
				_tables.sps[id] = sps;
				return true;
			}
		}
		else if (hevc::PPS_NUT == type)
		{
			HevcPps  pps;
			uint32_t id;

			if (parseHevcPps(_rbsp, _size, pps, id)
			&&  id < hevc::kMaxPpsCount)
			{
				_tables.pps[id] = pps;
				return true;
			}
		}

		return false;
	}

	bool hevcSlicePoc(HevcTables& _tables, const uint8_t* _rbsp, uint32_t _size, int32_t& _poc)
	{
		const uint8_t type = hevc::getNalUnitType(_rbsp);

		h264::Bitstream bs;
		bs.init(_rbsp + hevc::kNalHeaderSize, _size - hevc::kNalHeaderSize);

		bs.u1();

		if (hevc::isIrap(type) )
		{
			bs.u1();
		}

		const uint32_t ppsId = bs.ue();

		if (hevc::kMaxPpsCount <= ppsId
		||  !_tables.pps[ppsId].valid)
		{
			return false;
		}

		const HevcPps& pps = _tables.pps[ppsId];

		if (hevc::kMaxSpsCount <= pps.spsId
		||  !_tables.sps[pps.spsId].valid)
		{
			return false;
		}

		const HevcSps& sps = _tables.sps[pps.spsId];

		for (uint32_t ii = 0; ii < pps.numExtraSliceHeaderBits; ++ii)
		{
			bs.u1();
		}

		bs.ue();

		if (pps.outputFlagPresent)
		{
			bs.u1();
		}

		if (sps.separateColourPlane)
		{
			bs.u(2);
		}

		const int32_t maxPocLsb = 1 << sps.log2MaxPocLsb;
		const int32_t pocLsb    = hevc::isIdr(type) ? 0 : int32_t(bs.u(int(sps.log2MaxPocLsb) ) );

		int32_t pocMsb;

		if (hevc::isIdrOrBla(type)
		|| (hevc::CRA_NUT == type && _tables.firstPicture) )
		{
			pocMsb = 0;
		}
		else if (pocLsb < _tables.prevPocLsb
		     &&  _tables.prevPocLsb - pocLsb >= maxPocLsb / 2)
		{
			pocMsb = _tables.prevPocMsb + maxPocLsb;
		}
		else if (pocLsb > _tables.prevPocLsb
		     &&  pocLsb - _tables.prevPocLsb > maxPocLsb / 2)
		{
			pocMsb = _tables.prevPocMsb - maxPocLsb;
		}
		else
		{
			pocMsb = _tables.prevPocMsb;
		}

		_tables.prevPocMsb   = pocMsb;
		_tables.prevPocLsb   = pocLsb;
		_tables.firstPicture = false;

		_poc = pocMsb + pocLsb;

		return true;
	}

	struct Av1SequenceHeader
	{
		uint32_t maxWidth;
		uint32_t maxHeight;
		int64_t  frameUs;
		uint8_t  profile;
		uint8_t  levelIdx;
		uint8_t  highBitdepth;
		uint8_t  twelveBit;
		uint8_t  monochrome;
		uint8_t  subsamplingX;
		uint8_t  subsamplingY;
		uint8_t  reducedStillPictureHeader;
	};

	uint32_t uvlc(h264::Bitstream& _bs)
	{
		uint32_t leadingZeros = 0;

		while (leadingZeros < av1::kMaxLeadingZeros
		&&     0 == _bs.u1() )
		{
			++leadingZeros;
		}

		if (av1::kMaxLeadingZeros <= leadingZeros)
		{
			return UINT32_MAX;
		}

		return _bs.u(int(leadingZeros) ) + (1u << leadingZeros) - 1;
	}

	bool parseAv1SequenceHeader(const uint8_t* _data, uint32_t _size, Av1SequenceHeader& _out)
	{
		h264::Bitstream br;
		br.init(_data, _size);

		_out = {};
		_out.profile = uint8_t(br.u(3) );
		br.u1();
		_out.reducedStillPictureHeader = uint8_t(br.u1() );

		bool     decoderModelInfoPresent = false;
		uint32_t bufferDelayLength       = 0;

		if (_out.reducedStillPictureHeader)
		{
			_out.levelIdx = uint8_t(br.u(5) );
		}
		else
		{
			if (0 != br.u1() )
			{
				const uint32_t numUnitsInDisplayTick = br.u(32);
				const uint32_t timeScale             = br.u(32);
				uint32_t ticksPerPicture = 1;

				if (0 != br.u1() )
				{
					ticksPerPicture = uvlc(br) + 1;
				}

				if (0 != numUnitsInDisplayTick
				&&  0 != timeScale)
				{
					_out.frameUs = int64_t(1000000ull * uint64_t(numUnitsInDisplayTick) * ticksPerPicture / uint64_t(timeScale) );
				}

				decoderModelInfoPresent = 0 != br.u1();

				if (decoderModelInfoPresent)
				{
					bufferDelayLength = br.u(5) + 1;
					br.u(32);
					br.u(5);
					br.u(5);
				}
			}

			const bool     initialDisplayDelayPresent = 0 != br.u1();
			const uint32_t numOperatingPoints         = br.u(5) + 1;

			for (uint32_t ii = 0; ii < numOperatingPoints; ++ii)
			{
				br.u(12);
				const uint32_t levelIdx = br.u(5);

				if (7 < levelIdx)
				{
					br.u1();
				}

				if (0 == ii)
				{
					_out.levelIdx = uint8_t(levelIdx);
				}

				if (decoderModelInfoPresent
				&&  0 != br.u1() )
				{
					br.u(int(bufferDelayLength) );
					br.u(int(bufferDelayLength) );
					br.u1();
				}

				if (initialDisplayDelayPresent
				&&  0 != br.u1() )
				{
					br.u(4);
				}
			}
		}

		const uint32_t widthBits  = br.u(4) + 1;
		const uint32_t heightBits = br.u(4) + 1;
		_out.maxWidth  = br.u(int(widthBits) )  + 1;
		_out.maxHeight = br.u(int(heightBits) ) + 1;

		if (!_out.reducedStillPictureHeader
		&&  0 != br.u1() )
		{
			br.u(4);
			br.u(3);
		}

		br.u(3);

		if (!_out.reducedStillPictureHeader)
		{
			br.u(4);
			const bool enableOrderHint = 0 != br.u1();

			if (enableOrderHint)
			{
				br.u(2);
			}

			const uint32_t forceScreenContentTools = 0 != br.u1() ? 2 : br.u1();

			if (0 < forceScreenContentTools
			&&  0 == br.u1() )
			{
				br.u1();
			}

			if (enableOrderHint)
			{
				br.u(3);
			}
		}

		br.u(3);

		_out.highBitdepth = uint8_t(br.u1() );
		_out.twelveBit    = av1::PROFILE_PROFESSIONAL == _out.profile && _out.highBitdepth ? uint8_t(br.u1() ) : 0;
		_out.monochrome   = av1::PROFILE_HIGH == _out.profile ? 0 : uint8_t(br.u1() );

		uint32_t colorPrimaries = 2;
		uint32_t transfer       = 2;
		uint32_t matrix         = 2;

		if (0 != br.u1() )
		{
			colorPrimaries = br.u(8);
			transfer       = br.u(8);
			matrix         = br.u(8);
		}

		if (_out.monochrome)
		{
			br.u1();
			_out.subsamplingX = 1;
			_out.subsamplingY = 1;
		}
		else if (1 == colorPrimaries && 13 == transfer && 0 == matrix)
		{
		}
		else
		{
			br.u1();

			if (av1::PROFILE_MAIN == _out.profile)
			{
				_out.subsamplingX = 1;
				_out.subsamplingY = 1;
			}
			else if (av1::PROFILE_PROFESSIONAL == _out.profile)
			{
				if (_out.twelveBit)
				{
					_out.subsamplingX = uint8_t(br.u1() );
					_out.subsamplingY = _out.subsamplingX ? uint8_t(br.u1() ) : 0;
				}
				else
				{
					_out.subsamplingX = 1;
				}
			}
		}

		return !br.eof()
			&& 0 != _out.maxWidth
			&& 0 != _out.maxHeight
			;
	}

	void noteAv1SequenceHeader(Impl& _video, const Av1SequenceHeader& _seq)
	{
		_video.profile  = _seq.profile;
		_video.level    = _seq.levelIdx;
		_video.bitDepth = _seq.twelveBit ? 12 : _seq.highBitdepth ? 10 : 8;
		_video.chroma   = _seq.subsamplingX && _seq.subsamplingY ? 0
			:             _seq.subsamplingX                      ? 2
			:                                                      4
			;
		_video.width  = uint16_t(_seq.maxWidth);
		_video.height = uint16_t(_seq.maxHeight);
	}

	struct Obu
	{
		uint8_t  type;
		uint32_t headerSize;
		uint32_t payloadSize;
		bool     hasSize;
	};

	bool readObuHeader(const uint8_t* _data, uint32_t _size, Obu& _out)
	{
		if (0 == _size)
		{
			return false;
		}

		const uint8_t header       = _data[0];
		const bool    hasExtension = 0 != (header & av1::kObuExtensionFlag);

		_out.type       = (header >> av1::kObuTypeShift) & av1::kObuTypeMask;
		_out.hasSize    = 0 != (header & av1::kObuHasSizeField);
		_out.headerSize = 1 + (hasExtension ? 1 : 0);

		if (0 != (header & 0x80)
		||  _size < _out.headerSize)
		{
			return false;
		}

		if (!_out.hasSize)
		{
			_out.payloadSize = _size - _out.headerSize;
			return true;
		}

		uint32_t size = 0;

		for (uint32_t shift = 0; shift < 32; shift += 7)
		{
			if (_out.headerSize >= _size)
			{
				return false;
			}

			const uint8_t byte = _data[_out.headerSize++];
			size |= uint32_t(byte & av1::kLeb128ValueMask) << shift;

			if (0 == (byte & av1::kLeb128ContinuationBit) )
			{
				break;
			}
		}

		_out.payloadSize = bx::min(size, _size - _out.headerSize);

		return true;
	}

	template <typename Fn>
	void visitObus(const uint8_t* _data, uint32_t _size, Fn _visit)
	{
		uint32_t pos = 0;

		while (pos < _size)
		{
			Obu obu;

			if (!readObuHeader(_data + pos, _size - pos, obu) )
			{
				break;
			}

			const uint32_t obuSize = obu.headerSize + obu.payloadSize;
			_visit(obu.type, _data + pos, obuSize, _data + pos + obu.headerSize, obu.payloadSize);
			pos += obuSize;
		}
	}

	bool av1FrameIsKey(const uint8_t* _payload, uint32_t _size, bool _reducedStillPictureHeader)
	{
		if (0 == _size)
		{
			return false;
		}

		if (_reducedStillPictureHeader)
		{
			return true;
		}

		h264::Bitstream br;
		br.init(_payload, _size);

		if (0 != br.u1() )
		{
			return false;
		}

		const uint32_t frameType = br.u(2);
		const bool     showFrame = 0 != br.u1();

		return av1::KEY_FRAME == frameType && showFrame;
	}

	bool av1TemporalUnitIsKey(const uint8_t* _data, uint32_t _size, bool _reducedStillPictureHeader)
	{
		bool seen = false;
		bool key  = false;

		visitObus(_data, _size, [&](uint8_t _type, const uint8_t*, uint32_t, const uint8_t* _payload, uint32_t _payloadSize)
		{
			if (!seen
			&& (av1::OBU_FRAME_HEADER == _type || av1::OBU_FRAME == _type) )
			{
				seen = true;
				key  = av1FrameIsKey(_payload, _payloadSize, _reducedStillPictureHeader);
			}
		});

		return key;
	}

	bool takeAv1SequenceHeader(Impl& _video, Av1SequenceHeader& _seq, const uint8_t* _data, uint32_t _size)
	{
		bool found = false;

		visitObus(_data, _size, [&](uint8_t _type, const uint8_t* _obu, uint32_t _obuSize, const uint8_t* _payload, uint32_t _payloadSize)
		{
			if (!found
			&&  av1::OBU_SEQUENCE_HEADER == _type
			&&  parseAv1SequenceHeader(_payload, _payloadSize, _seq) )
			{
				found = true;
				_video.parameterSets.clear();
				_video.parameterSets.insert(_video.parameterSets.end(), _obu, _obu + _obuSize);
			}
		});

		return found;
	}

	struct Probe
	{
		Impl::Container        container;
		bgfx::VideoCodec::Enum codec;
	};

	bool probeAnnexB(const uint8_t* _data, uint32_t _size, bgfx::VideoCodec::Enum& _codec)
	{
		uint32_t header = 0;

		if (4 <= _size && 0 == _data[0] && 0 == _data[1] && 0 == _data[2] && 1 == _data[3])
		{
			header = 4;
		}
		else if (3 <= _size && 0 == _data[0] && 0 == _data[1] && 1 == _data[2])
		{
			header = 3;
		}
		else
		{
			return false;
		}

		if (_size < header + 2
		||  0 != (_data[header] & 0x80) )
		{
			return false;
		}

		const uint8_t  hevcType     = hevc::getNalUnitType(_data + header);
		const uint32_t hevcLayerId  = (uint32_t(_data[header] & 1) << 5) | (_data[header + 1] >> 3);
		const uint32_t hevcTidPlus1 = _data[header + 1] & 7;

		const bool hevcHead = false
			|| hevc::isParameterSet(hevcType)
			|| hevc::AUD_NUT        == hevcType
			|| hevc::PREFIX_SEI_NUT == hevcType
			|| hevc::isIrap(hevcType)
			;

		if (hevcHead
		&&  0 == hevcLayerId
		&&  0 != hevcTidPlus1)
		{
			_codec = bgfx::VideoCodec::H265;
			return true;
		}

		const uint8_t h264Type = _data[header] & kH264NalUnitTypeMask;

		const bool h264Head = false
			|| h264::NAL_UNIT_TYPE_SPS             == h264Type
			|| h264::NAL_UNIT_TYPE_PPS             == h264Type
			|| h264::NAL_UNIT_TYPE_AUD             == h264Type
			|| h264::NAL_UNIT_TYPE_SEI             == h264Type
			|| h264::NAL_UNIT_TYPE_CODED_SLICE_IDR == h264Type
			;

		if (h264Head)
		{
			_codec = bgfx::VideoCodec::H264;
			return true;
		}

		return false;
	}

	bool probeObu(const uint8_t* _data, uint32_t _size)
	{
		Obu obu;

		if (!readObuHeader(_data, _size, obu)
		||  !obu.hasSize)
		{
			return false;
		}

		if (av1::OBU_SEQUENCE_HEADER == obu.type)
		{
			return true;
		}

		if (av1::OBU_TEMPORAL_DELIMITER != obu.type
		||  0 != obu.payloadSize)
		{
			return false;
		}

		const uint32_t next = obu.headerSize;

		return readObuHeader(_data + next, _size - next, obu)
			&& obu.hasSize
			&& av1::OBU_SEQUENCE_HEADER == obu.type
			;
	}

	bool probeBytes(const uint8_t* _data, uint32_t _size, Probe& _out)
	{
		if (12 <= _size)
		{
			const uint8_t* box = _data + 4;

			if (isFourCC(box, "ftyp")
			||  isFourCC(box, "moov")
			||  isFourCC(box, "mdat")
			||  isFourCC(box, "free")
			||  isFourCC(box, "skip")
			||  isFourCC(box, "wide") )
			{
				_out = { Impl::Mp4, bgfx::VideoCodec::Count };
				return true;
			}

			if (isFourCC(_data, "DKIF")
			&&  isFourCC(_data + 8, "AV01") )
			{
				_out = { Impl::Ivf, bgfx::VideoCodec::AV1 };
				return true;
			}
		}

		bgfx::VideoCodec::Enum codec;

		if (probeAnnexB(_data, _size, codec) )
		{
			_out = { Impl::AnnexB, codec };
			return true;
		}

		if (probeObu(_data, _size) )
		{
			_out = { Impl::Obu, bgfx::VideoCodec::AV1 };
			return true;
		}

		return false;
	}

	bool probeFile(const bx::FilePath& _filePath, Probe& _out)
	{
		bx::FileReader reader;
		bx::Error err;

		if (!bx::open(&reader, _filePath, &err) )
		{
			return false;
		}

		uint8_t data[kProbeSize] = {};
		const int32_t size = bx::read(&reader, data, sizeof(data), &err);
		bx::close(&reader);

		return 0 < size
			&& probeBytes(data, uint32_t(size), _out)
			;
	}

	class FileScanner
	{
	public:
		FileScanner(bx::FileReaderI* _reader, uint64_t _size)
			: m_reader(_reader)
			, m_size(_size)
			, m_bufferPos(0)
			, m_bufferLen(0)
		{
			m_buffer.resize(kScanBufferSize);
		}

		const uint8_t* window(uint64_t _pos, uint32_t _minLen, uint32_t& _len)
		{
			if (_pos >= m_size)
			{
				_len = 0;
				return NULL;
			}

			const uint64_t want = bx::min<uint64_t>(_minLen, m_size - _pos);

			if (_pos < m_bufferPos
			||  _pos + want > m_bufferPos + m_bufferLen)
			{
				refill(_pos);
			}

			_len = uint32_t(bx::min<uint64_t>(m_bufferPos + m_bufferLen - _pos, UINT32_MAX) );

			return &m_buffer[size_t(_pos - m_bufferPos)];
		}

		uint64_t size() const
		{
			return m_size;
		}

	private:
		void refill(uint64_t _pos)
		{
			bx::Error err;
			bx::seek(m_reader, int64_t(_pos), bx::Whence::Begin);
			const int32_t len = bx::read(m_reader, m_buffer.data(), int32_t(m_buffer.size() ), &err);

			m_bufferPos = _pos;
			m_bufferLen = 0 < len ? uint32_t(len) : 0;
		}

		bx::FileReaderI*     m_reader;
		uint64_t             m_size;
		uint64_t             m_bufferPos;
		uint32_t             m_bufferLen;
		stl::vector<uint8_t> m_buffer;
	};

	uint64_t findStartCode(FileScanner& _scanner, uint64_t _pos)
	{
		const uint64_t size = _scanner.size();

		while (_pos + 3 <= size)
		{
			uint32_t len;
			const uint8_t* data = _scanner.window(_pos, 3, len);

			if (NULL == data
			||  len < 3)
			{
				break;
			}

			uint32_t ii = 0;

			for (; ii + 3 <= len; ++ii)
			{
				if (0 == data[ii]
				&&  0 == data[ii+1]
				&&  1 == data[ii+2])
				{
					const uint64_t sc = _pos + ii;

					if (0 < ii)
					{
						return 0 == data[ii-1] ? sc - 1 : sc;
					}

					if (0 < sc)
					{
						uint32_t prevLen;
						const uint8_t* prev = _scanner.window(sc - 1, 1, prevLen);
						return NULL != prev && 0 == prev[0] ? sc - 1 : sc;
					}

					return sc;
				}
			}

			_pos += ii;
		}

		return size;
	}

	struct GopPicture
	{
		int32_t  poc;
		uint32_t frame;
	};

	int32_t compareGopPicture(const void* _lhs, const void* _rhs)
	{
		const GopPicture& lhs = *(const GopPicture*)_lhs;
		const GopPicture& rhs = *(const GopPicture*)_rhs;

		if (lhs.poc != rhs.poc)
		{
			return lhs.poc < rhs.poc ? -1 : 1;
		}

		return lhs.frame < rhs.frame ? -1 : lhs.frame > rhs.frame ? 1 : 0;
	}

	void finalizeGop(Impl& _video, stl::vector<GopPicture>& _gop, uint64_t& _displayBase, int64_t _frameUs)
	{
		if (_gop.empty() )
		{
			return;
		}

		bx::quickSort(_gop.data(), uint32_t(_gop.size() ), sizeof(GopPicture), compareGopPicture);

		for (uint32_t ii = 0; ii < uint32_t(_gop.size() ); ++ii)
		{
			_video.frames[_gop[ii].frame].ptsUs = (_displayBase + ii) * uint64_t(_frameUs);
		}

		_displayBase += _gop.size();
		_gop.clear();
	}

	void closeFrame(Impl& _video, uint64_t _end)
	{
		if (!_video.frames.empty() )
		{
			Impl::Frame& last = _video.frames.back();
			last.size = uint32_t(_end - last.offset);
			_video.totalBytes += last.size;
		}
	}

	bool indexAnnexB(Impl& _video)
	{
		const bool isHevc = bgfx::VideoCodec::H265 == _video.codec;

		FileScanner scanner(&_video.reader, _video.fileSize);

		H264Tables h264Tables;
		HevcTables hevcTables;

		int64_t  frameUs     = 0;
		uint64_t displayBase = 0;
		uint64_t unitBegin   = UINT64_MAX;
		uint64_t pos         = findStartCode(scanner, 0);

		stl::vector<GopPicture> gop;
		stl::vector<uint8_t>    rbsp;
		rbsp.resize(kNalPeekSize);

		while (pos < scanner.size() )
		{
			uint32_t len;
			const uint8_t* sc = scanner.window(pos, 4, len);

			if (NULL == sc
			||  len < 3)
			{
				break;
			}

			const uint32_t scLen  = 1 == sc[2] ? 3 : 4;
			const uint64_t header = pos + scLen;
			const uint64_t next   = findStartCode(scanner, header);

			if (header >= next)
			{
				pos = next;
				continue;
			}

			const uint32_t peek     = uint32_t(bx::min<uint64_t>(next - header, kNalPeekSize) );
			const uint8_t* nal      = scanner.window(header, peek, len);
			const uint32_t nalLen   = bx::min(peek, len);
			const uint32_t rbspSize = stripEmulationPrevention(rbsp.data(), nal, nalLen);
			const uint32_t minSize  = isHevc ? hevc::kNalHeaderSize + 1 : 2;

			if (rbspSize < minSize)
			{
				pos = next;
				continue;
			}

			bool parameterSet;
			bool slice;
			bool firstSlice;
			bool keyframe;

			if (isHevc)
			{
				const uint8_t type = hevc::getNalUnitType(rbsp.data() );
				parameterSet = hevc::isParameterSet(type);
				slice        = hevc::isVcl(type);
				firstSlice   = 0 != (rbsp[hevc::kNalHeaderSize] & 0x80);
				keyframe     = hevc::isIrap(type);
			}
			else
			{
				const uint8_t type = rbsp[0] & kH264NalUnitTypeMask;
				parameterSet = h264::NAL_UNIT_TYPE_SPS == type || h264::NAL_UNIT_TYPE_PPS == type;
				slice        = h264::NAL_UNIT_TYPE_CODED_SLICE_NON_IDR == type || h264::NAL_UNIT_TYPE_CODED_SLICE_IDR == type;
				firstSlice   = 0 != (rbsp[1] & 0x80);
				keyframe     = h264::NAL_UNIT_TYPE_CODED_SLICE_IDR == type;
			}

			if (parameterSet)
			{
				if (isHevc)
				{
					parseHevcParameterSet(hevcTables, rbsp.data(), rbspSize);
				}
				else
				{
					parseH264ParameterSet(h264Tables, _video, frameUs, rbsp.data(), rbspSize);
				}

				if (_video.frames.empty()
				&&  UINT64_MAX == unitBegin)
				{
					appendNalAsAnnexB(_video.parameterSets, nal, nalLen);
				}
				else
				{
					unitBegin = bx::min(unitBegin, pos);
				}
			}
			else if (slice && firstSlice)
			{
				const uint64_t start = UINT64_MAX != unitBegin ? unitBegin : pos;
				closeFrame(_video, start);

				int32_t poc = 0;

				const bool haveOrder = isHevc
					? hevcSlicePoc(hevcTables, rbsp.data(), rbspSize, poc)
					: h264SlicePoc(h264Tables, rbsp.data(), rbspSize, poc)
					;

				const bool gopStart = isHevc
					? hevc::isIdrOrBla(hevc::getNalUnitType(rbsp.data() ) )
					: keyframe
					;

				if (gopStart)
				{
					finalizeGop(_video, gop, displayBase, 0 != frameUs ? frameUs : kDefaultFrameUs);
				}

				const uint32_t frameIdx = uint32_t(_video.frames.size() );

				_video.frames.push_back(
					{
						.ptsUs      = 0,
						.offset     = start,
						.size       = 0,
						.isKeyframe = keyframe,
					});

				gop.push_back({ haveOrder ? poc : int32_t(frameIdx), frameIdx });
				unitBegin = UINT64_MAX;
			}
			else if (!slice
			     &&  !_video.frames.empty() )
			{
				unitBegin = bx::min(unitBegin, pos);
			}

			pos = next;
		}

		closeFrame(_video, scanner.size() );

		if (0 == frameUs
		&&  isHevc)
		{
			for (uint32_t ii = 0; ii < hevc::kMaxSpsCount; ++ii)
			{
				if (hevcTables.sps[ii].valid)
				{
					const HevcSps& sps = hevcTables.sps[ii];
					_video.profile  = sps.profile;
					_video.level    = sps.level;
					_video.chroma   = chromaFromFormatIdc(sps.chromaFormatIdc);
					_video.bitDepth = sps.bitDepth;
					_video.width    = sps.width;
					_video.height   = sps.height;
					frameUs         = sps.frameUs;
					break;
				}
			}
		}

		finalizeGop(_video, gop, displayBase, 0 != frameUs ? frameUs : kDefaultFrameUs);

		return !_video.frames.empty()
			&& !_video.parameterSets.empty()
			&& 0 != _video.width
			&& 0 != _video.height
			;
	}

	bool indexObu(Impl& _video)
	{
		FileScanner scanner(&_video.reader, _video.fileSize);

		Av1SequenceHeader seq = {};
		bool haveSeq   = false;
		bool keySeen   = false;
		uint64_t pos   = 0;

		while (pos < scanner.size() )
		{
			uint32_t len;
			const uint8_t* data = scanner.window(pos, av1::kObuHeaderMaxSize, len);
			Obu obu;

			if (NULL == data
			||  !readObuHeader(data, len, obu) )
			{
				break;
			}

			const uint64_t payload = pos + obu.headerSize;
			const uint64_t next    = obu.hasSize
				? bx::min(payload + obu.payloadSize, scanner.size() )
				: scanner.size()
				;

			if (av1::OBU_TEMPORAL_DELIMITER == obu.type
			||  _video.frames.empty() )
			{
				closeFrame(_video, pos);

				_video.frames.push_back(
					{
						.ptsUs      = 0,
						.offset     = pos,
						.size       = 0,
						.isKeyframe = false,
					});

				keySeen = false;
			}

			if (av1::OBU_SEQUENCE_HEADER == obu.type
			&&  !haveSeq)
			{
				const uint32_t obuSize = uint32_t(next - pos);
				const uint8_t* whole   = scanner.window(pos, obuSize, len);

				if (NULL != whole
				&&  obuSize <= len
				&&  parseAv1SequenceHeader(whole + obu.headerSize, obu.payloadSize, seq) )
				{
					haveSeq = true;
					_video.parameterSets.insert(_video.parameterSets.end(), whole, whole + obuSize);
				}
			}
			else if (!keySeen
			     && (av1::OBU_FRAME_HEADER == obu.type || av1::OBU_FRAME == obu.type) )
			{
				const uint8_t* head = scanner.window(payload, 1, len);
				keySeen = true;
				_video.frames.back().isKeyframe = NULL != head && av1FrameIsKey(head, 1, 0 != seq.reducedStillPictureHeader);
			}

			pos = next;
		}

		closeFrame(_video, scanner.size() );

		if (!haveSeq)
		{
			return false;
		}

		noteAv1SequenceHeader(_video, seq);

		const int64_t frameUs = 0 != seq.frameUs ? seq.frameUs : kDefaultFrameUs;

		for (uint32_t ii = 0; ii < uint32_t(_video.frames.size() ); ++ii)
		{
			_video.frames[ii].ptsUs = uint64_t(ii) * uint64_t(frameUs);
		}

		return !_video.frames.empty();
	}

	bool indexIvf(Impl& _video)
	{
		FileScanner scanner(&_video.reader, _video.fileSize);

		uint32_t len;
		const uint8_t* header = scanner.window(0, ivf::kHeaderSize, len);

		if (NULL == header
		||  len < ivf::kHeaderSize)
		{
			return false;
		}

		const uint32_t headerSize  = readLe<uint16_t>(header + 6);
		const uint32_t timebaseDen = readLe<uint32_t>(header + 16);
		const uint32_t timebaseNum = readLe<uint32_t>(header + 20);

		Av1SequenceHeader seq = {};
		bool haveSeq = false;

		uint64_t pos = bx::max<uint32_t>(headerSize, ivf::kHeaderSize);

		while (pos + ivf::kFrameHeaderSize <= scanner.size() )
		{
			const uint8_t* frameHeader = scanner.window(pos, ivf::kFrameHeaderSize, len);

			if (NULL == frameHeader
			||  len < ivf::kFrameHeaderSize)
			{
				break;
			}

			const uint32_t size   = readLe<uint32_t>(frameHeader);
			const uint64_t pts    = readLe<uint64_t>(frameHeader + 4);
			const uint64_t offset = pos + ivf::kFrameHeaderSize;

			if (0 == size
			||  offset + size > scanner.size()
			||  kScanBufferSize < size)
			{
				break;
			}

			const uint8_t* data = scanner.window(offset, size, len);

			if (NULL == data
			||  len < size)
			{
				break;
			}

			if (!haveSeq)
			{
				haveSeq = takeAv1SequenceHeader(_video, seq, data, size);
			}

			const uint64_t ptsUs = 0 != timebaseDen
				? pts * uint64_t(timebaseNum) * 1000000ull / uint64_t(timebaseDen)
				: uint64_t(_video.frames.size() ) * uint64_t(kDefaultFrameUs)
				;

			_video.frames.push_back(
				{
					.ptsUs      = ptsUs,
					.offset     = offset,
					.size       = size,
					.isKeyframe = av1TemporalUnitIsKey(data, size, 0 != seq.reducedStillPictureHeader),
				});

			_video.totalBytes += size;
			pos = offset + size;
		}

		if (!haveSeq)
		{
			return false;
		}

		noteAv1SequenceHeader(_video, seq);

		return !_video.frames.empty();
	}

	bool parseAvcC(Impl& _video, const uint8_t* _data, uint32_t _size, uint32_t& _lengthSize)
	{
		if (NULL == _data
		||  _size < kBoxHeaderSize + 7)
		{
			return false;
		}

		uint32_t pos = kBoxHeaderSize;
		++pos;

		const uint8_t profileIdc = _data[pos++];
		++pos;

		const uint8_t levelIdc = _data[pos++];
		_lengthSize            = uint32_t(_data[pos++] & 0x03) + 1;
		const uint32_t numSps  = uint32_t(_data[pos++] & 0x1f);

		_video.profile  = profileIdc;
		_video.level    = levelIdc;
		_video.chroma   = 0;
		_video.bitDepth = 8;

		H264Tables tables;
		int64_t    frameUs = 0;
		stl::vector<uint8_t> rbsp;

		for (uint32_t ii = 0; ii < numSps; ++ii)
		{
			if (pos + 2 > _size)
			{
				return false;
			}

			const uint32_t nalLen = readBe<uint16_t>(_data + pos);
			pos += 2;

			if (pos + nalLen > _size)
			{
				return false;
			}

			appendNalAsAnnexB(_video.parameterSets, _data + pos, nalLen);
			stripEmulationPrevention(rbsp, _data + pos, nalLen);
			parseH264ParameterSet(tables, _video, frameUs, rbsp.data(), uint32_t(rbsp.size() ) );

			pos += nalLen;
		}

		if (pos + 1 > _size)
		{
			return false;
		}

		const uint32_t numPps = _data[pos++];

		for (uint32_t ii = 0; ii < numPps; ++ii)
		{
			if (pos + 2 > _size)
			{
				return false;
			}

			const uint32_t nalLen = readBe<uint16_t>(_data + pos);
			pos += 2;

			if (pos + nalLen > _size)
			{
				return false;
			}

			appendNalAsAnnexB(_video.parameterSets, _data + pos, nalLen);
			pos += nalLen;
		}

		return true;
	}

	bool parseHvcC(Impl& _video, const uint8_t* _data, uint32_t _size, uint32_t& _lengthSize)
	{
		if (NULL == _data
		||  _size < kBoxHeaderSize + 23)
		{
			return false;
		}

		uint32_t pos = kBoxHeaderSize;
		++pos;

		const uint8_t profileIdc = _data[pos++] & 0x1f;
		pos += 10;

		const uint8_t levelIdc = _data[pos++];
		pos += 3;

		const uint8_t chromaFormat = _data[pos++] & 0x03;
		const uint8_t bitDepthLuma = uint8_t( (_data[pos++] & 0x07) + 8);
		pos += 3;

		_lengthSize = uint32_t(_data[pos++] & 0x03) + 1;

		if (pos + 1 > _size)
		{
			return false;
		}

		const uint32_t numArrays = _data[pos++];

		_video.profile  = profileIdc;
		_video.level    = levelIdc;
		_video.chroma   = chromaFromFormatIdc(chromaFormat);
		_video.bitDepth = bitDepthLuma;

		stl::vector<uint8_t> vps;
		stl::vector<uint8_t> sps;
		stl::vector<uint8_t> pps;

		for (uint32_t aa = 0; aa < numArrays; ++aa)
		{
			if (pos + 3 > _size)
			{
				return false;
			}

			const uint8_t  nalUnitType = _data[pos++] & 0x3f;
			const uint32_t numNalus    = readBe<uint16_t>(_data + pos);
			pos += 2;

			stl::vector<uint8_t>* dst = NULL;

			switch (nalUnitType)
			{
				case hevc::VPS_NUT: dst = &vps; break;
				case hevc::SPS_NUT: dst = &sps; break;
				case hevc::PPS_NUT: dst = &pps; break;
				default:                        break;
			}

			for (uint32_t nn = 0; nn < numNalus; ++nn)
			{
				if (pos + 2 > _size)
				{
					return false;
				}

				const uint32_t nalLen = readBe<uint16_t>(_data + pos);
				pos += 2;

				if (pos + nalLen > _size)
				{
					return false;
				}

				if (NULL != dst)
				{
					appendNalAsAnnexB(*dst, _data + pos, nalLen);
				}

				pos += nalLen;
			}
		}

		_video.parameterSets.insert(_video.parameterSets.end(), vps.begin(), vps.end() );
		_video.parameterSets.insert(_video.parameterSets.end(), sps.begin(), sps.end() );
		_video.parameterSets.insert(_video.parameterSets.end(), pps.begin(), pps.end() );

		return true;
	}

	bool parseAv1C(Impl& _video, const uint8_t* _data, uint32_t _size)
	{
		if (NULL == _data
		||  _size < kBoxHeaderSize + av1::kAv1CSize)
		{
			return false;
		}

		const uint8_t* av1c = _data + kBoxHeaderSize;

		const uint8_t highBitdepth = (av1c[2] >> 6) & 1;
		const uint8_t twelveBit    = (av1c[2] >> 5) & 1;
		const uint8_t subsamplingX = (av1c[2] >> 3) & 1;
		const uint8_t subsamplingY = (av1c[2] >> 2) & 1;

		_video.profile  = av1c[1] >> 5;
		_video.level    = av1c[1] & 0x1f;
		_video.bitDepth = twelveBit ? 12 : highBitdepth ? 10 : 8;
		_video.chroma   = subsamplingX && subsamplingY ? 0
			:             subsamplingX                 ? 2
			:                                            4
			;

		Av1SequenceHeader seq;
		takeAv1SequenceHeader(_video, seq, av1c + av1::kAv1CSize, _size - kBoxHeaderSize - av1::kAv1CSize);

		return true;
	}

	lsmash_codec_specific_t* getUnstructuredCodecSpecific(lsmash_summary_t* _sum, uint32_t _idx, lsmash_codec_specific_t*& _cs)
	{
		_cs = lsmash_get_codec_specific_data(_sum, _idx + 1);

		if (NULL == _cs)
		{
			return NULL;
		}

		return LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED == _cs->format
			? _cs
			: lsmash_convert_codec_specific_format(_cs, LSMASH_CODEC_SPECIFIC_FORMAT_UNSTRUCTURED)
			;
	}

	void parseMp4CodecSpecific(Impl& _video, lsmash_summary_t* _sum, uint32_t& _lengthSize)
	{
		for (uint32_t ii = 0; ; ++ii)
		{
			lsmash_codec_specific_t* cs;
			lsmash_codec_specific_t* raw = getUnstructuredCodecSpecific(_sum, ii, cs);

			if (NULL == cs)
			{
				break;
			}

			bool done = false;

			if (NULL != raw)
			{
				const uint8_t* data = raw->data.unstructured;
				const uint32_t size = raw->size;

				if (bgfx::VideoCodec::H264 == _video.codec
				&&  LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_H264 == cs->type)
				{
					done = parseAvcC(_video, data, size, _lengthSize);
				}
				else if (bgfx::VideoCodec::H265 == _video.codec
				     &&  LSMASH_CODEC_SPECIFIC_DATA_TYPE_ISOM_VIDEO_HEVC == cs->type)
				{
					done = parseHvcC(_video, data, size, _lengthSize);
				}
				else if (bgfx::VideoCodec::AV1 == _video.codec
				     &&  LSMASH_CODEC_SPECIFIC_DATA_TYPE_UNKNOWN == cs->type
				     &&  kBoxHeaderSize <= size
				     &&  isFourCC(data + 4, "av1C") )
				{
					done = parseAv1C(_video, data, size);
				}
			}

			if (raw != cs
			&&  NULL != raw)
			{
				lsmash_destroy_codec_specific_data(raw);
			}

			if (done)
			{
				break;
			}
		}
	}

	void takeInBandParameterSets(Impl& _video)
	{
		lsmash_sample_t* s = lsmash_get_sample_from_media_timeline(_video.root, _video.trackId, 1);

		if (NULL == s)
		{
			return;
		}

		if (bgfx::VideoCodec::AV1 == _video.codec)
		{
			Av1SequenceHeader seq;
			takeAv1SequenceHeader(_video, seq, s->data, s->length);
		}
		else
		{
			const bool isHevc = bgfx::VideoCodec::H265 == _video.codec;
			H264Tables tables;
			int64_t    frameUs = 0;
			stl::vector<uint8_t> rbsp;

			visitLengthPrefixedNals(s->data, s->length, _video.lengthSize, [&](const uint8_t* _nal, uint32_t _nalLen)
			{
				if (0 == _nalLen)
				{
					return;
				}

				bool keep;

				if (isHevc)
				{
					keep = hevc::kNalHeaderSize <= _nalLen && hevc::isParameterSet(hevc::getNalUnitType(_nal) );
				}
				else
				{
					const uint8_t type = _nal[0] & kH264NalUnitTypeMask;
					keep = h264::NAL_UNIT_TYPE_SPS == type || h264::NAL_UNIT_TYPE_PPS == type;

					if (keep)
					{
						stripEmulationPrevention(rbsp, _nal, _nalLen);
						parseH264ParameterSet(tables, _video, frameUs, rbsp.data(), uint32_t(rbsp.size() ) );
					}
				}

				if (keep)
				{
					appendNalAsAnnexB(_video.parameterSets, _nal, _nalLen);
				}
			});
		}

		lsmash_delete_sample(s);
	}

	bool loadMp4(Impl& _video, const char* _path)
	{
		lsmash_root_t* root = lsmash_create_root();

		if (NULL == root)
		{
			return false;
		}

		lsmash_file_parameters_t fp = {};

		if (lsmash_open_file(_path, 1, &fp) < 0)
		{
			lsmash_destroy_root(root);
			return false;
		}

		_video.root     = root;
		_video.fp       = fp;
		_video.fpOpened = true;

		lsmash_file_t* fh = lsmash_set_file(root, &fp);

		if (NULL == fh
		||  lsmash_read_file(fh, &fp) < 0)
		{
			return false;
		}

		lsmash_movie_parameters_t mp;
		lsmash_initialize_movie_parameters(&mp);

		if (lsmash_get_movie_parameters(root, &mp) < 0)
		{
			return false;
		}

		uint32_t trackId = 0;
		lsmash_media_parameters_t md;
		lsmash_initialize_media_parameters(&md);

		for (uint32_t ii = 0; ii < mp.number_of_tracks; ++ii)
		{
			const uint32_t tid = lsmash_get_track_ID(root, ii + 1);

			if (0 == tid)
			{
				continue;
			}

			lsmash_initialize_media_parameters(&md);

			if (lsmash_get_media_parameters(root, tid, &md) < 0)
			{
				continue;
			}

			if (md.handler_type == ISOM_MEDIA_HANDLER_TYPE_VIDEO_TRACK)
			{
				trackId = tid;
				break;
			}
		}

		if (0 == trackId)
		{
			return false;
		}

		lsmash_summary_t* sum = lsmash_get_summary(root, trackId, 1);

		if (NULL == sum)
		{
			return false;
		}

		if (lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_AVC1_VIDEO)
		||  lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_AVC2_VIDEO)
		||  lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_AVC3_VIDEO)
		||  lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_AVC4_VIDEO) )
		{
			_video.codec = bgfx::VideoCodec::H264;
		}
		else if (lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_HVC1_VIDEO)
		     ||  lsmash_check_codec_type_identical(sum->sample_type, ISOM_CODEC_TYPE_HEV1_VIDEO) )
		{
			_video.codec = bgfx::VideoCodec::H265;
		}
		else if (LSMASH_4CC('a', 'v', '0', '1') == sum->sample_type.fourcc)
		{
			_video.codec = bgfx::VideoCodec::AV1;
		}
		else
		{
			lsmash_cleanup_summary(sum);
			return false;
		}

		const lsmash_video_summary_t* vsum = (const lsmash_video_summary_t*)sum;
		_video.width  = uint16_t(vsum->width);
		_video.height = uint16_t(vsum->height);

		uint32_t lengthSize = 4;
		parseMp4CodecSpecific(_video, sum, lengthSize);
		lsmash_cleanup_summary(sum);

		_video.trackId    = trackId;
		_video.lengthSize = lengthSize;

		if (lsmash_construct_timeline(root, trackId) < 0)
		{
			return false;
		}

		if (_video.parameterSets.empty() )
		{
			takeInBandParameterSets(_video);
		}

		const uint32_t timescale  = bx::max<uint32_t>(md.timescale, 1);
		const uint32_t numSamples = lsmash_get_sample_count_in_media_timeline(root, trackId);

		_video.frames.reserve(numSamples);

		for (uint32_t ii = 0; ii < numSamples; ++ii)
		{
			lsmash_sample_t s = {};

			if (0 != lsmash_get_sample_info_from_media_timeline(root, trackId, ii + 1, &s) )
			{
				break;
			}

			_video.frames.push_back(
				{
					.ptsUs      = s.cts * 1000000ull / timescale,
					.offset     = 0,
					.size       = s.length,
					.isKeyframe = 0 != (s.prop.ra_flags & ISOM_SAMPLE_RANDOM_ACCESS_FLAG_SYNC),
				});

			_video.totalBytes += s.length;
		}

		return !_video.frames.empty()
			&& !_video.parameterSets.empty()
			;
	}

	bool loadVideoFile(Impl& _video, const char* _path)
	{
		const bx::FilePath filePath(_path);
		Probe probe;

		if (!probeFile(filePath, probe) )
		{
			return false;
		}

		_video.container = probe.container;
		_video.codec     = probe.codec;

		if (Impl::Mp4 == probe.container)
		{
			return loadMp4(_video, _path);
		}

		bx::Error err;

		if (!bx::open(&_video.reader, filePath, &err) )
		{
			return false;
		}

		_video.readerOpened = true;
		_video.fileSize     = uint64_t(bx::seek(&_video.reader, 0, bx::Whence::End) );
		bx::seek(&_video.reader, 0, bx::Whence::Begin);

		switch (probe.container)
		{
		case Impl::AnnexB: return indexAnnexB(_video);
		case Impl::Obu:    return indexObu(_video);
		case Impl::Ivf:    return indexIvf(_video);
		default:           break;
		}

		return false;
	}

} // namespace

VideoPlayer::VideoPlayer()
	: m_impl(NULL)
	, m_isOpen(false)
	, m_hasError(false)
	, m_paused(false)
	, m_pendingSet(false)
	, m_width(0)
	, m_height(0)
	, m_durationUs(0)
	, m_playbackTimeUs(0)
	, m_lastTickHpc(0)
	, m_nextAuToSubmit(0)
	, m_lastSetIdr(UINT32_MAX)
	, m_playbackRate(1.0f)
	, m_aMarkerUs(-1)
	, m_bMarkerUs(-1)
	, m_videoTexture(BGFX_INVALID_HANDLE)
	, m_format(bgfx::TextureFormat::Count)
{
}

VideoPlayer::~VideoPlayer()
{
	close();
}

bool VideoPlayer::isVideoFile(const bx::FilePath& _filePath)
{
	Probe probe;
	return probeFile(_filePath, probe);
}

bool VideoPlayer::open(const char* _filePath)
{
	close();

	m_impl = BX_NEW(entry::getAllocator(), Impl);

	if (NULL == m_impl)
	{
		m_hasError = true;
		return false;
	}

	if (!loadVideoFile(*m_impl, _filePath) )
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
		m_hasError = true;

		return false;
	}

	m_width  = m_impl->width;
	m_height = m_impl->height;

	const bgfx::Caps* caps = bgfx::getCaps();

	m_format = 0 != (caps->formats[bgfx::TextureFormat::RGBA8] & BGFX_CAPS_FORMAT_TEXTURE_VIDEO_DECODE_DST)
		? bgfx::TextureFormat::RGBA8
		: bgfx::TextureFormat::BGRA8
		;

	const bool codecAvailable  = 0 != (caps->supported & BGFX_CAPS_VIDEO_DECODE);
	const bool targetSupported = 0 != (caps->formats[m_format] & BGFX_CAPS_FORMAT_TEXTURE_VIDEO_DECODE_DST);
	const bool codecValid = bgfx::isVideoCodecValid(
		  m_impl->codec
		, m_impl->chroma
		, m_impl->bitDepth
		, m_impl->width
		, m_impl->height
		, m_impl->maxDpbSlots
		, m_impl->maxActiveReferences
		);

	if (!codecAvailable
	||  !targetSupported
	||  !codecValid)
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
		m_hasError = true;
		return false;
	}

	const uint32_t psSize    = uint32_t(m_impl->parameterSets.size() );
	const uint32_t totalSize = uint32_t(sizeof(bgfx::VideoDecoderInit) ) + psSize;

	const uint64_t durationUs    = bx::max<uint64_t>(m_impl->frames.back().ptsUs, 1);
	const uint64_t bytesPerSec   = m_impl->totalBytes * 1000000ull / durationUs;
	const uint32_t cachedAuBytes = uint32_t(bx::clamp<uint64_t>(bytesPerSec * kCacheWindowUs / 1000000ull, kMinCachedAuBytes, UINT32_MAX) );

	const bgfx::Memory* mem = bgfx::alloc(totalSize);

	bgfx::VideoDecoderInit* decInit = (bgfx::VideoDecoderInit*)mem->data;
	*decInit =
	{
		.magic             = BX_MAKEFOURCC('V', 'D', 'I', 0x0),
		.codec             = m_impl->codec,
		.parameterSets     = mem->data + sizeof(bgfx::VideoDecoderInit),
		.parameterSetsSize = psSize,
		.cachedAuBytes     = cachedAuBytes,
		.flags             = 0,
	};

	bx::memCopy(
		  mem->data + sizeof(bgfx::VideoDecoderInit)
		, m_impl->parameterSets.data()
		, psSize
		);

	m_videoTexture = bgfx::createTexture2D(
		  m_width
		, m_height
		, false
		, 1
		, m_format
		, BGFX_SAMPLER_U_CLAMP
		| BGFX_SAMPLER_V_CLAMP
		, mem
		);

	if (!bgfx::isValid(m_videoTexture) )
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl     = NULL;
		m_hasError = true;

		return false;
	}

	m_durationUs     = m_impl->frames.back().ptsUs;
	m_playbackTimeUs = 0;
	m_lastTickHpc    = bx::getHPCounter();
	m_nextAuToSubmit = 0;
	m_lastSetIdr     = UINT32_MAX;
	m_playbackRate   = 1.0f;
	m_paused         = false;
	m_pendingSet     = false;
	m_aMarkerUs      = -1;
	m_bMarkerUs      = -1;
	m_isOpen         = true;
	m_hasError       = false;

	submitAccessUnitsUpTo(kLookaheadUs);

	return true;
}

void VideoPlayer::close()
{
	if (bgfx::isValid(m_videoTexture) )
	{
		bgfx::destroy(m_videoTexture);
		m_videoTexture = BGFX_INVALID_HANDLE;
	}

	if (NULL != m_impl)
	{
		bx::deleteObject(entry::getAllocator(), m_impl);
		m_impl = NULL;
	}

	m_isOpen         = false;
	m_hasError       = false;
	m_paused         = false;
	m_pendingSet     = false;
	m_width          = 0;
	m_height         = 0;
	m_durationUs     = 0;
	m_playbackTimeUs = 0;
	m_nextAuToSubmit = 0;
	m_lastSetIdr     = UINT32_MAX;
	m_playbackRate   = 1.0f;
	m_aMarkerUs      = -1;
	m_bMarkerUs      = -1;
}

bgfx::VideoCodec::Enum VideoPlayer::codec() const
{
	return NULL != m_impl ? m_impl->codec : bgfx::VideoCodec::Count;
}

uint32_t VideoPlayer::findIdrAtOrBefore(uint64_t _ptsUs) const
{
	if (NULL == m_impl
	||  m_impl->frames.empty() )
	{
		return 0;
	}

	uint32_t lastIdr = 0;

	for (uint32_t ii = 0; ii < uint32_t(m_impl->frames.size() ); ++ii)
	{
		if (m_impl->frames[ii].ptsUs > _ptsUs)
		{
			break;
		}

		if (m_impl->frames[ii].isKeyframe)
		{
			lastIdr = ii;
		}
	}

	return lastIdr;
}

uint32_t VideoPlayer::findIdrAtOrAfter(uint64_t _ptsUs) const
{
	if (NULL == m_impl
	||  m_impl->frames.empty() )
	{
		return 0;
	}

	const uint32_t numFrames = uint32_t(m_impl->frames.size() );

	for (uint32_t ii = 0; ii < numFrames; ++ii)
	{
		if (m_impl->frames[ii].ptsUs >= _ptsUs
		&&  m_impl->frames[ii].isKeyframe)
		{
			return ii;
		}
	}

	return numFrames;
}

uint32_t VideoPlayer::findFrameAtOrBefore(uint64_t _ptsUs) const
{
	if (NULL == m_impl
	||  m_impl->frames.empty() )
	{
		return 0;
	}

	const uint32_t numFrames = uint32_t(m_impl->frames.size() );
	uint32_t       result    = 0;

	for (uint32_t ii = 0; ii < numFrames; ++ii)
	{
		if (m_impl->frames[ii].ptsUs > _ptsUs)
		{
			break;
		}

		result = ii;
	}

	return result;
}

void VideoPlayer::submitDecodeFrame(uint32_t _index, bool _setPosition)
{
	const Impl::Frame& f = m_impl->frames[_index];

	stl::vector<uint8_t>& scratch = m_impl->scratch;
	scratch.clear();

	if (Impl::Mp4 == m_impl->container)
	{
		lsmash_sample_t* s = lsmash_get_sample_from_media_timeline(
			  m_impl->root
			, m_impl->trackId
			, _index + 1
			);

		if (NULL == s)
		{
			return;
		}

		if (bgfx::VideoCodec::AV1 == m_impl->codec)
		{
			scratch.insert(scratch.end(), s->data, s->data + s->length);
		}
		else
		{
			avccToAnnexB(scratch, s->data, s->length, m_impl->lengthSize);
		}

		lsmash_delete_sample(s);
	}
	else
	{
		scratch.resize(f.size);

		bx::Error err;
		bx::seek(&m_impl->reader, int64_t(f.offset), bx::Whence::Begin);
		const int32_t read = bx::read(&m_impl->reader, scratch.data(), int32_t(f.size), &err);

		if (!err.isOk()
		||  uint32_t(read) != f.size)
		{
			return;
		}
	}

	struct Payload
	{
		bgfx::VideoDecoderFrame frame;
		bgfx::VideoDecoderAu    au;
	};

	const uint32_t bitstreamSize = uint32_t(scratch.size() );
	const uint32_t totalSize     = uint32_t(sizeof(Payload) ) + bitstreamSize;

	const bgfx::Memory* mem = bgfx::alloc(totalSize);
	Payload* dstPayload     = (Payload*)mem->data;
	uint8_t* dstBitstream   = (uint8_t*)(dstPayload + 1);

	bx::memCopy(dstBitstream, scratch.data(), bitstreamSize);

	dstPayload->au =
	{
		.size  = bitstreamSize,
		.ptsUs = int64_t(f.ptsUs),
	};

	dstPayload->frame =
	{
		.magic              = BX_MAKEFOURCC('V', 'D', 'F', 0x0),
		.bitstream          = dstBitstream,
		.aus                = &dstPayload->au,
		.numAus             = 1,
		.presentationTimeUs = 0,
		.flags              = uint8_t(_setPosition
			? BGFX_VIDEO_DECODE_FRAME_SET
			: BGFX_VIDEO_DECODE_FRAME_NONE
			),
	};

	bgfx::updateTexture2D(
		  m_videoTexture
		, 0
		, 0
		, 0, 0
		, m_width
		, m_height
		, mem
		);
}

void VideoPlayer::submitAccessUnitsUpTo(int64_t _untilPtsUs)
{
	if (NULL == m_impl)
	{
		return;
	}

	uint32_t submitted = 0;

	while (m_nextAuToSubmit < uint32_t(m_impl->frames.size() )
		&& int64_t(m_impl->frames[m_nextAuToSubmit].ptsUs) <= _untilPtsUs
		&& submitted < kMaxSubmitPerCall)
	{
		submitDecodeFrame(m_nextAuToSubmit, m_pendingSet);
		m_pendingSet = false;
		++m_nextAuToSubmit;
		++submitted;
	}
}

void VideoPlayer::submitPresentationTick(int64_t _presentationTimeUs)
{
	const bgfx::VideoDecoderFrame desc =
	{
		.magic              = BX_MAKEFOURCC('V', 'D', 'F', 0x0),
		.bitstream          = NULL,
		.aus                = NULL,
		.numAus             = 0,
		.presentationTimeUs = _presentationTimeUs,
		.flags              = BGFX_VIDEO_DECODE_FRAME_NONE,
	};

	bgfx::updateTexture2D(
		  m_videoTexture
		, 0
		, 0
		, 0, 0
		, m_width
		, m_height
		, bgfx::copy(&desc, sizeof(desc) )
		);
}

void VideoPlayer::tick()
{
	if (!m_isOpen)
	{
		return;
	}

	const int64_t nowHpc   = bx::getHPCounter();
	const int64_t deltaHpc = nowHpc - m_lastTickHpc;
	m_lastTickHpc = nowHpc;

	if (!m_paused)
	{
		m_lastSetIdr = UINT32_MAX;

		const uint64_t deltaUs = uint64_t(double(deltaHpc) * 1000000.0 * double(m_playbackRate) / double(bx::getHPFrequency() ) );
		m_playbackTimeUs += deltaUs;

		if (m_aMarkerUs >= 0
		&&  m_bMarkerUs >  m_aMarkerUs
		&&  int64_t(m_playbackTimeUs) >= m_bMarkerUs)
		{
			seekTo(uint64_t(m_aMarkerUs) );
		}
		else if (m_playbackTimeUs > m_durationUs)
		{
			seekTo(m_aMarkerUs >= 0 ? uint64_t(m_aMarkerUs) : 0);
		}
	}

	submitPresentationTick(int64_t(m_playbackTimeUs) );
	submitAccessUnitsUpTo(int64_t(m_playbackTimeUs) + kLookaheadUs);
}

void VideoPlayer::seekTo(uint64_t _targetUs)
{
	if (!m_isOpen
	||  NULL == m_impl)
	{
		return;
	}

	const uint64_t target = bx::min(_targetUs, m_durationUs);

	const uint32_t idr         = findIdrAtOrBefore(target);
	const uint32_t targetFrame = findFrameAtOrBefore(target);
	const bool     needReprime =
		   targetFrame < m_nextAuToSubmit
		|| idr         > m_nextAuToSubmit
		;

	if (needReprime
	&&  idr != m_lastSetIdr)
	{
		m_nextAuToSubmit = idr;
		m_pendingSet     = true;
		m_lastSetIdr     = idr;
	}

	m_playbackTimeUs = m_paused
		? target
		: m_impl->frames[idr].ptsUs
		;
	m_lastTickHpc    = bx::getHPCounter();
}

void VideoPlayer::seekRelative(int64_t _deltaUs)
{
	if (!m_isOpen
	||  NULL == m_impl)
	{
		return;
	}

	m_lastSetIdr = UINT32_MAX;

	int64_t target = int64_t(m_playbackTimeUs) + _deltaUs;

	int64_t lo = 0;
	int64_t hi = int64_t(m_durationUs);

	if (m_aMarkerUs >= 0
	&&  m_bMarkerUs > m_aMarkerUs)
	{
		lo = m_aMarkerUs;
		hi = m_bMarkerUs;
	}

	if (_deltaUs > 0
	&&  target > hi)
	{
		seekTo(uint64_t(lo) );
		return;
	}

	target = bx::clamp(target, lo, hi);

	if (_deltaUs > 0)
	{
		const uint32_t idrBefore    = findIdrAtOrBefore(uint64_t(target) );
		const uint64_t idrBeforePts = m_impl->frames[idrBefore].ptsUs;

		if (idrBeforePts <= m_playbackTimeUs)
		{
			const uint32_t numFrames = uint32_t(m_impl->frames.size() );
			const uint32_t idrAfter  = findIdrAtOrAfter(m_playbackTimeUs + 1);

			if (idrAfter < numFrames)
			{
				m_nextAuToSubmit = idrAfter;
				m_pendingSet     = true;
				m_lastSetIdr     = idrAfter;
				m_playbackTimeUs = m_impl->frames[idrAfter].ptsUs;
				m_lastTickHpc    = bx::getHPCounter();
				return;
			}

			return;
		}
	}

	seekTo(uint64_t(target) );
}

void VideoPlayer::restart()
{
	if (!m_isOpen)
	{
		return;
	}

	m_lastSetIdr = UINT32_MAX;
	seekTo(m_aMarkerUs >= 0 ? uint64_t(m_aMarkerUs) : 0);
}

void VideoPlayer::togglePause()
{
	if (!m_isOpen)
	{
		return;
	}

	m_paused = !m_paused;

	m_lastTickHpc = bx::getHPCounter();
}

void VideoPlayer::rateUp()
{
	if (!m_isOpen)
	{
		return;
	}

	m_playbackRate = bx::min(m_playbackRate * kRateStepFactor, kRateMax);
}

void VideoPlayer::rateDown()
{
	if (!m_isOpen)
	{
		return;
	}

	m_playbackRate = bx::max(m_playbackRate / kRateStepFactor, kRateMin);
}

void VideoPlayer::cycleAbMarker()
{
	if (!m_isOpen)
	{
		return;
	}

	if (m_aMarkerUs < 0)
	{
		m_aMarkerUs = int64_t(m_playbackTimeUs);
		m_bMarkerUs = -1;
	}
	else if (m_bMarkerUs < 0)
	{
		int64_t b = int64_t(m_playbackTimeUs);

		if (b < m_aMarkerUs)
		{
			m_bMarkerUs = m_aMarkerUs;
			m_aMarkerUs = b;
		}
		else
		{
			m_bMarkerUs = b;
		}
	}
	else
	{
		m_aMarkerUs = -1;
		m_bMarkerUs = -1;
	}
}
