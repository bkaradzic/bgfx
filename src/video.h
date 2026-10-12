/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VIDEO_H_HEADER_GUARD
#define BGFX_VIDEO_H_HEADER_GUARD

#include <h264/h264.h>

namespace bgfx
{
	inline uint32_t getDecodableCodecCaps(VideoCodec::Enum _codec)
	{
		return VideoCodec::H264 == _codec
			? BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
			: 0
			;
	}

	struct VideoPictureRect
	{
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
	};

	inline VideoPictureRect getPictureRect(const h264::SPS& _sps)
	{
		const uint32_t frameMbsOnly = 0 != _sps.frame_mbs_only_flag ? 1 : 0;
		const uint32_t codedWidth   = uint32_t(_sps.pic_width_in_mbs_minus1 + 1) * 16;
		const uint32_t codedHeight  = uint32_t(_sps.pic_height_in_map_units_minus1 + 1) * 16 * (2 - frameMbsOnly);

		if (0 == _sps.frame_cropping_flag)
		{
			return { .x = 0, .y = 0, .width = codedWidth, .height = codedHeight };
		}

		const uint32_t cropUnitX = 2;
		const uint32_t cropUnitY = 2 * (2 - frameMbsOnly);
		const uint32_t left      = uint32_t(_sps.frame_crop_left_offset)   * cropUnitX;
		const uint32_t right     = uint32_t(_sps.frame_crop_right_offset)  * cropUnitX;
		const uint32_t top       = uint32_t(_sps.frame_crop_top_offset)    * cropUnitY;
		const uint32_t bottom    = uint32_t(_sps.frame_crop_bottom_offset) * cropUnitY;

		if (left + right  >= codedWidth
		||  top  + bottom >= codedHeight)
		{
			return { .x = 0, .y = 0, .width = codedWidth, .height = codedHeight };
		}

		return
		{
			.x      = left,
			.y      = top,
			.width  = codedWidth  - left - right,
			.height = codedHeight - top  - bottom,
		};
	}

	inline void getYuvToRgb(float _result[12], uint8_t _matrixCoefficients, bool _fullRange)
	{
		float kr = 0.2126f;
		float kb = 0.0722f;

		switch (_matrixCoefficients)
		{
		case 4:  kr = 0.30f;   kb = 0.11f;   break;
		case 5:
		case 6:  kr = 0.299f;  kb = 0.114f;  break;
		case 7:  kr = 0.212f;  kb = 0.087f;  break;
		case 9:
		case 10: kr = 0.2627f; kb = 0.0593f; break;
		default: break;
		}

		const float kg  = 1.0f - kr - kb;
		const float crR =  2.0f * (1.0f - kr);
		const float cbG = -2.0f * kb * (1.0f - kb) / kg;
		const float crG = -2.0f * kr * (1.0f - kr) / kg;
		const float cbB =  2.0f * (1.0f - kb);

		const float yScale  = _fullRange ? 1.0f : 255.0f/219.0f;
		const float yOffset = _fullRange ? 0.0f :  16.0f/255.0f;
		const float cScale  = _fullRange ? 1.0f : 255.0f/224.0f;
		const float cOffset = 128.0f/255.0f;

		const float tmp0 = -yScale * yOffset;
		const float tmp1 =  cScale * cOffset;

		_result[ 0] = yScale;
		_result[ 1] = 0.0f;
		_result[ 2] = crR * cScale;
		_result[ 3] = tmp0 - crR * tmp1;

		_result[ 4] = yScale;
		_result[ 5] = cbG * cScale;
		_result[ 6] = crG * cScale;
		_result[ 7] = tmp0 - (cbG + crG) * tmp1;

		_result[ 8] = yScale;
		_result[ 9] = cbB * cScale;
		_result[10] = 0.0f;
		_result[11] = tmp0 - cbB * tmp1;
	}

	inline void getYuvToRgb(float _result[12], const h264::SPS& _sps)
	{
		const bool signalType = true
			&& 0 != _sps.vui_parameters_present_flag
			&& 0 != _sps.vui.video_signal_type_present_flag
			;

		const bool colourDescription = true
			&& signalType
			&& 0 != _sps.vui.colour_description_present_flag
			;

		getYuvToRgb(
			  _result
			, colourDescription ? uint8_t(_sps.vui.matrix_coefficients) : 2
			, signalType && 0 != _sps.vui.video_full_range_flag
			);
	}

	inline uint32_t stripEmulationPrevention(uint8_t* _dst, const uint8_t* _src, uint32_t _size)
	{
		uint32_t dstIdx = 0;
		uint32_t zeros  = 0;

		for (uint32_t ii = 0; ii < _size; ++ii)
		{
			const uint8_t b = _src[ii];

			if (zeros >= 2 && 0x03 == b)
			{
				zeros = 0;
				continue;
			}

			_dst[dstIdx++] = b;
			zeros = (0 == b) ? zeros + 1 : 0;
		}

		return dstIdx;
	}

	inline uint32_t nalUnitSize(const uint8_t* _data, uint32_t _size)
	{
		if (_size < 3)
		{
			return _size;
		}

		for (uint32_t ii = 0, end = _size - 2; ii < end; ++ii)
		{
			if (0 == _data[ii] && 0 == _data[ii+1] && 1 == _data[ii+2])
			{
				uint32_t startSize = ii;

				if (startSize > 0 && 0 == _data[startSize-1])
				{
					--startSize;
				}

				return startSize;
			}
		}

		return _size;
	}

