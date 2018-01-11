/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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

struct DdVertex
{
	float x, y, z;
};

struct SpriteHandle { uint16_t idx; };
inline bool isValid(SpriteHandle _handle) { return _handle.idx != UINT16_MAX; }

struct GeometryHandle { uint16_t idx; };
inline bool isValid(GeometryHandle _handle) { return _handle.idx != UINT16_MAX; }

///
void ddInit(bool _depthTestLess = true, bx::AllocatorI* _allocator = NULL);

///
void ddShutdown();

///
SpriteHandle ddCreateSprite(uint16_t _width, uint16_t _height, const void* _data);

///
void ddDestroy(SpriteHandle _handle);

///
GeometryHandle ddCreateGeometry(uint32_t _numVertices, const DdVertex* _vertices, uint32_t _numIndices = 0, const uint16_t* _indices = NULL);

///
void ddDestroy(GeometryHandle _handle);

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
void ddSetSpin(float _spin);

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
void ddDraw(const Cylinder& _cylinder);

///
void ddDraw(const Capsule& _capsule);

///
void ddDraw(const Disk& _disk);

///
void ddDraw(const Obb& _obb);

///
void ddDraw(const Sphere& _sphere);

///
void ddDraw(const Cone& _cone);

///
void ddDraw(GeometryHandle _handle);

///
void ddDrawLineList(uint32_t _numVertices, const DdVertex* _vertices, uint32_t _numIndices = 0, const uint16_t* _indices = NULL);

///
void ddDrawTriList(uint32_t _numVertices, const DdVertex* _vertices, uint32_t _numIndices = 0, const uint16_t* _indices = NULL);

///
void ddDrawFrustum(const void* _viewProj);

///
void ddDrawArc(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _degrees);

///
void ddDrawCircle(const void* _normal, const void* _center, float _radius, float _weight = 0.0f);

///
void ddDrawCircle(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _weight = 0.0f);

///
void ddDrawQuad(const float* _normal, const float* _center, float _size);

///
void ddDrawQuad(SpriteHandle _handle, const float* _normal, const float* _center, float _size);

///
void ddDrawQuad(bgfx::TextureHandle _handle, const float* _normal, const float* _center, float _size);

///
void ddDrawCone(const void* _from, const void* _to, float _radius);

///
void ddDrawCylinder(const void* _from, const void* _to, float _radius);

///
void ddDrawCapsule(const void* _from, const void* _to, float _radius);

///
void ddDrawAxis(float _x, float _y, float _z, float _len = 1.0f, Axis::Enum _highlight = Axis::Count, float _thickness = 0.0f);

///
void ddDrawGrid(const void* _normal, const void* _center, uint32_t _size = 20, float _step = 1.0f);

///
void ddDrawGrid(Axis::Enum _axis, const void* _center, uint32_t _size = 20, float _step = 1.0f);

///
void ddDrawOrb(float _x, float _y, float _z, float _radius, Axis::Enum _highlight = Axis::Count);

#endif // DEBUGDRAW_H_HEADER_GUARD
