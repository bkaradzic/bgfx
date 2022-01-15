$input v_normal, v_texcoord0, v_texcoord1, v_texcoord2

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"

SAMPLER2D(s_albedo, 0);
SAMPLER2D(s_normal, 1);

// struct ModelUniforms
uniform vec4 u_modelParams[2];

#define u_color				(u_modelParams[0].xyz)
#define u_lightPosition		(u_modelParams[1].xyz)

// http://www.thetenthplanet.de/archives/1180
// "followup: normal mapping without precomputed tangents"
mat3 cotangentFrame(vec3 N, vec3 p, vec2 uv)
{
	// get edge vectors of the pixel triangle
	vec3 dp1 = dFdx(p);
	vec3 dp2 = dFdy(p);
	vec2 duv1 = dFdx(uv);
	vec2 duv2 = dFdy(uv);

	// solve the linear system
	vec3 dp2perp = cross(dp2, N);
	vec3 dp1perp = cross(N, dp1);
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;
	
	// construct a scale-invariant frame
	float invMax = inversesqrt(max(dot(T,T), dot(B,B)));
	return mat3(T*invMax, B*invMax, N);
}

void main()
{
	vec3 albedo = toLinear(texture2D(s_albedo, v_texcoord0).xyz);

	// get vertex normal
	vec3 normal = normalize(v_normal);
	
	// get normal map normal, unpack, and calculate z
	vec3 normalMap;
	normalMap.xy = texture2D(s_normal, v_texcoord0).xy;
	normalMap.xy = normalMap.xy * 2.0 - 1.0;
	normalMap.z = sqrt(1.0 - dot(normalMap.xy, normalMap.xy));
	
	// swap x and y, because the brick texture looks flipped, don't copy this...
	normalMap.xy = -normalMap.yx;

	// perturb geometry normal by normal map
	vec3 pos = v_texcoord1.xyz; // contains world space pos
	mat3 TBN = cotangentFrame(normal, pos, v_texcoord0);
	vec3 bumpedNormal = normalize(instMul(TBN, normalMap));

	vec3 light = (u_lightPosition - pos);
	light = normalize(light);

	float NdotL = saturate(dot(bumpedNormal, light));
	float diffuse = NdotL * 1.0;

	vec3 V = v_texcoord2.xyz; // contains view vector
	vec3 H = normalize(V+light);
	float NdotH = saturate(dot(bumpedNormal, H));
	float specular = 5.0 * pow(NdotH, 256);
	float ambient = 0.1;

	float lightAmount = ambient + diffuse;
	vec3 color = u_color * albedo * lightAmount + specular;

	// leave color in linear space for better dof filter result

	gl_FragColor = vec4(color, 1.0);
}
