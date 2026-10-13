/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_METAL
#	include "renderer_mtl.h"
#	include "video_mtl.h"

#	if BGFX_CONFIG_VIDEO_METAL
#		include "video.h"
#		include <VideoToolbox/VideoToolbox.h>
#		include <CoreMedia/CoreMedia.h>
#		include <CoreVideo/CVMetalTextureCache.h>

#		if defined(__MAC_14_0) || defined(__IPHONE_17_0)
#			define BGFX_VIDEO_METAL_AV1 1
#		else
#			define BGFX_VIDEO_METAL_AV1 0
#		endif // defined(__MAC_14_0) || defined(__IPHONE_17_0)

namespace bgfx { namespace mtl
{
	namespace hevc
	{
		enum NalUnitType
		{
			BLA_W_LP   = 16,
			BLA_W_RADL = 17,
			BLA_N_LP   = 18,
			IDR_W_RADL = 19,
			IDR_N_LP   = 20,
			CRA_NUT    = 21,
			VPS_NUT    = 32,
			SPS_NUT    = 33,
			PPS_NUT    = 34,
		};

		static constexpr uint32_t kNalHeaderSize    = 2;
		static constexpr uint32_t kNalUnitTypeShift = 1;
		static constexpr uint8_t  kNalUnitTypeMask  = 0x3f;

		inline NalUnitType getNalUnitType(const uint8_t* _nal)
		{
			return NalUnitType( (_nal[0] >> kNalUnitTypeShift) & kNalUnitTypeMask);
		}

		inline bool isIrap(NalUnitType _type)
		{
			return bx::isInRange(_type, BLA_W_LP, CRA_NUT);
		}
	}

	namespace h273
	{
		enum ColourPrimaries
		{
			CP_BT709       = 1,
			CP_UNSPECIFIED = 2,
		};

		enum TransferCharacteristics
		{
			TC_UNSPECIFIED = 2,
			TC_SRGB        = 13,
		};

		enum MatrixCoefficients
		{
			MC_IDENTITY    = 0,
			MC_BT709       = 1,
			MC_UNSPECIFIED = 2,
			MC_BT601       = 6,
			MC_SMPTE240M   = 7,
			MC_BT2020_NCL  = 9,
		};
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

		static constexpr uint32_t kObuTypeShift          = 3;
		static constexpr uint8_t  kObuTypeMask           = 0xf;
		static constexpr uint8_t  kObuExtensionFlag      = 0x4;
		static constexpr uint8_t  kObuHasSizeField       = 0x2;
		static constexpr uint32_t kObuHeaderMaxSize      = 8;
		static constexpr uint32_t kMaxLeadingZeros       = 32;
		static constexpr uint8_t  kLeb128ValueMask       = 0x7f;
		static constexpr uint8_t  kLeb128ContinuationBit = 0x80;
		static constexpr uint8_t  kAv1CMarkerVersion     = 0x81;
	}

	static constexpr uint32_t kNalLengthSize       = 4;
	static constexpr uint32_t kMaxParameterSets    = 16;
	static constexpr uint8_t  kH264NalUnitTypeMask = 0x1f;

	struct RendererContextMtl;

	void initVideoDecoder();
	PipelineStateMtl* videoGetComputePipelineState(RendererContextMtl* _renderer, ProgramHandle _handle);
	void videoEndEncoding(RendererContextMtl* _renderer);
	MTL::CommandBuffer* videoEnsureCommandBuffer(RendererContextMtl* _renderer);
	MTL::SamplerState* videoGetSamplerState(RendererContextMtl* _renderer, uint64_t _samplerFlags);

	static void freeBlockBxAlloc(void* _refcon, void* _memoryBlock, size_t _sizeInBytes)
	{
		BX_UNUSED(_refcon, _sizeInBytes);

		if (NULL != _memoryBlock)
		{
			bx::free(g_allocator, _memoryBlock);
		}
	}

	template <typename Fn>
	static uint32_t visitAnnexBNalUnits(const uint8_t* _data, uint32_t _size, Fn _visit)
	{
		uint32_t count    = 0;
		uint32_t pos      = 0;
		uint32_t nalStart = UINT32_MAX;

		while (pos + 3 < _size)
		{
			const bool sc4 = true
				&& 0 == _data[pos  ]
				&& 0 == _data[pos+1]
				&& 0 == _data[pos+2]
				&& 1 == _data[pos+3]
				;
			const bool sc3 = true
				&& 0 == _data[pos  ]
				&& 0 == _data[pos+1]
				&& 1 == _data[pos+2]
				;

			if (sc3
			||  sc4)
			{
				const uint32_t scLen = sc4 ? 4 : 3;

				if (UINT32_MAX != nalStart)
				{
					_visit(_data + nalStart, pos - nalStart);
					++count;
				}

				pos     += scLen;
				nalStart = pos;

				continue;
			}

			++pos;
		}

		if (UINT32_MAX != nalStart
		&&  nalStart < _size)
		{
			_visit(_data + nalStart, _size - nalStart);
			++count;
		}

		return count;
	}

	static uint32_t annexBToLengthPrefixed(uint8_t* _out, const uint8_t* _data, uint32_t _size)
	{
		uint32_t outPos = 0;

		visitAnnexBNalUnits(_data, _size, [&](const uint8_t* _nal, uint32_t _nalSize)
		{
			const uint32_t lengthBE = bx::endianSwap(_nalSize);
			bx::memCopy(_out + outPos, &lengthBE, kNalLengthSize);
			outPos += kNalLengthSize;
			bx::memCopy(_out + outPos, _nal, _nalSize);
			outPos += _nalSize;
		});

		return outPos;
	}

	static bool peekHevcAuIsIrap(const uint8_t* _data, uint32_t _size)
	{
		bool irap = false;

		visitAnnexBNalUnits(_data, _size, [&](const uint8_t* _nal, uint32_t _nalSize)
		{
			if (hevc::kNalHeaderSize <= _nalSize)
			{
				irap |= hevc::isIrap(hevc::getNalUnitType(_nal) );
			}
		});

		return irap;
	}

