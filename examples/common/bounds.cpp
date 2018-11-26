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
	_obb.m_mtx[ 0] = (_aabb.m_max.x - _aabb.m_min.x) * 0.5f;
	_obb.m_mtx[ 5] = (_aabb.m_max.y - _aabb.m_min.y) * 0.5f;
	_obb.m_mtx[10] = (_aabb.m_max.z - _aabb.m_min.z) * 0.5f;
	_obb.m_mtx[12] = (_aabb.m_min.x + _aabb.m_max.x) * 0.5f;
	_obb.m_mtx[13] = (_aabb.m_min.y + _aabb.m_max.y) * 0.5f;
	_obb.m_mtx[14] = (_aabb.m_min.z + _aabb.m_max.z) * 0.5f;
	_obb.m_mtx[15] = 1.0f;
}

void toAabb(Aabb& _aabb, const Obb& _obb)
{
	bx::Vec3 xyz = { 1.0f, 1.0f, 1.0f };
	bx::Vec3 tmp = bx::mul(xyz, _obb.m_mtx);

	_aabb.m_min = tmp;
	_aabb.m_max = tmp;

	for (uint32_t ii = 1; ii < 8; ++ii)
	{
		xyz.x = ii & 1 ? -1.0f : 1.0f;
		xyz.y = ii & 2 ? -1.0f : 1.0f;
		xyz.z = ii & 4 ? -1.0f : 1.0f;
		tmp = bx::mul(xyz, _obb.m_mtx);

		_aabb.m_min = bx::min(_aabb.m_min, tmp);
		_aabb.m_max = bx::max(_aabb.m_max, tmp);
	}
}

void toAabb(Aabb& _aabb, const Sphere& _sphere)
{
	const float radius = _sphere.m_radius;
	_aabb.m_min = bx::sub(_sphere.m_center, radius);
	_aabb.m_max = bx::add(_sphere.m_center, radius);
}

void toAabb(Aabb& _aabb, const Disk& _disk)
{
	// Reference(s):
	// - https://web.archive.org/web/20181113055756/http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	//
	const bx::Vec3 nsq = bx::mul(_disk.m_normal, _disk.m_normal);
	const bx::Vec3 one = { 1.0f, 1.0f, 1.0f };
	const bx::Vec3 tmp = bx::sub(one, nsq);
	const float inv = 1.0f / (tmp.x*tmp.y*tmp.z);

	const bx::Vec3 extent =
	{
		_disk.m_radius * tmp.x * bx::sqrt((nsq.x + nsq.y * nsq.z) * inv),
		_disk.m_radius * tmp.y * bx::sqrt((nsq.y + nsq.z * nsq.x) * inv),
		_disk.m_radius * tmp.z * bx::sqrt((nsq.z + nsq.x * nsq.y) * inv),
	};

	_aabb.m_min = bx::sub(_disk.m_center, extent);
	_aabb.m_max = bx::add(_disk.m_center, extent);
}

