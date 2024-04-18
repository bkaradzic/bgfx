#include "bgfx_compute.sh"

#include "uniforms.sh"

BUFFER_WO(u_SubdBufferOut, uint, 1);
BUFFER_RW(u_CulledSubdBuffer, uint, 2);
BUFFER_RW(indirectBuffer, uvec4, 3);
BUFFER_RW(atomicCounterBuffer, uint, 4);
BUFFER_WO(u_SubdBufferIn, uint, 8);

NUM_THREADS(1u, 1u, 1u)
void main()
{
	uint subd = 6 << (2 * u_gpu_subd - 1);

	if((2 * u_gpu_subd - 1) <= 0) {
		subd = 3u;
	}

	drawIndexedIndirect(indirectBuffer, 0u, subd, 0u, 0u, 0u, 0u);
	dispatchIndirect(indirectBuffer, 1u, 2u / UPDATE_INDIRECT_VALUE_DIVIDE + 1u, 1u, 1u);

	u_SubdBufferOut[0] = 0;
	u_SubdBufferOut[1] = 1;
	u_SubdBufferOut[2] = 1;
	u_SubdBufferOut[3] = 1;

	u_CulledSubdBuffer[0] = 0;
	u_CulledSubdBuffer[1] = 1;
	u_CulledSubdBuffer[2] = 1;
	u_CulledSubdBuffer[3] = 1;

	u_SubdBufferIn[0] = 0;
	u_SubdBufferIn[1] = 1;
	u_SubdBufferIn[2] = 1;
	u_SubdBufferIn[3] = 1;

	uint tmp;

	atomicFetchAndExchange(atomicCounterBuffer[0], 0, tmp);
	atomicFetchAndExchange(atomicCounterBuffer[1], 0, tmp);
	atomicFetchAndExchange(atomicCounterBuffer[2], 2, tmp);
}
