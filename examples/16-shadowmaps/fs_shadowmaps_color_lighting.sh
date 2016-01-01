/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

uniform vec4 u_params0;
uniform vec4 u_params1;
uniform vec4 u_params2;
uniform vec4 u_color;

uniform vec4 u_materialKa;
uniform vec4 u_materialKd;
uniform vec4 u_materialKs;
uniform vec4 u_lightPosition;
uniform vec4 u_lightAmbientPower;
uniform vec4 u_lightDiffusePower;
uniform vec4 u_lightSpecularPower;
uniform vec4 u_lightSpotDirectionInner;
uniform vec4 u_lightAttenuationSpotOuter;
uniform vec4 u_smSamplingParams;
uniform vec4 u_csmFarDistances;

#if SM_OMNI
uniform vec4 u_tetraNormalGreen;
uniform vec4 u_tetraNormalYellow;
uniform vec4 u_tetraNormalBlue;
uniform vec4 u_tetraNormalRed;
#endif

SAMPLER2D(s_shadowMap0, 4);
SAMPLER2D(s_shadowMap1, 5);
SAMPLER2D(s_shadowMap2, 6);
SAMPLER2D(s_shadowMap3, 7);

struct Shader
{
	vec3 ambi;
	vec3 diff;
	vec3 spec;
};

Shader evalShader(float _diff, float _spec)
{
	Shader shader;

	shader.ambi = u_lightAmbientPower.xyz  * u_lightAmbientPower.w  * u_materialKa.xyz;
	shader.diff = u_lightDiffusePower.xyz  * u_lightDiffusePower.w  * u_materialKd.xyz * _diff;
	shader.spec = u_lightSpecularPower.xyz * u_lightSpecularPower.w * u_materialKs.xyz * _spec;

	return shader;
}

float computeVisibility(sampler2D _sampler
					  , vec4 _shadowCoord
					  , float _bias
					  , vec4 _samplingParams
					  , vec2 _texelSize
					  , float _depthMultiplier
					  , float _minVariance
					  , float _hardness
					  )
{
	float visibility;

#if SM_LINEAR
	vec4 shadowcoord = vec4(_shadowCoord.xy / _shadowCoord.w, _shadowCoord.z, 1.0);
#else
	vec4 shadowcoord = _shadowCoord;
#endif

#if SM_HARD
	visibility = hardShadow(_sampler, shadowcoord, _bias);
#elif SM_PCF
	visibility = PCF(_sampler, shadowcoord, _bias, _samplingParams, _texelSize);
#elif SM_VSM
	visibility = VSM(_sampler, shadowcoord, _bias, _depthMultiplier, _minVariance);
#elif SM_ESM
	visibility = ESM(_sampler, shadowcoord, _bias, _depthMultiplier * _hardness);
#endif

	return visibility;
}