void toAabb(Aabb& _aabb, const Cylinder& _cylinder)
{
	// Reference(s):
	// - https://web.archive.org/web/20181113055756/http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	//
	const bx::Vec3 axis = bx::sub(_cylinder.m_end, _cylinder.m_pos);
	const bx::Vec3 asq  = bx::mul(axis, axis);
	const bx::Vec3 nsq  = bx::mul(asq, 1.0f/bx::dot(axis, axis) );
	const bx::Vec3 one  = { 1.0f, 1.0f, 1.0f };
	const bx::Vec3 tmp  = bx::sub(one, nsq);

	const float inv = 1.0f / (tmp.x*tmp.y*tmp.z);

	const bx::Vec3 extent =
	{
		_cylinder.m_radius * tmp.x * bx::sqrt( (nsq.x + nsq.y * nsq.z) * inv),
		_cylinder.m_radius * tmp.y * bx::sqrt( (nsq.y + nsq.z * nsq.x) * inv),
		_cylinder.m_radius * tmp.z * bx::sqrt( (nsq.z + nsq.x * nsq.y) * inv),
	};

	const bx::Vec3 minP = bx::sub(_cylinder.m_pos, extent);
	const bx::Vec3 minE = bx::sub(_cylinder.m_end, extent);
	const bx::Vec3 maxP = bx::add(_cylinder.m_pos, extent);
	const bx::Vec3 maxE = bx::add(_cylinder.m_end, extent);

	_aabb.m_min = bx::min(minP, minE);
	_aabb.m_max = bx::max(maxP, maxE);
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
	bx::Vec3 min, max;
	uint8_t* vertex = (uint8_t*)_vertices;
	float* position = (float*)vertex;
	min.x = max.x = position[0];
	min.y = max.y = position[1];
	min.z = max.z = position[2];
	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		position = (float*)vertex;
		vertex += _stride;

		bx::Vec3 pos =
		{
			position[0],
			position[1],
			position[2],
		};
		min = bx::min(pos, min);
		max = bx::max(pos, max);
	}

	_aabb.m_min = min;
	_aabb.m_max = max;
}

void toAabb(Aabb& _aabb, const float* _mtx, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	bx::Vec3 min, max;
	uint8_t* vertex = (uint8_t*)_vertices;

	float position[3];
	bx::vec3MulMtx(position, (float*)vertex, _mtx);
	min.x = max.x = position[0];
	min.y = max.y = position[1];
	min.z = max.z = position[2];
	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		bx::vec3MulMtx(position, (float*)vertex, _mtx);
		vertex += _stride;

		bx::Vec3 pos =
		{
			position[0],
			position[1],
			position[2],
		};
		min = bx::min(pos, min);
		max = bx::max(pos, max);
	}

	_aabb.m_min = min;
	_aabb.m_max = max;
}

float calcAreaAabb(const Aabb& _aabb)
{
	const float ww = _aabb.m_max.x - _aabb.m_min.x;
	const float hh = _aabb.m_max.y - _aabb.m_min.y;
	const float dd = _aabb.m_max.z - _aabb.m_min.z;
	return 2.0f * (ww*hh + ww*dd + hh*dd);
}

void aabbExpand(Aabb& _aabb, float _factor)
{
	_aabb.m_min.x -= _factor;
	_aabb.m_min.y -= _factor;
	_aabb.m_min.z -= _factor;
	_aabb.m_max.x += _factor;
	_aabb.m_max.y += _factor;
	_aabb.m_max.z += _factor;
}

void aabbExpand(Aabb& _aabb, const float* _pos)
{
	const bx::Vec3 pos = { _pos[0], _pos[1], _pos[2] };
	_aabb.m_min = bx::min(_aabb.m_min, pos);
	_aabb.m_max = bx::max(_aabb.m_max, pos);
}

uint32_t aabbOverlapTest(const Aabb& _aabb0, const Aabb& _aabb1)
{
	const uint32_t ltMinX = _aabb0.m_max.x < _aabb1.m_min.x;
	const uint32_t gtMaxX = _aabb0.m_min.x > _aabb1.m_max.x;
	const uint32_t ltMinY = _aabb0.m_max.y < _aabb1.m_min.y;
	const uint32_t gtMaxY = _aabb0.m_min.y > _aabb1.m_max.y;
	const uint32_t ltMinZ = _aabb0.m_max.z < _aabb1.m_min.z;
	const uint32_t gtMaxZ = _aabb0.m_min.z > _aabb1.m_max.z;

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

	bx::Vec3 center =
	{
		(aabb.m_min.x + aabb.m_max.x) * 0.5f,
		(aabb.m_min.y + aabb.m_max.y) * 0.5f,
		(aabb.m_min.z + aabb.m_max.z) * 0.5f,
	};

	float maxDistSq = 0.0f;
	uint8_t* vertex = (uint8_t*)_vertices;

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		float* position = (float*)vertex;
		vertex += _stride;

		const float xx = position[0] - center.x;
		const float yy = position[1] - center.y;
		const float zz = position[2] - center.z;
		const float distSq = xx*xx + yy*yy + zz*zz;
		maxDistSq = bx::max(distSq, maxDistSq);
	}

	_sphere.m_center = center;
	_sphere.m_radius = bx::sqrt(maxDistSq);
}

