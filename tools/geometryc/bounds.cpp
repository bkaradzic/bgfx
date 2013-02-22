/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/rng.h>
#include "bounds.h"
#include "math.h"

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

void aabbTransformToObb(Obb& _obb, const Aabb& _aabb, const float* _mtx)
{
	aabbToObb(_obb, _aabb);
	float result[16];
	mtxMul(result, _obb.m_mtx, _mtx);
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
		min[0] = fmin(xx, min[0]);
		min[1] = fmin(yy, min[1]);
		min[2] = fmin(zz, min[2]);
		max[0] = fmax(xx, max[0]);
		max[1] = fmax(yy, max[1]);
		max[2] = fmax(zz, max[2]);
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
	vec3MulMtx(position, (float*)vertex, _mtx);
	min[0] = max[0] = position[0];
	min[1] = max[1] = position[1];
	min[2] = max[2] = position[2];
	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		vec3MulMtx(position, (float*)vertex, _mtx);
		vertex += _stride;

		float xx = position[0];
		float yy = position[1];
		float zz = position[2];
		min[0] = fmin(xx, min[0]);
		min[1] = fmin(yy, min[1]);
		min[2] = fmin(zz, min[2]);
		max[0] = fmax(xx, max[0]);
		max[1] = fmax(yy, max[1]);
		max[2] = fmax(zz, max[2]);
	}

	_aabb.m_min[0] = min[0];
	_aabb.m_min[1] = min[1];
	_aabb.m_min[2] = min[2];
	_aabb.m_max[0] = max[0];
	_aabb.m_max[1] = max[1];
	_aabb.m_max[2] = max[2];
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
				mtxRotateXYZ(mtx, ax, ay, az);

				float mtxT[16];
				mtxTranspose(mtxT, mtx);
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
		maxDistSq = fmax(distSq, maxDistSq);
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
				maxDistSq = flerp(maxDistSq, distSq, _step);

				break;
			}
		}

	} while (!done);

	_sphere.m_center[0] = center[0];
	_sphere.m_center[1] = center[1];
	_sphere.m_center[2] = center[2];
	_sphere.m_radius = sqrtf(maxDistSq);
}
