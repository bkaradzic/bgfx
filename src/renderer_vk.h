/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_VK_H_HEADER_GUARD
#define BGFX_RENDERER_VK_H_HEADER_GUARD

#if BX_PLATFORM_ANDROID
#	define VK_USE_PLATFORM_ANDROID_KHR
#	define KHR_SURFACE_EXTENSION_NAME VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_ANDROID
#elif BX_PLATFORM_LINUX
//#	define VK_USE_PLATFORM_MIR_KHR
#	define VK_USE_PLATFORM_XLIB_KHR
#	define VK_USE_PLATFORM_XCB_KHR
//#	define VK_USE_PLATFORM_WAYLAND_KHR
#	define KHR_SURFACE_EXTENSION_NAME VK_KHR_XCB_SURFACE_EXTENSION_NAME
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_LINUX
#elif BX_PLATFORM_WINDOWS
#	define VK_USE_PLATFORM_WIN32_KHR
#	define KHR_SURFACE_EXTENSION_NAME  VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#	define VK_IMPORT_INSTANCE_PLATFORM VK_IMPORT_INSTANCE_WINDOWS
#else
#	define KHR_SURFACE_EXTENSION_NAME ""
#	define VK_IMPORT_INSTANCE_PLATFORM
#endif // BX_PLATFORM_*

#define VK_NO_STDINT_H
#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>
#include "renderer.h"
#include "debug_renderdoc.h"

#define VK_IMPORT \
			VK_IMPORT_FUNC(false, vkCreateInstance); \
			VK_IMPORT_FUNC(false, vkGetInstanceProcAddr); \
			VK_IMPORT_FUNC(false, vkGetDeviceProcAddr); \
			VK_IMPORT_FUNC(false, vkEnumerateInstanceExtensionProperties); \
			VK_IMPORT_FUNC(false, vkEnumerateInstanceLayerProperties); \

#define VK_IMPORT_INSTANCE_ANDROID \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateAndroidSurfaceKHR);

#define VK_IMPORT_INSTANCE_LINUX \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateXlibSurfaceKHR); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceXlibPresentationSupportKHR); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateXcbSurfaceKHR); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceXcbPresentationSupportKHR); \

//			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateWaylandSurfaceKHR);
//			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceWaylandPresentationSupportKHR);
//			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateMirSurfaceKHR);
//			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceMirPresentationSupportKHR);

#define VK_IMPORT_INSTANCE_WINDOWS \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateWin32SurfaceKHR); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkGetPhysicalDeviceWin32PresentationSupportKHR);

#define VK_IMPORT_INSTANCE \
			VK_IMPORT_INSTANCE_FUNC(false, vkDestroyInstance); \
			VK_IMPORT_INSTANCE_FUNC(false, vkEnumeratePhysicalDevices); \
			VK_IMPORT_INSTANCE_FUNC(false, vkEnumerateDeviceExtensionProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkEnumerateDeviceLayerProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceFormatProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceImageFormatProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceMemoryProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceQueueFamilyProperties); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceSurfaceCapabilitiesKHR); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceSurfaceFormatsKHR); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceSurfacePresentModesKHR); \
			VK_IMPORT_INSTANCE_FUNC(false, vkGetPhysicalDeviceSurfaceSupportKHR); \
			VK_IMPORT_INSTANCE_FUNC(false, vkCreateDevice); \
			VK_IMPORT_INSTANCE_FUNC(false, vkDestroyDevice); \
			VK_IMPORT_INSTANCE_FUNC(false, vkDestroySurfaceKHR); \
			/* VK_EXT_debug_report */ \
			VK_IMPORT_INSTANCE_FUNC(true,  vkCreateDebugReportCallbackEXT); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkDestroyDebugReportCallbackEXT); \
			VK_IMPORT_INSTANCE_FUNC(true,  vkDebugReportMessageEXT); \
			VK_IMPORT_INSTANCE_PLATFORM

