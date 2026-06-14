/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_VULKAN
#	include "renderer_vk.h"
#	include "video_vk.h"

#	if BGFX_CONFIG_VIDEO_VULKAN
#		include "video_vk.h"
#		include "video.h"

namespace bgfx { namespace vk
{
	struct RendererContextVK;

	bool videoIsExtensionSupported(RendererContextVK* _renderer, const char* _name);
	void initVideoDecoder(RendererContextVK* _renderer, const VideoBindingVK& _binding);
	int32_t videoSelectMemoryType(RendererContextVK* _renderer, uint32_t _typeBits, uint32_t _flags);
	VkPipeline videoGetPipeline(RendererContextVK* _renderer, ProgramHandle _handle);
	const ProgramVK& videoGetProgram(RendererContextVK* _renderer, ProgramHandle _handle);
	VkCommandBuffer videoGetCommandBuffer(RendererContextVK* _renderer);
	VkSampler videoGetSampler(RendererContextVK* _renderer, uint64_t _samplerFlags, VkFormat _format);
	void videoRelease(RendererContextVK* _renderer, VkImageView& _obj);

	static VideoBindingVK s_videoVK;

	static StdVideoH264LevelIdc translateH264Level(int32_t _levelIdc)
	{
		switch (_levelIdc)
		{
		case 10: return STD_VIDEO_H264_LEVEL_IDC_1_0;
		case 11: return STD_VIDEO_H264_LEVEL_IDC_1_1;
		case 12: return STD_VIDEO_H264_LEVEL_IDC_1_2;
		case 13: return STD_VIDEO_H264_LEVEL_IDC_1_3;
		case 20: return STD_VIDEO_H264_LEVEL_IDC_2_0;
		case 21: return STD_VIDEO_H264_LEVEL_IDC_2_1;
		case 22: return STD_VIDEO_H264_LEVEL_IDC_2_2;
		case 30: return STD_VIDEO_H264_LEVEL_IDC_3_0;
		case 31: return STD_VIDEO_H264_LEVEL_IDC_3_1;
		case 32: return STD_VIDEO_H264_LEVEL_IDC_3_2;
		case 40: return STD_VIDEO_H264_LEVEL_IDC_4_0;
		case 41: return STD_VIDEO_H264_LEVEL_IDC_4_1;
		case 42: return STD_VIDEO_H264_LEVEL_IDC_4_2;
		case 50: return STD_VIDEO_H264_LEVEL_IDC_5_0;
		case 51: return STD_VIDEO_H264_LEVEL_IDC_5_1;
		case 52: return STD_VIDEO_H264_LEVEL_IDC_5_2;
		case 60: return STD_VIDEO_H264_LEVEL_IDC_6_0;
		case 61: return STD_VIDEO_H264_LEVEL_IDC_6_1;
		case 62: return STD_VIDEO_H264_LEVEL_IDC_6_2;
		default: break;
		}

		return STD_VIDEO_H264_LEVEL_IDC_4_0;
	}

	struct VideoDecoderVK
	{
		static constexpr uint32_t kNumDpbSlots           = 32;
		static constexpr uint32_t kMaxSessionMemory      = 8;
		static constexpr uint32_t kCopyRingSize          = 16;
		static constexpr uint32_t kYuvDescriptorRingSize = 4;

		struct ReorderedPicture
		{
			ReorderedPicture()
				: image(VK_NULL_HANDLE)
				, memory(VK_NULL_HANDLE)
				, yView(VK_NULL_HANDLE)
				, cbcrView(VK_NULL_HANDLE)
				, layout(VK_IMAGE_LAYOUT_UNDEFINED)
				, ptsUs(0)
				, displayOrder(-1)
			{
			}

			VkImage        image;
			VkDeviceMemory memory;
			VkImageView    yView;
			VkImageView    cbcrView;
			VkImageLayout  layout;
			int64_t        ptsUs;
			int32_t        displayOrder;
		};

		VideoDecoderVK()
			: m_created(false)
			, m_dstWidth(0)
			, m_dstHeight(0)
			, m_codedWidth(0)
			, m_codedHeight(0)
			, m_numDpbSlots(kNumDpbSlots)
			, m_nextSlot(0)
			, m_currentSlot(0)
			, m_numActiveRefs(0)
			, m_prevPocLsb(0)
			, m_prevPocMsb(0)
			, m_displayOrderNext(0)
			, m_displayedSlot(-1)
			, m_prevDisplayedSlot(-1)
			, m_initFlags(0)
			, m_cachedAuBytes(0)
			, m_renderer(NULL)
			, m_videoSession(VK_NULL_HANDLE)
			, m_sessionParams(VK_NULL_HANDLE)
			, m_numSessionMemory(0)
			, m_maxActiveRefs(0)
			, m_dpbCoincide(false)
			, m_decodeOutputImage(VK_NULL_HANDLE)
			, m_decodeOutputImageMemory(VK_NULL_HANDLE)
			, m_decodeOutputImageView(VK_NULL_HANDLE)
			, m_decodeOutputLayout(VK_IMAGE_LAYOUT_UNDEFINED)
			, m_bitstreamBuffer(VK_NULL_HANDLE)
			, m_bitstreamBufferMemory(VK_NULL_HANDLE)
			, m_bitstreamBufferSize(0)
			, m_bitstreamMapped(NULL)
			, m_bitstreamAlignment(1)
			, m_videoCommandPool(VK_NULL_HANDLE)
			, m_videoCommandBuffer(VK_NULL_HANDLE)
			, m_videoFence(VK_NULL_HANDLE)
			, m_copyCommandPool(VK_NULL_HANDLE)
			, m_copyControl(kCopyRingSize)
			, m_lastCopyRingIdx(0)
			, m_haveCopyInFlight(false)
			, m_yuvDescriptorPool(VK_NULL_HANDLE)
			, m_yuvDescriptorIndex(0)
			, m_firstDecode(true)
		{
			bx::memSet(m_referenceUsage, 0, sizeof(m_referenceUsage) );
			bx::memSet(&m_spsActive, 0, sizeof(m_spsActive) );
			bx::memSet(m_spsArray, 0, sizeof(m_spsArray) );
			bx::memSet(m_ppsArray, 0, sizeof(m_ppsArray) );
			bx::memSet(m_spsValid, 0, sizeof(m_spsValid) );
			bx::memSet(m_ppsValid, 0, sizeof(m_ppsValid) );
			bx::memSet(m_sessionMemory, 0, sizeof(m_sessionMemory) );
			bx::memSet(&m_h264Profile, 0, sizeof(m_h264Profile) );
			bx::memSet(&m_videoProfile, 0, sizeof(m_videoProfile) );
			bx::memSet(m_pocStatus, 0, sizeof(m_pocStatus) );
			bx::memSet(m_frameNumStatus, 0, sizeof(m_frameNumStatus) );
			bx::memSet(&m_codedExtent, 0, sizeof(m_codedExtent) );
			bx::memSet(&m_stdHeaderVersion, 0, sizeof(m_stdHeaderVersion) );
			bx::memSet(m_yuvDescriptorSet, 0, sizeof(m_yuvDescriptorSet) );
			bx::memSet(m_copyCommandBufferRing, 0, sizeof(m_copyCommandBufferRing) );
			bx::memSet(m_copyFenceRing, 0, sizeof(m_copyFenceRing) );
			bx::memSet(m_videoSemaphoreRing, 0, sizeof(m_videoSemaphoreRing) );

			m_dpbImage       = VK_NULL_HANDLE;
			m_dpbImageMemory = VK_NULL_HANDLE;
			bx::memSet(m_dpbImageView,   0, sizeof(m_dpbImageView) );

			for (uint32_t ii = 0; ii < kNumDpbSlots; ++ii)
			{
				m_dpbLayouts[ii] = VK_IMAGE_LAYOUT_UNDEFINED;
			}

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				m_reorderPool[ii].displayOrder = -1;
				m_reorderPool[ii].ptsUs = 0;
			}
		}

		bool create(const VideoDecoderInit& _init, RendererContextVK* _renderer, uint16_t _width, uint16_t _height)
		{
			m_renderer      = _renderer;
			m_initFlags     = _init.flags;
			m_cachedAuBytes = (0 != _init.cachedAuBytes) ? _init.cachedAuBytes : (4u << 20);

			m_auQueue.configure(m_cachedAuBytes, 0 != (m_initFlags & BGFX_VIDEO_DECODER_INIT_RETAIN) );

			if (VideoCodec::H264 != _init.codec)
			{
				BX_TRACE("VideoDecoderVK: codec %d not yet supported.", _init.codec);
				return false;
			}

			if (NULL == _init.parameterSets || 0 == _init.parameterSetsSize)
			{
				BX_TRACE("VideoDecoderVK: empty H.264 parameter sets.");
				return false;
			}

			if (NULL       == vkCmdBeginVideoCodingKHR
			||  NULL       == vkCmdDecodeVideoKHR
			||  NULL       == vkCreateVideoSessionKHR
			||  UINT32_MAX == s_videoVK.videoDecodeQueueFamily
			   )
			{
				BX_TRACE("VideoDecoderVK: VK_KHR_video decode entry points/queue are unavailable.");
				return false;
			}

			h264::PPS ppsActive = {};
			if (!bgfx::parseParameterSets(
				  m_spsArray
				, BX_COUNTOF(m_spsArray)
				, m_ppsArray
				, BX_COUNTOF(m_ppsArray)
				, m_spsActive
				, ppsActive
				, _init.parameterSets
				, _init.parameterSetsSize
				, m_spsValid
				, m_ppsValid
				) )
			{
				BX_TRACE("VideoDecoderVK: failed to parse SPS/PPS.");
				return false;
			}

			if (0 != m_spsActive.bit_depth_luma_minus8
			||  0 != m_spsActive.bit_depth_chroma_minus8
			||  1 != m_spsActive.chroma_format_idc)
			{
				BX_TRACE("VideoDecoderVK: only 8-bit 4:2:0/NV12 H.264 is supported.");
				return false;
			}

			m_dstWidth = _width;
			m_dstHeight = _height;
			m_codedWidth = uint32_t(m_spsActive.pic_width_in_mbs_minus1 + 1) * 16;
			m_codedHeight = uint32_t(m_spsActive.pic_height_in_map_units_minus1 + 1) * 16 * (m_spsActive.frame_mbs_only_flag ? 1 : 2);
			m_numDpbSlots = bx::min<uint32_t>(bx::max<uint32_t>(uint32_t(m_spsActive.num_ref_frames) + 1, 2), kNumDpbSlots);

			VkDevice device = s_videoVK.device;
			const VkAllocationCallbacks* allocCb = s_videoVK.allocCb;

			m_h264Profile =
			{
				.sType         = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR,
				.pNext         = NULL,
				.stdProfileIdc = StdVideoH264ProfileIdc(m_spsActive.profile_idc),
				.pictureLayout = VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_PROGRESSIVE_KHR,
			};

			m_videoProfile =
			{
				.sType               = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR,
				.pNext               = &m_h264Profile,
				.videoCodecOperation = VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR,
				.chromaSubsampling   = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR,
				.lumaBitDepth        = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR,
				.chromaBitDepth      = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR,
			};

			VkVideoDecodeH264CapabilitiesKHR h264Caps
			{
				.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR,
				.pNext                  = NULL,
				.maxLevelIdc            = STD_VIDEO_H264_LEVEL_IDC_INVALID,
				.fieldOffsetGranularity = {},
			};

			VkVideoDecodeCapabilitiesKHR decodeCaps
			{
				.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR,
				.pNext = &h264Caps,
				.flags = 0,
			};

			VkVideoCapabilitiesKHR videoCaps
			{
				.sType                             = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR,
				.pNext                             = &decodeCaps,
				.flags                             = 0,
				.minBitstreamBufferOffsetAlignment = 0,
				.minBitstreamBufferSizeAlignment   = 0,
				.pictureAccessGranularity          = {},
				.minCodedExtent                    = {},
				.maxCodedExtent                    = {},
				.maxDpbSlots                       = 0,
				.maxActiveReferencePictures        = 0,
				.stdHeaderVersion                  = {},
			};
			VkResult result = vkGetPhysicalDeviceVideoCapabilitiesKHR(s_videoVK.physicalDevice, &m_videoProfile, &videoCaps);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkGetPhysicalDeviceVideoCapabilitiesKHR failed (%d).", result);
				return false;
			}