void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step)
{
	bx::RngMwc rng;

	uint8_t* vertex = (uint8_t*)_vertices;

	bx::Vec3 center;
	float* position = (float*)&vertex[0];
	center.x = position[0];
	center.y = position[1];
	center.z = position[2];

	position = (float*)&vertex[1*_stride];
	center.x += position[0];
	center.y += position[1];
	center.z += position[2];

	center.x *= 0.5f;
	center.y *= 0.5f;
	center.z *= 0.5f;

	float xx = position[0] - center.x;
	float yy = position[1] - center.y;
	float zz = position[2] - center.z;
	float maxDistSq = xx*xx + yy*yy + zz*zz;

	float radiusStep = _step * 0.37f;

	bool done;
	do
	{
		done = true;
		for (uint32_t ii = 0, index = rng.gen()%_numVertices; ii < _numVertices; ++ii, index = (index + 1)%_numVertices)
		{
			position = (float*)&vertex[index*_stride];

			xx = position[0] - center.x;
			yy = position[1] - center.y;
			zz = position[2] - center.z;
			float distSq = xx*xx + yy*yy + zz*zz;

			if (distSq > maxDistSq)
			{
				done = false;

				center.x += xx * radiusStep;
				center.y += yy * radiusStep;
				center.z += zz * radiusStep;
				maxDistSq = bx::lerp(maxDistSq, distSq, _step);

				break;
			}
		}

	} while (!done);

	_sphere.m_center = center;
	_sphere.m_radius = bx::sqrt(maxDistSq);
}

void calcPlaneUv(const Plane& _plane, bx::Vec3& _udir, bx::Vec3& _vdir)
{
	bx::calcTangentFrame(_udir, _vdir, _plane.m_normal);
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

	near.m_normal.x = xw - xz;
	near.m_normal.y = yw - yz;
	near.m_normal.z = zw - zz;
	near.m_dist     = ww - wz;

	far.m_normal.x = xw + xz;
	far.m_normal.y = yw + yz;
	far.m_normal.z = zw + zz;
	far.m_dist     = ww + wz;

	const float xx = _viewProj[ 0];
	const float yx = _viewProj[ 4];
	const float zx = _viewProj[ 8];
	const float wx = _viewProj[12];

	left.m_normal.x = xw - xx;
	left.m_normal.y = yw - yx;
	left.m_normal.z = zw - zx;
	left.m_dist     = ww - wx;

	right.m_normal.x = xw + xx;
	right.m_normal.y = yw + yx;
	right.m_normal.z = zw + zx;
	right.m_dist     = ww + wx;

	const float xy = _viewProj[ 1];
	const float yy = _viewProj[ 5];
	const float zy = _viewProj[ 9];
	const float wy = _viewProj[13];

	top.m_normal.x = xw + xy;
	top.m_normal.y = yw + yy;
	top.m_normal.z = zw + zy;
	top.m_dist     = ww + wy;

	bottom.m_normal.x = xw - xy;
	bottom.m_normal.y = yw - yy;
	bottom.m_normal.z = zw - zy;
	bottom.m_dist      = ww - wy;

	Plane* plane = _result;
	for (uint32_t ii = 0; ii < 6; ++ii)
	{
		const float len = bx::length(plane->m_normal);
		plane->m_normal = bx::normalize(plane->m_normal);
		float invLen = 1.0f / len;
		plane->m_dist *= invLen;
		++plane;
	}
}

