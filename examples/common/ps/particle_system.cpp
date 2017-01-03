/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>

#include "particle_system.h"
#include "../bgfx_utils.h"

#include <bx/easing.h>
#include <bx/crtimpl.h>
#include <bx/handlealloc.h>

#include "vs_particle.bin.h"
#include "fs_particle.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_particle),
	BGFX_EMBEDDED_SHADER(fs_particle),

	BGFX_EMBEDDED_SHADER_END()
};

static const bx::EaseFn s_easeFunc[] =
{
	bx::easeLinear,
	bx::easeInQuad,
	bx::easeOutQuad,
	bx::easeInOutQuad,
	bx::easeOutInQuad,
	bx::easeInCubic,
	bx::easeOutCubic,
	bx::easeInOutCubic,
	bx::easeOutInCubic,
	bx::easeInQuart,
	bx::easeOutQuart,
	bx::easeInOutQuart,
	bx::easeOutInQuart,
	bx::easeInQuint,
	bx::easeOutQuint,
	bx::easeInOutQuint,
	bx::easeOutInQuint,
	bx::easeInSine,
	bx::easeOutSine,
	bx::easeInOutSine,
	bx::easeOutInSine,
	bx::easeInExpo,
	bx::easeOutExpo,
	bx::easeInOutExpo,
	bx::easeOutInExpo,
	bx::easeInCirc,
	bx::easeOutCirc,
	bx::easeInOutCirc,
	bx::easeOutInCirc,
	bx::easeInElastic,
	bx::easeOutElastic,
	bx::easeInOutElastic,
	bx::easeOutInElastic,
	bx::easeInBack,
	bx::easeOutBack,
	bx::easeInOutBack,
	bx::easeOutInBack,
	bx::easeInBounce,
	bx::easeOutBounce,
	bx::easeInOutBounce,
	bx::easeOutInBounce,
};
BX_STATIC_ASSERT(BX_COUNTOF(s_easeFunc) == bx::Easing::Count);

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
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;

struct Particle
{
	float start[3];
	float end[2][3];
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

struct Emitter
{
	void create(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles);
	void destroy();

	void reset()
	{
		m_num = 0;
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
					memcpy(&particle, &m_particles[num-1], sizeof(Particle) );
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

		float time = 0.0f;
		for (uint32_t ii = 0
			; ii < numParticles && m_num < m_max
			; ++ii
			)
		{
			Particle& particle = m_particles[m_num];
			m_num++;

			const float up[3] = { 0.0f, 1.0f, 0.0f };

			float pos[3];
			switch (m_shape)
			{
				default:
				case EmitterShape::Sphere:
					bx::randUnitSphere(pos, &m_rng);
					break;

				case EmitterShape::Hemisphere:
					bx::randUnitHemisphere(pos, &m_rng, up);
					break;

				case EmitterShape::Circle:
					bx::randUnitCircle(pos, &m_rng);
					break;

				case EmitterShape::Disc:
					{
						float tmp[3];
						bx::randUnitCircle(tmp, &m_rng);
						bx::vec3Mul(pos, tmp, bx::frnd(&m_rng) );
					}
					break;

				case EmitterShape::Rect:
					pos[0] = bx::frndh(&m_rng);
					pos[1] = 0.0f;
					pos[2] = bx::frndh(&m_rng);
					break;
			}

			float dir[3];
			switch (m_direction)
			{
				default:
				case EmitterDirection::Up:
					bx::vec3Move(dir, up);
					break;

				case EmitterDirection::Outward:
					bx::vec3Norm(dir, pos);
					break;
			}

			float start[3];
			float end[3];
			const float startOffset = bx::flerp(m_uniforms.m_offsetStart[0], m_uniforms.m_offsetStart[1], bx::frnd(&m_rng) );
			bx::vec3Mul(start, pos, startOffset);

			const float endOffset = bx::flerp(m_uniforms.m_offsetEnd[0], m_uniforms.m_offsetEnd[1], bx::frnd(&m_rng) );
			float tmp1[3];
			bx::vec3Mul(tmp1, dir, endOffset);
			bx::vec3Add(end, tmp1, start);

			particle.life = time;
			particle.lifeSpan = bx::flerp(m_uniforms.m_lifeSpan[0], m_uniforms.m_lifeSpan[1], bx::frnd(&m_rng) );

			float gravity[3] = { 0.0f, -9.81f * m_uniforms.m_gravityScale * bx::fsq(particle.lifeSpan), 0.0f };

			bx::vec3MulMtx(particle.start,  start, mtx);
			bx::vec3MulMtx(particle.end[0], end,   mtx);
			bx::vec3Add(particle.end[1], particle.end[0], gravity);

			memcpy(particle.rgba, m_uniforms.m_rgba, BX_COUNTOF(m_uniforms.m_rgba)*sizeof(uint32_t) );

			particle.blendStart = bx::flerp(m_uniforms.m_blendStart[0], m_uniforms.m_blendStart[1], bx::frnd(&m_rng) );
			particle.blendStart = bx::flerp(m_uniforms.m_blendEnd[0],   m_uniforms.m_blendEnd[1],   bx::frnd(&m_rng) );

			particle.scaleStart = bx::flerp(m_uniforms.m_scaleStart[0], m_uniforms.m_scaleStart[1], bx::frnd(&m_rng) );
			particle.scaleEnd   = bx::flerp(m_uniforms.m_scaleEnd[0],   m_uniforms.m_scaleEnd[1],   bx::frnd(&m_rng) );

			time += timePerParticle;
		}
	}

