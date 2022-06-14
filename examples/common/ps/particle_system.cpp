/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>

#include "particle_system.h"
#include "../bgfx_utils.h"
#include "../packrect.h"

#include <bx/easing.h>
#include <bx/handlealloc.h>

#include "vs_particle.bin.h"
#include "fs_particle.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_particle),
	BGFX_EMBEDDED_SHADER(fs_particle),

	BGFX_EMBEDDED_SHADER_END()
};

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
	float m_u;
	float m_v;
	float m_blend;
	float m_angle;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorTexCoord0Vertex::ms_layout;

void EmitterUniforms::reset()
{
	m_position[0] = 0.0f;
	m_position[1] = 0.0f;
	m_position[2] = 0.0f;

	m_angle[0] = 0.0f;
	m_angle[1] = 0.0f;
	m_angle[2] = 0.0f;

	m_particlesPerSecond = 0;

	m_offsetStart[0] = 0.0f;
	m_offsetStart[1] = 1.0f;
	m_offsetEnd[0]   = 2.0f;
	m_offsetEnd[1]   = 3.0f;

	m_rgba[0] = 0x00ffffff;
	m_rgba[1] = UINT32_MAX;
	m_rgba[2] = UINT32_MAX;
	m_rgba[3] = UINT32_MAX;
	m_rgba[4] = 0x00ffffff;

	m_blendStart[0] = 0.8f;
	m_blendStart[1] = 1.0f;
	m_blendEnd[0]   = 0.0f;
	m_blendEnd[1]   = 0.2f;

	m_scaleStart[0] = 0.1f;
	m_scaleStart[1] = 0.2f;
	m_scaleEnd[0]   = 0.3f;
	m_scaleEnd[1]   = 0.4f;

	m_lifeSpan[0]   = 1.0f;
	m_lifeSpan[1]   = 2.0f;

	m_gravityScale  = 0.0f;

	m_easePos   = bx::Easing::Linear;
	m_easeRgba  = bx::Easing::Linear;
	m_easeBlend = bx::Easing::Linear;
	m_easeScale = bx::Easing::Linear;
}

namespace ps
{
	struct Particle
	{
		bx::Vec3 start;
		bx::Vec3 end[2];
		float blendStart;
		float blendEnd;
		float scaleStart;
		float scaleEnd;

		uint32_t rgba[5];

		float life;
		float lifeSpan;
	};

	struct ParticleSort
	{
		float    dist;
		uint32_t idx;
	};

	inline uint32_t toAbgr(const float* _rgba)
	{
		return 0
			| (uint8_t(_rgba[0]*255.0f)<< 0)
			| (uint8_t(_rgba[1]*255.0f)<< 8)
			| (uint8_t(_rgba[2]*255.0f)<<16)
			| (uint8_t(_rgba[3]*255.0f)<<24)
			;
	}

	inline uint32_t toAbgr(float _rr, float _gg, float _bb, float _aa)
	{
		return 0
			| (uint8_t(_rr*255.0f)<< 0)
			| (uint8_t(_gg*255.0f)<< 8)
			| (uint8_t(_bb*255.0f)<<16)
			| (uint8_t(_aa*255.0f)<<24)
			;
	}

#define SPRITE_TEXTURE_SIZE 1024
	template<uint16_t MaxHandlesT = 256, uint16_t TextureSizeT = 1024>
	struct SpriteT
	{
		SpriteT()
			: m_ra(TextureSizeT, TextureSizeT)
		{
		}

		EmitterSpriteHandle create(uint16_t _width, uint16_t _height)
		{
			EmitterSpriteHandle handle = { bx::kInvalidHandle };

			if (m_handleAlloc.getNumHandles() < m_handleAlloc.getMaxHandles() )
			{
				Pack2D pack;
				if (m_ra.find(_width, _height, pack) )
				{
					handle.idx = m_handleAlloc.alloc();
					m_pack[handle.idx] = pack;
				}
			}

			return handle;
		}

