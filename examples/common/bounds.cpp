/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/rng.h>
#include <bx/fpumath.h>
#include "bounds.h"

void aabbToObb(Obb& _obb, const Aabb& _aabb)
{
	memset(_obb.m_mtx, 0, sizeof(_obb.m_mtx) );
	_obb.m_mtx[ 0] = (_aabb.m_max[0] - _aabb.m_min[0]) * 0.5f;
	_obb.m_mtx[ 5] = (_aabb.m_max[1] - _aabb.m_min[1]) * 0.5f;
	_obb.m_mtx[10] = (_aabb.m_max[2] - _aabb.m_min[2]) * 0.5f;
	_obb.m_mtx[12] = (_aabb.m_min[0] + _aabb.m_max[0]) * 0.5f;
	_obb.m_mtx[13] = (_aabb.m_min[1] + _aabb.m_max[1]) * 0.5f;
	_obb.m_mtx[14] = (_aabb.m_min[2] + _aabb.m_max[2]) * 0.5f;
	_obb.m_mtx[15] = 1.0f;
}

void sphereToAabb(Aabb& _aabb, const Sphere& _sphere)
{
	float xx = _sphere.m_center[0];
	float yy = _sphere.m_center[1];
	float zz = _sphere.m_center[2];
	float radius = _sphere.m_radius;
	_aabb.m_min[0] = xx - radius;
	_aabb.m_min[1] = yy - radius;
	_aabb.m_min[2] = zz - radius;
	_aabb.m_max[0] = xx + radius;
	_aabb.m_max[1] = yy + radius;
	_aabb.m_max[2] = zz + radius;
}

void aabbTransformToObb(Obb& _obb, const Aabb& _aabb, const float* _mtx)
{
	aabbToObb(_obb, _aabb);
	float result[16];
	bx::mtxMul(result, _obb.m_mtx, _mtx);
	memcpy(_obb.m_mtx, result, sizeof(result) );
}

float calcAreaAabb(Aabb& _aabb)
{
	float ww = _aabb.m_max[0] - _aabb.m_min[0];
	float hh = _aabb.m_max[1] - _aabb.m_min[1];
	float dd = _aabb.m_max[2] - _aabb.m_min[2];
	return 2.0f * (ww*hh + ww*dd + hh*dd);
}

void calcAabb(Aabb& _aabb, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	float min[3], max[3];
	uint8_t* vertex = (uint8_t*)_vertices;
	float* position = (float*)vertex;
	min[0] = max[0] = position[0];
	min[1] = max[1] = position[1];
	min[2] = max[2] = position[2];
	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		position = (float*)vertex;
		vertex += _stride;

		float xx = position[0];
		float yy = position[1];
		float zz = position[2];
		min[0] = bx::fmin(xx, min[0]);
		min[1] = bx::fmin(yy, min[1]);
		min[2] = bx::fmin(zz, min[2]);
		max[0] = bx::fmax(xx, max[0]);
		max[1] = bx::fmax(yy, max[1]);
		max[2] = bx::fmax(zz, max[2]);
	}

	_aabb.m_min[0] = min[0];
	_aabb.m_min[1] = min[1];
	_aabb.m_min[2] = min[2];
	_aabb.m_max[0] = max[0];
	_aabb.m_max[1] = max[1];
	_aabb.m_max[2] = max[2];
}

void calcAabb(Aabb& _aabb, const float* _mtx, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	float min[3], max[3];
	uint8_t* vertex = (uint8_t*)_vertices;

	float position[3];
	bx::vec3MulMtx(position, (float*)vertex, _mtx);
	min[0] = max[0] = position[0];
	min[1] = max[1] = position[1];
	min[2] = max[2] = position[2];
	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		bx::vec3MulMtx(position, (float*)vertex, _mtx);
		vertex += _stride;

		float xx = position[0];
		float yy = position[1];
		float zz = position[2];
		min[0] = bx::fmin(xx, min[0]);
		min[1] = bx::fmin(yy, min[1]);
		min[2] = bx::fmin(zz, min[2]);
		max[0] = bx::fmax(xx, max[0]);
		max[1] = bx::fmax(yy, max[1]);
		max[2] = bx::fmax(zz, max[2]);
	}

	_aabb.m_min[0] = min[0];
	_aabb.m_min[1] = min[1];
	_aabb.m_min[2] = min[2];
	_aabb.m_max[0] = max[0];
	_aabb.m_max[1] = max[1];
	_aabb.m_max[2] = max[2];
}

void aabbExpand(Aabb& _aabb, float _factor)
{
	_aabb.m_min[0] -= _factor;
	_aabb.m_min[1] -= _factor;
	_aabb.m_min[2] -= _factor;
	_aabb.m_max[0] += _factor;
	_aabb.m_max[1] += _factor;
	_aabb.m_max[2] += _factor;
}