			m_maxActiveRefs = videoCaps.maxActiveReferencePictures;

			if (BGFX_PCI_ID_INTEL != s_videoVK.vendorId)
			{
				m_numDpbSlots = bx::min<uint32_t>(m_numDpbSlots, videoCaps.maxDpbSlots);
			}

			m_stdHeaderVersion = videoCaps.stdHeaderVersion;

			BX_TRACE(
				  "VideoDecoderVK: num_ref_frames=%u  m_numDpbSlots=%u  videoCaps.maxDpbSlots=%u  maxActiveRefs=%u"
				, uint32_t(m_spsActive.num_ref_frames)
				, m_numDpbSlots
				, videoCaps.maxDpbSlots
				, m_maxActiveRefs
				);

			const VkExtent2D granularity = videoCaps.pictureAccessGranularity;
			const uint32_t alignedW = (m_codedWidth  + granularity.width  - 1) / granularity.width  * granularity.width;
			const uint32_t alignedH = (m_codedHeight + granularity.height - 1) / granularity.height * granularity.height;

			VkVideoSessionCreateInfoKHR sessionCi
			{
				.sType                      = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR,
				.pNext                      = NULL,
				.queueFamilyIndex           = s_videoVK.videoDecodeQueueFamily,
				.flags                      = 0,
				.pVideoProfile              = &m_videoProfile,
				.pictureFormat              = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
				.maxCodedExtent             = { .width = alignedW, .height = alignedH },
				.referencePictureFormat     = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
				.maxDpbSlots                = m_numDpbSlots,
				.maxActiveReferencePictures = bx::min<uint32_t>(uint32_t(m_spsActive.num_ref_frames) * 2, m_maxActiveRefs),
				.pStdHeaderVersion          = &videoCaps.stdHeaderVersion,
			};
			result = vkCreateVideoSessionKHR(device, &sessionCi, allocCb, &m_videoSession);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkCreateVideoSessionKHR failed (%d).", result);
				return false;
			}

			uint32_t reqCount = 0;
			vkGetVideoSessionMemoryRequirementsKHR(device, m_videoSession, &reqCount, NULL);

			if (reqCount > kMaxSessionMemory)
			{
				BX_TRACE("VideoDecoderVK: too many session memory requirements (%u > %u).", reqCount, kMaxSessionMemory);
				destroy();
				return false;
			}

			VkVideoSessionMemoryRequirementsKHR reqs[kMaxSessionMemory] = {};

			for (uint32_t ii = 0; ii < reqCount; ++ii)
			{
				reqs[ii].sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
			}

			vkGetVideoSessionMemoryRequirementsKHR(device, m_videoSession, &reqCount, reqs);

			VkBindVideoSessionMemoryInfoKHR binds[kMaxSessionMemory] = {};

			for (uint32_t ii = 0; ii < reqCount; ++ii)
			{
				VkMemoryAllocateInfo ai
				{
					.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
					.pNext           = NULL,
					.allocationSize  = reqs[ii].memoryRequirements.size,
					.memoryTypeIndex = uint32_t(videoSelectMemoryType(m_renderer, reqs[ii].memoryRequirements.memoryTypeBits, 0) ),
				};

				result = vkAllocateMemory(device, &ai, allocCb, &m_sessionMemory[ii]);
				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateMemory[%u] failed (%d).", ii, result);
					destroy();
					return false;
				}

				m_numSessionMemory = ii + 1;

