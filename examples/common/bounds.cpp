/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/rng.h>
#include <bx/math.h>
#include "bounds.h"

using namespace bx;

Vec3 getCenter(const Aabb& _aabb)
{
	return mul(add(_aabb.min, _aabb.max), 0.5f);
}

Vec3 getExtents(const Aabb& _aabb)
{
	return mul(sub(_aabb.max, _aabb.min), 0.5f);
}

Vec3 getCenter(const Triangle& _triangle)
{
	return mul(add(add(_triangle.v0, _triangle.v1), _triangle.v2), 1.0f/3.0f);
}

void toAabb(Aabb& _outAabb, const Vec3& _extents)
{
	_outAabb.min = neg(_extents);
	_outAabb.max =     _extents;
}

void toAabb(Aabb& _outAabb, const Vec3& _center, const Vec3& _extents)
{
	_outAabb.min = sub(_center, _extents);
	_outAabb.max = add(_center, _extents);
}

void toAabb(Aabb& _outAabb, const Cylinder& _cylinder)
{
	// Reference(s):
	// - https://web.archive.org/web/20181113055756/http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	//
	const Vec3 axis = sub(_cylinder.end, _cylinder.pos);
	const Vec3 asq  = mul(axis, axis);
	const Vec3 nsq  = mul(asq, 1.0f/dot(axis, axis) );
	const Vec3 tmp  = sub(Vec3(1.0f), nsq);

	const float inv = 1.0f/(tmp.x*tmp.y*tmp.z);

	const Vec3 extent =
	{
		_cylinder.radius * tmp.x * bx::sqrt( (nsq.x + nsq.y * nsq.z) * inv),
		_cylinder.radius * tmp.y * bx::sqrt( (nsq.y + nsq.z * nsq.x) * inv),
		_cylinder.radius * tmp.z * bx::sqrt( (nsq.z + nsq.x * nsq.y) * inv),
	};

	const Vec3 minP = sub(_cylinder.pos, extent);
	const Vec3 minE = sub(_cylinder.end, extent);
	const Vec3 maxP = add(_cylinder.pos, extent);
	const Vec3 maxE = add(_cylinder.end, extent);

	_outAabb.min = min(minP, minE);
	_outAabb.max = max(maxP, maxE);
}

void toAabb(Aabb& _outAabb, const Disk& _disk)
{
	// Reference(s):
	// - https://web.archive.org/web/20181113055756/http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	//
	const Vec3 nsq = mul(_disk.normal, _disk.normal);
	const Vec3 one = { 1.0f, 1.0f, 1.0f };
	const Vec3 tmp = sub(one, nsq);
	const float inv = 1.0f / (tmp.x*tmp.y*tmp.z);

	const Vec3 extent =
	{
		_disk.radius * tmp.x * bx::sqrt( (nsq.x + nsq.y * nsq.z) * inv),
		_disk.radius * tmp.y * bx::sqrt( (nsq.y + nsq.z * nsq.x) * inv),
		_disk.radius * tmp.z * bx::sqrt( (nsq.z + nsq.x * nsq.y) * inv),
	};

	_outAabb.min = sub(_disk.center, extent);
	_outAabb.max = add(_disk.center, extent);
}

void toAabb(Aabb& _outAabb, const Obb& _obb)
{
	Vec3 xyz = { 1.0f, 1.0f, 1.0f };
	Vec3 tmp = mul(xyz, _obb.mtx);

	_outAabb.min = tmp;
	_outAabb.max = tmp;

	for (uint32_t ii = 1; ii < 8; ++ii)
	{
		xyz.x = ii & 1 ? -1.0f : 1.0f;
		xyz.y = ii & 2 ? -1.0f : 1.0f;
		xyz.z = ii & 4 ? -1.0f : 1.0f;
		tmp = mul(xyz, _obb.mtx);

		_outAabb.min = min(_outAabb.min, tmp);
		_outAabb.max = max(_outAabb.max, tmp);
	}
}

void toAabb(Aabb& _outAabb, const Sphere& _sphere)
{
	const float radius = _sphere.radius;
	_outAabb.min = sub(_sphere.center, radius);
	_outAabb.max = add(_sphere.center, radius);
}

void toAabb(Aabb& _outAabb, const Triangle& _triangle)
{
	_outAabb.min = min(_triangle.v0, _triangle.v1, _triangle.v2);
	_outAabb.max = max(_triangle.v0, _triangle.v1, _triangle.v2);
}

void aabbTransformToObb(Obb& _obb, const Aabb& _aabb, const float* _mtx)
{
	toObb(_obb, _aabb);
	float result[16];
	mtxMul(result, _obb.mtx, _mtx);
	memCopy(_obb.mtx, result, sizeof(result) );
}

void toAabb(Aabb& _outAabb, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Vec3 mn(init::None);
	Vec3 mx(init::None);
	uint8_t* vertex = (uint8_t*)_vertices;

	mn = mx = load<Vec3>(vertex);
	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		const Vec3 pos = load<Vec3>(vertex);
		vertex += _stride;

		mn = min(pos, mn);
		mx = max(pos, mx);
	}

	_outAabb.min = mn;
	_outAabb.max = mx;
}

void toAabb(Aabb& _outAabb, const float* _mtx, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Vec3 mn(init::None);
	Vec3 mx(init::None);
	uint8_t* vertex = (uint8_t*)_vertices;
	mn = mx = mul(load<Vec3>(vertex), _mtx);

	vertex += _stride;

	for (uint32_t ii = 1; ii < _numVertices; ++ii)
	{
		Vec3 pos = mul(load<Vec3>(vertex), _mtx);
		vertex += _stride;

		mn = min(pos, mn);
		mx = max(pos, mx);
	}

	_outAabb.min = mn;
	_outAabb.max = mx;
}

float calcAreaAabb(const Aabb& _aabb)
{
	const float ww = _aabb.max.x - _aabb.min.x;
	const float hh = _aabb.max.y - _aabb.min.y;
	const float dd = _aabb.max.z - _aabb.min.z;
	return 2.0f * (ww*hh + ww*dd + hh*dd);
}

void aabbExpand(Aabb& _outAabb, float _factor)
{
	_outAabb.min.x -= _factor;
	_outAabb.min.y -= _factor;
	_outAabb.min.z -= _factor;
	_outAabb.max.x += _factor;
	_outAabb.max.y += _factor;
	_outAabb.max.z += _factor;
}

void aabbExpand(Aabb& _outAabb, const Vec3& _pos)
{
	_outAabb.min = min(_outAabb.min, _pos);
	_outAabb.max = max(_outAabb.max, _pos);
}

void toObb(Obb& _outObb, const Aabb& _aabb)
{
	memSet(_outObb.mtx, 0, sizeof(_outObb.mtx) );
	_outObb.mtx[ 0] = (_aabb.max.x - _aabb.min.x) * 0.5f;
	_outObb.mtx[ 5] = (_aabb.max.y - _aabb.min.y) * 0.5f;
	_outObb.mtx[10] = (_aabb.max.z - _aabb.min.z) * 0.5f;
	_outObb.mtx[12] = (_aabb.min.x + _aabb.max.x) * 0.5f;
	_outObb.mtx[13] = (_aabb.min.y + _aabb.max.y) * 0.5f;
	_outObb.mtx[14] = (_aabb.min.z + _aabb.max.z) * 0.5f;
	_outObb.mtx[15] = 1.0f;
}

