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

namespace bgfx { namespace mtl
{
	struct RendererContextMtl;

	void initVideoDecoder();
	PipelineStateMtl* videoGetComputePipelineState(RendererContextMtl* _renderer, ProgramHandle _handle);
	void videoEndEncoding(RendererContextMtl* _renderer);
	MTL::CommandBuffer* videoEnsureCommandBuffer(RendererContextMtl* _renderer);
	MTL::SamplerState* videoGetSamplerState(RendererContextMtl* _renderer, uint64_t _samplerFlags);

	static void freeAvccBlockBxAlloc(void* _refcon, void* _memoryBlock, size_t _sizeInBytes)
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
		uint32_t count = 0;
		uint32_t pos   = 0;
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
					&& 0 == _data[pos]
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

		if (UINT32_MAX != nalStart && nalStart < _size)
		{
			_visit(_data + nalStart, _size - nalStart);
			++count;
		}

		return count;
	}

	static uint32_t annexBToAvcc(uint8_t* _out, const uint8_t* _data, uint32_t _size)
	{
		uint32_t outPos = 0;

		visitAnnexBNalUnits(_data, _size, [&](const uint8_t* _nal, uint32_t _nalSize)
		{
			const uint32_t lengthBE = bx::endianSwap(_nalSize);
			bx::memCopy(_out + outPos, &lengthBE, 4);
			outPos += 4;
			bx::memCopy(_out + outPos, _nal, _nalSize);
			outPos += _nalSize;
		});

		return outPos;
	}

	struct VideoDecoderMtl
	{
		VideoDecoderMtl()
			: m_renderer(NULL)
			, m_device(NULL)
			, m_formatDesc(NULL)
			, m_session(NULL)
			, m_textureCache(NULL)
			, m_queueHead(0)
			, m_queueTail(0)
			, m_dstWidth(0)
			, m_dstHeight(0)
			, m_initFlags(0)
			, m_cachedAuBytes(0)
			, m_dtsCounter(0)
			, m_lastDisplayedPts(INT64_MIN)
		{
			bx::memSet(m_queue, 0, sizeof(m_queue) );
		}

		bool create(const VideoDecoderInit& _init, RendererContextMtl* _renderer, MTL::Device* _device, uint16_t _width, uint16_t _height)
		{
			m_renderer         = _renderer;
			m_device           = _device;
			m_dstWidth         = _width;
			m_dstHeight        = _height;
			m_initFlags        = _init.flags;
			m_cachedAuBytes    = (0 != _init.cachedAuBytes) ? _init.cachedAuBytes : (4u << 20);
			m_queueHead        = 0;
			m_queueTail        = 0;
			m_dtsCounter       = 0;
			m_lastDisplayedPts = INT64_MIN;

			bx::memSet(m_queue, 0, sizeof(m_queue) );

			const uint8_t* psPtrs[16];
			size_t         psSize[16];
			uint32_t       psCount = 0;
			const bool     isHevc  = (VideoCodec::H265 == _init.codec);

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
						if (_nalSize < 2) return;
						const uint8_t nalType = (_nal[0] >> 1) & 0x3F;
						keep = (32 == nalType)
						    || (33 == nalType)
						    || (34 == nalType)
						    ;
					}
					else
					{
						const uint8_t nalType = _nal[0] & 0x1F;
						keep = (7 == nalType)
						    || (8 == nalType)
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
						, 4
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
					, 4
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

		bool createSession()
		{
			const int32_t pixelFormat = kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange;

			CFNumberRef pixelFormatNum = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &pixelFormat);
			const void* keys[]   = { kCVPixelBufferPixelFormatTypeKey, kCVPixelBufferMetalCompatibilityKey, kCVPixelBufferIOSurfacePropertiesKey };
			const void* values[] = { pixelFormatNum,                  kCFBooleanTrue,                      CFDictionaryCreate(kCFAllocatorDefault, NULL, NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks) };
			CFDictionaryRef destAttrs = CFDictionaryCreate(
				  kCFAllocatorDefault
				, keys
				, values
				, 3
				, &kCFTypeDictionaryKeyCallBacks
				, &kCFTypeDictionaryValueCallBacks
				);
			CFRelease(pixelFormatNum);
			CFRelease(values[2]);

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

			if (noErr != status || NULL == m_session)
			{
				BX_TRACE("VideoDecoderMtl: VTDecompressionSessionCreate failed: %d", (int)status);
				return false;
			}

			VTSessionSetProperty(m_session, kVTDecompressionPropertyKey_RealTime, kCFBooleanFalse);

			return true;
		}

