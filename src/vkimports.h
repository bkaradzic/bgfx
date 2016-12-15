/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#if !defined(VK_IMPORT_INSTANCE) && !defined(VK_IMPORT_DEVICE)
#	error VK_IMPORT_INSTANCE or VK_IMPORT_DEVICE must be defined!
#endif // !defined(VK_IMPORT_INSTANCE) || !defined(VK_IMPORT_DEVICE)

#if !defined(VK_IMPORT_INSTANCE)
#define VK_IMPORT_INSTANCE(_func)
#endif

#if !defined(VK_IMPORT_DEVICE)
#define VK_IMPORT_DEVICE(_func)
#endif

VK_IMPORT_INSTANCE(vkDestroyInstance);
VK_IMPORT_INSTANCE(vkEnumeratePhysicalDevices);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceProperties);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceFeatures);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceQueueFamilyProperties);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceFormatProperties);
VK_IMPORT_INSTANCE(vkCreateDevice);
VK_IMPORT_INSTANCE(vkGetDeviceProcAddr);

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VK_IMPORT_INSTANCE(vkCreateWin32SurfaceKHR);
#endif

#if defined(VK_KHR_surface)
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceSurfaceSupportKHR);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceSurfaceFormatsKHR);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
VK_IMPORT_INSTANCE(vkGetPhysicalDeviceSurfacePresentModesKHR);
#endif

#if defined(VK_KHR_swapchain)
VK_IMPORT_DEVICE(vkCreateSwapchainKHR);
VK_IMPORT_DEVICE(vkDestroySwapchainKHR);
VK_IMPORT_DEVICE(vkGetSwapchainImagesKHR);
VK_IMPORT_DEVICE(vkAcquireNextImageKHR);
VK_IMPORT_DEVICE(vkQueuePresentKHR);
#endif

VK_IMPORT_DEVICE(vkDestroyDevice);
VK_IMPORT_DEVICE(vkGetDeviceQueue);
VK_IMPORT_DEVICE(vkCreateImageView);
VK_IMPORT_DEVICE(vkDestroyImageView);
VK_IMPORT_DEVICE(vkCreateRenderPass);
VK_IMPORT_DEVICE(vkCreateFramebuffer);
VK_IMPORT_DEVICE(vkDestroyFramebuffer);
VK_IMPORT_DEVICE(vkCreateDescriptorSetLayout);
VK_IMPORT_DEVICE(vkCreatePipelineLayout);
VK_IMPORT_DEVICE(vkCreateShaderModule);
VK_IMPORT_DEVICE(vkCreateGraphicsPipelines);
VK_IMPORT_DEVICE(vkCreateDescriptorPool);
VK_IMPORT_DEVICE(vkAllocateDescriptorSets);
VK_IMPORT_DEVICE(vkCreateBuffer);
VK_IMPORT_DEVICE(vkAllocateMemory);
VK_IMPORT_DEVICE(vkBindBufferMemory);
VK_IMPORT_DEVICE(vkMapMemory);
VK_IMPORT_DEVICE(vkUnmapMemory);
VK_IMPORT_DEVICE(vkUpdateDescriptorSets);
VK_IMPORT_DEVICE(vkCreateCommandPool);
VK_IMPORT_DEVICE(vkAllocateCommandBuffers);
VK_IMPORT_DEVICE(vkBeginCommandBuffer);
VK_IMPORT_DEVICE(vkCmdBeginRenderPass);
VK_IMPORT_DEVICE(vkCmdBindPipeline);
VK_IMPORT_DEVICE(vkCmdBindDescriptorSets);
VK_IMPORT_DEVICE(vkCmdSetViewport);
VK_IMPORT_DEVICE(vkCmdDraw);
VK_IMPORT_DEVICE(vkCmdEndRenderPass);
VK_IMPORT_DEVICE(vkEndCommandBuffer);
VK_IMPORT_DEVICE(vkQueueSubmit);

#undef VK_IMPORT_INSTANCE
#undef VK_IMPORT_DEVICE
