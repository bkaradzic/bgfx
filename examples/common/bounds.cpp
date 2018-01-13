/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/rng.h>
#include <bx/math.h>
#include "bounds.h"

void aabbToObb(Obb& _obb, const Aabb& _aabb)
{
	bx::memSet(_obb.m_mtx, 0, sizeof(_obb.m_mtx) );
	_obb.m_mtx[ 0] = (_aabb.m_max[0] - _aabb.m_min[0]) * 0.5f;
	_obb.m_mtx[ 5] = (_aabb.m_max[1] - _aabb.m_min[1]) * 0.5f;
	_obb.m_mtx[10] = (_aabb.m_max[2] - _aabb.m_min[2]) * 0.5f;
	_obb.m_mtx[12] = (_aabb.m_min[0] + _aabb.m_max[0]) * 0.5f;
	_obb.m_mtx[13] = (_aabb.m_min[1] + _aabb.m_max[1]) * 0.5f;
	_obb.m_mtx[14] = (_aabb.m_min[2] + _aabb.m_max[2]) * 0.5f;
	_obb.m_mtx[15] = 1.0f;
}

void toAabb(Aabb& _aabb, const Obb& _obb)
{
	float xyz[3] = { 1.0f, 1.0f, 1.0f };

	float tmp[3];
	bx::vec3MulMtx(tmp, xyz, _obb.m_mtx);

	bx::vec3Move(_aabb.m_min, tmp);
	bx::vec3Move(_aabb.m_max, tmp);

	for (uint32_t ii = 1; ii < 8; ++ii)
	{
		xyz[0] = ii & 1 ? -1.0f : 1.0f;
		xyz[1] = ii & 2 ? -1.0f : 1.0f;
		xyz[2] = ii & 4 ? -1.0f : 1.0f;
		bx::vec3MulMtx(tmp, xyz, _obb.m_mtx);

		bx::vec3Min(_aabb.m_min, _aabb.m_min, tmp);
		bx::vec3Max(_aabb.m_max, _aabb.m_max, tmp);
	}
}

void toAabb(Aabb& _aabb, const Sphere& _sphere)
{
	float radius = _sphere.m_radius;
	bx::vec3Sub(_aabb.m_min, _sphere.m_center, radius);
	bx::vec3Add(_aabb.m_max, _sphere.m_center, radius);
}

void toAabb(Aabb& _aabb, const Disk& _disk)
{
	// Reference: http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	float nsq[3];
	bx::vec3Mul(nsq, _disk.m_normal, _disk.m_normal);

	float one[3] = { 1.0f, 1.0f, 1.0f };
	float tmp[3];
	bx::vec3Sub(tmp, one, nsq);

	const float inv = 1.0f / (tmp[0]*tmp[1]*tmp[2]);

	float extent[3];
	extent[0] = _disk.m_radius * tmp[0] * bx::sqrt( (nsq[0] + nsq[1] * nsq[2]) * inv);
	extent[1] = _disk.m_radius * tmp[1] * bx::sqrt( (nsq[1] + nsq[2] * nsq[0]) * inv);
	extent[2] = _disk.m_radius * tmp[2] * bx::sqrt( (nsq[2] + nsq[0] * nsq[1]) * inv);

	bx::vec3Sub(_aabb.m_min, _disk.m_center, extent);
	bx::vec3Add(_aabb.m_max, _disk.m_center, extent);
}

void toAabb(Aabb& _aabb, const Cylinder& _cylinder)
{
	// Reference: http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	float axis[3];
	bx::vec3Sub(axis, _cylinder.m_end, _cylinder.m_pos);

	float asq[3];
	bx::vec3Mul(asq, axis, axis);

	float nsq[3];
	bx::vec3Mul(nsq, asq, 1.0f/bx::vec3Dot(axis, axis) );

	float one[3] = { 1.0f, 1.0f, 1.0f };
	float tmp[3];
	bx::vec3Sub(tmp, one, nsq);

	const float inv = 1.0f / (tmp[0]*tmp[1]*tmp[2]);

	float extent[3];
	extent[0] = _cylinder.m_radius * tmp[0] * bx::sqrt( (nsq[0] + nsq[1] * nsq[2]) * inv);
	extent[1] = _cylinder.m_radius * tmp[1] * bx::sqrt( (nsq[1] + nsq[2] * nsq[0]) * inv);
	extent[2] = _cylinder.m_radius * tmp[2] * bx::sqrt( (nsq[2] + nsq[0] * nsq[1]) * inv);

	float minP[3];
	bx::vec3Sub(minP, _cylinder.m_pos, extent);

	float minE[3];
	bx::vec3Sub(minE, _cylinder.m_end, extent);

	float maxP[3];
	bx::vec3Add(maxP, _cylinder.m_pos, extent);

	float maxE[3];
	bx::vec3Add(maxE, _cylinder.m_end, extent);

	bx::vec3Min(_aabb.m_min, minP, minE);
	bx::vec3Max(_aabb.m_max, maxP, maxE);
}