	static uint8_t getMatrixCoefficients(CMVideoFormatDescriptionRef _formatDesc)
	{
		CFTypeRef matrix = CMFormatDescriptionGetExtension(_formatDesc, kCMFormatDescriptionExtension_YCbCrMatrix);

		if (NULL != matrix)
		{
			if (CFEqual(matrix, kCMFormatDescriptionYCbCrMatrix_ITU_R_601_4) )
			{
				return h273::MC_BT601;
			}

			if (CFEqual(matrix, kCMFormatDescriptionYCbCrMatrix_SMPTE_240M_1995) )
			{
				return h273::MC_SMPTE240M;
			}

			if (CFEqual(matrix, kCMFormatDescriptionYCbCrMatrix_ITU_R_2020) )
			{
				return h273::MC_BT2020_NCL;
			}
		}

		return h273::MC_BT709;
	}

	struct Av1BitReader
	{
		Av1BitReader(const uint8_t* _data, uint32_t _size)
			: data(_data)
			, size(_size)
			, pos(0)
		{
		}

		uint32_t read(uint32_t _bits)
		{
			uint32_t value = 0;

			for (uint32_t ii = 0; ii < _bits; ++ii)
			{
				const uint32_t byte = pos >> 3;
				const uint32_t bit  = byte < size
					? (data[byte] >> (7 - (pos & 7) ) ) & 1
					: 0
					;

				value = (value << 1) | bit;
				++pos;
			}

			return value;
		}

		uint32_t uvlc()
		{
			uint32_t leadingZeros = 0;

			while (leadingZeros < av1::kMaxLeadingZeros
			&&     0 == read(1) )
			{
				++leadingZeros;
			}

			if (av1::kMaxLeadingZeros <= leadingZeros)
			{
				return UINT32_MAX;
			}

			return read(leadingZeros) + (1u << leadingZeros) - 1;
		}

		bool overrun() const
		{
			return pos > size*8;
		}

		const uint8_t* data;
		uint32_t       size;
		uint32_t       pos;
	};

	struct Av1SequenceHeader
	{
		uint32_t maxWidth;
		uint32_t maxHeight;
		uint8_t  profile;
		uint8_t  levelIdx;
		uint8_t  tier;
		uint8_t  highBitdepth;
		uint8_t  twelveBit;
		uint8_t  monochrome;
		uint8_t  subsamplingX;
		uint8_t  subsamplingY;
		uint8_t  chromaSamplePosition;
		uint8_t  reducedStillPictureHeader;
		uint8_t  matrixCoefficients;
		uint8_t  colorRange;
	};

	static bool parseAv1SequenceHeader(const uint8_t* _data, uint32_t _size, Av1SequenceHeader& _out)
	{
		Av1BitReader br(_data, _size);

		_out = {};
		_out.profile = uint8_t(br.read(3) );
		br.read(1);
		_out.reducedStillPictureHeader = uint8_t(br.read(1) );

		bool     decoderModelInfoPresent = false;
		uint32_t bufferDelayLength       = 0;

		if (_out.reducedStillPictureHeader)
		{
			_out.levelIdx = uint8_t(br.read(5) );
		}
		else
		{
			if (0 != br.read(1) )
			{
				br.read(32);
				br.read(32);

				if (0 != br.read(1) )
				{
					br.uvlc();
				}

				decoderModelInfoPresent = 0 != br.read(1);

				if (decoderModelInfoPresent)
				{
					bufferDelayLength = br.read(5) + 1;
					br.read(32);
					br.read(5);
					br.read(5);
				}
			}

			const bool     initialDisplayDelayPresent = 0 != br.read(1);
			const uint32_t numOperatingPoints         = br.read(5) + 1;

			for (uint32_t ii = 0; ii < numOperatingPoints; ++ii)
			{
				br.read(12);
				const uint32_t levelIdx = br.read(5);
				const uint32_t tier     = 7 < levelIdx ? br.read(1) : 0;

				if (0 == ii)
				{
					_out.levelIdx = uint8_t(levelIdx);
					_out.tier     = uint8_t(tier);
				}

				if (decoderModelInfoPresent
				&&  0 != br.read(1) )
				{
					br.read(bufferDelayLength);
					br.read(bufferDelayLength);
					br.read(1);
				}

				if (initialDisplayDelayPresent
				&&  0 != br.read(1) )
				{
					br.read(4);
				}
			}
		}

		const uint32_t widthBits  = br.read(4) + 1;
		const uint32_t heightBits = br.read(4) + 1;
		_out.maxWidth  = br.read(widthBits)  + 1;
		_out.maxHeight = br.read(heightBits) + 1;

		if (!_out.reducedStillPictureHeader
		&&  0 != br.read(1) )
		{
			br.read(4);
			br.read(3);
		}

		br.read(3);

		if (!_out.reducedStillPictureHeader)
		{
			br.read(4);
			const bool enableOrderHint = 0 != br.read(1);

			if (enableOrderHint)
			{
				br.read(2);
			}

			const uint32_t forceScreenContentTools = 0 != br.read(1) ? 2 : br.read(1);

			if (0 < forceScreenContentTools
			&&  0 == br.read(1) )
			{
				br.read(1);
			}

			if (enableOrderHint)
			{
				br.read(3);
			}
		}

		br.read(3);

		_out.highBitdepth = uint8_t(br.read(1) );
		_out.twelveBit    = av1::PROFILE_PROFESSIONAL == _out.profile && _out.highBitdepth ? uint8_t(br.read(1) ) : 0;
		_out.monochrome   = av1::PROFILE_HIGH == _out.profile ? 0 : uint8_t(br.read(1) );

		uint32_t colorPrimaries = h273::CP_UNSPECIFIED;
		uint32_t transfer       = h273::TC_UNSPECIFIED;
		uint32_t matrix         = h273::MC_UNSPECIFIED;

		if (0 != br.read(1) )
		{
			colorPrimaries = br.read(8);
			transfer       = br.read(8);
			matrix         = br.read(8);
		}

		_out.matrixCoefficients = uint8_t(matrix);

		if (_out.monochrome)
		{
			_out.colorRange   = uint8_t(br.read(1) );
			_out.subsamplingX = 1;
			_out.subsamplingY = 1;
		}
		else if (h273::CP_BT709   == colorPrimaries
		     &&  h273::TC_SRGB     == transfer
		     &&  h273::MC_IDENTITY == matrix)
		{
			_out.colorRange = 1;
		}
		else
		{
			_out.colorRange = uint8_t(br.read(1) );

			if (av1::PROFILE_MAIN == _out.profile)
			{
				_out.subsamplingX = 1;
				_out.subsamplingY = 1;
			}
			else if (av1::PROFILE_PROFESSIONAL == _out.profile)
			{
				if (_out.twelveBit)
				{
					_out.subsamplingX = uint8_t(br.read(1) );
					_out.subsamplingY = _out.subsamplingX ? uint8_t(br.read(1) ) : 0;
				}
				else
				{
					_out.subsamplingX = 1;
				}
			}

			if (_out.subsamplingX
			&&  _out.subsamplingY)
			{
				_out.chromaSamplePosition = uint8_t(br.read(2) );
			}
		}

		return !br.overrun()
			&& 0 != _out.maxWidth
			&& 0 != _out.maxHeight
			;
	}