void calcObb(Obb& _outObb, const void* _vertices, uint32_t _numVertices, uint32_t _stride, uint32_t _steps)
{
	Aabb aabb;
	toAabb(aabb, _vertices, _numVertices, _stride);
	float minArea = calcAreaAabb(aabb);

	Obb best;
	toObb(best, aabb);

	float angleStep = float(kPiHalf/_steps);
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

	memCopy(&_outObb, &best, sizeof(Obb) );
}

void calcMaxBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride)
{
	Aabb aabb;
	toAabb(aabb, _vertices, _numVertices, _stride);

	Vec3 center = getCenter(aabb);

	float maxDistSq = 0.0f;
	uint8_t* vertex = (uint8_t*)_vertices;

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		const Vec3& pos = load<Vec3>(vertex);
		vertex += _stride;

		const Vec3 tmp = sub(pos, center);
		const float distSq = dot(tmp, tmp);
		maxDistSq = max(distSq, maxDistSq);
	}

	_sphere.center = center;
	_sphere.radius = bx::sqrt(maxDistSq);
}

void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step)
{
	RngMwc rng;

	uint8_t* vertex = (uint8_t*)_vertices;

	Vec3 center(init::None);
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
				maxDistSq = lerp(maxDistSq, distSq, _step);

				break;
			}
		}

	} while (!done);

	_sphere.center = center;
	_sphere.radius = bx::sqrt(maxDistSq);
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

	near.normal.x = xw - xz;
	near.normal.y = yw - yz;
	near.normal.z = zw - zz;
	near.dist     = ww - wz;

	far.normal.x = xw + xz;
	far.normal.y = yw + yz;
	far.normal.z = zw + zz;
	far.dist     = ww + wz;

	const float xx = _viewProj[ 0];
	const float yx = _viewProj[ 4];
	const float zx = _viewProj[ 8];
	const float wx = _viewProj[12];

	left.normal.x = xw - xx;
	left.normal.y = yw - yx;
	left.normal.z = zw - zx;
	left.dist     = ww - wx;

	right.normal.x = xw + xx;
	right.normal.y = yw + yx;
	right.normal.z = zw + zx;
	right.dist     = ww + wx;

	const float xy = _viewProj[ 1];
	const float yy = _viewProj[ 5];
	const float zy = _viewProj[ 9];
	const float wy = _viewProj[13];

	top.normal.x = xw + xy;
	top.normal.y = yw + yy;
	top.normal.z = zw + zy;
	top.dist     = ww + wy;

	bottom.normal.x = xw - xy;
	bottom.normal.y = yw - yy;
	bottom.normal.z = zw - zy;
	bottom.dist     = ww - wy;

	Plane* plane = _result;
	for (uint32_t ii = 0; ii < 6; ++ii)
	{
		const float invLen = 1.0f/length(plane->normal);
		plane->normal = normalize(plane->normal);
		plane->dist  *= invLen;
		++plane;
	}
}

Ray makeRay(float _x, float _y, const float* _invVp)
{
	Ray ray;

	const Vec3 near = { _x, _y, 0.0f };
	ray.pos = mulH(near, _invVp);

	const Vec3 far = { _x, _y, 1.0f };
	Vec3 tmp = mulH(far, _invVp);

	const Vec3 dir = sub(tmp, ray.pos);
	ray.dir = normalize(dir);

	return ray;
}

inline Vec3 getPointAt(const Ray& _ray, float _t)
{
	return mad(_ray.dir, _t, _ray.pos);
}

bool intersect(const Ray& _ray, const Aabb& _aabb, Hit* _hit)
{
	const Vec3 invDir = rcp(_ray.dir);
	const Vec3 tmp0   = sub(_aabb.min, _ray.pos);
	const Vec3 t0     = mul(tmp0, invDir);
	const Vec3 tmp1   = sub(_aabb.max, _ray.pos);
	const Vec3 t1     = mul(tmp1, invDir);

	const Vec3 mn = min(t0, t1);
	const Vec3 mx = max(t0, t1);

	const float tmin = max(mn.x, mn.y, mn.z);
	const float tmax = min(mx.x, mx.y, mx.z);

	if (0.0f > tmax
	||  tmin > tmax)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->plane.normal.x = float( (t1.x == tmin) - (t0.x == tmin) );
		_hit->plane.normal.y = float( (t1.y == tmin) - (t0.y == tmin) );
		_hit->plane.normal.z = float( (t1.z == tmin) - (t0.z == tmin) );

		_hit->plane.dist = tmin;
		_hit->pos        = getPointAt(_ray, tmin);
	}

	return true;
}

static constexpr Aabb kUnitAabb =
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
	mtxInverse(mtxInv, _obb.mtx);

	Ray obbRay;
	obbRay.pos = mul(_ray.pos, mtxInv);
	obbRay.dir = mulXyz0(_ray.dir, mtxInv);

	if (intersect(obbRay, kUnitAabb, _hit) )
	{
		if (NULL != _hit)
		{
			_hit->pos = mul(_hit->pos, _obb.mtx);

			const Vec3 tmp = mulXyz0(_hit->plane.normal, _obb.mtx);
			_hit->plane.normal = normalize(tmp);
		}

		return true;
	}

	return false;
}

bool intersect(const Ray& _ray, const Disk& _disk, Hit* _hit)
{
	Plane plane(_disk.normal, -dot(_disk.center, _disk.normal) );

	Hit tmpHit;
	_hit = NULL != _hit ? _hit : &tmpHit;

	if (intersect(_ray, plane, _hit) )
	{
		const Vec3 tmp = sub(_disk.center, _hit->pos);
		return dot(tmp, tmp) <= square(_disk.radius);
	}

	return false;
}