void aabbTransformToObb(Obb& _obb, const Aabb& _aabb, const float* _mtx)
{
	aabbToObb(_obb, _aabb);
	float result[16];
	bx::mtxMul(result, _obb.m_mtx, _mtx);
	bx::memCopy(_obb.m_mtx, result, sizeof(result) );
}

void toAabb(Aabb& _aabb, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
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
		min[0] = bx::min(xx, min[0]);
		min[1] = bx::min(yy, min[1]);
		min[2] = bx::min(zz, min[2]);
		max[0] = bx::max(xx, max[0]);
		max[1] = bx::max(yy, max[1]);
		max[2] = bx::max(zz, max[2]);
	}

	_aabb.m_min[0] = min[0];
	_aabb.m_min[1] = min[1];
	_aabb.m_min[2] = min[2];
	_aabb.m_max[0] = max[0];
	_aabb.m_max[1] = max[1];
	_aabb.m_max[2] = max[2];
}

void toAabb(Aabb& _aabb, const float* _mtx, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
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
		min[0] = bx::min(xx, min[0]);
		min[1] = bx::min(yy, min[1]);
		min[2] = bx::min(zz, min[2]);
		max[0] = bx::max(xx, max[0]);
		max[1] = bx::max(yy, max[1]);
		max[2] = bx::max(zz, max[2]);
	}

	_aabb.m_min[0] = min[0];
	_aabb.m_min[1] = min[1];
	_aabb.m_min[2] = min[2];
	_aabb.m_max[0] = max[0];
	_aabb.m_max[1] = max[1];
	_aabb.m_max[2] = max[2];
}

float calcAreaAabb(const Aabb& _aabb)
{
	float ww = _aabb.m_max[0] - _aabb.m_min[0];
	float hh = _aabb.m_max[1] - _aabb.m_min[1];
	float dd = _aabb.m_max[2] - _aabb.m_min[2];
	return 2.0f * (ww*hh + ww*dd + hh*dd);
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

void aabbExpand(Aabb& _aabb, const float* _pos)
{
	bx::vec3Min(_aabb.m_min, _aabb.m_min, _pos);
	bx::vec3Max(_aabb.m_max, _aabb.m_max, _pos);
}

uint32_t aabbOverlapTest(const Aabb& _aabb0, const Aabb& _aabb1)
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
	toAabb(aabb, _vertices, _numVertices, _stride);
	float minArea = calcAreaAabb(aabb);

	Obb best;
	aabbToObb(best, aabb);

	float angleStep = float(bx::kPiHalf/_steps);
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
				toAabb(aabb, mtxT, _vertices, _numVertices, _stride);

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

	bx::memCopy(&_obb, &best, sizeof(Obb) );
}

void calcMaxBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Aabb aabb;
	toAabb(aabb, _vertices, _numVertices, _stride);

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
		maxDistSq = bx::max(distSq, maxDistSq);
	}

	bx::vec3Move(_sphere.m_center, center);
	_sphere.m_radius = bx::sqrt(maxDistSq);
}

void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step)
{
	bx::RngMwc rng;

	uint8_t* vertex = (uint8_t*)_vertices;

	float center[3];
	float* position = (float*)&vertex[0];
	bx::vec3Move(center, position);

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

			xx = position[0] - center[0];
			yy = position[1] - center[1];
			zz = position[2] - center[2];
			float distSq = xx*xx + yy*yy + zz*zz;

			if (distSq > maxDistSq)
			{
				done = false;

				center[0] += xx * radiusStep;
				center[1] += yy * radiusStep;
				center[2] += zz * radiusStep;
				maxDistSq = bx::lerp(maxDistSq, distSq, _step);

				break;
			}
		}

	} while (!done);

	bx::vec3Move(_sphere.m_center, center);
	_sphere.m_radius = bx::sqrt(maxDistSq);
}

