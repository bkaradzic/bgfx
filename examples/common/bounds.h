/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BOUNDS_H_HEADER_GUARD
#define BOUNDS_H_HEADER_GUARD

struct Aabb
{
	float m_min[3];
	float m_max[3];
};

struct Cylinder
{
	float m_pos[3];
	float m_end[3];
	float m_radius;
};

struct Disk
{
	float m_center[3];
	float m_normal[3];
	float m_radius;
};

struct Obb
{
	float m_mtx[16];
};

struct Plane
{
	float m_normal[3];
	float m_dist;
};

struct Ray
{
	float m_pos[3];
	float m_dir[3];
};

struct Sphere
{
	float m_center[3];
	float m_radius;
};

struct Tris
{
	float m_v0[3];
	float m_v1[3];
	float m_v2[3];
};

struct Intersection
{
	float m_pos[3];
	float m_normal[3];
	float m_dist;
};

/// Convert axis aligned bounding box to oriented bounding box.
void aabbToObb(Obb& _obb, const Aabb& _aabb);

/// Convert sphere to axis aligned bounding box.
void sphereToAabb(Aabb& _aabb, const Sphere& _sphere);

/// Calculate surface area of axis aligned bounding box.
float calcAabbArea(Aabb& _aabb);

/// Calculate axis aligned bounding box.
void calcAabb(Aabb& _aabb, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Transform vertices and calculate axis aligned bounding box.
void calcAabb(Aabb& _aabb, const float* _mtx, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Expand AABB.
void aabbExpand(Aabb& _aabb, float _factor);

/// Returns 0 is two AABB don't overlap, otherwise returns flags of overlap
/// test.
uint32_t aabbOverlapTest(const Aabb& _aabb0, const Aabb& _aabb1);

/// Calculate oriented bounding box.
void calcObb(Obb& _obb, const void* _vertices, uint32_t _numVertices, uint32_t _stride, uint32_t _steps = 17);

/// Calculate maximum bounding sphere.
void calcMaxBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Calculate minimum bounding sphere.
void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step = 0.01f);

/// Calculate coplanar U/V vectors.
void calcPlaneUv(const Plane& _plane, float* _udir, float* _vdir);

/// Returns 6 (near, far, left, right, top, bottom) planes representing frustum planes.
void buildFrustumPlanes(Plane* _planes, const float* _viewProj);

/// Returns point from 3 intersecting planes.
void intersectPlanes(float _result[3], const Plane& _pa, const Plane& _pb, const Plane& _pc);

/// Make screen space ray from x, y coordinate and inverse view-projection matrix.
Ray makeRay(float _x, float _y, const float* _invVp);

/// Intersect ray / aabb.
bool intersect(const Ray& _ray, const Aabb& _aabb, Intersection* _intersection = NULL);

/// Intersect ray / cylinder.
bool intersect(const Ray& _ray, const Cylinder& _cylinder, bool _capsule, Intersection* _intersection = NULL);

/// Intersect ray / disk.
bool intersect(const Ray& _ray, const Disk& _disk, Intersection* _intersection = NULL);

/// Intersect ray / plane.
bool intersect(const Ray& _ray, const Plane& _plane, Intersection* _intersection = NULL);

/// Intersect ray / sphere.
bool intersect(const Ray& _ray, const Sphere& _sphere, Intersection* _intersection = NULL);

/// Intersect ray / triangle.
bool intersect(const Ray& _ray, const Tris& _triangle, Intersection* _intersection = NULL);

#endif // BOUNDS_H_HEADER_GUARD
