/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh"
#include "instance_data.sh"

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_instanceCount;
BGFX_END_UNIFORM_BLOCK

BUFFER_RW(instanceData, InstanceData, 0);

mat4 getTransform(float time, uint indexX, uint indexY)
{
	float ax = time + float(indexX) * 0.21;
	float ay = time + float(indexY) * 0.37;

	float sx = sin(ax);
	float cx = cos(ax);
	float sy = sin(ay);
	float cy = cos(ay);

	vec4 r0 = vec4(cy, 0.0, sy, 0.0);
	vec4 r1 = vec4(sx * sy, cx, -sx * cy, 0.0);
	vec4 r2 = vec4(-cx * sy, sx, cx * cy, 0.0);
	vec4 r3 = vec4(-15.0f + float(indexX) * 3.0f, -15.0f + float(indexY) * 3.0f, (sx * sy) * 4.0, 1.0);

	return mtxFromCols(r0, r1, r2, r3);
}

NUM_THREADS(16, 16, 1)
void main() 
{
	uint sideSize = uint(u_instanceCount.x);
	float time = u_instanceCount.y;

	uint indexX = gl_GlobalInvocationID.x;
	uint indexY = gl_GlobalInvocationID.y;

	if (indexX >= sideSize || indexY >= sideSize)
	{
		return;
	}

	uint index = indexY * sideSize + indexX;

	InstanceData data;

	data.transform = getTransform(time, indexX, indexY);
	data.color.r = sin(time + float(indexX) / 11.0f) * 0.5f + 0.5f;
	data.color.g = cos(time + float(indexY) / 11.0f) * 0.5f + 0.5f;
	data.color.b = sin(time * 3.0f) * 0.5f + 0.5f;
	data.color.a = 1.0f;

	instanceData[index] = data;
}