#define VK_IMPORT_DEVICE \
			VK_IMPORT_DEVICE_FUNC(false, vkGetDeviceQueue); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateSwapchainKHR); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroySwapchainKHR); \
			VK_IMPORT_DEVICE_FUNC(false, vkGetSwapchainImagesKHR); \
			VK_IMPORT_DEVICE_FUNC(false, vkAcquireNextImageKHR); \
			VK_IMPORT_DEVICE_FUNC(false, vkQueuePresentKHR); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateFence); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyFence); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateSemaphore); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroySemaphore); \
			VK_IMPORT_DEVICE_FUNC(false, vkResetFences); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateCommandPool); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyCommandPool); \
			VK_IMPORT_DEVICE_FUNC(false, vkResetCommandPool); \
			VK_IMPORT_DEVICE_FUNC(false, vkAllocateCommandBuffers); \
			VK_IMPORT_DEVICE_FUNC(false, vkFreeCommandBuffers); \
			VK_IMPORT_DEVICE_FUNC(false, vkGetBufferMemoryRequirements); \
			VK_IMPORT_DEVICE_FUNC(false, vkGetImageMemoryRequirements); \
			VK_IMPORT_DEVICE_FUNC(false, vkAllocateMemory); \
			VK_IMPORT_DEVICE_FUNC(false, vkFreeMemory); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateImage); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyImage); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateImageView); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyImageView); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateBuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyBuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateFramebuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyFramebuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateRenderPass); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyRenderPass); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateShaderModule); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyShaderModule); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreatePipelineCache); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyPipelineCache); \
			VK_IMPORT_DEVICE_FUNC(false, vkGetPipelineCacheData); \
			VK_IMPORT_DEVICE_FUNC(false, vkMergePipelineCaches); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateGraphicsPipelines); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateComputePipelines); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyPipeline); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreatePipelineLayout); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyPipelineLayout); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateSampler); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroySampler); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateDescriptorSetLayout); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyDescriptorSetLayout); \
			VK_IMPORT_DEVICE_FUNC(false, vkCreateDescriptorPool); \
			VK_IMPORT_DEVICE_FUNC(false, vkDestroyDescriptorPool); \
			VK_IMPORT_DEVICE_FUNC(false, vkResetDescriptorPool); \
			VK_IMPORT_DEVICE_FUNC(false, vkAllocateDescriptorSets); \
			VK_IMPORT_DEVICE_FUNC(false, vkFreeDescriptorSets); \
			VK_IMPORT_DEVICE_FUNC(false, vkUpdateDescriptorSets); \
			VK_IMPORT_DEVICE_FUNC(false, vkQueueSubmit); \
			VK_IMPORT_DEVICE_FUNC(false, vkQueueWaitIdle); \
			VK_IMPORT_DEVICE_FUNC(false, vkDeviceWaitIdle); \
			VK_IMPORT_DEVICE_FUNC(false, vkWaitForFences); \
			VK_IMPORT_DEVICE_FUNC(false, vkBeginCommandBuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkEndCommandBuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdPipelineBarrier); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBeginRenderPass); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdEndRenderPass); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetViewport); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDraw); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDrawIndexed); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDrawIndirect); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDrawIndexedIndirect); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDispatch); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdDispatchIndirect); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindPipeline); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetStencilReference); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetBlendConstants); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdSetScissor); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindDescriptorSets); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindIndexBuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdBindVertexBuffers); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdUpdateBuffer); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdClearColorImage); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdClearDepthStencilImage); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdClearAttachments); \
			VK_IMPORT_DEVICE_FUNC(false, vkCmdResolveImage); \
			VK_IMPORT_DEVICE_FUNC(false, vkMapMemory); \
			VK_IMPORT_DEVICE_FUNC(false, vkUnmapMemory); \
			VK_IMPORT_DEVICE_FUNC(false, vkFlushMappedMemoryRanges); \
			VK_IMPORT_DEVICE_FUNC(false, vkInvalidateMappedMemoryRanges); \
			VK_IMPORT_DEVICE_FUNC(false, vkBindBufferMemory); \
			VK_IMPORT_DEVICE_FUNC(false, vkBindImageMemory); \
			/* VK_EXT_debug_marker */ \
			VK_IMPORT_DEVICE_FUNC(true,  vkDebugMarkerSetObjectTagEXT); \
			VK_IMPORT_DEVICE_FUNC(true,  vkDebugMarkerSetObjectNameEXT); \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdDebugMarkerBeginEXT); \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdDebugMarkerEndEXT); \
			VK_IMPORT_DEVICE_FUNC(true,  vkCmdDebugMarkerInsertEXT); \

#define VK_DESTROY \
			VK_DESTROY_FUNC(Buffer); \
			VK_DESTROY_FUNC(CommandPool); \
			VK_DESTROY_FUNC(DescriptorPool); \
			VK_DESTROY_FUNC(DescriptorSetLayout); \
			VK_DESTROY_FUNC(Fence); \
			VK_DESTROY_FUNC(Framebuffer); \
			VK_DESTROY_FUNC(Image); \
			VK_DESTROY_FUNC(ImageView); \
			VK_DESTROY_FUNC(Pipeline); \
			VK_DESTROY_FUNC(PipelineCache); \
			VK_DESTROY_FUNC(PipelineLayout); \
			VK_DESTROY_FUNC(RenderPass); \
			VK_DESTROY_FUNC(Semaphore); \
			VK_DESTROY_FUNC(ShaderModule); \
			VK_DESTROY_FUNC(SwapchainKHR); \