static bool intersect(const Ray& _ray, const Cylinder& _cylinder, bool _capsule, Hit* _hit)
{
	Vec3 axis = sub(_cylinder.end, _cylinder.pos);
	const Vec3 rc   = sub(_ray.pos, _cylinder.pos);
	const Vec3 dxa  = cross(_ray.dir, axis);

	const float len    = length(dxa);
	const Vec3  normal = normalize(dxa);
	const float dist   = bx::abs(dot(rc, normal) );

	if (dist > _cylinder.radius)
	{
		return false;
	}

	Vec3 vo = cross(rc, axis);
	const float t0 = -dot(vo, normal) / len;

	vo = normalize(cross(normal, axis) );

	const float rsq   = square(_cylinder.radius);
	const float ddoto = dot(_ray.dir, vo);
	const float ss    = t0 - bx::abs(bx::sqrt(rsq - square(dist) ) / ddoto);

	if (0.0f > ss)
	{
		return false;
	}

	const Vec3 point = getPointAt(_ray, ss);

	const float axisLen = length(axis);
	axis = normalize(axis);
	const float pdota  = dot(_cylinder.pos, axis);
	const float height = dot(point, axis) - pdota;

	if (0.0f    < height
	&&  axisLen > height)
	{
		if (NULL != _hit)
		{
			const float t1 = height / axisLen;
			const Vec3 pointOnAxis = lerp(_cylinder.pos, _cylinder.end, t1);

			_hit->pos = point;

			const Vec3 tmp = sub(point, pointOnAxis);
			_hit->plane.normal = normalize(tmp);

			_hit->plane.dist = ss;
		}

		return true;
	}

	if (_capsule)
	{
		const float rdota = dot(_ray.pos, axis);
		const float pp    = rdota - pdota;
		const float t1    = pp / axisLen;

		const Vec3 pointOnAxis = lerp(_cylinder.pos, _cylinder.end, t1);
		const Vec3 axisToRay   = sub(_ray.pos, pointOnAxis);

		if (_cylinder.radius < length(axisToRay)
		&&  0.0f > ss)
		{
			return false;
		}

		Sphere sphere;
		sphere.radius = _cylinder.radius;

		sphere.center = 0.0f >= height
			? _cylinder.pos
			: _cylinder.end
			;

		return intersect(_ray, sphere, _hit);
	}

	Plane plane(init::None);
	Vec3 pos(init::None);

	if (0.0f >= height)
	{
		plane.normal = neg(axis);
		pos = _cylinder.pos;
	}
	else
	{
		plane.normal = axis;
		pos = _cylinder.end;
	}

	plane.dist = -dot(pos, plane.normal);

	Hit tmpHit;
	_hit = NULL != _hit ? _hit : &tmpHit;

	if (intersect(_ray, plane, _hit) )
	{
		const Vec3 tmp = sub(pos, _hit->pos);
		return dot(tmp, tmp) <= rsq;
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
	const Vec3 axis = sub(_cone.pos, _cone.end);

	const float len = length(axis);
	const Vec3 normal = normalize(axis);

	Disk disk;
	disk.center = _cone.pos;
	disk.normal = normal;
	disk.radius = _cone.radius;

	Hit tmpInt;
	Hit* out = NULL != _hit ? _hit : &tmpInt;
	bool hit = intersect(_ray, disk, out);

	const Vec3 ro = sub(_ray.pos, _cone.end);

	const float hyp    = bx::sqrt(square(_cone.radius) + square(len) );
	const float cosaSq = square(len/hyp);
	const float ndoto  = dot(normal, ro);
	const float ndotd  = dot(normal, _ray.dir);

	const float aa = square(ndotd) - cosaSq;
	const float bb = 2.0f * (ndotd*ndoto - dot(_ray.dir, ro)*cosaSq);
	const float cc = square(ndoto) - dot(ro, ro)*cosaSq;

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

	const Vec3 hitPos = getPointAt(_ray, tt);
	const Vec3 point  = sub(hitPos, _cone.end);

	const float hh = dot(normal, point);

	if (0.0f > hh
	||  len  < hh)
	{
		return hit;
	}

	if (NULL != _hit)
	{
		if (!hit
		||  tt < _hit->plane.dist)
		{
			_hit->plane.dist = tt;
			_hit->pos  = hitPos;

			const float scale = hh / dot(point, point);
			const Vec3 pointScaled = mul(point, scale);

			const Vec3 tmp = sub(pointScaled, normal);
			_hit->plane.normal = normalize(tmp);
		}
	}

	return true;
}

bool intersect(const Ray& _ray, const Plane& _plane, Hit* _hit)
{
	const float dist = distance(_plane, _ray.pos);
	if (0.0f > dist)
	{
		return false;
	}

	const float ndotd = dot(_ray.dir, _plane.normal);
	if (0.0f < ndotd)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->plane.normal = _plane.normal;

		float tt = -dist/ndotd;
		_hit->plane.dist = tt;
		_hit->pos = getPointAt(_ray, tt);
	}

	return true;
}

bool intersect(const Ray& _ray, const Sphere& _sphere, Hit* _hit)
{
	const Vec3 rs = sub(_ray.pos, _sphere.center);

	const float bb = dot(rs, _ray.dir);
	if (0.0f < bb)
	{
		return false;
	}

	const float aa = dot(_ray.dir, _ray.dir);
	const float cc = dot(rs, rs) - square(_sphere.radius);

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
		_hit->plane.dist = tt;

		const Vec3 point = getPointAt(_ray, tt);
		_hit->pos = point;

		const Vec3 tmp = sub(point, _sphere.center);
		_hit->plane.normal = normalize(tmp);
	}

	return true;
}

bool intersect(const Ray& _ray, const Triangle& _triangle, Hit* _hit)
{
	const Vec3 edge10 = sub(_triangle.v1, _triangle.v0);
	const Vec3 edge02 = sub(_triangle.v0, _triangle.v2);
	const Vec3 normal = cross(edge02, edge10);
	const Vec3 vo     = sub(_triangle.v0, _ray.pos);
	const Vec3 dxo    = cross(_ray.dir, vo);
	const float det = dot(normal, _ray.dir);

	if (0.0f < det)
	{
		return false;
	}

	const float invDet = 1.0f/det;
	const float bz = dot(dxo, edge02) * invDet;
	const float by = dot(dxo, edge10) * invDet;
	const float bx = 1.0f - by - bz;

	if (0.0f > bx
	||  0.0f > by
	||  0.0f > bz)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->plane.normal = normalize(normal);

		const float tt = dot(normal, vo) * invDet;
		_hit->plane.dist = tt;
		_hit->pos  = getPointAt(_ray, tt);
	}

	return true;
}

Vec3 barycentric(const Triangle& _triangle, const Vec3& _pos)
{
	const Vec3 v0 = sub(_triangle.v1, _triangle.v0);
	const Vec3 v1 = sub(_triangle.v2, _triangle.v0);
	const Vec3 v2 = sub(_pos, _triangle.v0);

	const float dot00 = dot(v0, v0);
	const float dot01 = dot(v0, v1);
	const float dot02 = dot(v0, v2);
	const float dot11 = dot(v1, v1);
	const float dot12 = dot(v1, v2);

	const float invDenom = 1.0f/(dot00*dot11 - square(dot01) );

	const float vv = (dot11*dot02 - dot01*dot12)*invDenom;
	const float ww = (dot00*dot12 - dot01*dot02)*invDenom;
	const float uu = 1.0f - vv - ww;

	return { uu, vv, ww };
}

Vec3 cartesian(const Triangle& _triangle, const Vec3& _uvw)
{
	const Vec3 b0 = mul(_triangle.v0, _uvw.x);
	const Vec3 b1 = mul(_triangle.v1, _uvw.y);
	const Vec3 b2 = mul(_triangle.v2, _uvw.z);

	return add(add(b0, b1), b2);
}

void calcPlane(Plane& _outPlane, const Disk& _disk)
{
	calcPlane(_outPlane, _disk.normal, _disk.center);
}

void calcPlane(Plane& _outPlane, const Triangle& _triangle)
{
	calcPlane(_outPlane, _triangle.v0, _triangle.v1, _triangle.v2);
}

struct Interval
{
	Interval(float _val)
		: start(_val)
		, end(_val)
	{
	}

	Interval(float _start, float _end)
		: start(_start)
		, end(_end)
	{
	}

	void set(float _val)
	{
		start = _val;
		end   = _val;
	}

	void expand(float _val)
	{
		start = min(_val, start);
		end   = max(_val, end);
	}

	float start;
	float end;
};

bool overlap(const Interval& _a, const Interval& _b)
{
	return _a.end > _b.start
		&& _b.end > _a.start
		;
}

float projectToAxis(const Vec3& _axis, const Vec3& _point)
{
	return dot(_axis, _point);
}

Interval projectToAxis(const Vec3& _axis, const Vec3* _points, uint32_t _num)
{
	Interval interval(projectToAxis(_axis, _points[0]) );

	for (uint32_t ii = 1; ii < _num; ++ii)
	{
		interval.expand(projectToAxis(_axis, _points[ii]) );
	}

	return interval;
}