void calcPlaneUv(const Plane& _plane, float* _udir, float* _vdir)
{
	bx::vec3TangentFrame(_plane.m_normal, _udir, _vdir);
}

void buildFrustumPlanes(Plane* _result, const float* _viewProj)
{
	const float xw = _viewProj[ 3];
	const float yw = _viewProj[ 7];
	const float zw = _viewProj[11];
	const float ww = _viewProj[15];

	const float xz = _viewProj[ 2];
	const float yz = _viewProj[ 6];
	const float zz = _viewProj[10];
	const float wz = _viewProj[14];

	Plane& near   = _result[0];
	Plane& far    = _result[1];
	Plane& left   = _result[2];
	Plane& right  = _result[3];
	Plane& top    = _result[4];
	Plane& bottom = _result[5];

	near.m_normal[0] = xw - xz;
	near.m_normal[1] = yw - yz;
	near.m_normal[2] = zw - zz;
	near.m_dist      = ww - wz;

	far.m_normal[0] = xw + xz;
	far.m_normal[1] = yw + yz;
	far.m_normal[2] = zw + zz;
	far.m_dist      = ww + wz;

	const float xx = _viewProj[ 0];
	const float yx = _viewProj[ 4];
	const float zx = _viewProj[ 8];
	const float wx = _viewProj[12];

	left.m_normal[0] = xw - xx;
	left.m_normal[1] = yw - yx;
	left.m_normal[2] = zw - zx;
	left.m_dist      = ww - wx;

	right.m_normal[0] = xw + xx;
	right.m_normal[1] = yw + yx;
	right.m_normal[2] = zw + zx;
	right.m_dist      = ww + wx;

	const float xy = _viewProj[ 1];
	const float yy = _viewProj[ 5];
	const float zy = _viewProj[ 9];
	const float wy = _viewProj[13];

	top.m_normal[0] = xw + xy;
	top.m_normal[1] = yw + yy;
	top.m_normal[2] = zw + zy;
	top.m_dist      = ww + wy;

	bottom.m_normal[0] = xw - xy;
	bottom.m_normal[1] = yw - yy;
	bottom.m_normal[2] = zw - zy;
	bottom.m_dist      = ww - wy;

	Plane* plane = _result;
	for (uint32_t ii = 0; ii < 6; ++ii)
	{
		float invLen = 1.0f / bx::vec3Norm(plane->m_normal, plane->m_normal);
		plane->m_dist *= invLen;
		++plane;
	}
}

void intersectPlanes(float _result[3], const Plane& _pa, const Plane& _pb, const Plane& _pc)
{
	float axb[3];
	bx::vec3Cross(axb, _pa.m_normal, _pb.m_normal);

	float bxc[3];
	bx::vec3Cross(bxc, _pb.m_normal, _pc.m_normal);

	float cxa[3];
	bx::vec3Cross(cxa, _pc.m_normal, _pa.m_normal);

	float tmp0[3];
	bx::vec3Mul(tmp0, bxc, _pa.m_dist);

	float tmp1[3];
	bx::vec3Mul(tmp1, cxa, _pb.m_dist);

	float tmp2[3];
	bx::vec3Mul(tmp2, axb, _pc.m_dist);

	float tmp[3];
	bx::vec3Add(tmp, tmp0, tmp1);
	bx::vec3Add(tmp0, tmp, tmp2);

	float denom = bx::vec3Dot(_pa.m_normal, bxc);
	bx::vec3Mul(_result, tmp0, -1.0f/denom);
}

Ray makeRay(float _x, float _y, const float* _invVp)
{
	Ray ray;

	const float near[3] = { _x, _y, 0.0f };
	bx::vec3MulMtxH(ray.m_pos, near, _invVp);

	float tmp[3];
	const float far[3]  = { _x, _y, 1.0f };
	bx::vec3MulMtxH(tmp, far, _invVp);

	float dir[3];
	bx::vec3Sub(dir, tmp, ray.m_pos);
	bx::vec3Norm(ray.m_dir, dir);

	return ray;
}

inline void getPointAt(float* _result, const Ray& _ray, float _t)
{
	float tmp[3];
	bx::vec3Mul(tmp, _ray.m_dir, _t);
	bx::vec3Add(_result, _ray.m_pos, tmp);
}

