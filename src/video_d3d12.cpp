/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D12
#	include "renderer_d3d12.h"
#	include "video_d3d12.h"

#	if BGFX_CONFIG_VIDEO_DIRECT3D12
#		include "video.h"
#		include <dxva.h>

namespace bgfx { namespace d3d12
{
	struct RendererContextD3D12;

	void initVideoDecoder(const VideoBindingD3D12& _binding);
	ID3D12PipelineState* videoGetPipelineState(RendererContextD3D12* _renderer, ProgramHandle _handle);
	ScratchBufferD3D12& videoGetScratchBuffer(RendererContextD3D12* _renderer);
	D3D12_GPU_DESCRIPTOR_HANDLE videoGetSamplerHandle(RendererContextD3D12* _renderer, const uint32_t* _samplerFlags);
	ID3D12GraphicsCommandList* videoGetCommandList(RendererContextD3D12* _renderer);
	void videoReleaseResource(RendererContextD3D12* _renderer, ID3D12Resource* _resource);

	static VideoBindingD3D12 s_videoD3D12;

	extern const GUID IID_ID3D12CommandAllocator;
	extern const GUID IID_ID3D12CommandQueue;
	extern const GUID IID_ID3D12Fence;
	extern const GUID IID_ID3D12GraphicsCommandList;
	extern const GUID IID_ID3D12Resource;

