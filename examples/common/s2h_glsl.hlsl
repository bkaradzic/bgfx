#ifndef S2H_GLSL
#define S2H_GLSL 1

#ifndef __SLANG__
	#define int2 ivec2
	#define int3 ivec3
	#define int4 ivec4
	#define uint2 uvec2
	#define uint3 uvec3
	#define uint4 uvec4
	#define float2 vec2
	#define float3 vec3
	#define float4 vec4
	#define float3x3 mat3
	#define float4x4 mat4
	#define lerp mix
	// GLSL does not support static globals, while shaderc's non-GLSL targets
	// need static const declarations for expressions such as _a = _A + 32u.
	#if !defined(S2H_BGFX) || BGFX_SHADER_LANGUAGE_GLSL
		#define static
	#endif
	#define rsqrt(_x) (1.0f / sqrt(_x))
	// bgfx provides its own mul macro.  It must remain in control so matrix
	// multiplication is translated correctly for every bgfx renderer.
	#ifndef S2H_BGFX
		#define mul(a,b) (a) * (b)
	#endif
	#if !defined(S2H_BGFX) || BGFX_SHADER_LANGUAGE_GLSL
		#define atan2 atan
	#endif
	#define asuint floatBitsToUint
	#define asfloat uintBitsToFloat
#endif

#define sincos(x,s,c) {s=sin(x);c=cos(x);}
#define saturate(x) clamp(x,0.0f,1.0f)
// bgfx maps GLSL's fract() to HLSL's frac() for non-GLSL targets.  Defining
// the inverse here on those targets creates a macro cycle that leaves fract()
// in generated DX11 HLSL.  The alias is only needed when compiling GLSL.
#if !defined(S2H_BGFX) || BGFX_SHADER_LANGUAGE_GLSL
	#define frac(x) fract(x)
#endif
#define groupshared shared
#define WaveActiveSum subgroupAdd
#define WaveGetLaneCount() gl_SubgroupSize
#define WaveActiveCountBits(x) subgroupBallotBitCount(uvec4(x,0,0,0))
#define WaveIsFirstLane subgroupElect
#define GroupMemoryBarrierWithGroupSync barrier
#define f32tof16(f) packHalf2x16(vec2(f, 0))
#define f16tof32(u) unpackHalf2x16(u).x


#endif // S2H_GLSL