	inline int32_t computePoc(
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
				if (_prevPocLsb > _sh.frame_num)
				{
					frameNumOffset = _prevPocMsb + maxFrameNum;
				}
				else
				{
					frameNumOffset = _prevPocMsb;
				}

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
		int32_t prevPocMsb = _prevPocMsb;
		int32_t prevPocLsb = _prevPocLsb;

		if (_isIdr)
		{
			prevPocMsb = 0;
			prevPocLsb = 0;
		}

		const int32_t pocLsb = _sh.pic_order_cnt_lsb;
		int32_t pocMsb;

		if ( (pocLsb < prevPocLsb) && ( (prevPocLsb - pocLsb) >= (maxPocLsb / 2) ) )
		{
			pocMsb = prevPocMsb + maxPocLsb;
		}
		else if ( (pocLsb > prevPocLsb) && ( (pocLsb - prevPocLsb) > (maxPocLsb / 2) ) )
		{
			pocMsb = prevPocMsb - maxPocLsb;
		}
		else
		{
			pocMsb = prevPocMsb;
		}

		const int32_t poc = pocMsb + pocLsb;

		if (0 != _nal.idc)
		{
			_prevPocMsb = pocMsb;
			_prevPocLsb = pocLsb;
		}

		return poc;
	}

	static constexpr int32_t kVideoMaxH264SizeInMbsMinus1 = 1023;

	inline bool isDecodableProfile(int32_t _profileIdc)
	{
		return false
			|| h264::PROFILE_IDC_BASELINE == _profileIdc
			|| h264::PROFILE_IDC_MAIN     == _profileIdc
			|| h264::PROFILE_IDC_HIGH     == _profileIdc
			;
	}

	inline bool isSpsInRange(const h264::SPS& _sps)
	{
		return true
			&& isDecodableProfile(_sps.profile_idc)
			&& bx::isInRange(_sps.seq_parameter_set_id,                  0, h264::MAX_SPS_ID)
			&& bx::isInRange(_sps.chroma_format_idc,                     0, h264::MAX_CHROMA_FORMAT_IDC)
			&& bx::isInRange(_sps.bit_depth_luma_minus8,                 0, h264::MAX_BIT_DEPTH_MINUS8)
			&& bx::isInRange(_sps.bit_depth_chroma_minus8,               0, h264::MAX_BIT_DEPTH_MINUS8)
			&& bx::isInRange(_sps.log2_max_frame_num_minus4,             0, h264::MAX_LOG2_MINUS4)
			&& bx::isInRange(_sps.pic_order_cnt_type,                    0, h264::MAX_PIC_ORDER_CNT_TYPE)
			&& bx::isInRange(_sps.log2_max_pic_order_cnt_lsb_minus4,     0, h264::MAX_LOG2_MINUS4)
			&& bx::isInRange(_sps.num_ref_frames_in_pic_order_cnt_cycle, 0, h264::MAX_NUM_REF_FRAMES_IN_PIC_ORDER_CNT_CYCLE)
			&& bx::isInRange(_sps.num_ref_frames,                        0, h264::MAX_NUM_REF_FRAMES)
			&& bx::isInRange(_sps.pic_width_in_mbs_minus1,               0, kVideoMaxH264SizeInMbsMinus1)
			&& bx::isInRange(_sps.pic_height_in_map_units_minus1,        0, kVideoMaxH264SizeInMbsMinus1)
			;
	}

	inline bool isPpsInRange(const h264::PPS& _pps, const h264::SPS& _sps)
	{
		const int32_t qpBdOffset = h264::QP_BD_OFFSET_PER_BIT*_sps.bit_depth_luma_minus8;
		const int32_t maxQpInit  = h264::MAX_QP - h264::PIC_INIT_QP;

		return true
			&& bx::isInRange(_pps.pic_parameter_set_id,          0, h264::MAX_PPS_ID)
			&& bx::isInRange(_pps.seq_parameter_set_id,          0, h264::MAX_SPS_ID)
			&& 0 == _pps.num_slice_groups_minus1
			&& bx::isInRange(_pps.num_ref_idx_l0_active_minus1,  0, h264::MAX_NUM_REF_IDX_ACTIVE_MINUS1)
			&& bx::isInRange(_pps.num_ref_idx_l1_active_minus1,  0, h264::MAX_NUM_REF_IDX_ACTIVE_MINUS1)
			&& bx::isInRange(_pps.weighted_bipred_idc,           0, h264::MAX_WEIGHTED_BIPRED_IDC)
			&& bx::isInRange(_pps.pic_init_qp_minus26,           -h264::PIC_INIT_QP - qpBdOffset,    maxQpInit)
			&& bx::isInRange(_pps.pic_init_qs_minus26,           -h264::PIC_INIT_QP,                 maxQpInit)
			&& bx::isInRange(_pps.chroma_qp_index_offset,        -h264::MAX_CHROMA_QP_INDEX_OFFSET, h264::MAX_CHROMA_QP_INDEX_OFFSET)
			&& bx::isInRange(_pps.second_chroma_qp_index_offset, -h264::MAX_CHROMA_QP_INDEX_OFFSET, h264::MAX_CHROMA_QP_INDEX_OFFSET)
			;
	}