	template <typename Fn>
	static uint32_t visitObus(const uint8_t* _data, uint32_t _size, Fn _visit)
	{
		uint32_t count = 0;
		uint32_t pos   = 0;

		while (pos < _size)
		{
			const uint8_t header       = _data[pos];
			const uint8_t type         = (header >> av1::kObuTypeShift) & av1::kObuTypeMask;
			const bool    hasExtension = 0 != (header & av1::kObuExtensionFlag);
			const bool    hasSize      = 0 != (header & av1::kObuHasSizeField);

			uint32_t payload = pos + 1 + (hasExtension ? 1 : 0);

			if (_size < payload)
			{
				break;
			}

			uint32_t size = _size - payload;

			if (hasSize)
			{
				size = 0;

				for (uint32_t shift = 0; payload < _size && shift < 32; shift += 7)
				{
					const uint8_t byte = _data[payload++];
					size |= uint32_t(byte & av1::kLeb128ValueMask) << shift;

					if (0 == (byte & av1::kLeb128ContinuationBit) )
					{
						break;
					}
				}

				size = bx::min(size, _size - payload);
			}

			_visit(type, hasExtension ? _data[pos+1] : uint8_t(0), hasExtension, &_data[payload], size);

			count++;
			pos = payload + size;
		}

		return count;
	}

	static uint32_t writeObuWithSize(uint8_t* _out, uint8_t _type, uint8_t _extension, bool _hasExtension, const uint8_t* _payload, uint32_t _payloadSize)
	{
		uint32_t outPos = 0;

		_out[outPos++] = uint8_t( (_type << av1::kObuTypeShift) | (_hasExtension ? av1::kObuExtensionFlag : 0) | av1::kObuHasSizeField);

		if (_hasExtension)
		{
			_out[outPos++] = _extension;
		}

		uint32_t size = _payloadSize;

		do
		{
			uint8_t byte = uint8_t(size & av1::kLeb128ValueMask);
			size >>= 7;
			_out[outPos++] = uint8_t(byte | (0 != size ? av1::kLeb128ContinuationBit : 0) );
		}
		while (0 != size);

		bx::memCopy(&_out[outPos], _payload, _payloadSize);

		return outPos + _payloadSize;
	}

	static uint32_t av1TemporalUnitToSample(uint8_t* _out, const uint8_t* _data, uint32_t _size)
	{
		uint32_t outPos = 0;

		visitObus(_data, _size, [&](uint8_t _type, uint8_t _extension, bool _hasExtension, const uint8_t* _payload, uint32_t _payloadSize)
		{
			if (av1::OBU_TEMPORAL_DELIMITER != _type)
			{
				outPos += writeObuWithSize(&_out[outPos], _type, _extension, _hasExtension, _payload, _payloadSize);
			}
		});

		return outPos;
	}

	static bool peekAv1AuIsKeyFrame(const uint8_t* _data, uint32_t _size, bool _reducedStillPictureHeader)
	{
		bool seen = false;
		bool key  = false;

		visitObus(_data, _size, [&](uint8_t _type, uint8_t, bool, const uint8_t* _payload, uint32_t _payloadSize)
		{
			if (seen
			|| (av1::OBU_FRAME_HEADER != _type && av1::OBU_FRAME != _type)
			||  0 == _payloadSize)
			{
				return;
			}

			seen = true;

			if (_reducedStillPictureHeader)
			{
				key = true;
				return;
			}

			Av1BitReader br(_payload, _payloadSize);

			if (0 != br.read(1) )
			{
				return;
			}

			const uint32_t frameType = br.read(2);
			const bool     showFrame = 0 != br.read(1);

			key = av1::KEY_FRAME == frameType && showFrame;
		});

		return key;
	}

	struct VideoDecoderMtl
	{
		struct ReorderedPicture
		{
			CVPixelBufferRef pb;
			int32_t          displayOrder;
			int64_t          ptsUs;
			uint32_t         generation;
		};

		VideoDecoderMtl()
			: m_renderer(NULL)
			, m_device(NULL)
			, m_formatDesc(NULL)
			, m_session(NULL)
			, m_textureCache(NULL)
			, m_codec(VideoCodec::Count)
			, m_dstWidth(0)
			, m_dstHeight(0)
			, m_initFlags(0)
			, m_cachedAuBytes(0)
			, m_dtsCounter(0)
			, m_decodeCounter(0)
			, m_displayedSlot(-1)
			, m_prevDisplayedSlot(-1)
			, m_sessionFailed(false)
		{
			bx::memSet(&m_av1, 0, sizeof(m_av1) );
			bx::memSet(m_yuvToRgb, 0, sizeof(m_yuvToRgb) );

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				m_reorderPool[ii] =
				{
					.pb           = NULL,
					.displayOrder = -1,
					.ptsUs        = 0,
					.generation   = 0,
				};
			}
		}