		void destroy(EmitterSpriteHandle _sprite)
		{
			const Pack2D& pack = m_pack[_sprite.idx];
			m_ra.clear(pack);
			m_handleAlloc.free(_sprite.idx);
		}

		const Pack2D& get(EmitterSpriteHandle _sprite) const
		{
			return m_pack[_sprite.idx];
		}

		bx::HandleAllocT<MaxHandlesT> m_handleAlloc;
		Pack2D                        m_pack[MaxHandlesT];
		RectPack2DT<256>              m_ra;
	};

	struct Emitter
	{
		void create(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles);
		void destroy();

		void reset()
		{
			m_dt = 0.0f;
			m_uniforms.reset();
			m_num = 0;
			bx::memSet(&m_aabb, 0, sizeof(bx::Aabb) );

			m_rng.reset();
		}

		void update(float _dt)
		{
			uint32_t num = m_num;
			for (uint32_t ii = 0; ii < num; ++ii)
			{
				Particle& particle = m_particles[ii];
				particle.life += _dt * 1.0f/particle.lifeSpan;

				if (particle.life > 1.0f)
				{
					if (ii != num-1)
					{
						bx::memCopy(&particle, &m_particles[num-1], sizeof(Particle) );
						--ii;
					}

					--num;
				}
			}

			m_num = num;

			if (0 < m_uniforms.m_particlesPerSecond)
			{
				spawn(_dt);
			}
		}

		void spawn(float _dt)
		{
			float mtx[16];
			bx::mtxSRT(mtx
				, 1.0f, 1.0f, 1.0f
				, m_uniforms.m_angle[0],    m_uniforms.m_angle[1],    m_uniforms.m_angle[2]
				, m_uniforms.m_position[0], m_uniforms.m_position[1], m_uniforms.m_position[2]
				);

			const float timePerParticle = 1.0f/m_uniforms.m_particlesPerSecond;
			m_dt += _dt;
			const uint32_t numParticles = uint32_t(m_dt / timePerParticle);
			m_dt -= numParticles * timePerParticle;

			constexpr bx::Vec3 up = { 0.0f, 1.0f, 0.0f };

			float time = 0.0f;
			for (uint32_t ii = 0
				; ii < numParticles && m_num < m_max
				; ++ii
				)
			{
				Particle& particle = m_particles[m_num];
				m_num++;

				bx::Vec3 pos(bx::init::None);
				switch (m_shape)
				{
					default:
					case EmitterShape::Sphere:
						pos = bx::randUnitSphere(&m_rng);
						break;

					case EmitterShape::Hemisphere:
						pos = bx::randUnitHemisphere(&m_rng, up);
						break;

					case EmitterShape::Circle:
						pos = bx::randUnitCircle(&m_rng);
						break;

					case EmitterShape::Disc:
						{
							const bx::Vec3 tmp = bx::randUnitCircle(&m_rng);
							pos = bx::mul(tmp, bx::frnd(&m_rng) );
						}
						break;

					case EmitterShape::Rect:
						pos =
						{
							bx::frndh(&m_rng),
							0.0f,
							bx::frndh(&m_rng),
						};
						break;
				}

				bx::Vec3 dir(bx::init::None);
				switch (m_direction)
				{
					default:
					case EmitterDirection::Up:
						dir = up;
						break;

					case EmitterDirection::Outward:
						dir = bx::normalize(pos);
						break;
				}

				const float startOffset = bx::lerp(m_uniforms.m_offsetStart[0], m_uniforms.m_offsetStart[1], bx::frnd(&m_rng) );
				const bx::Vec3 start = bx::mul(pos, startOffset);

				const float endOffset = bx::lerp(m_uniforms.m_offsetEnd[0], m_uniforms.m_offsetEnd[1], bx::frnd(&m_rng) );
				const bx::Vec3 tmp1 = bx::mul(dir, endOffset);
				const bx::Vec3 end  = bx::add(tmp1, start);

				particle.life = time;
				particle.lifeSpan = bx::lerp(m_uniforms.m_lifeSpan[0], m_uniforms.m_lifeSpan[1], bx::frnd(&m_rng) );

				const bx::Vec3 gravity = { 0.0f, -9.81f * m_uniforms.m_gravityScale * bx::square(particle.lifeSpan), 0.0f };

				particle.start  = bx::mul(start, mtx);
				particle.end[0] = bx::mul(end,   mtx);
				particle.end[1] = bx::add(particle.end[0], gravity);

				bx::memCopy(particle.rgba, m_uniforms.m_rgba, BX_COUNTOF(m_uniforms.m_rgba)*sizeof(uint32_t) );

				particle.blendStart = bx::lerp(m_uniforms.m_blendStart[0], m_uniforms.m_blendStart[1], bx::frnd(&m_rng) );
				particle.blendEnd   = bx::lerp(m_uniforms.m_blendEnd[0],   m_uniforms.m_blendEnd[1],   bx::frnd(&m_rng) );

				particle.scaleStart = bx::lerp(m_uniforms.m_scaleStart[0], m_uniforms.m_scaleStart[1], bx::frnd(&m_rng) );
				particle.scaleEnd   = bx::lerp(m_uniforms.m_scaleEnd[0],   m_uniforms.m_scaleEnd[1],   bx::frnd(&m_rng) );

				time += timePerParticle;
			}
		}

