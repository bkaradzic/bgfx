#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_RW(u_AtomicCounterBuffer, uint, 5);
BUFFER_RW(u_IndirectBuffer, uvec4, 6);

NUM_THREADS(1u, 1u, 1u)
void main()
{
	uint counter = u_AtomicCounterBuffer[1];

	uint subd = 6 << (2 * u_gpu_subd - 1);

	if((2 * u_gpu_subd - 1) <= 0) {
		subd = 3u;
	}

	drawIndexedIndirect(u_IndirectBuffer, 0, subd, counter / 2, 0u, 0u, 0u);
}