		void resetForSet()
		{
			if (NULL != m_session)
			{
				VTDecompressionSessionWaitForAsynchronousFrames(m_session);
				VTDecompressionSessionInvalidate(m_session);
				CFRelease(m_session);
				m_session = NULL;
			}

			if (NULL != m_textureCache)
			{
				CVMetalTextureCacheFlush(m_textureCache, 0);
			}

			{
				bx::MutexScope lock(m_queueMutex);

				while (m_queueHead != m_queueTail)
				{
					CFRelease(m_queue[m_queueHead % kQueueCapacity].pb);
					++m_queueHead;
				}

				m_queueHead = 0;
				m_queueTail = 0;
			}

			m_dtsCounter = 0;
			m_lastDisplayedPts = INT64_MIN;
			createSession();
		}
		void destroy()
		{
			if (NULL != m_session)
			{
				VTDecompressionSessionWaitForAsynchronousFrames(m_session);
				VTDecompressionSessionInvalidate(m_session);
				CFRelease(m_session);
				m_session = NULL;
			}

			if (NULL != m_textureCache)
			{
				CVMetalTextureCacheFlush(m_textureCache, 0);
				CFRelease(m_textureCache);
				m_textureCache = NULL;
			}

			{
				bx::MutexScope lock(m_queueMutex);

				while (m_queueHead != m_queueTail)
				{
					CFRelease(m_queue[m_queueHead % kQueueCapacity].pb);
					++m_queueHead;
				}
			}

			if (NULL != m_formatDesc)
			{
				CFRelease(m_formatDesc);
				m_formatDesc = NULL;
			}
		}

