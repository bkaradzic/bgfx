$input v_normal, v_texcoord0

/*
* Copyright 2017 Stanislav Pidhorskyi. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"

SAMPLER2D(s_texLightmap,  0);
uniform vec4 u_sunDirection;
uniform vec4 u_sunLuminance;
uniform vec4 u_skyLuminance;
uniform vec4 u_parameters;

// https://www.shadertoy.com/view/4ssXRX
// http://www.loopit.dk/banding_in_games.pdf
// http://www.dspguide.com/ch2/6.htm

//uniformly distributed, normalized rand, [0, 1)
float nrand(in vec2 n)
{
	return fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

float n4rand_ss(in vec2 n)
{
	float nrnd0 = nrand( n + 0.07*fract( u_parameters.w ) );
	float nrnd1 = nrand( n + 0.11*fract( u_parameters.w + 0.573953 ) );	
	return 0.23*sqrt(-log(nrnd0+0.00001))*cos(2.0*3.141592*nrnd1)+0.5;
}

float toLinear(float _rgb)
{
	return pow(abs(_rgb), 2.2);
}

void main()
{
	vec3 normal = normalize(v_normal);

	float occulsion = toLinear(texture2D(s_texLightmap, v_texcoord0).r);
	
	vec3 skyDirection = vec3(0.0, 0.0, 1.0);
	
	float diffuseSun = max(0.0, dot(normal, normalize(u_sunDirection.xyz)));
	float diffuseSky = 1.0 + 0.5 * dot(normal, skyDirection);
	
	vec3 color = diffuseSun * u_sunLuminance.rgb + (diffuseSky * u_skyLuminance.rgb + 0.01) * occulsion;
	color *= 0.5;
	
	//color = mix(color, (u_skyLuminance + u_sunLuminance)*0.3, v_fogFactor);
	
	gl_FragColor.xyz = color * u_parameters.z;
	gl_FragColor.w = 1.0;
	float r = n4rand_ss(gl_FragCoord.xy) / 40.0;
	gl_FragColor.xyz = toGamma(gl_FragColor.xyz) + vec3(r, r, r);
}