	inline bool isSliceHeaderInRange(const h264::SliceHeader& _sh, const h264::PPS& _pps, const h264::SPS& _sps)
	{
		const int32_t qpBdOffset   = h264::QP_BD_OFFSET_PER_BIT*_sps.bit_depth_luma_minus8;
		const int32_t sliceQp      = h264::PIC_INIT_QP + _pps.pic_init_qp_minus26 + _sh.slice_qp_delta;
		const int32_t frameHeight  = (_sps.pic_height_in_map_units_minus1 + 1) * (0 != _sps.frame_mbs_only_flag ? 1 : 2);
		const int32_t picSizeInMbs = (_sps.pic_width_in_mbs_minus1 + 1) * frameHeight;
		const int32_t mbaff        = 0 != _sps.mb_adaptive_frame_field_flag && 0 == _sh.field_pic_flag ? 1 : 0;

		return true
			&& bx::isInRange(_sh.first_mb_in_slice * (1 + mbaff), 0,           picSizeInMbs - 1)
			&& bx::isInRange(_sh.slice_type,                      0,           h264::MAX_SLICE_TYPE)
			&& bx::isInRange(sliceQp,                             -qpBdOffset, h264::MAX_QP)
			&& bx::isInRange(_sh.num_ref_idx_l0_active_minus1,    0,           h264::MAX_NUM_REF_IDX_ACTIVE_MINUS1)
			&& bx::isInRange(_sh.num_ref_idx_l1_active_minus1,    0,           h264::MAX_NUM_REF_IDX_ACTIVE_MINUS1)
			&& bx::isInRange(_sh.cabac_init_idc,                  0,           h264::MAX_CABAC_INIT_IDC)
			&& bx::isInRange(_sh.disable_deblocking_filter_idc,   0,           h264::MAX_DISABLE_DEBLOCKING_FILTER_IDC)
			&& bx::isInRange(_sh.slice_alpha_c0_offset_div2,      -h264::MAX_DEBLOCKING_OFFSET_DIV2, h264::MAX_DEBLOCKING_OFFSET_DIV2)
			&& bx::isInRange(_sh.slice_beta_offset_div2,          -h264::MAX_DEBLOCKING_OFFSET_DIV2, h264::MAX_DEBLOCKING_OFFSET_DIV2)
			&& bx::isInRange(_sh.idr_pic_id,                      0,           h264::MAX_IDR_PIC_ID)
			&& bx::isInRange(_sh.redundant_pic_cnt,               0,           h264::MAX_REDUNDANT_PIC_CNT)
			;
	}

	inline bool peekH264Sps(const uint8_t* _data, uint32_t _size, h264::SPS& _outSps)
	{
		h264::Bitstream bs;
		bs.init(_data, _size);

		while (h264::find_next_nal(&bs) )
		{
			const uint8_t* nalStart = bs.p;
			const uint32_t nalSize  = nalUnitSize(nalStart, uint32_t(bs.end - bs.p) );

			uint8_t rbsp[1024];
			const uint32_t rbspSize = stripEmulationPrevention(rbsp, nalStart, bx::min<uint32_t>(nalSize, sizeof(rbsp) ) );

			h264::Bitstream nalBs;
			nalBs.init(rbsp, rbspSize);

			h264::NALHeader nal = {};

			if (h264::read_nal_header(&nal, &nalBs)
			&&  h264::NAL_UNIT_TYPE_SPS == nal.type)
			{
				_outSps = {};
				h264::read_sps(&_outSps, &nalBs);

				return true;
			}

			bs.p         = nalStart + nalSize;
			bs.bits_left = 8;
		}

		return false;
	}

	inline bool parseParameterSets(
		  h264::SPS* _spsArray
		, uint32_t _spsArrayLen
		, h264::PPS* _ppsArray
		, uint32_t _ppsArrayLen
		, h264::SPS& _spsActive
		, h264::PPS& _ppsActive
		, const uint8_t* _data
		, uint32_t _size
		, bool* _spsValid = NULL
		, bool* _ppsValid = NULL
		)
	{
		h264::Bitstream bs;
		bs.init(_data, _size);

		bool sawSps = false;
		bool sawPps = false;

		while (h264::find_next_nal(&bs) )
		{
			const uint8_t* nalStart = bs.p;
			const uint32_t nalRemaining = uint32_t(bs.end - bs.p);
			const uint32_t nalSize = nalUnitSize(nalStart, nalRemaining);

			uint8_t rbsp[4096];
			const uint32_t rbspSize = nalSize < sizeof(rbsp)
				? stripEmulationPrevention(rbsp, nalStart, nalSize)
				: nalSize
				;
			const uint8_t* parseData = nalSize < sizeof(rbsp) ? rbsp : nalStart;
			const uint32_t parseSize = nalSize < sizeof(rbsp) ? rbspSize : nalSize;

			h264::Bitstream nalBs;
			nalBs.init(parseData, parseSize);

			h264::NALHeader nal = {};
			if (!h264::read_nal_header(&nal, &nalBs) )
			{
				break;
			}

			if (h264::NAL_UNIT_TYPE_SPS == nal.type)
			{
				h264::SPS sps = {};
				h264::read_sps(&sps, &nalBs);

				if (isSpsInRange(sps)
				&&  sps.seq_parameter_set_id < (int)_spsArrayLen)
				{
					_spsArray[sps.seq_parameter_set_id] = sps;

					if (NULL != _spsValid)
					{
						_spsValid[sps.seq_parameter_set_id] = true;
					}

					_spsActive = sps;
					sawSps = true;
				}
			}
			else if (h264::NAL_UNIT_TYPE_PPS == nal.type)
			{
				h264::PPS pps = {};
				h264::read_pps(&pps, &nalBs);

				if (bx::isInRange(pps.seq_parameter_set_id, 0, int32_t(_spsArrayLen) - 1)
				&&  isPpsInRange(pps, _spsArray[pps.seq_parameter_set_id])
				&&  pps.pic_parameter_set_id < (int)_ppsArrayLen)
				{
					_ppsArray[pps.pic_parameter_set_id] = pps;

					if (NULL != _ppsValid)
					{
						_ppsValid[pps.pic_parameter_set_id] = true;
					}

					_ppsActive = pps;
					sawPps = true;
				}
			}

			bs.p = nalStart + nalSize;
			bs.bits_left = 8;
		}

		return sawSps && sawPps;
	}

