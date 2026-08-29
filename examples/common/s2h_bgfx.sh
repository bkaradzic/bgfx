//////////////////////////////////////////////////////////////////////////
// Shader To Human (S2H) - bgfx shaderc compatibility adapter           //
//////////////////////////////////////////////////////////////////////////
//
// Include bgfx's common shader header before this adapter. It provides
// shaderc's portable mul() and LOOP macros used by S2H.
//
//     #include "common.sh"
//     #include "s2h_bgfx.sh"
//     #include "s2h.hlsl"
//
// The S2H source files retain their HLSL extension so they can be shared
// unchanged with existing HLSL integrations.

#ifndef S2H_BGFX_INCLUDE
#define S2H_BGFX_INCLUDE

#define S2H_BGFX 1
#define S2H_LOOP LOOP

// shaderc's generated HLSL does not permit asfloat() in a global const
// initializer. This finite value is far beyond any practical scene depth and
// remains a literal expression on every shaderc backend.
#define S2H_FLT_MAX 1.0e30f

#include "s2h_glsl.hlsl"

#endif // S2H_BGFX_INCLUDE
