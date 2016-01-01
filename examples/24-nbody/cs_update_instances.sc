/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_RO(prevPositionBuffer,    vec4, 0);
BUFFER_RO(currPositionBuffer,    vec4, 1);
BUFFER_WR(outPrevPositionBuffer, vec4, 2);
BUFFER_WR(outCurrPositionBuffer, vec4, 3);

#define GROUP_SIZE 512
SHARED vec3 otherEntries[GROUP_SIZE];

vec3 calcAcceleration(vec3 _currPosition, vec3 _otherPosition)
{
	vec3  difference = _otherPosition - _currPosition;
	float dist2 = dot(difference, difference);
	float dist6 = dist2 * dist2 * dist2;
	float invDist3 = 1.0 / (sqrt(dist6) + 0.1);
	return u_gravity * u_gravity * invDist3 * difference;
}

NUM_THREADS(GROUP_SIZE, 1, 1)
void main()
{
	vec3 prevPosition = prevPositionBuffer[gl_GlobalInvocationID.x].xyz;
	vec3 currPosition = currPositionBuffer[gl_GlobalInvocationID.x].xyz;

	vec3 newAcceleration = vec3_splat(0.0);

	for (int j = 0; j < int(u_dispatchSize); ++j)
	{
		otherEntries[gl_LocalInvocationIndex] = currPositionBuffer[j * GROUP_SIZE + int(gl_LocalInvocationIndex)].xyz;

		barrier();
		for (int i = 0; i < GROUP_SIZE; ++i)
		{
			newAcceleration += calcAcceleration(currPosition, otherEntries[i]);
		}
	}

	newAcceleration += (prevPosition - currPosition) * u_damping;
	float accelerationMagnitude = length(newAcceleration);
	float color = pow(min(accelerationMagnitude / 3.0, 1.0), 0.25);
	if (accelerationMagnitude > 0.0)
	{
		newAcceleration = normalize(newAcceleration) * min(accelerationMagnitude, u_maxAcceleration);
	}

	vec3 newPosition = 2.0 * currPosition - prevPosition + newAcceleration * u_timeStep;

	outPrevPositionBuffer[gl_GlobalInvocationID.x] = vec4(currPosition, 0.0);
	outCurrPositionBuffer[gl_GlobalInvocationID.x] = vec4(newPosition, color);
}