	uint32_t render(const float* _mtxView, const float* _eye, uint32_t _first, ParticleSort* _outSort, PosColorTexCoord0Vertex* _outVertices) const
	{
		bx::EaseFn easeRgba  = s_easeFunc[m_uniforms.m_easeRgba];
		bx::EaseFn easePos   = s_easeFunc[m_uniforms.m_easePos];
		bx::EaseFn easeBlend = s_easeFunc[m_uniforms.m_easeBlend];
		bx::EaseFn easeScale = s_easeFunc[m_uniforms.m_easeScale];

		for (uint32_t jj = 0, num = m_num; jj < num; ++jj)
		{
			const Particle& particle = m_particles[jj];

			const float ttPos   = easePos(particle.life);
			const float ttScale = easeScale(particle.life);
			const float ttBlend = bx::fsaturate(easeBlend(particle.life) );
			const float ttRgba  = bx::fsaturate(easeRgba(particle.life) );

			float p0[3];
			bx::vec3Lerp(p0, particle.start, particle.end[0], ttPos);

			float p1[3];
			bx::vec3Lerp(p1, particle.end[0], particle.end[1], ttPos);

			float pos[3];
			bx::vec3Lerp(pos, p0, p1, ttPos);

			const uint32_t current = _first + jj;
			ParticleSort& sort = _outSort[current];
			float tmp[3];
			bx::vec3Sub(tmp, _eye, pos);
			sort.dist = bx::fsqrt(bx::vec3Dot(tmp, tmp) );
			sort.idx  = current;

			uint32_t idx = uint32_t(ttRgba*4);
			float ttmod = bx::fmod(ttRgba, 0.25f)/0.25f;
			uint32_t rgbaStart = particle.rgba[idx];
			uint32_t rgbaEnd   = particle.rgba[idx+1];

			float rr = bx::flerp( ( (uint8_t*)&rgbaStart)[0], ( (uint8_t*)&rgbaEnd)[0], ttmod)/255.0f;
			float gg = bx::flerp( ( (uint8_t*)&rgbaStart)[1], ( (uint8_t*)&rgbaEnd)[1], ttmod)/255.0f;
			float bb = bx::flerp( ( (uint8_t*)&rgbaStart)[2], ( (uint8_t*)&rgbaEnd)[2], ttmod)/255.0f;
			float aa = bx::flerp( ( (uint8_t*)&rgbaStart)[3], ( (uint8_t*)&rgbaEnd)[3], ttmod)/255.0f;

			float blend = bx::flerp(particle.blendStart, particle.blendEnd, ttBlend);
			float scale = bx::flerp(particle.scaleStart, particle.scaleEnd, ttScale);

			uint32_t abgr = toAbgr(rr, gg, bb, aa);

			float udir[3] = { _mtxView[0]*scale, _mtxView[4]*scale, _mtxView[8]*scale };
			float vdir[3] = { _mtxView[1]*scale, _mtxView[5]*scale, _mtxView[9]*scale };

			PosColorTexCoord0Vertex* vertex = &_outVertices[current*4];
			bx::vec3Sub(tmp, pos, udir);
			bx::vec3Sub(&vertex->m_x, tmp, vdir);
			vertex->m_abgr  = abgr;
			vertex->m_u     = 0.0f;
			vertex->m_v     = 0.0f;
			vertex->m_blend = blend;
			++vertex;

			bx::vec3Add(tmp, pos, udir);
			bx::vec3Sub(&vertex->m_x, tmp, vdir);
			vertex->m_abgr  = abgr;
			vertex->m_u     = 1.0f;
			vertex->m_v     = 0.0f;
			vertex->m_blend = blend;
			++vertex;

			bx::vec3Add(tmp, pos, udir);
			bx::vec3Add(&vertex->m_x, tmp, vdir);
			vertex->m_abgr  = abgr;
			vertex->m_u     = 1.0f;
			vertex->m_v     = 1.0f;
			vertex->m_blend = blend;
			++vertex;

			bx::vec3Sub(tmp, pos, udir);
			bx::vec3Add(&vertex->m_x, tmp, vdir);
			vertex->m_abgr  = abgr;
			vertex->m_u     = 0.0f;
			vertex->m_v     = 1.0f;
			vertex->m_blend = blend;
			++vertex;
		}

		return m_num;
	}