		uint32_t render(const float _uv[4], const float* _mtxView, const bx::Vec3& _eye, uint32_t _first, uint32_t _max, ParticleSort* _outSort, PosColorTexCoord0Vertex* _outVertices)
		{
			bx::EaseFn easeRgba  = bx::getEaseFunc(m_uniforms.m_easeRgba);
			bx::EaseFn easePos   = bx::getEaseFunc(m_uniforms.m_easePos);
			bx::EaseFn easeBlend = bx::getEaseFunc(m_uniforms.m_easeBlend);
			bx::EaseFn easeScale = bx::getEaseFunc(m_uniforms.m_easeScale);

			bx::Aabb aabb =
			{
				{  bx::kInfinity,  bx::kInfinity,  bx::kInfinity },
				{ -bx::kInfinity, -bx::kInfinity, -bx::kInfinity },
			};

			for (uint32_t jj = 0, num = m_num, current = _first
				; jj < num && current < _max
				; ++jj, ++current
				)
			{
				const Particle& particle = m_particles[jj];

				const float ttPos   = easePos(particle.life);
				const float ttScale = easeScale(particle.life);
				const float ttBlend = bx::clamp(easeBlend(particle.life), 0.0f, 1.0f);
				const float ttRgba  = bx::clamp(easeRgba(particle.life),  0.0f, 1.0f);

				const bx::Vec3 p0  = bx::lerp(particle.start,  particle.end[0], ttPos);
				const bx::Vec3 p1  = bx::lerp(particle.end[0], particle.end[1], ttPos);
				const bx::Vec3 pos = bx::lerp(p0, p1, ttPos);

				ParticleSort& sort = _outSort[current];
				const bx::Vec3 tmp0 = bx::sub(_eye, pos);
				sort.dist = bx::length(tmp0);
				sort.idx  = current;

				uint32_t idx = uint32_t(ttRgba*4);
				float ttmod = bx::mod(ttRgba, 0.25f)/0.25f;
				uint32_t rgbaStart = particle.rgba[idx];
				uint32_t rgbaEnd   = particle.rgba[idx+1];

				float rr = bx::lerp( ( (uint8_t*)&rgbaStart)[0], ( (uint8_t*)&rgbaEnd)[0], ttmod)/255.0f;
				float gg = bx::lerp( ( (uint8_t*)&rgbaStart)[1], ( (uint8_t*)&rgbaEnd)[1], ttmod)/255.0f;
				float bb = bx::lerp( ( (uint8_t*)&rgbaStart)[2], ( (uint8_t*)&rgbaEnd)[2], ttmod)/255.0f;
				float aa = bx::lerp( ( (uint8_t*)&rgbaStart)[3], ( (uint8_t*)&rgbaEnd)[3], ttmod)/255.0f;

				float blend = bx::lerp(particle.blendStart, particle.blendEnd, ttBlend);
				float scale = bx::lerp(particle.scaleStart, particle.scaleEnd, ttScale);

				uint32_t abgr = toAbgr(rr, gg, bb, aa);

				const bx::Vec3 udir = { _mtxView[0]*scale, _mtxView[4]*scale, _mtxView[8]*scale };
				const bx::Vec3 vdir = { _mtxView[1]*scale, _mtxView[5]*scale, _mtxView[9]*scale };

				PosColorTexCoord0Vertex* vertex = &_outVertices[current*4];

				const bx::Vec3 ul = bx::sub(bx::sub(pos, udir), vdir);
				bx::store(&vertex->m_x, ul);
				aabbExpand(aabb, ul);
				vertex->m_abgr  = abgr;
				vertex->m_u     = _uv[0];
				vertex->m_v     = _uv[1];
				vertex->m_blend = blend;
				++vertex;

				const bx::Vec3 ur = bx::sub(bx::add(pos, udir), vdir);
				bx::store(&vertex->m_x, ur);
				aabbExpand(aabb, ur);
				vertex->m_abgr  = abgr;
				vertex->m_u     = _uv[2];
				vertex->m_v     = _uv[1];
				vertex->m_blend = blend;
				++vertex;

				const bx::Vec3 br = bx::add(bx::add(pos, udir), vdir);
				bx::store(&vertex->m_x, br);
				aabbExpand(aabb, br);
				vertex->m_abgr  = abgr;
				vertex->m_u     = _uv[2];
				vertex->m_v     = _uv[3];
				vertex->m_blend = blend;
				++vertex;

				const bx::Vec3 bl = bx::add(bx::sub(pos, udir), vdir);
				bx::store(&vertex->m_x, bl);
				aabbExpand(aabb, bl);
				vertex->m_abgr  = abgr;
				vertex->m_u     = _uv[0];
				vertex->m_v     = _uv[3];
				vertex->m_blend = blend;
				++vertex;
			}

			m_aabb = aabb;

			return m_num;
		}

