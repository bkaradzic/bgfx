$input a_position, a_tangent, a_bitangent, a_texcoord0
$output v_texcoord0, v_ts_light_pos, v_ts_view_pos, v_ts_frag_pos

uniform mat4 u_norm_mtx;
uniform vec4 u_light_pos;

#include "../common/common.sh"

mat3 transpose(mat3 inMatrix)
{
	vec3 i0 = inMatrix[0];
	vec3 i1 = inMatrix[1];
	vec3 i2 = inMatrix[2];

	mat3 outMatrix = mat3(
		vec3(i0.x, i1.x, i2.x),
		vec3(i0.y, i1.y, i2.y),
		vec3(i0.z, i1.z, i2.z)
	);

	return outMatrix;
}

void main()
{
	vec3 wpos = mul(u_model[0], vec4(a_position, 1.0) ).xyz;
	gl_Position = mul(u_viewProj, vec4(wpos, 1.0) );

	vec3 tangent = a_tangent * 2.0 - 1.0;
	vec3 bitangent = a_bitangent * 2.0 - 1.0;
	vec3 normal = cross(tangent, bitangent);

	vec3 t = normalize(mat3(u_norm_mtx) * tangent);
	vec3 b = normalize(mat3(u_norm_mtx) * bitangent);
	vec3 n = normalize(mat3(u_norm_mtx) * normal);
	mat3 tbn = transpose(mat3(t, b, n));

	v_ts_light_pos = tbn * u_light_pos.xyz;
	// Our camera is always at the origin
	v_ts_view_pos = tbn * vec3(0, 0, 0);
	v_ts_frag_pos = tbn * wpos;

	v_texcoord0 = a_texcoord0;
}