		bool create(const VideoDecoderInit& _init, RendererContextMtl* _renderer, MTL::Device* _device, uint16_t _width, uint16_t _height)
		{
			m_renderer      = _renderer;
			m_device        = _device;
			m_codec         = _init.codec;
			m_dstWidth      = _width;
			m_dstHeight     = _height;
			m_initFlags     = _init.flags;
			m_cachedAuBytes = (0 != _init.cachedAuBytes) ? _init.cachedAuBytes : (4u << 20);
			m_auQueue.configure(m_cachedAuBytes, 0 != (m_initFlags & BGFX_VIDEO_DECODER_INIT_RETAIN) );

			bool created = false;

			switch (m_codec)
			{
			case VideoCodec::H264:
			case VideoCodec::H265:
				created = createFormatDescriptionFromParameterSets(_init);
				break;

			case VideoCodec::AV1:
				created = createAv1FormatDescription(_init);
				break;

			default:
				break;
			}

			if (!created)
			{
				return false;
			}

			if (VideoCodec::AV1 == m_codec)
			{
				getYuvToRgb(m_yuvToRgb, m_av1.matrixCoefficients, false);
			}
			else
			{
				getYuvToRgb(m_yuvToRgb, getMatrixCoefficients(m_formatDesc), false);
			}

			if (!createSession() )
			{
				CFRelease(m_formatDesc);
				m_formatDesc = NULL;

				return false;
			}

			CVReturn cvr = CVMetalTextureCacheCreate(
				  kCFAllocatorDefault
				, NULL
				, (id<MTLDevice>)_device
				, NULL
				, &m_textureCache
				);

			BX_ASSERT(kCVReturnSuccess == cvr, "CVMetalTextureCacheCreate failed: %d", (int)cvr);
			BX_UNUSED(cvr);

			return true;
		}

		bool createFormatDescriptionFromParameterSets(const VideoDecoderInit& _init)
		{
			const uint8_t* psPtrs[kMaxParameterSets];
			size_t         psSize[kMaxParameterSets];
			uint32_t       psCount = 0;
			const bool     isHevc  = VideoCodec::H265 == _init.codec;

			visitAnnexBNalUnits(_init.parameterSets, _init.parameterSetsSize, [&](const uint8_t* _nal, uint32_t _nalSize)
			{
				if (0 == _nalSize
				||  psCount >= BX_COUNTOF(psPtrs) )
				{
					return;
				}

				bool keep = false;

				if (isHevc)
				{
					if (_nalSize < hevc::kNalHeaderSize)
					{
						return;
					}

					const hevc::NalUnitType nalType = hevc::getNalUnitType(_nal);
					keep = hevc::VPS_NUT == nalType
						|| hevc::SPS_NUT == nalType
						|| hevc::PPS_NUT == nalType
						;
				}
				else
				{
					const uint8_t nalType = _nal[0] & kH264NalUnitTypeMask;
					keep = h264::NAL_UNIT_TYPE_SPS == nalType
						|| h264::NAL_UNIT_TYPE_PPS == nalType
						;
				}

				if (keep)
				{
					psPtrs[psCount] = _nal;
					psSize[psCount] = _nalSize;
					++psCount;
				}
			});

			if (0 == psCount)
			{
				BX_TRACE("VideoDecoderMtl: no parameter set NAL units found (codec=%d).", int(_init.codec) );
				return false;
			}

			OSStatus status = noErr;

			if (isHevc)
			{
				if (__builtin_available(macOS 10.13, iOS 11.0, tvOS 11.0, *) )
				{
					status = CMVideoFormatDescriptionCreateFromHEVCParameterSets(
						  kCFAllocatorDefault
						, psCount
						, psPtrs
						, psSize
						, kNalLengthSize
						, NULL
						, &m_formatDesc
						);
				}
				else
				{
					BX_TRACE("VideoDecoderMtl: HEVC requires macOS 10.13+.");
					return false;
				}
			}
			else
			{
				status = CMVideoFormatDescriptionCreateFromH264ParameterSets(
					  kCFAllocatorDefault
					, psCount
					, psPtrs
					, psSize
					, kNalLengthSize
					, &m_formatDesc
					);
			}

			if (noErr != status
			||  NULL == m_formatDesc)
			{
				BX_TRACE("VideoDecoderMtl: CMVideoFormatDescriptionCreateFrom%sParameterSets failed: %d"
					, isHevc ? "HEVC" : "H264"
					, (int)status
					);

				return false;
			}

			return true;
		}

