/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BOUNDS_H_HEADER_GUARD
#define BOUNDS_H_HEADER_GUARD

#include <bx/math.h>

///
struct Aabb
{
	bx::Vec3 min;
	bx::Vec3 max;
};

///
struct Capsule
{
	bx::Vec3 pos;
	bx::Vec3 end;
	float    radius;
};

///
struct Cone
{
	bx::Vec3 pos;
	bx::Vec3 end;
	float    radius;
};

///
struct Cylinder
{
	bx::Vec3 pos;
	bx::Vec3 end;
	float    radius;
};

///
struct Disk
{
	bx::Vec3 center;
	bx::Vec3 normal;
	float    radius;
};

///
struct Obb
{
	float mtx[16];
};

///
struct Sphere
{
	bx::Vec3 center;
	float    radius;
};

///
struct Triangle
{
	bx::Vec3 v0;
	bx::Vec3 v1;
	bx::Vec3 v2;
};

///
struct Ray
{
	bx::Vec3 pos;
	bx::Vec3 dir;
};

///
struct Hit
{
	bx::Vec3  pos;
	bx::Plane plane;
};

///
bx::Vec3 getCenter(const Aabb& _aabb);

///
bx::Vec3 getExtents(const Aabb& _aabb);

///
bx::Vec3 getCenter(const Triangle& _triangle);

///
void toAabb(Aabb& _outAabb, const bx::Vec3& _extents);

///
void toAabb(Aabb& _outAabb, const bx::Vec3& _center, const bx::Vec3& _extents);

/// Convert cylinder to axis aligned bounding box.
void toAabb(Aabb& _outAabb, const Cylinder& _cylinder);

/// Convert disk to axis aligned bounding box.
void toAabb(Aabb& _outAabb, const Disk& _disk);

/// Convert oriented bounding box to axis aligned bounding box.
void toAabb(Aabb& _outAabb, const Obb& _obb);

/// Convert sphere to axis aligned bounding box.
void toAabb(Aabb& _outAabb, const Sphere& _sphere);

/// Convert triangle to axis aligned bounding box.
void toAabb(Aabb& _outAabb, const Triangle& _triangle);