uint32_t aabbOverlapTest(Aabb& _aabb0, Aabb& _aabb1)
{
	const uint32_t ltMinX = _aabb0.m_max[0] < _aabb1.m_min[0];
	const uint32_t gtMaxX = _aabb0.m_min[0] > _aabb1.m_max[0];
	const uint32_t ltMinY = _aabb0.m_max[1] < _aabb1.m_min[1];
	const uint32_t gtMaxY = _aabb0.m_min[1] > _aabb1.m_max[1];
	const uint32_t ltMinZ = _aabb0.m_max[2] < _aabb1.m_min[2];
	const uint32_t gtMaxZ = _aabb0.m_min[2] > _aabb1.m_max[2];

	return 0
		| (ltMinX<<0)
		| (gtMaxX<<1)
		| (ltMinY<<2)
		| (gtMaxY<<3)
		| (ltMinZ<<4)
		| (gtMaxZ<<5)
		;
}

void calcObb(Obb& _obb, const void* _vertices, uint32_t _numVertices, uint32_t _stride, uint32_t _steps)
{
	Aabb aabb;
	calcAabb(aabb, _vertices, _numVertices, _stride);
	float minArea = calcAreaAabb(aabb);

	Obb best;
	aabbToObb(best, aabb);

	float angleStep = float(M_PI_2/_steps);
	float ax = 0.0f;
	float mtx[16];

	for (uint32_t ii = 0; ii < _steps; ++ii)
	{
		float ay = 0.0f;

		for (uint32_t jj = 0; jj < _steps; ++jj)
		{
			float az = 0.0f;

			for (uint32_t kk = 0; kk < _steps; ++kk)
			{
				bx::mtxRotateXYZ(mtx, ax, ay, az);

				float mtxT[16];
				bx::mtxTranspose(mtxT, mtx);
				calcAabb(aabb, mtxT, _vertices, _numVertices, _stride);

				float area = calcAreaAabb(aabb);
				if (area < minArea)
				{
					minArea = area;
					aabbTransformToObb(best, aabb, mtx);
				}

				az += angleStep;
			}

			ay += angleStep;
		}

		ax += angleStep;
	}

	memcpy(&_obb, &best, sizeof(Obb) );
}

void calcMaxBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Aabb aabb;
	calcAabb(aabb, _vertices, _numVertices, _stride);

	float center[3];
	center[0] = (aabb.m_min[0] + aabb.m_max[0]) * 0.5f;
	center[1] = (aabb.m_min[1] + aabb.m_max[1]) * 0.5f;
	center[2] = (aabb.m_min[2] + aabb.m_max[2]) * 0.5f;

	float maxDistSq = 0.0f;
	uint8_t* vertex = (uint8_t*)_vertices;

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		float* position = (float*)vertex;
		vertex += _stride;

		float xx = position[0] - center[0];
		float yy = position[1] - center[1];
		float zz = position[2] - center[2];

		float distSq = xx*xx + yy*yy + zz*zz;
		maxDistSq = bx::fmax(distSq, maxDistSq);
	}

	_sphere.m_center[0] = center[0];
	_sphere.m_center[1] = center[1];
	_sphere.m_center[2] = center[2];
	_sphere.m_radius = sqrtf(maxDistSq);
}

void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step)
{
	bx::RngMwc rng;

	uint8_t* vertex = (uint8_t*)_vertices;

	float center[3];
	float* position = (float*)&vertex[0];
	center[0] = position[0];
	center[1] = position[1];
	center[2] = position[2];

	position = (float*)&vertex[1*_stride];
	center[0] += position[0];
	center[1] += position[1];
	center[2] += position[2];

	center[0] *= 0.5f;
	center[1] *= 0.5f;
	center[2] *= 0.5f;

	float xx = position[0] - center[0];
	float yy = position[1] - center[1];
	float zz = position[2] - center[2];
	float maxDistSq = xx*xx + yy*yy + zz*zz;

	float radiusStep = _step * 0.37f;

	bool done;
	do 
	{
		done = true;
		for (uint32_t ii = 0, index = rng.gen()%_numVertices; ii < _numVertices; ++ii, index = (index + 1)%_numVertices)
		{
			position = (float*)&vertex[index*_stride];

			float xx = position[0] - center[0];
			float yy = position[1] - center[1];
			float zz = position[2] - center[2];
			float distSq = xx*xx + yy*yy + zz*zz;

			if (distSq > maxDistSq)
			{
				done = false;

				center[0] += xx * radiusStep;
				center[1] += yy * radiusStep;
				center[2] += zz * radiusStep;
				maxDistSq = bx::flerp(maxDistSq, distSq, _step);

				break;
			}
		}

	} while (!done);

	_sphere.m_center[0] = center[0];
	_sphere.m_center[1] = center[1];
	_sphere.m_center[2] = center[2];
	_sphere.m_radius = sqrtf(maxDistSq);
}