Interval projectToAxis(const Vec3& _axis, const Aabb& _aabb)
{
	const float extent = bx::abs(projectToAxis(abs(_axis), getExtents(_aabb) ) );
	const float center =         projectToAxis(    _axis , getCenter (_aabb) );
	return
	{
		center - extent,
		center + extent,
	};
}

Interval projectToAxis(const Vec3& _axis, const Triangle& _triangle)
{
	const float a0 = projectToAxis(_axis, _triangle.v0);
	const float a1 = projectToAxis(_axis, _triangle.v1);
	const float a2 = projectToAxis(_axis, _triangle.v2);
	return
	{
		min(a0, a1, a2),
		max(a0, a1, a2),
	};
}

struct Srt
{
	Quaternion rotation    = init::Identity;
	Vec3       translation = init::Zero;
	Vec3       scale       = init::Zero;
};

Srt toSrt(const Aabb& _aabb)
{
	return { init::Identity, getCenter(_aabb), getExtents(_aabb) };
}

Srt toSrt(const void* _mtx)
{
	Srt result;

	const float* mtx = (const float*)_mtx;

	result.translation = { mtx[12], mtx[13], mtx[14] };

	float xx = mtx[ 0];
	float xy = mtx[ 1];
	float xz = mtx[ 2];
	float yx = mtx[ 4];
	float yy = mtx[ 5];
	float yz = mtx[ 6];
	float zx = mtx[ 8];
	float zy = mtx[ 9];
	float zz = mtx[10];

	result.scale =
	{
		bx::sqrt(xx*xx + xy*xy + xz*xz),
		bx::sqrt(yx*yx + yy*yy + yz*yz),
		bx::sqrt(zx*zx + zy*zy + zz*zz),
	};

	const Vec3 invScale = rcp(result.scale);

	xx *= invScale.x;
	xy *= invScale.x;
	xz *= invScale.x;
	yx *= invScale.y;
	yy *= invScale.y;
	yz *= invScale.y;
	zx *= invScale.z;
	zy *= invScale.z;
	zz *= invScale.z;

	const float trace = xx + yy + zz;

	if (0.0f < trace)
	{
		const float invS = 0.5f * rsqrt(trace + 1.0f);
		result.rotation =
		{
			(yz - zy) * invS,
			(zx - xz) * invS,
			(xy - yx) * invS,
			0.25f     / invS,
		};
	}
	else
	{
		if (xx > yy
		&&  xx > zz)
		{
			const float invS = 0.5f * bx::sqrt(max(1.0f + xx - yy - zz, 1e-8f) );
			result.rotation =
			{
				0.25f     / invS,
				(xy + yx) * invS,
				(xz + zx) * invS,
				(yz - zy) * invS,
			};
		}
		else if (yy > zz)
		{
			const float invS = 0.5f * bx::sqrt(max(1.0f + yy - xx - zz, 1e-8f) );
			result.rotation =
			{
				(xy + yx) * invS,
				0.25f     / invS,
				(yz + zy) * invS,
				(zx - xz) * invS,
			};
		}
		else
		{
			const float invS = 0.5f * bx::sqrt(max(1.0f + zz - xx - yy, 1e-8f) );
			result.rotation =
			{
				(xz + zx) * invS,
				(yz + zy) * invS,
				0.25f     / invS,
				(xy - yx) * invS,
			};
		}
	}

	return result;
}

void mtxFromSrt(float* _outMtx, const Srt& _srt)
{
	mtxQuat(_outMtx, _srt.rotation);

	store<Vec3>(&_outMtx[0], mul(load<Vec3>(&_outMtx[0]), _srt.scale.x) );
	store<Vec3>(&_outMtx[4], mul(load<Vec3>(&_outMtx[4]), _srt.scale.y) );
	store<Vec3>(&_outMtx[8], mul(load<Vec3>(&_outMtx[8]), _srt.scale.z) );

	store<Vec3>(&_outMtx[12], _srt.translation);
}

bool isNearZero(float _v)
{
	return equal(_v, 0.0f, 0.00001f);
}

bool isNearZero(const Vec3& _v)
{
	return isNearZero(dot(_v, _v) );
}

struct Line
{
	Vec3 pos = init::None;
	Vec3 dir = init::None;
};

inline Vec3 getPointAt(const Line& _line, float _t)
{
	return mad(_line.dir, _t, _line.pos);
}

bool intersect(Line& _outLine, const Plane& _planeA, const Plane& _planeB)
{
	const Vec3  axb   = cross(_planeA.normal, _planeB.normal);
	const float denom = dot(axb, axb);

	if (isNearZero(denom) )
	{
		return false;
	}

	const Vec3 bxaxb = cross(_planeB.normal, axb);
	const Vec3 axbxa = cross(axb, _planeA.normal);
	const Vec3 tmp0  = mul(bxaxb, _planeA.dist);
	const Vec3 tmp1  = mul(axbxa, _planeB.dist);
	const Vec3 tmp2  = add(tmp0, tmp1);

	_outLine.pos = mul(tmp2, -1.0f/denom);
	_outLine.dir = normalize(axb);

	return true;
}

Vec3 intersectPlanes(const Plane& _pa, const Plane& _pb, const Plane& _pc)
{
	const Vec3 axb  = cross(_pa.normal, _pb.normal);
	const Vec3 bxc  = cross(_pb.normal, _pc.normal);
	const Vec3 cxa  = cross(_pc.normal, _pa.normal);
	const Vec3 tmp0 = mul(bxc, _pa.dist);
	const Vec3 tmp1 = mul(cxa, _pb.dist);
	const Vec3 tmp2 = mul(axb, _pc.dist);
	const Vec3 tmp3 = add(tmp0, tmp1);
	const Vec3 tmp4 = add(tmp3, tmp2);

	const float denom = dot(_pa.normal, bxc);
	const Vec3 result = mul(tmp4, -1.0f/denom);

	return result;
}

struct LineSegment
{
	Vec3 pos;
	Vec3 end;
};

inline Vec3 getPointAt(const LineSegment& _line, float _t)
{
	return lerp(_line.pos, _line.end, _t);
}

bool intersect(float& _outTa, float& _outTb, const LineSegment& _a, const LineSegment& _b)
{
	// Reference(s):
	//
	// - The shortest line between two lines in 3D
	//   https://web.archive.org/web/20120309093234/http://paulbourke.net/geometry/lineline3d/

	const Vec3 bd = sub(_b.end, _b.pos);
	if (isNearZero(bd) )
	{
		return false;
	}

	const Vec3 ad = sub(_a.end, _a.pos);
	if (isNearZero(ad) )
	{
		return false;
	}

	const Vec3  ab = sub(_a.pos, _b.pos);

	const float d0 = projectToAxis(ab, bd);
	const float d1 = projectToAxis(ad, bd);
	const float d2 = projectToAxis(ab, ad);
	const float d3 = projectToAxis(bd, bd);
	const float d4 = projectToAxis(ad, ad);

	const float denom = d4*d3 - square(d1);

	float ta = 0.0f;

	if (!isNearZero(denom) )
	{
		ta = (d0*d1 - d2*d3)/denom;
	}

	_outTa = ta;
	_outTb = (d0+d1*ta)/d3;

	return true;
}

bool intersect(const LineSegment& _a, const LineSegment& _b)
{
	float ta, tb;
	if (!intersect(ta, tb, _a, _b) )
	{
		return false;
	}

	return 0.0f >= ta
		&& 1.0f <= ta
		&& 0.0f >= tb
		&& 1.0f <= tb
		;
}

