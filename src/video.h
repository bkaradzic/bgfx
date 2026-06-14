/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VIDEO_H_HEADER_GUARD
#define BGFX_VIDEO_H_HEADER_GUARD

#include <h264/h264.h>

namespace bgfx
{
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

				if (sps.seq_parameter_set_id < (int)_spsArrayLen)
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

				if (pps.pic_parameter_set_id < (int)_ppsArrayLen)
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

			if (h264::NAL_UNIT_TYPE_SPS == nal.type)
			{
				h264::SPS sps = {};
				h264::read_sps(&sps, &nalBs);

				if (sps.seq_parameter_set_id < 32)
				{
					const_cast<h264::SPS*>(_spsArray)[sps.seq_parameter_set_id] = sps;
				}

				bs.p = nalStart + nalSize;
				bs.bits_left = 8;

				continue;
			}

			if (h264::NAL_UNIT_TYPE_PPS == nal.type)
			{
				h264::PPS pps = {};
				h264::read_pps(&pps, &nalBs);

				if (pps.pic_parameter_set_id < 256)
				{
					_ppsArray[pps.pic_parameter_set_id] = pps;
				}

				bs.p = nalStart + nalSize;
				bs.bits_left = 8;

				continue;
			}

			if (h264::NAL_UNIT_TYPE_CODED_SLICE_NON_IDR == nal.type
			||  h264::NAL_UNIT_TYPE_CODED_SLICE_IDR     == nal.type)
			{
				h264::SliceHeader sh = {};
				h264::read_slice_header(&sh, &nal, _ppsArray, const_cast<h264::SPS*>(_spsArray), &nalBs);

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

	inline int64_t applyLoopWrap(int64_t _ptsUs, int64_t _minPts, int64_t _maxPts)
	{
		if (_minPts >= _maxPts
		||  _ptsUs  <= _maxPts)
		{
			return _ptsUs;
		}

		const int64_t span = _maxPts - _minPts + 1;
		const int64_t wrapped = ( (_ptsUs - _minPts) % span) + _minPts;
		return wrapped;
	}

	template <typename ReorderEntryT>
	inline bool reorderPoolCovers(
		  const ReorderEntryT* _pool
		, uint32_t             _count
		, int64_t              _ptsUs
		, int64_t              _toleranceUs
		)
	{
		for (uint32_t ii = 0; ii < _count; ++ii)
		{
			if (-1 != _pool[ii].displayOrder)
			{
				const int64_t diff = _pool[ii].ptsUs >= _ptsUs
					? _pool[ii].ptsUs - _ptsUs
					: _ptsUs - _pool[ii].ptsUs
					;

				if (diff <= _toleranceUs)
				{
					return true;
				}
			}
		}
		return false;
	}

	template <typename ResetFn, typename DecodeOneFn, typename HasSpaceFn>
	inline bool faultInFromCache(
		  AuCache&    _cache
		, int64_t     _ptsUs
		, ResetFn     _reset
		, DecodeOneFn _decodeOne
		, HasSpaceFn  _hasReorderSpace
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

		while (!_cache.empty()
		&&     _hasReorderSpace() )
		{
			const PendingAU& au = _cache.front();
			_decodeOne(au.data.data(), uint32_t(au.data.size() ), au.ptsUs);

			const bool reachedTarget = au.ptsUs >= _ptsUs;
			_cache.pop();

			if (reachedTarget)
			{
				break;
			}
		}

		return true;
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
		if (-1 == _displayedSlot)
		{
			int32_t bestSlot = -1;
			int64_t minPts   = INT64_MAX;
			int64_t maxPts   = INT64_MIN;

			for (uint32_t ii = 0; ii < _poolCount; ++ii)
			{
				if (-1 != _pool[ii].displayOrder)
				{
					if (_pool[ii].ptsUs < minPts)
					{
						minPts   = _pool[ii].ptsUs;
						bestSlot = int32_t(ii);
					}

					if (_pool[ii].ptsUs > maxPts)
					{
						maxPts = _pool[ii].ptsUs;
					}
				}
			}

			if (-1 == bestSlot)
			{
				return;
			}

			if (minPts == maxPts
			&& !_streamDrained)
			{
				return;
			}

			_displayedSlot = bestSlot;
			_dispatch(uint32_t(_displayedSlot) );

			return;
		}

		const int64_t curPts = _pool[_displayedSlot].ptsUs;

		if (_presentationTimeUs + 500000 < curPts)
		{
			int32_t snapSlot = -1;
			int64_t minPts   = INT64_MAX;
			for (uint32_t ii = 0; ii < _poolCount; ++ii)
			{
				if (-1 != _pool[ii].displayOrder
				&&  _pool[ii].ptsUs <  curPts
				&&  _pool[ii].ptsUs <  minPts)
				{
					minPts   = _pool[ii].ptsUs;
					snapSlot = int32_t(ii);
				}
			}

			if (-1 == snapSlot)
			{
				return;
			}

			if (-1 != _prevDisplayedSlot)
			{
				_pool[_prevDisplayedSlot].displayOrder = -1;
			}

			_prevDisplayedSlot = _displayedSlot;
			_displayedSlot     = snapSlot;
			_dispatch(uint32_t(_displayedSlot) );

			return;
		}

		if (_presentationTimeUs > curPts + 500000)
		{
			int32_t jumpSlot = -1;
			int64_t bestPts  = curPts;
			for (uint32_t ii = 0; ii < _poolCount; ++ii)
			{
				if (-1 != _pool[ii].displayOrder
				&&  _pool[ii].ptsUs >  bestPts
				&&  _pool[ii].ptsUs <= _presentationTimeUs)
				{
					bestPts  = _pool[ii].ptsUs;
					jumpSlot = int32_t(ii);
				}
			}

			if (-1 != jumpSlot)
			{
				if (-1 != _prevDisplayedSlot)
				{
					_pool[_prevDisplayedSlot].displayOrder = -1;
				}

				_prevDisplayedSlot = _displayedSlot;
				_displayedSlot     = jumpSlot;
				_dispatch(uint32_t(_displayedSlot) );

				return;
			}
		}

		int32_t nextSlot = -1;
		int64_t nextPts  = INT64_MAX;
		int64_t maxPts   = INT64_MIN;

		for (uint32_t ii = 0; ii < _poolCount; ++ii)
		{
			if (-1 != _pool[ii].displayOrder)
			{
				if (_pool[ii].ptsUs > maxPts)
				{
					maxPts = _pool[ii].ptsUs;
				}

				if (_pool[ii].ptsUs >  curPts
				&&  _pool[ii].ptsUs <  nextPts)
				{
					nextPts  = _pool[ii].ptsUs;
					nextSlot = int32_t(ii);
				}
			}
		}

		if (-1 == nextSlot)
		{
			return;
		}

		if (_presentationTimeUs < nextPts)
		{
			return;
		}

		if (nextPts == maxPts && !_streamDrained)
		{
			return;
		}

		if (-1 != _prevDisplayedSlot)
		{
			_pool[_prevDisplayedSlot].displayOrder = -1;
		}

		_prevDisplayedSlot = _displayedSlot;
		_displayedSlot     = nextSlot;
		_dispatch(uint32_t(_displayedSlot) );
	}
}

#endif // BGFX_VIDEO_H_HEADER_GUARD