#define _VK_CHECK(_check, _call) \
				BX_MACRO_BLOCK_BEGIN \
					/*BX_TRACE(#_call);*/ \
					VkResult vkresult = _call; \
					_check(VK_SUCCESS == vkresult, #_call "; VK error 0x%x: %s", vkresult, getName(vkresult) ); \
				BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define VK_CHECK(_call) _VK_CHECK(BX_CHECK, _call)
#else
#	define VK_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

namespace bgfx { namespace vk
{
#define VK_DESTROY_FUNC(_name) \
			struct Vk##_name \
			{ \
				::Vk##_name vk; \
				Vk##_name() {} \
				Vk##_name(::Vk##_name _vk) : vk(_vk) {} \
				operator ::Vk##_name() { return vk; } \
				operator ::Vk##_name() const { return vk; } \
				::Vk##_name* operator &() { return &vk; } \
				const ::Vk##_name* operator &() const { return &vk; } \
			}; \
			BX_STATIC_ASSERT(sizeof(::Vk##_name) == sizeof(Vk##_name) ); \
			void vkDestroy(Vk##_name&)
VK_DESTROY
#undef VK_DESTROY_FUNC

	struct DslBinding
	{
		enum Enum
		{
//			CombinedImageSampler,
			UniformBuffer,
//			StorageBuffer,

			Count
		};
	};

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
				vkDestroy(it->second);
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				vkDestroy(it->second);
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

	class ScratchBufferVK
	{
	public:
		ScratchBufferVK()
		{
		}

		~ScratchBufferVK()
		{
		}

		void create(uint32_t _size, uint32_t _maxDescriptors);
		void destroy();
		void reset(VkDescriptorBufferInfo& _gpuAddress);
		void* allocUbv(VkDescriptorBufferInfo& _gpuAddress, uint32_t _size);

		VkDescriptorSet* m_descriptorSet;
		VkBuffer m_buffer;
		VkDeviceMemory m_deviceMem;
		uint8_t* m_data;
		uint32_t m_size;
		uint32_t m_pos;
		uint32_t m_currentDs;
		uint32_t m_maxDescriptors;
	};

	struct ImageVK
	{
		ImageVK()
			: m_memory(VK_NULL_HANDLE)
			, m_image(VK_NULL_HANDLE)
			, m_imageView(VK_NULL_HANDLE)
		{
		}

		VkResult create(VkFormat _format, const VkExtent3D& _extent);
		void destroy();

		VkDeviceMemory m_memory;
		VkImage        m_image;
		VkImageView    m_imageView;
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

		void create(uint32_t _size, void* _data, uint16_t _flags, bool _vertex, uint32_t _stride = 0);
		void update(VkCommandBuffer _commandBuffer, uint32_t _offset, uint32_t _size, void* _data, bool _discard = false);
		void destroy();

		VkBuffer m_buffer;
		VkDeviceMemory m_deviceMem;
		uint32_t m_size;
		uint16_t m_flags;
		bool m_dynamic;
	};

	typedef BufferVK IndexBufferVK;

	struct VertexBufferVK : public BufferVK
	{
		void create(uint32_t _size, void* _data, VertexDeclHandle _declHandle, uint16_t _flags);

		VertexDeclHandle m_decl;
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
		{
		}

		void create(const Memory* _mem);
		void destroy();

		const Memory* m_code;
		VkShaderModule m_module;
		UniformBuffer* m_constantBuffer;

		PredefinedUniform m_predefined[PredefinedUniform::Count];
		uint16_t m_attrMask[Attrib::Count];

		uint32_t m_hash;
		uint16_t m_numUniforms;
		uint16_t m_size;
		uint8_t m_numPredefined;
	};

	struct ProgramVK
	{
		ProgramVK()
			: m_vsh(NULL)
			, m_fsh(NULL)
		{
		}

		void create(const ShaderVK* _vsh, const ShaderVK* _fsh)
		{
			BX_CHECK(NULL != _vsh->m_code, "Vertex shader doesn't exist.");
			m_vsh = _vsh;
			bx::memCopy(&m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined*sizeof(PredefinedUniform));
			m_numPredefined = _vsh->m_numPredefined;

			if (NULL != _fsh)
			{
				BX_CHECK(NULL != _fsh->m_code, "Fragment shader doesn't exist.");
				m_fsh = _fsh;
				bx::memCopy(&m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined*sizeof(PredefinedUniform));
				m_numPredefined += _fsh->m_numPredefined;
			}
		}

		void destroy()
		{
			m_numPredefined = 0;
			m_vsh = NULL;
			m_fsh = NULL;
		}

		const ShaderVK* m_vsh;
		const ShaderVK* m_fsh;

		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		uint8_t m_numPredefined;
	};

	struct TextureVK
	{
		void destroy();
	};

	struct FrameBufferVK
	{
		void destroy();

		TextureHandle m_texture[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		TextureHandle m_depth;
//		IDXGISwapChain* m_swapChain;
		uint32_t m_width;
		uint32_t m_height;
		uint16_t m_denseIdx;
		uint8_t m_num;
		uint8_t m_numTh;
		Attachment m_attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
	};

} /* namespace bgfx */ } // namespace vk

#endif // BGFX_RENDERER_VK_H_HEADER_GUARD