bool intersect(const LineSegment& _line, const Plane& _plane, Hit* _hit)
{
	const float dist  = distance(_plane, _line.pos);
	const float flip  = sign(dist);
	const Vec3  dir   = normalize(sub(_line.end, _line.pos) );
	const float ndotd = dot(dir, _plane.normal);
	const float tt    = -dist/ndotd;
	const float len   = length(sub(_line.end, _line.pos) );

	if (tt < 0.0f || tt > len)
	{
		return false;
	}

	if (NULL != _hit)
	{
		_hit->pos = mad(dir, tt, _line.pos);

		_hit->plane.normal =  mul(_plane.normal, flip);
		_hit->plane.dist   = -dot(_hit->plane.normal, _hit->pos);
	}

	return true;
}

float distance(const Plane& _plane, const LineSegment& _line)
{
	const float pd = distance(_plane, _line.pos);
	const float ed = distance(_plane, _line.end);
	return min(max(pd*ed, 0.0f), bx::abs(pd), bx::abs(ed) );
}

Vec3 closestPoint(const Line& _line, const Vec3& _point)
{
	const float tt = projectToAxis(_line.dir, sub(_point, _line.pos) );
	return getPointAt(_line, tt);
}

Vec3 closestPoint(const LineSegment& _line, const Vec3& _point, float& _outT)
{
	const Vec3  axis     = sub(_line.end, _line.pos);
	const float lengthSq = dot(axis, axis);
	const float tt       = clamp(projectToAxis(axis, sub(_point, _line.pos) ) / lengthSq, 0.0f, 1.0f);
	_outT = tt;
	return mad(axis, tt, _line.pos);
}

Vec3 closestPoint(const LineSegment& _line, const Vec3& _point)
{
	float ignored;
	return closestPoint(_line, _point, ignored);
}

Vec3 closestPoint(const Plane& _plane, const Vec3& _point)
{
	const float dist = distance(_plane, _point);
	return sub(_point, mul(_plane.normal, dist) );
}

Vec3 closestPoint(const Aabb& _aabb, const Vec3& _point)
{
	return clamp(_point, _aabb.min, _aabb.max);
}

Vec3 closestPoint(const Obb& _obb, const Vec3& _point)
{
	const Srt srt = toSrt(_obb.mtx);

	Aabb aabb;
	toAabb(aabb, srt.scale);

	const Quaternion invRotation = invert(srt.rotation);
	const Vec3 obbSpacePos = mul(sub(_point, srt.translation), srt.rotation);
	const Vec3 pos = closestPoint(aabb, obbSpacePos);

	return add(mul(pos, invRotation), srt.translation);
}

Vec3 closestPoint(const Triangle& _triangle, const Vec3& _point)
{
	Plane plane(init::None);
	calcPlane(plane, _triangle);

	const Vec3 pos = closestPoint(plane, _point);
	const Vec3 uvw = barycentric(_triangle, pos);

	return cartesian(_triangle, clamp<Vec3>(uvw, Vec3(0.0f), Vec3(1.0f) ) );
}

bool overlap(const Aabb& _aabb, const Vec3& _pos)
{
	const Vec3 ac  = getCenter(_aabb);
	const Vec3 ae  = getExtents(_aabb);
	const Vec3 abc = bx::abs(sub(ac, _pos) );

	return abc.x <= ae.x
		&& abc.y <= ae.y
		&& abc.z <= ae.z
		;
}

bool overlap(const Aabb& _aabbA, const Aabb& _aabbB)
{
	return true
		&& overlap(Interval{_aabbA.min.x, _aabbA.max.x}, Interval{_aabbB.min.x, _aabbB.max.x})
		&& overlap(Interval{_aabbA.min.y, _aabbA.max.y}, Interval{_aabbB.min.y, _aabbB.max.y})
		&& overlap(Interval{_aabbA.min.z, _aabbA.max.z}, Interval{_aabbB.min.z, _aabbB.max.z})
		;
}

bool overlap(const Aabb& _aabb, const Plane& _plane)
{
	const Vec3 center = getCenter(_aabb);
	const float dist  = distance(_plane, center);

	const Vec3 extents = getExtents(_aabb);
	const Vec3 normal  = bx::abs(_plane.normal);
	const float radius = dot(extents, normal);

	return bx::abs(dist) <= radius;
}

static constexpr Vec3 kAxis[] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
};

bool overlap(const Aabb& _aabb, const Triangle& _triangle)
{
	Aabb triAabb;
	toAabb(triAabb, _triangle);

	if (!overlap(_aabb, triAabb) )
	{
		return false;
	}

	Plane plane(init::None);
	calcPlane(plane, _triangle);

	if (!overlap(_aabb, plane) )
	{
		return false;
	}

	const Vec3 center = getCenter(_aabb);
	const Vec3 v0 = sub(_triangle.v0, center);
	const Vec3 v1 = sub(_triangle.v1, center);
	const Vec3 v2 = sub(_triangle.v2, center);

	const Vec3 edge[] =
	{
		sub(v1, v0),
		sub(v2, v1),
		sub(v0, v2),
	};

	for (uint32_t ii = 0; ii < 3; ++ii)
	{
		for (uint32_t jj = 0; jj < 3; ++jj)
		{
			const Vec3 axis = cross(kAxis[ii], edge[jj]);

			const Interval aabbR = projectToAxis(axis, _aabb);
			const Interval triR  = projectToAxis(axis, _triangle);

			if (!overlap(aabbR, triR) )
			{
				return false;
			}
		}
	}

	return true;
}

bool overlap(const Aabb& _aabb, const Capsule& _capsule)
{
	const Vec3 pos = closestPoint(LineSegment{_capsule.pos, _capsule.end}, getCenter(_aabb) );
	return overlap(_aabb, Sphere{pos, _capsule.radius});
}

bool overlap(const Aabb& _aabb, const Cone& _cone)
{
	float tt;
	const Vec3 pos = closestPoint(LineSegment{_cone.pos, _cone.end}, getCenter(_aabb), tt);
	return overlap(_aabb, Sphere{pos, lerp(_cone.radius, 0.0f, tt)});
}

