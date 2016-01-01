/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh"
#include "uniforms.sh"

BUFFER_WR(prevPositionBuffer, vec4, 0);
BUFFER_WR(currPositionBuffer, vec4, 1);

uint rotl(uint _x, uint _r)
{
	return (_x << _r) | (_x >> (32u - _r) );
}

uint hash(uint _key, uint _seed)
{
	uint c1 = 0xcc9e2d51u;
	uint c2 = 0x1b873593u;

	uint k1 = _key;
	uint h1 = _seed;
	k1 *= c1;
	k1 = rotl(k1, 15u);
	k1 *= c2;

	h1 ^= k1;
	h1 = rotl(h1, 13u);
	h1 = h1 * 5u + 0xe6546b64u;
	k1 *= c1;
	k1 = rotl(k1, 15u);
	k1 *= c2;
	h1 ^= k1;

	h1 ^= h1 >> uint(16u);
	h1 *= 0x85ebca6bu;
	h1 ^= h1 >> 13u;
	h1 *= 0xc2b2ae35u;
	h1 ^= h1 >> 16u;

	return h1;
}

vec3 randomPointOnSphere(uint _id, uint _seed)
{
	uvec2 u = uvec2(
			hash(_id, _seed + 0u),
			hash(_id, _seed + 1u)
			);
	vec2 v = uintBitsToFloat( (u >> 9u) | 0x3f800000u) - 1.0;

	float lambda = v.x * 3.14159 * 2.0;
	float phi = acos(2.0 * v.y - 1.0) - 3.14159 / 2.0;

	vec3 p;
	p.x = cos(lambda) * cos(phi);
	p.y = sin(phi);
	p.z = sin(lambda) * cos(phi);

	return p;
}

NUM_THREADS(512, 1, 1)
void main()
{
	uint key = gl_GlobalInvocationID.x;

	vec3 position;

	if (u_initialShape == 0u)
	{
		position = vec3_splat(0.0);
	}
	else if (u_initialShape == 1u)
	{
		position = 20.0 * randomPointOnSphere(gl_GlobalInvocationID.x, u_baseSeed * 7u);
	}
	else if (u_initialShape == 2u)
	{
		uvec3 u = uvec3(
				hash(gl_GlobalInvocationID.x, u_baseSeed * 7u + 0u),
				hash(gl_GlobalInvocationID.x, u_baseSeed * 7u + 1u),
				hash(gl_GlobalInvocationID.x, u_baseSeed * 7u + 2u)
				);
		position = 20.0 * (uintBitsToFloat((u >> 9u) | uvec3(0x40000000, 0x40000000, 0x40000000) ) - 3.0);
	}
	else
	{
		uvec3 u = uvec3(
				hash(gl_GlobalInvocationID.x, u_baseSeed * 7u + 0u),
				hash(gl_GlobalInvocationID.x, u_baseSeed * 7u + 1u),
				hash(gl_GlobalInvocationID.x, u_baseSeed * 7u + 2u)
				);
		vec3 v = 3.14159 * 2.0 * (uintBitsToFloat( (u >> 9u) | uvec3(0x3f800000u, 0x3f800000u, 0x3f800000u) ) - 1.0);
		position.x = 20.0 * cos(v.x) + 3.0 * cos(v.y) * cos(v.x);
		position.y = 3.0 * sin(v.y);
		position.z = 20.0 * sin(v.x) + 3.0 * cos(v.y) * sin(v.x);
	}

	vec3 velocity = u_initialSpeed * randomPointOnSphere(gl_GlobalInvocationID.x, u_baseSeed * 7u + 3u);

	prevPositionBuffer[gl_GlobalInvocationID.x] = vec4(position - velocity * u_timeStep, 0.0);
	currPositionBuffer[gl_GlobalInvocationID.x] = vec4(position, 0.0);
}