bx::Vec3 intersectPlanes(const Plane& _pa, const Plane& _pb, const Plane& _pc)
{
	const bx::Vec3 axb  = bx::cross(_pa.m_normal, _pb.m_normal);
	const bx::Vec3 bxc  = bx::cross(_pb.m_normal, _pc.m_normal);
	const bx::Vec3 cxa  = bx::cross(_pc.m_normal, _pa.m_normal);
	const bx::Vec3 tmp0 = bx::mul(bxc, _pa.m_dist);
	const bx::Vec3 tmp1 = bx::mul(cxa, _pb.m_dist);
	const bx::Vec3 tmp2 = bx::mul(axb, _pc.m_dist);
	const bx::Vec3 tmp3 = bx::add(tmp0, tmp1);
	const bx::Vec3 tmp4 = bx::add(tmp3, tmp2);

	const float denom = bx::dot(_pa.m_normal, bxc);
	const bx::Vec3 result = bx::mul(tmp4, -1.0f/denom);

	return result;
}

Ray makeRay(float _x, float _y, const float* _invVp)
{
	Ray ray;

	const bx::Vec3 near = { _x, _y, 0.0f };
	ray.m_pos = bx::mulH(near, _invVp);

	const bx::Vec3 far = { _x, _y, 1.0f };
	bx::Vec3 tmp = bx::mulH(far, _invVp);

	const bx::Vec3 dir = bx::sub(tmp, ray.m_pos);
	ray.m_dir = bx::normalize(dir);

	return ray;
}

inline bx::Vec3 getPointAt(const Ray& _ray, float _t)
{
	return bx::add(bx::mul(_ray.m_dir, _t), _ray.m_pos);
}

bool intersect(const Ray& _ray, const Aabb& _aabb, Hit* _hit)
{
	const bx::Vec3 invDir = bx::rcp(_ray.m_dir);
	const bx::Vec3 tmp0   = bx::sub(_aabb.m_min, _ray.m_pos);
	const bx::Vec3 t0     = bx::mul(tmp0, invDir);
	const bx::Vec3 tmp1   = bx::sub(_aabb.m_max, _ray.m_pos);
	const bx::Vec3 t1     = bx::mul(tmp1, invDir);

	const bx::Vec3 min = bx::min(t0, t1);
	const bx::Vec3 max = bx::max(t0, t1);

	const float tmin = bx::max(min.x, min.y, min.z);
	const float tmax = bx::min(max.x, max.y, max.z);

	if (tmax < 0.0f
	||  tmin > tmax)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->m_normal.x = float( (t1.x == tmin) - (t0.x == tmin) );
		_hit->m_normal.y = float( (t1.y == tmin) - (t0.y == tmin) );
		_hit->m_normal.z = float( (t1.z == tmin) - (t0.z == tmin) );

		_hit->m_dist = tmin;
		_hit->m_pos  = getPointAt(_ray, tmin);
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
	obbRay.m_pos = bx::mul(_ray.m_pos, mtxInv);
	obbRay.m_dir = bx::mulXyz0(_ray.m_dir, mtxInv);

	if (intersect(obbRay, s_kUnitAabb, _hit) )
	{
		if (NULL != _hit)
		{
			_hit->m_pos = bx::mul(_hit->m_pos, _obb.m_mtx);

			const bx::Vec3 tmp = bx::mulXyz0(_hit->m_normal, _obb.m_mtx);
			_hit->m_normal = bx::normalize(tmp);
		}

		return true;
	}

	return false;
}

bool intersect(const Ray& _ray, const Disk& _disk, Hit* _hit)
{
	Plane plane;
	plane.m_normal = _disk.m_normal;
	plane.m_dist = -bx::dot(_disk.m_center, _disk.m_normal);

	Hit tmpHit;
	_hit = NULL != _hit ? _hit : &tmpHit;

	if (intersect(_ray, plane, _hit) )
	{
		const bx::Vec3 tmp = bx::sub(_disk.m_center, _hit->m_pos);
		return bx::dot(tmp, tmp) <= bx::square(_disk.m_radius);
	}

	return false;
}

