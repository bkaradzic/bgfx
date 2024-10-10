/*
* Copyright 2021 Richard Schubert. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*
* AMD FidelityFX Super Resolution 1.0 (FSR)
* Port from https://github.com/GPUOpen-Effects/FidelityFX-FSR/blob/master/sample/src/VK/FSR_Pass.glsl
*/

#include "bgfx_compute.sh"

uniform vec4 u_params[3];

#define ViewportSizeRcasAttenuation u_params[0]
#define SrcSize                     u_params[1]
#define DstSize                     u_params[2]

#define A_GPU 1

#if BGFX_SHADER_LANGUAGE_GLSL
#define A_GLSL 1
#define A_SKIP_EXT 1
#else
#define A_HLSL 1
#endif // BGFX_SHADER_LANGUAGE_GLSL

#if SAMPLE_SLOW_FALLBACK
#	include "ffx_a.h"
	SAMPLER2D(InputTexture, 0);
	IMAGE2D_WO(OutputTexture, rgba32f, 1);
#	if SAMPLE_EASU
		#define FSR_EASU_F 1
		AF4 FsrEasuRF(AF2 p) { AF4 res = textureGather(InputTexture, p, 0); return res; }
		AF4 FsrEasuGF(AF2 p) { AF4 res = textureGather(InputTexture, p, 1); return res; }
		AF4 FsrEasuBF(AF2 p) { AF4 res = textureGather(InputTexture, p, 2); return res; }
#	endif
#	if SAMPLE_RCAS
		#define FSR_RCAS_F
		AF4 FsrRcasLoadF(ASU2 p) { return texelFetch(InputTexture, ASU2(p), 0); }
		void FsrRcasInputF(inout AF1 r, inout AF1 g, inout AF1 b) {}
#	endif
#else
#	define A_HALF
#	include "ffx_a.h"
	SAMPLER2D(InputTexture, 0);
	IMAGE2D_WO(OutputTexture, rgba16f, 1);
#	if SAMPLE_EASU
		#define FSR_EASU_H 1
		AH4 FsrEasuRH(AF2 p) { AH4 res = AH4(textureGather(InputTexture, p, 0)); return res; }
		AH4 FsrEasuGH(AF2 p) { AH4 res = AH4(textureGather(InputTexture, p, 1)); return res; }
		AH4 FsrEasuBH(AF2 p) { AH4 res = AH4(textureGather(InputTexture, p, 2)); return res; }
#	endif
#	if SAMPLE_RCAS
		#define FSR_RCAS_H
		AH4 FsrRcasLoadH(ASW2 p) { return AH4(texelFetch(InputTexture, ASU2(p), 0)); }
		void FsrRcasInputH(inout AH1 r,inout AH1 g,inout AH1 b){}
#	endif
#endif

#include "ffx_fsr1.h"

void CurrFilter(AU2 pos, AU4 Const0, AU4 Const1, AU4 Const2, AU4 Const3, AU4 Sample)
{
#if SAMPLE_BILINEAR
	AF2 pp = (AF2(pos) * AF2_AU2(Const0.xy) + AF2_AU2(Const0.zw)) * AF2_AU2(Const1.xy) + AF2(0.5, -0.5) * AF2_AU2(Const1.zw);
	imageStore(OutputTexture, ASU2(pos), texture2DLod(InputTexture, pp, 0.0));
#endif

#if SAMPLE_EASU
#	if SAMPLE_SLOW_FALLBACK
		AF3 c;
		FsrEasuF(c, pos, Const0, Const1, Const2, Const3);
		if( Sample.x == 1 )
			c *= c;
		imageStore(OutputTexture, ASU2(pos), AF4(c, 1));
#	else
		AH3 c;
		FsrEasuH(c, pos, Const0, Const1, Const2, Const3);
		if( Sample.x == 1 )
			c *= c;
		imageStore(OutputTexture, ASU2(pos), AH4(c, 1));
#	endif
#endif

#if SAMPLE_RCAS
#	if SAMPLE_SLOW_FALLBACK
		AF3 c;
		FsrRcasF(c.r, c.g, c.b, pos, Const0);
		if( Sample.x == 1 )
			c *= c;
		imageStore(OutputTexture, ASU2(pos), AF4(c, 1));
#	else
		AH3 c;
		FsrRcasH(c.r, c.g, c.b, pos, Const0);
		if( Sample.x == 1 )
			c *= c;
		imageStore(OutputTexture, ASU2(pos), AH4(c, 1));
#	endif
#endif
}

NUM_THREADS(64, 1, 1)
void main()
{
	AU4 Const0, Const1, Const2, Const3, Sample;

	// We compute these constants on GPU because bgfx does not support uniform type uint.
#if SAMPLE_EASU || SAMPLE_BILINEAR
	FsrEasuCon(Const0, Const1, Const2, Const3,
		ViewportSizeRcasAttenuation.x, ViewportSizeRcasAttenuation.y,  // Viewport size (top left aligned) in the input image which is to be scaled.
		SrcSize.x, SrcSize.y,  // The size of the input image.
		DstSize.x, DstSize.y); // The output resolution.
	Sample.x = 0; // no HDR output
#endif // SAMPLE_EASU || SAMPLE_BILINEAR

#if SAMPLE_RCAS
	FsrRcasCon(Const0, ViewportSizeRcasAttenuation.z);
	Sample.x = 0;  // no HDR output
#endif // SAMPLE_RCAS

	// Do remapping of local xy in workgroup for a more PS-like swizzle pattern.
	AU2 gxy = ARmp8x8(gl_LocalInvocationID.x) + AU2(gl_WorkGroupID.x << 4u, gl_WorkGroupID.y << 4u);
	CurrFilter(gxy, Const0, Const1, Const2, Const3, Sample);
	gxy.x += 8u;
	CurrFilter(gxy, Const0, Const1, Const2, Const3, Sample);
	gxy.y += 8u;
	CurrFilter(gxy, Const0, Const1, Const2, Const3, Sample);
	gxy.x -= 8u;
	CurrFilter(gxy, Const0, Const1, Const2, Const3, Sample);
}
