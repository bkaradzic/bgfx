/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

//instance data for all instances (pre culling)
BUFFER_RO(instanceDataIn, vec4, 1);

// Output
BUFFER_WR(indirectBuffer, uvec4, 0);

uniform vec4 u_drawParams;

NUM_THREADS(1, 1, 1)
void main()
{
	int NoofDrawcalls = int(u_drawParams.x);
	
	// tbd: frustum check draws
	
	for (int k = 0; k < NoofDrawcalls; k++) {
		drawIndexedIndirect(
						// Target location params:
			indirectBuffer,			// target buffer
			k,						// index in buffer
						// Draw call params:
			instanceDataIn[k].w,	// number of indices for this draw call
			1u, 					// number of instances for this draw call. You can disable this draw call by setting to zero
			instanceDataIn[k].z,	// offset in the index buffer
			instanceDataIn[k].x,	// offset in the vertex buffer. Note that you can use this to "reindex" submeshses - all indicies in this draw will be decremented by this amount
			k						// offset in the instance buffer. If you are drawing more than 1 instance per call see gpudrivenrendering for how to handle
			);
		}

}