static bool intersect(const Ray& _ray, const Cylinder& _cylinder, bool _capsule, Hit* _hit)
{
	bx::Vec3 axis = bx::sub(_cylinder.m_end, _cylinder.m_pos);
	const bx::Vec3 rc   = bx::sub(_ray.m_pos, _cylinder.m_pos);
	const bx::Vec3 dxa  = bx::cross(_ray.m_dir, axis);

	const float len = bx::length(dxa);
	const bx::Vec3 normal = bx::normalize(dxa);
	const float dist = bx::abs(bx::dot(rc, normal) );

	if (dist > _cylinder.m_radius)
	{
		return false;
	}

	bx::Vec3 vo = bx::cross(rc, axis);
	const float t0 = -bx::dot(vo, normal) / len;

	vo = bx::normalize(bx::cross(normal, axis) );

	const float rsq   = bx::square(_cylinder.m_radius);
	const float ddoto = bx::dot(_ray.m_dir, vo);
	const float ss    = t0 - bx::abs(bx::sqrt(rsq - bx::square(dist) ) / ddoto);

	if (0.0f > ss)
	{
		return false;
	}

	const bx::Vec3 point = getPointAt(_ray, ss);

	const float axisLen = bx::length(axis);
	axis = bx::normalize(axis);
	const float pdota  = bx::dot(_cylinder.m_pos, axis);
	const float height = bx::dot(point, axis) - pdota;

	if (height > 0.0f
	&&  height < axisLen)
	{
		if (NULL != _hit)
		{
			const float t1 = height / axisLen;
			const bx::Vec3 pointOnAxis = bx::lerp(_cylinder.m_pos, _cylinder.m_end, t1);

			_hit->m_pos = point;

			const bx::Vec3 tmp = bx::sub(point, pointOnAxis);
			_hit->m_normal = bx::normalize(tmp);

			_hit->m_dist = ss;
		}

		return true;
	}

	if (_capsule)
	{
		const float rdota = bx::dot(_ray.m_pos, axis);
		const float pp    = rdota - pdota;
		const float t1    = pp / axisLen;

		const bx::Vec3 pointOnAxis = bx::lerp(_cylinder.m_pos, _cylinder.m_end, t1);
		const bx::Vec3 axisToRay   = bx::sub(_ray.m_pos, pointOnAxis);

		if (_cylinder.m_radius < bx::length(axisToRay)
		&&  0.0f > ss)
		{
			return false;
		}

		Sphere sphere;
		sphere.m_radius = _cylinder.m_radius;

		sphere.m_center = 0.0f >= height
			? _cylinder.m_pos
			: _cylinder.m_end
			;

		return intersect(_ray, sphere, _hit);
	}

	Plane plane;
	bx::Vec3 pos;

	if (0.0f >= height)
	{
		plane.m_normal = bx::neg(axis);
		pos = _cylinder.m_pos;
	}
	else
	{
		plane.m_normal = axis;
		pos = _cylinder.m_end;
	}

	plane.m_dist = -bx::dot(pos, plane.m_normal);

	Hit tmpHit;
	_hit = NULL != _hit ? _hit : &tmpHit;

	if (intersect(_ray, plane, _hit) )
	{
		const bx::Vec3 tmp = bx::sub(pos, _hit->m_pos);
		return bx::dot(tmp, tmp) <= rsq;
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
	const bx::Vec3 axis = bx::sub(_cone.m_pos, _cone.m_end);

	const float len = bx::length(axis);
	const bx::Vec3 normal = bx::normalize(axis);

	Disk disk;
	disk.m_center = _cone.m_pos;
	disk.m_normal = normal;
	disk.m_radius = _cone.m_radius;

	Hit tmpInt;
	Hit* out = NULL != _hit ? _hit : &tmpInt;
	bool hit = intersect(_ray, disk, out);

	const bx::Vec3 ro = bx::sub(_ray.m_pos, _cone.m_end);

	const float hyp    = bx::sqrt(bx::square(_cone.m_radius) + bx::square(len) );
	const float cosaSq = bx::square(len/hyp);
	const float ndoto  = bx::dot(normal, ro);
	const float ndotd  = bx::dot(normal, _ray.m_dir);

	const float aa = bx::square(ndotd) - cosaSq;
	const float bb = 2.0f * (ndotd*ndoto - bx::dot(_ray.m_dir, ro)*cosaSq);
	const float cc = bx::square(ndoto) - bx::dot(ro, ro)*cosaSq;

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

	const bx::Vec3 hitPos = getPointAt(_ray, tt);
	const bx::Vec3 point  = bx::sub(hitPos, _cone.m_end);

	const float hh = bx::dot(normal, point);

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
			_hit->m_pos  = hitPos;

			const float scale = hh / bx::dot(point, point);
			const bx::Vec3 pointScaled = bx::mul(point, scale);

			const bx::Vec3 tmp = bx::sub(pointScaled, normal);
			_hit->m_normal = bx::normalize(tmp);
		}
	}

	return true;
}