		bool decode(const VideoDecoderFrame& _frame, MTL::Texture* _dst)
		{
			if (NULL == m_session)
			{
				return false;
			}

			if (0 != (_frame.flags & BGFX_VIDEO_DECODE_FRAME_SET) )
			{
				resetForSet();

				if (NULL == m_session)
				{
					return false;
				}
			}

			const uint8_t* auBitstream = _frame.bitstream;

			for (uint32_t auIdx = 0; auIdx < _frame.numAus; ++auIdx)
			{
				const uint32_t auSize = _frame.aus[auIdx].size;
				const int64_t  auPts  = _frame.aus[auIdx].ptsUs;

				const uint32_t nalCount = visitAnnexBNalUnits(auBitstream, auSize, [](const uint8_t*, uint32_t){});
				const uint32_t avccBufSize = auSize + nalCount;
				uint8_t* avccBytes = (uint8_t*)bx::alloc(g_allocator, avccBufSize);
				const uint32_t avccSize = annexBToAvcc(avccBytes, auBitstream, auSize);

				BX_ASSERT(avccSize <= avccBufSize
					, "annexBToAvcc wrote %u bytes into a %u-byte buffer (auSize=%u nalCount=%u)"
					, avccSize, avccBufSize, auSize, nalCount
					);

				auBitstream += auSize;

				CMBlockBufferCustomBlockSource customSource = {};
				customSource.version   = kCMBlockBufferCustomBlockSourceVersion;
				customSource.FreeBlock = freeAvccBlockBxAlloc;

				CMBlockBufferRef blockBuffer = NULL;
				OSStatus status = CMBlockBufferCreateWithMemoryBlock(
					  kCFAllocatorDefault
					, avccBytes
					, avccSize
					, kCFAllocatorNull
					, &customSource
					, 0
					, avccSize
					, 0
					, &blockBuffer
					);

				if (noErr != status)
				{
					bx::free(g_allocator, avccBytes);

					return false;
				}

				const size_t sampleSize = avccSize;
				CMSampleBufferRef sampleBuffer = NULL;

				const int64_t synthesizedDtsUs = int64_t(++m_dtsCounter * 1000ull);

				CMSampleTimingInfo timing;
				timing.duration = kCMTimeInvalid;
				timing.presentationTimeStamp = CMTimeMake(auPts,            1000000);
				timing.decodeTimeStamp       = CMTimeMake(synthesizedDtsUs, 1000000);

				status = CMSampleBufferCreate(
					  kCFAllocatorDefault
					, blockBuffer
					, true
					, NULL
					, NULL
					, m_formatDesc
					, 1
					, 1, &timing
					, 1, &sampleSize
					, &sampleBuffer
					);

				CFRelease(blockBuffer);

				if (noErr != status)
				{
					return false;
				}

				VTDecodeFrameFlags flags = kVTDecodeFrame_EnableAsynchronousDecompression
					| kVTDecodeFrame_EnableTemporalProcessing
					;
				VTDecodeInfoFlags  infoFlags = 0;
				status = VTDecompressionSessionDecodeFrame(m_session, sampleBuffer, flags, NULL, &infoFlags);

				CFRelease(sampleBuffer);

				if (noErr != status)
				{
					BX_TRACE("VideoDecoderMtl: DecodeFrame submit failed: %d", (int)status);

					return false;
				}
			}

			const int64_t presentUs = _frame.presentationTimeUs;

			if (0 == presentUs && 0 != _frame.numAus)
			{
				return true;
			}

			CVPixelBufferRef pic = NULL;
			int64_t picPts = INT64_MIN;
			{
				bx::MutexScope lock(m_queueMutex);

				uint32_t bestIdx = UINT32_MAX;
				int64_t  bestPts = INT64_MIN;

				for (uint32_t ii = m_queueHead; ii != m_queueTail; ++ii)
				{
					const int64_t pts = m_queue[ii % kQueueCapacity].ptsUs;
					if (pts <= presentUs && pts > bestPts)
					{
						bestPts = pts;
						bestIdx = ii;
					}
				}

				if (UINT32_MAX == bestIdx
				&&  m_queueHead != m_queueTail
				&&  INT64_MIN == m_lastDisplayedPts)
				{
					bestIdx = m_queueHead;
					bestPts = m_queue[bestIdx % kQueueCapacity].ptsUs;

					for (uint32_t ii = m_queueHead + 1; ii != m_queueTail; ++ii)
					{
						const int64_t pts = m_queue[ii % kQueueCapacity].ptsUs;

						if (pts < bestPts)
						{
							bestPts = pts;
							bestIdx = ii;
						}
					}
				}

				if (UINT32_MAX != bestIdx)
				{
					pic    = m_queue[bestIdx % kQueueCapacity].pb;
					picPts = bestPts;
					CFRetain(pic);

					uint32_t writeIdx = m_queueHead;

					for (uint32_t ii = m_queueHead; ii != m_queueTail; ++ii)
					{
						QueueEntry& e = m_queue[ii % kQueueCapacity];

						if (e.ptsUs <= picPts)
						{
							CFRelease(e.pb);
						}
						else
						{
							m_queue[writeIdx % kQueueCapacity] = e;
							++writeIdx;
						}
					}

					m_queueTail = writeIdx;
					m_lastDisplayedPts = picPts;
				}
			}

			if (NULL == pic)
			{
				return true;
			}

			BX_UNUSED(picPts);

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
				return false;
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
				return false;
			}

			MTL::Texture* yTex = (MTL::Texture*)CVMetalTextureGetTexture(yMtlTex);
			MTL::Texture* cTex = (MTL::Texture*)CVMetalTextureGetTexture(cMtlTex);

			BX_ASSERT(NULL != g_videoDecode, "g_videoDecode not initialized.");
			PipelineStateMtl* pso = videoGetComputePipelineState(m_renderer, g_videoDecode->m_program);

			if (NULL == pso)
			{
				CFRelease(yMtlTex);
				CFRelease(cMtlTex);
				CFRelease(pic);
				return false;
			}

			videoEndEncoding(m_renderer);

			MTL::CommandBuffer* cmdBuf = videoEnsureCommandBuffer(m_renderer);

			MTL::ComputeCommandEncoder* cce = cmdBuf->computeCommandEncoder();
			cce->setComputePipelineState(pso->m_cps);

			MTL::SamplerState* linearClamp = videoGetSamplerState(m_renderer,
				  BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				| BGFX_SAMPLER_W_CLAMP
				);

			cce->setTexture(_dst, 0);
			cce->setTexture(yTex, 1);
			cce->setSamplerState(linearClamp, 1);
			cce->setTexture(cTex, 2);
			cce->setSamplerState(linearClamp, 2);

