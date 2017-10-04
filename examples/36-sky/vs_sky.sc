$input a_position
$output v_skyColor, v_screenPos, v_viewDir

/*
* Copyright 2017 Stanislav Pidhorskyi. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/


uniform vec4 u_sunDirection;
uniform vec4 u_skyLuminanceXYZ;
uniform vec4 u_parameters; // x - sun size, y - sun bloom, z - exposition
uniform vec4 u_perezCoeff[5];

#include "../common/common.sh"

vec3 Perez(vec3 A,vec3 B,vec3 C,vec3 D, vec3 E,float costeta, float cosgamma)
{
	float _1_costeta = 1.0 / costeta;
	float cos2gamma = cosgamma * cosgamma;
	float gamma = acos(cosgamma);
	vec3 f = (vec3_splat(1.0) + A * exp(B * _1_costeta))
		   * (vec3_splat(1.0) + C * exp(D * gamma) + E * cos2gamma);
	return f;
}

void main()
{
	v_screenPos = a_position.xy;

	vec4 rayStart = mul(u_invViewProj, vec4(vec3(a_position.xy, -1.0), 1.0));
	vec4 rayEnd = mul(u_invViewProj, vec4(vec3(a_position.xy, 1.0), 1.0));

	rayStart = rayStart / rayStart.w;
	rayEnd = rayEnd / rayEnd.w;

	v_viewDir = normalize(rayEnd.xyz - rayStart.xyz);
	v_viewDir.y = abs(v_viewDir.y);

	gl_Position = vec4(a_position.xy, 1.0, 1.0);

	vec3 lightDir = normalize(u_sunDirection.xyz);
	vec3 skyDir = vec3(0.0, 1.0, 0.0);

	// Perez coefficients.
	vec3 A = u_perezCoeff[0].xyz;
	vec3 B = u_perezCoeff[1].xyz;
	vec3 C = u_perezCoeff[2].xyz;
	vec3 D = u_perezCoeff[3].xyz;
	vec3 E = u_perezCoeff[4].xyz;

	float costeta = max(dot(v_viewDir, skyDir), 0.001);
	float cosgamma = clamp(dot(v_viewDir, lightDir), -0.9999, 0.9999);
	float cosgammas = dot(skyDir, lightDir);

	vec3 P = Perez(A,B,C,D,E, costeta, cosgamma);
	vec3 P0 = Perez(A,B,C,D,E, 1.0, cosgammas);

	vec3 skyColorxyY = vec3(
		  u_skyLuminanceXYZ.x / (u_skyLuminanceXYZ.x+u_skyLuminanceXYZ.y + u_skyLuminanceXYZ.z)
		, u_skyLuminanceXYZ.y / (u_skyLuminanceXYZ.x+u_skyLuminanceXYZ.y + u_skyLuminanceXYZ.z)
		, u_skyLuminanceXYZ.y
		);

	vec3 Yp = skyColorxyY * P / P0;

	vec3 skyColorXYZ = vec3(Yp.x * Yp.z / Yp.y,Yp.z, (1.0 - Yp.x- Yp.y)*Yp.z/Yp.y);

	v_skyColor = convertXYZ2RGB(skyColorXYZ * u_parameters.z);
}