		EmitterShape::Enum     m_shape;
		EmitterDirection::Enum m_direction;

		float           m_dt;
		bx::RngMwc      m_rng;
		EmitterUniforms m_uniforms;

		bx::Aabb m_aabb;

		Particle* m_particles;
		uint32_t m_num;
		uint32_t m_max;
	};

	static int32_t particleSortFn(const void* _lhs, const void* _rhs)
	{
		const ParticleSort& lhs = *(const ParticleSort*)_lhs;
		const ParticleSort& rhs = *(const ParticleSort*)_rhs;
		return lhs.dist > rhs.dist ? -1 : 1;
	}

	struct ParticleSystem
	{
		void init(uint16_t _maxEmitters, bx::AllocatorI* _allocator)
		{
			m_allocator = _allocator;

			if (NULL == _allocator)
			{
				static bx::DefaultAllocator allocator;
				m_allocator = &allocator;
			}

			m_emitterAlloc = bx::createHandleAlloc(m_allocator, _maxEmitters);
			m_emitter = (Emitter*)BX_ALLOC(m_allocator, sizeof(Emitter)*_maxEmitters);

			PosColorTexCoord0Vertex::init();

			m_num = 0;

			s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
			m_texture  = bgfx::createTexture2D(
				  SPRITE_TEXTURE_SIZE
				, SPRITE_TEXTURE_SIZE
				, false
				, 1
				, bgfx::TextureFormat::BGRA8
				);

			bgfx::RendererType::Enum type = bgfx::getRendererType();
			m_particleProgram = bgfx::createProgram(
				  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_particle")
				, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_particle")
				, true
				);
		}