bool intersect(const Ray& _ray, const Aabb& _aabb, Hit* _hit)
{
	float invDir[3];
	bx::vec3Rcp(invDir, _ray.m_dir);

	float tmp[3];

	float t0[3];
	bx::vec3Sub(tmp, _aabb.m_min, _ray.m_pos);
	bx::vec3Mul(t0, tmp, invDir);

	float t1[3];
	bx::vec3Sub(tmp, _aabb.m_max, _ray.m_pos);
	bx::vec3Mul(t1, tmp, invDir);

	float min[3];
	bx::vec3Min(min, t0, t1);

	float max[3];
	bx::vec3Max(max, t0, t1);

	const float tmin = bx::max(min[0], min[1], min[2]);
	const float tmax = bx::min(max[0], max[1], max[2]);

	if (tmax < 0.0f
	||  tmin > tmax)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->m_normal[0] = float( (t1[0] == tmin) - (t0[0] == tmin) );
		_hit->m_normal[1] = float( (t1[1] == tmin) - (t0[1] == tmin) );
		_hit->m_normal[2] = float( (t1[2] == tmin) - (t0[2] == tmin) );

		_hit->m_dist = tmin;
		getPointAt(_hit->m_pos, _ray, tmin);
	}

	return true;
}

static const Aabb s_kUnitAabb =
{
	{ -1.0f, -1.0f, -1.0f },
	{  1.0f,  1.0f,  1.0f },
};

bool intersect(const Ray& _ray, const Obb& _obb, Hit* _hit)
{
	Aabb aabb;
	toAabb(aabb, _obb);

	if (!intersect(_ray, aabb) )
	{
		return false;
	}

	float mtxInv[16];
	bx::mtxInverse(mtxInv, _obb.m_mtx);

	Ray obbRay;
	bx::vec3MulMtx(obbRay.m_pos, _ray.m_pos, mtxInv);
	bx::vec3MulMtxXyz0(obbRay.m_dir, _ray.m_dir, mtxInv);

	if (intersect(obbRay, s_kUnitAabb, _hit) )
	{
		if (NULL != _hit)
		{
			float tmp[3];
			bx::vec3MulMtx(tmp, _hit->m_pos, _obb.m_mtx);
			bx::vec3Move(_hit->m_pos, tmp);

			bx::vec3MulMtxXyz0(tmp, _hit->m_normal, _obb.m_mtx);
			bx::vec3Norm(_hit->m_normal, tmp);
		}

		return true;
	}

	return false;
}

bool intersect(const Ray& _ray, const Disk& _disk, Hit* _hit)
{
	Plane plane;
	bx::vec3Move(plane.m_normal, _disk.m_normal);
	plane.m_dist = -bx::vec3Dot(_disk.m_center, _disk.m_normal);

	Hit tmpHit;
	_hit = NULL != _hit ? _hit : &tmpHit;

	if (intersect(_ray, plane, _hit) )
	{
		float tmp[3];
		bx::vec3Sub(tmp, _disk.m_center, _hit->m_pos);
		return bx::vec3Dot(tmp, tmp) <= bx::square(_disk.m_radius);
	}

	return false;
}

