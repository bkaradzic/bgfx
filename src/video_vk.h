/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_VIDEO_VK_H_HEADER_GUARD
#define BGFX_VIDEO_VK_H_HEADER_GUARD

#include <vulkan-local/vulkan.h>

namespace bgfx { namespace vk
{
	struct RendererContextVK;
	struct TextureVK;
	struct VideoDecoderVK;

	struct VideoBindingVK
	{
		VkDevice                     device;
		const VkAllocationCallbacks* allocCb;
		VkPhysicalDevice             physicalDevice;
		uint32_t                     videoDecodeQueueFamily;
		uint32_t                     globalQueueFamily;
		VkQueue                      videoDecodeQueue;
		VkQueue                      globalQueue;
		uint16_t                     vendorId;
	};

	void initVideoDecoder(RendererContextVK* _renderer, const VideoBindingVK& _binding);

	VideoDecoderVK* videoDecoderCreate(const VideoDecoderInit& _init, RendererContextVK* _renderer, uint16_t _width, uint16_t _height);
	void videoDecoderDestroy(VideoDecoderVK* _decoder);
	bool videoDecoderDecode(VideoDecoderVK* _decoder, const VideoDecoderFrame& _frame, TextureVK& _dst);

} } // namespace bgfx::vk

#endif // BGFX_VIDEO_VK_H_HEADER_GUARD