	inline bool peekAuIsIdr(const uint8_t* _data, uint32_t _size)
	{
		h264::Bitstream bs;
		bs.init(_data, _size);

		while (h264::find_next_nal(&bs) )
		{
			if (bs.p < bs.end)
			{
				const uint8_t nalType = uint8_t(*bs.p) & 0x1F;
				if (5 == nalType)
				{
					return true;
				}
			}

			const uint32_t nalRemaining = uint32_t(bs.end - bs.p);
			const uint32_t nalSize      = nalUnitSize(bs.p, nalRemaining);
			bs.p += nalSize;
			bs.bits_left = 8;
		}

		return false;
	}

	inline uint32_t findFirstSliceNalOffset(const uint8_t* _data, uint32_t _size)
	{
		h264::Bitstream bs;
		bs.init(_data, _size);

		while (h264::find_next_nal(&bs) )
		{
			if (bs.p < bs.end)
			{
				const uint8_t nalType = uint8_t(*bs.p) & 0x1F;
				if (h264::NAL_UNIT_TYPE_CODED_SLICE_NON_IDR == nalType
				||  h264::NAL_UNIT_TYPE_CODED_SLICE_IDR     == nalType)
				{
					const uint8_t* startCode = bs.p - 3;
					if (startCode > _data && 0 == startCode[-1])
					{
						--startCode;
					}

					return uint32_t(startCode - _data);
				}
			}

			const uint32_t nalRemaining = uint32_t(bs.end - bs.p);
			const uint32_t nalSize      = nalUnitSize(bs.p, nalRemaining);
			bs.p += nalSize;
			bs.bits_left = 8;
		}
		return 0;
	}

	inline uint32_t enumerateSliceNalOffsets(
		  const uint8_t* _data
		, uint32_t _size
		, uint32_t* _offsets
		, uint32_t _maxOffsets
		)
	{
		h264::Bitstream bs;
		bs.init(_data, _size);
		uint32_t count = 0;

		while (h264::find_next_nal(&bs) )
		{
			if (bs.p < bs.end)
			{
				const uint8_t nalType = uint8_t(*bs.p) & 0x1F;

				if (h264::NAL_UNIT_TYPE_CODED_SLICE_NON_IDR == nalType
				||  h264::NAL_UNIT_TYPE_CODED_SLICE_IDR     == nalType)
				{
					const uint8_t* startCode = bs.p - 3;

					if (startCode > _data && 0 == startCode[-1])
					{
						--startCode;
					}

					if (count < _maxOffsets)
					{
						_offsets[count] = uint32_t(startCode - _data);
					}

					++count;
				}
			}

			const uint32_t nalRemaining = uint32_t(bs.end - bs.p);
			const uint32_t nalSize      = nalUnitSize(bs.p, nalRemaining);
			bs.p += nalSize;
			bs.bits_left = 8;
		}
		return count;
	}

	inline bool parseSliceFromAccessUnit(
		  const h264::SPS* _spsArray
		, h264::PPS* _ppsArray
		, const uint8_t* _data
		, uint32_t _size
		, h264::NALHeader& _outNal
		, h264::SliceHeader& _outSlice
		, bool& _outIsIdr
		, const bool* _spsValid
		, const bool* _ppsValid
		)
	{
		h264::Bitstream bs;
		bs.init(_data, _size);

		while (h264::find_next_nal(&bs) )
		{
			const uint8_t* nalStart = bs.p;
			const uint32_t nalRemaining = uint32_t(bs.end - bs.p);
			const uint32_t nalSize = nalUnitSize(nalStart, nalRemaining);

			uint8_t rbsp[1024];
			const uint32_t stripIn = nalSize < uint32_t(sizeof(rbsp) ) ? nalSize : uint32_t(sizeof(rbsp) );
			const uint32_t rbspSize = stripEmulationPrevention(rbsp, nalStart, stripIn);

			h264::Bitstream nalBs;
			nalBs.init(rbsp, rbspSize);

			h264::NALHeader nal = {};
			if (!h264::read_nal_header(&nal, &nalBs) )
			{
				return false;
			}

			if (h264::NAL_UNIT_TYPE_CODED_SLICE_NON_IDR == nal.type
			||  h264::NAL_UNIT_TYPE_CODED_SLICE_IDR     == nal.type)
			{
				h264::Bitstream peek = nalBs;
				peek.ue();
				const uint32_t sliceType = peek.ue();
				const uint32_t ppsId     = peek.ue();

				if (uint32_t(h264::MAX_SLICE_TYPE) < sliceType
				||  uint32_t(h264::MAX_PPS_ID)     < ppsId
				||  !_ppsValid[ppsId])
				{
					return false;
				}

				const uint32_t spsId = uint32_t(_ppsArray[ppsId].seq_parameter_set_id);

				if (uint32_t(h264::MAX_SPS_ID) < spsId
				||  !_spsValid[spsId])
				{
					return false;
				}

				h264::SliceHeader sh = {};
				h264::read_slice_header(&sh, &nal, _ppsArray, const_cast<h264::SPS*>(_spsArray), &nalBs);

				if (0 != sh.field_pic_flag
				||  !isSliceHeaderInRange(sh, _ppsArray[ppsId], _spsArray[spsId]) )
				{
					return false;
				}

				_outNal   = nal;
				_outSlice = sh;
				_outIsIdr = (h264::NAL_UNIT_TYPE_CODED_SLICE_IDR == nal.type);

				return true;
			}

			bs.p = nalStart + nalSize;
			bs.bits_left = 8;
		}

		return false;
	}

