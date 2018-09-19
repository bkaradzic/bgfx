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
void ddInit(bx::AllocatorI* _allocator = NULL);

///
void ddShutdown();

///
SpriteHandle ddCreateSprite(uint16_t _width, uint16_t _height, const void* _data);

///
void ddDestroy(SpriteHandle _handle);

///
GeometryHandle ddCreateGeometry(uint32_t _numVertices, const DdVertex* _vertices, uint32_t _numIndices = 0, const void* _indices = NULL, bool _index32 = false);

///
void ddDestroy(GeometryHandle _handle);


struct DebugDrawEncoder
{
	///
	DebugDrawEncoder();

	///
	~DebugDrawEncoder();

	///
	void begin(uint16_t _viewId, bool _depthTestLess = true, bgfx::Encoder* _encoder = NULL);

	///
	void end();

	///
	void push();

	///
	void pop();

	///
	void setDepthTestLess(bool _depthTestLess);

	///
	void setState(bool _depthTest, bool _depthWrite, bool _clockwise);

	///
	void setColor(uint32_t _abgr);

	///
	void setLod(uint8_t _lod);

	///
	void setWireframe(bool _wireframe);

	///
	void setStipple(bool _stipple, float _scale = 1.0f, float _offset = 0.0f);

	///
	void setSpin(float _spin);

	///
	void setTransform(const void* _mtx);

	///
	void setTranslate(float _x, float _y, float _z);

	///
	void pushTransform(const void* _mtx);

	///
	void popTransform();

	///
	void moveTo(float _x, float _y, float _z = 0.0f);

	///
	void moveTo(const void* _pos);

	///
	void lineTo(float _x, float _y, float _z = 0.0f);

	///
	void lineTo(const void* _pos);

	///
	void close();

	///
	void draw(const Aabb& _aabb);

	///
	void draw(const Cylinder& _cylinder);

	///
	void draw(const Capsule& _capsule);

	///
	void draw(const Disk& _disk);

	///
	void draw(const Obb& _obb);

	///
	void draw(const Sphere& _sphere);

	///
	void draw(const Cone& _cone);

	///
	void draw(GeometryHandle _handle);

	///
	void drawLineList(uint32_t _numVertices, const DdVertex* _vertices, uint32_t _numIndices = 0, const uint16_t* _indices = NULL);

	///
	void drawTriList(uint32_t _numVertices, const DdVertex* _vertices, uint32_t _numIndices = 0, const uint16_t* _indices = NULL);

	///
	void drawFrustum(const void* _viewProj);

	///
	void drawArc(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _degrees);

	///
	void drawCircle(const void* _normal, const void* _center, float _radius, float _weight = 0.0f);

	///
	void drawCircle(Axis::Enum _axis, float _x, float _y, float _z, float _radius, float _weight = 0.0f);

	///
	void drawQuad(const float* _normal, const float* _center, float _size);

	///
	void drawQuad(SpriteHandle _handle, const float* _normal, const float* _center, float _size);

	///
	void drawQuad(bgfx::TextureHandle _handle, const float* _normal, const float* _center, float _size);

	///
	void drawCone(const void* _from, const void* _to, float _radius);

	///
	void drawCylinder(const void* _from, const void* _to, float _radius);

	///
	void drawCapsule(const void* _from, const void* _to, float _radius);

	///
	void drawAxis(float _x, float _y, float _z, float _len = 1.0f, Axis::Enum _highlight = Axis::Count, float _thickness = 0.0f);

	///
	void drawGrid(const void* _normal, const void* _center, uint32_t _size = 20, float _step = 1.0f);

	///
	void drawGrid(Axis::Enum _axis, const void* _center, uint32_t _size = 20, float _step = 1.0f);

	///
	void drawOrb(float _x, float _y, float _z, float _radius, Axis::Enum _highlight = Axis::Count);

	BX_ALIGN_DECL_CACHE_LINE(uint8_t) m_internal[50<<10];
};

#endif // DEBUGDRAW_H_HEADER_GUARD
