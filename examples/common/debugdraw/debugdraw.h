/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef DEBUGDRAW_H_HEADER_GUARD
#define DEBUGDRAW_H_HEADER_GUARD

#include <bx/allocator.h>
#include "../bounds.h"

struct Axis
{
	enum Enum
	{
		X,
		Y,
		Z,

		Count
	};
};

///
void ddInit(bool _depthTestLess = true, bx::AllocatorI* _allocator = NULL);

///
void ddShutdown();

///
void ddBegin(uint8_t _viewId);

///
void ddEnd();

///
void ddPush();

///
void ddPop();

///
void ddSetState(bool _depthTest, bool _depthWrite, bool _clockwise);

///
void ddSetColor(uint32_t _abgr);

///
void ddSetLod(uint8_t _lod);

///
void ddSetWireframe(bool _wireframe);

///
void ddSetStipple(bool _stipple, float _scale = 1.0f, float _offset = 0.0f);

///
void ddSetTransform(const void* _mtx);

///
void ddSetTranslate(float _x, float _y, float _z);

///
void ddMoveTo(float _x, float _y, float _z = 0.0f);

///
void ddMoveTo(const void* _pos);

///
void ddLineTo(float _x, float _y, float _z = 0.0f);

///
void ddLineTo(const void* _pos);

///
void ddClose();

///
void ddDraw(const Aabb& _aabb);

///
void ddDraw(const Cylinder& _cylinder, bool _capsule = false);

///
void ddDraw(const Disk& _disk);

///
void ddDraw(const Obb& _obb);

///
void ddDraw(const Sphere& _sphere);

///
void ddDrawFrustum(const void* _viewProj);

///
void ddDrawArc(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _degrees);

///
void ddDrawCircle(const void* _normal, const void* _center, float _radius, float _weight = 0.0f);

///
void ddDrawCircle(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _weight = 0.0f);

///
void ddDrawCone(const void* _from, const void* _to, float _radius, float _weight = 0.0f);

///
void ddDrawCylinder(const void* _from, const void* _to, float _radius, float _weight = 0.0f);

///
void ddDrawAxis(float _x, float _y, float _z, float _len = 1.0f, Axis::Enum _highlight = Axis::Count);

///
void ddDrawGrid(const void* _normal, const void* _center, uint32_t _size = 20, float _step = 1.0f);

///
void ddDrawGrid(Axis::Enum _axis, const void* _center, uint32_t _size = 20, float _step = 1.0f);

///
void ddDrawOrb(float _x, float _y, float _z, float _radius, Axis::Enum _highlight = Axis::Count);

#endif // DEBUGDRAW_H_HEADER_GUARD