	inline void buildEffectiveScalingLists(
		  const h264::SPS& _sps
		, const h264::PPS& _pps
		, uint8_t (&_out4x4)[6][16]
		, uint8_t (&_out8x8)[2][64]
		)
	{
		// H.264 default scaling lists in zig-zag scan order (table 7-3
		// for 4x4, table 7-4 for 8x8 with the 8x8 zig-zag scan applied).
		static const uint8_t kDefault4x4Intra[16] =
		{
			 6,13,13,20, 20,20,28,28, 28,28,32,32, 32,37,37,42,
		};

		static const uint8_t kDefault4x4Inter[16] =
		{
			10,14,14,20, 20,20,24,24, 24,24,27,27, 27,30,30,34,
		};

		static const uint8_t kDefault8x8Intra[64] =
		{
			 6,10,10,13, 11,13,16,16, 16,16,18,18, 18,18,18,23,
			23,23,23,23, 23,25,25,25, 25,25,25,25, 27,27,27,27,
			27,27,27,27, 29,29,29,29, 29,29,29,31, 31,31,31,31,
			31,33,33,33, 33,33,36,36, 36,36,38,38, 38,40,40,42,
		};

		static const uint8_t kDefault8x8Inter[64] =
		{
			 9,13,13,15, 13,15,17,17, 17,17,19,19, 19,19,19,21,
			21,21,21,21, 21,22,22,22, 22,22,22,22, 24,24,24,24,
			24,24,24,24, 25,25,25,25, 25,25,25,27, 27,27,27,27,
			27,28,28,28, 28,28,30,30, 30,30,32,32, 32,33,33,35,
		};

		uint8_t sps4[6][16] = {};
		uint8_t sps8[2][64] = {};

		const bool spsHas = !!_sps.seq_scaling_matrix_present_flag;

		auto copyDefault4 = [](uint8_t* _dst, bool _intra)
		{
			const uint8_t* src = _intra ? kDefault4x4Intra : kDefault4x4Inter;
			for (uint32_t k = 0; k < 16; ++k) { _dst[k] = src[k]; }
		};

		auto copyDefault8 = [](uint8_t* _dst, bool _intra)
		{
			const uint8_t* src = _intra ? kDefault8x8Intra : kDefault8x8Inter;
			for (uint32_t k = 0; k < 64; ++k) { _dst[k] = src[k]; }
		};

		auto copy4 = [](uint8_t* _dst, const uint8_t* _src)
		{
			for (uint32_t k = 0; k < 16; ++k) { _dst[k] = _src[k]; }
		};

		auto copy8 = [](uint8_t* _dst, const uint8_t* _src)
		{
			for (uint32_t k = 0; k < 64; ++k) { _dst[k] = _src[k]; }
		};

		auto fromInt4 = [](uint8_t* _dst, const int* _src)
		{
			for (uint32_t k = 0; k < 16; ++k) { _dst[k] = uint8_t(_src[k]); }
		};

		auto fromInt8 = [](uint8_t* _dst, const int* _src)
		{
			for (uint32_t k = 0; k < 64; ++k) { _dst[k] = uint8_t(_src[k]); }
		};

		auto fillSps4 = [&](uint32_t _i, const uint8_t* _fallback)
		{
			if (spsHas && _sps.seq_scaling_list_present_flag[_i])
			{
				if (_sps.UseDefaultScalingMatrix4x4Flag[_i])
				{
					copyDefault4(sps4[_i], _i < 3);
				}
				else
				{
					fromInt4(sps4[_i], _sps.ScalingList4x4[_i]);
				}
			}
			else
			{
				copy4(sps4[_i], _fallback);
			}
		};

		fillSps4(0, kDefault4x4Intra);
		fillSps4(1, sps4[0]);
		fillSps4(2, sps4[1]);
		fillSps4(3, kDefault4x4Inter);
		fillSps4(4, sps4[3]);
		fillSps4(5, sps4[4]);

		auto fillSps8 = [&](uint32_t _i, const uint8_t* _fallback)
		{
			if (spsHas && _sps.seq_scaling_list_present_flag[6 + _i])
			{
				if (_sps.UseDefaultScalingMatrix8x8Flag[_i])
				{
					copyDefault8(sps8[_i], 0 == _i);
				}
				else
				{
					fromInt8(sps8[_i], _sps.ScalingList8x8[_i]);
				}
			}
			else
			{
				copy8(sps8[_i], _fallback);
			}
		};

		fillSps8(0, kDefault8x8Intra);
		fillSps8(1, kDefault8x8Inter);

		const bool ppsHas = !!_pps.pic_scaling_matrix_present_flag;

		auto fillPps4 = [&](uint32_t _i, const uint8_t* _fallback)
		{
			if (ppsHas && _pps.pic_scaling_list_present_flag[_i])
			{
				if (_pps.UseDefaultScalingMatrix4x4Flag[_i])
				{
					copyDefault4(_out4x4[_i], _i < 3);
				}
				else
				{
					fromInt4(_out4x4[_i], _pps.ScalingList4x4[_i]);
				}
			}
			else
			{
				copy4(_out4x4[_i], _fallback);
			}
		};

		fillPps4(0, sps4[0]);
		fillPps4(1, _out4x4[0]);
		fillPps4(2, _out4x4[1]);
		fillPps4(3, sps4[3]);
		fillPps4(4, _out4x4[3]);
		fillPps4(5, _out4x4[4]);

		auto fillPps8 = [&](uint32_t _i, const uint8_t* _fallback)
		{
			if (ppsHas && _pps.pic_scaling_list_present_flag[6 + _i])
			{
				if (_pps.UseDefaultScalingMatrix8x8Flag[_i])
				{
					copyDefault8(_out8x8[_i], 0 == _i);
				}
				else
				{
					fromInt8(_out8x8[_i], _pps.ScalingList8x8[_i]);
				}
			}
			else
			{
				copy8(_out8x8[_i], _fallback);
			}
		};

		fillPps8(0, sps8[0]);
		fillPps8(1, sps8[1]);
	}