	static const GUID IID_ID3D12VideoDecodeCommandList                  = { 0x3b60536e, 0xad29, 0x4e64, { 0xa2, 0x69, 0xf8, 0x53, 0x83, 0x7e, 0x5e, 0x53 } };
	static const GUID IID_ID3D12VideoDecoder                            = { 0xc59b6bdc, 0x7720, 0x4074, { 0xa1, 0x36, 0x17, 0xa1, 0x56, 0x03, 0x74, 0x70 } };
	static const GUID IID_ID3D12VideoDecoderHeap                        = { 0x0946b7c9, 0xebf6, 0x4047, { 0xbb, 0x73, 0x86, 0x83, 0xe2, 0x7d, 0xbb, 0x1f } };
	static const GUID IID_ID3D12VideoDevice                             = { 0x1f052807, 0x0b46, 0x4acc, { 0x8a, 0x89, 0x36, 0x4f, 0x79, 0x37, 0x18, 0xa4 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_AV1_12BIT_PROFILE2     = { 0x17127009, 0xa00f, 0x4ce1, { 0x99, 0x4e, 0xbf, 0x40, 0x81, 0xf6, 0xf3, 0xf0 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_AV1_12BIT_PROFILE2_420 = { 0x2d80bed6, 0x9cac, 0x4835, { 0x9e, 0x91, 0x32, 0x7b, 0xbc, 0x4f, 0x9e, 0xe8 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_AV1_PROFILE0           = { 0xb8be4ccb, 0xcf53, 0x46ba, { 0x8d, 0x59, 0xd6, 0xb8, 0xa6, 0xda, 0x5d, 0x2a } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_AV1_PROFILE1           = { 0x6936ff0f, 0x45b1, 0x4163, { 0x9c, 0xc1, 0x64, 0x6e, 0xf6, 0x94, 0x61, 0x08 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_AV1_PROFILE2           = { 0x0c5f2aa1, 0xe541, 0x4089, { 0xbb, 0x7b, 0x98, 0x11, 0x0a, 0x19, 0xd7, 0xc8 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_H264                   = { 0x1b81be68, 0xa0c7, 0x11d3, { 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN              = { 0x5b11d51b, 0x2f4c, 0x4452, { 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10            = { 0x107af0e0, 0xef1a, 0x4d19, { 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10_422        = { 0x0bac4fe5, 0x1532, 0x4429, { 0xa8, 0x54, 0xf8, 0x4d, 0xe0, 0x49, 0x53, 0xdb } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10_444        = { 0x0dabeffa, 0x4458, 0x4602, { 0xbc, 0x03, 0x07, 0x95, 0x65, 0x9d, 0x61, 0x7c } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN12            = { 0x1a72925f, 0x0c2c, 0x4f15, { 0x96, 0xfb, 0xb1, 0x7d, 0x14, 0x73, 0x60, 0x3f } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN12_422        = { 0x55bcac81, 0xf311, 0x4093, { 0xa7, 0xd0, 0x1c, 0xbc, 0x0b, 0x84, 0x9b, 0xee } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN12_444        = { 0x9798634d, 0xfe9d, 0x48e5, { 0xb4, 0xda, 0xdb, 0xec, 0x45, 0xb3, 0xdf, 0x01 } };
	static const GUID D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN_444          = { 0x4008018f, 0xf537, 0x4b36, { 0x98, 0xcf, 0x61, 0xaf, 0x8a, 0x2c, 0x1a, 0x33 } };

	struct VideoDecoderD3D12
	{
		static constexpr uint32_t kNumDpbSlots         = 17;
		static constexpr uint32_t kBitstreamRingFrames = 8;
		static constexpr uint32_t kCopyRingSize        = 16;

		struct ReorderedPicture
		{
			ID3D12Resource* texture;
			int32_t displayOrder;
			int64_t ptsUs;
		};

		struct DpbState
		{
			D3D12_RESOURCE_STATES state;
			int32_t  poc;
			int32_t  frameNum;
		};

		VideoDecoderD3D12()
			: m_renderer(NULL)
			, m_videoDevice(NULL)
			, m_decoder(NULL)
			, m_decoderHeap(NULL)
			, m_videoQueue(NULL)
			, m_videoFence(NULL)
			, m_videoFenceValue(0)
			, m_videoControl(BX_COUNTOF(m_videoCmdAllocator) )
			, m_copyControl(BX_COUNTOF(m_copyCmdAllocator) )
			, m_bitstreamBuffer(NULL)
			, m_bitstreamMapped(NULL)
			, m_bitstreamCapacity(0)
			, m_bitstreamCursor(0)
			, m_dummyCbv(NULL)
			, m_dpb(NULL)
			, m_dpbOutput(NULL)
			, m_referenceOnly(false)
			, m_codedWidth(0)
			, m_codedHeight(0)
			, m_dstWidth(0)
			, m_dstHeight(0)
			, m_numDpbSlots(kNumDpbSlots)
			, m_nextSlot(0)
			, m_currentSlot(0)
			, m_numActiveRefs(0)
			, m_displayOrderNext(0)
			, m_prevPocLsb(0)
			, m_prevPocMsb(0)
			, m_displayedSlot(-1)
			, m_prevDisplayedSlot(-1)
			, m_statusReportFeedback(0)
			, m_initFlags(0)
			, m_cachedAuBytes(0)
		{
			bx::memSet(m_dpbState, 0, sizeof(m_dpbState) );
			bx::memSet(m_referenceUsage, 0, sizeof(m_referenceUsage) );
			bx::memSet(&m_spsActive, 0, sizeof(m_spsActive) );

			for (uint32_t ii = 0; ii < kBitstreamRingFrames; ++ii)
			{
				m_videoCmdAllocator[ii] = NULL;
				m_videoCmdAllocatorFence[ii] = 0;
			}

			m_videoCmd = NULL;

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				m_copyCmdAllocator[ii] = NULL;
				m_copyFenceRing[ii] = 0;
			}

			m_copyCmdList        = NULL;
			m_copyFence      = NULL;
			m_copyFenceValue = 0;

			bx::memSet(m_slotLastCopyFence, 0, sizeof(m_slotLastCopyFence) );

			m_lastDpbOutputCopyFence = 0;

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				m_reorderPool[ii].texture     = NULL;
				m_reorderPool[ii].displayOrder = -1;
			}
		}

		bool create(const VideoDecoderInit& _init, RendererContextD3D12* _renderer, uint16_t _width, uint16_t _height)
		{
			m_renderer = _renderer;
			m_initFlags     = _init.flags;
			m_cachedAuBytes = (0 != _init.cachedAuBytes) ? _init.cachedAuBytes : (4u << 20);
			m_auQueue.configure(m_cachedAuBytes, 0 != (m_initFlags & BGFX_VIDEO_DECODER_INIT_RETAIN) );

			if (VideoCodec::H264 != _init.codec)
			{
				BX_TRACE("VideoDecoderD3D12: codec %d not yet supported on D3D12.", _init.codec);
				return false;
			}

			if (NULL == _init.parameterSets
			||  0    == _init.parameterSetsSize)
			{
				BX_TRACE("VideoDecoderD3D12: empty parameter sets.");
				return false;
			}

			h264::PPS ppsActive = {};
			if (!bgfx::parseParameterSets(m_spsArray, BX_COUNTOF(m_spsArray), m_ppsArray, BX_COUNTOF(m_ppsArray), m_spsActive, ppsActive, _init.parameterSets, _init.parameterSetsSize) )
			{
				BX_TRACE("VideoDecoderD3D12: failed to parse SPS/PPS from parameter sets.");
				return false;
			}

			if (0 != m_spsActive.bit_depth_luma_minus8
			||  0 != m_spsActive.bit_depth_chroma_minus8
			||  1 != m_spsActive.chroma_format_idc)
			{
				BX_TRACE("VideoDecoderD3D12: only 8-bit 4:2:0 (NV12) is supported.");
				return false;
			}

			HRESULT hr = s_videoD3D12.device->QueryInterface(IID_ID3D12VideoDevice, (void**)&m_videoDevice);
			if (FAILED(hr)
			||  NULL == m_videoDevice)
			{
				BX_TRACE("VideoDecoderD3D12: ID3D12VideoDevice not available.");
				return false;
			}

			m_dstWidth  = _width;
			m_dstHeight = _height;

			m_codedWidth  = (m_spsActive.pic_width_in_mbs_minus1 + 1) * 16;
			m_codedHeight = (m_spsActive.pic_height_in_map_units_minus1 + 1) * 16 * (m_spsActive.frame_mbs_only_flag ? 1 : 2);

			m_numDpbSlots = bx::clamp<uint32_t>(uint32_t(m_spsActive.num_ref_frames) + 1, 2, kNumDpbSlots);
			const DXGI_FORMAT decodeFormat = DXGI_FORMAT_NV12;

			D3D12_VIDEO_DECODER_DESC decoderDesc
			{
				.NodeMask      = 0,
				.Configuration =
				{
					.DecodeProfile       = D3D12_VIDEO_DECODE_PROFILE_H264,
					.BitstreamEncryption = {},
					.InterlaceType       = D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_NONE,
				},
			};

			D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT decodeSupport
			{
				.NodeIndex          = 0,
				.Configuration      = decoderDesc.Configuration,
				.Width              = m_codedWidth,
				.Height             = m_codedHeight,
				.DecodeFormat       = decodeFormat,
				.FrameRate          = { 0, 1 },
				.BitRate            = 0,
				.SupportFlags       = D3D12_VIDEO_DECODE_SUPPORT_FLAG_NONE,
				.ConfigurationFlags = D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_NONE,
				.DecodeTier         = D3D12_VIDEO_DECODE_TIER_NOT_SUPPORTED,
			};

			hr = m_videoDevice->CheckFeatureSupport(D3D12_FEATURE_VIDEO_DECODE_SUPPORT, &decodeSupport, sizeof(decodeSupport) );

			if (FAILED(hr)
			||  0 == (decodeSupport.SupportFlags & D3D12_VIDEO_DECODE_SUPPORT_FLAG_SUPPORTED)
			||  decodeSupport.DecodeTier < D3D12_VIDEO_DECODE_TIER_1)
			{
				BX_TRACE("VideoDecoderD3D12: H.264 NV12 not supported by hardware (tier=%d, hr=0x%08x).", decodeSupport.DecodeTier, hr);
				DX_RELEASE_I(m_videoDevice);
				return false;
			}

			m_referenceOnly = 0 != (decodeSupport.ConfigurationFlags & D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_REFERENCE_ONLY_ALLOCATIONS_REQUIRED);

			const uint16_t vendorId = s_videoD3D12.vendorId;
			if (BGFX_PCI_ID_INTEL == vendorId)
			{
				if (!m_referenceOnly)
				{
					BX_TRACE("VideoDecoderD3D12: Intel detected (vendorId=0x%04x): forcing reference-only DPB.", vendorId);
				}
				m_referenceOnly = true;
			}

			uint32_t heapWidth  = m_codedWidth;
			uint32_t heapHeight = m_codedHeight;
			if (0 != (decodeSupport.ConfigurationFlags & D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_HEIGHT_ALIGNMENT_MULTIPLE_32_REQUIRED) )
			{
				heapWidth  = bx::strideAlign(heapWidth,  32);
				heapHeight = bx::strideAlign(heapHeight, 32);
			}

			D3D12_VIDEO_DECODER_HEAP_DESC heapDesc
			{
				.NodeMask                    = 0,
				.Configuration               = decoderDesc.Configuration,
				.DecodeWidth                 = heapWidth,
				.DecodeHeight                = heapHeight,
				.Format                      = decodeFormat,
				.FrameRate                   = { 0, 1 },
				.BitRate                     = 0,
				.MaxDecodePictureBufferCount = m_numDpbSlots,
			};
			hr = m_videoDevice->CreateVideoDecoderHeap(&heapDesc, IID_ID3D12VideoDecoderHeap, (void**)&m_decoderHeap);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: CreateVideoDecoderHeap failed (0x%08x).", hr);
				destroy();
				return false;
			}

			hr = m_videoDevice->CreateVideoDecoder(&decoderDesc, IID_ID3D12VideoDecoder, (void**)&m_decoder);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: CreateVideoDecoder failed (0x%08x).", hr);
				destroy();
				return false;
			}

			D3D12_COMMAND_QUEUE_DESC queueDesc
			{
				.Type     = D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE,
				.Priority = 0,
				.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE,
				.NodeMask = 0,
			};

			hr = s_videoD3D12.device->CreateCommandQueue(&queueDesc, IID_ID3D12CommandQueue, (void**)&m_videoQueue);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: video CreateCommandQueue failed (0x%08x).", hr);
				destroy();
				return false;
			}

			for (uint32_t ii = 0; ii < kBitstreamRingFrames; ++ii)
			{
				hr = s_videoD3D12.device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE, IID_ID3D12CommandAllocator, (void**)&m_videoCmdAllocator[ii]);
				if (FAILED(hr) )
				{
					BX_TRACE("VideoDecoderD3D12: video CreateCommandAllocator failed (0x%08x).", hr);
					destroy();
					return false;
				}
			}

			hr = s_videoD3D12.device->CreateCommandList(0
				, D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE
				, m_videoCmdAllocator[0]
				, NULL
				, IID_ID3D12VideoDecodeCommandList
				, (void**)&m_videoCmd
				);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: CreateCommandList(VIDEO_DECODE) failed (0x%08x).", hr);
				destroy();
				return false;
			}

			m_videoCmd->Close();

			hr = s_videoD3D12.device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, (void**)&m_videoFence);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: CreateFence failed (0x%08x).", hr);
				destroy();
				return false;
			}

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				hr = s_videoD3D12.device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_ID3D12CommandAllocator, (void**)&m_copyCmdAllocator[ii]);
				if (FAILED(hr) )
				{
					BX_TRACE("VideoDecoderD3D12: copy CreateCommandAllocator failed (0x%08x).", hr);
					destroy();
					return false;
				}
			}

			hr = s_videoD3D12.device->CreateCommandList(0
				, D3D12_COMMAND_LIST_TYPE_DIRECT
				, m_copyCmdAllocator[0]
				, NULL
				, IID_ID3D12GraphicsCommandList
				, (void**)&m_copyCmdList
				);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: CreateCommandList(DIRECT) failed (0x%08x).", hr);
				destroy();
				return false;
			}

			m_copyCmdList->Close();

			hr = s_videoD3D12.device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_ID3D12Fence, (void**)&m_copyFence);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: copy CreateFence failed (0x%08x).", hr);
				destroy();
				return false;
			}

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				m_copyFenceRing[ii] = 0;
			}

			m_copyFenceValue = 0;
			m_videoControl.reset();
			m_copyControl.reset();
			bx::memSet(m_slotLastCopyFence, 0, sizeof(m_slotLastCopyFence) );

			const uint32_t bitstreamBudget = bx::max<uint32_t>(2u*1024u*1024u, m_codedWidth * m_codedHeight);
			m_bitstreamCapacity = bx::alignUp<uint64_t>(uint64_t(bitstreamBudget) * kBitstreamRingFrames, D3D12_VIDEO_DECODE_MIN_BITSTREAM_OFFSET_ALIGNMENT);

			{
				D3D12_RESOURCE_DESC desc
				{
					.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER,
					.Alignment        = 0,
					.Width            = m_bitstreamCapacity,
					.Height           = 1,
					.DepthOrArraySize = 1,
					.MipLevels        = 1,
					.Format           = DXGI_FORMAT_UNKNOWN,
					.SampleDesc       = { .Count = 1, .Quality = 0 },
					.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
					.Flags            = D3D12_RESOURCE_FLAG_NONE,
				};

				D3D12_HEAP_PROPERTIES heap
				{
					.Type                 = D3D12_HEAP_TYPE_UPLOAD,
					.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
					.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
					.CreationNodeMask     = 0,
					.VisibleNodeMask      = 0,
				};

				hr = s_videoD3D12.device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_ID3D12Resource, (void**)&m_bitstreamBuffer);

				if (FAILED(hr) )
				{
					BX_TRACE("VideoDecoderD3D12: bitstream buffer create failed (0x%08x).", hr);
					destroy();
					return false;
				}

				D3D12_RANGE noRead = { 0, 0 };
				hr = m_bitstreamBuffer->Map(0, &noRead, (void**)&m_bitstreamMapped);

				if (FAILED(hr) )
				{
					BX_TRACE("VideoDecoderD3D12: bitstream Map failed (0x%08x).", hr);
					destroy();
					return false;
				}
			}

			{
				D3D12_RESOURCE_DESC desc
				{
					.Dimension        = D3D12_RESOURCE_DIMENSION_BUFFER,
					.Alignment        = 0,
					.Width            = 256,
					.Height           = 1,
					.DepthOrArraySize = 1,
					.MipLevels        = 1,
					.Format           = DXGI_FORMAT_UNKNOWN,
					.SampleDesc       = { .Count = 1, .Quality = 0 },
					.Layout           = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,
					.Flags            = D3D12_RESOURCE_FLAG_NONE,
				};

				D3D12_HEAP_PROPERTIES heap
				{
					.Type                 = D3D12_HEAP_TYPE_UPLOAD,
					.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
					.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
					.CreationNodeMask     = 0,
					.VisibleNodeMask      = 0,
				};

				hr = s_videoD3D12.device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_ID3D12Resource, (void**)&m_dummyCbv);

				if (FAILED(hr) )
				{
					BX_TRACE("VideoDecoderD3D12: dummy CBV create failed (0x%08x).", hr);
					destroy();
					return false;
				}
			}

			{
				D3D12_RESOURCE_DESC desc
				{
					.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
					.Alignment        = 0,
					.Width            = m_codedWidth,
					.Height           = m_codedHeight,
					.DepthOrArraySize = uint16_t(m_numDpbSlots),
					.MipLevels        = 1,
					.Format           = decodeFormat,
					.SampleDesc       = { .Count = 1, .Quality = 0 },
					.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
					.Flags            = m_referenceOnly
						? (D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY | D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE)
						: D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS
						,
				};

				D3D12_HEAP_PROPERTIES heap
				{
					.Type                 = D3D12_HEAP_TYPE_DEFAULT,
					.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
					.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
					.CreationNodeMask     = 0,
					.VisibleNodeMask      = 0,
				};

				hr = s_videoD3D12.device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COMMON, NULL, IID_ID3D12Resource, (void**)&m_dpb);

				if (FAILED(hr) )
				{
					BX_TRACE("VideoDecoderD3D12: DPB texture create failed (0x%08x).", hr);
					destroy();
					return false;
				}

				if (m_referenceOnly)
				{
					// AMD path: separate output texture (sampleable NV12).
					desc.DepthOrArraySize = 1;
					desc.Flags = D3D12_RESOURCE_FLAG_NONE;
					hr = s_videoD3D12.device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COMMON, NULL, IID_ID3D12Resource, (void**)&m_dpbOutput);
					if (FAILED(hr) )
					{
						BX_TRACE("VideoDecoderD3D12: DPB output texture create failed (0x%08x).", hr);
						destroy();
						return false;
					}
				}
			}

			for (uint32_t ii = 0; ii < m_numDpbSlots; ++ii)
			{
				m_dpbState[ii].state = D3D12_RESOURCE_STATE_COMMON;
			}

			BX_TRACE("VideoDecoderD3D12: H.264 decoder ready, coded %dx%d, dst %dx%d, %s DPB."
				, m_codedWidth, m_codedHeight
				, m_dstWidth, m_dstHeight
				, m_referenceOnly ? "reference-only" : "shared"
				);

			return true;
		}

		void destroy()
		{
			if (NULL != m_videoFence
			&&  NULL != m_videoQueue)
			{
				const uint64_t fence = ++m_videoFenceValue;
				m_videoQueue->Signal(m_videoFence, fence);

				if (m_videoFence->GetCompletedValue() < fence)
				{
					HANDLE evt = CreateEventA(NULL, FALSE, FALSE, NULL);
					m_videoFence->SetEventOnCompletion(fence, evt);
					WaitForSingleObject(evt, INFINITE);
					CloseHandle(evt);
				}
			}

			if (NULL != m_copyFence
			&&  NULL != s_videoD3D12.commandQueue)
			{
				const uint64_t fence = ++m_copyFenceValue;
				s_videoD3D12.commandQueue->Signal(m_copyFence, fence);

				if (m_copyFence->GetCompletedValue() < fence)
				{
					HANDLE evt = CreateEventA(NULL, FALSE, FALSE, NULL);
					m_copyFence->SetEventOnCompletion(fence, evt);
					WaitForSingleObject(evt, INFINITE);
					CloseHandle(evt);
				}
			}

			DX_RELEASE(m_videoCmd, 0);
			DX_RELEASE(m_copyCmdList, 0);

			for (uint32_t ii = 0; ii < kBitstreamRingFrames; ++ii)
			{
				if (NULL != m_videoCmdAllocator[ii])
				{
					m_videoCmdAllocator[ii]->Reset();
				}
			}

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				if (NULL != m_copyCmdAllocator[ii])
				{
					m_copyCmdAllocator[ii]->Reset();
				}
			}

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				if (NULL != m_reorderPool[ii].texture)
				{
					videoReleaseResource(m_renderer, m_reorderPool[ii].texture);
					m_reorderPool[ii].texture = NULL;
				}

				m_reorderPool[ii].displayOrder = -1;
			}

			if (NULL != m_bitstreamBuffer
			&&  NULL != m_bitstreamMapped)
			{
				D3D12_RANGE noWrite = { 0, 0 };
				m_bitstreamBuffer->Unmap(0, &noWrite);
				m_bitstreamMapped = NULL;
			}

			DX_RELEASE(m_bitstreamBuffer, 0);
			DX_RELEASE(m_dummyCbv, 0);
			DX_RELEASE(m_dpbOutput, 0);
			DX_RELEASE(m_dpb, 0);

			for (uint32_t ii = 0; ii < kBitstreamRingFrames; ++ii)
			{
				DX_RELEASE(m_videoCmdAllocator[ii], 0);
			}

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				DX_RELEASE(m_copyCmdAllocator[ii], 0);
			}

			DX_RELEASE(m_copyFence, 0);
			DX_RELEASE(m_videoFence, 0);
			DX_RELEASE(m_videoQueue, 0);
			DX_RELEASE(m_decoder, 0);
			DX_RELEASE(m_decoderHeap, 0);

			DX_RELEASE_I(m_videoDevice);
		}

