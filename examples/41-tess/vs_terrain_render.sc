$input a_texcoord0
$output v_texcoord0

#include "terrain_common.sh"

BUFFER_RO(u_CulledSubdBuffer, uint, 2);
BUFFER_RO(u_VertexBuffer, vec4, 3);
BUFFER_RO(u_IndexBuffer, uint, 4);

void main()
{
	// get threadID (each key is associated to a thread)
	int threadID = gl_InstanceID;

	// get coarse triangle associated to the key
	uint primID = u_CulledSubdBuffer[threadID*2];

	vec4 v_in[3];

	v_in[0] = u_VertexBuffer[u_IndexBuffer[primID * 3    ]];
	v_in[1] = u_VertexBuffer[u_IndexBuffer[primID * 3 + 1]];
	v_in[2] = u_VertexBuffer[u_IndexBuffer[primID * 3 + 2]];

	// compute sub-triangle associated to the key
	uint key = u_CulledSubdBuffer[threadID*2+1];

	vec4 v[3];

	subd(key, v_in, v);

	// compute vertex location
	vec4 finalVertex = berp(v, a_texcoord0);

	finalVertex.z+= dmap(finalVertex.xy);

	v_texcoord0 = finalVertex.xy * 0.5 + 0.5;

	gl_Position = mul(u_modelViewProj, finalVertex);
}
