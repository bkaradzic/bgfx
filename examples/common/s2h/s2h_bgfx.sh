// S2H bgfx shaderc compatibility adapter. For the S2H library itself include
// s2h/s2h.sh, s2h/s2h_3d.sh or s2h/s2h_scatter.sh.

#ifndef S2H_BGFX_INCLUDE
#define S2H_BGFX_INCLUDE

#include <bgfx_shader.sh>

#define S2H_BGFX 1
#define S2H_LOOP LOOP

// shaderc's generated HLSL does not permit asfloat() in a global const
// initializer.
#define S2H_FLT_MAX 1.0e30f

#include "s2h/s2h_glsl.hlsl"

// S2H uses a top-left pixel origin; bgfx_ndc.z is the OpenGL origin sign.
float2 s2h_getPixelCoord(float2 _fragmentCoord)
{
#if BGFX_SHADER_LANGUAGE_GLSL
	return float2(
		  _fragmentCoord.x
		, mix(_fragmentCoord.y, u_viewRect.w - _fragmentCoord.y, 0.5f * (bgfx_ndc.z + 1.0f))
		);
#else
	return _fragmentCoord;
#endif // BGFX_SHADER_LANGUAGE_GLSL
}

#endif // S2H_BGFX_INCLUDE
