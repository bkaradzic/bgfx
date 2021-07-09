/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_RENDERER_NVN_H_HEADER_GUARD
#define BGFX_RENDERER_NVN_H_HEADER_GUARD

#include <atomic>
#include <array>
#include <vector>

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunknown-pragmas");
BX_PRAGMA_DIAGNOSTIC_IGNORED_GCC("-Wpragmas");
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4005) // warning C4005: '' : macro redefinition
#include <nn/vi.h>
#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrImpl.h>
#include <nn/mem/mem_StandardAllocator.h>
#include <nn/perf/perf_Profile.h>
#include <nn/oe.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#include "renderer.h"
#include "renderer_nvn/memory.h"
#include "renderer_nvn/textures_samplers_pool.h"

namespace bgfx { namespace nvn
{

} }

#endif // BGFX_RENDERER_NVN_H_HEADER_GUARD
