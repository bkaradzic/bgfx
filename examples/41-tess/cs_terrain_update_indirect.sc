#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_RW(indirectBuffer, uvec4, 3);
BUFFER_RW(atomicCounterBuffer, uint, 4);

NUM_THREADS(1u, 1u, 1u)
void main()
{
	uint counter;
	uint counter2;

	atomicFetchAndExchange(atomicCounterBuffer[0], 0u, counter);
	atomicFetchAndExchange(atomicCounterBuffer[1], 0u, counter2);

	uint cnt = (counter / 2u) / UPDATE_INDIRECT_VALUE_DIVIDE + 1u;

	uint tmp;

	atomicFetchAndExchange(atomicCounterBuffer[2], (counter / 2), tmp);

	dispatchIndirect(indirectBuffer, 1u, cnt, 1u, 1u);
}