		bool decode(const VideoDecoderFrame& _frame, TextureD3D12& _dst)
		{
			if (NULL == m_decoder)
			{
				return false;
			}

			if (0 != (_frame.flags & BGFX_VIDEO_DECODE_FRAME_SET) )
			{
				resetForSet();
			}

			if (NULL != _frame.bitstream && 0 != _frame.numAus)
			{
				const uint8_t* bs = _frame.bitstream;
				for (uint32_t ii = 0; ii < _frame.numAus; ++ii)
				{
					const uint32_t auSize = _frame.aus[ii].size;
					const bool isIdr = bgfx::peekAuIsIdr(bs, auSize);
					m_auQueue.enqueue(bs, auSize, _frame.aus[ii].ptsUs, isIdr);
					bs += auSize;
				}
			}

			while (!m_auQueue.empty()
			&&     bgfx::hasReorderSpace(m_reorderPool, kVideoMaxReorderInFlight) )
			{
				const bgfx::PendingAU& au = m_auQueue.front();
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
					adjustedClock = bgfx::applyLoopWrap(adjustedClock, m_auQueue.minPts(), m_auQueue.maxPts() );

					const bool poolCovers = bgfx::reorderPoolCovers(m_reorderPool, kVideoMaxReorderInFlight, adjustedClock, 500000);
					const bool forwardCanCatchUp = true
						&& !m_auQueue.empty()
						&& m_auQueue.front().ptsUs <= adjustedClock + 500000
						;

					if (!poolCovers
					&&  !forwardCanCatchUp)
					{
						bgfx::faultInFromCache(
							  m_auQueue
							, adjustedClock
							, [this]() { resetForSet(); }
							, [this](const uint8_t* _bs, uint32_t _bsSize, int64_t _pts)
							  {
								  decodeOneAU(_bs, _bsSize, _pts);
							  }
							, [this]()
							  {
								  return bgfx::hasReorderSpace(m_reorderPool, kVideoMaxReorderInFlight);
							  }
							);
					}
				}

				pickDisplaySlotForTime(adjustedClock, _dst);
			}

