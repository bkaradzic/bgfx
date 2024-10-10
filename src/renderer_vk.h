/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_RENDERER_VK_H_HEADER_GUARD
#define BGFX_RENDERER_VK_H_HEADER_GUARD

#if BX_PLATFORM_ANDROID
#	define VK_USE_PLATFORM_ANDROID_KHR
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_ANDROID
#elif BX_PLATFORM_LINUX
#	define VK_USE_PLATFORM_WAYLAND_KHR
#	define VK_USE_PLATFORM_XLIB_KHR
#	define VK_USE_PLATFORM_XCB_KHR
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_LINUX
#elif BX_PLATFORM_WINDOWS
#	define VK_USE_PLATFORM_WIN32_KHR
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_WINDOWS
#elif BX_PLATFORM_OSX
#	define VK_USE_PLATFORM_MACOS_MVK
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_MACOS
#elif BX_PLATFORM_NX
# define VK_USE_PLATFORM_VI_NN
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_NX
#else
#	define VK_IMPORT_INSTANCE_PLATFORM
#endif // BX_PLATFORM_*

#define VK_NO_STDINT_H
#define VK_NO_PROTOTYPES
#include <vulkan-local/vulkan.h>
#include <vulkan-local/vulkan_beta.h>

// vulkan.h pulls X11 crap...
#if defined(None)
#	undef None
#endif // defined(None)

#if defined(Success)
#	undef Success
#endif // defined(Success)

#if defined(Status)
#	undef Status
#endif // defined(Status)

#include "renderer.h"
#include "debug_renderdoc.h"

#define VK_IMPORT                                                          \
			VK_IMPORT_FUNC(false, vkCreateInstance);                       \
			VK_IMPORT_FUNC(false, vkGetInstanceProcAddr);                  \
			VK_IMPORT_FUNC(false, vkGetDeviceProcAddr);                    \
			VK_IMPORT_FUNC(false, vkEnumerateInstanceExtensionProperties); \
			VK_IMPORT_FUNC(false, vkEnumerateInstanceLayerProperties);     \
			/* 1.1 */                                                      \
			VK_IMPORT_FUNC(true,  vkEnumerateInstanceVersion);             \

#define VK_IMPORT_INSTANCE_ANDROID                                     \
			/* VK_KHR_android_surface */                               \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateAndroidSurfaceKHR); \

#define VK_IMPORT_INSTANCE_LINUX                                                              \
			/* VK_KHR_wayland_surface */                                                      \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateWaylandSurfaceKHR);                        \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceWaylandPresentationSupportKHR); \
			/* VK_KHR_xlib_surface */                                                         \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateXlibSurfaceKHR);                           \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceXlibPresentationSupportKHR);    \
			/* VK_KHR_xcb_surface */                                                          \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateXcbSurfaceKHR);                            \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceXcbPresentationSupportKHR);     \

#define VK_IMPORT_INSTANCE_WINDOWS                                                          \
			/* VK_KHR_win32_surface */                                                      \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateWin32SurfaceKHR);                        \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceWin32PresentationSupportKHR); \

#define VK_IMPORT_INSTANCE_MACOS                                     \
			/* VK_MVK_macos_surface */                               \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateMacOSSurfaceMVK); \

#define VK_IMPORT_INSTANCE_NX \
			/* VK_NN_vi_surface */                              \
			VK_IMPORT_INSTANCE_FUNC(true, vkCreateViSurfaceNN); \