	inline uint32_t applyMmcoUnmarkShortTerm(
		  uint8_t* _referenceUsage
		, uint16_t* _refFrameNums
		, uint32_t _numActiveRefs
		, int32_t _currFrameNum
		, int32_t _maxFrameNum
		, const h264::SliceHeader& _sh
		)
	{
		if (0 == _sh.drpm.adaptive_ref_pic_marking_mode_flag)
		{
			return _numActiveRefs;
		}

		for (uint32_t kk = 0; kk < 64; ++kk)
		{
			const uint32_t op = _sh.drpm.memory_management_control_operation[kk];

			if (0 == op)
			{
				break;
			}

			if (1 == op)
			{
				const int32_t diff    = int32_t(_sh.drpm.difference_of_pic_nums_minus1[kk]) + 1;
				const int32_t picNumX = _currFrameNum - diff;

				for (uint32_t ii = 0; ii < _numActiveRefs; ++ii)
				{
					const int32_t fn     = int32_t(_refFrameNums[ii]);
					const int32_t fnWrap = fn > _currFrameNum ? fn - _maxFrameNum : fn;

					if (fnWrap == picNumX)
					{
						for (uint32_t jj = ii; jj + 1 < _numActiveRefs; ++jj)
						{
							_referenceUsage[jj] = _referenceUsage[jj + 1];
							_refFrameNums[jj]   = _refFrameNums[jj + 1];
						}

						--_numActiveRefs;

						break;
					}
				}
			}
			else if (5 == op)
			{
				_numActiveRefs = 0;
			}
		}

		return _numActiveRefs;
	}

	static constexpr uint32_t kVideoMaxReorderInFlight = 16;
	static constexpr uint32_t kVideoMaxH264SpsCount    = 32;
	static constexpr uint32_t kVideoMaxH264PpsCount    = 256;
	static constexpr uint32_t kMaxSlicesPerPicture     = 64;

	struct PendingAU
	{
		stl::vector<uint8_t> data;
		int64_t              ptsUs;
		int32_t              gopId;
		bool                 isIdr;

		void swap(PendingAU& _other)
		{
			data.swap(_other.data);
			int64_t tmpPts = ptsUs; ptsUs = _other.ptsUs; _other.ptsUs = tmpPts;
			int32_t tmpGop = gopId; gopId = _other.gopId; _other.gopId = tmpGop;
			bool    tmpIdr = isIdr; isIdr = _other.isIdr; _other.isIdr = tmpIdr;
		}
	};

	class AuCache
	{
	public:
		AuCache()
			: m_head(0)
			, m_softCapBytes(0)
			, m_totalBytes(0)
			, m_currentGopId(-1)
			, m_minPts(INT64_MAX)
			, m_maxPts(INT64_MIN)
			, m_retain(false)
			, m_seenAnyIdr(false)
		{
		}

		void configure(uint32_t _softCapBytes, bool _retain)
		{
			m_softCapBytes = _softCapBytes;
			m_retain       = _retain;
		}

		void enqueue(const uint8_t* _bitstream, uint32_t _size, int64_t _ptsUs, bool _isIdr)
		{
			if (_isIdr)
			{
				++m_currentGopId;
				m_seenAnyIdr = true;
			}

			m_items.emplace_back();

			PendingAU& au = m_items.back();
			au.data.resize(_size);

			bx::memCopy(au.data.data(), _bitstream, _size);

			au.ptsUs = _ptsUs;
			au.gopId = m_currentGopId;
			au.isIdr = _isIdr;

			m_totalBytes += _size;

			m_minPts = bx::min(m_minPts, _ptsUs);
			m_maxPts = bx::max(m_maxPts, _ptsUs);
		}

		bool empty() const
		{
			return m_head >= m_items.size();
		}

		const PendingAU& front() const
		{
			return m_items[m_head];
		}

		void pop()
		{
			++m_head;
		}

