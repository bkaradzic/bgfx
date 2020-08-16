#include "bgfx_compute.sh"
#include "matrices.sh"
#include "isubd.sh"
#include "uniforms.sh"

BUFFER_RW(u_AtomicCounterBuffer, uint, 4);
BUFFER_RW(u_SubdBufferOut, uint, 1);

SAMPLER2D(u_DmapSampler, 0); // displacement map
SAMPLER2D(u_SmapSampler, 1); // slope map

// displacement map
float dmap(vec2 pos)
{
	return (texture2DLod(u_DmapSampler, pos * 0.5 + 0.5, 0).x) * u_DmapFactor;
}

float distanceToLod(float z, float lodFactor)
{
	// Note that we multiply the result by two because the triangles
	// edge lengths decreases by half every two subdivision steps.
	return -2.0 * log2(clamp(z * lodFactor, 0.0f, 1.0f));
}

float computeLod(vec3 c)
{
	//displace
	c.z += dmap(mtxGetColumn(u_invView, 3).xy);

	vec3 cxf = mul(u_modelView, vec4(c.x, c.y, c.z, 1)).xyz;
	float z = length(cxf);

	return distanceToLod(z, u_LodFactor);
}

float computeLod(in vec4 v[3])
{
	vec3 c = (v[1].xyz + v[2].xyz) / 2.0;
	return computeLod(c);
}

float computeLod(in vec3 v[3])
{
	vec3 c = (v[1].xyz + v[2].xyz) / 2.0;
	return computeLod(c);
}

void writeKey(uint primID, uint key)
{
	uint idx = 0;

	atomicFetchAndAdd(u_AtomicCounterBuffer[0], 2, idx);

	u_SubdBufferOut[idx] = primID;
	u_SubdBufferOut[idx+1] = key;
}

void updateSubdBuffer(
	  uint primID
	, uint key
	, uint targetLod
	, uint parentLod
	, bool isVisible
	)
{
	// extract subdivision level associated to the key
	uint keyLod = findMSB_(key);

	// update the key accordingly
	if (/* subdivide ? */ keyLod < targetLod && !isLeafKey(key) && isVisible)
	{
		uint children[2]; childrenKeys(key, children);

		writeKey(primID, children[0]);
		writeKey(primID, children[1]);
	}
	else if (/* keep ? */ keyLod < (parentLod + 1) && isVisible)
	{
		writeKey(primID, key);
	}
	else /* merge ? */
	{

		if (/* is root ? */isRootKey(key))
		{
			writeKey(primID, key);
		}

		else if (/* is zero child ? */isChildZeroKey(key)) {
			writeKey(primID, parentKey(key));
		}

	}
}

void updateSubdBuffer(uint primID, uint key, uint targetLod, uint parentLod)
{
	updateSubdBuffer(primID, key, targetLod, parentLod, true);
}