	EmitterShape::Enum     m_shape;
	EmitterDirection::Enum m_direction;

	float           m_dt;
	bx::RngMwc      m_rng;
	EmitterUniforms m_uniforms;

	Particle* m_particles;
	uint32_t m_num;
	uint32_t m_max;
};

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

static int32_t particleSortFn(const void* _lhs, const void* _rhs)
{
	const ParticleSort& lhs = *(const ParticleSort*)_lhs;
	const ParticleSort& rhs = *(const ParticleSort*)_rhs;
	return lhs.dist > rhs.dist ? -1 : 1;
}

struct ParticleSystem
{
	void init(bx::AllocatorI* _allocator)
	{
		m_allocator = _allocator;

#if BX_CONFIG_ALLOCATOR_CRT
		if (NULL == _allocator)
		{
			static bx::CrtAllocator allocator;
			m_allocator = &allocator;
		}
#endif // BX_CONFIG_ALLOCATOR_CRT

		PosColorTexCoord0Vertex::init();

		m_num = 0;

		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
		m_particleTexture = loadTexture("textures/particle.ktx");

		bgfx::RendererType::Enum type = bgfx::getRendererType();
		m_particleProgram = bgfx::createProgram(
			  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_particle")
			, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_particle")
			, true
			);
	}

	void shutdown()
	{
		bgfx::destroyProgram(m_particleProgram);
		bgfx::destroyTexture(m_particleTexture);
		bgfx::destroyUniform(s_texColor);

		m_allocator = NULL;
	}

	void update(float _dt)
	{
		uint32_t numParticles = 0;
		for (uint16_t ii = 0, num = m_emitterAlloc.getNumHandles(); ii < num; ++ii)
		{
			const uint16_t idx = m_emitterAlloc.getHandleAt(ii);
			Emitter& emitter = m_emitter[idx];
			emitter.update(_dt);
			numParticles += emitter.m_num;
		}

		m_num = numParticles;
	}