		void compact()
		{
			if (m_retain)
			{
				return;
			}

			dropOverSoftCap();

			if (m_head == m_items.size() && m_head > 0)
			{
				m_items.clear();
				m_head        = 0;
				m_totalBytes  = 0;
				m_minPts      = INT64_MAX;
				m_maxPts      = INT64_MIN;
				return;
			}

			if (m_head > 64)
			{
				const size_t remaining = m_items.size() - m_head;
				size_t freedBytes = 0;

				for (size_t ii = 0; ii < m_head; ++ii)
				{
					freedBytes += m_items[ii].data.size();
				}

				for (size_t ii = 0; ii < remaining; ++ii)
				{
					m_items[ii].data.swap(m_items[m_head + ii].data);
					m_items[ii].ptsUs = m_items[m_head + ii].ptsUs;
					m_items[ii].gopId = m_items[m_head + ii].gopId;
					m_items[ii].isIdr = m_items[m_head + ii].isIdr;
				}

				m_items.resize(remaining);
				m_head = 0;
				m_totalBytes -= uint32_t(freedBytes);
			}
		}

		void dropOverSoftCap()
		{
			if (0 == m_softCapBytes)
			{
				return;
			}

			size_t pendingBytes = 0;

			for (size_t ii = m_head; ii < m_items.size(); ++ii)
			{
				pendingBytes += m_items[ii].data.size();
			}

			while (pendingBytes > m_softCapBytes)
			{
				size_t nextIdr = m_head + 1;

				while (nextIdr < m_items.size()
				&&     !m_items[nextIdr].isIdr)
				{
					++nextIdr;
				}

				if (nextIdr >= m_items.size() )
				{
					break;
				}

				for (size_t ii = m_head; ii < nextIdr; ++ii)
				{
					pendingBytes -= m_items[ii].data.size();
				}

				m_head = nextIdr;
			}
		}

		void clear()
		{
			m_items.clear();
			m_head = 0;
			m_totalBytes = 0;
			m_minPts = INT64_MAX;
			m_maxPts = INT64_MIN;
			m_currentGopId = -1;
			m_seenAnyIdr   = false;
		}

		uint32_t size() const
		{
			return uint32_t(m_items.size() );
		}

		const PendingAU& at(uint32_t _idx) const
		{
			return m_items[_idx];
		}

		int32_t findRunHeadForPts(int64_t _ptsUs) const
		{
			int32_t best = -1;
			for (uint32_t ii = 0; ii < uint32_t(m_items.size() ); ++ii)
			{
				if (m_items[ii].isIdr
				&&  m_items[ii].ptsUs <= _ptsUs)
				{
					best = int32_t(ii);
				}
			}

			return best;
		}

		void rewindTo(uint32_t _idx)
		{
			m_head = _idx;
		}

		uint32_t readCursor() const
		{
			return uint32_t(m_head);
		}

		bool isRetaining() const { return m_retain; }
		bool hasIdr()    const   { return m_seenAnyIdr; }
		int64_t minPts() const   { return m_minPts; }
		int64_t maxPts() const   { return m_maxPts; }

	private:
		stl::vector<PendingAU> m_items;
		size_t                 m_head;
		uint32_t               m_softCapBytes;
		uint32_t               m_totalBytes;
		int32_t                m_currentGopId;
		int64_t                m_minPts;
		int64_t                m_maxPts;
		bool                   m_retain;
		bool                   m_seenAnyIdr;
	};

	typedef AuCache AuQueue;

	inline int64_t applyLoopWrap(int64_t _ptsUs, int64_t _minPts, int64_t _maxPts, uint32_t _numAus)
	{
		if (_minPts >= _maxPts
		||  _ptsUs  <= _maxPts
		||  2 > _numAus)
		{
			return _ptsUs;
		}

		const int64_t duration = (_maxPts - _minPts) / int64_t(_numAus - 1);
		const int64_t span     = _maxPts - _minPts + duration;
		const int64_t wrapped = ( (_ptsUs - _minPts) % span) + _minPts;
		return wrapped;
	}

	template <typename ReorderEntryT>
	inline bool reorderPoolCovers(
		  const AuCache&       _cache
		, const ReorderEntryT* _pool
		, uint32_t             _count
		, int64_t              _ptsUs
		)
	{
		int64_t targetPts = INT64_MIN;

		for (uint32_t ii = 0; ii < _cache.size(); ++ii)
		{
			const int64_t pts = _cache.at(ii).ptsUs;

			if (pts <= _ptsUs
			&&  pts >  targetPts)
			{
				targetPts = pts;
			}
		}

		if (INT64_MIN == targetPts)
		{
			return true;
		}

		for (uint32_t ii = 0; ii < _count; ++ii)
		{
			if (-1 != _pool[ii].displayOrder
			&&  targetPts == _pool[ii].ptsUs)
			{
				return true;
			}
		}

		return false;
	}

	template <typename ReorderEntryT>
	inline bool hasReorderSpace(const ReorderEntryT* _pool, uint32_t _count)
	{
		for (uint32_t ii = 0; ii < _count; ++ii)
		{
			if (-1 == _pool[ii].displayOrder)
			{
				return true;
			}
		}

		return false;
	}

	template <typename ReorderEntryT>
	inline void releaseReorderBefore(ReorderEntryT* _pool, uint32_t _count, int64_t _ptsUs)
	{
		for (uint32_t ii = 0; ii < _count; ++ii)
		{
			if (-1 != _pool[ii].displayOrder
			&&  _pool[ii].ptsUs < _ptsUs)
			{
				_pool[ii].displayOrder = -1;
			}
		}
	}

