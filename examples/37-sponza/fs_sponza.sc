$input v_pos, v_normal, v_tangent, v_bitangent, v_texcoord0

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

SAMPLER2D(s_diffuseMap, 0);
SAMPLER2D(s_normalMap, 1);
SAMPLER2D(s_specularMap, 2);
uniform vec4 u_lightDir;
uniform vec4 u_viewDir;


void main()
{
	float gamma = 2.2;

	// sample albedo
	vec4 albedo = texture2D(s_diffuseMap, v_texcoord0);
	if (albedo.w < 0.5)
	{
		discard;
	}

	// convert to linear
	albedo.xyz = pow(albedo.xyz, vec3_splat(gamma));

	// sample specular
	vec3 specularColor = texture2D(s_specularMap, v_texcoord0).xyz;

	// convert to linear
	specularColor.xyz = pow(specularColor.xyz, vec3_splat(gamma)); 

	// sample normal map
	vec3 tangentNormal;
	tangentNormal.xy = texture2D(s_normalMap, v_texcoord0).xy * 2.0 - 1.0;
	tangentNormal.z = sqrt(1.0 - dot(tangentNormal.xy, tangentNormal.xy) );

	// convert to world space
	vec3 ws_normal = normalize(v_normal);
	vec3 ws_tangent = normalize(v_tangent);
	vec3 ws_bitangent = normalize(v_bitangent);
	mat3 tbn = mat3(ws_tangent, ws_bitangent, ws_normal );
	vec3 normal = mul(tangentNormal, tbn);

	// Simple Blinn–Phong shading
	float shininess = 8.0;

	float ndotl = dot( u_lightDir.xyz, normal );
        float lambertian = max(0.0, ndotl);
	lambertian = lambertian * 2.2;

	vec3 h = normalize( u_lightDir.xyz + u_viewDir.xyz );
	float ndoth = dot( normal, h );
	float specular = pow( max(0.0, ndoth ), shininess );
	specular = specular * 0.15;

	vec3 ambient = (0.65 * albedo.xyz);

	vec3 fragColor = (albedo.xyz * lambertian) + (specularColor * specular) + ambient;

	// Convert back to srgb
	gl_FragColor.xyz = pow(fragColor.xyz, vec3_splat(1.0 / gamma));

	gl_FragColor.w = 1.0;
}