	void render(uint8_t _view, const float* _mtxView, const float* _eye)
	{
		if (0 != m_num)
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::TransientIndexBuffer tib;
			bgfx::allocTransientBuffers(&tvb
					, PosColorTexCoord0Vertex::ms_decl
					, m_num*4
					, &tib
					, m_num*6
					);
			PosColorTexCoord0Vertex* vertices = (PosColorTexCoord0Vertex*)tvb.data;

			ParticleSort* particleSort = (ParticleSort*)BX_ALLOC(m_allocator, m_num*sizeof(ParticleSort) );

			uint32_t pos = 0;
			for (uint16_t ii = 0, num = m_emitterAlloc.getNumHandles(); ii < num; ++ii)
			{
				const uint16_t idx = m_emitterAlloc.getHandleAt(ii);
				const Emitter& emitter = m_emitter[idx];
				pos += emitter.render(_mtxView, _eye, pos, particleSort, vertices);
			}

			qsort(particleSort
				, m_num
				, sizeof(ParticleSort)
				, particleSortFn
				);

			uint16_t* indices = (uint16_t*)tib.data;
			for (uint32_t ii = 0; ii < m_num; ++ii)
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
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CW
				| BGFX_STATE_BLEND_NORMAL
				);
			bgfx::setVertexBuffer(&tvb);
			bgfx::setIndexBuffer(&tib);
			bgfx::setTexture(0, s_texColor, m_particleTexture);
			bgfx::submit(_view, m_particleProgram);
		}
	}

	EmitterHandle createEmitter(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles)
	{
		EmitterHandle handle = { m_emitterAlloc.alloc() };

		if (UINT16_MAX != handle.idx)
		{
			m_emitter[handle.idx].create(_shape, _direction, _maxParticles);
		}

		return handle;
	}

	void updateEmitter(EmitterHandle _handle, const EmitterUniforms* _uniforms)
	{
		Emitter& emitter = m_emitter[_handle.idx];

		if (NULL == _uniforms)
		{
			emitter.reset();
		}
		else
		{
			memcpy(&emitter.m_uniforms, _uniforms, sizeof(EmitterUniforms) );
		}
	}

	void destroyEmitter(EmitterHandle _handle)
	{
		m_emitter[_handle.idx].destroy();
		m_emitterAlloc.free(_handle.idx);
	}

	bx::AllocatorI* m_allocator;

#define MAX_EMITTERS 64
	bx::HandleAllocT<MAX_EMITTERS> m_emitterAlloc;
	Emitter m_emitter[MAX_EMITTERS];

	bgfx::UniformHandle s_texColor;
	bgfx::TextureHandle m_particleTexture;
	bgfx::ProgramHandle m_particleProgram;

	uint32_t m_num;
};

static ParticleSystem s_ps;

void Emitter::create(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles)
{
	m_dt = 0.0f;
	m_uniforms.reset();
	m_shape     = _shape;
	m_direction = _direction;

	m_num = 0;
	m_max = _maxParticles;
	m_particles = (Particle*)BX_ALLOC(s_ps.m_allocator, m_max*sizeof(Particle) );
}

void Emitter::destroy()
{
	BX_FREE(s_ps.m_allocator, m_particles);
	m_particles = NULL;
}

void psInit(bx::AllocatorI* _allocator)
{
	s_ps.init(_allocator);
}

void psShutdown()
{
	s_ps.shutdown();
}

EmitterHandle psCreateEmitter(EmitterShape::Enum _shape, EmitterDirection::Enum _direction, uint32_t _maxParticles)
{
	return s_ps.createEmitter(_shape, _direction, _maxParticles);
}

void psUpdateEmitter(EmitterHandle _handle, const EmitterUniforms* _uniforms)
{
	s_ps.updateEmitter(_handle, _uniforms);
}

void psDestroyEmitter(EmitterHandle _handle)
{
	s_ps.destroyEmitter(_handle);
}

void psUpdate(float _dt)
{
	s_ps.update(_dt);
}

void psRender(uint8_t _view, const float* _mtxView, const float* _eye)
{
	s_ps.render(_view, _mtxView, _eye);
}