bool overlap(const Aabb& _aabb, const Disk& _disk)
{
	if (!overlap(_aabb, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_aabb, plane);
}

static void calcObbVertices(
	  bx::Vec3* _outVertices
	, const bx::Vec3& _axisX
	, const bx::Vec3& _axisY
	, const bx::Vec3& _axisZ
	, const bx::Vec3& _pos
	, const bx::Vec3& _scale
	)
{
	const Vec3 ax = mul(_axisX, _scale.x);
	const Vec3 ay = mul(_axisY, _scale.y);
	const Vec3 az = mul(_axisZ, _scale.z);

	const Vec3 ppx = add(_pos, ax);
	const Vec3 pmx = sub(_pos, ax);
	const Vec3 ypz = add(ay, az);
	const Vec3 ymz = sub(ay, az);

	_outVertices[0] = sub(pmx, ymz);
	_outVertices[1] = sub(ppx, ymz);
	_outVertices[2] = add(ppx, ymz);
	_outVertices[3] = add(pmx, ymz);
	_outVertices[4] = sub(pmx, ypz);
	_outVertices[5] = sub(ppx, ypz);
	_outVertices[6] = add(ppx, ypz);
	_outVertices[7] = add(pmx, ypz);
}

static bool overlaps(const Vec3& _axis, const Vec3* _vertsA, const Vec3* _vertsB)
{
	Interval ia = projectToAxis(_axis, _vertsA, 8);
	Interval ib = projectToAxis(_axis, _vertsB, 8);

	return overlap(ia, ib);
}

static bool overlap(const Srt& _srtA, const Srt& _srtB)
{
	const Vec3 ax = toXAxis(_srtA.rotation);
	const Vec3 ay = toYAxis(_srtA.rotation);
	const Vec3 az = toZAxis(_srtA.rotation);

	const Vec3 bx = toXAxis(_srtB.rotation);
	const Vec3 by = toYAxis(_srtB.rotation);
	const Vec3 bz = toZAxis(_srtB.rotation);

	Vec3 vertsA[8] = { init::None, init::None, init::None, init::None, init::None, init::None, init::None, init::None };
	calcObbVertices(vertsA, ax, ay, az, init::Zero, _srtA.scale);

	Vec3 vertsB[8] = { init::None, init::None, init::None, init::None, init::None, init::None, init::None, init::None };
	calcObbVertices(vertsB, bx, by, bz, sub(_srtB.translation, _srtA.translation), _srtB.scale);

	return overlaps(ax,            vertsA, vertsB)
		&& overlaps(ay,            vertsA, vertsB)
		&& overlaps(az,            vertsA, vertsB)
		&& overlaps(bx,            vertsA, vertsB)
		&& overlaps(by,            vertsA, vertsB)
		&& overlaps(bz,            vertsA, vertsB)
		&& overlaps(cross(ax, bx), vertsA, vertsB)
		&& overlaps(cross(ax, by), vertsA, vertsB)
		&& overlaps(cross(ax, bz), vertsA, vertsB)
		&& overlaps(cross(ay, bx), vertsA, vertsB)
		&& overlaps(cross(ay, by), vertsA, vertsB)
		&& overlaps(cross(ay, bz), vertsA, vertsB)
		&& overlaps(cross(az, bx), vertsA, vertsB)
		&& overlaps(cross(az, by), vertsA, vertsB)
		&& overlaps(cross(az, bz), vertsA, vertsB)
		;
}

bool overlap(const Aabb& _aabb, const Obb& _obb)
{
	const Srt srtA = toSrt(_aabb);
	const Srt srtB = toSrt(_obb.mtx);

	return overlap(srtA, srtB);
}

bool overlap(const Capsule& _capsule, const Vec3& _pos)
{
	const Vec3 pos = closestPoint(LineSegment{_capsule.pos, _capsule.end}, _pos);
	return overlap(Sphere{pos, _capsule.radius}, _pos);
}

bool overlap(const Capsule& _capsule, const Plane& _plane)
{
	return distance(_plane, LineSegment{_capsule.pos, _capsule.end}) <= _capsule.radius;
}

bool overlap(const Capsule& _capsuleA, const Capsule& _capsuleB)
{
	float ta, tb;
	if (!intersect(ta, tb, {_capsuleA.pos, _capsuleA.end}, {_capsuleB.pos, _capsuleB.end}) )
	{
		return false;
	}

	if (0.0f <= ta
	&&  1.0f >= ta
	&&  0.0f <= tb
	&&  1.0f >= tb)
	{
		const Vec3 ad = sub(_capsuleA.end, _capsuleA.pos);
		const Vec3 bd = sub(_capsuleB.end, _capsuleB.pos);

		return overlap(
			  Sphere{mad(ad, ta, _capsuleA.pos), _capsuleA.radius}
			, Sphere{mad(bd, tb, _capsuleB.pos), _capsuleB.radius}
			);
	}

	if (0.0f <= ta
	&&  1.0f >= ta)
	{
		return overlap(_capsuleA, Sphere{0.0f >= tb ? _capsuleB.pos : _capsuleB.end, _capsuleB.radius});
	}

	if (0.0f <= tb
	&&  1.0f >= tb)
	{
		return overlap(_capsuleB, Sphere{0.0f >= ta ? _capsuleA.pos : _capsuleA.end, _capsuleA.radius});
	}

	const Vec3 pa = 0.0f > ta ? _capsuleA.pos : _capsuleA.end;
	const Vec3 pb = 0.0f > tb ? _capsuleB.pos : _capsuleB.end;
	const Vec3 closestA = closestPoint(LineSegment{_capsuleA.pos, _capsuleA.end}, pb);
	const Vec3 closestB = closestPoint(LineSegment{_capsuleB.pos, _capsuleB.end}, pa);

	if (dot(closestA, pb) <= dot(closestB, pa) )
	{
		return overlap(_capsuleA, Sphere{closestB, _capsuleB.radius});
	}

	return overlap(_capsuleB, Sphere{closestA, _capsuleA.radius});
}

bool overlap(const Cone& _cone, const Vec3& _pos)
{
	float tt;
	const Vec3 pos = closestPoint(LineSegment{_cone.pos, _cone.end}, _pos, tt);
	return overlap(Disk{pos, normalize(sub(_cone.end, _cone.pos) ), lerp(_cone.radius, 0.0f, tt)}, _pos);
}

bool overlap(const Cone& _cone, const Cylinder& _cylinder)
{
	BX_UNUSED(_cone, _cylinder);
	return false;
}

bool overlap(const Cone& _cone, const Capsule& _capsule)
{
	BX_UNUSED(_cone, _capsule);
	return false;
}

bool overlap(const Cone& _coneA, const Cone& _coneB)
{
	BX_UNUSED(_coneA, _coneB);
	return false;
}

bool overlap(const Cone& _cone, const Disk& _disk)
{
	BX_UNUSED(_cone, _disk);
	return false;
}

bool overlap(const Cone& _cone, const Obb& _obb)
{
	BX_UNUSED(_cone, _obb);
	return false;
}

bool overlap(const Cylinder& _cylinder, const Vec3& _pos)
{
	const Vec3 pos = closestPoint(LineSegment{_cylinder.pos, _cylinder.end}, _pos);
	return overlap(Disk{pos, normalize(sub(_cylinder.end, _cylinder.pos) ), _cylinder.radius}, _pos);
}

bool overlap(const Cylinder& _cylinder, const Sphere& _sphere)
{
	const Vec3 pos = closestPoint(LineSegment{_cylinder.pos, _cylinder.end}, _sphere.center);
	return overlap(Disk{pos, normalize(sub(_cylinder.end, _cylinder.pos) ), _cylinder.radius}, _sphere);
}

bool overlap(const Cylinder& _cylinder, const Aabb& _aabb)
{
	const Vec3 pos = closestPoint(LineSegment{_cylinder.pos, _cylinder.end}, getCenter(_aabb) );
	return overlap(Disk{pos, normalize(sub(_cylinder.end, _cylinder.pos) ), _cylinder.radius}, _aabb);
}

bool overlap(const Cylinder& _cylinder, const Plane& _plane)
{
	BX_UNUSED(_cylinder, _plane);
	return false;
}

bool overlap(const Cylinder& _cylinderA, const Cylinder& _cylinderB)
{
	BX_UNUSED(_cylinderA, _cylinderB);
	return false;
}

bool overlap(const Cylinder& _cylinder, const Capsule& _capsule)
{
	BX_UNUSED(_cylinder, _capsule);
	return false;
}

bool overlap(const Cylinder& _cylinder, const Disk& _disk)
{
	BX_UNUSED(_cylinder, _disk);
	return false;
}

bool overlap(const Cylinder& _cylinder, const Obb& _obb)
{
	BX_UNUSED(_cylinder, _obb);
	return false;
}

bool overlap(const Disk& _disk, const Vec3& _pos)
{
	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	if (!isNearZero(distance(plane, _pos) ) )
	{
		return false;
	}

	return distanceSq(_disk.center, _pos) <= square(_disk.radius);
}

bool overlap(const Disk& _disk, const Plane& _plane)
{
	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	if (!overlap(plane, _plane) )
	{
		return false;
	}

	return overlap(_plane, Sphere{_disk.center, _disk.radius});
}

bool overlap(const Disk& _disk, const Capsule& _capsule)
{
	if (!overlap(_capsule, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_capsule, plane);
}

bool overlap(const Disk& _diskA, const Disk& _diskB)
{
	Plane planeA(init::None);
	calcPlane(planeA, _diskA.normal, _diskA.center);

	Plane planeB(init::None);
	calcPlane(planeB, _diskB);

	Line line;

	if (!intersect(line, planeA, planeB) )
	{
		return false;
	}

	const Vec3 pa = closestPoint(line, _diskA.center);
	const Vec3 pb = closestPoint(line, _diskB.center);

	const float lenA = distance(pa, _diskA.center);
	const float lenB = distance(pb, _diskB.center);

	return bx::sqrt(square(_diskA.radius) - square(lenA) )
		+  bx::sqrt(square(_diskB.radius) - square(lenB) )
		>= distance(pa, pb)
		;
}

bool overlap(const Disk& _disk, const Obb& _obb)
{
	if (!overlap(_obb, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_obb, plane);
}

bool overlap(const Obb& _obb, const Vec3& _pos)
{
	const Srt srt = toSrt(_obb.mtx);

	Aabb aabb;
	toAabb(aabb, srt.scale);

	const Quaternion invRotation = invert(srt.rotation);
	const Vec3 pos = mul(sub(_pos, srt.translation), invRotation);

	return overlap(aabb, pos);
}

bool overlap(const Obb& _obb, const Plane& _plane)
{
	const Srt srt = toSrt(_obb.mtx);

	const Quaternion invRotation = invert(srt.rotation);
	const Vec3 axis =
	{
		projectToAxis(_plane.normal, mul(Vec3{1.0f, 0.0f, 0.0f}, invRotation) ),
		projectToAxis(_plane.normal, mul(Vec3{0.0f, 1.0f, 0.0f}, invRotation) ),
		projectToAxis(_plane.normal, mul(Vec3{0.0f, 0.0f, 1.0f}, invRotation) ),
	};

	const float dist   = bx::abs(distance(_plane, srt.translation) );
	const float radius = dot(srt.scale, bx::abs(axis) );

	return dist <= radius;
}

bool overlap(const Obb& _obb, const Capsule& _capsule)
{
	const Srt srt = toSrt(_obb.mtx);

	Aabb aabb;
	toAabb(aabb, srt.scale);

	const Quaternion invRotation = invert(srt.rotation);

	const Capsule capsule =
	{
		mul(sub(_capsule.pos, srt.translation), invRotation),
		mul(sub(_capsule.end, srt.translation), invRotation),
		_capsule.radius,
	};

	return overlap(aabb, capsule);
}

bool overlap(const Obb& _obbA, const Obb& _obbB)
{
	const Srt srtA = toSrt(_obbA.mtx);
	const Srt srtB = toSrt(_obbB.mtx);

	return overlap(srtA, srtB);
}

bool overlap(const Plane& _plane, const LineSegment& _line)
{
	return isNearZero(distance(_plane, _line) );
}

bool overlap(const Plane& _plane, const Vec3& _pos)
{
	return isNearZero(distance(_plane, _pos) );
}

bool overlap(const Plane& _planeA, const Plane& _planeB)
{
	const Vec3  dir = cross(_planeA.normal, _planeB.normal);
	const float len = length(dir);

	return !isNearZero(len);
}

bool overlap(const Plane& _plane, const Cone& _cone)
{
	const Vec3 axis = sub(_cone.pos, _cone.end);
	const float len = length(axis);
	const Vec3 dir  = normalize(axis);

	const Vec3 v1 = cross(_plane.normal, dir);
	const Vec3 v2 = cross(v1, dir);

	const float bb = len;
	const float aa = _cone.radius;
	const float cc = bx::sqrt(square(aa) + square(bb) );

	const Vec3 pos = add(add(_cone.end
		, mul(dir, len * bb/cc) )
		, mul(v2,  len * aa/cc)
		);

	return overlap(_plane, LineSegment{pos, _cone.end});
}

bool overlap(const Sphere& _sphere, const Vec3& _pos)
{
	const float distSq   = distanceSq(_sphere.center, _pos);
	const float radiusSq = square(_sphere.radius);
	return distSq <= radiusSq;
}

bool overlap(const Sphere& _sphereA, const Sphere& _sphereB)
{
	const float distSq   = distanceSq(_sphereA.center, _sphereB.center);
	const float radiusSq = square(_sphereA.radius + _sphereB.radius);
	return distSq <= radiusSq;
}

bool overlap(const Sphere& _sphere, const Aabb& _aabb)
{
	const Vec3 pos = closestPoint(_aabb, _sphere.center);
	return overlap(_sphere, pos);
}

bool overlap(const Sphere& _sphere, const Plane& _plane)
{
	return bx::abs(distance(_plane, _sphere.center) ) <= _sphere.radius;
}

bool overlap(const Sphere& _sphere, const Triangle& _triangle)
{
	Plane plane(init::None);
	calcPlane(plane, _triangle);

	if (!overlap(_sphere, plane) )
	{
		return false;
	}

	const Vec3 pos = closestPoint(plane, _sphere.center);
	const Vec3 uvw = barycentric(_triangle, pos);
	const float nr = -_sphere.radius;

	return uvw.x >= nr
		&& uvw.y >= nr
		&& uvw.z >= nr
		;
}

bool overlap(const Sphere& _sphere, const Capsule& _capsule)
{
	const Vec3 pos = closestPoint(LineSegment{_capsule.pos, _capsule.end}, _sphere.center);
	return overlap(_sphere, Sphere{pos, _capsule.radius});
}

bool overlap(const Sphere& _sphere, const Cone& _cone)
{
	float tt;
	const Vec3 pos = closestPoint(LineSegment{_cone.pos, _cone.end}, _sphere.center, tt);
	return overlap(_sphere, Sphere{pos, lerp(_cone.radius, 0.0f, tt)});
}

bool overlap(const Sphere& _sphere, const Disk& _disk)
{
	if (!overlap(_sphere, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_sphere, plane);
}

bool overlap(const Sphere& _sphere, const Obb& _obb)
{
	const Vec3 pos = closestPoint(_obb, _sphere.center);
	return overlap(_sphere, pos);
}

bool overlap(const Triangle& _triangle, const Vec3& _pos)
{
	const Vec3 uvw = barycentric(_triangle, _pos);

	return uvw.x >= 0.0f
		&& uvw.y >= 0.0f
		&& uvw.z >= 0.0f
		;
}

bool overlap(const Triangle& _triangle, const Plane& _plane)
{
	const float dist0 = distance(_plane, _triangle.v0);
	const float dist1 = distance(_plane, _triangle.v1);
	const float dist2 = distance(_plane, _triangle.v2);

	const float minDist = min(dist0, dist1, dist2);
	const float maxDist = max(dist0, dist1, dist2);

	return 0.0f > minDist
		&& 0.0f < maxDist
		;
}

inline bool overlap(const Triangle& _triangleA, const Triangle& _triangleB, const Vec3& _axis)
{
	const Interval ia = projectToAxis(_axis, _triangleA);
	const Interval ib = projectToAxis(_axis, _triangleB);
	return overlap(ia, ib);
}

bool overlap(const Triangle& _triangleA, const Triangle& _triangleB)
{
	const Vec3 baA = sub(_triangleA.v1, _triangleA.v0);
	const Vec3 cbA = sub(_triangleA.v2, _triangleA.v1);
	const Vec3 acA = sub(_triangleA.v0, _triangleA.v2);

	const Vec3 baB = sub(_triangleB.v1, _triangleB.v0);
	const Vec3 cbB = sub(_triangleB.v2, _triangleB.v1);
	const Vec3 acB = sub(_triangleB.v0, _triangleB.v2);

	return overlap(_triangleA, _triangleB, cross(baA, cbA) )
		&& overlap(_triangleA, _triangleB, cross(baB, cbB) )
		&& overlap(_triangleA, _triangleB, cross(baB, baA) )
		&& overlap(_triangleA, _triangleB, cross(baB, cbA) )
		&& overlap(_triangleA, _triangleB, cross(baB, acA) )
		&& overlap(_triangleA, _triangleB, cross(cbB, baA) )
		&& overlap(_triangleA, _triangleB, cross(cbB, cbA) )
		&& overlap(_triangleA, _triangleB, cross(cbB, acA) )
		&& overlap(_triangleA, _triangleB, cross(acB, baA) )
		&& overlap(_triangleA, _triangleB, cross(acB, cbA) )
		&& overlap(_triangleA, _triangleB, cross(acB, acA) )
		;
}

template<typename Ty>
bool overlap(const Triangle& _triangle, const Ty& _ty)
{
	Plane plane(init::None);
	calcPlane(plane, _triangle);

	plane.normal = neg(plane.normal);
	plane.dist   = -plane.dist;

	const LineSegment line =
	{
		_ty.pos,
		_ty.end,
	};

	Hit hit;
	if (intersect(line, plane, &hit) )
	{
		return true;
	}

	const Vec3 pos = closestPoint(plane, hit.pos);
	const Vec3 uvw = barycentric(_triangle, pos);

	const float nr = -_ty.radius;

	if (uvw.x >= nr
	&&  uvw.y >= nr
	&&  uvw.z >= nr)
	{
		return true;
	}

	const LineSegment ab = LineSegment{_triangle.v0, _triangle.v1};
	const LineSegment bc = LineSegment{_triangle.v1, _triangle.v2};
	const LineSegment ca = LineSegment{_triangle.v2, _triangle.v0};

	float ta0 = 0.0f, tb0 = 0.0f;
	const bool i0 = intersect(ta0, tb0, ab, line);

	float ta1, tb1;
	const bool i1 = intersect(ta1, tb1, bc, line);

	float ta2, tb2;
	const bool i2 = intersect(ta2, tb2, ca, line);

	if (!i0
	||  !i1
	||  !i2)
	{
		return false;
	}

	ta0 = clamp(ta0, 0.0f, 1.0f);
	ta1 = clamp(ta1, 0.0f, 1.0f);
	ta2 = clamp(ta2, 0.0f, 1.0f);
	tb0 = clamp(tb0, 0.0f, 1.0f);
	tb1 = clamp(tb1, 0.0f, 1.0f);
	tb2 = clamp(tb2, 0.0f, 1.0f);

	const Vec3 pa0 = getPointAt(ab, ta0);
	const Vec3 pa1 = getPointAt(bc, ta1);
	const Vec3 pa2 = getPointAt(ca, ta2);

	const Vec3 pb0 = getPointAt(line, tb0);
	const Vec3 pb1 = getPointAt(line, tb1);
	const Vec3 pb2 = getPointAt(line, tb2);

	const float d0 = distanceSq(pa0, pb0);
	const float d1 = distanceSq(pa1, pb1);
	const float d2 = distanceSq(pa2, pb2);

	if (d0 <= d1
	&&  d0 <= d2)
	{
		return overlap(_ty, pa0);
	}
	else if (d1 <= d2)
	{
		return overlap(_ty, pa1);
	}

	return overlap(_ty, pa2);
}

bool overlap(const Triangle& _triangle, const Cylinder& _cylinder)
{
	return overlap<Cylinder>(_triangle, _cylinder);
}

bool overlap(const Triangle& _triangle, const Capsule& _capsule)
{
	return overlap<Capsule>(_triangle, _capsule);
}

bool overlap(const Triangle& _triangle, const Cone& _cone)
{
	const LineSegment ab = LineSegment{_triangle.v0, _triangle.v1};
	const LineSegment bc = LineSegment{_triangle.v1, _triangle.v2};
	const LineSegment ca = LineSegment{_triangle.v2, _triangle.v0};

	const LineSegment line =
	{
		_cone.pos,
		_cone.end,
	};

	float ta0 = 0.0f, tb0 = 0.0f;
	const bool i0 = intersect(ta0, tb0, ab, line);

	float ta1, tb1;
	const bool i1 = intersect(ta1, tb1, bc, line);

	float ta2, tb2;
	const bool i2 = intersect(ta2, tb2, ca, line);

	if (!i0
	||  !i1
	||  !i2)
	{
		return false;
	}

	ta0 = clamp(ta0, 0.0f, 1.0f);
	ta1 = clamp(ta1, 0.0f, 1.0f);
	ta2 = clamp(ta2, 0.0f, 1.0f);
	tb0 = clamp(tb0, 0.0f, 1.0f);
	tb1 = clamp(tb1, 0.0f, 1.0f);
	tb2 = clamp(tb2, 0.0f, 1.0f);

	const Vec3 pa0 = getPointAt(ab, ta0);
	const Vec3 pa1 = getPointAt(bc, ta1);
	const Vec3 pa2 = getPointAt(ca, ta2);

	const Vec3 pb0 = getPointAt(line, tb0);
	const Vec3 pb1 = getPointAt(line, tb1);
	const Vec3 pb2 = getPointAt(line, tb2);

	const float d0 = distanceSq(pa0, pb0);
	const float d1 = distanceSq(pa1, pb1);
	const float d2 = distanceSq(pa2, pb2);

	if (d0 <= d1
	&&  d0 <= d2)
	{
		return overlap(_cone, pa0);
	}
	else if (d1 <= d2)
	{
		return overlap(_cone, pa1);
	}

	return overlap(_cone, pa2);
}

bool overlap(const Triangle& _triangle, const Disk& _disk)
{
	if (!overlap(_triangle, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	Plane plane(init::None);
	calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_triangle, plane);
}

bool overlap(const Triangle& _triangle, const Obb& _obb)
{
	const Srt srt = toSrt(_obb.mtx);

	Aabb aabb;
	toAabb(aabb, srt.scale);

	const Quaternion invRotation = invert(srt.rotation);

	const Triangle triangle =
	{
		mul(sub(_triangle.v0, srt.translation), invRotation),
		mul(sub(_triangle.v1, srt.translation), invRotation),
		mul(sub(_triangle.v2, srt.translation), invRotation),
	};

	return overlap(triangle, aabb);
}