/// Calculate axis aligned bounding box.
void toAabb(Aabb& _outAabb, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Transform vertices and calculate axis aligned bounding box.
void toAabb(Aabb& _outAabb, const float* _mtx, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Expand AABB.
void aabbExpand(Aabb& _outAabb, float _factor);

/// Expand AABB with xyz.
void aabbExpand(Aabb& _outAabb, const bx::Vec3& _pos);

/// Calculate surface area of axis aligned bounding box.
float calcAreaAabb(const Aabb& _aabb);

/// Convert axis aligned bounding box to oriented bounding box.
void toObb(Obb& _outObb, const Aabb& _aabb);

/// Calculate oriented bounding box.
void calcObb(Obb& _outObb, const void* _vertices, uint32_t _numVertices, uint32_t _stride, uint32_t _steps = 17);

/// Calculate maximum bounding sphere.
void calcMaxBoundingSphere(Sphere& _outSphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Calculate minimum bounding sphere.
void calcMinBoundingSphere(Sphere& _outSphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step = 0.01f);

/// Returns 6 (near, far, left, right, top, bottom) planes representing frustum planes.
void buildFrustumPlanes(bx::Plane* _outPlanes, const float* _viewProj);

/// Returns point from 3 intersecting planes.
bx::Vec3 intersectPlanes(const bx::Plane& _pa, const bx::Plane& _pb, const bx::Plane& _pc);

/// Make screen space ray from x, y coordinate and inverse view-projection matrix.
Ray makeRay(float _x, float _y, const float* _invVp);

/// Intersect ray / AABB.
bool intersect(const Ray& _ray, const Aabb& _aabb, Hit* _hit = NULL);

/// Intersect ray / OBB.
bool intersect(const Ray& _ray, const Obb& _obb, Hit* _hit = NULL);

/// Intersect ray / cylinder.
bool intersect(const Ray& _ray, const Cylinder& _cylinder, Hit* _hit = NULL);

/// Intersect ray / capsule.
bool intersect(const Ray& _ray, const Capsule& _capsule, Hit* _hit = NULL);

/// Intersect ray / cone.
bool intersect(const Ray& _ray, const Cone& _cone, Hit* _hit = NULL);

/// Intersect ray / disk.
bool intersect(const Ray& _ray, const Disk& _disk, Hit* _hit = NULL);

/// Intersect ray / plane.
bool intersect(const Ray& _ray, const bx::Plane& _plane, Hit* _hit = NULL);

/// Intersect ray / sphere.
bool intersect(const Ray& _ray, const Sphere& _sphere, Hit* _hit = NULL);

/// Intersect ray / triangle.
bool intersect(const Ray& _ray, const Triangle& _triangle, Hit* _hit = NULL);

///
bool overlap(const Aabb& _aabb, const bx::Vec3& _pos);

///
bool overlap(const Aabb& _aabb, const Sphere& _sphere);

///
bool overlap(const Aabb& _aabbA, const Aabb& _aabbB);

///
bool overlap(const Aabb& _aabb, const bx::Plane& _plane);

///
bool overlap(const Aabb& _aabb, const Triangle& _triangle);

///
bool overlap(const Aabb& _aabb, const Cylinder& _cylinder);

///
bool overlap(const Aabb& _aabb, const Capsule& _capsule);

///
bool overlap(const Aabb& _aabb, const Cone& _cone);

///
bool overlap(const Aabb& _aabb, const Disk& _disk);

///
bool overlap(const Aabb& _aabb, const Obb& _obb);

///
bool overlap(const Capsule& _capsule, const bx::Vec3& _pos);

///
bool overlap(const Capsule& _capsule, const Sphere& _sphere);

///
bool overlap(const Capsule& _capsule, const Aabb& _aabb);

///
bool overlap(const Capsule& _capsule, const bx::Plane& _plane);

///
bool overlap(const Capsule& _capsule, const Triangle& _triangle);

///
bool overlap(const Capsule& _capsule, const Cylinder& _cylinder);

///
bool overlap(const Capsule& _capsuleA, const Capsule& _capsuleB);

///
bool overlap(const Capsule& _capsule, const Cone& _cone);

///
bool overlap(const Capsule& _capsule, const Disk& _disk);

///
bool overlap(const Capsule& _capsule, const Obb& _obb);

///
bool overlap(const Cone& _cone, const bx::Vec3& _pos);

///
bool overlap(const Cone& _cone, const Sphere& _sphere);

///
bool overlap(const Cone& _cone, const Aabb& _aabb);

///
bool overlap(const Cone& _cone, const bx::Plane& _plane);

///
bool overlap(const Cone& _cone, const Triangle& _triangle);

///
bool overlap(const Cone& _cone, const Cylinder& _cylinder);

///
bool overlap(const Cone& _cone, const Capsule& _capsule);

///
bool overlap(const Cone& _coneA, const Cone& _coneB);

///
bool overlap(const Cone& _cone, const Disk& _disk);

///
bool overlap(const Cone& _cone, const Obb& _obb);

///
bool overlap(const Cylinder& _cylinder, const bx::Vec3& _pos);

///
bool overlap(const Cylinder& _cylinder, const Sphere& _sphere);

///
bool overlap(const Cylinder& _cylinder, const Aabb& _aabb);

///
bool overlap(const Cylinder& _cylinder, const bx::Plane& _plane);

///
bool overlap(const Cylinder& _cylinder, const Triangle& _triangle);

///
bool overlap(const Cylinder& _cylinderA, const Cylinder& _cylinderB);

///
bool overlap(const Cylinder& _cylinder, const Capsule& _capsule);

///
bool overlap(const Cylinder& _cylinder, const Cone& _cone);

///
bool overlap(const Cylinder& _cylinder, const Disk& _disk);

///
bool overlap(const Cylinder& _cylinder, const Obb& _obb);

///
bool overlap(const Disk& _disk, const bx::Vec3& _pos);

///
bool overlap(const Disk& _disk, const Sphere& _sphere);

///
bool overlap(const Disk& _disk, const Aabb& _aabb);

///
bool overlap(const Disk& _disk, const bx::Plane& _plane);

///
bool overlap(const Disk& _disk, const Triangle& _triangle);

///
bool overlap(const Disk& _disk, const Cylinder& _cylinder);

///
bool overlap(const Disk& _disk, const Capsule& _capsule);

///
bool overlap(const Disk& _disk, const Cone& _cone);

///
bool overlap(const Disk& _diskA, const Disk& _diskB);

///
bool overlap(const Disk& _disk, const Obb& _obb);

///
bool overlap(const Obb& _obb, const bx::Vec3& _pos);

///
bool overlap(const Obb& _obb, const Sphere& _sphere);

///
bool overlap(const Obb& _obb, const Aabb& _aabb);

///
bool overlap(const Obb& _obb, const bx::Plane& _plane);

///
bool overlap(const Obb& _obb, const Triangle& _triangle);

///
bool overlap(const Obb& _obb, const Cylinder& _cylinder);

///
bool overlap(const Obb& _obb, const Capsule& _capsule);

///
bool overlap(const Obb& _obb, const Cone& _cone);

///
bool overlap(const Obb& _obb, const Disk& _disk);

///
bool overlap(const Obb& _obbA, const Obb& _obbB);

///
bool overlap(const bx::Plane& _plane, const bx::Vec3& _pos);

///
bool overlap(const bx::Plane& _plane, const Sphere& _sphere);

///
bool overlap(const bx::Plane& _plane, const Aabb& _aabb);

///
bool overlap(const bx::Plane& _planeA, const bx::Plane& _planeB);

///
bool overlap(const bx::Plane& _plane, const Triangle& _triangle);

///
bool overlap(const bx::Plane& _plane, const Cylinder& _cylinder);

///
bool overlap(const bx::Plane& _plane, const Capsule& _capsule);

///
bool overlap(const bx::Plane& _plane, const Cone& _cone);

///
bool overlap(const bx::Plane& _plane, const Disk& _disk);

///
bool overlap(const bx::Plane& _plane, const Obb& _obb);

///
bool overlap(const Sphere& _sphere, const bx::Vec3& _pos);

///
bool overlap(const Sphere& _sphereA, const Sphere& _sphereB);

///
bool overlap(const Sphere& _sphere, const Aabb& _aabb);

///
bool overlap(const Sphere& _sphere, const bx::Plane& _plane);

///
bool overlap(const Sphere& _sphere, const Triangle& _triangle);

///
bool overlap(const Sphere& _sphere, const Cylinder& _cylinder);

///
bool overlap(const Sphere& _sphere, const Capsule& _capsule);

///
bool overlap(const Sphere& _sphere, const Cone& _cone);

///
bool overlap(const Sphere& _sphere, const Disk& _disk);

///
bool overlap(const Sphere& _sphere, const Obb& _obb);

///
bool overlap(const Triangle& _triangle, const bx::Vec3& _pos);

///
bool overlap(const Triangle& _triangle, const Sphere& _sphere);

///
bool overlap(const Triangle& _triangle, const Aabb& _aabb);

///
bool overlap(const Triangle& _triangle, const bx::Plane& _plane);

///
bool overlap(const Triangle& _triangleA, const Triangle& _triangleB);

///
bool overlap(const Triangle& _triangle, const Cylinder& _cylinder);

///
bool overlap(const Triangle& _triangle, const Capsule& _capsule);

///
bool overlap(const Triangle& _triangle, const Cone& _cone);

///
bool overlap(const Triangle& _triangle, const Disk& _disk);

///
bool overlap(const Triangle& _triangle, const Obb& _obb);

#include "bounds.inl"

#endif // BOUNDS_H_HEADER_GUARD
