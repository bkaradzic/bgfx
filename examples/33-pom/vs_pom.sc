$input a_position, a_tangent, a_bitangent, a_texcoord0
$output v_texcoord0, v_ts_light_pos, v_ts_view_pos, v_ts_frag_pos

uniform mat4 u_norm_mtx;
uniform vec4 u_light_pos;

#include "../common/common.sh"

void main()
{
	vec3 wpos = mul(u_model[0], vec4(a_position, 1.0) ).xyz;
	gl_Position = mul(u_viewProj, vec4(wpos, 1.0) );

	vec3 tangent   = a_tangent   * 2.0 - 1.0;
	vec3 bitangent = a_bitangent * 2.0 - 1.0;
	vec3 normal    = cross(tangent, bitangent);

	vec3 t = normalize(mul(u_norm_mtx, vec4(tangent,   0.0) ).xyz);
	vec3 b = normalize(mul(u_norm_mtx, vec4(bitangent, 0.0) ).xyz);
	vec3 n = normalize(mul(u_norm_mtx, vec4(normal,    0.0) ).xyz);
	mat3 tbn = mat3(t, b, n);

	v_ts_light_pos = instMul(u_light_pos.xyz, tbn);
	// Our camera is always at the origin
	v_ts_view_pos  = instMul(vec3_splat(0.0), tbn);
	v_ts_frag_pos  = instMul(wpos,            tbn);

	v_texcoord0 = a_texcoord0;
}
