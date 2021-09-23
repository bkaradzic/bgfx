/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#ifndef SHARED_FUNCTIONS_SH
#define SHARED_FUNCTIONS_SH

vec2 GetTexCoordPreviousNoJitter(vec2 texCoord, vec2 velocity)
{
	vec2 texCoordPrev = texCoord - velocity;
	return texCoordPrev;
}

vec2 GetTexCoordPrevious(vec2 texCoord, vec2 velocity)
{
	vec2 texCoordPrev = texCoord - velocity;

	vec2 jitterDelta = (u_jitterCurr-u_jitterPrev);
	texCoordPrev += jitterDelta * u_viewTexel.xy;

	return texCoordPrev;
}

#endif // SHARED_FUNCTIONS_SH
