/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D11
#	include "renderer_d3d11.h"
#	include "video_d3d11.h"

#	if BGFX_CONFIG_VIDEO_DIRECT3D11
#		include "video.h"
#		include <dxva.h>

namespace bgfx { namespace d3d11
{
	struct RendererContextD3D11;

	const ProgramD3D11& videoGetProgram(RendererContextD3D11* _renderer, ProgramHandle _handle);
	ID3D11SamplerState* videoGetSamplerState(RendererContextD3D11* _renderer, uint32_t _flags);

	static VideoBindingD3D11 s_videoD3D11;

	extern const GUID IID_ID3D11Device3;

	static const GUID IID_ID3D11VideoContext          = { 0x61f21c45, 0x3c0e, 0x4a74, { 0x9c, 0xea, 0x67, 0x10, 0x0d, 0x9a, 0xd5, 0xe4 } };
	static const GUID IID_ID3D11VideoDevice           = { 0x10ec4d5b, 0x975a, 0x4689, { 0xb9, 0xe4, 0xd0, 0xaa, 0xc3, 0x0f, 0xe3, 0x33 } };
	static const GUID DXVA2_ModeH264_E                = { 0x1b81be68, 0xa0c7, 0x11d3, { 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5 } };
	static const GUID DXVA2_ModeH264_VLD_FGT          = { 0x1b81be69, 0xa0c7, 0x11d3, { 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5 } };
	static const GUID DXVA2_ModeHEVC_VLD_Main         = { 0x5b11d51b, 0x2f4c, 0x4452, { 0xbc, 0xc3, 0x09, 0xf2, 0xa1, 0x16, 0x0c, 0xc0 } };
	static const GUID DXVA2_ModeHEVC_VLD_Main10       = { 0x107af0e0, 0xef1a, 0x4d19, { 0xab, 0xa8, 0x67, 0xa1, 0x63, 0x07, 0x3d, 0x13 } };
	static const GUID DXVA2_NoEncrypt                 = { 0x1b81bed0, 0xa0c7, 0x11d3, { 0xb9, 0x84, 0x00, 0xc0, 0x4f, 0x2e, 0x73, 0xc5 } };
	static const GUID DXVA_ModeAV1_VLD_12bit_Profile2 = { 0x17127009, 0xa00f, 0x4ce1, { 0x99, 0x4e, 0xbf, 0x40, 0x81, 0xf6, 0xf3, 0xf0 } };
	static const GUID DXVA_ModeAV1_VLD_Profile0       = { 0xb8be4ccb, 0xcf53, 0x46ba, { 0x8d, 0x59, 0xd6, 0xb8, 0xa6, 0xda, 0x5d, 0x2a } };
	static const GUID DXVA_ModeAV1_VLD_Profile1       = { 0x6936ff0f, 0x45b1, 0x4163, { 0x9c, 0xc1, 0x64, 0x6e, 0xf6, 0x94, 0x6e, 0xea } };
	static const GUID DXVA_ModeAV1_VLD_Profile2       = { 0x0c5f2aa1, 0xe541, 0x4089, { 0xbb, 0x7b, 0x98, 0x11, 0x0a, 0x19, 0xd7, 0xc8 } };

	struct VideoDecoderD3D11
	{
		static constexpr uint32_t kNumDpbSlots = 32;

		struct ReorderedPicture
		{
			int32_t slotIndex;
			int32_t displayOrder;
			int64_t ptsUs;
		};

		struct DpbState
		{
			int32_t poc;
			int32_t frameNum;
		};

		VideoDecoderD3D11()
			: m_renderer(NULL)
			, m_videoDevice(NULL)
			, m_videoContext(NULL)
			, m_decoder(NULL)
			, m_sampler(NULL)
			, m_codedWidth(0)
			, m_codedHeight(0)
			, m_dstWidth(0)
			, m_dstHeight(0)
			, m_numDpbSlots(kNumDpbSlots)
			, m_nextSlot(0)
			, m_currentSlot(0)
			, m_numActiveRefs(0)
			, m_prevPocLsb(0)
			, m_prevPocMsb(0)
			, m_displayedSlot(-1)
			, m_prevDisplayedSlot(-1)
			, m_statusReportFeedback(0)
			, m_initFlags(0)
			, m_cachedAuBytes(0)
		{
			m_dpbArray = NULL;

			bx::memSet(m_dpbViews,        0, sizeof(m_dpbViews) );
			bx::memSet(m_reorderTex,      0, sizeof(m_reorderTex) );
			bx::memSet(m_reorderSrvY,     0, sizeof(m_reorderSrvY) );
			bx::memSet(m_reorderSrvCbCr,  0, sizeof(m_reorderSrvCbCr) );
			bx::memSet(m_dpbState,        0, sizeof(m_dpbState) );
			bx::memSet(m_referenceUsage,  0, sizeof(m_referenceUsage) );
			bx::memSet(&m_spsActive,      0, sizeof(m_spsActive) );
			bx::memSet(m_spsArray,        0, sizeof(m_spsArray) );
			bx::memSet(m_ppsArray,        0, sizeof(m_ppsArray) );

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				m_reorderPool[ii].slotIndex    = -1;
				m_reorderPool[ii].displayOrder = -1;
				m_reorderPool[ii].ptsUs        = 0;
			}
		}