		void shutdown()
		{
			bgfx::destroy(m_particleProgram);
			bgfx::destroy(m_texture);
			bgfx::destroy(s_texColor);

			bx::destroyHandleAlloc(m_allocator, m_emitterAlloc);
			BX_FREE(m_allocator, m_emitter);

			m_allocator = NULL;
		}

		EmitterSpriteHandle createSprite(uint16_t _width, uint16_t _height, const void* _data)
		{
			EmitterSpriteHandle handle = m_sprite.create(_width, _height);

			if (isValid(handle) )
			{
				const Pack2D& pack = m_sprite.get(handle);
				bgfx::updateTexture2D(
						m_texture
						, 0
						, 0
						, pack.m_x
						, pack.m_y
						, pack.m_width
						, pack.m_height
						, bgfx::copy(_data, pack.m_width*pack.m_height*4)
						);
			}

			return handle;
		}

		void destroy(EmitterSpriteHandle _handle)
		{
			m_sprite.destroy(_handle);
		}

		void update(float _dt)
		{
			uint32_t numParticles = 0;
			for (uint16_t ii = 0, num = m_emitterAlloc->getNumHandles(); ii < num; ++ii)
			{
				const uint16_t idx = m_emitterAlloc->getHandleAt(ii);
				Emitter& emitter = m_emitter[idx];
				emitter.update(_dt);
				numParticles += emitter.m_num;
			}

			m_num = numParticles;
		}

		void render(uint8_t _view, const float* _mtxView, const bx::Vec3& _eye)
		{
			if (0 != m_num)
			{
				bgfx::TransientVertexBuffer tvb;
				bgfx::TransientIndexBuffer tib;

				const uint32_t numVertices = bgfx::getAvailTransientVertexBuffer(m_num*4, PosColorTexCoord0Vertex::ms_layout);
				const uint32_t numIndices  = bgfx::getAvailTransientIndexBuffer(m_num*6);
				const uint32_t max = bx::uint32_min(numVertices/4, numIndices/6);
				BX_WARN(m_num == max
					, "Truncating transient buffer for particles to maximum available (requested %d, available %d)."
					, m_num
					, max
					);

				if (0 < max)
				{
					bgfx::allocTransientBuffers(&tvb
						, PosColorTexCoord0Vertex::ms_layout
						, max*4
						, &tib
						, max*6
						);
					PosColorTexCoord0Vertex* vertices = (PosColorTexCoord0Vertex*)tvb.data;

					ParticleSort* particleSort = (ParticleSort*)BX_ALLOC(m_allocator, max*sizeof(ParticleSort) );

					uint32_t pos = 0;
					for (uint16_t ii = 0, numEmitters = m_emitterAlloc->getNumHandles(); ii < numEmitters; ++ii)
					{
						const uint16_t idx = m_emitterAlloc->getHandleAt(ii);
						Emitter& emitter = m_emitter[idx];

						const Pack2D& pack = m_sprite.get(emitter.m_uniforms.m_handle);
						const float invTextureSize = 1.0f/SPRITE_TEXTURE_SIZE;
						const float uv[4] =
						{
							 pack.m_x                  * invTextureSize,
							 pack.m_y                  * invTextureSize,
							(pack.m_x + pack.m_width ) * invTextureSize,
							(pack.m_y + pack.m_height) * invTextureSize,
						};

						pos += emitter.render(uv, _mtxView, _eye, pos, max, particleSort, vertices);
					}

					qsort(particleSort
						, max
						, sizeof(ParticleSort)
						, particleSortFn
						);

					uint16_t* indices = (uint16_t*)tib.data;
					for (uint32_t ii = 0; ii < max; ++ii)
					{
						const ParticleSort& sort = particleSort[ii];
						uint16_t* index = &indices[ii*6];
						uint16_t idx = (uint16_t)sort.idx;
						index[0] = idx*4+0;
						index[1] = idx*4+1;
						index[2] = idx*4+2;
						index[3] = idx*4+2;
						index[4] = idx*4+3;
						index[5] = idx*4+0;
					}

					BX_FREE(m_allocator, particleSort);

					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_DEPTH_TEST_LESS
						| BGFX_STATE_CULL_CW
						| BGFX_STATE_BLEND_NORMAL
						);
					bgfx::setVertexBuffer(0, &tvb);
					bgfx::setIndexBuffer(&tib);
					bgfx::setTexture(0, s_texColor, m_texture);
					bgfx::submit(_view, m_particleProgram);
				}
			}
		}