		bool createAv1FormatDescription(const VideoDecoderInit& _init)
		{
#if BGFX_VIDEO_METAL_AV1
			const uint8_t* seqPayload     = NULL;
			uint32_t       seqPayloadSize = 0;
			uint8_t        seqExtension   = 0;
			bool           seqHasExtension = false;

			visitObus(_init.parameterSets, _init.parameterSetsSize, [&](uint8_t _type, uint8_t _extension, bool _hasExtension, const uint8_t* _payload, uint32_t _payloadSize)
			{
				if (av1::OBU_SEQUENCE_HEADER == _type
				&&  NULL == seqPayload)
				{
					seqPayload      = _payload;
					seqPayloadSize  = _payloadSize;
					seqExtension    = _extension;
					seqHasExtension = _hasExtension;
				}
			});

			if (NULL == seqPayload
			||  !parseAv1SequenceHeader(seqPayload, seqPayloadSize, m_av1) )
			{
				BX_TRACE("VideoDecoderMtl: no AV1 sequence header OBU found.");
				return false;
			}

			const uint8_t av1c[4] =
			{
				av1::kAv1CMarkerVersion,
				uint8_t( (m_av1.profile << 5) | m_av1.levelIdx),
				uint8_t( (m_av1.tier         << 7)
				       | (m_av1.highBitdepth << 6)
				       | (m_av1.twelveBit    << 5)
				       | (m_av1.monochrome   << 4)
				       | (m_av1.subsamplingX << 3)
				       | (m_av1.subsamplingY << 2)
				       |  m_av1.chromaSamplePosition
				       ),
				0,
			};

			uint8_t* seqObu = (uint8_t*)bx::alloc(g_allocator, seqPayloadSize + av1::kObuHeaderMaxSize);
			const uint32_t seqObuSize = writeObuWithSize(seqObu, av1::OBU_SEQUENCE_HEADER, seqExtension, seqHasExtension, seqPayload, seqPayloadSize);

			CFMutableDataRef av1cData = CFDataCreateMutable(kCFAllocatorDefault, 0);
			CFDataAppendBytes(av1cData, av1c, sizeof(av1c) );
			CFDataAppendBytes(av1cData, seqObu, seqObuSize);
			bx::free(g_allocator, seqObu);

			const void* atomKeys[]   = { CFSTR("av1C") };
			const void* atomValues[] = { av1cData };
			CFDictionaryRef atoms = CFDictionaryCreate(
				  kCFAllocatorDefault
				, atomKeys
				, atomValues
				, 1
				, &kCFTypeDictionaryKeyCallBacks
				, &kCFTypeDictionaryValueCallBacks
				);
			CFRelease(av1cData);

			const void* extKeys[]   = { kCMFormatDescriptionExtension_SampleDescriptionExtensionAtoms };
			const void* extValues[] = { atoms };
			CFDictionaryRef extensions = CFDictionaryCreate(
				  kCFAllocatorDefault
				, extKeys
				, extValues
				, 1
				, &kCFTypeDictionaryKeyCallBacks
				, &kCFTypeDictionaryValueCallBacks
				);
			CFRelease(atoms);

			const OSStatus status = CMVideoFormatDescriptionCreate(
				  kCFAllocatorDefault
				, kCMVideoCodecType_AV1
				, int32_t(m_av1.maxWidth)
				, int32_t(m_av1.maxHeight)
				, extensions
				, &m_formatDesc
				);
			CFRelease(extensions);

			if (noErr != status
			||  NULL == m_formatDesc)
			{
				BX_TRACE("VideoDecoderMtl: CMVideoFormatDescriptionCreate(AV1) failed: %d", (int)status);
				return false;
			}

			return true;
#else
			BX_UNUSED(_init);
			return false;
#endif // BGFX_VIDEO_METAL_AV1
		}

		bool createSession()
		{
			const int32_t pixelFormat = kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange;

			CFNumberRef     pixelFormatNum = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &pixelFormat);
			CFDictionaryRef ioSurfaceProps = CFDictionaryCreate(kCFAllocatorDefault, NULL, NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

			const void* keys[]   = { kCVPixelBufferPixelFormatTypeKey, kCVPixelBufferMetalCompatibilityKey, kCVPixelBufferIOSurfacePropertiesKey };
			const void* values[] = { pixelFormatNum,                  kCFBooleanTrue,                      ioSurfaceProps                      };
			CFDictionaryRef destAttrs = CFDictionaryCreate(
				  kCFAllocatorDefault
				, keys
				, values
				, BX_COUNTOF(keys)
				, &kCFTypeDictionaryKeyCallBacks
				, &kCFTypeDictionaryValueCallBacks
				);
			CFRelease(pixelFormatNum);
			CFRelease(ioSurfaceProps);

			VTDecompressionOutputCallbackRecord callback;
			callback.decompressionOutputCallback = &VideoDecoderMtl::decodeOutputCallback;
			callback.decompressionOutputRefCon   = this;

			OSStatus status = VTDecompressionSessionCreate(
				  kCFAllocatorDefault
				, m_formatDesc
				, NULL
				, destAttrs
				, &callback
				, &m_session
				);

			CFRelease(destAttrs);

			if (noErr != status
			||  NULL == m_session)
			{
				BX_TRACE("VideoDecoderMtl: VTDecompressionSessionCreate failed: %d", (int)status);
				m_session = NULL;
				return false;
			}

			VTSessionSetProperty(m_session, kVTDecompressionPropertyKey_RealTime, kCFBooleanFalse);

			return true;
		}

		void destroySession()
		{
			if (NULL != m_session)
			{
				VTDecompressionSessionWaitForAsynchronousFrames(m_session);
				VTDecompressionSessionInvalidate(m_session);
				CFRelease(m_session);
				m_session = NULL;
			}
		}

		void releasePicture(uint32_t _poolIdx)
		{
			ReorderedPicture& pic = m_reorderPool[_poolIdx];

			bx::MutexScope lock(m_poolMutex);

			if (NULL != pic.pb)
			{
				CFRelease(pic.pb);
			}

			pic.pb           = NULL;
			pic.displayOrder = -1;
			pic.ptsUs        = 0;
			++pic.generation;
		}

		CVPixelBufferRef acquirePicture(uint32_t _poolIdx)
		{
			bx::MutexScope lock(m_poolMutex);

			CVPixelBufferRef pb = m_reorderPool[_poolIdx].pb;

			if (NULL != pb)
			{
				CFRetain(pb);
			}

			return pb;
		}

		bool takeSessionFailed()
		{
			bx::MutexScope lock(m_poolMutex);

			const bool failed = m_sessionFailed;
			m_sessionFailed = false;

			return failed;
		}

		void waitForPendingFrames()
		{
			if (NULL != m_session)
			{
				VTDecompressionSessionWaitForAsynchronousFrames(m_session);
			}
		}

		void releasePictures()
		{
			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				releasePicture(ii);
			}
		}

		void resetForSet()
		{
			waitForPendingFrames();

			if (m_auQueue.isRetaining() )
			{
				m_auQueue.rewindTo(m_auQueue.size() );
			}
			else
			{
				m_auQueue.clear();
			}

			releasePictures();

			m_displayedSlot     = -1;
			m_prevDisplayedSlot = -1;
		}