		bool create(const VideoDecoderInit& _init, RendererContextD3D11* _renderer, uint16_t _width, uint16_t _height)
		{
			m_renderer = _renderer;

			m_initFlags     = _init.flags;
			m_cachedAuBytes = (0 != _init.cachedAuBytes) ? _init.cachedAuBytes : (4u << 20);
			m_auQueue.configure(m_cachedAuBytes, 0 != (m_initFlags & BGFX_VIDEO_DECODER_INIT_RETAIN) );

			if (VideoCodec::H264 != _init.codec)
			{
				BX_TRACE("VideoDecoderD3D11: codec %d not yet supported on D3D11.", _init.codec);
				return false;
			}

			if (NULL == _init.parameterSets
			||  0    == _init.parameterSetsSize)
			{
				BX_TRACE("VideoDecoderD3D11: empty parameter sets.");
				return false;
			}

			h264::PPS ppsActive = {};

			if (!parseParameterSets(m_spsArray, BX_COUNTOF(m_spsArray), m_ppsArray, BX_COUNTOF(m_ppsArray), m_spsActive, ppsActive, _init.parameterSets, _init.parameterSetsSize) )
			{
				BX_TRACE("VideoDecoderD3D11: failed to parse SPS/PPS from parameter sets.");
				return false;
			}

			if (0 != m_spsActive.bit_depth_luma_minus8
			||  0 != m_spsActive.bit_depth_chroma_minus8
			||  1 != m_spsActive.chroma_format_idc)
			{
				BX_TRACE("VideoDecoderD3D11: only 8-bit 4:2:0 (NV12) is supported.");
				return false;
			}

			m_dstWidth    = _width;
			m_dstHeight   = _height;
			m_codedWidth  = (m_spsActive.pic_width_in_mbs_minus1 + 1) * 16;
			m_codedHeight = (m_spsActive.pic_height_in_map_units_minus1 + 1) * 16 * (m_spsActive.frame_mbs_only_flag ? 1 : 2);

			HRESULT hr = s_videoD3D11.device->QueryInterface(IID_ID3D11VideoDevice, (void**)&m_videoDevice);

			if (FAILED(hr)
			||  NULL == m_videoDevice)
			{
				BX_TRACE("VideoDecoderD3D11: ID3D11VideoDevice not available (hr=0x%08x).", hr);
				return false;
			}

			hr = s_videoD3D11.deviceCtx->QueryInterface(IID_ID3D11VideoContext, (void**)&m_videoContext);

			if (FAILED(hr)
			||  NULL == m_videoContext)
			{
				BX_TRACE("VideoDecoderD3D11: ID3D11VideoContext not available (hr=0x%08x).", hr);
				return false;
			}

			bool h264Supported = false;
			const uint32_t decoderProfileCount = m_videoDevice->GetVideoDecoderProfileCount();

			for (uint32_t ii = 0; ii < decoderProfileCount; ++ii)
			{
				GUID profile = {};
				if (SUCCEEDED(m_videoDevice->GetVideoDecoderProfile(ii, &profile) )
				&&  0 == bx::memCmp(&profile, &DXVA2_ModeH264_E, sizeof(GUID) ) )
				{
					h264Supported = true;
					break;
				}
			}

			if (!h264Supported)
			{
				BX_TRACE("VideoDecoderD3D11: H.264 NoFGT decode profile not supported by hardware.");
				return false;
			}

			const uint32_t paddedWidth  = bx::strideAlign(m_codedWidth,  16);
			const uint32_t paddedHeight = bx::strideAlign(m_codedHeight, 16);

			D3D11_VIDEO_DECODER_DESC decoderDesc
			{
				.Guid         = DXVA2_ModeH264_E,
				.SampleWidth  = paddedWidth,
				.SampleHeight = paddedHeight,
				.OutputFormat = DXGI_FORMAT_NV12,
			};

			uint32_t configCount = 0;
			hr = m_videoDevice->GetVideoDecoderConfigCount(&decoderDesc, &configCount);

			if (FAILED(hr) || 0 == configCount)
			{
				BX_TRACE("VideoDecoderD3D11: GetVideoDecoderConfigCount failed (hr=0x%08x, count=%u).", hr, configCount);
				return false;
			}

			D3D11_VIDEO_DECODER_CONFIG decoderConfig = {};
			bool gotConfig = false;

			for (uint32_t pass = 0; pass < 2 && !gotConfig; ++pass)
			{
				const UCHAR want = (0 == pass) ? 2 : 1;
				for (uint32_t ii = 0; ii < configCount; ++ii)
				{
					D3D11_VIDEO_DECODER_CONFIG cfg = {};
					if (FAILED(m_videoDevice->GetVideoDecoderConfig(&decoderDesc, ii, &cfg) ) )
					{
						continue;
					}

					const bool noEnc = true
						&& 0 == bx::memCmp(&cfg.guidConfigBitstreamEncryption, &DXVA2_NoEncrypt, sizeof(GUID) )
						&& 0 == bx::memCmp(&cfg.guidConfigMBcontrolEncryption, &DXVA2_NoEncrypt, sizeof(GUID) )
						&& 0 == bx::memCmp(&cfg.guidConfigResidDiffEncryption, &DXVA2_NoEncrypt, sizeof(GUID) )
						;

					if (noEnc
					&&  want == cfg.ConfigBitstreamRaw)
					{
						decoderConfig = cfg;
						gotConfig     = true;
						break;
					}
				}
			}

			if (!gotConfig)
			{
				BX_TRACE("VideoDecoderD3D11: no compatible D3D11_VIDEO_DECODER_CONFIG found.");
				return false;
			}

			hr = m_videoDevice->CreateVideoDecoder(&decoderDesc, &decoderConfig, &m_decoder);

			if (FAILED(hr)
			||  NULL == m_decoder)
			{
				BX_TRACE("VideoDecoderD3D11: CreateVideoDecoder failed (hr=0x%08x).", hr);
				return false;
			}

			{
				D3D11_TEXTURE2D_DESC desc
				{
					.Width          = paddedWidth,
					.Height         = paddedHeight,
					.MipLevels      = 1,
					.ArraySize      = m_numDpbSlots,
					.Format         = DXGI_FORMAT_NV12,
					.SampleDesc     = { .Count = 1, .Quality = 0 },
					.Usage          = D3D11_USAGE_DEFAULT,
					.BindFlags      = D3D11_BIND_DECODER,
					.CPUAccessFlags = 0,
					.MiscFlags      = 0,
				};

				hr = s_videoD3D11.device->CreateTexture2D(&desc, NULL, &m_dpbArray);

				if (FAILED(hr) || NULL == m_dpbArray)
				{
					BX_TRACE("VideoDecoderD3D11: DPB array texture create failed (hr=0x%08x).", hr);
					return false;
				}
			}

			for (uint32_t slot = 0; slot < m_numDpbSlots; ++slot)
			{
				D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC viewDesc
				{
					.DecodeProfile = DXVA2_ModeH264_E,
					.ViewDimension = D3D11_VDOV_DIMENSION_TEXTURE2D,
					.Texture2D     = { .ArraySlice = slot },
				};

				hr = m_videoDevice->CreateVideoDecoderOutputView(m_dpbArray, &viewDesc, &m_dpbViews[slot]);

				if (FAILED(hr)
				||  NULL == m_dpbViews[slot])
				{
					BX_TRACE("VideoDecoderD3D11: CreateVideoDecoderOutputView slot %u failed (hr=0x%08x).", slot, hr);
					return false;
				}
			}

			{
				const uint32_t reorderW = (m_dstWidth  + 1) & ~1u;
				const uint32_t reorderH = (m_dstHeight + 1) & ~1u;

				for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
				{
					D3D11_TEXTURE2D_DESC desc
					{
						.Width          = reorderW,
						.Height         = reorderH,
						.MipLevels      = 1,
						.ArraySize      = 1,
						.Format         = DXGI_FORMAT_NV12,
						.SampleDesc     = { .Count = 1, .Quality = 0 },
						.Usage          = D3D11_USAGE_DEFAULT,
						.BindFlags      = D3D11_BIND_SHADER_RESOURCE,
						.CPUAccessFlags = 0,
						.MiscFlags      = 0,
					};

					hr = s_videoD3D11.device->CreateTexture2D(&desc, NULL, &m_reorderTex[ii]);

					if (FAILED(hr)
					||  NULL == m_reorderTex[ii])
					{
						BX_TRACE("VideoDecoderD3D11: reorder texture %u create failed (hr=0x%08x).", ii, hr);
						return false;
					}

					ID3D11Device3* device3 = NULL;
					hr = s_videoD3D11.device->QueryInterface(IID_ID3D11Device3, (void**)&device3);

					if (FAILED(hr)
					||  NULL == device3)
					{
						BX_TRACE("VideoDecoderD3D11: ID3D11Device3 not available, planar NV12 SRVs require it (hr=0x%08x).", hr);
						return false;
					}

					ID3D11ShaderResourceView1* srv1 = NULL;

					D3D11_SHADER_RESOURCE_VIEW_DESC1 srvDescY
					{
						.Format        = DXGI_FORMAT_R8_UNORM,
						.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
						.Texture2D     = { .MostDetailedMip = 0, .MipLevels = 1, .PlaneSlice = 0 },
					};

					hr = device3->CreateShaderResourceView1(m_reorderTex[ii], &srvDescY, &srv1);

					if (FAILED(hr)
					||  NULL == srv1)
					{
						BX_TRACE("VideoDecoderD3D11: reorder R8 SRV %u failed (hr=0x%08x).", ii, hr);
						DX_RELEASE_I(device3);
						return false;
					}

					m_reorderSrvY[ii] = srv1;
					srv1 = NULL;

					D3D11_SHADER_RESOURCE_VIEW_DESC1 srvDescCbCr
					{
						.Format        = DXGI_FORMAT_R8G8_UNORM,
						.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
						.Texture2D     = { .MostDetailedMip = 0, .MipLevels = 1, .PlaneSlice = 1 },
					};

					hr = device3->CreateShaderResourceView1(m_reorderTex[ii], &srvDescCbCr, &srv1);

					if (FAILED(hr)
					||  NULL == srv1)
					{
						BX_TRACE("VideoDecoderD3D11: reorder R8G8 SRV %u failed (hr=0x%08x).", ii, hr);
						DX_RELEASE_I(device3);
						return false;
					}

					m_reorderSrvCbCr[ii] = srv1;

					DX_RELEASE_I(device3);
				}
			}

			m_sampler = videoGetSamplerState(
				  _renderer
				, BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				);

			if (NULL == m_sampler)
			{
				BX_TRACE("VideoDecoderD3D11: videoGetSamplerState failed.");
				return false;
			}

			BX_TRACE("VideoDecoderD3D11: H.264 decoder ready, coded %dx%d (padded %ux%u), dst %dx%d."
				, m_codedWidth, m_codedHeight
				, paddedWidth, paddedHeight
				, m_dstWidth, m_dstHeight
				);

			return true;
		}

