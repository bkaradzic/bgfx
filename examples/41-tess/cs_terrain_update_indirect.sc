#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_RW(u_AtomicCounterBuffer, uint, 5);
BUFFER_RW(u_IndirectBuffer, uvec4, 6);

NUM_THREADS(1u, 1u, 1u)
void main()
{
	uint counter;
	uint counter2;

	atomicFetchAndExchange(u_AtomicCounterBuffer[0], 0u, counter);
	atomicFetchAndExchange(u_AtomicCounterBuffer[1], 0u, counter2);

	uint cnt = (counter / 2u) / UPDATE_INDIRECT_VALUE_DIVIDE + 1u;

	uint tmp;

	atomicFetchAndExchange(u_AtomicCounterBuffer[2], (counter / 2), tmp);

	dispatchIndirect(u_IndirectBuffer, 1u, cnt, 1u, 1u);
}