		EmitterHandle createEmitter(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles)
		{
			EmitterHandle handle = { m_emitterAlloc->alloc() };

			if (UINT16_MAX != handle.idx)
			{
				m_emitter[handle.idx].create(_shape, _direction, _maxParticles);
			}

			return handle;
		}

		void updateEmitter(EmitterHandle _handle, const EmitterUniforms* _uniforms)
		{
			BX_ASSERT(isValid(_handle)
				, "destroyEmitter handle %d is not valid."
				, _handle.idx
				);

			Emitter& emitter = m_emitter[_handle.idx];

			if (NULL == _uniforms)
			{
				emitter.reset();
			}
			else
			{
				bx::memCopy(&emitter.m_uniforms, _uniforms, sizeof(EmitterUniforms) );
			}
		}

		void getAabb(EmitterHandle _handle, bx::Aabb& _outAabb)
		{
			BX_ASSERT(isValid(_handle)
				, "getAabb handle %d is not valid."
				, _handle.idx
				);
			_outAabb = m_emitter[_handle.idx].m_aabb;
		}

		void destroyEmitter(EmitterHandle _handle)
		{
			BX_ASSERT(isValid(_handle)
				, "destroyEmitter handle %d is not valid."
				, _handle.idx
				);

			m_emitter[_handle.idx].destroy();
			m_emitterAlloc->free(_handle.idx);
		}

		bx::AllocatorI* m_allocator;

		bx::HandleAlloc* m_emitterAlloc;
		Emitter* m_emitter;

		typedef SpriteT<256, SPRITE_TEXTURE_SIZE> Sprite;
		Sprite m_sprite;

		bgfx::UniformHandle s_texColor;
		bgfx::TextureHandle m_texture;
		bgfx::ProgramHandle m_particleProgram;

		uint32_t m_num;
	};

	static ParticleSystem s_ctx;

	void Emitter::create(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles)
	{
		reset();

		m_shape     = _shape;
		m_direction = _direction;
		m_max       = _maxParticles;
		m_particles = (Particle*)BX_ALLOC(s_ctx.m_allocator, m_max*sizeof(Particle) );
	}

	void Emitter::destroy()
	{
		BX_FREE(s_ctx.m_allocator, m_particles);
		m_particles = NULL;
	}

} // namespace ps

using namespace ps;

void psInit(uint16_t _maxEmitters, bx::AllocatorI* _allocator)
{
	s_ctx.init(_maxEmitters, _allocator);
}

void psShutdown()
{
	s_ctx.shutdown();
}

EmitterSpriteHandle psCreateSprite(uint16_t _width, uint16_t _height, const void* _data)
{
	return s_ctx.createSprite(_width, _height, _data);
}

void psDestroy(EmitterSpriteHandle _handle)
{
	s_ctx.destroy(_handle);
}

EmitterHandle psCreateEmitter(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles)
{
	return s_ctx.createEmitter(_shape, _direction, _maxParticles);
}

void psUpdateEmitter(EmitterHandle _handle, const EmitterUniforms* _uniforms)
{
	s_ctx.updateEmitter(_handle, _uniforms);
}

void psGetAabb(EmitterHandle _handle, bx::Aabb& _outAabb)
{
	s_ctx.getAabb(_handle, _outAabb);
}

void psDestroyEmitter(EmitterHandle _handle)
{
	s_ctx.destroyEmitter(_handle);
}

void psUpdate(float _dt)
{
	s_ctx.update(_dt);
}

void psRender(uint8_t _view, const float* _mtxView, const bx::Vec3& _eye)
{
	s_ctx.render(_view, _mtxView, _eye);
}