		void destroy()
		{
			destroySession();
			releasePictures();
			m_auQueue.clear();

			if (NULL != m_textureCache)
			{
				CVMetalTextureCacheFlush(m_textureCache, 0);
				CFRelease(m_textureCache);
				m_textureCache = NULL;
			}

			if (NULL != m_formatDesc)
			{
				CFRelease(m_formatDesc);
				m_formatDesc = NULL;
			}
		}

		bool peekAuIsKeyFrame(const uint8_t* _data, uint32_t _size) const
		{
			switch (m_codec)
			{
			case VideoCodec::H264: return peekAuIsIdr(_data, _size);
			case VideoCodec::H265: return peekHevcAuIsIrap(_data, _size);
			case VideoCodec::AV1:  return peekAv1AuIsKeyFrame(_data, _size, 0 != m_av1.reducedStillPictureHeader);
			default: break;
			}

			return false;
		}

		bool decode(const VideoDecoderFrame& _frame, MTL::Texture* _dst)
		{
			if (NULL == m_formatDesc)
			{
				return false;
			}

			if (0 != (_frame.flags & BGFX_VIDEO_DECODE_FRAME_SET) )
			{
				resetForSet();
			}

			if (NULL != _frame.bitstream
			&&  0 != _frame.numAus)
			{
				const uint8_t* bs = _frame.bitstream;

				for (uint32_t ii = 0; ii < _frame.numAus; ++ii)
				{
					const uint32_t auSize = _frame.aus[ii].size;
					m_auQueue.enqueue(bs, auSize, _frame.aus[ii].ptsUs, peekAuIsKeyFrame(bs, auSize) );
					bs += auSize;
				}
			}

			while (!m_auQueue.empty()
			&&     hasReorderSpace(m_reorderPool, kVideoMaxReorderInFlight) )
			{
				const PendingAU& au = m_auQueue.front();
				decodeOneAU(au.data.data(), uint32_t(au.data.size() ), au.ptsUs);
				m_auQueue.pop();
			}

			m_auQueue.compact();

			if (0 == _frame.numAus
			&&  0 == (_frame.flags & BGFX_VIDEO_DECODE_FRAME_NO_BLIT) )
			{
				int64_t adjustedClock = _frame.presentationTimeUs;

				if (0 != (_frame.flags & BGFX_VIDEO_DECODE_FRAME_LOOP)
				&&  m_auQueue.isRetaining()
				&&  m_auQueue.minPts() < m_auQueue.maxPts() )
				{
					adjustedClock = applyLoopWrap(adjustedClock, m_auQueue.minPts(), m_auQueue.maxPts(), m_auQueue.size() );

					const bool poolCovers = reorderPoolCovers(m_auQueue, m_reorderPool, kVideoMaxReorderInFlight, adjustedClock);
					const bool forwardCanCatchUp = true
						&& !m_auQueue.empty()
						&& m_auQueue.front().ptsUs <= adjustedClock + 500000
						;

					if (!poolCovers
					&&  !forwardCanCatchUp)
					{
						faultInFromCache(
							  m_auQueue
							, adjustedClock
							, [this]() { resetForSet(); }
							, [this](const uint8_t* _bs, uint32_t _bsSize, int64_t _pts)
							  {
								  decodeOneAU(_bs, _bsSize, _pts);
							  }
							, m_reorderPool
							, kVideoMaxReorderInFlight
							);
					}
				}

				bgfx::pickDisplaySlotForTime(
					  adjustedClock
					, m_reorderPool
					, kVideoMaxReorderInFlight
					, m_displayedSlot
					, m_prevDisplayedSlot
					, m_auQueue.empty()
					, [this, _dst](uint32_t _slot)
					{
						dispatchYuvToRgb(_slot, _dst);
					});
			}

			return true;
		}

		bool decodeOneAU(const uint8_t* _bitstream, uint32_t _bitstreamSize, int64_t _ptsUs)
		{
			if (takeSessionFailed() )
			{
				destroySession();
			}

			if (NULL == m_session
			&&  !createSession() )
			{
				return false;
			}

			uint8_t* sampleBytes = NULL;
			uint32_t sampleSize  = 0;

			if (VideoCodec::AV1 == m_codec)
			{
				const uint32_t numObus = visitObus(_bitstream, _bitstreamSize, [](uint8_t, uint8_t, bool, const uint8_t*, uint32_t) {});
				sampleBytes = (uint8_t*)bx::alloc(g_allocator, _bitstreamSize + av1::kObuHeaderMaxSize*numObus);
				sampleSize  = av1TemporalUnitToSample(sampleBytes, _bitstream, _bitstreamSize);
			}
			else
			{
				const uint32_t numNals = visitAnnexBNalUnits(_bitstream, _bitstreamSize, [](const uint8_t*, uint32_t) {});
				sampleBytes = (uint8_t*)bx::alloc(g_allocator, _bitstreamSize + kNalLengthSize*numNals);
				sampleSize  = annexBToLengthPrefixed(sampleBytes, _bitstream, _bitstreamSize);
			}

			if (0 == sampleSize)
			{
				bx::free(g_allocator, sampleBytes);
				return false;
			}

			CMBlockBufferCustomBlockSource customSource = {};
			customSource.version   = kCMBlockBufferCustomBlockSourceVersion;
			customSource.FreeBlock = freeBlockBxAlloc;

			CMBlockBufferRef blockBuffer = NULL;
			OSStatus status = CMBlockBufferCreateWithMemoryBlock(
				  kCFAllocatorDefault
				, sampleBytes
				, sampleSize
				, kCFAllocatorNull
				, &customSource
				, 0
				, sampleSize
				, 0
				, &blockBuffer
				);

			if (noErr != status)
			{
				bx::free(g_allocator, sampleBytes);
				return false;
			}

			const size_t  sampleSizes[] = { sampleSize };
			const int64_t dtsUs         = int64_t(++m_dtsCounter * 1000ull);

			const CMSampleTimingInfo timing =
			{
				.duration              = kCMTimeInvalid,
				.presentationTimeStamp = CMTimeMake(_ptsUs, 1000000),
				.decodeTimeStamp       = CMTimeMake(dtsUs,  1000000),
			};

			CMSampleBufferRef sampleBuffer = NULL;
			status = CMSampleBufferCreate(
				  kCFAllocatorDefault
				, blockBuffer
				, true
				, NULL
				, NULL
				, m_formatDesc
				, 1
				, 1, &timing
				, 1, sampleSizes
				, &sampleBuffer
				);

			CFRelease(blockBuffer);

			if (noErr != status)
			{
				return false;
			}

			const uint32_t poolIdx = pickReorderSlotOrEvictOldest(m_reorderPool, kVideoMaxReorderInFlight);
			releasePicture(poolIdx);

			ReorderedPicture& pic = m_reorderPool[poolIdx];
			pic.displayOrder = int32_t(m_decodeCounter++ & 0x7fffffff);
			pic.ptsUs        = _ptsUs;

			const uintptr_t refCon = (uintptr_t(pic.generation) << 32) | uintptr_t(poolIdx);

			VTDecodeInfoFlags infoFlags = 0;
			status = VTDecompressionSessionDecodeFrame(
				  m_session
				, sampleBuffer
				, kVTDecodeFrame_EnableAsynchronousDecompression
				, (void*)refCon
				, &infoFlags
				);

			CFRelease(sampleBuffer);

			if (noErr != status)
			{
				BX_TRACE("VideoDecoderMtl: VTDecompressionSessionDecodeFrame failed: %d", (int)status);
				releasePicture(poolIdx);
				destroySession();
				return false;
			}

			return true;
		}