bool intersect(const Ray& _ray, const Plane& _plane, Hit* _hit)
{
	float equation = bx::dot(_ray.m_pos, _plane.m_normal) + _plane.m_dist;
	if (0.0f > equation)
	{
		return false;
	}

	float ndotd = bx::dot(_ray.m_dir, _plane.m_normal);
	if (0.0f < ndotd)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->m_normal = _plane.m_normal;

		float tt = -equation/ndotd;
		_hit->m_dist = tt;
		_hit->m_pos  = getPointAt(_ray, tt);
	}

	return true;
}

bool intersect(const Ray& _ray, const Sphere& _sphere, Hit* _hit)
{
	const bx::Vec3 rs = bx::sub(_ray.m_pos, _sphere.m_center);

	const float bb = bx::dot(rs, _ray.m_dir);
	if (0.0f < bb)
	{
		return false;
	}

	const float aa = bx::dot(_ray.m_dir, _ray.m_dir);
	const float cc = bx::dot(rs, rs) - bx::square(_sphere.m_radius);

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

		const bx::Vec3 point = getPointAt(_ray, tt);
		_hit->m_pos = point;

		const bx::Vec3 tmp = bx::sub(point, _sphere.m_center);
		_hit->m_normal = bx::normalize(tmp);
	}

	return true;
}

bool intersect(const Ray& _ray, const Tris& _triangle, Hit* _hit)
{
	const bx::Vec3 edge10 = bx::sub(_triangle.m_v1, _triangle.m_v0);
	const bx::Vec3 edge02 = bx::sub(_triangle.m_v0, _triangle.m_v2);
	const bx::Vec3 normal = bx::cross(edge02, edge10);
	const bx::Vec3 vo     = bx::sub(_triangle.m_v0, _ray.m_pos);
	const bx::Vec3 dxo    = bx::cross(_ray.m_dir, vo);
	const float det = bx::dot(normal, _ray.m_dir);

	if (det > 0.0f)
	{
		return false;
	}

	const float invDet = 1.0f/det;
	const float bz = bx::dot(dxo, edge02) * invDet;
	const float by = bx::dot(dxo, edge10) * invDet;
	const float bx = 1.0f - by - bz;

	if (bx < 0.0f || by < 0.0f || bz < 0.0f)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->m_normal = bx::normalize(normal);

		const float tt = bx::dot(normal, vo) * invDet;
		_hit->m_dist = tt;
		_hit->m_pos  = getPointAt(_ray, tt);
	}

	return true;
}
