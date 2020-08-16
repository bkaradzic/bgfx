
////////////////////////////////////////////////////////////////////////////////
// Implicit Subdivision Shader for Terrain Rendering
//

#include "terrain_common.sh"
#include "fcull.sh"

BUFFER_RO(u_SubdBufferIn, uint, 8);
BUFFER_RW(u_CulledSubdBuffer, uint, 2);
BUFFER_RO(u_VertexBuffer, vec4, 6);
BUFFER_RO(u_IndexBuffer, uint, 7);

/**
 * Compute LoD Shader
 *
 * This compute shader is responsible for updating the subdivision
 * buffer and visible buffer that will be sent to the rasterizer.
 */

NUM_THREADS(COMPUTE_THREAD_COUNT, 1u, 1u)
void main()
{
	// get threadID (each key is associated to a thread)
	uint threadID = gl_GlobalInvocationID.x;

	if (threadID >= u_AtomicCounterBuffer[2])
	{
		return;
	}

	// get coarse triangle associated to the key
	uint primID = u_SubdBufferIn[threadID*2];

	vec4 v_in[3];
	v_in[0] = u_VertexBuffer[u_IndexBuffer[primID * 3    ]];
	v_in[1] = u_VertexBuffer[u_IndexBuffer[primID * 3 + 1]];
	v_in[2] = u_VertexBuffer[u_IndexBuffer[primID * 3 + 2]];

	// compute distance-based LOD
	uint key = u_SubdBufferIn[threadID*2+1];

	vec4 v[3];
	vec4 vp[3];

	subd(key, v_in, v, vp);

	uint targetLod; uint parentLod;

	if (u_freeze == 0)
	{
		targetLod = uint(computeLod(v));
		parentLod = uint(computeLod(vp));
	}
	else
	{
		targetLod = parentLod = findMSB_(key);
	}

	updateSubdBuffer(primID, key, targetLod, parentLod);

	// Cull invisible nodes
	mat4 mvp = u_modelViewProj;
	vec4 bmin = min(min(v[0], v[1]), v[2]);
	vec4 bmax = max(max(v[0], v[1]), v[2]);

	// account for displacement in bound computations
	bmin.z = 0;
	bmax.z = u_DmapFactor;

	// update CulledSubdBuffer
	if (u_cull == 0
	||  frustumCullingTest(mvp, bmin.xyz, bmax.xyz) )
	{
		// write key
		uint idx = 0;
		atomicFetchAndAdd(u_AtomicCounterBuffer[1], 2, idx);
		u_CulledSubdBuffer[idx] = primID;
		u_CulledSubdBuffer[idx+1] = key;
	}
}
