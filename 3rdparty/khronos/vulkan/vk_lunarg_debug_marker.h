//
// File: vk_lunarg_debug_marker.h
//
/*
 * Copyright (c) 2015-2016 The Khronos Group Inc.
 * Copyright (c) 2015-2016 Valve Corporation
 * Copyright (c) 2015-2016 LunarG, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and/or associated documentation files (the "Materials"), to
 * deal in the Materials without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Materials, and to permit persons to whom the Materials are
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice(s) and this permission notice shall be included in
 * all copies or substantial portions of the Materials.
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR THE
 * USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 * Authors:
 *   Jon Ashburn <jon@lunarg.com>
 *   Courtney Goeltzenleuchter <courtney@lunarg.com>
 */

#ifndef __VK_DEBUG_MARKER_H__
#define __VK_DEBUG_MARKER_H__

#include "vulkan.h"

#define VK_DEBUG_MARKER_EXTENSION_NUMBER 6
#define VK_DEBUG_MARKER_EXTENSION_REVISION 1
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*
***************************************************************************************************
*   DebugMarker Vulkan Extension API
***************************************************************************************************
*/

#define DEBUG_MARKER_EXTENSION_NAME "VK_LUNARG_DEBUG_MARKER"

// ------------------------------------------------------------------------------------------------
// Enumerations

#define VK_DEBUG_MARKER_ENUM_EXTEND(type, id)                                  \
    ((type)(VK_DEBUG_MARKER_EXTENSION_NUMBER * -1000 + (id)))

#define VK_OBJECT_INFO_TYPE_DBG_OBJECT_TAG                                     \
    VK_DEBUG_MARKER_ENUM_EXTEND(VkDbgObjectInfoType, 0)
#define VK_OBJECT_INFO_TYPE_DBG_OBJECT_NAME                                    \
    VK_DEBUG_MARKER_ENUM_EXTEND(VkDbgObjectInfoType, 1)

// ------------------------------------------------------------------------------------------------
// API functions

typedef void(VKAPI_PTR *PFN_vkCmdDbgMarkerBegin)(VkCommandBuffer commandBuffer,
                                                 const char *pMarker);
typedef void(VKAPI_PTR *PFN_vkCmdDbgMarkerEnd)(VkCommandBuffer commandBuffer);
typedef VkResult(VKAPI_PTR *PFN_vkDbgSetObjectTag)(
    VkDevice device, VkDebugReportObjectTypeEXT objType, uint64_t object,
    size_t tagSize, const void *pTag);
typedef VkResult(VKAPI_PTR *PFN_vkDbgSetObjectName)(
    VkDevice device, VkDebugReportObjectTypeEXT objType, uint64_t object,
    size_t nameSize, const char *pName);

#ifndef VK_NO_PROTOTYPES

// DebugMarker extension entrypoints
VKAPI_ATTR void VKAPI_CALL
vkCmdDbgMarkerBegin(VkCommandBuffer commandBuffer, const char *pMarker);

VKAPI_ATTR void VKAPI_CALL vkCmdDbgMarkerEnd(VkCommandBuffer commandBuffer);

VKAPI_ATTR VkResult VKAPI_CALL
vkDbgSetObjectTag(VkDevice device, VkDebugReportObjectTypeEXT objType,
                  uint64_t object, size_t tagSize, const void *pTag);

VKAPI_ATTR VkResult VKAPI_CALL
vkDbgSetObjectName(VkDevice device, VkDebugReportObjectTypeEXT objType,
                   uint64_t object, size_t nameSize, const char *pName);

#endif // VK_NO_PROTOTYPES

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // __VK_DEBUG_MARKER_H__
