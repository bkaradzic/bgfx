$input v_view, v_normal

/*
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"

SAMPLERCUBE(s_texCube, 0);
SAMPLERCUBE(s_texCubeIrr, 1);

vec3 calcFresnel(vec3 _cspec, float _dot)
{
	return _cspec + (1.0 - _cspec)*pow(1.0 - _dot, 5.0);
}

vec3 calcLambert(vec3 _cdiff, float _ndotl)
{
	return _cdiff*_ndotl;
}

vec3 calcBlinn(vec3 _cspec, float _ndoth, float _ndotl, float _specPwr)
{
	float norm = (_specPwr+8.0)*0.125;
	float brdf = pow(_ndoth, _specPwr)*_ndotl*norm;
	return _cspec*brdf;
}

float specPwr(float _gloss)
{
	return exp2(10.0*_gloss+2.0);
}

void main()
{
	// Light.
	vec3 ld     = normalize(u_lightDir);
	vec3 clight = u_lightCol;

	// Input.
	vec3 nn = normalize(v_normal);
	vec3 vv = normalize(v_view);
	vec3 hh = normalize(vv + ld);

	float ndotv = clamp(dot(nn, vv), 0.0, 1.0);
	float ndotl = clamp(dot(nn, ld), 0.0, 1.0);
	float ndoth = clamp(dot(nn, hh), 0.0, 1.0);
	float hdotv = clamp(dot(hh, vv), 0.0, 1.0);

	// Material params.
	vec3  albedo       = u_rgbDiff.xyz;
	float reflectivity = u_reflectivity;
	float gloss        = u_glossiness;

	// Reflection.
	vec3 refl;
	if (0.0 == u_metalOrSpec) // Metalness workflow.
	{
		refl = mix(vec3_splat(0.04), albedo, reflectivity);
	}
	else // Specular workflow.
	{
		refl = u_rgbSpec.xyz * vec3_splat(reflectivity);
	}
	vec3 dirF0 = calcFresnel(refl, hdotv);
	vec3 envF0 = calcFresnel(refl, ndotv);

	// Direct lighting.
	vec3 dirSpec = dirF0;
	vec3 dirDiff = albedo * 1.0-dirF0;

	vec3 lambert = u_doDiffuse  * calcLambert(dirDiff, ndotl);
	vec3 blinn   = u_doSpecular * calcBlinn(dirSpec, ndoth, ndotl, specPwr(gloss));
	vec3 direct  = (lambert + blinn)*clight;

	// Indirect lighting.
	vec3 envSpec = envF0;
	vec3 envDiff = albedo * 1.0-envF0;

	// Note: Environment textures are filtered with cmft: https://github.com/dariomanesku/cmft
	// Params used:
	// --excludeBase true //!< First level mip is not filtered.
	// --mipCount 7       //!< 7 mip levels are used in total, [256x256 .. 4x4]. Lower res mip maps should be avoided.
	// --glossScale 10    //!< Spec power scale. See: specPwr().
	// --glossBias 2      //!< Spec power bias. See: specPwr().
	// --edgeFixup warp   //!< This must be used on DirectX9. When fileted with 'warp', fixCubeLookup() should be used.
	float mip = 1.0 + 5.0*(1.0 - gloss); // Use mip levels [1..6] for radiance.

	mat4 mtx;
	mtx[0] = u_mtx0;
	mtx[1] = u_mtx1;
	mtx[2] = u_mtx2;
	mtx[3] = u_mtx3;
	vec3 vr = 2.0*ndotv*nn - vv; // Same as: -reflect(vv, nn);
	vec3 cubeR = normalize(instMul(mtx, vec4(vr, 0.0)).xyz);
	vec3 cubeN = normalize(instMul(mtx, vec4(nn, 0.0)).xyz);
	cubeR = fixCubeLookup(cubeR, mip, 256.0);

	vec3 radiance   = u_doSpecularIbl * envSpec * toLinear(textureCubeLod(s_texCube, cubeR, mip).xyz);
	vec3 irradiance = u_doDiffuseIbl  * envDiff * toLinear(textureCube(s_texCubeIrr, cubeN).xyz);
	vec3 indirect = radiance + irradiance;

	// Color.
	vec3 color = direct + indirect;
	color = color * exp2(u_exposure);
	gl_FragColor.xyz = toFilmic(color);
	gl_FragColor.w = 1.0;
}
