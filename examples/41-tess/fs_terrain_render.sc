$input v_texcoord0

#include "terrain_common.sh"

void main()
{
	vec2 s = texture2D(u_SmapSampler, v_texcoord0).rg * u_DmapFactor;
	vec3 n = normalize(vec3(-s, 1));
	float d = clamp(n.z, 0.0, 1.0) / 3.14159;
	vec3 r = vec3(d, d, d);
	gl_FragColor = vec4(r, 1);
}