static bool intersect(const Ray& _ray, const Cylinder& _cylinder, bool _capsule, Hit* _hit)
{
	float axis[3];
	bx::vec3Sub(axis, _cylinder.m_end, _cylinder.m_pos);

	float rc[3];
	bx::vec3Sub(rc, _ray.m_pos, _cylinder.m_pos);

	float normal[3];
	bx::vec3Cross(normal, _ray.m_dir, axis);

	const float len  = bx::vec3Norm(normal, normal);
	const float dist = bx::abs(bx::vec3Dot(rc, normal) );

	if (dist > _cylinder.m_radius)
	{
		return false;
	}

	float vo[3];
	bx::vec3Cross(vo, rc, axis);
	const float t0 = -bx::vec3Dot(vo, normal) / len;

	bx::vec3Cross(vo, normal, axis);
	bx::vec3Norm(vo, vo);

	const float rsq   = bx::square(_cylinder.m_radius);
	const float ddoto = bx::vec3Dot(_ray.m_dir, vo);
	const float ss    = t0 - bx::abs(bx::sqrt(rsq - bx::square(dist) ) / ddoto);

	if (0.0f > ss)
	{
		return false;
	}

	float point[3];
	getPointAt(point, _ray, ss);

	const float axisLen = bx::vec3Norm(axis, axis);
	const float pdota   = bx::vec3Dot(_cylinder.m_pos, axis);
	const float height  = bx::vec3Dot(point, axis) - pdota;

	if (height > 0.0f
	&&  height < axisLen)
	{
		if (NULL != _hit)
		{
			const float t1 = height / axisLen;
			float pointOnAxis[3];
			bx::vec3Lerp(pointOnAxis, _cylinder.m_pos, _cylinder.m_end, t1);

			bx::vec3Move(_hit->m_pos, point);

			float tmp[3];
			bx::vec3Sub(tmp, point, pointOnAxis);
			bx::vec3Norm(_hit->m_normal, tmp);

			_hit->m_dist = ss;
		}

		return true;
	}

	if (_capsule)
	{
		const float rdota = bx::vec3Dot(_ray.m_pos, axis);
		const float pp    = rdota - pdota;
		const float t1    = pp / axisLen;

		float pointOnAxis[3];
		bx::vec3Lerp(pointOnAxis, _cylinder.m_pos, _cylinder.m_end, t1);

		float axisToRay[3];
		bx::vec3Sub(axisToRay, _ray.m_pos, pointOnAxis);

		if (_cylinder.m_radius < bx::vec3Length(axisToRay)
		&&  0.0f > ss)
		{
			return false;
		}

		Sphere sphere;
		sphere.m_radius = _cylinder.m_radius;

		bx::vec3Move(sphere.m_center, 0.0f >= height
			? _cylinder.m_pos
			: _cylinder.m_end
			);

		return intersect(_ray, sphere, _hit);
	}

	Plane plane;
	float pos[3];

	if (0.0f >= height)
	{
		bx::vec3Neg(plane.m_normal, axis);
		bx::vec3Move(pos, _cylinder.m_pos);
	}
	else
	{
		bx::vec3Move(plane.m_normal, axis);
		bx::vec3Move(pos, _cylinder.m_end);
	}

	plane.m_dist = -bx::vec3Dot(pos, plane.m_normal);

	Hit tmpHit;
	_hit = NULL != _hit ? _hit : &tmpHit;

	if (intersect(_ray, plane, _hit) )
	{
		float tmp[3];
		bx::vec3Sub(tmp, pos, _hit->m_pos);
		return bx::vec3Dot(tmp, tmp) <= rsq;
	}

	return false;
}

bool intersect(const Ray& _ray, const Cylinder& _cylinder, Hit* _hit)
{
	return intersect(_ray, _cylinder, false, _hit);
}

bool intersect(const Ray& _ray, const Capsule& _capsule, Hit* _hit)
{
	BX_STATIC_ASSERT(sizeof(Capsule) == sizeof(Cylinder) );
	return intersect(_ray, *( (const Cylinder*)&_capsule), true, _hit);
}

bool intersect(const Ray& _ray, const Cone& _cone, Hit* _hit)
{
	float axis[3];
	bx::vec3Sub(axis, _cone.m_pos, _cone.m_end);

	float normal[3];
	const float len = bx::vec3Norm(normal, axis);

	Disk disk;
	bx::vec3Move(disk.m_center, _cone.m_pos);
	bx::vec3Move(disk.m_normal, normal);
	disk.m_radius = _cone.m_radius;

	Hit tmpInt;
	Hit* out = NULL != _hit ? _hit : &tmpInt;
	bool hit = intersect(_ray, disk, out);

	float ro[3];
	bx::vec3Sub(ro, _ray.m_pos, _cone.m_end);

	const float hyp    = bx::sqrt(bx::square(_cone.m_radius) + bx::square(len) );
	const float cosaSq = bx::square(len/hyp);
	const float ndoto  = bx::vec3Dot(normal, ro);
	const float ndotd  = bx::vec3Dot(normal, _ray.m_dir);

	const float aa = bx::square(ndotd) - cosaSq;
	const float bb = 2.0f * (ndotd*ndoto - bx::vec3Dot(_ray.m_dir, ro)*cosaSq);
	const float cc = bx::square(ndoto) - bx::vec3Dot(ro, ro)*cosaSq;

	float det = bb*bb - 4.0f*aa*cc;

	if (0.0f > det)
	{
		return hit;
	}

	det = bx::sqrt(det);
	const float invA2 = 1.0f / (2.0f*aa);
	const float t1 = (-bb - det) * invA2;
	const float t2 = (-bb + det) * invA2;

	float tt = t1;
	if (0.0f > t1
	|| (0.0f < t2 && t2 < t1) )
	{
		tt = t2;
	}

	if (0.0f > tt)
	{
		return hit;
	}

	float hitPos[3];
	getPointAt(hitPos, _ray, tt);

	float point[3];
	bx::vec3Sub(point, hitPos, _cone.m_end);

	const float hh = bx::vec3Dot(normal, point);

	if (0.0f > hh
	||  len  < hh)
	{
		return hit;
	}

	if (NULL != _hit)
	{
		if (!hit
		||  tt < _hit->m_dist)
		{
			_hit->m_dist = tt;

			bx::vec3Move(_hit->m_pos, hitPos);

			const float scale = hh / bx::vec3Dot(point, point);
			float pointScaled[3];
			bx::vec3Mul(pointScaled, point, scale);

			float tmp[3];
			bx::vec3Sub(tmp, pointScaled, normal);
			bx::vec3Norm(_hit->m_normal, tmp);
		}
	}

	return true;
}

