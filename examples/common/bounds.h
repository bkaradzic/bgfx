/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BOUNDS_H_HEADER_GUARD
#define BOUNDS_H_HEADER_GUARD

struct Aabb
{
	float m_min[3];
	float m_max[3];
};

struct Obb
{
	float m_mtx[16];
};

struct Sphere
{
	float m_center[3];
	float m_radius;
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
uint32_t aabbOverlapTest(Aabb& _aabb0, Aabb& _aabb1);

/// Calculate oriented bounding box.
void calcObb(Obb& _obb, const void* _vertices, uint32_t _numVertices, uint32_t _stride, uint32_t _steps = 17);

/// Calculate maximum bounding sphere.
void calcMaxBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride);

/// Calculate minimum bounding sphere.
void calcMinBoundingSphere(Sphere& _sphere, const void* _vertices, uint32_t _numVertices, uint32_t _stride, float _step = 0.01f);

#endif // BOUNDS_H_HEADER_GUARD