		void dispatchYuvToRgb(uint32_t _poolIdx, MTL::Texture* _dst)
		{
			BX_ASSERT(NULL != g_videoDecode, "Video decode program not initialized.");
			BX_ASSERT(_poolIdx < kVideoMaxReorderInFlight, "Reorder pool index out of range.");

			if (NULL == _dst)
			{
				return;
			}

			CVPixelBufferRef pic = acquirePicture(_poolIdx);

			if (NULL == pic)
			{
				waitForPendingFrames();
				pic = acquirePicture(_poolIdx);
			}

			if (NULL == pic)
			{
				return;
			}

			const size_t yWidth  = CVPixelBufferGetWidthOfPlane (pic, 0);
			const size_t yHeight = CVPixelBufferGetHeightOfPlane(pic, 0);
			const size_t cWidth  = CVPixelBufferGetWidthOfPlane (pic, 1);
			const size_t cHeight = CVPixelBufferGetHeightOfPlane(pic, 1);

			CVMetalTextureRef yMtlTex = NULL;
			CVMetalTextureRef cMtlTex = NULL;

			CVReturn cvr = CVMetalTextureCacheCreateTextureFromImage(
				  kCFAllocatorDefault
				, m_textureCache
				, pic
				, NULL
				, MTLPixelFormatR8Unorm
				, yWidth, yHeight, 0
				, &yMtlTex
				);

			if (kCVReturnSuccess != cvr
			||  NULL == yMtlTex)
			{
				BX_TRACE("VideoDecoderMtl: Y plane texture create failed: %d", (int)cvr);
				CFRelease(pic);
				return;
			}

			cvr = CVMetalTextureCacheCreateTextureFromImage(
				  kCFAllocatorDefault
				, m_textureCache
				, pic
				, NULL
				, MTLPixelFormatRG8Unorm
				, cWidth, cHeight, 1
				, &cMtlTex
				);

			if (kCVReturnSuccess != cvr
			||  NULL == cMtlTex)
			{
				BX_TRACE("VideoDecoderMtl: CbCr plane texture create failed: %d", (int)cvr);
				CFRelease(yMtlTex);
				CFRelease(pic);
				return;
			}

			const TextureFormat::Enum dstFormat = MTL::PixelFormatRGBA16Float == _dst->pixelFormat()
				? TextureFormat::RGBA16F
				: TextureFormat::RGBA8
				;

			PipelineStateMtl* pso = videoGetComputePipelineState(m_renderer, g_videoDecode->getProgram(dstFormat) );

			if (NULL == pso)
			{
				CFRelease(yMtlTex);
				CFRelease(cMtlTex);
				CFRelease(pic);
				return;
			}

			MTL::Texture* yTex = (MTL::Texture*)CVMetalTextureGetTexture(yMtlTex);
			MTL::Texture* cTex = (MTL::Texture*)CVMetalTextureGetTexture(cMtlTex);

			videoEndEncoding(m_renderer);

			MTL::CommandBuffer* cmdBuf = videoEnsureCommandBuffer(m_renderer);

			MTL::ComputeCommandEncoder* cce = cmdBuf->computeCommandEncoder();
			cce->setComputePipelineState(pso->m_cps);

			MTL::SamplerState* linearClamp = videoGetSamplerState(m_renderer, 0
				| BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				| BGFX_SAMPLER_W_CLAMP
				);

			cce->setTexture(_dst, 0);
			cce->setTexture(yTex, 1);
			cce->setSamplerState(linearClamp, 1);
			cce->setTexture(cTex, 2);
			cce->setSamplerState(linearClamp, 2);
			cce->setBytes(m_yuvToRgb, sizeof(m_yuvToRgb), 0);

			const MTL::Size threadsPerGroup = MTL::Size::Make(8, 8, 1);
			const MTL::Size groupCount      = MTL::Size::Make(
				  (m_dstWidth  + 7) / 8
				, (m_dstHeight + 7) / 8
				, 1
				);
			cce->dispatchThreadgroups(groupCount, threadsPerGroup);
			cce->endEncoding();

			MTL::HandlerFunction releaseRefs = [pic, yMtlTex, cMtlTex](MTL::CommandBuffer*)
			{
				CFRelease(yMtlTex);
				CFRelease(cMtlTex);
				CFRelease(pic);
			};

			cmdBuf->addCompletedHandler(releaseRefs);
		}

