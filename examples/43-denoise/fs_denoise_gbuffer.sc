$input v_normal, v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3

#include "../common/common.sh"
#include "parameters.sh"
#include "normal_encoding.sh"

SAMPLER2D(s_albedo, 0);
SAMPLER2D(s_normal, 1);

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
	normalMap.xy = normalMap.yx;

	// perturb geometry normal by normal map
	vec3 pos = v_texcoord2.xyz; // contains world space pos
	mat3 TBN = cotangentFrame(normal, pos, v_texcoord0);
	vec3 bumpedNormal = normalize(instMul(TBN, normalMap));

	// need some proxy for roughness value w/o roughness texture
	// assume horizontal (blue) normal map is smooth, and then
	// modulate with albedo for some higher frequency detail
	float roughness = normalMap.z * mix(0.9, 1.0, albedo.y);
	roughness = roughness * 0.6 + 0.2;

	// Calculate velocity as delta position from previous frame to this
	vec2 previousNDC = v_texcoord1.xy * (1.0/v_texcoord1.w);
	previousNDC.y *= -1.0;
	previousNDC = previousNDC * 0.5 + 0.5;
	vec2 velocity = gl_FragCoord.xy*u_viewTexel.xy - previousNDC;

	vec3 bufferNormal = NormalEncode(bumpedNormal);

	gl_FragData[0] = vec4(toGamma(albedo), 1.0);
	gl_FragData[1] = vec4(bufferNormal, roughness); // Todo, better packing
	gl_FragData[2] = vec4(velocity, 0.0, 0.0);
}
