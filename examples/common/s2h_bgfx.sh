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

// S2H examples use a top-left pixel origin to match their source tools and
// host mouse coordinates. bgfx exposes the native fragment origin, so the
// host supplies the target height and whether the renderer is bottom-left.
uniform vec4 u_s2hScreen;

float2 s2h_getPixelCoord(float2 _fragmentCoord)
{
	return float2(
		  _fragmentCoord.x
		, mix(_fragmentCoord.y, u_s2hScreen.x - _fragmentCoord.y, u_s2hScreen.y)
		);
}

#endif // S2H_BGFX_INCLUDE
