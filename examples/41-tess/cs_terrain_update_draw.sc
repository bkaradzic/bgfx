#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_RW(indirectBuffer, uvec4, 3);
BUFFER_RW(atomicCounterBuffer, uint, 4);

NUM_THREADS(1u, 1u, 1u)
void main()
{
	uint counter = atomicCounterBuffer[1];

	uint subd = 6 << (2 * u_gpu_subd - 1);

	if((2 * u_gpu_subd - 1) <= 0) {
		subd = 3u;
	}

	drawIndexedIndirect(indirectBuffer, 0, subd, counter / 2, 0u, 0u, 0u);
}