		void destroy()
		{
			for (uint32_t ii = 0; ii < m_numDpbSlots; ++ii)
			{
				DX_RELEASE(m_dpbViews[ii], 0);
			}
			DX_RELEASE(m_dpbArray, 0);

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				DX_RELEASE(m_reorderSrvCbCr[ii], 0);
				DX_RELEASE(m_reorderSrvY[ii], 0);
				DX_RELEASE(m_reorderTex[ii], 0);
			}

			DX_RELEASE(m_decoder, 0);
			DX_RELEASE_I(m_videoContext);
			DX_RELEASE_I(m_videoDevice);

			m_sampler = NULL;

			m_currentSlot          = 0;
			m_nextSlot             = 0;
			m_numActiveRefs        = 0;
			m_displayedSlot        = -1;
			m_statusReportFeedback = 0;

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				m_reorderPool[ii].slotIndex    = -1;
				m_reorderPool[ii].displayOrder = -1;
				m_reorderPool[ii].ptsUs        = 0;
			}
		}

		bool decode(const VideoDecoderFrame& _frame, TextureD3D11& _dst)
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
					const bool isIdr = peekAuIsIdr(bs, auSize);
					m_auQueue.enqueue(bs, auSize, _frame.aus[ii].ptsUs, isIdr);
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
					adjustedClock = applyLoopWrap(adjustedClock, m_auQueue.minPts(), m_auQueue.maxPts() );

					const bool poolCovers = reorderPoolCovers(m_reorderPool, kVideoMaxReorderInFlight, adjustedClock, 500000);
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
							, [this]()
							  {
								  return hasReorderSpace(m_reorderPool, kVideoMaxReorderInFlight);
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
				m_reorderPool[ii].slotIndex    = -1;
				m_reorderPool[ii].displayOrder = -1;
				m_reorderPool[ii].ptsUs        = 0;
			}

			m_displayedSlot     = -1;
			m_prevDisplayedSlot = -1;
			m_numActiveRefs     = 0;
			m_nextSlot          = 0;
			m_currentSlot       = 0;
			m_prevPocLsb        = 0;
			m_prevPocMsb        = 0;

			bx::memSet(m_referenceUsage, 0, sizeof(m_referenceUsage) );
			bx::memSet(m_dpbState,       0, sizeof(m_dpbState) );

		}

		bool decodeOneAU(const uint8_t* _bitstream, uint32_t _bitstreamSize, int64_t _ptsUs)
		{
			h264::NALHeader nal = {};
			h264::SliceHeader sh = {};
			bool isIdr = false;

			if (!parseSliceFromAccessUnit(m_spsArray, m_ppsArray, _bitstream, _bitstreamSize, nal, sh, isIdr) )
			{
				BX_TRACE("VideoDecoderD3D11: no slice NAL found in access unit.");
				return false;
			}

			const h264::PPS& pps = m_ppsArray[sh.pic_parameter_set_id];
			const h264::SPS& sps = m_spsArray[pps.seq_parameter_set_id];

			if (isIdr)
			{
				m_numActiveRefs = 0;
				m_nextSlot      = 0;
			}

			const int32_t poc = computePoc(m_prevPocMsb, m_prevPocLsb, sps, sh, nal, isIdr);
			const int32_t displayOrder = poc / 2;

			m_currentSlot = pickFreeDpbSlot(
				  m_nextSlot
				, m_numDpbSlots
				, m_referenceUsage
				, m_numActiveRefs
				, [this](uint32_t _slot)
				{
					for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
					{
						if (-1 != m_reorderPool[ii].displayOrder
						&&  m_reorderPool[ii].slotIndex == int32_t(_slot) )
						{
							return true;
						}
					}

					return false;
				});

			BX_ASSERT(m_currentSlot < m_numDpbSlots
				, "DPB exhausted: m_numDpbSlots=%u m_numActiveRefs=%u. Cap maxRefs to m_numDpbSlots-1."
				, m_numDpbSlots
				, m_numActiveRefs
				);

			m_nextSlot = (m_currentSlot + 1) % m_numDpbSlots;
			m_dpbState[m_currentSlot].poc      = poc;
			m_dpbState[m_currentSlot].frameNum = sh.frame_num;

			const uint32_t poolIdx = pickReorderSlotOrEvictOldest(m_reorderPool, kVideoMaxReorderInFlight);
			m_reorderPool[poolIdx].slotIndex    = int32_t(m_currentSlot);
			m_reorderPool[poolIdx].displayOrder = displayOrder;
			m_reorderPool[poolIdx].ptsUs        = _ptsUs;

			DXVA_PicParams_H264 picParams = {};
			DXVA_Qmatrix_H264   qmatrix   = {};

			picParams.wFrameWidthInMbsMinus1         = uint16_t(sps.pic_width_in_mbs_minus1);
			picParams.wFrameHeightInMbsMinus1        = uint16_t(sps.pic_height_in_map_units_minus1);
			picParams.IntraPicFlag                   = isIdr ? 1 : 0;
			picParams.MbaffFrameFlag                 = 0;
			picParams.field_pic_flag                 = 0;
			picParams.chroma_format_idc              = 1;
			picParams.bit_depth_chroma_minus8        = uint8_t(sps.bit_depth_chroma_minus8);
			picParams.bit_depth_luma_minus8          = uint8_t(sps.bit_depth_luma_minus8);
			picParams.residual_colour_transform_flag = uint8_t(sps.separate_colour_plane_flag);
			picParams.CurrPic.AssociatedFlag         = 0;
			picParams.CurrPic.Index7Bits             = uint8_t(m_currentSlot);
			picParams.CurrFieldOrderCnt[0]           = poc;
			picParams.CurrFieldOrderCnt[1]           = poc;

			for (uint32_t ii = 0; ii < 16; ++ii)
			{
				picParams.RefFrameList[ii].bPicEntry = 0xFF;
				picParams.FieldOrderCntList[ii][0]   = 0;
				picParams.FieldOrderCntList[ii][1]   = 0;
				picParams.FrameNumList[ii]           = 0;
			}

			picParams.UsedForReferenceFlags = 0;

			for (uint32_t ii = 0; ii < m_numActiveRefs && ii < 16; ++ii)
			{
				const uint32_t refSlot = m_referenceUsage[ii];
				picParams.RefFrameList[ii].AssociatedFlag = 0;
				picParams.RefFrameList[ii].Index7Bits     = uint8_t(refSlot);
				picParams.FieldOrderCntList[ii][0]        = m_dpbState[refSlot].poc;
				picParams.FieldOrderCntList[ii][1]        = m_dpbState[refSlot].poc;
				picParams.FrameNumList[ii]                = uint16_t(m_dpbState[refSlot].frameNum);
				picParams.UsedForReferenceFlags          |= 1u << (ii * 2 + 0);
				picParams.UsedForReferenceFlags          |= 1u << (ii * 2 + 1);
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

			if (sps.seq_scaling_matrix_present_flag
			||  pps.pic_scaling_matrix_present_flag)
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

			const uint32_t sliceOffsetInAu    = findFirstSliceNalOffset(_bitstream, _bitstreamSize);
			const uint8_t* sliceBitstream     = _bitstream + sliceOffsetInAu;
			const uint32_t sliceBitstreamSize = _bitstreamSize - sliceOffsetInAu;

			DXVA_Slice_H264_Short sliceCtl
			{
				.BSNALunitDataLocation = 0,
				.SliceBytesInBuffer    = sliceBitstreamSize,
				.wBadSliceChopping     = 0,
			};

			HRESULT hr = m_videoContext->DecoderBeginFrame(m_decoder, m_dpbViews[m_currentSlot], 0, NULL);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D11: DecoderBeginFrame failed (hr=0x%08x).", hr);
				return false;
			}

			uint32_t  bufSize = 0;
			void* bufPtr  = NULL;

			hr = m_videoContext->GetDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_BITSTREAM, &bufSize, &bufPtr);

			if (FAILED(hr)
			||  NULL == bufPtr
			||  bufSize < sliceBitstreamSize)
			{
				BX_TRACE("VideoDecoderD3D11: GetDecoderBuffer(BITSTREAM) failed (hr=0x%08x, sz=%u, need=%u).", hr, bufSize, sliceBitstreamSize);
				m_videoContext->DecoderEndFrame(m_decoder);
				return false;
			}

			bx::memCopy(bufPtr, sliceBitstream, sliceBitstreamSize);
			m_videoContext->ReleaseDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_BITSTREAM);

			hr = m_videoContext->GetDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_PICTURE_PARAMETERS, &bufSize, &bufPtr);

			if (FAILED(hr)
			||  NULL == bufPtr
			||  bufSize < sizeof(picParams) )
			{
				BX_TRACE("VideoDecoderD3D11: GetDecoderBuffer(PICTURE_PARAMETERS) failed (hr=0x%08x).", hr);
				m_videoContext->DecoderEndFrame(m_decoder);
				return false;
			}

			bx::memCopy(bufPtr, &picParams, sizeof(picParams) );
			m_videoContext->ReleaseDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_PICTURE_PARAMETERS);

			hr = m_videoContext->GetDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_INVERSE_QUANTIZATION_MATRIX, &bufSize, &bufPtr);

			if (FAILED(hr)
			||  NULL == bufPtr
			||  bufSize < sizeof(qmatrix) )
			{
				BX_TRACE("VideoDecoderD3D11: GetDecoderBuffer(IQM) failed (hr=0x%08x).", hr);
				m_videoContext->DecoderEndFrame(m_decoder);
				return false;
			}

			bx::memCopy(bufPtr, &qmatrix, sizeof(qmatrix) );
			m_videoContext->ReleaseDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_INVERSE_QUANTIZATION_MATRIX);

			hr = m_videoContext->GetDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL, &bufSize, &bufPtr);

			if (FAILED(hr)
			||  NULL == bufPtr
			||  bufSize < sizeof(sliceCtl) )
			{
				BX_TRACE("VideoDecoderD3D11: GetDecoderBuffer(SLICE_CONTROL) failed (hr=0x%08x).", hr);
				m_videoContext->DecoderEndFrame(m_decoder);
				return false;
			}

			bx::memCopy(bufPtr, &sliceCtl, sizeof(sliceCtl) );

			m_videoContext->ReleaseDecoderBuffer(m_decoder, D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL);

			D3D11_VIDEO_DECODER_BUFFER_DESC bd[4]
			{
				{
					.BufferType         = D3D11_VIDEO_DECODER_BUFFER_BITSTREAM,
					.BufferIndex        = 0,
					.DataOffset         = 0,
					.DataSize           = sliceBitstreamSize,
					.FirstMBaddress     = 0,
					.NumMBsInBuffer     = 0,
					.Width              = 0,
					.Height             = 0,
					.Stride             = 0,
					.ReservedBits       = 0,
					.pIV                = NULL,
					.IVSize             = 0,
					.PartialEncryption  = FALSE,
					.EncryptedBlockInfo = {},
				},
				{
					.BufferType         = D3D11_VIDEO_DECODER_BUFFER_PICTURE_PARAMETERS,
					.BufferIndex        = 0,
					.DataOffset         = 0,
					.DataSize           = sizeof(picParams),
					.FirstMBaddress     = 0,
					.NumMBsInBuffer     = 0,
					.Width              = 0,
					.Height             = 0,
					.Stride             = 0,
					.ReservedBits       = 0,
					.pIV                = NULL,
					.IVSize             = 0,
					.PartialEncryption  = FALSE,
					.EncryptedBlockInfo = {},
				},
				{
					.BufferType         = D3D11_VIDEO_DECODER_BUFFER_INVERSE_QUANTIZATION_MATRIX,
					.BufferIndex        = 0,
					.DataOffset         = 0,
					.DataSize           = sizeof(qmatrix),
					.FirstMBaddress     = 0,
					.NumMBsInBuffer     = 0,
					.Width              = 0,
					.Height             = 0,
					.Stride             = 0,
					.ReservedBits       = 0,
					.pIV                = NULL,
					.IVSize             = 0,
					.PartialEncryption  = FALSE,
					.EncryptedBlockInfo = {},
				},
				{
					.BufferType         = D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL,
					.BufferIndex        = 0,
					.DataOffset         = 0,
					.DataSize           = sizeof(sliceCtl),
					.FirstMBaddress     = 0,
					.NumMBsInBuffer     = 0,
					.Width              = 0,
					.Height             = 0,
					.Stride             = 0,
					.ReservedBits       = 0,
					.pIV                = NULL,
					.IVSize             = 0,
					.PartialEncryption  = FALSE,
					.EncryptedBlockInfo = {},
				},
			};

			hr = m_videoContext->SubmitDecoderBuffers(m_decoder, BX_COUNTOF(bd), bd);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D11: SubmitDecoderBuffers failed (hr=0x%08x).", hr);
				m_videoContext->DecoderEndFrame(m_decoder);
				return false;
			}

			hr = m_videoContext->DecoderEndFrame(m_decoder);

			if (FAILED(hr) )
			{
				BX_TRACE("VideoDecoderD3D11: DecoderEndFrame failed (hr=0x%08x).", hr);
				return false;
			}

			{
				const uint32_t copyW = (m_dstWidth  + 1) & ~1u;
				const uint32_t copyH = (m_dstHeight + 1) & ~1u;
				const uint32_t srcW  = bx::min<uint32_t>(copyW, m_codedWidth);
				const uint32_t srcH  = bx::min<uint32_t>(copyH, m_codedHeight);

				ID3D11DeviceContext* deviceCtx = s_videoD3D11.deviceCtx;

				D3D11_BOX boxY;
				boxY.left   = 0;
				boxY.top    = 0;
				boxY.front  = 0;
				boxY.right  = srcW;
				boxY.bottom = srcH;
				boxY.back   = 1;
				deviceCtx->CopySubresourceRegion(
					  m_reorderTex[poolIdx], 0
					, 0, 0, 0
					, m_dpbArray, m_currentSlot
					, &boxY
					);

				D3D11_BOX boxUV;
				boxUV.left   = 0;
				boxUV.top    = 0;
				boxUV.front  = 0;
				boxUV.right  = srcW / 2;
				boxUV.bottom = srcH / 2;
				boxUV.back   = 1;
				deviceCtx->CopySubresourceRegion(
					  m_reorderTex[poolIdx], 1
					, 0, 0, 0
					, m_dpbArray, m_numDpbSlots + m_currentSlot
					, &boxUV
					);
			}

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

				const uint32_t maxRefs = bx::min<uint32_t>(
					  bx::min<uint32_t>(uint32_t(sps.num_ref_frames), 16)
					, m_numDpbSlots - 1
					);

				m_numActiveRefs = appendShortTermRef(
					  m_referenceUsage
					, m_numActiveRefs
					, m_currentSlot
					, maxRefs
					);
			}

			return true;
		}

		void pickDisplaySlotForTime(int64_t _presentationTimeUs, TextureD3D11& _dst)
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
					  dispatchYuvToRgb(_slot, _dst);
				});
		}


		void dispatchYuvToRgb(uint32_t _poolIdx, TextureD3D11& _dst)
		{
			BX_ASSERT(NULL != g_videoDecode && isValid(g_videoDecode->m_program), "Video decode program not initialized.");
			BX_ASSERT(_poolIdx < kVideoMaxReorderInFlight, "Reorder pool index out of range.");

			ID3D11DeviceContext*  deviceCtx = s_videoD3D11.deviceCtx;
			const ProgramD3D11&   program   = videoGetProgram(m_renderer, g_videoDecode->m_program);

			if (NULL == program.m_vsh
			||  NULL == program.m_vsh->m_computeShader
			||  NULL == _dst.m_uav)
			{
				return;
			}

			ID3D11ComputeShader* cs = program.m_vsh->m_computeShader;

			deviceCtx->CSSetShader(cs, NULL, 0);

			ID3D11ShaderResourceView* nullSrv = NULL;
			deviceCtx->VSSetShaderResources(0, 1, &nullSrv);
			deviceCtx->PSSetShaderResources(0, 1, &nullSrv);

			ID3D11ShaderResourceView* srvs[3] = { NULL, m_reorderSrvY[_poolIdx], m_reorderSrvCbCr[_poolIdx] };
			deviceCtx->CSSetShaderResources(0, 3, srvs);

			ID3D11SamplerState* samplers[3] = { NULL, m_sampler, m_sampler };
			deviceCtx->CSSetSamplers(0, 3, samplers);

			ID3D11UnorderedAccessView* uav = _dst.m_uav;
			deviceCtx->CSSetUnorderedAccessViews(0, 1, &uav, NULL);

			deviceCtx->Dispatch(
				  bx::max<uint32_t>( (m_dstWidth  + 7) / 8, 1)
				, bx::max<uint32_t>( (m_dstHeight + 7) / 8, 1)
				, 1
				);

			ID3D11UnorderedAccessView* nullUav = NULL;
			deviceCtx->CSSetUnorderedAccessViews(0, 1, &nullUav, NULL);

			ID3D11ShaderResourceView* nullSrvs[3] = { NULL, NULL, NULL };
			deviceCtx->CSSetShaderResources(0, 3, nullSrvs);

			ID3D11SamplerState* nullSamplers[3] = { NULL, NULL, NULL };
			deviceCtx->CSSetSamplers(0, 3, nullSamplers);

			deviceCtx->CSSetShader(NULL, NULL, 0);
		}

		RendererContextD3D11* m_renderer;

		ID3D11VideoDevice*  m_videoDevice;
		ID3D11VideoContext* m_videoContext;
		ID3D11VideoDecoder* m_decoder;

		ID3D11Texture2D*              m_dpbArray;
		ID3D11VideoDecoderOutputView* m_dpbViews[kNumDpbSlots];

		ID3D11Texture2D*          m_reorderTex[kVideoMaxReorderInFlight];
		ID3D11ShaderResourceView* m_reorderSrvY[kVideoMaxReorderInFlight];
		ID3D11ShaderResourceView* m_reorderSrvCbCr[kVideoMaxReorderInFlight];
		ID3D11SamplerState*       m_sampler;

		DpbState m_dpbState[kNumDpbSlots];
		uint8_t  m_referenceUsage[kNumDpbSlots];

		uint32_t m_codedWidth;
		uint32_t m_codedHeight;
		uint32_t m_dstWidth;
		uint32_t m_dstHeight;
		uint32_t m_numDpbSlots;
		uint32_t m_nextSlot;
		uint32_t m_currentSlot;
		uint32_t m_numActiveRefs;

		int32_t  m_prevPocLsb;
		int32_t  m_prevPocMsb;

		ReorderedPicture m_reorderPool[kVideoMaxReorderInFlight];
		int32_t  m_displayedSlot;
		int32_t  m_prevDisplayedSlot;

		uint32_t m_statusReportFeedback;

		AuQueue  m_auQueue;

		uint32_t m_initFlags;
		uint32_t m_cachedAuBytes;

		h264::SPS m_spsActive;
		h264::SPS m_spsArray[kVideoMaxH264SpsCount];
		h264::PPS m_ppsArray[kVideoMaxH264PpsCount];
	};

	VideoDecoderD3D11* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextD3D11* _renderer, uint16_t _width, uint16_t _height)
	{
		VideoDecoderD3D11* decoder = BX_NEW(g_allocator, VideoDecoderD3D11);

		if (!decoder->create(_init, _renderer, _width, _height) )
		{
			decoder->destroy();
			bx::deleteObject(g_allocator, decoder);
			return NULL;
		}

		return decoder;
	}

	void videoDecoderDestroy(VideoDecoderD3D11* _decoder)
	{
		if (NULL != _decoder)
		{
			_decoder->destroy();
			bx::deleteObject(g_allocator, _decoder);
		}
	}

	bool videoDecoderDecode(VideoDecoderD3D11* _decoder, const VideoDecoderFrame& _frame, TextureD3D11& _dst)
	{
		return _decoder->decode(_frame, _dst);
	}

	void initVideoDecoder(const VideoBindingD3D11& _binding)
	{
		s_videoD3D11 = _binding;

		ID3D11VideoDevice* videoDevice = NULL;
		HRESULT hr = _binding.device->QueryInterface(IID_ID3D11VideoDevice, (void**)&videoDevice);

		if (FAILED(hr)
		||  NULL == videoDevice)
		{
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
			// H.264
			{ &DXVA2_ModeH264_E,                VideoCodec::H264, BGFX_CAPS_VIDEO_CODEC_BIT_8  | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &DXVA2_ModeH264_VLD_FGT,          VideoCodec::H264, BGFX_CAPS_VIDEO_CODEC_BIT_8  | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },

			// HEVC / H.265
			{ &DXVA2_ModeHEVC_VLD_Main,         VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_8  | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &DXVA2_ModeHEVC_VLD_Main10,       VideoCodec::H265, BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },

			// AV1
			{ &DXVA_ModeAV1_VLD_Profile0,       VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_8
			                                                    | BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420 },
			{ &DXVA_ModeAV1_VLD_Profile1,       VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_8
			                                                    | BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_444 },
			{ &DXVA_ModeAV1_VLD_Profile2,       VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
			                                                                                   | BGFX_CAPS_VIDEO_CODEC_CHROMA_422 },
			{ &DXVA_ModeAV1_VLD_12bit_Profile2, VideoCodec::AV1,  BGFX_CAPS_VIDEO_CODEC_BIT_12 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
			                                                                                   | BGFX_CAPS_VIDEO_CODEC_CHROMA_422 },
		};

		const uint32_t supportedCount = videoDevice->GetVideoDecoderProfileCount();

		bool anySupported = false;

		for (uint32_t ii = 0; ii < supportedCount; ++ii)
		{
			GUID profile;

			if (FAILED(videoDevice->GetVideoDecoderProfile(ii, &profile) ) )
			{
				continue;
			}

			for (uint32_t jj = 0; jj < BX_COUNTOF(s_profiles); ++jj)
			{
				if (0 == bx::memCmp(&profile, s_profiles[jj].guid, sizeof(GUID) ) )
				{
					BOOL supported = false;
					hr = videoDevice->CheckVideoDecoderFormat(s_profiles[jj].guid, DXGI_FORMAT_NV12, &supported);

					if (SUCCEEDED(hr)
					&&  supported)
					{
						g_caps.codecs[s_profiles[jj].codec] |= s_profiles[jj].caps;
						anySupported = true;
					}

					supported = false;
					hr = videoDevice->CheckVideoDecoderFormat(s_profiles[jj].guid, DXGI_FORMAT_P010, &supported);

					if (SUCCEEDED(hr)
					&&  supported)
					{
						g_caps.codecs[s_profiles[jj].codec] |= s_profiles[jj].caps;
						anySupported = true;
					}

					break;
				}
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
} } // namespace bgfx::d3d11

#	else

namespace bgfx { namespace d3d11
{
	void initVideoDecoder(const VideoBindingD3D11& _binding)
	{
		BX_UNUSED(_binding);
	}

	VideoDecoderD3D11* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextD3D11* _renderer, uint16_t _width, uint16_t _height)
	{
		BX_UNUSED(_init, _renderer, _width, _height);
		return NULL;
	}

	void videoDecoderDestroy(VideoDecoderD3D11* _decoder)
	{
		BX_UNUSED(_decoder);
	}

	bool videoDecoderDecode(VideoDecoderD3D11* _decoder, const VideoDecoderFrame& _frame, TextureD3D11& _dst)
	{
		BX_UNUSED(_decoder, _frame, _dst);
		return false;
	}
} } // namespace bgfx::d3d11

#	endif // BGFX_CONFIG_VIDEO_DIRECT3D11

#endif // BGFX_CONFIG_RENDERER_DIRECT3D11