			return true;
		}

		void resetForSet()
		{
			if (m_auQueue.isRetaining() )
			{
				m_auQueue.rewindTo(m_auQueue.size() );
			}
			else
			{
				m_auQueue.clear();
			}

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				m_reorderPool[ii].displayOrder = -1;
				m_reorderPool[ii].ptsUs        = 0;
			}

			m_displayedSlot     = -1;
			m_prevDisplayedSlot = -1;
			m_displayOrderNext  = 0;
			m_numActiveRefs = 0;
			m_nextSlot      = 0;
			m_currentSlot   = 0;
			bx::memSet(m_referenceUsage, 0, sizeof(m_referenceUsage) );

			for (uint32_t ii = 0; ii < kNumDpbSlots; ++ii)
			{
				m_dpbState[ii].poc      = 0;
				m_dpbState[ii].frameNum = 0;
			}

			m_prevPocLsb = 0;
			m_prevPocMsb = 0;
		}

		bool decodeOneAU(const uint8_t* _bitstream, uint32_t _bitstreamSize, int64_t _ptsUs)
		{
			h264::NALHeader nal = {};
			h264::SliceHeader sh = {};
			bool isIdr = false;
			if (!bgfx::parseSliceFromAccessUnit(m_spsArray, m_ppsArray, _bitstream, _bitstreamSize, nal, sh, isIdr) )
			{
				BX_TRACE("VideoDecoderD3D12: no slice NAL found in access unit.");
				return false;
			}

			const h264::PPS& pps = m_ppsArray[sh.pic_parameter_set_id];
			const h264::SPS& sps = m_spsArray[pps.seq_parameter_set_id];

			if (isIdr)
			{
				m_numActiveRefs       = 0;
				m_nextSlot            = 0;
			}

			const int32_t poc = bgfx::computePoc(m_prevPocMsb, m_prevPocLsb, sps, sh, nal, isIdr);

			m_currentSlot = bgfx::pickFreeDpbSlot(
				  m_nextSlot
				, m_numDpbSlots
				, m_referenceUsage
				, m_numActiveRefs
				, [](uint32_t){ return false; }
				);
			BX_ASSERT(m_currentSlot < m_numDpbSlots
				, "DPB exhausted: m_numDpbSlots=%u m_numActiveRefs=%u. Cap maxRefs to m_numDpbSlots-1."
				, m_numDpbSlots
				, m_numActiveRefs
				);
			m_nextSlot = (m_currentSlot + 1) % m_numDpbSlots;

			const uint32_t reorderSlot = bgfx::pickReorderSlotOrEvictOldest(m_reorderPool, kVideoMaxReorderInFlight);
			const int32_t displayOrder = m_displayOrderNext++;
			m_reorderPool[reorderSlot].displayOrder = displayOrder;
			m_reorderPool[reorderSlot].ptsUs        = _ptsUs;

			m_dpbState[m_currentSlot].poc      = poc;
			m_dpbState[m_currentSlot].frameNum = sh.frame_num;

			while (0 == m_videoControl.reserve(1) )
			{
				const uint32_t readIdx = m_videoControl.m_read;
				const uint64_t waitFence = m_videoCmdAllocatorFence[readIdx];
				if (waitFence > m_videoFence->GetCompletedValue() )
				{
					HANDLE evt = CreateEventA(NULL, FALSE, FALSE, NULL);
					m_videoFence->SetEventOnCompletion(waitFence, evt);
					WaitForSingleObject(evt, INFINITE);
					CloseHandle(evt);
				}
				m_videoControl.consume(1);
			}

			const uint32_t allocIdx = m_videoControl.m_current;
			const uint32_t sliceOffsetInAu = bgfx::findFirstSliceNalOffset(_bitstream, _bitstreamSize);
			const uint8_t* sliceBitstream  = _bitstream + sliceOffsetInAu;
			const uint32_t sliceBitstreamSize = _bitstreamSize - sliceOffsetInAu;

			const uint32_t alignedSize = bx::alignUp<uint32_t>(sliceBitstreamSize, D3D12_VIDEO_DECODE_MIN_BITSTREAM_OFFSET_ALIGNMENT);
			if (m_bitstreamCursor + alignedSize > m_bitstreamCapacity)
			{
				m_bitstreamCursor = 0;
			}

			const uint64_t bitstreamOffset = m_bitstreamCursor;
			bx::memCopy(m_bitstreamMapped + bitstreamOffset, sliceBitstream, sliceBitstreamSize);
			m_bitstreamCursor += alignedSize;

			HRESULT hr = m_videoCmdAllocator[allocIdx]->Reset();
			BX_WARN(SUCCEEDED(hr), "VideoDecoderD3D12: video allocator Reset failed (0x%08x).", hr);
			BX_UNUSED(hr);

			hr = m_videoCmd->Reset(m_videoCmdAllocator[allocIdx]);
			BX_WARN(SUCCEEDED(hr), "VideoDecoderD3D12: video cmdlist Reset failed (0x%08x).", hr);

			if (m_dpbState[m_currentSlot].state != D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE)
			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = m_dpb,
							.Subresource = m_currentSlot,
							.StateBefore = m_dpbState[m_currentSlot].state,
							.StateAfter  = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = m_dpb,
							.Subresource = m_numDpbSlots + m_currentSlot,
							.StateBefore = m_dpbState[m_currentSlot].state,
							.StateAfter  = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
						},
					},
				};
				m_videoCmd->ResourceBarrier(BX_COUNTOF(barriers), barriers);
				m_dpbState[m_currentSlot].state = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE;
			}

			if (m_referenceOnly)
			{
				D3D12_RESOURCE_BARRIER barrier
				{
					.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
					.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
					.Transition =
					{
						.pResource   = m_dpbOutput,
						.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
						.StateBefore = D3D12_RESOURCE_STATE_COMMON,
						.StateAfter  = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
					},
				};
				m_videoCmd->ResourceBarrier(1, &barrier);
			}

			DXVA_PicParams_H264   picParams = {};
			DXVA_Qmatrix_H264     qmatrix   = {};
			DXVA_Slice_H264_Short sliceCtl  = {};

			picParams.wFrameWidthInMbsMinus1                 = uint16_t(sps.pic_width_in_mbs_minus1);
			picParams.wFrameHeightInMbsMinus1                = uint16_t(sps.pic_height_in_map_units_minus1);
			picParams.IntraPicFlag                           = isIdr ? 1 : 0;
			picParams.MbaffFrameFlag                         = 0;
			picParams.field_pic_flag                         = 0;
			picParams.chroma_format_idc                      = 1;
			picParams.bit_depth_chroma_minus8                = uint8_t(sps.bit_depth_chroma_minus8);
			picParams.bit_depth_luma_minus8                  = uint8_t(sps.bit_depth_luma_minus8);
			picParams.residual_colour_transform_flag         = uint8_t(sps.separate_colour_plane_flag);
			picParams.CurrPic.AssociatedFlag                 = 0;
			picParams.CurrPic.Index7Bits                     = uint8_t(m_currentSlot);
			picParams.CurrFieldOrderCnt[0]                   = poc;
			picParams.CurrFieldOrderCnt[1]                   = poc;

			for (uint32_t ii = 0; ii < 16; ++ii)
			{
				picParams.RefFrameList[ii].bPicEntry         = 0xFF;
				picParams.FieldOrderCntList[ii][0]           = 0;
				picParams.FieldOrderCntList[ii][1]           = 0;
				picParams.FrameNumList[ii]                   = 0;
			}
			picParams.UsedForReferenceFlags                  = 0;
			for (uint32_t ii = 0; ii < m_numActiveRefs && ii < 16; ++ii)
			{
				const uint32_t refSlot = m_referenceUsage[ii];
				picParams.RefFrameList[ii].AssociatedFlag    = 0;
				picParams.RefFrameList[ii].Index7Bits        = uint8_t(refSlot);
				picParams.FieldOrderCntList[ii][0]           = m_dpbState[refSlot].poc;
				picParams.FieldOrderCntList[ii][1]           = m_dpbState[refSlot].poc;
				picParams.FrameNumList[ii]                   = uint16_t(m_dpbState[refSlot].frameNum);
				picParams.UsedForReferenceFlags             |= 1u << (ii * 2 + 0);
				picParams.UsedForReferenceFlags             |= 1u << (ii * 2 + 1);
			}

			picParams.weighted_pred_flag                     = uint8_t(pps.weighted_pred_flag);
			picParams.weighted_bipred_idc                    = uint8_t(pps.weighted_bipred_idc);
			picParams.sp_for_switch_flag                     = 0;
			picParams.transform_8x8_mode_flag                = uint8_t(pps.transform_8x8_mode_flag);
			picParams.constrained_intra_pred_flag            = uint8_t(pps.constrained_intra_pred_flag);
			picParams.num_ref_frames                         = uint8_t(sps.num_ref_frames);
			picParams.MbsConsecutiveFlag                     = 1;
			picParams.frame_mbs_only_flag                    = uint8_t(sps.frame_mbs_only_flag);
			picParams.MinLumaBipredSize8x8Flag               = sps.level_idc >= 31 ? 1 : 0;
			picParams.RefPicFlag                             = (0 != nal.idc) ? 1 : 0;
			picParams.frame_num                              = uint16_t(sh.frame_num);
			picParams.pic_init_qp_minus26                    = int8_t(pps.pic_init_qp_minus26);
			picParams.pic_init_qs_minus26                    = int8_t(pps.pic_init_qs_minus26);
			picParams.chroma_qp_index_offset                 = int8_t(pps.chroma_qp_index_offset);
			picParams.second_chroma_qp_index_offset          = int8_t(pps.second_chroma_qp_index_offset);
			picParams.log2_max_frame_num_minus4              = uint8_t(sps.log2_max_frame_num_minus4);
			picParams.pic_order_cnt_type                     = uint8_t(sps.pic_order_cnt_type);
			picParams.log2_max_pic_order_cnt_lsb_minus4      = uint8_t(sps.log2_max_pic_order_cnt_lsb_minus4);
			picParams.delta_pic_order_always_zero_flag       = uint8_t(sps.delta_pic_order_always_zero_flag);
			picParams.direct_8x8_inference_flag              = uint8_t(sps.direct_8x8_inference_flag);
			picParams.entropy_coding_mode_flag               = uint8_t(pps.entropy_coding_mode_flag);
			picParams.pic_order_present_flag                 = uint8_t(pps.pic_order_present_flag);
			picParams.num_slice_groups_minus1                = uint8_t(pps.num_slice_groups_minus1);
			picParams.slice_group_map_type                   = uint8_t(pps.slice_group_map_type);
			picParams.deblocking_filter_control_present_flag = uint8_t(pps.deblocking_filter_control_present_flag);
			picParams.redundant_pic_cnt_present_flag         = uint8_t(pps.redundant_pic_cnt_present_flag);
			picParams.slice_group_change_rate_minus1         = uint16_t(pps.slice_group_change_rate_minus1);
			picParams.Reserved16Bits                         = 3;
			picParams.StatusReportFeedbackNumber             = ++m_statusReportFeedback;
			picParams.ContinuationFlag                       = 1;
			picParams.num_ref_idx_l0_active_minus1           = uint8_t(pps.num_ref_idx_l0_active_minus1);
			picParams.num_ref_idx_l1_active_minus1           = uint8_t(pps.num_ref_idx_l1_active_minus1);

			if (sps.seq_scaling_matrix_present_flag || pps.pic_scaling_matrix_present_flag)
			{
				uint8_t lists4x4[6][16];
				uint8_t lists8x8[2][64];
				buildEffectiveScalingLists(sps, pps, lists4x4, lists8x8);
				for (int i = 0; i < 6; ++i)
				{
					for (int j = 0; j < 16; ++j)
					{
						qmatrix.bScalingLists4x4[i][j] = lists4x4[i][j];
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					qmatrix.bScalingLists8x8[0][i] = lists8x8[0][i];
					qmatrix.bScalingLists8x8[1][i] = lists8x8[1][i];
				}
			}
			else
			{
				bx::memSet(&qmatrix, 16, sizeof(qmatrix) );
			}

			sliceCtl.BSNALunitDataLocation = 0;
			sliceCtl.SliceBytesInBuffer    = sliceBitstreamSize;
			sliceCtl.wBadSliceChopping     = 0;

			ID3D12Resource* refFrames[kNumDpbSlots]      = {};
			UINT            refSubresources[kNumDpbSlots] = {};
			for (uint32_t ii = 0; ii < m_numDpbSlots; ++ii)
			{
				refFrames[ii]       = m_dpb;
				refSubresources[ii] = UINT(ii);
			}

			D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS input
			{
				.NumFrameArguments = 3,
				.FrameArguments    =
				{
					{ .Type = D3D12_VIDEO_DECODE_ARGUMENT_TYPE_PICTURE_PARAMETERS,         .Size = sizeof(picParams), .pData = &picParams },
					{ .Type = D3D12_VIDEO_DECODE_ARGUMENT_TYPE_INVERSE_QUANTIZATION_MATRIX,.Size = sizeof(qmatrix),   .pData = &qmatrix   },
					{ .Type = D3D12_VIDEO_DECODE_ARGUMENT_TYPE_SLICE_CONTROL,              .Size = sizeof(sliceCtl),  .pData = &sliceCtl  },
				},
				.ReferenceFrames =
				{
					.NumTexture2Ds = kNumDpbSlots,
					.ppTexture2Ds  = refFrames,
					.pSubresources = refSubresources,
					.ppHeaps       = NULL,
				},
				.CompressedBitstream =
				{
					.pBuffer = m_bitstreamBuffer,
					.Offset  = bitstreamOffset,
					.Size    = sliceBitstreamSize,
				},
				.pHeap = m_decoderHeap,
			};

			D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS output = m_referenceOnly
				? D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS
				{
					.pOutputTexture2D    = m_dpbOutput,
					.OutputSubresource   = 0,
					.ConversionArguments =
					{
						.Enable               = TRUE,
						.pReferenceTexture2D  = m_dpb,
						.ReferenceSubresource = m_currentSlot,
						.OutputColorSpace     = DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709,
						.DecodeColorSpace     = DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709,
					},
				}
				: D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS
				{
					.pOutputTexture2D    = m_dpb,
					.OutputSubresource   = m_currentSlot,
					.ConversionArguments = {},
				}
				;

			m_videoCmd->DecodeFrame(m_decoder, &output, &input);

			if (m_referenceOnly)
			{
				D3D12_RESOURCE_BARRIER barrier
				{
					.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
					.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
					.Transition =
					{
						.pResource   = m_dpbOutput,
						.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
						.StateBefore = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
						.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
					},
				};
				m_videoCmd->ResourceBarrier(1, &barrier);

				D3D12_RESOURCE_BARRIER dpbBarriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = m_dpb,
							.Subresource = m_currentSlot,
							.StateBefore = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = m_dpb,
							.Subresource = m_numDpbSlots + m_currentSlot,
							.StateBefore = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
				};
				m_videoCmd->ResourceBarrier(BX_COUNTOF(dpbBarriers), dpbBarriers);
				m_dpbState[m_currentSlot].state = D3D12_RESOURCE_STATE_COMMON;
			}
			else
			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = m_dpb,
							.Subresource = m_currentSlot,
							.StateBefore = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = m_dpb,
							.Subresource = m_numDpbSlots + m_currentSlot,
							.StateBefore = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
				};
				m_videoCmd->ResourceBarrier(BX_COUNTOF(barriers), barriers);
				m_dpbState[m_currentSlot].state = D3D12_RESOURCE_STATE_COMMON;
			}

			hr = m_videoCmd->Close();
			BX_WARN(SUCCEEDED(hr), "VideoDecoderD3D12: video Close failed (0x%08x).", hr);

			ID3D12CommandList* lists[] = { m_videoCmd };

			if (m_slotLastCopyFence[m_currentSlot] > 0)
			{
				m_videoQueue->Wait(m_copyFence, m_slotLastCopyFence[m_currentSlot]);
			}

			if (m_referenceOnly && m_lastDpbOutputCopyFence > 0)
			{
				m_videoQueue->Wait(m_copyFence, m_lastDpbOutputCopyFence);
			}

			m_videoQueue->ExecuteCommandLists(BX_COUNTOF(lists), lists);

			const uint64_t signalValue = ++m_videoFenceValue;
			m_videoQueue->Signal(m_videoFence, signalValue);
			m_videoCmdAllocatorFence[allocIdx] = signalValue;
			m_videoControl.commit(1);

			if (0 != nal.idc)
			{
				if (0 != sh.drpm.adaptive_ref_pic_marking_mode_flag
				&&  m_numActiveRefs > 0)
				{
					uint16_t refFrameNums[16];
					const uint32_t n = bx::min<uint32_t>(m_numActiveRefs, 16);

					for (uint32_t ii = 0; ii < n; ++ii)
					{
						refFrameNums[ii] = uint16_t(m_dpbState[m_referenceUsage[ii]].frameNum);
					}

					const int32_t maxFrameNum = 1 << (sps.log2_max_frame_num_minus4 + 4);

					m_numActiveRefs = applyMmcoUnmarkShortTerm(
						  m_referenceUsage
						, refFrameNums
						, n
						, sh.frame_num
						, maxFrameNum
						, sh
						);
				}

				const uint32_t maxRefs = bx::min<uint32_t>(uint32_t(sps.num_ref_frames), m_numDpbSlots - 1);

				m_numActiveRefs = bgfx::appendShortTermRef(
					  m_referenceUsage
					, m_numActiveRefs
					, m_currentSlot
					, maxRefs
					);
			}

			while (0 == m_copyControl.reserve(1) )
			{
				const uint32_t readIdx = m_copyControl.m_read;
				const uint64_t waitFence = m_copyFenceRing[readIdx];

				if (m_copyFence->GetCompletedValue() < waitFence)
				{
					HANDLE evt = CreateEventA(NULL, FALSE, FALSE, NULL);
					m_copyFence->SetEventOnCompletion(waitFence, evt);
					WaitForSingleObject(evt, INFINITE);
					CloseHandle(evt);
				}

				m_copyControl.consume(1);
			}

			const uint32_t copyRingIdx = m_copyControl.m_current;

			hr = m_copyCmdAllocator[copyRingIdx]->Reset();
			BX_WARN(SUCCEEDED(hr), "VideoDecoderD3D12: copy allocator Reset failed (0x%08x).", hr);

			hr = m_copyCmdList->Reset(m_copyCmdAllocator[copyRingIdx], NULL);
			BX_WARN(SUCCEEDED(hr), "VideoDecoderD3D12: copy cmdlist Reset failed (0x%08x).", hr);

			ID3D12GraphicsCommandList* commandList = m_copyCmdList;

			ID3D12Resource* nv12Source = m_referenceOnly
				? m_dpbOutput
				: m_dpb;

			const uint32_t nv12LumaSubres   = m_referenceOnly ? 0u : m_currentSlot;
			const uint32_t nv12ChromaSubres = m_referenceOnly ? 1u : (m_numDpbSlots + m_currentSlot);

			ID3D12Resource* reorderTex = acquireReorderTexture(uint32_t(reorderSlot) );

			if (NULL == reorderTex)
			{
				m_copyCmdList->Close();
				return false;
			}

			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = reorderTex,
							.Subresource = 0,
							.StateBefore = D3D12_RESOURCE_STATE_COMMON,
							.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = reorderTex,
							.Subresource = 1,
							.StateBefore = D3D12_RESOURCE_STATE_COMMON,
							.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST,
						},
					},
				};

				commandList->ResourceBarrier(BX_COUNTOF(barriers), barriers);
			}

			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = nv12Source,
							.Subresource = nv12LumaSubres,
							.StateBefore = D3D12_RESOURCE_STATE_COMMON,
							.StateAfter  = D3D12_RESOURCE_STATE_COPY_SOURCE,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = nv12Source,
							.Subresource = nv12ChromaSubres,
							.StateBefore = D3D12_RESOURCE_STATE_COMMON,
							.StateAfter  = D3D12_RESOURCE_STATE_COPY_SOURCE,
						},
					},
				};

				commandList->ResourceBarrier(BX_COUNTOF(barriers), barriers);
			}

			{
				const uint32_t reorderW = (m_dstWidth  + 1) & ~1u;
				const uint32_t reorderH = (m_dstHeight + 1) & ~1u;

				const D3D12_BOX lumaBox   = { 0, 0, 0, reorderW,     reorderH,     1 };
				const D3D12_BOX chromaBox = { 0, 0, 0, reorderW / 2, reorderH / 2, 1 };

				{
					D3D12_TEXTURE_COPY_LOCATION dst
					{
						.pResource        = reorderTex,
						.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
						.SubresourceIndex = 0,
					};
					D3D12_TEXTURE_COPY_LOCATION src
					{
						.pResource        = nv12Source,
						.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
						.SubresourceIndex = nv12LumaSubres,
					};
					commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, &lumaBox);
				}

				{
					D3D12_TEXTURE_COPY_LOCATION dst
					{
						.pResource        = reorderTex,
						.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
						.SubresourceIndex = 1,
					};
					D3D12_TEXTURE_COPY_LOCATION src
					{
						.pResource        = nv12Source,
						.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,
						.SubresourceIndex = nv12ChromaSubres,
					};
					commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, &chromaBox);
				}
			}

			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = nv12Source,
							.Subresource = nv12LumaSubres,
							.StateBefore = D3D12_RESOURCE_STATE_COPY_SOURCE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = nv12Source,
							.Subresource = nv12ChromaSubres,
							.StateBefore = D3D12_RESOURCE_STATE_COPY_SOURCE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
				};
				commandList->ResourceBarrier(BX_COUNTOF(barriers), barriers);
			}

			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = reorderTex,
							.Subresource = 0,
							.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
					{
						.Type       = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags      = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = reorderTex,
							.Subresource = 1,
							.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
				};
				commandList->ResourceBarrier(BX_COUNTOF(barriers), barriers);
			}

			hr = m_copyCmdList->Close();
			BX_WARN(SUCCEEDED(hr), "VideoDecoderD3D12: copy Close failed (0x%08x).", hr);

			ID3D12CommandQueue* gfxQueue = s_videoD3D12.commandQueue;
			gfxQueue->Wait(m_videoFence, signalValue);

			ID3D12CommandList* copyLists[] = { m_copyCmdList };
			gfxQueue->ExecuteCommandLists(BX_COUNTOF(copyLists), copyLists);

			const uint64_t copySignal = ++m_copyFenceValue;
			gfxQueue->Signal(m_copyFence, copySignal);

			m_copyFenceRing[copyRingIdx] = copySignal;
			m_slotLastCopyFence[m_currentSlot] = copySignal;
			m_lastDpbOutputCopyFence = copySignal;
			m_copyControl.commit(1);

			return true;
		}

		void pickDisplaySlotForTime(int64_t _presentationTimeUs, TextureD3D12& _dst)
		{
			bgfx::pickDisplaySlotForTime(
				  _presentationTimeUs
				, m_reorderPool
				, kVideoMaxReorderInFlight
				, m_displayedSlot
				, m_prevDisplayedSlot
				, m_auQueue.empty()
				, [this, &_dst](uint32_t _slot)
				  {
					  ID3D12GraphicsCommandList* gfx = videoGetCommandList(m_renderer);
					  dispatchYuvToRgb(gfx, m_reorderPool[_slot].texture, _dst);
				  }
				);
		}

		RendererContextD3D12* m_renderer;

		ID3D12Resource* acquireReorderTexture(uint32_t _slot)
		{
			BX_ASSERT(_slot < kVideoMaxReorderInFlight, "VideoDecoderD3D12: reorder slot %u out of range.", _slot);
			if (NULL != m_reorderPool[_slot].texture)
			{
				return m_reorderPool[_slot].texture;
			}

			ID3D12Device* device = s_videoD3D12.device;

			D3D12_RESOURCE_DESC desc
			{
				.Dimension        = D3D12_RESOURCE_DIMENSION_TEXTURE2D,
				.Alignment        = 0,
				.Width            = (m_dstWidth  + 1) & ~1u,
				.Height           = (m_dstHeight + 1) & ~1u,
				.DepthOrArraySize = 1,
				.MipLevels        = 1,
				.Format           = DXGI_FORMAT_NV12,
				.SampleDesc       = { .Count = 1, .Quality = 0 },
				.Layout           = D3D12_TEXTURE_LAYOUT_UNKNOWN,
				.Flags            = D3D12_RESOURCE_FLAG_NONE,
			};

			D3D12_HEAP_PROPERTIES heap
			{
				.Type                 = D3D12_HEAP_TYPE_DEFAULT,
				.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
				.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN,
				.CreationNodeMask     = 0,
				.VisibleNodeMask      = 0,
			};

			HRESULT hr = device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_COMMON, NULL, IID_ID3D12Resource, (void**)&m_reorderPool[_slot].texture);
			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D12: reorder texture create failed (0x%08x).", hr);
				return NULL;
			}

			return m_reorderPool[_slot].texture;
		}

		void dispatchYuvToRgb(ID3D12GraphicsCommandList* _commandList, ID3D12Resource* _nv12, TextureD3D12& _dst)
		{
			BX_ASSERT(NULL != g_videoDecode && isValid(g_videoDecode->m_program), "Video decode program not initialized.");

			ID3D12PipelineState* pso = videoGetPipelineState(m_renderer, g_videoDecode->m_program);

			if (NULL == pso)
			{
				return;
			}

			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = _nv12,
							.Subresource = 0,
							.StateBefore = D3D12_RESOURCE_STATE_COMMON,
							.StateAfter  = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
						},
					},
					{
						.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = _nv12,
							.Subresource = 1,
							.StateBefore = D3D12_RESOURCE_STATE_COMMON,
							.StateAfter  = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
						},
					},
				};
				_commandList->ResourceBarrier(BX_COUNTOF(barriers), barriers);
			}

			_dst.setState(_commandList, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

			ScratchBufferD3D12& scratch = videoGetScratchBuffer(m_renderer);

			_commandList->SetComputeRootSignature(s_videoD3D12.computeRootSignature);
			ID3D12DescriptorHeap* heaps[] =
			{
				s_videoD3D12.samplerHeap,
				scratch.getHeap(),
			};
			_commandList->SetDescriptorHeaps(BX_COUNTOF(heaps), heaps);
			_commandList->SetPipelineState(pso);

			uint32_t samplerFlags[BGFX_MAX_COMPUTE_BINDINGS] = {};
			samplerFlags[1] = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP;
			samplerFlags[2] = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP;
			_commandList->SetComputeRootDescriptorTable(ComputeRp::Sampler, videoGetSamplerHandle(m_renderer, samplerFlags) );

			D3D12_GPU_VIRTUAL_ADDRESS cbvAddress = m_dummyCbv->GetGPUVirtualAddress();
			_commandList->SetComputeRootConstantBufferView(ComputeRp::CBV, cbvAddress);

			D3D12_GPU_DESCRIPTOR_HANDLE srvHandle[BGFX_MAX_COMPUTE_BINDINGS] = {};
			{
				scratch.allocEmpty(srvHandle[0]);

				D3D12_SHADER_RESOURCE_VIEW_DESC srvDescY
				{
					.Format                  = DXGI_FORMAT_R8_UNORM,
					.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D,
					.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
					.Texture2D               =
					{
						.MostDetailedMip     = 0,
						.MipLevels           = 1,
						.PlaneSlice          = 0,
						.ResourceMinLODClamp = 0.0f,
					},
				};
				scratch.allocSrv(srvHandle[1], _nv12, srvDescY);

				D3D12_SHADER_RESOURCE_VIEW_DESC srvDescCbCr
				{
					.Format                  = DXGI_FORMAT_R8G8_UNORM,
					.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D,
					.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING,
					.Texture2D               =
					{
						.MostDetailedMip     = 0,
						.MipLevels           = 1,
						.PlaneSlice          = 1,
						.ResourceMinLODClamp = 0.0f,
					},
				};
				scratch.allocSrv(srvHandle[2], _nv12, srvDescCbCr);

				for (uint32_t ii = 3; ii < BGFX_MAX_COMPUTE_BINDINGS; ++ii)
				{
					scratch.allocEmpty(srvHandle[ii]);
				}
			}
			_commandList->SetComputeRootDescriptorTable(ComputeRp::SRV, srvHandle[0]);

			D3D12_GPU_DESCRIPTOR_HANDLE uavHandle[BGFX_MAX_COMPUTE_BINDINGS] = {};
			{
				scratch.allocUav(uavHandle[0], _dst, 0);

				for (uint32_t ii = 1; ii < BGFX_MAX_COMPUTE_BINDINGS; ++ii)
				{
					scratch.allocEmpty(uavHandle[ii]);
				}
			}
			_commandList->SetComputeRootDescriptorTable(ComputeRp::UAV, uavHandle[0]);

			_commandList->Dispatch(
				  bx::max<uint32_t>( (m_dstWidth  + 7) / 8, 1)
				, bx::max<uint32_t>( (m_dstHeight + 7) / 8, 1)
				, 1
				);

			{
				D3D12_RESOURCE_BARRIER barriers[2]
				{
					{
						.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = _nv12,
							.Subresource = 0,
							.StateBefore = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
					{
						.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
						.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
						.Transition =
						{
							.pResource   = _nv12,
							.Subresource = 1,
							.StateBefore = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,
							.StateAfter  = D3D12_RESOURCE_STATE_COMMON,
						},
					},
				};
				_commandList->ResourceBarrier(BX_COUNTOF(barriers), barriers);
			}
		}

		ID3D12VideoDevice*            m_videoDevice;
		ID3D12VideoDecoder*           m_decoder;
		ID3D12VideoDecoderHeap*       m_decoderHeap;
		ID3D12CommandQueue*           m_videoQueue;
		ID3D12CommandAllocator*       m_videoCmdAllocator[kBitstreamRingFrames];
		uint64_t                      m_videoCmdAllocatorFence[kBitstreamRingFrames];
		ID3D12VideoDecodeCommandList* m_videoCmd;
		ID3D12Fence*                  m_videoFence;
		uint64_t                      m_videoFenceValue;
		bx::RingBufferControl         m_videoControl;

		ID3D12CommandAllocator*    m_copyCmdAllocator[kCopyRingSize];
		ID3D12GraphicsCommandList* m_copyCmdList;
		ID3D12Fence*               m_copyFence;
		uint64_t                   m_copyFenceValue;
		uint64_t                   m_copyFenceRing[kCopyRingSize];
		uint64_t                   m_slotLastCopyFence[kNumDpbSlots];

		uint64_t              m_lastDpbOutputCopyFence;
		bx::RingBufferControl m_copyControl;

		ID3D12Resource* m_bitstreamBuffer;
		uint8_t*        m_bitstreamMapped;
		uint64_t        m_bitstreamCapacity;
		uint64_t        m_bitstreamCursor;
		ID3D12Resource* m_dummyCbv;

		ID3D12Resource* m_dpb;
		ID3D12Resource* m_dpbOutput;
		bool            m_referenceOnly;
		DpbState        m_dpbState[kNumDpbSlots];
		uint8_t         m_referenceUsage[kNumDpbSlots];

		uint32_t m_codedWidth;
		uint32_t m_codedHeight;
		uint32_t m_dstWidth;
		uint32_t m_dstHeight;
		uint32_t m_numDpbSlots;
		uint32_t m_nextSlot;
		uint32_t m_currentSlot;
		uint32_t m_numActiveRefs;

		int32_t  m_displayOrderNext;
		int32_t  m_prevPocLsb;
		int32_t  m_prevPocMsb;

		ReorderedPicture m_reorderPool[kVideoMaxReorderInFlight];
		int32_t   m_displayedSlot;
		int32_t   m_prevDisplayedSlot;

		uint32_t  m_statusReportFeedback;

		bgfx::AuQueue m_auQueue;

		uint32_t  m_initFlags;
		uint32_t  m_cachedAuBytes;

		h264::SPS m_spsActive;
		h264::SPS m_spsArray[kVideoMaxH264SpsCount];
		h264::PPS m_ppsArray[kVideoMaxH264PpsCount];
	};

	VideoDecoderD3D12* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextD3D12* _renderer, uint16_t _width, uint16_t _height)
	{
		VideoDecoderD3D12* decoder = BX_NEW(g_allocator, VideoDecoderD3D12);
		if (!decoder->create(_init, _renderer, _width, _height) )
		{
			decoder->destroy();
			bx::deleteObject(g_allocator, decoder);
			return NULL;
		}
		return decoder;
	}

	void videoDecoderDestroy(VideoDecoderD3D12* _decoder)
	{
		if (NULL != _decoder)
		{
			_decoder->destroy();
			bx::deleteObject(g_allocator, _decoder);
		}
	}

	bool videoDecoderDecode(VideoDecoderD3D12* _decoder, const VideoDecoderFrame& _frame, TextureD3D12& _dst)
	{
		return _decoder->decode(_frame, _dst);
	}

	void initVideoDecoder(const VideoBindingD3D12& _binding)
	{
		s_videoD3D12 = _binding;

		ID3D12VideoDevice* videoDevice = NULL;
		HRESULT hr = _binding.device->QueryInterface(IID_ID3D12VideoDevice, (void**)&videoDevice);

		if (FAILED(hr) || NULL == videoDevice)
		{
			return;
		}

		D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILE_COUNT profileCount = {};
		hr = videoDevice->CheckFeatureSupport(
			  D3D12_FEATURE_VIDEO_DECODE_PROFILE_COUNT
			, &profileCount
			, sizeof(profileCount)
			);

		if (FAILED(hr) || 0 == profileCount.ProfileCount)
		{
			DX_RELEASE(videoDevice, 0);
			return;
		}

		GUID* profiles = (GUID*)BX_STACK_ALLOC(profileCount.ProfileCount * sizeof(GUID) );

		D3D12_FEATURE_DATA_VIDEO_DECODE_PROFILES profileList
		{
			.NodeIndex    = 0,
			.ProfileCount = profileCount.ProfileCount,
			.pProfiles    = profiles,
		};

		hr = videoDevice->CheckFeatureSupport(
			  D3D12_FEATURE_VIDEO_DECODE_PROFILES
			, &profileList
			, sizeof(profileList)
			);

		if (FAILED(hr) )
		{
			DX_RELEASE(videoDevice, 0);
			return;
		}

		struct ProfileEntry
		{
			const GUID*      guid;
			VideoCodec::Enum codec;
			uint32_t         caps;
		};

		static const ProfileEntry s_profiles[] =
		{
			{ &D3D12_VIDEO_DECODE_PROFILE_H264,                   VideoCodec::H264, BGFX_CAPS_VIDEO_CODEC_BIT_8  | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN,              VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_8  | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10,            VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN12,            VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_12 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10_422,        VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_422 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN12_422,        VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_12 | BGFX_CAPS_VIDEO_CODEC_CHROMA_422 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN_444,          VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_8  | BGFX_CAPS_VIDEO_CODEC_CHROMA_444 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN10_444,        VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_444 },
			{ &D3D12_VIDEO_DECODE_PROFILE_HEVC_MAIN12_444,        VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_12 | BGFX_CAPS_VIDEO_CODEC_CHROMA_444 },
			{ &D3D12_VIDEO_DECODE_PROFILE_AV1_PROFILE0,           VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_8
			                                                                      | BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &D3D12_VIDEO_DECODE_PROFILE_AV1_PROFILE1,           VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_8
			                                                                      | BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_444 },
			{ &D3D12_VIDEO_DECODE_PROFILE_AV1_PROFILE2,           VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
				                                                                                                 | BGFX_CAPS_VIDEO_CODEC_CHROMA_422 },
			{ &D3D12_VIDEO_DECODE_PROFILE_AV1_12BIT_PROFILE2,     VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_12 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
				                                                                                                 | BGFX_CAPS_VIDEO_CODEC_CHROMA_422 },
			{ &D3D12_VIDEO_DECODE_PROFILE_AV1_12BIT_PROFILE2_420, VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_12 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },

		};

		bool anySupported = false;

		for (UINT ii = 0; ii < profileList.ProfileCount; ++ii)
		{
			for (uint32_t jj = 0; jj < BX_COUNTOF(s_profiles); ++jj)
			{
				if (0 != bx::memCmp(&profiles[ii], s_profiles[jj].guid, sizeof(GUID) ) )
				{
					continue;
				}

				D3D12_FEATURE_DATA_VIDEO_DECODE_SUPPORT support
				{
					.NodeIndex     = 0,
					.Configuration =
					{
						.DecodeProfile       = profiles[ii],
						.BitstreamEncryption = D3D12_BITSTREAM_ENCRYPTION_TYPE_NONE,
						.InterlaceType       = D3D12_VIDEO_FRAME_CODED_INTERLACE_TYPE_NONE,
					},
					.Width        = 1920,
					.Height       = 1080,
					.DecodeFormat = (s_profiles[jj].caps & BGFX_CAPS_VIDEO_CODEC_BIT_10)
						? DXGI_FORMAT_P010 : DXGI_FORMAT_NV12,
					.FrameRate          = { .Numerator = 30, .Denominator = 1 },
					.BitRate            = 0,
					.SupportFlags       = D3D12_VIDEO_DECODE_SUPPORT_FLAG_NONE,
					.ConfigurationFlags = D3D12_VIDEO_DECODE_CONFIGURATION_FLAG_NONE,
					.DecodeTier         = D3D12_VIDEO_DECODE_TIER_NOT_SUPPORTED,
				};

				hr = videoDevice->CheckFeatureSupport(
					  D3D12_FEATURE_VIDEO_DECODE_SUPPORT
					, &support
					, sizeof(support)
					);

				if (SUCCEEDED(hr)
				&&  0 != (support.SupportFlags & D3D12_VIDEO_DECODE_SUPPORT_FLAG_SUPPORTED) )
				{
					g_caps.codecs[s_profiles[jj].codec] |= s_profiles[jj].caps;
					anySupported = true;
				}

				break;
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

		DX_RELEASE_I(videoDevice);
	}

} } // namespace bgfx::d3d12

#	else

namespace bgfx { namespace d3d12
{
	void initVideoDecoder(const VideoBindingD3D12& _binding)
	{
		BX_UNUSED(_binding);
	}

	VideoDecoderD3D12* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextD3D12* _renderer, uint16_t _width, uint16_t _height)
	{
		BX_UNUSED(_init, _renderer, _width, _height);
		return NULL;
	}

	void videoDecoderDestroy(VideoDecoderD3D12* _decoder)
	{
		BX_UNUSED(_decoder);
	}

	bool videoDecoderDecode(VideoDecoderD3D12* _decoder, const VideoDecoderFrame& _frame, TextureD3D12& _dst)
	{
		BX_UNUSED(_decoder, _frame, _dst);
		return false;
	}

} } // namespace bgfx::d3d12

#	endif // BGFX_CONFIG_VIDEO_DIRECT3D12

#endif // BGFX_CONFIG_RENDERER_DIRECT3D12