	template <typename ReorderEntryT, typename ResetFn, typename DecodeOneFn>
	inline bool faultInFromCache(
		  AuCache&       _cache
		, int64_t        _ptsUs
		, ResetFn        _reset
		, DecodeOneFn    _decodeOne
		, ReorderEntryT* _pool
		, uint32_t       _count
		)
	{
		if (!_cache.isRetaining()
		||  !_cache.hasIdr() )
		{
			return false;
		}

		const int32_t idx = _cache.findRunHeadForPts(_ptsUs);

		if (idx < 0)
		{
			return false;
		}

		_reset();
		_cache.rewindTo(uint32_t(idx) );

		int64_t bestPts = INT64_MIN;

		while (!_cache.empty()
		&&     hasReorderSpace(_pool, _count) )
		{
			const PendingAU& au = _cache.front();
			const int64_t    pts = au.ptsUs;

			_decodeOne(au.data.data(), uint32_t(au.data.size() ), pts);
			_cache.pop();

			if (pts <= _ptsUs
			&&  pts >  bestPts)
			{
				bestPts = pts;
				releaseReorderBefore(_pool, _count, bestPts);
			}
		}

		return true;
	}

	template <typename ReorderEntryT>
	inline uint32_t pickReorderSlotOrEvictOldest(const ReorderEntryT* _pool, uint32_t _count)
	{
		for (uint32_t ii = 0; ii < _count; ++ii)
		{
			if (-1 == _pool[ii].displayOrder)
			{
				return ii;
			}
		}

		uint32_t evict = 0;

		for (uint32_t ii = 1; ii < _count; ++ii)
		{
			if (_pool[ii].ptsUs < _pool[evict].ptsUs)
			{
				evict = ii;
			}
		}

		return evict;
	}

	template <typename IsPinnedFn>
	inline uint32_t pickFreeDpbSlot(
		  uint32_t _nextSlot
		, uint32_t _numDpbSlots
		, const uint8_t* _referenceUsage
		, uint32_t _numActiveRefs
		, IsPinnedFn _isPinned
		)
	{
		uint32_t pick = _nextSlot;
		for (uint32_t attempt = 0; attempt < _numDpbSlots; ++attempt)
		{
			bool inUse = false;

			for (uint32_t ii = 0; ii < _numActiveRefs && !inUse; ++ii)
			{
				if (_referenceUsage[ii] == pick)
				{
					inUse = true;
				}
			}

			if (!inUse && _isPinned(pick) )
			{
				inUse = true;
			}

			if (!inUse)
			{
				return pick;
			}
			pick = (pick + 1) % _numDpbSlots;
		}
		return UINT32_MAX;
	}

	inline uint32_t appendShortTermRef(
		  uint8_t* _referenceUsage
		, uint32_t _numActiveRefs
		, uint32_t _currentSlot
		, uint32_t _maxRefs
		)
	{
		if (0 == _maxRefs)
		{
			return _numActiveRefs;
		}

		if (_numActiveRefs < _maxRefs)
		{
			_referenceUsage[_numActiveRefs] = uint8_t(_currentSlot);
			return _numActiveRefs + 1;
		}

		bx::memMove(_referenceUsage, _referenceUsage + 1, (_maxRefs - 1) * sizeof(uint8_t) );
		_referenceUsage[_maxRefs - 1] = uint8_t(_currentSlot);

		return _maxRefs;
	}

	template <typename ReorderEntryT, typename DispatchFn>
	inline void pickDisplaySlotForTime(
		  int64_t        _presentationTimeUs
		, ReorderEntryT* _pool
		, uint32_t       _poolCount
		, int32_t&       _displayedSlot
		, int32_t&       _prevDisplayedSlot
		, bool           _streamDrained
		, DispatchFn     _dispatch
		)
	{
		int32_t minSlot  = -1;
		int64_t minPts   = INT64_MAX;
		int64_t maxPts   = INT64_MIN;

		for (uint32_t ii = 0; ii < _poolCount; ++ii)
		{
			if (-1 != _pool[ii].displayOrder)
			{
				if (_pool[ii].ptsUs < minPts)
				{
					minPts  = _pool[ii].ptsUs;
					minSlot = int32_t(ii);
				}

				maxPts = bx::max(maxPts, _pool[ii].ptsUs);
			}
		}

		if (-1 == minSlot)
		{
			return;
		}

		int32_t pickSlot = -1;
		int64_t pickPts  = INT64_MIN;

		for (uint32_t ii = 0; ii < _poolCount; ++ii)
		{
			const int64_t pts = _pool[ii].ptsUs;

			if (-1 != _pool[ii].displayOrder
			&&  pts >  pickPts
			&&  pts <= _presentationTimeUs
			&& (pts <  maxPts || _streamDrained) )
			{
				pickPts  = pts;
				pickSlot = int32_t(ii);
			}
		}

		if (-1 == pickSlot)
		{
			if (-1 != _displayedSlot
			|| (minPts == maxPts && !_streamDrained) )
			{
				return;
			}

			pickPts  = minPts;
			pickSlot = minSlot;
		}

		if (pickSlot == _displayedSlot)
		{
			return;
		}

		for (uint32_t ii = 0; ii < _poolCount; ++ii)
		{
			if (int32_t(ii) != _displayedSlot
			&&  -1 != _pool[ii].displayOrder
			&&  _pool[ii].ptsUs < pickPts)
			{
				_pool[ii].displayOrder = -1;
			}
		}

		_prevDisplayedSlot = _displayedSlot;
		_displayedSlot     = pickSlot;
		_dispatch(uint32_t(_displayedSlot) );
	}
}

#endif // BGFX_VIDEO_H_HEADER_GUARD
