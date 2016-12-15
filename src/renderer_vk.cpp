/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"
#include "debug_renderdoc.h"

#if BX_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

namespace bgfx { namespace vk
{
#	define VK_IMPORT_INSTANCE(_func) PFN_##_func _func = NULL
#	define VK_IMPORT_DEVICE(_func) PFN_##_func _func = NULL
#	include "vkimports.h"

#if BX_PLATFORM_WINDOWS
	static const char * VULKAN_LIBRARY_NAME = "vulkan-1." BX_DL_EXT;
#else
	static const char * VULKAN_LIBRARY_NAME = "libvulkan." BX_DL_EXT;
#endif

	static const int VULKAN_ALIGNMENT = 16;
	static const int VULKAN_MAX_DEVICES = 8;
	static const int VULKAN_MAX_SURFACE_FORMATS = 32;
	static const int VULKAN_MAX_SURFACE_PRESENT_MODES = 4;
	static const int VULKAN_MAX_SWAP_IMAGES = 4;
	static const int VULKAN_MAX_QUEUE_FAMILIES = 4;

	void* VKAPI_PTR AllocationFunction(void* pUserData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
	{
		BX_UNUSED(pUserData, allocationScope);
		if (alignment > VULKAN_ALIGNMENT)
		{
			// FIXME: There's no way to pass the alignment to the free function
			// So we can't really do aligned allocations
			BX_CHECK(false, "Aligned allocation larger than supported size");
			return NULL;
		}
		return BX_ALIGNED_ALLOC(g_allocator, size, VULKAN_ALIGNMENT);
	}

	void* VKAPI_PTR ReallocationFunction(void* pUserData, void* pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
	{
		BX_UNUSED(pUserData, allocationScope);
		if (alignment > VULKAN_ALIGNMENT)
		{
			// FIXME: There's no way to pass the alignment to the free function
			// So we can't really do aligned allocations
			BX_CHECK(false, "Aligned allocation larger than supported size");
			return NULL;
		}
		return BX_ALIGNED_REALLOC(g_allocator, pOriginal, size, VULKAN_ALIGNMENT);
	}

	void VKAPI_PTR FreeFunction(void* pUserData, void* pMemory)
	{
		BX_UNUSED(pUserData);
		BX_ALIGNED_FREE(g_allocator, pMemory, VULKAN_ALIGNMENT);
	}

	void VKAPI_PTR InternalAllocationNotification(void* pUserData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope)
	{
		BX_UNUSED(pUserData, size, allocationType, allocationScope);
	}

	void VKAPI_PTR InternalFreeNotification(void* pUserData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope)
	{
		BX_UNUSED(pUserData, size, allocationType, allocationScope);
	}

	static const VkAllocationCallbacks s_allocationCallbacks =
	{
		NULL,
		AllocationFunction,
		ReallocationFunction,
		FreeFunction,
		InternalAllocationNotification,
		InternalFreeNotification
	};

	struct TextureFormatInfo
	{
		VkFormat format;
		VkFormat srgbFormat;
	};

	static TextureFormatInfo s_textureFormat[] =
	{
		{ VK_FORMAT_BC1_RGB_UNORM_BLOCK,       VK_FORMAT_BC1_RGB_SRGB_BLOCK       }, // BC1
		{ VK_FORMAT_BC2_UNORM_BLOCK,           VK_FORMAT_BC2_SRGB_BLOCK           }, // BC2
		{ VK_FORMAT_BC3_UNORM_BLOCK,           VK_FORMAT_BC3_SRGB_BLOCK           }, // BC3
		{ VK_FORMAT_BC4_UNORM_BLOCK,           VK_FORMAT_UNDEFINED                }, // BC4
		{ VK_FORMAT_BC5_UNORM_BLOCK,           VK_FORMAT_UNDEFINED                }, // BC5
		{ VK_FORMAT_BC6H_UFLOAT_BLOCK,         VK_FORMAT_UNDEFINED                }, // BC6H
		{ VK_FORMAT_BC7_UNORM_BLOCK,           VK_FORMAT_BC7_SRGB_BLOCK           }, // BC7
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // ETC1
		{ VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK,   VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK   }, // ETC2
		{ VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK, VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK }, // ETC2A
		{ VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK, VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK }, // ETC2A1
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // PTC12
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // PTC14
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // PTC12A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // PTC14A
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // PTC22
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // PTC24
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // Unknown
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // R1
		{ VK_FORMAT_R8_UNORM,                  VK_FORMAT_UNDEFINED                }, // A8
		{ VK_FORMAT_R8_UNORM,                  VK_FORMAT_R8_SRGB                  }, // R8
		{ VK_FORMAT_R8_SINT,                   VK_FORMAT_UNDEFINED                }, // R8I
		{ VK_FORMAT_R8_UINT,                   VK_FORMAT_UNDEFINED                }, // R8U
		{ VK_FORMAT_R8_SNORM,                  VK_FORMAT_UNDEFINED                }, // R8S
		{ VK_FORMAT_R16_UNORM,                 VK_FORMAT_UNDEFINED                }, // R16
		{ VK_FORMAT_R16_SINT,                  VK_FORMAT_UNDEFINED                }, // R16I
		{ VK_FORMAT_R16_UINT,                  VK_FORMAT_UNDEFINED                }, // R16U
		{ VK_FORMAT_R16_SFLOAT,                VK_FORMAT_UNDEFINED                }, // R16F
		{ VK_FORMAT_R16_SNORM,                 VK_FORMAT_UNDEFINED                }, // R16S
		{ VK_FORMAT_R32_SINT,                  VK_FORMAT_UNDEFINED                }, // R32I
		{ VK_FORMAT_R32_UINT,                  VK_FORMAT_UNDEFINED                }, // R32U
		{ VK_FORMAT_R32_SFLOAT,                VK_FORMAT_UNDEFINED                }, // R32F
		{ VK_FORMAT_R8G8_UNORM,                VK_FORMAT_R8G8_SRGB                }, // RG8
		{ VK_FORMAT_R8G8_SINT,                 VK_FORMAT_UNDEFINED                }, // RG8I
		{ VK_FORMAT_R8G8_UINT,                 VK_FORMAT_UNDEFINED                }, // RG8U
		{ VK_FORMAT_R8G8_SNORM,                VK_FORMAT_UNDEFINED                }, // RG8S
		{ VK_FORMAT_R16G16_UNORM,              VK_FORMAT_UNDEFINED                }, // RG16
		{ VK_FORMAT_R16G16_SINT,               VK_FORMAT_UNDEFINED                }, // RG16I
		{ VK_FORMAT_R16G16_UINT,               VK_FORMAT_UNDEFINED                }, // RG16U
		{ VK_FORMAT_R16G16_SFLOAT,             VK_FORMAT_UNDEFINED                }, // RG16F
		{ VK_FORMAT_R16G16_SNORM,              VK_FORMAT_UNDEFINED                }, // RG16S
		{ VK_FORMAT_R32G32_SINT,               VK_FORMAT_UNDEFINED                }, // RG32I
		{ VK_FORMAT_R32G32_UINT,               VK_FORMAT_UNDEFINED                }, // RG32U
		{ VK_FORMAT_R32G32_SFLOAT,             VK_FORMAT_UNDEFINED                }, // RG32F
		{ VK_FORMAT_R8G8B8_UNORM,              VK_FORMAT_R8G8B8_SRGB              }, // RGB8
		{ VK_FORMAT_R8G8B8_SINT,               VK_FORMAT_UNDEFINED                }, // RGB8I
		{ VK_FORMAT_R8G8B8_UINT,               VK_FORMAT_UNDEFINED                }, // RGB8U
		{ VK_FORMAT_R8G8B8_SNORM,              VK_FORMAT_UNDEFINED                }, // RGB8S
		{ VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,    VK_FORMAT_UNDEFINED                }, // RGB9E5F
		{ VK_FORMAT_B8G8R8A8_UNORM,            VK_FORMAT_B8G8R8A8_SRGB            }, // BGRA8
		{ VK_FORMAT_R8G8B8A8_UNORM,            VK_FORMAT_R8G8B8A8_SRGB            }, // RGBA8
		{ VK_FORMAT_R8G8B8A8_SINT,             VK_FORMAT_UNDEFINED                }, // RGBA8I
		{ VK_FORMAT_R8G8B8A8_UINT,             VK_FORMAT_UNDEFINED                }, // RGBA8U
		{ VK_FORMAT_R8G8B8A8_SNORM,            VK_FORMAT_UNDEFINED                }, // RGBA8S
		{ VK_FORMAT_R16G16B16A16_UNORM,        VK_FORMAT_UNDEFINED                }, // RGBA16
		{ VK_FORMAT_R16G16B16A16_SINT,         VK_FORMAT_UNDEFINED                }, // RGBA16I
		{ VK_FORMAT_R16G16B16A16_UINT,         VK_FORMAT_UNDEFINED                }, // RGBA16U
		{ VK_FORMAT_R16G16B16A16_SFLOAT,       VK_FORMAT_UNDEFINED                }, // RGBA16F
		{ VK_FORMAT_R16G16B16A16_SNORM,        VK_FORMAT_UNDEFINED                }, // RGBA16S
		{ VK_FORMAT_R32G32B32A32_SINT,         VK_FORMAT_UNDEFINED                }, // RGBA32I
		{ VK_FORMAT_R32G32B32A32_UINT,         VK_FORMAT_UNDEFINED                }, // RGBA32U
		{ VK_FORMAT_R32G32B32A32_SFLOAT,       VK_FORMAT_UNDEFINED                }, // RGBA32F
		{ VK_FORMAT_R5G6B5_UNORM_PACK16,       VK_FORMAT_UNDEFINED                }, // R5G6B5
		{ VK_FORMAT_R4G4B4A4_UNORM_PACK16,     VK_FORMAT_UNDEFINED                }, // RGBA4
		{ VK_FORMAT_R5G5B5A1_UNORM_PACK16,     VK_FORMAT_UNDEFINED                }, // RGB5A1
		{ VK_FORMAT_A2B10G10R10_UNORM_PACK32,  VK_FORMAT_UNDEFINED                }, // RGB10A2
		{ VK_FORMAT_B10G11R11_UFLOAT_PACK32,   VK_FORMAT_UNDEFINED                }, // R11G11B10F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // UnknownDepth
		{ VK_FORMAT_D16_UNORM,                 VK_FORMAT_UNDEFINED                }, // D16
		{ VK_FORMAT_X8_D24_UNORM_PACK32,       VK_FORMAT_UNDEFINED                }, // D24
		{ VK_FORMAT_D24_UNORM_S8_UINT,         VK_FORMAT_UNDEFINED                }, // D24S8
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // D32
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // D16F
		{ VK_FORMAT_UNDEFINED,                 VK_FORMAT_UNDEFINED                }, // D24F
		{ VK_FORMAT_D32_SFLOAT,                VK_FORMAT_UNDEFINED                }, // D32F
		{ VK_FORMAT_S8_UINT,                   VK_FORMAT_UNDEFINED                }  // D0S8
	};
	BX_STATIC_ASSERT(TextureFormat::Count == BX_COUNTOF(s_textureFormat) );

	struct RendererContextVulkan : public RendererContextI
	{
		RendererContextVulkan()
		{
			// Pretend all features that are not returning results to CPU
			// are available.
			g_caps.supported = 0
				| BGFX_CAPS_TEXTURE_COMPARE_LEQUAL
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_COMPUTE
				| BGFX_CAPS_FRAGMENT_ORDERING
				| BGFX_CAPS_SWAP_CHAIN
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_DRAW_INDIRECT
				| BGFX_CAPS_HIDPI
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_CONSERVATIVE_RASTER
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_CUBE_ARRAY
				;
		}

		~RendererContextVulkan()
		{
		}

		static int32_t compareDescending(const void* _lhs, const void* _rhs)
		{
			return *(const int32_t*)_rhs - *(const int32_t*)_lhs;
		}

#		define CHECK_NULL(_variable) \
			if (NULL == (_variable)) { \
				BX_TRACE("Failed getting " #_variable); \
				return false; \
			}

#		define CHECK_RESULT(_function, ...) \
		{ \
			VkResult result = _function(__VA_ARGS__); \
			if (VK_SUCCESS != result) { \
				BX_TRACE("Failed " #_function ": %s", getResultString(result)); \
				return false; \
			} \
		}

		bool init()
		{
			m_vulkanLibrary = bx::dlopen(VULKAN_LIBRARY_NAME);
			CHECK_NULL(m_vulkanLibrary);

			PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)bx::dlsym(m_vulkanLibrary, "vkGetInstanceProcAddr");
			CHECK_NULL(vkGetInstanceProcAddr);

			PFN_vkCreateInstance vkCreateInstance = (PFN_vkCreateInstance)vkGetInstanceProcAddr(NULL, "vkCreateInstance");
			CHECK_NULL(vkCreateInstance);

			VkApplicationInfo applicationInfo = { VK_STRUCTURE_TYPE_APPLICATION_INFO, 0};
			applicationInfo.apiVersion = VK_API_VERSION_1_0;
			applicationInfo.pEngineName = "BGFX";
			applicationInfo.engineVersion = BGFX_API_VERSION;

			const char * instanceExtensions[] =
			{
				VK_KHR_SURFACE_EXTENSION_NAME,
#				if BX_PLATFORM_WINDOWS
					VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#				endif
			};

			VkInstanceCreateInfo instanceCreateInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, 0};
			instanceCreateInfo.pApplicationInfo = &applicationInfo;
			instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions;
			instanceCreateInfo.enabledExtensionCount = BX_COUNTOF(instanceExtensions);
			CHECK_RESULT(vkCreateInstance, &instanceCreateInfo, &s_allocationCallbacks, &m_instance);

#			define VK_IMPORT_INSTANCE(_func) \
			{ \
				_func = (PFN_##_func)vkGetInstanceProcAddr(m_instance, #_func); \
				CHECK_NULL(_func); \
			}
#			include "vkimports.h"

#			if BX_PLATFORM_WINDOWS
			{
				VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = { VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, 0 };
				surfaceCreateInfo.hinstance = (HINSTANCE)GetModuleHandle(NULL);
				surfaceCreateInfo.hwnd = (HWND)g_platformData.nwh;
				CHECK_RESULT(vkCreateWin32SurfaceKHR, m_instance, &surfaceCreateInfo, &s_allocationCallbacks, &m_surface);
			}
#			endif

			CHECK_NULL(m_surface);

			uint32_t numDevices = VULKAN_MAX_DEVICES;
			VkPhysicalDevice physicalDevices[VULKAN_MAX_DEVICES];
			CHECK_RESULT(vkEnumeratePhysicalDevices, m_instance, &numDevices, physicalDevices);

			BX_TRACE("%d physical device available", numDevices);

			uint32_t bestDevice = selectBestDevice(physicalDevices, numDevices);
			if (bestDevice == numDevices)
			{
				BX_TRACE("No suitable devices found");
				return false;
			}

			BX_TRACE("Using device %d", bestDevice);
			if (!initDevice(physicalDevices[bestDevice]))
			{
				return false;
			}
			if (!initSwapChain(physicalDevices[bestDevice]))
			{
				return false;
			}
			return true;
		}

		uint32_t selectBestDevice(VkPhysicalDevice physicalDevices[VULKAN_MAX_DEVICES], uint32_t numDevices)
		{
			g_caps.numGPUs = bx::uint32_min(4, numDevices);

			if (0 == numDevices)
			{
				return 0;
			}
			uint32_t deviceScores[VULKAN_MAX_DEVICES];
			for (uint32_t ii = 0; ii < numDevices; ii++)
			{
				int32_t deviceScore = 0;
				VkPhysicalDeviceProperties deviceProperties;
				vkGetPhysicalDeviceProperties(physicalDevices[ii], &deviceProperties);
				VkPhysicalDeviceFeatures deviceFeatures;
				vkGetPhysicalDeviceFeatures(physicalDevices[ii], &deviceFeatures);
				uint32_t queueFamilyPropertyCount = VULKAN_MAX_QUEUE_FAMILIES;
				VkQueueFamilyProperties queueFamilyProperties[VULKAN_MAX_QUEUE_FAMILIES];
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[ii], &queueFamilyPropertyCount, queueFamilyProperties);

				BX_TRACE("Device %d: %s", ii, deviceProperties.deviceName);
				BX_TRACE("    Vendor: %X", deviceProperties.vendorID);
				BX_TRACE("    Device: %X", deviceProperties.deviceID);

				if (ii < BX_COUNTOF(g_caps.gpu))
				{
					g_caps.gpu[ii].deviceId = deviceProperties.deviceID;
					g_caps.gpu[ii].vendorId = deviceProperties.vendorID;
				}
				if (deviceProperties.vendorID == g_caps.vendorId)
				{
					if (deviceProperties.deviceID == g_caps.deviceId)
					{
						deviceScore |= 1 << 22;
					}
					deviceScore |= 1 << 21;
				}
				switch (deviceProperties.deviceType)
				{
					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
						BX_TRACE("    Type: Discrete GPU");
						deviceScore |= 1 << 20;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
						BX_TRACE("    Type: Integrated GPU");
						deviceScore |= 1 << 19;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
						BX_TRACE("    Type: Virtual GPU");
						deviceScore |= 1 << 18;
						break;
					case VK_PHYSICAL_DEVICE_TYPE_CPU:
						BX_TRACE("    Type: CPU");
						break;
					case VK_PHYSICAL_DEVICE_TYPE_OTHER:
						BX_TRACE("    Type: Other");
						break;
					default:
						BX_TRACE("    Type: Unknown");
						break;
				}
				deviceScore += deviceFeatures.robustBufferAccess;
				deviceScore += deviceFeatures.fullDrawIndexUint32;
				deviceScore += deviceFeatures.imageCubeArray;
				deviceScore += deviceFeatures.independentBlend;
				deviceScore += deviceFeatures.geometryShader;
				deviceScore += deviceFeatures.tessellationShader;
				deviceScore += deviceFeatures.sampleRateShading;
				deviceScore += deviceFeatures.dualSrcBlend;
				deviceScore += deviceFeatures.logicOp;
				deviceScore += deviceFeatures.multiDrawIndirect;
				deviceScore += deviceFeatures.drawIndirectFirstInstance;
				deviceScore += deviceFeatures.depthClamp;
				deviceScore += deviceFeatures.depthBiasClamp;
				deviceScore += deviceFeatures.fillModeNonSolid;
				deviceScore += deviceFeatures.depthBounds;
				deviceScore += deviceFeatures.wideLines;
				deviceScore += deviceFeatures.largePoints;
				deviceScore += deviceFeatures.alphaToOne;
				deviceScore += deviceFeatures.multiViewport;
				deviceScore += deviceFeatures.samplerAnisotropy;
				deviceScore += deviceFeatures.textureCompressionETC2;
				deviceScore += deviceFeatures.textureCompressionASTC_LDR;
				deviceScore += deviceFeatures.textureCompressionBC;
				deviceScore += deviceFeatures.occlusionQueryPrecise;
				deviceScore += deviceFeatures.pipelineStatisticsQuery;
				deviceScore += deviceFeatures.vertexPipelineStoresAndAtomics;
				deviceScore += deviceFeatures.fragmentStoresAndAtomics;
				deviceScore += deviceFeatures.shaderTessellationAndGeometryPointSize;
				deviceScore += deviceFeatures.shaderImageGatherExtended;
				deviceScore += deviceFeatures.shaderStorageImageExtendedFormats;
				deviceScore += deviceFeatures.shaderStorageImageMultisample;
				deviceScore += deviceFeatures.shaderStorageImageReadWithoutFormat;
				deviceScore += deviceFeatures.shaderStorageImageWriteWithoutFormat;
				deviceScore += deviceFeatures.shaderUniformBufferArrayDynamicIndexing;
				deviceScore += deviceFeatures.shaderSampledImageArrayDynamicIndexing;
				deviceScore += deviceFeatures.shaderStorageBufferArrayDynamicIndexing;
				deviceScore += deviceFeatures.shaderStorageImageArrayDynamicIndexing;
				deviceScore += deviceFeatures.shaderClipDistance;
				deviceScore += deviceFeatures.shaderCullDistance;
				deviceScore += deviceFeatures.shaderFloat64;
				deviceScore += deviceFeatures.shaderInt64;
				deviceScore += deviceFeatures.shaderInt16;
				deviceScore += deviceFeatures.shaderResourceResidency;
				deviceScore += deviceFeatures.shaderResourceMinLod;
				deviceScore += deviceFeatures.sparseBinding;
				deviceScore += deviceFeatures.sparseResidencyBuffer;
				deviceScore += deviceFeatures.sparseResidencyImage2D;
				deviceScore += deviceFeatures.sparseResidencyImage3D;
				deviceScore += deviceFeatures.sparseResidency2Samples;
				deviceScore += deviceFeatures.sparseResidency4Samples;
				deviceScore += deviceFeatures.sparseResidency8Samples;
				deviceScore += deviceFeatures.sparseResidency16Samples;
				deviceScore += deviceFeatures.sparseResidencyAliased;
				deviceScore += deviceFeatures.variableMultisampleRate;
				deviceScore += deviceFeatures.inheritedQueries;

				bool hasGraphicsQueue = false;
				for (uint32_t jj = 0; jj < queueFamilyPropertyCount; jj++)
				{
					BX_TRACE("    Queue Family %d:", jj);
					BX_TRACE("        Queue Count: %d", queueFamilyProperties[jj].queueCount);
					BX_TRACE("        Graphics: %s", (queueFamilyProperties[jj].queueFlags & VK_QUEUE_GRAPHICS_BIT)?"yes":"no");
					BX_TRACE("        Compute: %s", (queueFamilyProperties[jj].queueFlags & VK_QUEUE_COMPUTE_BIT)?"yes":"no");
					BX_TRACE("        Transfer: %s", (queueFamilyProperties[jj].queueFlags & VK_QUEUE_TRANSFER_BIT)?"yes":"no");
					BX_TRACE("        Sparse Binding: %s", (queueFamilyProperties[jj].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)?"yes":"no");

					VkBool32 supported = VK_FALSE;
					VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevices[ii], jj, m_surface, &supported);
					BX_TRACE("        Surface Supported: %s", (VK_SUCCESS == result && VK_TRUE == supported)?"yes":"no");

					if (queueFamilyProperties[jj].queueFlags & VK_QUEUE_GRAPHICS_BIT)
					{
						if (VK_SUCCESS == result && VK_TRUE == supported)
						{
							hasGraphicsQueue = true;
						}
					}
				}
				if (!hasGraphicsQueue)
				{
					deviceScore = 0;
				}
				BX_TRACE("    Score: %d", deviceScore);
				deviceScores[ii] = (deviceScore << 8) | ii;
			}
			qsort(deviceScores, numDevices, sizeof(deviceScores[0]), compareDescending);

			if ((deviceScores[0] >> 8) == 0)
			{
				return numDevices;
			}

			return deviceScores[0] & 0xFF;
		}

		bool initDevice(VkPhysicalDevice physicalDevice)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

			VkPhysicalDeviceFeatures deviceFeatures;
			vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

			uint32_t queueFamilyPropertyCount = VULKAN_MAX_QUEUE_FAMILIES;
			VkQueueFamilyProperties queueFamilyProperties[VULKAN_MAX_QUEUE_FAMILIES];
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertyCount, queueFamilyProperties);

			g_caps.deviceId = deviceProperties.deviceID & 0xFFFF;
			g_caps.vendorId = deviceProperties.vendorID & 0xFFFF;

			g_caps.homogeneousDepth = true;
			g_caps.originBottomLeft = true;

			g_caps.limits.maxTextureSize = deviceProperties.limits.maxImageDimension2D;
			g_caps.limits.maxFBAttachments = deviceProperties.limits.maxColorAttachments;
			g_caps.limits.maxVertexStreams = deviceProperties.limits.maxVertexInputBindings;

			for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
			{
				uint16_t support = BGFX_CAPS_FORMAT_TEXTURE_NONE;

				const TextureFormatInfo & tfi = s_textureFormat[ii];
				if (tfi.format != VK_FORMAT_UNDEFINED)
				{
					VkFormatProperties formatProperties;
					vkGetPhysicalDeviceFormatProperties(physicalDevice, tfi.format, &formatProperties);
					VkFormatFeatureFlags features = formatProperties.linearTilingFeatures | formatProperties.optimalTilingFeatures | formatProperties.bufferFeatures;
					if (features & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
					{
						support |= BGFX_CAPS_FORMAT_TEXTURE_2D | BGFX_CAPS_FORMAT_TEXTURE_3D | BGFX_CAPS_FORMAT_TEXTURE_CUBE;
						if (ii < TextureFormat::UnknownDepth)
						{
							if (deviceProperties.limits.sampledImageColorSampleCounts > VK_SAMPLE_COUNT_1_BIT)
							{
								support |= BGFX_CAPS_FORMAT_TEXTURE_MSAA;
							}
						}
						else
						{
							if (deviceProperties.limits.sampledImageDepthSampleCounts > VK_SAMPLE_COUNT_1_BIT)
							{
								support |= BGFX_CAPS_FORMAT_TEXTURE_MSAA;
							}
						}
					}
					if (features & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
					{
						support |= BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER;
						if (deviceProperties.limits.framebufferColorSampleCounts > VK_SAMPLE_COUNT_1_BIT)
						{
							support |= BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA;
						}
					}
					if (features & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
					{
						support |= BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER;
						if (deviceProperties.limits.framebufferDepthSampleCounts > VK_SAMPLE_COUNT_1_BIT)
						{
							support |= BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA;
						}
					}
					if (features & VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
					{
						support |= BGFX_CAPS_FORMAT_TEXTURE_VERTEX;
					}
					if (features & VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
					{
						support |= BGFX_CAPS_FORMAT_TEXTURE_IMAGE;
					}
				}
				if (tfi.srgbFormat != VK_FORMAT_UNDEFINED)
				{
					VkFormatProperties formatProperties;
					vkGetPhysicalDeviceFormatProperties(physicalDevice, tfi.srgbFormat, &formatProperties);
					VkFormatFeatureFlags features = formatProperties.linearTilingFeatures | formatProperties.optimalTilingFeatures | formatProperties.bufferFeatures;
					if (features & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
					{
						support |= BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB | BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB | BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB;
					}
				}
				g_caps.formats[ii] = support;
			}

			VkDeviceQueueCreateInfo deviceQueueCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, 0};
			deviceQueueCreateInfo.queueCount = 1;
			for (uint32_t jj = 0; jj < queueFamilyPropertyCount; jj++)
			{
				if (queueFamilyProperties[jj].queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					VkBool32 supported = VK_FALSE;
					VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, jj, m_surface, &supported);
					if (VK_SUCCESS == result && VK_TRUE == supported)
					{
						deviceQueueCreateInfo.queueFamilyIndex = jj;
					}
					break;
				}
			}

			const char * deviceExtensions[] =
			{
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			VkDeviceCreateInfo deviceCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, 0};
			deviceCreateInfo.queueCreateInfoCount = 1;
			deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
			deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;
			deviceCreateInfo.enabledExtensionCount = BX_COUNTOF(deviceExtensions);

			CHECK_RESULT(vkCreateDevice, physicalDevice, &deviceCreateInfo, &s_allocationCallbacks, &m_device);

#			define VK_IMPORT_DEVICE(_func) \
			{ \
				_func = (PFN_##_func)vkGetDeviceProcAddr(m_device, #_func); \
				CHECK_NULL(_func); \
			}
#			include "vkimports.h"

			vkGetDeviceQueue(m_device, deviceQueueCreateInfo.queueFamilyIndex, 0, &m_queue);

			return true;
		}

		bool initSwapChain(VkPhysicalDevice physicalDevice)
		{
			VkSurfaceCapabilitiesKHR surfaceCapabilities;
			CHECK_RESULT(vkGetPhysicalDeviceSurfaceCapabilitiesKHR, physicalDevice, m_surface, &surfaceCapabilities);

			uint32_t surfaceFormatCount = VULKAN_MAX_SURFACE_FORMATS;
			VkSurfaceFormatKHR surfaceFormats[VULKAN_MAX_SURFACE_FORMATS];
			CHECK_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR, physicalDevice, m_surface, &surfaceFormatCount, surfaceFormats);

			uint32_t presentModeCount = VULKAN_MAX_SURFACE_PRESENT_MODES;
			VkPresentModeKHR presentModes[VULKAN_MAX_SURFACE_PRESENT_MODES];
			CHECK_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR, physicalDevice, m_surface, &presentModeCount, presentModes);

			VkSwapchainCreateInfoKHR swapCreateInfo = { VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, 0 };
			swapCreateInfo.surface = m_surface;
			swapCreateInfo.minImageCount = surfaceCapabilities.minImageCount;

			if ((surfaceFormatCount == 0) || (surfaceFormatCount == 1 && surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
			{
				swapCreateInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
				swapCreateInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
			}
			else
			{
				swapCreateInfo.imageFormat = surfaceFormats[0].format;
				swapCreateInfo.imageColorSpace = surfaceFormats[0].colorSpace;
			}

			swapCreateInfo.imageExtent = surfaceCapabilities.currentExtent;
			swapCreateInfo.imageArrayLayers = 1;
			swapCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			swapCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			swapCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			swapCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

			// This is our 3rd choice mode
			swapCreateInfo.presentMode = presentModes[0];

			for (uint32_t ii = 0; ii < presentModeCount; ii++)
			{
				if (presentModes[ii] == VK_PRESENT_MODE_FIFO_RELAXED_KHR)
				{
					// This is our preferred mode
					swapCreateInfo.presentMode = presentModes[ii];
					break;
				}
				else if (presentModes[ii] == VK_PRESENT_MODE_FIFO_KHR)
				{
					// This is our 2nd choice mode
					swapCreateInfo.presentMode = presentModes[ii];
				}
			}

			CHECK_RESULT(vkCreateSwapchainKHR, m_device, &swapCreateInfo, &s_allocationCallbacks, &m_swapchain);

			m_swapImageCount = VULKAN_MAX_SWAP_IMAGES;
			CHECK_RESULT(vkGetSwapchainImagesKHR, m_device, m_swapchain, &m_swapImageCount, m_swapImages);

			for (uint32_t ii = 0; ii < m_swapImageCount; ii++)
			{
				m_swapImageViews[ii] = VK_NULL_HANDLE;
				m_swapFramebuffers[ii] = VK_NULL_HANDLE;
			}
			for (uint32_t ii = 0; ii < m_swapImageCount; ii++)
			{
				VkImageViewCreateInfo imageViewCreateInfo = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, 0 };
				imageViewCreateInfo.image = m_swapImages[ii];
				imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
				imageViewCreateInfo.format = swapCreateInfo.imageFormat;
				imageViewCreateInfo.components =
				{
					VK_COMPONENT_SWIZZLE_R,
					VK_COMPONENT_SWIZZLE_G,
					VK_COMPONENT_SWIZZLE_B,
					VK_COMPONENT_SWIZZLE_A
				};
				imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				imageViewCreateInfo.subresourceRange.levelCount = 1;
				imageViewCreateInfo.subresourceRange.layerCount = 1;
				CHECK_RESULT(vkCreateImageView, m_device, &imageViewCreateInfo, &s_allocationCallbacks, &m_swapImageViews[ii]);

				VkFramebufferCreateInfo framebufferCreateInfo = { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, 0 };
				framebufferCreateInfo.attachmentCount = 1;
				framebufferCreateInfo.pAttachments = &m_swapImageViews[ii];
				framebufferCreateInfo.width = swapCreateInfo.imageExtent.width;
				framebufferCreateInfo.height = swapCreateInfo.imageExtent.height;
				framebufferCreateInfo.layers = 1;

				CHECK_RESULT(vkCreateFramebuffer, m_device, &framebufferCreateInfo, &s_allocationCallbacks, &m_swapFramebuffers[ii]);
			}

			CHECK_RESULT(vkAcquireNextImageKHR, m_device, m_swapchain, UINT64_MAX, VK_NULL_HANDLE, VK_NULL_HANDLE, &m_currentSwapImage);

			return true;
		}

		void shutdown()
		{
			for (uint32_t ii = 0; ii < m_swapImageCount; ii++)
			{
				vkDestroyFramebuffer(m_device, m_swapFramebuffers[ii], &s_allocationCallbacks);
				vkDestroyImageView(m_device, m_swapImageViews[ii], &s_allocationCallbacks);
			}
			m_swapImageCount = 0;
			if (VK_NULL_HANDLE != m_swapchain)
			{
				vkDestroySwapchainKHR(m_device, m_swapchain, &s_allocationCallbacks);
				m_swapchain = VK_NULL_HANDLE;
			}
			if (VK_NULL_HANDLE != m_queue)
			{
				// No need to destroy a queue
				m_queue = VK_NULL_HANDLE;
			}
			if (VK_NULL_HANDLE != m_device)
			{
				vkDestroyDevice(m_device, &s_allocationCallbacks);
				m_device = VK_NULL_HANDLE;
			}
			if (VK_NULL_HANDLE != m_surface)
			{
				// No need to destroy a surface
				m_surface = VK_NULL_HANDLE;
			}
			if (VK_NULL_HANDLE != m_instance)
			{
				vkDestroyInstance(m_instance, &s_allocationCallbacks);
				m_instance = VK_NULL_HANDLE;
			}
			if (NULL != m_vulkanLibrary)
			{
				bx::dlclose(m_vulkanLibrary);
				m_vulkanLibrary = NULL;
			}
		}

		const char * getResultString(VkResult result)
		{
			switch (result)
			{
				case VK_SUCCESS: return "VK_SUCCESS";
				case VK_NOT_READY: return "VK_NOT_READY";
				case VK_TIMEOUT: return "VK_TIMEOUT";
				case VK_EVENT_SET: return "VK_EVENT_SET";
				case VK_EVENT_RESET: return "VK_EVENT_RESET";
				case VK_INCOMPLETE: return "VK_INCOMPLETE";
				case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
				case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
				case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
				case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
				case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
				case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
				case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
				case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
				case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
				case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
				case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
				case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
				case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
				case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
				case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
				case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
				case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
				case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
				default: return "VK_UNKNOWN";
			}
		}

		RendererType::Enum getRendererType() const BX_OVERRIDE
		{
			return RendererType::Vulkan;
		}

		const char* getRendererName() const BX_OVERRIDE
		{
			return BGFX_RENDERER_VULKAN_NAME;
		}

		void flip(HMD& /*_hmd*/) BX_OVERRIDE
		{
			VkPresentInfoKHR presentInfo = { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR, 0 };
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = &m_swapchain;
			presentInfo.pImageIndices = &m_currentSwapImage;
			vkQueuePresentKHR(m_queue, &presentInfo);
		}

		void createIndexBuffer(IndexBufferHandle /*_handle*/, Memory* /*_mem*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyIndexBuffer(IndexBufferHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createVertexDecl(VertexDeclHandle /*_handle*/, const VertexDecl& /*_decl*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyVertexDecl(VertexDeclHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createVertexBuffer(VertexBufferHandle /*_handle*/, Memory* /*_mem*/, VertexDeclHandle /*_declHandle*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyVertexBuffer(VertexBufferHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateDynamicIndexBuffer(IndexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_size*/, uint16_t /*_flags*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateDynamicVertexBuffer(VertexBufferHandle /*_handle*/, uint32_t /*_offset*/, uint32_t /*_size*/, Memory* /*_mem*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createShader(ShaderHandle /*_handle*/, Memory* /*_mem*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyShader(ShaderHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createProgram(ProgramHandle /*_handle*/, ShaderHandle /*_vsh*/, ShaderHandle /*_fsh*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyProgram(ProgramHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createTexture(TextureHandle /*_handle*/, Memory* /*_mem*/, uint32_t /*_flags*/, uint8_t /*_skip*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateTexture(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/, const Rect& /*_rect*/, uint16_t /*_z*/, uint16_t /*_depth*/, uint16_t /*_pitch*/, const Memory* /*_mem*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateTextureEnd() BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void readTexture(TextureHandle /*_handle*/, void* /*_data*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		uintptr_t getInternal(TextureHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
			return 0;
		}

		void destroyTexture(TextureHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, uint8_t /*_num*/, const Attachment* /*_attachment*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_depthFormat*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyFrameBuffer(FrameBufferHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void createUniform(UniformHandle /*_handle*/, UniformType::Enum /*_type*/, uint16_t /*_num*/, const char* /*_name*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void destroyUniform(UniformHandle /*_handle*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void saveScreenShot(const char* /*_filePath*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateViewName(uint8_t /*_id*/, const char* /*_name*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void updateUniform(uint16_t /*_loc*/, const void* /*_data*/, uint32_t /*_size*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void setMarker(const char* /*_marker*/, uint32_t /*_size*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void submit(Frame* _render, ClearQuad& /*_clearQuad*/, TextVideoMemBlitter& /*_textVideoMemBlitter*/) BX_OVERRIDE
		{
			if (_render->m_capture)
			{
				renderDocTriggerCapture();
			}

			_render->sort();

		}

		void blitSetup(TextVideoMemBlitter& /*_blitter*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void blitRender(TextVideoMemBlitter& /*_blitter*/, uint32_t /*_numIndices*/) BX_OVERRIDE
		{
			BX_CHECK(false, "Not Implemented");
		}

		void * m_vulkanLibrary = NULL;
		VkInstance m_instance = VK_NULL_HANDLE;
		VkDevice m_device = VK_NULL_HANDLE;
		VkQueue m_queue = VK_NULL_HANDLE;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;

		VkSwapchainKHR m_swapchain = VK_NULL_HANDLE;
		uint32_t m_swapImageCount = 0;
		uint32_t m_currentSwapImage = 0;
		VkImage m_swapImages[VULKAN_MAX_SWAP_IMAGES];
		VkImageView m_swapImageViews[VULKAN_MAX_SWAP_IMAGES];
		VkFramebuffer m_swapFramebuffers[VULKAN_MAX_SWAP_IMAGES];
	};

	static RendererContextVulkan* s_renderVulkan;

	RendererContextI* rendererCreate()
	{
		s_renderVulkan = BX_NEW(g_allocator, RendererContextVulkan);
		if (!s_renderVulkan->init())
		{
			s_renderVulkan->shutdown();
			BX_DELETE(g_allocator, s_renderVulkan);
			s_renderVulkan = NULL;
		}
		return s_renderVulkan;
	}

	void rendererDestroy()
	{
		BX_DELETE(g_allocator, s_renderVulkan);
		s_renderVulkan = NULL;
	}
} /* namespace vk */ } // namespace bgfx