			const MTL::Size threadsPerGroup = MTL::Size::Make(8, 8, 1);
			const MTL::Size groupCount      = MTL::Size::Make(
				  (m_dstWidth  + 7) / 8
				, (m_dstHeight + 7) / 8
				, 1
				);
			cce->dispatchThreadgroups(groupCount, threadsPerGroup);
			cce->endEncoding();

			CVPixelBufferRef  retainedPic = pic;
			CVMetalTextureRef retainedY   = yMtlTex;
			CVMetalTextureRef retainedC   = cMtlTex;

			MTL::HandlerFunction releaseRefs = [retainedPic, retainedY, retainedC](MTL::CommandBuffer*)
			{
				CFRelease(retainedY);
				CFRelease(retainedC);
				CFRelease(retainedPic);
			};

			cmdBuf->addCompletedHandler(releaseRefs);

			return true;
		}

		static void decodeOutputCallback(
			  void* _refCon
			, void* /*_sourceFrameRefCon*/
			, OSStatus _status
			, VTDecodeInfoFlags /*_infoFlags*/
			, CVImageBufferRef _imageBuffer
			, CMTime _pts
			, CMTime /*_duration*/
			)
		{
			VideoDecoderMtl* self = (VideoDecoderMtl*)_refCon;

			if (noErr != _status
			||  NULL == _imageBuffer)
			{
				return;
			}

			const int64_t ptsUs = CMTIME_IS_VALID(_pts) && _pts.timescale > 0
				? int64_t(double(_pts.value) * 1000000.0 / double(_pts.timescale) )
				: INT64_MIN;

			bx::MutexScope lock(self->m_queueMutex);

			if (self->m_queueTail - self->m_queueHead >= kQueueCapacity)
			{
				const int64_t newPts = ptsUs;
				uint32_t worstIdx = self->m_queueHead;
				int64_t  worstPts = self->m_queue[worstIdx % kQueueCapacity].ptsUs;

				for (uint32_t ii = self->m_queueHead + 1; ii != self->m_queueTail; ++ii)
				{
					const int64_t pts = self->m_queue[ii % kQueueCapacity].ptsUs;

					if (pts > worstPts)
					{
						worstPts = pts;
						worstIdx = ii;
					}
				}

				if (newPts >= worstPts)
				{
					return;
				}

				CFRelease(self->m_queue[worstIdx % kQueueCapacity].pb);
				uint32_t writeIdx = self->m_queueHead;

				for (uint32_t ii = self->m_queueHead; ii != self->m_queueTail; ++ii)
				{
					if (ii == worstIdx)
					{
						continue;
					}

					self->m_queue[writeIdx % kQueueCapacity] = self->m_queue[ii % kQueueCapacity];
					++writeIdx;
				}

				self->m_queueTail = writeIdx;
			}

			CFRetain(_imageBuffer);
			QueueEntry& e = self->m_queue[self->m_queueTail % kQueueCapacity];
			e.pb    = (CVPixelBufferRef)_imageBuffer;
			e.ptsUs = ptsUs;
			++self->m_queueTail;
		}

		static constexpr uint32_t kQueueCapacity = 192;
		static constexpr uint32_t kReorderDepth  = 4;

		struct QueueEntry
		{
			CVPixelBufferRef pb;
			int64_t          ptsUs;
		};

		RendererContextMtl* m_renderer;
		MTL::Device*        m_device;

		CMVideoFormatDescriptionRef m_formatDesc;
		VTDecompressionSessionRef   m_session;
		CVMetalTextureCacheRef      m_textureCache;
		bx::Mutex  m_queueMutex;
		QueueEntry m_queue[kQueueCapacity];
		uint32_t   m_queueHead;
		uint32_t   m_queueTail;
		uint16_t   m_dstWidth;
		uint16_t   m_dstHeight;
		uint32_t   m_initFlags;
		uint32_t   m_cachedAuBytes;
		uint64_t   m_dtsCounter;
		int64_t    m_lastDisplayedPts;
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
#if defined(__MAC_14_0) || defined(__IPHONE_17_0)
		{ VideoCodec::AV1,  kCMVideoCodecType_AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_BIT_10, BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
#endif // defined(__MAC_14_0) || defined(__IPHONE_17_0)
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