		static void decodeOutputCallback(
			  void* _refCon
			, void* _sourceFrameRefCon
			, OSStatus _status
			, VTDecodeInfoFlags _infoFlags
			, CVImageBufferRef _imageBuffer
			, CMTime /*_pts*/
			, CMTime /*_duration*/
			)
		{
			VideoDecoderMtl* self       = (VideoDecoderMtl*)_refCon;
			const uintptr_t  refCon     = uintptr_t(_sourceFrameRefCon);
			const uint32_t   poolIdx    = uint32_t(refCon & UINT32_MAX);
			const uint32_t   generation = uint32_t(refCon >> 32);

			bx::MutexScope lock(self->m_poolMutex);

			if (noErr != _status)
			{
				self->m_sessionFailed = true;
				return;
			}

			if (NULL == _imageBuffer
			||  0 != (_infoFlags & kVTDecodeInfo_FrameDropped)
			||  kVideoMaxReorderInFlight <= poolIdx)
			{
				return;
			}

			ReorderedPicture& pic = self->m_reorderPool[poolIdx];

			if (generation != pic.generation)
			{
				return;
			}

			if (NULL != pic.pb)
			{
				CFRelease(pic.pb);
			}

			pic.pb = (CVPixelBufferRef)CFRetain(_imageBuffer);
		}

		RendererContextMtl* m_renderer;
		MTL::Device*        m_device;

		CMVideoFormatDescriptionRef m_formatDesc;
		VTDecompressionSessionRef   m_session;
		CVMetalTextureCacheRef      m_textureCache;

		bx::Mutex         m_poolMutex;
		AuQueue           m_auQueue;
		ReorderedPicture  m_reorderPool[kVideoMaxReorderInFlight];
		Av1SequenceHeader m_av1;
		VideoCodec::Enum  m_codec;
		uint16_t          m_dstWidth;
		uint16_t          m_dstHeight;
		uint32_t          m_initFlags;
		uint32_t          m_cachedAuBytes;
		uint64_t          m_dtsCounter;
		uint32_t          m_decodeCounter;
		int32_t           m_displayedSlot;
		int32_t           m_prevDisplayedSlot;
		bool              m_sessionFailed;
		float             m_yuvToRgb[12];
	};

	VideoDecoderMtl* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextMtl* _renderer, MTL::Device* _device, uint16_t _width, uint16_t _height)
	{
		VideoDecoderMtl* decoder = BX_NEW(g_allocator, VideoDecoderMtl);

		if (!decoder->create(_init, _renderer, _device, _width, _height) )
		{
			decoder->destroy();
			bx::deleteObject(g_allocator, decoder);

			return NULL;
		}

		return decoder;
	}

	void videoDecoderDestroy(VideoDecoderMtl* _decoder)
	{
		if (NULL != _decoder)
		{
			_decoder->destroy();
			bx::deleteObject(g_allocator, _decoder);
		}
	}

	bool videoDecoderDecode(VideoDecoderMtl* _decoder, const VideoDecoderFrame& _frame, MTL::Texture* _dst)
	{
		return _decoder->decode(_frame, _dst);
	}

	struct CodecProbe
	{
		VideoCodec::Enum codec;
		CMVideoCodecType cmType;
		uint32_t         bitDepths;
		uint32_t         chroma;
	};

	static const CodecProbe s_probes[] =
	{
		{ VideoCodec::H264, kCMVideoCodecType_H264, BGFX_CAPS_VIDEO_CODEC_BIT_8,                                BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
		{ VideoCodec::H265, kCMVideoCodecType_HEVC, BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_BIT_10, BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
#if BGFX_VIDEO_METAL_AV1
		{ VideoCodec::AV1,  kCMVideoCodecType_AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_BIT_10, BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
#endif // BGFX_VIDEO_METAL_AV1
	};

	void initVideoDecoder()
	{
		bool anySupported = false;

		for (uint32_t ii = 0; ii < BX_COUNTOF(s_probes); ++ii)
		{
			const CodecProbe& probe = s_probes[ii];
			bool supported = false;

			if (__builtin_available(macOS 10.13, iOS 11.0, tvOS 11.0, *) )
			{
				supported = VTIsHardwareDecodeSupported(probe.cmType);
			}

			if (supported)
			{
				g_caps.codecs[probe.codec] = probe.bitDepths | probe.chroma;
				anySupported = true;

				BX_TRACE("[MTL] Video decode supported: codec = %d caps = 0x%08x"
					, probe.codec
					, g_caps.codecs[probe.codec]
					);
			}
		}

		if (anySupported)
		{
			g_caps.supported |= BGFX_CAPS_VIDEO_DECODE;

			const TextureFormat::Enum dstFormats[] =
			{
				TextureFormat::BGRA8,
				TextureFormat::RGBA8,
				TextureFormat::RGB10A2,
				TextureFormat::RGBA16F,
			};

			for (uint32_t ii = 0; ii < BX_COUNTOF(dstFormats); ++ii)
			{
				const TextureFormat::Enum fmt = dstFormats[ii];
				if (0 != (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_2D) )
				{
					g_caps.formats[fmt] |= BGFX_CAPS_FORMAT_TEXTURE_VIDEO_DECODE_DST;
				}
			}
		}
	}

} } // namespace bgfx::mtl

#else

namespace bgfx { namespace mtl
{
	void initVideoDecoder()
	{
	}

	VideoDecoderMtl* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextMtl* _renderer, MTL::Device* _device, uint16_t _width, uint16_t _height)
	{
		BX_UNUSED(_init, _renderer, _device, _width, _height);
		return NULL;
	}

	void videoDecoderDestroy(VideoDecoderMtl* _decoder)
	{
		BX_UNUSED(_decoder);
	}

	bool videoDecoderDecode(VideoDecoderMtl* _decoder, const VideoDecoderFrame& _frame, MTL::Texture* _dst)
	{
		BX_UNUSED(_decoder, _frame, _dst);
		return false;
	}

} } // namespace bgfx::mtl

#	endif // BGFX_CONFIG_VIDEO_METAL

#endif // BGFX_CONFIG_RENDERER_METAL
