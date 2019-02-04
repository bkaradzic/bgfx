/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
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
	return bx::mul(bx::add(bx::add(_triangle.v0, _triangle.v1), _triangle.v2), 1.0f/3.0f);
}

void toAabb(Aabb& _outAabb, const Vec3& _center, const Vec3& _extent)
{
	_outAabb.min = sub(_center, _extent);
	_outAabb.max = add(_center, _extent);
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
		_disk.radius * tmp.x * sqrt( (nsq.x + nsq.y * nsq.z) * inv),
		_disk.radius * tmp.y * sqrt( (nsq.y + nsq.z * nsq.x) * inv),
		_disk.radius * tmp.z * sqrt( (nsq.z + nsq.x * nsq.y) * inv),
	};

	_outAabb.min = sub(_disk.center, extent);
	_outAabb.max = add(_disk.center, extent);
}

void toAabb(Aabb& _outAabb, const Cylinder& _cylinder)
{
	// Reference(s):
	// - https://web.archive.org/web/20181113055756/http://iquilezles.org/www/articles/diskbbox/diskbbox.htm
	//
	const Vec3 axis = sub(_cylinder.end, _cylinder.pos);
	const Vec3 asq  = mul(axis, axis);
	const Vec3 nsq  = mul(asq, 1.0f/dot(axis, axis) );
	const Vec3 one  = { 1.0f, 1.0f, 1.0f };
	const Vec3 tmp  = sub(one, nsq);

	const float inv = 1.0f / (tmp.x*tmp.y*tmp.z);

	const Vec3 extent =
	{
		_cylinder.radius * tmp.x * sqrt( (nsq.x + nsq.y * nsq.z) * inv),
		_cylinder.radius * tmp.y * sqrt( (nsq.y + nsq.z * nsq.x) * inv),
		_cylinder.radius * tmp.z * sqrt( (nsq.z + nsq.x * nsq.y) * inv),
	};

	const Vec3 minP = sub(_cylinder.pos, extent);
	const Vec3 minE = sub(_cylinder.end, extent);
	const Vec3 maxP = add(_cylinder.pos, extent);
	const Vec3 maxE = add(_cylinder.end, extent);

	_outAabb.min = min(minP, minE);
	_outAabb.max = max(maxP, maxE);
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
	Vec3 mn, mx;
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
	Vec3 mn, mx;
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
	_sphere.radius = sqrt(maxDistSq);
}

void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step)
{
	RngMwc rng;

	uint8_t* vertex = (uint8_t*)_vertices;

	Vec3 center;
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
	_sphere.radius = sqrt(maxDistSq);
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
		const float len = length(plane->normal);
		plane->normal = normalize(plane->normal);
		float invLen = 1.0f / len;
		plane->dist *= invLen;
		++plane;
	}
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
	return add(mul(_ray.dir, _t), _ray.pos);
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
	Plane plane;
	plane.normal = _disk.normal;
	plane.dist   = -dot(_disk.center, _disk.normal);

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

	const float len = length(dxa);
	const Vec3 normal = normalize(dxa);
	const float dist = bx::abs(dot(rc, normal) );

	if (dist > _cylinder.radius)
	{
		return false;
	}

	Vec3 vo = cross(rc, axis);
	const float t0 = -dot(vo, normal) / len;

	vo = normalize(cross(normal, axis) );

	const float rsq   = square(_cylinder.radius);
	const float ddoto = dot(_ray.dir, vo);
	const float ss    = t0 - bx::abs(sqrt(rsq - square(dist) ) / ddoto);

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

	Plane plane;
	Vec3 pos;

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

	const float hyp    = sqrt(square(_cone.radius) + square(len) );
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

	det = sqrt(det);
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
		_hit->pos  = getPointAt(_ray, tt);
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

	const float sqrtDiscriminant = sqrt(discriminant);
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

void barycentric(float& _outU, float& _outV, float& _outW, const Triangle& _triangle, const Vec3& _pos)
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
	_outU = (dot11*dot02 - dot01*dot12)*invDenom;
	_outV = (dot00*dot12 - dot01*dot02)*invDenom;
	_outW = 1.0f - _outU - _outV;
}

Vec3 closestPoint(const Plane& _plane, const Vec3 _pos)
{
	const float dist = distance(_plane, _pos);
	return sub(_pos, mul(_plane.normal, dist) );
}

Vec3 closestPoint(const Aabb& _aabb, const Vec3 _pos)
{
	return clamp(_pos, _aabb.min, _aabb.max);
}

bool overlap(const Sphere& _sphere, const Vec3& _pos)
{
	const Vec3 ba = sub(_sphere.center, _pos);
	const float   rsq = square(_sphere.radius);
	return dot(ba, ba) <= rsq;
}

bool overlap(const Sphere& _sphereA, const Sphere& _sphereB)
{
	const Vec3   ba = sub(_sphereA.center, _sphereB.center);
	const float rsq = square(_sphereA.radius + _sphereB.radius);
	return dot(ba, ba) <= rsq;
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
	Plane plane;
	calcPlane(plane, _triangle.v0, _triangle.v1, _triangle.v2);

	if (!overlap(_sphere, plane) )
	{
		return false;
	}

	const Vec3 pos = closestPoint(plane, _sphere.center);

	float uu, vv, ww;
	barycentric(uu, vv, ww, _triangle, pos);

	const float nr = -_sphere.radius;

	return uu >= nr
		&& vv >= nr
		&& ww >= nr
		;
}