#define VK_IMPORT_INSTANCE                                                             \
			VK_IMPORT_INSTANCE_FUNC(false, vkDestroyInstance);                         \
			VK_IMPORT_INSTANCE_FUNC(false, vkEnumeratePhysicalDevices);                \
			VK_IMPORT_INSTANCE_FUNC(false, vkEnumerateDeviceExtensionProperties);      \
			VK_IMPORT_INSTANCE_FUNC(false, vkEnumerateDeviceLayerProperties);          \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceProperties);             \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceFormatProperties);       \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceFeatures);               \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceImageFormatProperties);  \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceMemoryProperties);       \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceQueueFamilyProperties);  \
			VK_IMPORT_INSTANCE_FUNC(false, vkCreateDevice);                            \
			VK_IMPORT_INSTANCE_FUNC(false, vkDestroyDevice);                           \
			/* VK_KHR_surface */                                                       \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceSurfaceCapabilitiesKHR); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceSurfaceFormatsKHR);      \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceSurfacePresentModesKHR); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceSurfaceSupportKHR);      \
			VK_IMPORT_INSTANCE_FUNC(true,  vkDestroySurfaceKHR);                       \
			/* VK_KHR_get_physical_device_properties2 */                               \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceFeatures2KHR);           \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceMemoryProperties2KHR);   \
			/* VK_EXT_debug_report */                                                  \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateDebugReportCallbackEXT);            \
			VK_IMPORT_INSTANCE_FUNC(true,  vkDestroyDebugReportCallbackEXT);           \
			VK_IMPORT_INSTANCE_PLATFORM

#define VK_IMPORT_DEVICE                                                    \
			VK_IMPORT_DEVICE_FUNC(false, vkGetDeviceQueue);                 \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateFence);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyFence);                   \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateSemaphore);                \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroySemaphore);               \
			VK_IMPORT_DEVICE_FUNC(false, vkResetFences);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateCommandPool);              \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyCommandPool);             \
			VK_IMPORT_DEVICE_FUNC(false, vkResetCommandPool);               \
			VK_IMPORT_DEVICE_FUNC(false, vkAllocateCommandBuffers);         \
			VK_IMPORT_DEVICE_FUNC(false, vkFreeCommandBuffers);             \
			VK_IMPORT_DEVICE_FUNC(false, vkGetBufferMemoryRequirements);    \
			VK_IMPORT_DEVICE_FUNC(false, vkGetImageMemoryRequirements);     \
			VK_IMPORT_DEVICE_FUNC(false, vkGetImageSubresourceLayout);      \
			VK_IMPORT_DEVICE_FUNC(false, vkAllocateMemory);                 \
			VK_IMPORT_DEVICE_FUNC(false, vkFreeMemory);                     \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateImage);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyImage);                   \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateImageView);                \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyImageView);               \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateBuffer);                   \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyBuffer);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateFramebuffer);              \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyFramebuffer);             \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateRenderPass);               \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyRenderPass);              \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateShaderModule);             \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyShaderModule);            \
			VK_IMPORT_DEVICE_FUNC(false, vkCreatePipelineCache);            \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyPipelineCache);           \
			VK_IMPORT_DEVICE_FUNC(false, vkGetPipelineCacheData);           \
			VK_IMPORT_DEVICE_FUNC(false, vkMergePipelineCaches);            \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateGraphicsPipelines);        \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateComputePipelines);         \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyPipeline);                \
			VK_IMPORT_DEVICE_FUNC(false, vkCreatePipelineLayout);           \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyPipelineLayout);          \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateSampler);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroySampler);                 \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateDescriptorSetLayout);      \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyDescriptorSetLayout);     \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateDescriptorPool);           \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyDescriptorPool);          \
			VK_IMPORT_DEVICE_FUNC(false, vkResetDescriptorPool);            \
			VK_IMPORT_DEVICE_FUNC(false, vkAllocateDescriptorSets);         \
			VK_IMPORT_DEVICE_FUNC(false, vkFreeDescriptorSets);             \
			VK_IMPORT_DEVICE_FUNC(false, vkUpdateDescriptorSets);           \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateQueryPool);                \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyQueryPool);               \
			VK_IMPORT_DEVICE_FUNC(false, vkQueueSubmit);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkQueueWaitIdle);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkDeviceWaitIdle);                 \
			VK_IMPORT_DEVICE_FUNC(false, vkWaitForFences);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkBeginCommandBuffer);             \
			VK_IMPORT_DEVICE_FUNC(false, vkEndCommandBuffer);               \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdPipelineBarrier);             \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBeginRenderPass);             \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdEndRenderPass);               \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetViewport);                 \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDraw);                        \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDrawIndexed);                 \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDrawIndirect);                \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDrawIndexedIndirect);         \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDispatch);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDispatchIndirect);            \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindPipeline);                \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetStencilReference);         \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetBlendConstants);           \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetScissor);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindDescriptorSets);          \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindIndexBuffer);             \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindVertexBuffers);           \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdClearColorImage);             \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdClearDepthStencilImage);      \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdClearAttachments);            \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdResolveImage);                \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdCopyBuffer);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdCopyBufferToImage);           \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdCopyImage);                   \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdCopyImageToBuffer);           \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBlitImage);                   \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdResetQueryPool);              \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdWriteTimestamp);              \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBeginQuery);                  \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdEndQuery);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdCopyQueryPoolResults);        \
			VK_IMPORT_DEVICE_FUNC(false, vkMapMemory);                      \
			VK_IMPORT_DEVICE_FUNC(false, vkUnmapMemory);                    \
			VK_IMPORT_DEVICE_FUNC(false, vkFlushMappedMemoryRanges);        \
			VK_IMPORT_DEVICE_FUNC(false, vkInvalidateMappedMemoryRanges);   \
			VK_IMPORT_DEVICE_FUNC(false, vkBindBufferMemory);               \
			VK_IMPORT_DEVICE_FUNC(false, vkBindImageMemory);                \
			/* VK_KHR_swapchain */                                          \
			VK_IMPORT_DEVICE_FUNC(true,  vkCreateSwapchainKHR);             \
			VK_IMPORT_DEVICE_FUNC(true,  vkDestroySwapchainKHR);            \
			VK_IMPORT_DEVICE_FUNC(true,  vkGetSwapchainImagesKHR);          \
			VK_IMPORT_DEVICE_FUNC(true,  vkAcquireNextImageKHR);            \
			VK_IMPORT_DEVICE_FUNC(true,  vkQueuePresentKHR);                \
			/* VK_EXT_debug_utils */                                        \
			VK_IMPORT_DEVICE_FUNC(true,  vkSetDebugUtilsObjectNameEXT);     \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdBeginDebugUtilsLabelEXT);     \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdEndDebugUtilsLabelEXT);       \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdInsertDebugUtilsLabelEXT);    \
			/* VK_KHR_draw_indirect_count */                                \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdDrawIndirectCountKHR);        \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdDrawIndexedIndirectCountKHR); \

#define VK_DESTROY                                \
			VK_DESTROY_FUNC(Buffer);              \
			VK_DESTROY_FUNC(CommandPool);         \
			VK_DESTROY_FUNC(DescriptorPool);      \
			VK_DESTROY_FUNC(DescriptorSetLayout); \
			VK_DESTROY_FUNC(Fence);               \
			VK_DESTROY_FUNC(Framebuffer);         \
			VK_DESTROY_FUNC(Image);               \
			VK_DESTROY_FUNC(ImageView);           \
			VK_DESTROY_FUNC(Pipeline);            \
			VK_DESTROY_FUNC(PipelineCache);       \
			VK_DESTROY_FUNC(PipelineLayout);      \
			VK_DESTROY_FUNC(QueryPool);           \
			VK_DESTROY_FUNC(RenderPass);          \
			VK_DESTROY_FUNC(Sampler);             \
			VK_DESTROY_FUNC(Semaphore);           \
			VK_DESTROY_FUNC(ShaderModule);        \
			VK_DESTROY_FUNC(SwapchainKHR);        \

#define _VK_CHECK(_check, _call)                                                                                \
				BX_MACRO_BLOCK_BEGIN                                                                            \
					/*BX_TRACE(#_call);*/                                                                       \
					VkResult vkresult = _call;                                                                  \
					_check(VK_SUCCESS == vkresult, #_call "; VK error 0x%x: %s", vkresult, getName(vkresult) ); \
				BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define VK_CHECK(_call) _VK_CHECK(BX_ASSERT, _call)
#else
#	define VK_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG_ANNOTATION
#	define BGFX_VK_BEGIN_DEBUG_UTILS_LABEL(_name, _abgr)         \
		BX_MACRO_BLOCK_BEGIN                                     \
			VkDebugUtilsLabelEXT dul;                            \
			dul.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT; \
			dul.pNext = NULL;                                    \
			dul.pLabelName = _name;                              \
			dul.color[0] = ((_abgr >> 24) & 0xff) / 255.0f;      \
			dul.color[1] = ((_abgr >> 16) & 0xff) / 255.0f;      \
			dul.color[2] = ((_abgr >> 8)  & 0xff) / 255.0f;      \
			dul.color[3] = ((_abgr >> 0)  & 0xff) / 255.0f;      \
			vkCmdBeginDebugUtilsLabelEXT(m_commandBuffer, &dul); \
		BX_MACRO_BLOCK_END

#	define BGFX_VK_END_DEBUG_UTILS_LABEL()               \
		BX_MACRO_BLOCK_BEGIN                             \
			vkCmdEndDebugUtilsLabelEXT(m_commandBuffer); \
		BX_MACRO_BLOCK_END
#else
#	define BGFX_VK_BEGIN_DEBUG_UTILS_LABEL(_view, _abgr) BX_UNUSED(_view, _abgr)
#	define BGFX_VK_END_DEBUG_UTILS_LABEL() BX_NOOP()
#endif // BGFX_CONFIG_DEBUG_ANNOTATION

#define BGFX_VK_PROFILER_BEGIN(_view, _abgr)                      \
	BX_MACRO_BLOCK_BEGIN                                          \
		BGFX_VK_BEGIN_DEBUG_UTILS_LABEL(s_viewName[view], _abgr); \
		BGFX_PROFILER_BEGIN(s_viewName[view], _abgr);             \
	BX_MACRO_BLOCK_END

#define BGFX_VK_PROFILER_BEGIN_LITERAL(_name, _abgr)   \
	BX_MACRO_BLOCK_BEGIN                               \
		BGFX_VK_BEGIN_DEBUG_UTILS_LABEL(_name, _abgr); \
		BGFX_PROFILER_BEGIN_LITERAL("" _name, _abgr);  \
	BX_MACRO_BLOCK_END

#define BGFX_VK_PROFILER_END()           \
	BX_MACRO_BLOCK_BEGIN                 \
		BGFX_PROFILER_END();             \
		BGFX_VK_END_DEBUG_UTILS_LABEL(); \
	BX_MACRO_BLOCK_END

namespace bgfx { namespace vk
{

#define VK_DESTROY_FUNC(_name)                                   \
	struct Vk##_name                                             \
	{                                                            \
		::Vk##_name vk;                                          \
		Vk##_name() {}                                           \
		Vk##_name(::Vk##_name _vk) : vk(_vk) {}                  \
		operator ::Vk##_name() { return vk; }                    \
		operator ::Vk##_name() const { return vk; }              \
		::Vk##_name* operator &() { return &vk; }                \
		const ::Vk##_name* operator &() const { return &vk; }    \
	};                                                           \
	BX_STATIC_ASSERT(sizeof(::Vk##_name) == sizeof(Vk##_name) ); \
	void vkDestroy(Vk##_name&);                                  \
	void release(Vk##_name&)
VK_DESTROY
VK_DESTROY_FUNC(DeviceMemory);
VK_DESTROY_FUNC(SurfaceKHR);
VK_DESTROY_FUNC(DescriptorSet);
#undef VK_DESTROY_FUNC

	template<typename Ty>
	void release(Ty)
	{
	}

	template<typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _key, Ty _value)
		{
			invalidate(_key);
			m_hashMap.insert(stl::make_pair(_key, _value) );
		}

		Ty find(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return 0;
		}

		void invalidate(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				release(it->second);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				release(it->second);
			}

			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint64_t, Ty> HashMap;
		HashMap m_hashMap;
	};

	struct StagingBufferVK
	{
		VkBuffer m_buffer;
		VkDeviceMemory m_deviceMem;

		uint8_t* m_data;
		uint32_t m_size;
		uint32_t m_offset;
		bool     m_isFromScratch;
	};

	class ScratchBufferVK
	{
	public:
		ScratchBufferVK()
		{
		}

		~ScratchBufferVK()
		{
		}

		void create(uint32_t _size, uint32_t _count, VkBufferUsageFlags _usage, uint32_t align);
		void createUniform(uint32_t _size, uint32_t _count);
		void createStaging(uint32_t _size);
		void destroy();
		void reset();
		uint32_t alloc(uint32_t _size, uint32_t _minAlign = 1);
		uint32_t write(const void* _data, uint32_t _size, uint32_t _minAlign = 1);
		void flush();

		VkBuffer m_buffer;
		VkDeviceMemory m_deviceMem;

		uint8_t* m_data;
		uint32_t m_size;
		uint32_t m_pos;
		uint32_t m_align;
	};

	struct BufferVK
	{
		BufferVK()
			: m_buffer(VK_NULL_HANDLE)
			, m_deviceMem(VK_NULL_HANDLE)
			, m_size(0)
			, m_flags(BGFX_BUFFER_NONE)
			, m_dynamic(false)
		{
		}

		void create(VkCommandBuffer _commandBuffer, uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride = 0);
		void update(VkCommandBuffer _commandBuffer, uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);
		void destroy();

		VkBuffer m_buffer;
		VkDeviceMemory m_deviceMem;
		uint32_t m_size;
		uint16_t m_flags;
		bool m_dynamic;
	};

	typedef BufferVK IndexBufferVK;

	struct MsaaSamplerVK
	{
		uint16_t Count;
		VkSampleCountFlagBits Sample;
	};

	struct VertexBufferVK : public BufferVK
	{
		void create(VkCommandBuffer _commandBuffer, uint32_t _size, void* _data, VertexLayoutHandle _layoutHandle, uint16_t _flags);

		VertexLayoutHandle m_layoutHandle;
	};

	struct BindType
	{
		enum Enum
		{
			Buffer,
			Image,
			Sampler,

			Count
		};
	};

	struct BindInfo
	{
		UniformHandle uniformHandle = BGFX_INVALID_HANDLE;
		BindType::Enum type;
		uint32_t binding;
		uint32_t samplerBinding;
		uint32_t index;
	};

	struct TextureBindInfo
	{
		VkImageViewType type;
	};

	struct ShaderVK
	{
		ShaderVK()
			: m_code(NULL)
			, m_module(VK_NULL_HANDLE)
			, m_constantBuffer(NULL)
			, m_hash(0)
			, m_numUniforms(0)
			, m_numPredefined(0)
			, m_uniformBinding(0)
			, m_numBindings(0)
			, m_oldBindingModel(false)
		{
		}

		void create(const Memory* _mem);
		void destroy();

		const Memory* m_code;
		VkShaderModule m_module;
		UniformBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];
		uint8_t m_attrRemap[Attrib::Count];

		uint32_t m_hash;
		uint16_t m_numUniforms;
		uint16_t m_size;
		uint8_t m_numPredefined;
		uint8_t m_numAttrs;

		BindInfo m_bindInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		TextureBindInfo m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint8_t m_numTextures;

		uint32_t m_uniformBinding;
		uint16_t m_numBindings;
		VkDescriptorSetLayoutBinding m_bindings[2 * BGFX_CONFIG_MAX_TEXTURE_SAMPLERS + 1];

		bool m_oldBindingModel;
	};

	struct ProgramVK
	{
		ProgramVK()
			: m_vsh(NULL)
			, m_fsh(NULL)
			, m_descriptorSetLayout(VK_NULL_HANDLE)
			, m_pipelineLayout(VK_NULL_HANDLE)
		{
		}

		void create(const ShaderVK* _vsh, const ShaderVK* _fsh);
		void destroy();

		const ShaderVK* m_vsh;
		const ShaderVK* m_fsh;

		BindInfo m_bindInfo[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];

		TextureBindInfo m_textures[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint8_t m_numTextures;

		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		uint8_t m_numPredefined;

		VkDescriptorSetLayout m_descriptorSetLayout;
		VkPipelineLayout m_pipelineLayout;
	};

	struct TimerQueryVK
	{
		TimerQueryVK()
			: m_control(BX_COUNTOF(m_query) )
		{
		}

		VkResult init();
		void shutdown();
		uint32_t begin(uint32_t _resultIdx, uint32_t _frameNum);
		void end(uint32_t _idx);
		bool update();

		struct Result
		{
			void reset()
			{
				m_begin    = 0;
				m_end      = 0;
				m_pending  = 0;
				m_frameNum = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
			uint32_t m_frameNum;
		};

		struct Query
		{
			uint32_t m_resultIdx;
			uint32_t m_frameNum;
			uint64_t m_completed;
			bool     m_ready;
		};

		uint64_t m_frequency;

		Result m_result[BGFX_CONFIG_MAX_VIEWS+1];
		Query m_query[BGFX_CONFIG_MAX_VIEWS*4];

		VkBuffer m_readback;
		VkDeviceMemory m_readbackMemory;
		VkQueryPool m_queryPool;
		const uint64_t* m_queryResult;
		bx::RingBufferControl m_control;
	};

	struct OcclusionQueryVK
	{
		OcclusionQueryVK()
			: m_control(BX_COUNTOF(m_handle) )
		{
		}

		VkResult init();
		void shutdown();
		void begin(OcclusionQueryHandle _handle);
		void end();
		void flush(Frame* _render);
		void resolve(Frame* _render);
		void invalidate(OcclusionQueryHandle _handle);

		OcclusionQueryHandle m_handle[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];

		VkBuffer m_readback;
		VkDeviceMemory m_readbackMemory;
		VkQueryPool m_queryPool;
		const uint32_t* m_queryResult;
		bx::RingBufferControl m_control;
	};

	struct ReadbackVK
	{
		void create(VkImage _image, uint32_t _width, uint32_t _height, TextureFormat::Enum _format);
		void destroy();
		uint32_t pitch(uint8_t _mip = 0) const;
		void copyImageToBuffer(VkCommandBuffer _commandBuffer, VkBuffer _buffer, VkImageLayout _layout, VkImageAspectFlags _aspect, uint8_t _mip = 0) const;
		void readback(VkDeviceMemory _memory, VkDeviceSize _offset, void* _data, uint8_t _mip = 0) const;

		VkImage  m_image;
		uint32_t m_width;
		uint32_t m_height;
		TextureFormat::Enum  m_format;
	};

	struct TextureVK
	{
		TextureVK()
			: m_directAccessPtr(NULL)
			, m_sampler({ 1, VK_SAMPLE_COUNT_1_BIT })
			, m_format(VK_FORMAT_UNDEFINED)
			, m_textureImage(VK_NULL_HANDLE)
			, m_textureDeviceMem(VK_NULL_HANDLE)
			, m_currentImageLayout(VK_IMAGE_LAYOUT_UNDEFINED)
			, m_singleMsaaImage(VK_NULL_HANDLE)
			, m_singleMsaaDeviceMem(VK_NULL_HANDLE)
			, m_currentSingleMsaaImageLayout(VK_IMAGE_LAYOUT_UNDEFINED)
		{
		}

		void* create(VkCommandBuffer _commandBuffer, const Memory* _mem, uint64_t _flags, uint8_t _skip);
		// internal render target
		VkResult create(VkCommandBuffer _commandBuffer, uint32_t _width, uint32_t _height, uint64_t _flags, VkFormat _format);

		void destroy();

		void update(VkCommandBuffer _commandBuffer, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void resolve(VkCommandBuffer _commandBuffer, uint8_t _resolve, uint32_t _layer, uint32_t _numLayers, uint32_t _mip);

		void copyBufferToTexture(VkCommandBuffer _commandBuffer, VkBuffer _stagingBuffer, uint32_t _bufferImageCopyCount, VkBufferImageCopy* _bufferImageCopy);
		VkImageLayout setImageMemoryBarrier(VkCommandBuffer _commandBuffer, VkImageLayout _newImageLayout, bool _singleMsaaImage = false);

		VkResult createView(uint32_t _layer, uint32_t _numLayers, uint32_t _mip, uint32_t _numMips, VkImageViewType _type, VkImageAspectFlags _aspectMask, bool _renderTarget, ::VkImageView* _view) const;

		void*    m_directAccessPtr;
		uint64_t m_flags;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint32_t m_numLayers;
		uint32_t m_numSides;
		uint8_t  m_requestedFormat;
		uint8_t  m_textureFormat;
		uint8_t  m_numMips;

		MsaaSamplerVK m_sampler;

		VkImageViewType    m_type;
		VkFormat           m_format;
		VkComponentMapping m_components;
		VkImageAspectFlags m_aspectMask;

		VkImage        m_textureImage;
		VkDeviceMemory m_textureDeviceMem;
		VkImageLayout  m_currentImageLayout;

		VkImage        m_singleMsaaImage;
		VkDeviceMemory m_singleMsaaDeviceMem;
		VkImageLayout  m_currentSingleMsaaImageLayout;

		VkImageLayout m_sampledLayout;

		ReadbackVK m_readback;

	private:
		VkResult createImages(VkCommandBuffer _commandBuffer);
		static VkImageAspectFlags getAspectMask(VkFormat _format);
	};

	constexpr uint32_t kMaxBackBuffers = bx::max(BGFX_CONFIG_MAX_BACK_BUFFERS, 10);

	struct SwapChainVK
	{
		SwapChainVK()
			: m_nwh(NULL)
			, m_swapChain(VK_NULL_HANDLE)
			, m_lastImageRenderedSemaphore(VK_NULL_HANDLE)
			, m_lastImageAcquiredSemaphore(VK_NULL_HANDLE)
			, m_backBufferColorMsaaImageView(VK_NULL_HANDLE)
		{
		}

		VkResult create(VkCommandBuffer _commandBuffer, void* _nwh, const Resolution& _resolution, TextureFormat::Enum _depthFormat = TextureFormat::Count);

		void destroy();

		void update(VkCommandBuffer _commandBuffer, void* _nwh, const Resolution& _resolution);

		VkResult createSurface();
		VkResult createSwapChain();
		VkResult createAttachments(VkCommandBuffer _commandBuffer);
		VkResult createFrameBuffer();

		void releaseSurface();
		void releaseSwapChain();
		void releaseAttachments();
		void releaseFrameBuffer();

		uint32_t findPresentMode(bool _vsync);
		TextureFormat::Enum findSurfaceFormat(TextureFormat::Enum _format, VkColorSpaceKHR _colorSpace, bool _srgb);

		bool acquire(VkCommandBuffer _commandBuffer);
		void present();

		void transitionImage(VkCommandBuffer _commandBuffer);

		VkQueue m_queue;
		VkSwapchainCreateInfoKHR m_sci;

		void* m_nwh;
		Resolution m_resolution;

		TextureFormat::Enum m_colorFormat;
		TextureFormat::Enum m_depthFormat;

		VkSurfaceKHR   m_surface;
		VkSwapchainKHR m_swapChain;
		uint32_t       m_numSwapChainImages;
		VkImageLayout  m_backBufferColorImageLayout[kMaxBackBuffers];
		VkImage        m_backBufferColorImage[kMaxBackBuffers];
		VkImageView    m_backBufferColorImageView[kMaxBackBuffers];
		VkFramebuffer  m_backBufferFrameBuffer[kMaxBackBuffers];
		VkFence        m_backBufferFence[kMaxBackBuffers];
		uint32_t       m_backBufferColorIdx;

		VkSemaphore m_presentDoneSemaphore[kMaxBackBuffers];
		VkSemaphore m_renderDoneSemaphore[kMaxBackBuffers];
		uint32_t    m_currentSemaphore;

		VkSemaphore m_lastImageRenderedSemaphore;
		VkSemaphore m_lastImageAcquiredSemaphore;

		bool m_needPresent;
		bool m_needToRefreshSwapchain;
		bool m_needToRecreateSurface;

		TextureVK   m_backBufferDepthStencil;
		VkImageView m_backBufferDepthStencilImageView;

		TextureVK     m_backBufferColorMsaa;
		VkImageView   m_backBufferColorMsaaImageView;
		MsaaSamplerVK m_sampler;

		bool m_supportsReadback;
		bool m_supportsManualResolve;
	};

	struct FrameBufferVK
	{
		FrameBufferVK()
			: m_depth({ kInvalidHandle })
			, m_width(0)
			, m_height(0)
			, m_denseIdx(kInvalidHandle)
			, m_num(0)
			, m_numTh(0)
			, m_nwh(NULL)
			, m_needPresent(false)
			, m_framebuffer(VK_NULL_HANDLE)
		{
		}

		void create(uint8_t _num, const Attachment* _attachment);
		VkResult create(uint16_t _denseIdx, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format = TextureFormat::Count, TextureFormat::Enum _depthFormat = TextureFormat::Count);
		uint16_t destroy();

		void update(VkCommandBuffer _commandBuffer, const Resolution& _resolution);

		void preReset();
		void postReset();

		void resolve();

		bool acquire(VkCommandBuffer _commandBuffer);
		void present();

		bool isRenderable() const;

		TextureHandle m_texture[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		TextureHandle m_depth;
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];

		SwapChainVK m_swapChain;
		void* m_nwh;
		bool m_needPresent;
		bool m_needResolve;

		VkImageView m_textureImageViews[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		VkFramebuffer m_framebuffer;
		VkRenderPass m_renderPass;
		MsaaSamplerVK m_sampler;

		VkFramebuffer m_currentFramebuffer;
	};

	struct CommandQueueVK
	{
		VkResult init(uint32_t _queueFamily, VkQueue _queue, uint32_t _numFramesInFlight);
		VkResult reset();
		void shutdown();

		VkResult alloc(VkCommandBuffer* _commandBuffer);
		void addWaitSemaphore(VkSemaphore _semaphore, VkPipelineStageFlags _waitFlags = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
		void addSignalSemaphore(VkSemaphore _semaphore);
		void kick(bool _wait = false);
		void finish(bool _finishAll = false);

		void release(uint64_t _handle, VkObjectType _type);
		void consume();

		uint32_t m_queueFamily;
		VkQueue m_queue;

		uint32_t m_numFramesInFlight;

		uint32_t m_currentFrameInFlight;
		uint32_t m_consumeIndex;

		VkCommandBuffer m_activeCommandBuffer;

		VkFence m_currentFence;
		VkFence m_completedFence;

		uint64_t m_submitted;

		struct CommandList
		{
			VkCommandPool m_commandPool = VK_NULL_HANDLE;
			VkCommandBuffer m_commandBuffer = VK_NULL_HANDLE;
			VkFence m_fence = VK_NULL_HANDLE;
		};

		CommandList m_commandList[BGFX_CONFIG_MAX_FRAME_LATENCY];

		uint32_t             m_numWaitSemaphores;
		VkSemaphore          m_waitSemaphores[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		VkPipelineStageFlags m_waitSemaphoreStages[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		uint32_t             m_numSignalSemaphores;
		VkSemaphore          m_signalSemaphores[BGFX_CONFIG_MAX_FRAME_BUFFERS];

		struct Resource
		{
			VkObjectType m_type;
			uint64_t m_handle;
		};

		typedef stl::vector<Resource> ResourceArray;
		ResourceArray m_release[BGFX_CONFIG_MAX_FRAME_LATENCY];

	private:
		template<typename Ty>
		void destroy(uint64_t _handle)
		{
			typedef decltype(Ty::vk) vk_t;
			Ty obj = vk_t(_handle);
			vkDestroy(obj);
		}
	};

} /* namespace bgfx */ } // namespace vk

#endif // BGFX_RENDERER_VK_H_HEADER_GUARD