bool intersect(const Ray& _ray, const Plane& _plane, Hit* _hit)
{
	float equation = bx::vec3Dot(_ray.m_pos, _plane.m_normal) + _plane.m_dist;
	if (0.0f > equation)
	{
		return false;
	}

	float ndotd = bx::vec3Dot(_ray.m_dir, _plane.m_normal);
	if (0.0f < ndotd)
	{
		return false;
	}

	if (NULL != _hit)
	{
		bx::vec3Move(_hit->m_normal, _plane.m_normal);

		float tt = -equation/ndotd;
		_hit->m_dist = tt;

		getPointAt(_hit->m_pos, _ray, tt);
	}

	return true;
}

bool intersect(const Ray& _ray, const Sphere& _sphere, Hit* _hit)
{
	float rs[3];
	bx::vec3Sub(rs, _ray.m_pos, _sphere.m_center);

	const float bb = bx::vec3Dot(rs, _ray.m_dir);
	if (0.0f < bb)
	{
		return false;
	}

	const float aa = bx::vec3Dot(_ray.m_dir, _ray.m_dir);
	const float cc = bx::vec3Dot(rs, rs) - bx::square(_sphere.m_radius);

	const float discriminant = bb*bb - aa*cc;

	if (0.0f >= discriminant)
	{
		return false;
	}

	const float sqrtDiscriminant = bx::sqrt(discriminant);
	const float invA = 1.0f / aa;
	const float tt = -(bb + sqrtDiscriminant)*invA;

	if (0.0f >= tt)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->m_dist = tt;

		float point[3];
		getPointAt(point, _ray, tt);
		bx::vec3Move(_hit->m_pos, point);

		float tmp[3];
		bx::vec3Sub(tmp, point, _sphere.m_center);
		bx::vec3Norm(_hit->m_normal, tmp);
	}

	return true;
}

bool intersect(const Ray& _ray, const Tris& _triangle, Hit* _hit)
{
	float edge10[3];
	bx::vec3Sub(edge10, _triangle.m_v1, _triangle.m_v0);

	float edge02[3];
	bx::vec3Sub(edge02, _triangle.m_v0, _triangle.m_v2);

	float normal[3];
	bx::vec3Cross(normal, edge02, edge10);

	float vo[3];
	bx::vec3Sub(vo, _triangle.m_v0, _ray.m_pos);

	float dxo[3];
	bx::vec3Cross(dxo, _ray.m_dir, vo);

	const float det = bx::vec3Dot(normal, _ray.m_dir);

	if (det > 0.0f)
	{
		return false;
	}

	const float invDet = 1.0f/det;
	const float bz = bx::vec3Dot(dxo, edge02) * invDet;
	const float by = bx::vec3Dot(dxo, edge10) * invDet;
	const float bx = 1.0f - by - bz;

	if (bx < 0.0f || by < 0.0f || bz < 0.0f)
	{
		return false;
	}

	if (NULL != _hit)
	{
		bx::vec3Norm(_hit->m_normal, normal);

		const float tt = bx::vec3Dot(normal, vo) * invDet;
		_hit->m_dist = tt;

		getPointAt(_hit->m_pos, _ray, tt);
	}

	return true;
}
