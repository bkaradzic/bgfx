/*
 * Copyright 2022 Liam Twigger. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

//instance data for all instances (pre culling)
BUFFER_RO(instanceDataIn, vec4, 0);

// Output
BUFFER_WO(indirectBuffer, uvec4, 1);
BUFFER_WO(instanceBufferOut, vec4, 2);
#ifdef INDIRECT_COUNT
BUFFER_WO(indirectCountBuffer, int, 3);
#endif

uniform vec4 u_drawParams;

// Use 64*1*1 local threads
NUM_THREADS(64, 1, 1)

void main()
{
	int tId = int(gl_GlobalInvocationID.x);
	int numDrawItems = int(u_drawParams.x);
	int sideSize = int(u_drawParams.y);
	float time = u_drawParams.z;

	// Work out the amount of work we're going to do here
	int maxToDraw = min(sideSize*sideSize, numDrawItems);

	int numToDrawPerThread = maxToDraw/64 + 1;

	int idxStart = tId*numToDrawPerThread;
	int idxMax = min(maxToDraw, (tId+1)*numToDrawPerThread);

	// Prepare draw mtx
	for (int k = idxStart; k < idxMax; k++) {
		int yy = k / sideSize;
		int xx = k % sideSize;

		float _ax = time + xx * 0.21f;
		float _ay = time + yy * 0.37f;
		float sx = sin(_ax);
		float cx = cos(_ax);
		float sy = sin(_ay);
		float cy = cos(_ay);

		vec4 a = vec4(    cy,  0,     sy, 0);
		vec4 b = vec4( sx*sy, cx, -sx*cy, 0);
		vec4 c = vec4(-cx*sy, sx,  cx*cy, 0);

		vec4 d = vec4(-15.0f - (sideSize-11)*1.2f + float(xx) * 3.0f, -15.0f - (sideSize-11)*1.4f + float(yy) * 3.0f, max(0.0f, (sideSize-11.0f)*3.0f), 1.0f);

		vec4 color;
		color.x = sin(time + float(xx) / 11.0f) * 0.5f + 0.5f;
		color.y = cos(time + float(yy) / 11.0f) * 0.5f + 0.5f;
		color.z = sin(time * 3.0f) * 0.5f + 0.5f;
		color.w = 1.0f;

		instanceBufferOut[k*5+0] = a;
		instanceBufferOut[k*5+1] = b;
		instanceBufferOut[k*5+2] = c;
		instanceBufferOut[k*5+3] = d;
		instanceBufferOut[k*5+4] = color;
		}

	// Fill indirect buffer

	for (int k = idxStart; k < idxMax; k++) {
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

	#ifdef INDIRECT_COUNT
	if (tId == 0)
	{
		// If BGFX_CAPS_DRAW_INDIRECT_COUNT is supported, you can limit the
		// number of draw calls dynamically without a CPU round trip
		indirectCountBuffer[0] = maxToDraw;
	}
	#endif
}
