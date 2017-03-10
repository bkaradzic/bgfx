/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef PARTICLE_SYSTEM_H_HEADER_GUARD
#define PARTICLE_SYSTEM_H_HEADER_GUARD

#include <bx/allocator.h>
#include <bx/easing.h>
#include <bx/rng.h>

#include "../bounds.h"

struct EmitterHandle       { uint16_t idx; };
struct EmitterSpriteHandle { uint16_t idx; };

template<typename Ty>
inline bool isValid(Ty _handle)
{
	return _handle.idx != UINT16_MAX;
}

struct EmitterShape
{
	enum Enum
	{
		Sphere,
		Hemisphere,
		Circle,
		Disc,
		Rect,

		Count
	};
};

struct EmitterDirection
{
	enum Enum
	{
		Up,
		Outward,

		Count
	};
};

struct EmitterUniforms
{
	void reset();

	float m_position[3];
	float m_angle[3];

	float m_blendStart[2];
	float m_blendEnd[2];
	float m_offsetStart[2];
	float m_offsetEnd[2];
	float m_scaleStart[2];
	float m_scaleEnd[2];
	float m_lifeSpan[2];
	float m_gravityScale;

	uint32_t m_rgba[5];
	uint32_t m_particlesPerSecond;

	bx::Easing::Enum m_easePos;
	bx::Easing::Enum m_easeRgba;
	bx::Easing::Enum m_easeBlend;
	bx::Easing::Enum m_easeScale;

	EmitterSpriteHandle m_handle;
};

///
void psInit(uint16_t _maxEmitters = 64, bx::AllocatorI* _allocator = NULL);

///
void psShutdown();

///
EmitterSpriteHandle psCreateSprite(uint16_t _width, uint16_t _height, const void* _data);

///
void psDestroy(EmitterSpriteHandle _handle);

///
EmitterHandle psCreateEmitter(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles);

///
void psUpdateEmitter(EmitterHandle _handle, const EmitterUniforms* _uniforms = NULL);

///
void psGetAabb(EmitterHandle _handle, Aabb& _outAabb);

///
void psDestroyEmitter(EmitterHandle _handle);

///
void psUpdate(float _dt);

///
void psRender(uint8_t _view, const float* _mtxView, const float* _eye);

#endif // PARTICLE_SYSTEM_H_HEADER_GUARD
