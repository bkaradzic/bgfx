$input v_normal, v_texcoord0, v_texcoord1

#include "../common/common.sh"
#include "parameters.sh"
#include "normal_encoding.sh"

void main()
{
	vec3 albedo = vec3_splat(1.0);

	// get vertex normal
	vec3 normal = normalize(v_normal);
	float roughness = 1.0;

	vec3 bufferNormal = NormalEncode(normal);

	// write data to alpha channel of color buffer to signify different handling
	// while lighting/shading these pixels in the gbuffer combine pass
	gl_FragData[0] = vec4(toGamma(albedo), 0.0);
	gl_FragData[1] = vec4(bufferNormal, roughness);
}