bool overlap(const Sphere& _sphere, const Cylinder& _cylinder)
{
	BX_UNUSED(_sphere, _cylinder);
	return false;
}

bool overlap(const Sphere& _sphere, const Capsule& _capsule)
{
	BX_UNUSED(_sphere, _capsule);
	return false;
}

bool overlap(const Sphere& _sphere, const Cone& _cone)
{
	BX_UNUSED(_sphere, _cone);
	return false;
}

bool overlap(const Sphere& _sphere, const Disk& _disk)
{
	if (!overlap(_sphere, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	bx::Plane plane;
	bx::calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_sphere, plane);
}

bool overlap(const Sphere& _sphere, const Obb& _obb)
{
	BX_UNUSED(_sphere, _obb);
	return false;
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

bool overlap(const Aabb& _aabb, const Sphere& _sphere)
{
	return overlap(_sphere, _aabb);
}

uint32_t overlapTestMask(const Aabb& _aabbA, const Aabb& _aabbB)
{
	/// Returns 0 is two AABB don't overlap, otherwise returns flags of overlap
	/// test.
	const uint32_t ltMinX = _aabbA.max.x < _aabbB.min.x;
	const uint32_t gtMaxX = _aabbA.min.x > _aabbB.max.x;
	const uint32_t ltMinY = _aabbA.max.y < _aabbB.min.y;
	const uint32_t gtMaxY = _aabbA.min.y > _aabbB.max.y;
	const uint32_t ltMinZ = _aabbA.max.z < _aabbB.min.z;
	const uint32_t gtMaxZ = _aabbA.min.z > _aabbB.max.z;

	return 0
		| (ltMinX << 0)
		| (gtMaxX << 1)
		| (ltMinY << 2)
		| (gtMaxY << 3)
		| (ltMinZ << 4)
		| (gtMaxZ << 5)
		;
}

bool overlap(const Aabb& _aabbA, const Aabb& _aabbB)
{
#if 0
	return 0 != overlapTestMask(_aabbA, _aabbB);
#else
	const Vec3 ac  = getCenter(_aabbA);
	const Vec3 bc  = getCenter(_aabbB);
	const Vec3 abc = bx::abs(sub(ac, bc) );
	const Vec3 ae  = getExtents(_aabbA);
	const Vec3 be  = getExtents(_aabbB);
	const Vec3 abe = add(ae, be);

	return abc.x <= abe.x
		&& abc.y <= abe.y
		&& abc.z <= abe.z
		;
#endif // 0
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

bool overlap(const Aabb& _aabb, const Triangle& _triangle)
{
	Plane plane;
	calcPlane(plane, _triangle.v0, _triangle.v1, _triangle.v2);

	if (!overlap(_aabb, plane) )
	{
		return false;
	}

	BX_UNUSED(_aabb, _triangle);
	return false;
}

bool overlap(const Aabb& _aabb, const Cylinder& _cylinder)
{
	BX_UNUSED(_aabb, _cylinder);
	return false;
}

bool overlap(const Aabb& _aabb, const Capsule& _capsule)
{
	BX_UNUSED(_aabb, _capsule);
	return false;
}

bool overlap(const Aabb& _aabb, const Cone& _cone)
{
	BX_UNUSED(_aabb, _cone);
	return false;
}

bool overlap(const Aabb& _aabb, const Disk& _disk)
{
	if (!overlap(_aabb, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	bx::Plane plane;
	bx::calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_aabb, plane);
}

bool overlap(const Aabb& _aabb, const Obb& _obb)
{
	BX_UNUSED(_aabb, _obb);
	return false;
}

bool overlap(const Triangle& _triangle, const bx::Vec3& _pos)
{
	float uu, vv, ww;
	barycentric(uu, vv, ww, _triangle, _pos);

	return uu >= 0.0f
		&& vv >= 0.0f
		&& ww >= 0.0f
		;
}

bool overlap(const Triangle& _triangle, const Sphere& _sphere)
{
	return overlap(_sphere, _triangle);
}

bool overlap(const Triangle& _triangle, const Aabb& _aabb)
{
	return overlap(_aabb, _triangle);
}

bool overlap(const Triangle& _triangle, const bx::Plane& _plane)
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

bool overlap(const Triangle& _triangleA, const Triangle& _triangleB)
{
	BX_UNUSED(_triangleA, _triangleB);
	return false;
}

bool overlap(const Triangle& _triangle, const Cylinder& _cylinder)
{
	BX_UNUSED(_triangle, _cylinder);
	return false;
}

bool overlap(const Triangle& _triangle, const Capsule& _capsule)
{
	BX_UNUSED(_triangle, _capsule);
	return false;
}

bool overlap(const Triangle& _triangle, const Cone& _cone)
{
	BX_UNUSED(_triangle, _cone);
	return false;
}

bool overlap(const Triangle& _triangle, const Disk& _disk)
{
	if (!overlap(_triangle, Sphere{_disk.center, _disk.radius}) )
	{
		return false;
	}

	bx::Plane plane;
	bx::calcPlane(plane, _disk.normal, _disk.center);

	return overlap(_triangle, plane);
}

bool overlap(const Triangle& _triangle, const Obb& _obb)
{
	BX_UNUSED(_triangle, _obb);
	return false;
}