				binds[ii] =
				{
					.sType           = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR,
					.pNext           = NULL,
					.memoryBindIndex = reqs[ii].memoryBindIndex,
					.memory          = m_sessionMemory[ii],
					.memoryOffset    = 0,
					.memorySize      = ai.allocationSize,
				};
			}

			result = vkBindVideoSessionMemoryKHR(device, m_videoSession, reqCount, binds);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkBindVideoSessionMemoryKHR failed (%d).", result);
				destroy();
				return false;
			}

			if (!createSessionParameters() )
			{
				destroy();
				return false;
			}

			m_dpbCoincide = (decodeCaps.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR) != 0;
			m_codedExtent.width  = alignedW;
			m_codedExtent.height = alignedH;
			m_bitstreamAlignment = uint32_t(bx::max<VkDeviceSize>(videoCaps.minBitstreamBufferOffsetAlignment, videoCaps.minBitstreamBufferSizeAlignment) );

			if (0 == m_bitstreamAlignment)
			{
				m_bitstreamAlignment = 1;
			}

			VkVideoProfileListInfoKHR profileList
			{
				.sType        = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR,
				.pNext        = NULL,
				.profileCount = 1,
				.pProfiles    = &m_videoProfile,
			};

			const uint32_t videoSharedQueueFamilies[] =
			{
				s_videoVK.globalQueueFamily,
				s_videoVK.videoDecodeQueueFamily,
			};

			const bool isMultiQueue = s_videoVK.globalQueueFamily != s_videoVK.videoDecodeQueueFamily;
			const VkSharingMode videoSharingMode  = isMultiQueue ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
			const uint32_t videoSharedQueueCount  = isMultiQueue ? uint32_t(BX_COUNTOF(videoSharedQueueFamilies) ) : 0u;
			const uint32_t* videoSharedQueuePtr   = isMultiQueue ? videoSharedQueueFamilies : NULL;

			{
				const VkImageUsageFlags dpbUsage = m_dpbCoincide
					? VkImageUsageFlags(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR | VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR | VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
					: VkImageUsageFlags(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR)
					;

				VkImageCreateInfo ci
				{
					.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
					.pNext                 = &profileList,
					.flags                 = 0,
					.imageType             = VK_IMAGE_TYPE_2D,
					.format                = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
					.extent                = { alignedW, alignedH, 1 },
					.mipLevels             = 1,
					.arrayLayers           = m_numDpbSlots,
					.samples               = VK_SAMPLE_COUNT_1_BIT,
					.tiling                = VK_IMAGE_TILING_OPTIMAL,
					.usage                 = dpbUsage,
					.sharingMode           = m_dpbCoincide ? videoSharingMode    : VK_SHARING_MODE_EXCLUSIVE,
					.queueFamilyIndexCount = m_dpbCoincide ? videoSharedQueueCount : 0u,
					.pQueueFamilyIndices   = m_dpbCoincide ? videoSharedQueuePtr  : NULL,
					.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
				};
				result = vkCreateImage(device, &ci, allocCb, &m_dpbImage);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateImage(DPB) failed (%d).", result);
					destroy();
					return false;
				}

				VkMemoryRequirements req = {};
				vkGetImageMemoryRequirements(device, m_dpbImage, &req);

				VkMemoryAllocateInfo ai
				{
					.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
					.pNext           = NULL,
					.allocationSize  = req.size,
					.memoryTypeIndex = uint32_t(videoSelectMemoryType(m_renderer, req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) ),
				};
				result = vkAllocateMemory(device, &ai, allocCb, &m_dpbImageMemory);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateMemory(DPB) failed (%d).", result);
					destroy();
					return false;
				}

				vkBindImageMemory(device, m_dpbImage, m_dpbImageMemory, 0);

				for (uint32_t slot = 0; slot < m_numDpbSlots; ++slot)
				{
					VkImageViewUsageCreateInfo viewUsage
					{
						.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
						.pNext = NULL,
						.usage = m_dpbCoincide
							? VkImageUsageFlags(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR | VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR)
							: VkImageUsageFlags(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR),
					};

					VkImageViewCreateInfo vci
					{
						.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
						.pNext            = &viewUsage,
						.flags            = 0,
						.image            = m_dpbImage,
						.viewType         = VK_IMAGE_VIEW_TYPE_2D,
						.format           = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
						.components       = {},
						.subresourceRange =
						{
							.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel   = 0,
							.levelCount     = 1,
							.baseArrayLayer = slot,
							.layerCount     = 1,
						},
					};
					result = vkCreateImageView(device, &vci, allocCb, &m_dpbImageView[slot]);

					if (VK_SUCCESS != result)
					{
						BX_TRACE("VideoDecoderVK: vkCreateImageView(DPB[%u]) failed (%d).", slot, result);
						destroy();
						return false;
					}
				}
			}

			if (!m_dpbCoincide)
			{
				VkImageCreateInfo ci
				{
					.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
					.pNext                 = &profileList,
					.flags                 = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT,
					.imageType             = VK_IMAGE_TYPE_2D,
					.format                = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
					.extent                = { alignedW, alignedH, 1 },
					.mipLevels             = 1,
					.arrayLayers           = 1,
					.samples               = VK_SAMPLE_COUNT_1_BIT,
					.tiling                = VK_IMAGE_TILING_OPTIMAL,
					.usage                 = 0
						| VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR
						| VK_IMAGE_USAGE_TRANSFER_SRC_BIT
						,
					.sharingMode           = videoSharingMode,
					.queueFamilyIndexCount = videoSharedQueueCount,
					.pQueueFamilyIndices   = videoSharedQueuePtr,
					.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
				};
				result = vkCreateImage(device, &ci, allocCb, &m_decodeOutputImage);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateImage(decode-output) failed (%d).", result);
					destroy();
					return false;
				}

				VkMemoryRequirements req = {};
				vkGetImageMemoryRequirements(device, m_decodeOutputImage, &req);

				VkMemoryAllocateInfo ai
				{
					.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
					.pNext           = NULL,
					.allocationSize  = req.size,
					.memoryTypeIndex = uint32_t(videoSelectMemoryType(m_renderer, req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) ),
				};
				result = vkAllocateMemory(device, &ai, allocCb, &m_decodeOutputImageMemory);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateMemory(decode-output) failed (%d).", result);
					destroy();
					return false;
				}
				vkBindImageMemory(device, m_decodeOutputImage, m_decodeOutputImageMemory, 0);

				VkImageViewUsageCreateInfo viewUsage
				{
					.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_USAGE_CREATE_INFO,
					.pNext = NULL,
					.usage = VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR,
				};

				VkImageViewCreateInfo vci
				{
					.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
					.pNext            = &viewUsage,
					.flags            = 0,
					.image            = m_decodeOutputImage,
					.viewType         = VK_IMAGE_VIEW_TYPE_2D,
					.format           = ci.format,
					.components       = {},
					.subresourceRange =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = 1,
						.baseArrayLayer = 0,
						.layerCount     = 1,
					},
				};
				result = vkCreateImageView(device, &vci, allocCb, &m_decodeOutputImageView);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateImageView(decode-output) failed (%d).", result);
					destroy();
					return false;
				}
			}

			{
				const VkDeviceSize pixelFootprint = VkDeviceSize(m_codedWidth) * VkDeviceSize(m_codedHeight) * 3 / 2;
				m_bitstreamBufferSize = bx::max<VkDeviceSize>(4 * 1024 * 1024, pixelFootprint);
				m_bitstreamBufferSize = bx::alignUp<VkDeviceSize>(m_bitstreamBufferSize, bx::max<VkDeviceSize>(m_bitstreamAlignment, 1) );

				VkBufferCreateInfo bi
				{
					.sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
					.pNext                 = &profileList,
					.flags                 = 0,
					.size                  = m_bitstreamBufferSize,
					.usage                 = VK_BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR,
					.sharingMode           = VK_SHARING_MODE_EXCLUSIVE,
					.queueFamilyIndexCount = 0,
					.pQueueFamilyIndices   = NULL,
				};
				result = vkCreateBuffer(device, &bi, allocCb, &m_bitstreamBuffer);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateBuffer(bitstream) failed (%d).", result);
					destroy();
					return false;
				}

				VkMemoryRequirements req = {};
				vkGetBufferMemoryRequirements(device, m_bitstreamBuffer, &req);

				const int32_t typeIdx = videoSelectMemoryType(
					  m_renderer
					, req.memoryTypeBits
					, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
					);

				if (-1 == typeIdx)
				{
					BX_TRACE("VideoDecoderVK: no host-visible memory type for bitstream buffer.");
					destroy();
					return false;
				}

				VkMemoryAllocateInfo ai
				{
					.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
					.pNext           = NULL,
					.allocationSize  = req.size,
					.memoryTypeIndex = uint32_t(typeIdx),
				};
				result = vkAllocateMemory(device, &ai, allocCb, &m_bitstreamBufferMemory);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateMemory(bitstream) failed (%d).", result);
					destroy();
					return false;
				}

				vkBindBufferMemory(device, m_bitstreamBuffer, m_bitstreamBufferMemory, 0);
				result = vkMapMemory(
					  device
					, m_bitstreamBufferMemory
					, 0
					, m_bitstreamBufferSize
					, 0
					, &m_bitstreamMapped
					);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkMapMemory(bitstream) failed (%d).", result);
					destroy();
					return false;
				}
			}

			{
				VkCommandPoolCreateInfo pci
				{
					.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.pNext            = NULL,
					.flags            = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
					.queueFamilyIndex = s_videoVK.videoDecodeQueueFamily,
				};
				result = vkCreateCommandPool(device, &pci, allocCb, &m_videoCommandPool);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateCommandPool(video) failed (%d).", result);
					destroy();
					return false;
				}

				VkCommandBufferAllocateInfo cbi
				{
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					.pNext              = NULL,
					.commandPool        = m_videoCommandPool,
					.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
					.commandBufferCount = 1,
				};
				result = vkAllocateCommandBuffers(device, &cbi, &m_videoCommandBuffer);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateCommandBuffers(video) failed (%d).", result);
					destroy();
					return false;
				}

				VkFenceCreateInfo fci
				{
					.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
					.pNext = NULL,
					.flags = VK_FENCE_CREATE_SIGNALED_BIT,
				};
				result = vkCreateFence(device, &fci, allocCb, &m_videoFence);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateFence(video) failed (%d).", result);
					destroy();
					return false;
				}
			}

			{
				VkCommandPoolCreateInfo pci
				{
					.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.pNext            = NULL,
					.flags            = 0
						| VK_COMMAND_POOL_CREATE_TRANSIENT_BIT
						| VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
						,
					.queueFamilyIndex = s_videoVK.globalQueueFamily,
				};
				result = vkCreateCommandPool(device, &pci, allocCb, &m_copyCommandPool);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateCommandPool(copy) failed (%d).", result);
					destroy();
					return false;
				}

				VkCommandBufferAllocateInfo cbi
				{
					.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
					.pNext              = NULL,
					.commandPool        = m_copyCommandPool,
					.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
					.commandBufferCount = kCopyRingSize,
				};
				result = vkAllocateCommandBuffers(device, &cbi, m_copyCommandBufferRing);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateCommandBuffers(copy ring) failed (%d).", result);
					destroy();
					return false;
				}

				VkFenceCreateInfo cfci
				{
					.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
					.pNext = NULL,
					.flags = VK_FENCE_CREATE_SIGNALED_BIT,
				};

				for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
				{
					result = vkCreateFence(device, &cfci, allocCb, &m_copyFenceRing[ii]);

					if (VK_SUCCESS != result)
					{
						BX_TRACE("VideoDecoderVK: vkCreateFence(copy ring) failed (%d).", result);
						destroy();
						return false;
					}
				}

				VkSemaphoreCreateInfo sci
				{
					.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
					.pNext = NULL,
					.flags = 0,
				};

				for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
				{
					result = vkCreateSemaphore(device, &sci, allocCb, &m_videoSemaphoreRing[ii]);

					if (VK_SUCCESS != result)
					{
						BX_TRACE("VideoDecoderVK: vkCreateSemaphore(video ring) failed (%d).", result);
						destroy();
						return false;
					}
				}

				m_copyControl.reset();
			}

			m_firstDecode = true;
			m_created = true;

			BX_TRACE(
				  "VideoDecoderVK: H.264 session ready, coded %ux%u, dst %ux%u, %u DPB slots, coincide=%d."
				, m_codedWidth
				, m_codedHeight
				, m_dstWidth
				, m_dstHeight
				, m_numDpbSlots
				, m_dpbCoincide ? 1 : 0
				);

			return true;
		}

		void destroy()
		{
			VkDevice device = s_videoVK.device;
			const VkAllocationCallbacks* allocCb = s_videoVK.allocCb;

			vkDeviceWaitIdle(device);

			if (VK_NULL_HANDLE != m_videoFence)
			{
				vkWaitForFences(device, 1, &m_videoFence, VK_TRUE, UINT64_MAX);
				vkDestroyFence(device, m_videoFence, allocCb);
				m_videoFence = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_videoCommandPool)
			{
				vkDestroyCommandPool(device, m_videoCommandPool, allocCb);
				m_videoCommandPool   = VK_NULL_HANDLE;
				m_videoCommandBuffer = VK_NULL_HANDLE;
			}

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				if (VK_NULL_HANDLE != m_copyFenceRing[ii])
				{
					vkWaitForFences(device, 1, &m_copyFenceRing[ii], VK_TRUE, UINT64_MAX);
					vkDestroyFence(device, m_copyFenceRing[ii], allocCb);
					m_copyFenceRing[ii] = VK_NULL_HANDLE;
				}
			}

			for (uint32_t ii = 0; ii < kCopyRingSize; ++ii)
			{
				if (VK_NULL_HANDLE != m_videoSemaphoreRing[ii])
				{
					vkDestroySemaphore(device, m_videoSemaphoreRing[ii], allocCb);
					m_videoSemaphoreRing[ii] = VK_NULL_HANDLE;
				}
			}

			if (VK_NULL_HANDLE != m_copyCommandPool)
			{
				vkDestroyCommandPool(device, m_copyCommandPool, allocCb);
				m_copyCommandPool = VK_NULL_HANDLE;
				bx::memSet(m_copyCommandBufferRing, 0, sizeof(m_copyCommandBufferRing) );
			}

			if (VK_NULL_HANDLE != m_yuvDescriptorPool)
			{
				vkDestroyDescriptorPool(device, m_yuvDescriptorPool, allocCb);
				m_yuvDescriptorPool = VK_NULL_HANDLE;
				bx::memSet(m_yuvDescriptorSet, 0, sizeof(m_yuvDescriptorSet) );
				m_yuvDescriptorIndex = 0;
			}

			if (VK_NULL_HANDLE != m_bitstreamBufferMemory)
			{
				if (NULL != m_bitstreamMapped)
				{
					vkUnmapMemory(device, m_bitstreamBufferMemory);
					m_bitstreamMapped = NULL;
				}
			}

			if (VK_NULL_HANDLE != m_bitstreamBuffer)
			{
				vkDestroyBuffer(device, m_bitstreamBuffer, allocCb);
				m_bitstreamBuffer = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_bitstreamBufferMemory)
			{
				vkFreeMemory(device, m_bitstreamBufferMemory, allocCb);
				m_bitstreamBufferMemory = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_decodeOutputImageView)
			{
				vkDestroyImageView(device, m_decodeOutputImageView, allocCb);
				m_decodeOutputImageView = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_decodeOutputImage)
			{
				vkDestroyImage(device, m_decodeOutputImage, allocCb);
				m_decodeOutputImage = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_decodeOutputImageMemory)
			{
				vkFreeMemory(device, m_decodeOutputImageMemory, allocCb);
				m_decodeOutputImageMemory = VK_NULL_HANDLE;
			}

			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				ReorderedPicture& pic = m_reorderPool[ii];

				if (VK_NULL_HANDLE != pic.yView)
				{
					vkDestroyImageView(device, pic.yView, allocCb);
					pic.yView = VK_NULL_HANDLE;
				}

				if (VK_NULL_HANDLE != pic.cbcrView)
				{
					vkDestroyImageView(device, pic.cbcrView, allocCb);
					pic.cbcrView = VK_NULL_HANDLE;
				}

				if (VK_NULL_HANDLE != pic.image)
				{
					vkDestroyImage(device, pic.image, allocCb);
					pic.image = VK_NULL_HANDLE;
				}

				if (VK_NULL_HANDLE != pic.memory)
				{
					vkFreeMemory(device, pic.memory, allocCb);
					pic.memory = VK_NULL_HANDLE;
				}

				pic.layout = VK_IMAGE_LAYOUT_UNDEFINED;
			}

			for (uint32_t ii = 0; ii < kNumDpbSlots; ++ii)
			{
				if (VK_NULL_HANDLE != m_dpbImageView[ii])
				{
					vkDestroyImageView(device, m_dpbImageView[ii], allocCb);
					m_dpbImageView[ii] = VK_NULL_HANDLE;
				}
			}

			if (VK_NULL_HANDLE != m_dpbImage)
			{
				vkDestroyImage(device, m_dpbImage, allocCb);
				m_dpbImage = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_dpbImageMemory)
			{
				vkFreeMemory(device, m_dpbImageMemory, allocCb);
				m_dpbImageMemory = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_sessionParams)
			{
				vkDestroyVideoSessionParametersKHR(device, m_sessionParams, allocCb);
				m_sessionParams = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_videoSession)
			{
				vkDestroyVideoSessionKHR(device, m_videoSession, allocCb);
				m_videoSession = VK_NULL_HANDLE;
			}

			for (uint32_t ii = 0; ii < m_numSessionMemory; ++ii)
			{
				if (VK_NULL_HANDLE != m_sessionMemory[ii])
				{
					vkFreeMemory(device, m_sessionMemory[ii], allocCb);
					m_sessionMemory[ii] = VK_NULL_HANDLE;
				}
			}

			m_numSessionMemory = 0;

			for (uint32_t ii = 0; ii < kNumDpbSlots; ++ii)
			{
				m_dpbLayouts[ii] = VK_IMAGE_LAYOUT_UNDEFINED;
				m_pocStatus[ii]  = 0;
				m_frameNumStatus[ii] = 0;
			}

			m_decodeOutputLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			m_firstDecode = true;
			m_haveCopyInFlight = false;
			m_lastCopyRingIdx  = 0;

			m_created = false;
			resetReorder();
		}

		bool decode(const VideoDecoderFrame& _frame, TextureVK& _dst)
		{
			if (!m_created)
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
				&&  m_auQueue.minPts() < m_auQueue.maxPts()
				   )
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
			bx::memSet(m_pocStatus,      0, sizeof(m_pocStatus) );
			bx::memSet(m_frameNumStatus, 0, sizeof(m_frameNumStatus) );

			m_prevPocLsb  = 0;
			m_prevPocMsb  = 0;
			m_firstDecode = true;

			for (uint32_t ii = 0; ii < kNumDpbSlots; ++ii)
			{
				m_dpbLayouts[ii] = VK_IMAGE_LAYOUT_UNDEFINED;
			}
			m_decodeOutputLayout = VK_IMAGE_LAYOUT_UNDEFINED;

			if (BGFX_PCI_ID_INTEL == s_videoVK.vendorId)
			{
				recreateVideoSession();
			}
		}

		void recreateVideoSession()
		{
			VkDevice                     device = s_videoVK.device;
			const VkAllocationCallbacks* allocCb = s_videoVK.allocCb;

			vkQueueWaitIdle(s_videoVK.videoDecodeQueue);
			vkQueueWaitIdle(s_videoVK.globalQueue);

			if (VK_NULL_HANDLE != m_sessionParams)
			{
				vkDestroyVideoSessionParametersKHR(device, m_sessionParams, allocCb);
				m_sessionParams = VK_NULL_HANDLE;
			}

			if (VK_NULL_HANDLE != m_videoSession)
			{
				vkDestroyVideoSessionKHR(device, m_videoSession, allocCb);
				m_videoSession = VK_NULL_HANDLE;
			}

			for (uint32_t ii = 0; ii < m_numSessionMemory; ++ii)
			{
				if (VK_NULL_HANDLE != m_sessionMemory[ii])
				{
					vkFreeMemory(device, m_sessionMemory[ii], allocCb);
					m_sessionMemory[ii] = VK_NULL_HANDLE;
				}
			}
			m_numSessionMemory = 0;

			VkVideoSessionCreateInfoKHR sessionCi
			{
				.sType                      = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR,
				.pNext                      = NULL,
				.queueFamilyIndex           = s_videoVK.videoDecodeQueueFamily,
				.flags                      = 0,
				.pVideoProfile              = &m_videoProfile,
				.pictureFormat              = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
				.maxCodedExtent             = m_codedExtent,
				.referencePictureFormat     = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
				.maxDpbSlots                = m_numDpbSlots,
				.maxActiveReferencePictures = bx::min<uint32_t>(uint32_t(m_spsActive.num_ref_frames) * 2, m_maxActiveRefs),
				.pStdHeaderVersion          = &m_stdHeaderVersion,
			};

			VkResult result = vkCreateVideoSessionKHR(device, &sessionCi, allocCb, &m_videoSession);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: recreateVideoSession vkCreateVideoSessionKHR failed (%d).", result);
				return;
			}

			uint32_t reqCount = 0;
			vkGetVideoSessionMemoryRequirementsKHR(device, m_videoSession, &reqCount, NULL);

			VkVideoSessionMemoryRequirementsKHR reqs[kMaxSessionMemory] = {};

			for (uint32_t ii = 0; ii < reqCount; ++ii)
			{
				reqs[ii].sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
			}

			vkGetVideoSessionMemoryRequirementsKHR(device, m_videoSession, &reqCount, reqs);

			VkBindVideoSessionMemoryInfoKHR binds[kMaxSessionMemory] = {};

			for (uint32_t ii = 0; ii < reqCount; ++ii)
			{
				VkMemoryAllocateInfo ai
				{
					.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
					.pNext           = NULL,
					.allocationSize  = reqs[ii].memoryRequirements.size,
					.memoryTypeIndex = uint32_t(videoSelectMemoryType(m_renderer, reqs[ii].memoryRequirements.memoryTypeBits, 0) ),
				};
				vkAllocateMemory(device, &ai, allocCb, &m_sessionMemory[ii]);
				m_numSessionMemory = ii + 1;

				binds[ii] =
				{
					.sType           = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR,
					.pNext           = NULL,
					.memoryBindIndex = reqs[ii].memoryBindIndex,
					.memory          = m_sessionMemory[ii],
					.memoryOffset    = 0,
					.memorySize      = ai.allocationSize,
				};
			}

			if (reqCount > 0)
			{
				vkBindVideoSessionMemoryKHR(device, m_videoSession, reqCount, binds);
			}

			createSessionParameters();
		}

		void pickDisplaySlotForTime(int64_t _presentationTimeUs, TextureVK& _dst)
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
				  }
				);
		}

		bool decodeOneAU(const uint8_t* _bitstream, uint32_t _bitstreamSize, int64_t _ptsUs)
		{
			if (NULL == _bitstream
			||     0 == _bitstreamSize)
			{
				return false;
			}

			h264::NALHeader  nal = {};
			h264::SliceHeader sh = {};
			bool isIdr = false;
			if (!bgfx::parseSliceFromAccessUnit(m_spsArray, m_ppsArray, _bitstream, _bitstreamSize, nal, sh, isIdr) )
			{
				return false;
			}

			const h264::PPS& pps = m_ppsArray[sh.pic_parameter_set_id];
			const h264::SPS& sps = m_spsArray[pps.seq_parameter_set_id];
			const int32_t poc = bgfx::computePoc(m_prevPocMsb, m_prevPocLsb, sps, sh, nal, isIdr);

			if (isIdr)
			{
				m_numActiveRefs = 0;

				m_nextSlot = 0;

				if (BGFX_PCI_ID_INTEL == s_videoVK.vendorId)
				{
					recreateVideoSession();
					m_firstDecode = true;
				}
			}

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

			const uint32_t slot = bgfx::pickReorderSlotOrEvictOldest(m_reorderPool, kVideoMaxReorderInFlight);
			m_reorderPool[slot].displayOrder = m_displayOrderNext++;
			m_reorderPool[slot].ptsUs = _ptsUs;

			const bool isIntra = false
				|| isIdr
				|| sh.slice_type == 2
				|| sh.slice_type == 4
				|| sh.slice_type == 7
				|| sh.slice_type == 9
				;
			const bool isReference = (0 != nal.idc);

			m_pocStatus[m_currentSlot]      = poc;
			m_frameNumStatus[m_currentSlot] = int32_t(sh.frame_num);

			const uint32_t sliceOffsetInAu     = bgfx::findFirstSliceNalOffset(_bitstream, _bitstreamSize);
			const uint8_t* sliceBitstream      = _bitstream + sliceOffsetInAu;
			const uint32_t sliceBitstreamSize  = _bitstreamSize - sliceOffsetInAu;

			const VkDeviceSize alignedSize = bx::alignUp<VkDeviceSize>(sliceBitstreamSize, m_bitstreamAlignment);
			if (alignedSize > m_bitstreamBufferSize)
			{
				BX_TRACE("VideoDecoderVK: bitstream %u exceeds buffer %u; skipping frame.",
				uint32_t(alignedSize), uint32_t(m_bitstreamBufferSize) );
				return false;
			}

			VkDevice device = s_videoVK.device;

			vkWaitForFences(device, 1, &m_videoFence, VK_TRUE, UINT64_MAX);
			vkResetFences(device, 1, &m_videoFence);
			vkResetCommandPool(device, m_videoCommandPool, 0);

			if (m_haveCopyInFlight)
			{
				vkWaitForFences(device, 1, &m_copyFenceRing[m_lastCopyRingIdx], VK_TRUE, UINT64_MAX);
				m_haveCopyInFlight = false;
			}

			bx::memCopy(m_bitstreamMapped, sliceBitstream, sliceBitstreamSize);

			if (alignedSize > sliceBitstreamSize)
			{
				bx::memSet(
					  (uint8_t*)m_bitstreamMapped + sliceBitstreamSize
					, 0
					, size_t(alignedSize - sliceBitstreamSize)
					);
			}

			{
				VkMappedMemoryRange range
				{
					.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
					.pNext  = NULL,
					.memory = m_bitstreamBufferMemory,
					.offset = 0,
					.size   = VK_WHOLE_SIZE,
				};

				vkFlushMappedMemoryRanges(device, 1, &range);
			}

			while (0 == m_copyControl.reserve(1) )
			{
				const uint32_t readIdx = m_copyControl.m_read;
				const VkResult wres = vkWaitForFences(
					  device
					, 1
					, &m_copyFenceRing[readIdx]
					, VK_TRUE
					, UINT64_MAX
					);

				if (VK_SUCCESS != wres)
				{
					BX_TRACE("VideoDecoderVK: vkWaitForFences(copy ring) failed (%d).", wres);
					return false;
				}

				m_copyControl.consume(1);
			}

			const uint32_t ringIdx = m_copyControl.m_current;
			VkCommandBuffer gfx       = m_copyCommandBufferRing[ringIdx];
			VkFence         copyFence = m_copyFenceRing[ringIdx];
			vkResetFences(device, 1, &copyFence);

			VkCommandBufferBeginInfo cbBegin
			{
				.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
				.pNext            = NULL,
				.flags            = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
				.pInheritanceInfo = NULL,
			};
			vkBeginCommandBuffer(m_videoCommandBuffer, &cbBegin);

			if (m_firstDecode)
			{
				VkImageMemoryBarrier barrier =
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = 0,
					.dstAccessMask       = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
					.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED,
					.newLayout           = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = m_dpbImage,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = VK_REMAINING_MIP_LEVELS,
						.baseArrayLayer = 0,
						.layerCount     = m_numDpbSlots,
					},
				};

				vkCmdPipelineBarrier(
					  m_videoCommandBuffer
					, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
					, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
					, 0
					, 0
					, NULL
					, 0
					, NULL
					, 1
					, &barrier
					);

				for (uint32_t ii = 0; ii < kNumDpbSlots; ++ii)
				{
					m_dpbLayouts[ii] = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
				}
			}

			if (m_dpbCoincide)
			{
				VkImageMemoryBarrier dpbBarriers[kNumDpbSlots];
				uint32_t numDpbBarriers = 0;

				const auto pushDpbBarrier = [&](uint32_t _slot)
				{
					if (VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR == m_dpbLayouts[_slot])
					{
						return;
					}
					dpbBarriers[numDpbBarriers] =
					{
						.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
						.pNext               = NULL,
						.srcAccessMask       = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
						.dstAccessMask       = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
						.oldLayout           = m_dpbLayouts[_slot],
						.newLayout           = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR,
						.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
						.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
						.image               = m_dpbImage,
						.subresourceRange    =
						{
							.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
							.baseMipLevel   = 0,
							.levelCount     = 1,
							.baseArrayLayer = _slot,
							.layerCount     = 1,
						},
					};
					m_dpbLayouts[_slot] = VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR;
					++numDpbBarriers;
				};

				pushDpbBarrier(m_currentSlot);
				for (uint32_t ii = 0; ii < m_numActiveRefs; ++ii)
				{
					pushDpbBarrier(m_referenceUsage[ii]);
				}

				if (0 != numDpbBarriers)
				{
					vkCmdPipelineBarrier(
						  m_videoCommandBuffer
						, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
						, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
						, 0
						, 0
						, NULL
						, 0
						, NULL
						, numDpbBarriers
						, dpbBarriers
						);
				}
			}

			if (!m_dpbCoincide)
			{
				VkImageMemoryBarrier barrier
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = VK_ACCESS_MEMORY_READ_BIT,
					.dstAccessMask       = VK_ACCESS_MEMORY_WRITE_BIT,
					.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED,
					.newLayout           = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = m_decodeOutputImage,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = VK_REMAINING_MIP_LEVELS,
						.baseArrayLayer = 0,
						.layerCount     = VK_REMAINING_ARRAY_LAYERS,
					},
				};

				vkCmdPipelineBarrier(
					  m_videoCommandBuffer
					, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
					, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
					, 0
					, 0
					, NULL
					, 0
					, NULL
					, 1
					, &barrier
					);

				m_decodeOutputLayout = VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR;
			}

			StdVideoDecodeH264PictureInfo stdPic
			{
				.flags =
				{
					.field_pic_flag           = uint32_t(sh.field_pic_flag),
					.is_intra                 = isIntra ? 1u : 0u,
					.IdrPicFlag               = isIdr ? 1u : 0u,
					.bottom_field_flag        = uint32_t(sh.bottom_field_flag),
					.is_reference             = isReference ? 1u : 0u,
					.complementary_field_pair = 0,
				},

				.seq_parameter_set_id = uint8_t(pps.seq_parameter_set_id),
				.pic_parameter_set_id = uint8_t(sh.pic_parameter_set_id),
				.reserved1            = 0,
				.reserved2            = 0,
				.frame_num            = uint16_t(sh.frame_num),
				.idr_pic_id           = uint16_t(sh.idr_pic_id),
				.PicOrderCnt          = { poc, poc },
			};

			VkVideoReferenceSlotInfoKHR     slotInfos[kNumDpbSlots]   = {};
			VkVideoPictureResourceInfoKHR   slotPics[kNumDpbSlots]    = {};
			VkVideoDecodeH264DpbSlotInfoKHR slotDpbH264[kNumDpbSlots] = {};
			StdVideoDecodeH264ReferenceInfo slotRef[kNumDpbSlots]     = {};

			for (uint32_t ii = 0; ii < m_numDpbSlots; ++ii)
			{
				slotPics[ii] =
				{
					.sType            = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR,
					.pNext            = NULL,
					.codedOffset      = {},
					.codedExtent      = m_codedExtent,
					.baseArrayLayer   = 0,
					.imageViewBinding = m_dpbImageView[ii],
				};

				slotRef[ii].FrameNum       = uint16_t(m_frameNumStatus[ii]);
				slotRef[ii].PicOrderCnt[0] = m_pocStatus[ii];
				slotRef[ii].PicOrderCnt[1] = m_pocStatus[ii];

				slotDpbH264[ii] =
				{
					.sType             = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_DPB_SLOT_INFO_KHR,
					.pNext             = NULL,
					.pStdReferenceInfo = &slotRef[ii],
				};

				slotInfos[ii] =
				{
					.sType            = VK_STRUCTURE_TYPE_VIDEO_REFERENCE_SLOT_INFO_KHR,
					.pNext            = &slotDpbH264[ii],
					.slotIndex        = int32_t(ii),
					.pPictureResource = &slotPics[ii],
				};
			}

			VkVideoReferenceSlotInfoKHR beginSlots[kNumDpbSlots] = {};
			uint32_t numActiveRefs = 0;

			for (uint32_t ii = 0; ii < m_numActiveRefs; ++ii)
			{
				const uint32_t refSlot = m_referenceUsage[ii];
				BX_ASSERT(refSlot != m_currentSlot, "Current slot must not be in reference list yet.");
				beginSlots[numActiveRefs++] = slotInfos[refSlot];
			}

			beginSlots[numActiveRefs] = slotInfos[m_currentSlot];
			beginSlots[numActiveRefs].slotIndex = -1;

			const uint32_t totalBeginSlots = numActiveRefs + 1;

			VkVideoBeginCodingInfoKHR beginInfo
			{
				.sType                  = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR,
				.pNext                  = NULL,
				.flags                  = 0,
				.videoSession           = m_videoSession,
				.videoSessionParameters = m_sessionParams,
				.referenceSlotCount     = totalBeginSlots,
				.pReferenceSlots        = beginSlots,
			};
			vkCmdBeginVideoCodingKHR(m_videoCommandBuffer, &beginInfo);

			const bool needsControlReset = false
				|| m_firstDecode
				|| (isIdr && BGFX_PCI_ID_INTEL == s_videoVK.vendorId)
				;

			if (needsControlReset)
			{
				VkVideoCodingControlInfoKHR control
				{
					.sType = VK_STRUCTURE_TYPE_VIDEO_CODING_CONTROL_INFO_KHR,
					.pNext = NULL,
					.flags = VK_VIDEO_CODING_CONTROL_RESET_BIT_KHR,
				};
				vkCmdControlVideoCodingKHR(m_videoCommandBuffer, &control);
			}

			uint32_t sliceOffsets[bgfx::kMaxSlicesPerPicture];
			const uint32_t sliceCount = bgfx::enumerateSliceNalOffsets(
				  sliceBitstream
				, sliceBitstreamSize
				, sliceOffsets
				, BX_COUNTOF(sliceOffsets)
				);

			if (0 == sliceCount
			||  sliceCount > BX_COUNTOF(sliceOffsets) )
			{
				BX_TRACE(
					  "VideoDecoderVK: invalid slice enumeration count=%u (max=%u)."
					, sliceCount
					, uint32_t(BX_COUNTOF(sliceOffsets) )
					);

				return false;
			}

			VkVideoDecodeH264PictureInfoKHR pictureInfoH264
			{
				.sType           = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PICTURE_INFO_KHR,
				.pNext           = NULL,
				.pStdPictureInfo = &stdPic,
				.sliceCount      = sliceCount,
				.pSliceOffsets   = sliceOffsets,
			};

			VkVideoDecodeInfoKHR decodeInfo
			{
				.sType             = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR,
				.pNext             = &pictureInfoH264,
				.flags             = 0,
				.srcBuffer         = m_bitstreamBuffer,
				.srcBufferOffset   = 0,
				.srcBufferRange    = alignedSize,
				.dstPictureResource = m_dpbCoincide
					? slotPics[m_currentSlot]
					: VkVideoPictureResourceInfoKHR
					{
						.sType            = VK_STRUCTURE_TYPE_VIDEO_PICTURE_RESOURCE_INFO_KHR,
						.pNext            = NULL,
						.codedOffset      = {},
						.codedExtent      = m_codedExtent,
						.baseArrayLayer   = 0,
						.imageViewBinding = m_decodeOutputImageView,
					},
				.pSetupReferenceSlot = &slotInfos[m_currentSlot],
				.referenceSlotCount  = numActiveRefs,
				.pReferenceSlots     = 0 != numActiveRefs ? beginSlots : NULL,
			};
			vkCmdDecodeVideoKHR(m_videoCommandBuffer, &decodeInfo);

			VkVideoEndCodingInfoKHR endInfo
			{
				.sType = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR,
				.pNext = NULL,
				.flags = 0,
			};
			vkCmdEndVideoCodingKHR(m_videoCommandBuffer, &endInfo);

			{
				VkImageMemoryBarrier post
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = VK_ACCESS_MEMORY_WRITE_BIT,
					.dstAccessMask       = VK_ACCESS_MEMORY_READ_BIT,
					.oldLayout           = m_dpbCoincide
						? VK_IMAGE_LAYOUT_VIDEO_DECODE_DPB_KHR
						: VK_IMAGE_LAYOUT_VIDEO_DECODE_DST_KHR
						,
					.newLayout           = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = m_dpbCoincide
						? m_dpbImage
						: m_decodeOutputImage
						,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = 1,
						.baseArrayLayer = m_dpbCoincide ? m_currentSlot : 0,
						.layerCount     = 1,
					},
				};
				vkCmdPipelineBarrier(m_videoCommandBuffer
					, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
					, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
					, 0, 0, NULL, 0, NULL, 1, &post);
			}

			vkEndCommandBuffer(m_videoCommandBuffer);

			VkSubmitInfo submit
			{
				.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO,
				.pNext                = NULL,
				.waitSemaphoreCount   = 0,
				.pWaitSemaphores      = NULL,
				.pWaitDstStageMask    = NULL,
				.commandBufferCount   = 1,
				.pCommandBuffers      = &m_videoCommandBuffer,
				.signalSemaphoreCount = 1,
				.pSignalSemaphores    = &m_videoSemaphoreRing[ringIdx],
			};

			const VkResult sres = vkQueueSubmit(s_videoVK.videoDecodeQueue, 1, &submit, m_videoFence);

			if (VK_SUCCESS != sres)
			{
				BX_TRACE("VideoDecoderVK: vkQueueSubmit(video) failed (%d).", sres);
				return false;
			}

			vkWaitForFences(device, 1, &m_videoFence, VK_TRUE, UINT64_MAX);

			if (m_dpbCoincide)
			{
				m_dpbLayouts[m_currentSlot] = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			}
			else
			{
				m_decodeOutputLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
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
						refFrameNums[ii] = uint16_t(m_frameNumStatus[m_referenceUsage[ii]]);
					}
					const int32_t maxFrameNum = 1 << (m_spsActive.log2_max_frame_num_minus4 + 4);
					m_numActiveRefs = applyMmcoUnmarkShortTerm(
						  m_referenceUsage
						, refFrameNums
						, n
						, sh.frame_num
						, maxFrameNum
						, sh
						);
				}

				const uint32_t maxRefs = bx::min<uint32_t>(uint32_t(m_spsActive.num_ref_frames), m_numDpbSlots - 1);
				m_numActiveRefs = bgfx::appendShortTermRef(
					  m_referenceUsage
					, m_numActiveRefs
					, m_currentSlot
					, maxRefs
					);
			}

			m_firstDecode = false;

			if (!createReorderImage(uint32_t(slot) ) )
			{
				return false;
			}

			VkCommandBufferBeginInfo copyBegin
			{
				.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
				.pNext            = NULL,
				.flags            = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
				.pInheritanceInfo = NULL,
			};

			{
				VkResult bres = vkBeginCommandBuffer(gfx, &copyBegin);
				if (VK_SUCCESS != bres) { BX_TRACE("VideoDecoderVK: vkBeginCommandBuffer(copy) failed (%d).", bres); return false; }
			}

			ReorderedPicture& reorder = m_reorderPool[slot];

			{
				VkImageMemoryBarrier preCopy
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = VK_ACCESS_SHADER_READ_BIT,
					.dstAccessMask       = VK_ACCESS_TRANSFER_WRITE_BIT,
					.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED,
					.newLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = reorder.image,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = VK_REMAINING_MIP_LEVELS,
						.baseArrayLayer = 0,
						.layerCount     = VK_REMAINING_ARRAY_LAYERS,
					},
				};

				vkCmdPipelineBarrier(gfx
					, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT
					, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT
					, VK_DEPENDENCY_BY_REGION_BIT
					, 0, NULL, 0, NULL, 1, &preCopy);
			}

			reorder.layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

			VkImage  srcImage = m_dpbCoincide ? m_dpbImage : m_decodeOutputImage;
			uint32_t srcLayer = m_dpbCoincide ? m_currentSlot : 0;

			const uint32_t reorderW = (m_dstWidth  + 1) & ~1u;
			const uint32_t reorderH = (m_dstHeight + 1) & ~1u;

			VkImageCopy cpy
			{
				.srcSubresource = { .aspectMask = VK_IMAGE_ASPECT_PLANE_0_BIT, .mipLevel = 0, .baseArrayLayer = srcLayer, .layerCount = 1 },
				.srcOffset      = {},
				.dstSubresource = { .aspectMask = VK_IMAGE_ASPECT_PLANE_0_BIT, .mipLevel = 0, .baseArrayLayer = 0,        .layerCount = 1 },
				.dstOffset      = {},
				.extent         = { reorderW, reorderH, 1 },
			};
			vkCmdCopyImage(gfx, srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, reorder.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &cpy);

			cpy.extent.width  = reorderW / 2;
			cpy.extent.height = reorderH / 2;
			cpy.srcSubresource.aspectMask = VK_IMAGE_ASPECT_PLANE_1_BIT;
			cpy.dstSubresource.aspectMask = VK_IMAGE_ASPECT_PLANE_1_BIT;
			vkCmdCopyImage(gfx, srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, reorder.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &cpy);

			{
				VkImageMemoryBarrier postCopy
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dstAccessMask       = VK_ACCESS_SHADER_READ_BIT,
					.oldLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.newLayout           = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = reorder.image,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = VK_REMAINING_MIP_LEVELS,
						.baseArrayLayer = 0,
						.layerCount     = VK_REMAINING_ARRAY_LAYERS,
					},
				};
				vkCmdPipelineBarrier(
					  gfx
					, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT
					, VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT
					, VK_DEPENDENCY_BY_REGION_BIT
					, 0
					, NULL
					, 0
					, NULL
					, 1
					, &postCopy
					);
			}

			reorder.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

			vkEndCommandBuffer(gfx);

			const VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_TRANSFER_BIT;

			VkSubmitInfo copySubmit
			{
				.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO,
				.pNext                = NULL,
				.waitSemaphoreCount   = 1,
				.pWaitSemaphores      = &m_videoSemaphoreRing[ringIdx],
				.pWaitDstStageMask    = &waitStage,
				.commandBufferCount   = 1,
				.pCommandBuffers      = &gfx,
				.signalSemaphoreCount = 0,
				.pSignalSemaphores    = NULL,
			};
			const VkResult cres = vkQueueSubmit(s_videoVK.globalQueue, 1, &copySubmit, copyFence);

			if (VK_SUCCESS != cres)
			{
				BX_TRACE("VideoDecoderVK: vkQueueSubmit(copy) failed (%d).", cres);
				return false;
			}
			m_copyControl.commit(1);

			m_lastCopyRingIdx  = ringIdx;
			m_haveCopyInFlight = true;

			return true;
		}

		bool createReorderImage(uint32_t _slot)
		{
			BX_ASSERT(_slot < kVideoMaxReorderInFlight, "Invalid reorder slot %u.", _slot);
			ReorderedPicture& pic = m_reorderPool[_slot];
			if (VK_NULL_HANDLE != pic.image)
			{
				return true;
			}

			VkDevice device = s_videoVK.device;
			const VkAllocationCallbacks* allocCb = s_videoVK.allocCb;

			VkImageCreateInfo ci
			{
				.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
				.pNext                 = NULL,
				.flags                 = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT,
				.imageType             = VK_IMAGE_TYPE_2D,
				.format                = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
				.extent                = { (m_dstWidth + 1) & ~1u, (m_dstHeight + 1) & ~1u, 1 },
				.mipLevels             = 1,
				.arrayLayers           = 1,
				.samples               = VK_SAMPLE_COUNT_1_BIT,
				.tiling                = VK_IMAGE_TILING_OPTIMAL,
				.usage                 = 0
					| VK_IMAGE_USAGE_TRANSFER_DST_BIT
					| VK_IMAGE_USAGE_SAMPLED_BIT
					,
				.sharingMode           = VK_SHARING_MODE_EXCLUSIVE,
				.queueFamilyIndexCount = 0,
				.pQueueFamilyIndices   = NULL,
				.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED,
			};

			VkResult result = vkCreateImage(device, &ci, allocCb, &pic.image);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkCreateImage(reorder) failed (%d).", result);
				return false;
			}

			VkMemoryRequirements req = {};
			vkGetImageMemoryRequirements(device, pic.image, &req);

			VkMemoryAllocateInfo ai
			{
				.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.pNext           = NULL,
				.allocationSize  = req.size,
				.memoryTypeIndex = uint32_t(videoSelectMemoryType(m_renderer, req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) ),
			};
			result = vkAllocateMemory(device, &ai, allocCb, &pic.memory);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkAllocateMemory(reorder) failed (%d).", result);
				return false;
			}

			result = vkBindImageMemory(device, pic.image, pic.memory, 0);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkBindImageMemory(reorder) failed (%d).", result);
				return false;
			}

			VkImageViewCreateInfo vci
			{
				.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
				.pNext            = NULL,
				.flags            = 0,
				.image            = pic.image,
				.viewType         = VK_IMAGE_VIEW_TYPE_2D,
				.format           = VK_FORMAT_R8_UNORM,
				.components       = {},
				.subresourceRange =
				{
					.aspectMask     = VK_IMAGE_ASPECT_PLANE_0_BIT,
					.baseMipLevel   = 0,
					.levelCount     = 1,
					.baseArrayLayer = 0,
					.layerCount     = 1,
				},
			};
			result = vkCreateImageView(device, &vci, allocCb, &pic.yView);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkCreateImageView(reorder Y) failed (%d).", result);
				return false;
			}

			vci.format = VK_FORMAT_R8G8_UNORM;
			vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_PLANE_1_BIT;
			result = vkCreateImageView(device, &vci, allocCb, &pic.cbcrView);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkCreateImageView(reorder CbCr) failed (%d).", result);
				return false;
			}

			pic.layout = VK_IMAGE_LAYOUT_UNDEFINED;
			return true;
		}

		bool dispatchYuvToRgb(uint32_t _displaySlot, TextureVK& _dst)
		{
			BX_ASSERT(NULL != g_videoDecode && isValid(g_videoDecode->m_program), "Video decode program not initialized.");

			VkPipeline pso = videoGetPipeline(m_renderer, g_videoDecode->m_program);
			if (VK_NULL_HANDLE == pso)
			{
				return false;
			}

			const ProgramVK& prog = videoGetProgram(m_renderer, g_videoDecode->m_program);
			VkDevice device = s_videoVK.device;
			VkCommandBuffer commandBuffer = videoGetCommandBuffer(m_renderer);

			if (VK_NULL_HANDLE == m_yuvDescriptorPool)
			{
				const VkAllocationCallbacks* allocCb = s_videoVK.allocCb;

				VkDescriptorPoolSize poolSizes[3]
				{
					{ .type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, .descriptorCount = kYuvDescriptorRingSize     },
					{ .type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, .descriptorCount = kYuvDescriptorRingSize * 2 },
					{ .type = VK_DESCRIPTOR_TYPE_SAMPLER,       .descriptorCount = kYuvDescriptorRingSize * 2 },
				};

				VkDescriptorPoolCreateInfo dpci
				{
					.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
					.pNext         = NULL,
					.flags         = 0,
					.maxSets       = kYuvDescriptorRingSize,
					.poolSizeCount = BX_COUNTOF(poolSizes),
					.pPoolSizes    = poolSizes,
				};

				VkResult result = vkCreateDescriptorPool(device, &dpci, allocCb, &m_yuvDescriptorPool);
				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateDescriptorPool(YUV->RGB) failed (%d).", result);
					return false;
				}

				::VkDescriptorSetLayout layouts[kYuvDescriptorRingSize];
				for (uint32_t ii = 0; ii < kYuvDescriptorRingSize; ++ii)
				{
					layouts[ii] = prog.m_descriptorSetLayout;
				}

				VkDescriptorSetAllocateInfo dsai
				{
					.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
					.pNext              = NULL,
					.descriptorPool     = m_yuvDescriptorPool,
					.descriptorSetCount = kYuvDescriptorRingSize,
					.pSetLayouts        = layouts,
				};
				result = vkAllocateDescriptorSets(device, &dsai, m_yuvDescriptorSet);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkAllocateDescriptorSets(YUV->RGB ring) failed (%d).", result);
					return false;
				}
			}

			VkDescriptorSet descriptorSet = m_yuvDescriptorSet[m_yuvDescriptorIndex];
			m_yuvDescriptorIndex = (m_yuvDescriptorIndex + 1) % kYuvDescriptorRingSize;

			_dst.setState(commandBuffer, VK_IMAGE_LAYOUT_GENERAL);

			VkImageView dstView = VK_NULL_HANDLE;
			{
				VkImageViewCreateInfo viewInfo
				{
					.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
					.pNext            = NULL,
					.flags            = 0,
					.image            = _dst.m_textureImage,
					.viewType         = VK_IMAGE_VIEW_TYPE_2D,
					.format           = VK_FORMAT_R8G8B8A8_UNORM,
					.components       =
					{
						.r = VK_COMPONENT_SWIZZLE_IDENTITY,
						.g = VK_COMPONENT_SWIZZLE_IDENTITY,
						.b = VK_COMPONENT_SWIZZLE_IDENTITY,
						.a = VK_COMPONENT_SWIZZLE_IDENTITY,
					},
					.subresourceRange =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = 1,
						.baseArrayLayer = 0,
						.layerCount     = 1,
					},
				};

				const VkResult result = vkCreateImageView(device, &viewInfo, s_videoVK.allocCb, &dstView);

				if (VK_SUCCESS != result)
				{
					BX_TRACE("VideoDecoderVK: vkCreateImageView(YUV->RGB dst rgba8) failed (%d).", result);
					return false;
				}
			}

			VkDescriptorImageInfo imageInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS * 2] = {};
			VkWriteDescriptorSet     writes[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS * 2] = {};
			uint32_t imageCount = 0;
			uint32_t writeCount = 0;

			const uint32_t samplerFlags = BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP;
			VkSampler ySampler    = videoGetSampler(m_renderer, samplerFlags, VK_FORMAT_R8_UNORM);
			VkSampler cbcrSampler = videoGetSampler(m_renderer, samplerFlags, VK_FORMAT_R8G8_UNORM);

			for (uint32_t stage = 0; stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++stage)
			{
				const BindInfo& bindInfo = prog.m_bindInfo[stage];
				if (!isValid(bindInfo.uniformHandle) )
				{
					continue;
				}

				if (BindType::Image == bindInfo.type)
				{
					imageInfo[imageCount].imageLayout = VK_IMAGE_LAYOUT_GENERAL;
					imageInfo[imageCount].imageView   = dstView;
					imageInfo[imageCount].sampler     = VK_NULL_HANDLE;

					writes[writeCount].sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writes[writeCount].dstSet          = descriptorSet;
					writes[writeCount].dstBinding      = bindInfo.binding;
					writes[writeCount].descriptorCount = 1;
					writes[writeCount].descriptorType  = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
					writes[writeCount].pImageInfo      = &imageInfo[imageCount];
					++writeCount;
					++imageCount;
				}
				else if (BindType::Sampler == bindInfo.type)
				{
					const bool yPlane = 1 == stage;
					imageInfo[imageCount].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					imageInfo[imageCount].imageView   = yPlane ? m_reorderPool[_displaySlot].yView : m_reorderPool[_displaySlot].cbcrView;
					imageInfo[imageCount].sampler     = yPlane ? ySampler : cbcrSampler;

					writes[writeCount].sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writes[writeCount].dstSet          = descriptorSet;
					writes[writeCount].dstBinding      = bindInfo.binding;
					writes[writeCount].descriptorCount = 1;
					writes[writeCount].descriptorType  = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
					writes[writeCount].pImageInfo      = &imageInfo[imageCount];
					++writeCount;

					writes[writeCount].sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
					writes[writeCount].dstSet          = descriptorSet;
					writes[writeCount].dstBinding      = bindInfo.samplerBinding;
					writes[writeCount].descriptorCount = 1;
					writes[writeCount].descriptorType  = VK_DESCRIPTOR_TYPE_SAMPLER;
					writes[writeCount].pImageInfo      = &imageInfo[imageCount];
					++writeCount;
					++imageCount;
				}
			}

			vkUpdateDescriptorSets(device, writeCount, writes, 0, NULL);

			{
				VkImageMemoryBarrier reorderImb
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dstAccessMask       = VK_ACCESS_SHADER_READ_BIT,
					.oldLayout           = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.newLayout           = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = m_reorderPool[_displaySlot].image,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = 1,
						.baseArrayLayer = 0,
						.layerCount     = 1,
					},
				};
				vkCmdPipelineBarrier(commandBuffer
					, VK_PIPELINE_STAGE_TRANSFER_BIT
					, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
					, 0
					, 0, NULL
					, 0, NULL
					, 1, &reorderImb
					);
			}

			vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pso);
			vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, prog.m_pipelineLayout, 0, 1, &descriptorSet, 0, NULL);
			vkCmdDispatch(commandBuffer, bx::max<uint32_t>((m_dstWidth + 7) / 8, 1), bx::max<uint32_t>((m_dstHeight + 7) / 8, 1), 1);

			{
				VkImageMemoryBarrier imb
				{
					.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
					.pNext               = NULL,
					.srcAccessMask       = VK_ACCESS_SHADER_WRITE_BIT,
					.dstAccessMask       = VK_ACCESS_SHADER_READ_BIT,
					.oldLayout           = VK_IMAGE_LAYOUT_GENERAL,
					.newLayout           = VK_IMAGE_LAYOUT_GENERAL,
					.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
					.image               = _dst.m_textureImage,
					.subresourceRange    =
					{
						.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
						.baseMipLevel   = 0,
						.levelCount     = 1,
						.baseArrayLayer = 0,
						.layerCount     = 1,
					},
				};
				vkCmdPipelineBarrier(commandBuffer
					, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
					, 0
					| VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
					| VK_PIPELINE_STAGE_VERTEX_SHADER_BIT
					| VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT
					, 0
					, 0, NULL
					, 0, NULL
					, 1, &imb
					);
			}

			videoRelease(m_renderer, dstView);

			return true;
		}

		bool createSessionParameters()
		{
			VkDevice device = s_videoVK.device;
			const VkAllocationCallbacks* allocCb = s_videoVK.allocCb;

			uint32_t numSps = 0;
			uint32_t numPps = 0;
			StdVideoH264SequenceParameterSet vkSpsArr[BX_COUNTOF(m_spsArray)] = {};
			StdVideoH264PictureParameterSet  vkPpsArr[BX_COUNTOF(m_ppsArray)] = {};
			StdVideoH264ScalingLists         vkPpsScalingArr[BX_COUNTOF(m_ppsArray)] = {};

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_spsArray); ++ii)
			{
				if (!m_spsValid[ii])
				{
					continue;
				}

				const h264::SPS& sps = m_spsArray[ii];
				StdVideoH264SequenceParameterSet& vk = vkSpsArr[numSps++];

				vk.flags.constraint_set0_flag                 = sps.constraint_set0_flag;
				vk.flags.constraint_set1_flag                 = sps.constraint_set1_flag;
				vk.flags.constraint_set2_flag                 = sps.constraint_set2_flag;
				vk.flags.constraint_set3_flag                 = sps.constraint_set3_flag;
				vk.flags.constraint_set4_flag                 = sps.constraint_set4_flag;
				vk.flags.constraint_set5_flag                 = sps.constraint_set5_flag;
				vk.flags.direct_8x8_inference_flag            = sps.direct_8x8_inference_flag;
				vk.flags.mb_adaptive_frame_field_flag         = sps.mb_adaptive_frame_field_flag;
				vk.flags.frame_mbs_only_flag                  = sps.frame_mbs_only_flag;
				vk.flags.delta_pic_order_always_zero_flag     = sps.delta_pic_order_always_zero_flag;
				vk.flags.separate_colour_plane_flag           = sps.separate_colour_plane_flag;
				vk.flags.gaps_in_frame_num_value_allowed_flag = sps.gaps_in_frame_num_value_allowed_flag;
				vk.flags.qpprime_y_zero_transform_bypass_flag = sps.qpprime_y_zero_transform_bypass_flag;
				vk.flags.frame_cropping_flag                  = sps.frame_cropping_flag;
				vk.flags.seq_scaling_matrix_present_flag      = sps.seq_scaling_matrix_present_flag;
				vk.flags.vui_parameters_present_flag          = 0; // skip VUI; we don't need it for decode
				vk.profile_idc                                = StdVideoH264ProfileIdc(sps.profile_idc);
				vk.level_idc                                  = translateH264Level(sps.level_idc);
				vk.chroma_format_idc                          = STD_VIDEO_H264_CHROMA_FORMAT_IDC_420;
				vk.seq_parameter_set_id                       = uint8_t(sps.seq_parameter_set_id);
				vk.bit_depth_luma_minus8                      = uint8_t(sps.bit_depth_luma_minus8);
				vk.bit_depth_chroma_minus8                    = uint8_t(sps.bit_depth_chroma_minus8);
				vk.log2_max_frame_num_minus4                  = uint8_t(sps.log2_max_frame_num_minus4);
				vk.pic_order_cnt_type                         = StdVideoH264PocType(sps.pic_order_cnt_type);
				vk.offset_for_non_ref_pic                     = sps.offset_for_non_ref_pic;
				vk.offset_for_top_to_bottom_field             = sps.offset_for_top_to_bottom_field;
				vk.log2_max_pic_order_cnt_lsb_minus4          = uint8_t(sps.log2_max_pic_order_cnt_lsb_minus4);
				vk.num_ref_frames_in_pic_order_cnt_cycle      = uint8_t(sps.num_ref_frames_in_pic_order_cnt_cycle);
				vk.max_num_ref_frames                         = uint8_t(sps.num_ref_frames);
				vk.pic_width_in_mbs_minus1                    = uint32_t(sps.pic_width_in_mbs_minus1);
				vk.pic_height_in_map_units_minus1             = uint32_t(sps.pic_height_in_map_units_minus1);
				vk.frame_crop_left_offset                     = uint32_t(sps.frame_crop_left_offset);
				vk.frame_crop_right_offset                    = uint32_t(sps.frame_crop_right_offset);
				vk.frame_crop_top_offset                      = uint32_t(sps.frame_crop_top_offset);
				vk.frame_crop_bottom_offset                   = uint32_t(sps.frame_crop_bottom_offset);
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_ppsArray); ++ii)
			{
				if (!m_ppsValid[ii])
				{
					continue;
				}
				const h264::PPS& pps = m_ppsArray[ii];
				StdVideoH264PictureParameterSet& vk = vkPpsArr[numPps];
				StdVideoH264ScalingLists& vkScaling = vkPpsScalingArr[numPps];
				++numPps;

				vk.flags.transform_8x8_mode_flag                      = pps.transform_8x8_mode_flag;
				vk.flags.redundant_pic_cnt_present_flag               = pps.redundant_pic_cnt_present_flag;
				vk.flags.constrained_intra_pred_flag                  = pps.constrained_intra_pred_flag;
				vk.flags.deblocking_filter_control_present_flag       = pps.deblocking_filter_control_present_flag;
				vk.flags.weighted_pred_flag                           = pps.weighted_pred_flag;
				vk.flags.bottom_field_pic_order_in_frame_present_flag = pps.pic_order_present_flag;
				vk.flags.entropy_coding_mode_flag                     = pps.entropy_coding_mode_flag;
				vk.flags.pic_scaling_matrix_present_flag              = pps.pic_scaling_matrix_present_flag;
				vk.seq_parameter_set_id                               = uint8_t(pps.seq_parameter_set_id);
				vk.pic_parameter_set_id                               = uint8_t(pps.pic_parameter_set_id);
				vk.num_ref_idx_l0_default_active_minus1               = uint8_t(pps.num_ref_idx_l0_active_minus1);
				vk.num_ref_idx_l1_default_active_minus1               = uint8_t(pps.num_ref_idx_l1_active_minus1);
				vk.weighted_bipred_idc                                = StdVideoH264WeightedBipredIdc(pps.weighted_bipred_idc);
				vk.pic_init_qp_minus26                                = int8_t(pps.pic_init_qp_minus26);
				vk.pic_init_qs_minus26                                = int8_t(pps.pic_init_qs_minus26);
				vk.chroma_qp_index_offset                             = int8_t(pps.chroma_qp_index_offset);
				vk.second_chroma_qp_index_offset                      = int8_t(pps.second_chroma_qp_index_offset);

				vkScaling = {};

				for (uint32_t jj = 0; jj < BX_COUNTOF(pps.pic_scaling_list_present_flag); ++jj)
				{
					vkScaling.scaling_list_present_mask = uint16_t(vkScaling.scaling_list_present_mask | (pps.pic_scaling_list_present_flag[jj] << jj) );
				}

				for (uint32_t jj = 0; jj < BX_COUNTOF(pps.UseDefaultScalingMatrix4x4Flag); ++jj)
				{
					vkScaling.use_default_scaling_matrix_mask = uint16_t(vkScaling.use_default_scaling_matrix_mask | (pps.UseDefaultScalingMatrix4x4Flag[jj] << jj) );
				}

				for (uint32_t jj = 0; jj < BX_COUNTOF(pps.ScalingList4x4); ++jj)
				{
					for (uint32_t kk = 0; kk < BX_COUNTOF(pps.ScalingList4x4[jj]); ++kk)
					{
						vkScaling.ScalingList4x4[jj][kk] = uint8_t(pps.ScalingList4x4[jj][kk]);
					}
				}

				for (uint32_t jj = 0; jj < BX_COUNTOF(pps.ScalingList8x8); ++jj)
				{
					for (uint32_t kk = 0; kk < BX_COUNTOF(pps.ScalingList8x8[jj]); ++kk)
					{
						vkScaling.ScalingList8x8[jj][kk] = uint8_t(pps.ScalingList8x8[jj][kk]);
					}
				}

				vk.pScalingLists = &vkScaling;
			}

			if (0 == numSps
			||  0 == numPps)
			{
				BX_TRACE("VideoDecoderVK: no SPS/PPS to populate session parameters.");
				return false;
			}

			VkVideoDecodeH264SessionParametersAddInfoKHR addInfo
			{
				.sType       = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_ADD_INFO_KHR,
				.pNext       = NULL,
				.stdSPSCount = numSps,
				.pStdSPSs    = vkSpsArr,
				.stdPPSCount = numPps,
				.pStdPPSs    = vkPpsArr,
			};

			VkVideoDecodeH264SessionParametersCreateInfoKHR h264Ci
			{
				.sType              = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_SESSION_PARAMETERS_CREATE_INFO_KHR,
				.pNext              = NULL,
				.maxStdSPSCount     = numSps,
				.maxStdPPSCount     = numPps,
				.pParametersAddInfo = &addInfo,
			};

			VkVideoSessionParametersCreateInfoKHR ci
			{
				.sType                          = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR,
				.pNext                          = &h264Ci,
				.flags                          = 0,
				.videoSessionParametersTemplate = VK_NULL_HANDLE,
				.videoSession                   = m_videoSession,
			};

			VkResult result = vkCreateVideoSessionParametersKHR(device, &ci, allocCb, &m_sessionParams);

			if (VK_SUCCESS != result)
			{
				BX_TRACE("VideoDecoderVK: vkCreateVideoSessionParametersKHR failed (%d).", result);
				return false;
			}

			return true;
		}

		void resetReorder()
		{
			for (uint32_t ii = 0; ii < kVideoMaxReorderInFlight; ++ii)
			{
				if (int32_t(ii) != m_displayedSlot
				&&  int32_t(ii) != m_prevDisplayedSlot)
				{
					m_reorderPool[ii].displayOrder = -1;
				}
			}

			m_displayOrderNext = 0;
			m_numActiveRefs = 0;
			m_nextSlot = 0;
		}

		bool             m_created;
		uint32_t         m_dstWidth;
		uint32_t         m_dstHeight;
		uint32_t         m_codedWidth;
		uint32_t         m_codedHeight;
		uint32_t         m_numDpbSlots;
		uint32_t         m_nextSlot;
		uint32_t         m_currentSlot;
		uint32_t         m_numActiveRefs;
		uint8_t          m_referenceUsage[kNumDpbSlots];
		int32_t          m_prevPocLsb;
		int32_t          m_prevPocMsb;
		int32_t          m_displayOrderNext;
		int32_t          m_displayedSlot;
		int32_t          m_prevDisplayedSlot;
		ReorderedPicture m_reorderPool[kVideoMaxReorderInFlight];
		h264::SPS        m_spsActive;
		h264::SPS        m_spsArray[kVideoMaxH264SpsCount];
		h264::PPS        m_ppsArray[kVideoMaxH264PpsCount];
		bool             m_spsValid[kVideoMaxH264SpsCount];
		bool             m_ppsValid[kVideoMaxH264PpsCount];

		bgfx::AuQueue m_auQueue;

		uint32_t m_initFlags;
		uint32_t m_cachedAuBytes;

		RendererContextVK* m_renderer;

		VkVideoSessionKHR           m_videoSession;
		VkVideoSessionParametersKHR m_sessionParams;

		VkDeviceMemory m_sessionMemory[kMaxSessionMemory];

		uint32_t       m_numSessionMemory;
		uint32_t       m_maxActiveRefs;

		VkVideoDecodeH264ProfileInfoKHR m_h264Profile;
		VkVideoProfileInfoKHR           m_videoProfile;

		VkImage         m_dpbImage;
		VkDeviceMemory  m_dpbImageMemory;
		VkImageView     m_dpbImageView[kNumDpbSlots];
		VkImageLayout   m_dpbLayouts[kNumDpbSlots];
		bool            m_dpbCoincide;

		VkImage         m_decodeOutputImage;
		VkDeviceMemory  m_decodeOutputImageMemory;
		VkImageView     m_decodeOutputImageView;
		VkImageLayout   m_decodeOutputLayout;

		VkBuffer        m_bitstreamBuffer;
		VkDeviceMemory  m_bitstreamBufferMemory;
		VkDeviceSize    m_bitstreamBufferSize;
		void*           m_bitstreamMapped;
		uint32_t        m_bitstreamAlignment;

		VkCommandPool   m_videoCommandPool;
		VkCommandBuffer m_videoCommandBuffer;
		VkFence         m_videoFence;
		VkCommandPool   m_copyCommandPool;

		VkCommandBuffer m_copyCommandBufferRing[kCopyRingSize];

		VkFence         m_copyFenceRing[kCopyRingSize];

		VkSemaphore           m_videoSemaphoreRing[kCopyRingSize];
		bx::RingBufferControl m_copyControl;

		uint32_t        m_lastCopyRingIdx;
		bool            m_haveCopyInFlight;

		VkDescriptorPool  m_yuvDescriptorPool;
		::VkDescriptorSet m_yuvDescriptorSet[kYuvDescriptorRingSize];
		uint32_t          m_yuvDescriptorIndex;

		int32_t               m_pocStatus[kNumDpbSlots];
		int32_t               m_frameNumStatus[kNumDpbSlots];
		VkExtent2D            m_codedExtent;
		VkExtensionProperties m_stdHeaderVersion;
		bool                  m_firstDecode;
	};

	VideoDecoderVK* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextVK* _renderer, uint16_t _width, uint16_t _height)
	{
		VideoDecoderVK* decoder = BX_NEW(g_allocator, VideoDecoderVK);
		if (!decoder->create(_init, _renderer, _width, _height) )
		{
			decoder->destroy();
			bx::deleteObject(g_allocator, decoder);
			return NULL;
		}
		return decoder;
	}

	void videoDecoderDestroy(VideoDecoderVK* _decoder)
	{
		if (NULL != _decoder)
		{
			_decoder->destroy();
			bx::deleteObject(g_allocator, _decoder);
		}
	}

	bool videoDecoderDecode(VideoDecoderVK* _decoder, const VideoDecoderFrame& _frame, TextureVK& _dst)
	{
		return _decoder->decode(_frame, _dst);
	}

	struct ProfileEntry
	{
		VideoCodec::Enum                    codec;
		const char*                         extensionName;
		VkVideoCodecOperationFlagBitsKHR    op;
		int32_t                             h264Profile;
		int32_t                             h265Profile;
		int32_t                             av1Profile;
		VkVideoChromaSubsamplingFlagBitsKHR chroma;
		VkVideoComponentBitDepthFlagBitsKHR depth;
		uint32_t                            caps;
	};

	static const ProfileEntry s_probes[] =
	{
		{
			  VideoCodec::H264
			, "VK_KHR_video_decode_h264"
			, VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR
			, STD_VIDEO_H264_PROFILE_IDC_HIGH
			, 0
			, 0
			, VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR
			, VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR
			, BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
		},
		{
			  VideoCodec::H265
			, "VK_KHR_video_decode_h265"
			, VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR
			, 0
			, STD_VIDEO_H265_PROFILE_IDC_MAIN
			, 0
			, VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR
			, VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR
			, BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
		},
		{
			  VideoCodec::H265
			, "VK_KHR_video_decode_h265"
			, VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR
			, 0
			, STD_VIDEO_H265_PROFILE_IDC_MAIN_10
			, 0
			, VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR
			, VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR
			, BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
		},
		{
			  VideoCodec::AV1
			, "VK_KHR_video_decode_av1"
			, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR
			, 0
			, 0
			, STD_VIDEO_AV1_PROFILE_MAIN
			, VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR
			, VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR
			, BGFX_CAPS_VIDEO_CODEC_BIT_8 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
		},
		{
			  VideoCodec::AV1
			, "VK_KHR_video_decode_av1"
			, VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR
			, 0
			, 0
			, STD_VIDEO_AV1_PROFILE_MAIN
			, VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR
			, VK_VIDEO_COMPONENT_BIT_DEPTH_10_BIT_KHR
			, BGFX_CAPS_VIDEO_CODEC_BIT_10 | BGFX_CAPS_VIDEO_CODEC_CHROMA_420
		},
	};

	void initVideoDecoder(RendererContextVK* _renderer, const VideoBindingVK& _binding)
	{
		s_videoVK = _binding;

		if (!videoIsExtensionSupported(_renderer, "VK_KHR_video_queue")
		||  NULL == vkGetPhysicalDeviceVideoCapabilitiesKHR)
		{
			return;
		}

		bool anySupported = false;
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_probes); ++ii)
		{
			const ProfileEntry& probe = s_probes[ii];
			if (!videoIsExtensionSupported(_renderer, probe.extensionName))
			{
				continue;
			}

			VkVideoDecodeH264ProfileInfoKHR h264Info = {};
			VkVideoDecodeH265ProfileInfoKHR h265Info = {};
			VkVideoDecodeAV1ProfileInfoKHR  av1Info  = {};
			const void* codecProfileChain = NULL;

			if (probe.codec == VideoCodec::H264)
			{
				h264Info =
				{
					.sType         = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_PROFILE_INFO_KHR,
					.pNext         = NULL,
					.stdProfileIdc = StdVideoH264ProfileIdc(probe.h264Profile),
					.pictureLayout = VK_VIDEO_DECODE_H264_PICTURE_LAYOUT_PROGRESSIVE_KHR,
				};
				codecProfileChain = &h264Info;
			}
			else if (probe.codec == VideoCodec::H265)
			{
				h265Info =
				{
					.sType         = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR,
					.pNext         = NULL,
					.stdProfileIdc = StdVideoH265ProfileIdc(probe.h265Profile),
				};
				codecProfileChain = &h265Info;
			}
			else if (probe.codec == VideoCodec::AV1)
			{
				av1Info =
				{
					.sType            = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_PROFILE_INFO_KHR,
					.pNext            = NULL,
					.stdProfile       = StdVideoAV1Profile(probe.av1Profile),
					.filmGrainSupport = VK_FALSE,
				};
				codecProfileChain = &av1Info;
			}

			VkVideoProfileInfoKHR profileInfo
			{
				.sType               = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR,
				.pNext               = codecProfileChain,
				.videoCodecOperation = probe.op,
				.chromaSubsampling   = VkVideoChromaSubsamplingFlagsKHR(probe.chroma),
				.lumaBitDepth        = VkVideoComponentBitDepthFlagsKHR(probe.depth),
				.chromaBitDepth      = VkVideoComponentBitDepthFlagsKHR(probe.depth),
			};

			VkVideoDecodeH264CapabilitiesKHR h264Caps
			{
				.sType                  = VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR,
				.pNext                  = NULL,
				.maxLevelIdc            = STD_VIDEO_H264_LEVEL_IDC_INVALID,
				.fieldOffsetGranularity = {},
			};

			VkVideoDecodeH265CapabilitiesKHR h265Caps
			{
				.sType       = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR,
				.pNext       = NULL,
				.maxLevelIdc = STD_VIDEO_H265_LEVEL_IDC_INVALID,
			};

			VkVideoDecodeAV1CapabilitiesKHR av1Caps
			{
				.sType    = VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_CAPABILITIES_KHR,
				.pNext    = NULL,
				.maxLevel = STD_VIDEO_AV1_LEVEL_INVALID,
			};

			VkVideoDecodeCapabilitiesKHR decodeCaps
			{
				.sType = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR,
				.pNext = probe.codec == VideoCodec::H264 ? (void*)&h264Caps
				       : probe.codec == VideoCodec::H265 ? (void*)&h265Caps
				       : probe.codec == VideoCodec::AV1  ? (void*)&av1Caps
				       : NULL,
				.flags = 0,
			};

			VkVideoCapabilitiesKHR videoCaps
			{
				.sType                             = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR,
				.pNext                             = &decodeCaps,
				.flags                             = 0,
				.minBitstreamBufferOffsetAlignment = 0,
				.minBitstreamBufferSizeAlignment   = 0,
				.pictureAccessGranularity          = {},
				.minCodedExtent                    = {},
				.maxCodedExtent                    = {},
				.maxDpbSlots                       = 0,
				.maxActiveReferencePictures        = 0,
				.stdHeaderVersion                  = {},
			};

			VkResult result = vkGetPhysicalDeviceVideoCapabilitiesKHR(
				  _binding.physicalDevice
				, &profileInfo
				, &videoCaps
				);

			if (VK_SUCCESS == result)
			{
				g_caps.codecs[probe.codec] |= probe.caps;
				anySupported = true;

				BX_TRACE("[VK] Video decode supported: codec=%d caps=0x%08x"
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

} } // namespace bgfx::vk

#	else

namespace bgfx { namespace vk
{
	void initVideoDecoder(RendererContextVK* _renderer, const VideoBindingVK& _binding)
	{
		BX_UNUSED(_renderer, _binding);
	}

	VideoDecoderVK* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextVK* _renderer, uint16_t _width, uint16_t _height)
	{
		BX_UNUSED(_init, _renderer, _width, _height);
		return NULL;
	}

	void videoDecoderDestroy(VideoDecoderVK* _decoder)
	{
		BX_UNUSED(_decoder);
	}

	bool videoDecoderDecode(VideoDecoderVK* _decoder, const VideoDecoderFrame& _frame, TextureVK& _dst)
	{
		BX_UNUSED(_decoder, _frame, _dst);
		return false;
	}

} } // namespace bgfx::vk

#endif // BGFX_CONFIG_VIDEO_VULKAN

#endif // BGFX_CONFIG_RENDERER_VULKAN
