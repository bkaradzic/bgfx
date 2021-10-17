/*
* Copyright 2021 Richard Schubert. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*
* AMD FidelityFX Super Resolution 1.0 (FSR)
* Based on https://github.com/GPUOpen-Effects/FidelityFX-FSR/blob/master/sample/
*/

#include "fsr.h"

#include <bgfx_utils.h>

struct FsrResources
{
	struct Uniforms
	{
		struct Vec4
		{
			float x;
			float y;
			float z;
			float w;
		};

		enum
		{
			NumVec4 = 3
		};

		void init()
		{
			u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);
		};

		void submit() const
		{
			bgfx::setUniform(u_params, m_params, NumVec4);
		}

		void destroy()
		{
			bgfx::destroy(u_params);
		}

		union
		{
			struct
			{
				Vec4 ViewportSizeRcasAttenuation;
				Vec4 SrcSize;
				Vec4 DstSize;
			};

			uint32_t m_params[NumVec4 * 4];
		};

		bgfx::UniformHandle u_params = BGFX_INVALID_HANDLE;
	};

	uint32_t m_width{ 0 };
	uint32_t m_height{ 0 };

	// Resource handles
	bgfx::ProgramHandle m_bilinear16Program = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle m_bilinear32Program = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle m_easu16Program = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle m_easu32Program = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle m_rcas16Program = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle m_rcas32Program = BGFX_INVALID_HANDLE;

	// Shader uniforms
	Uniforms m_uniforms;

	// Uniforms to indentify texture samplers
	bgfx::UniformHandle s_inputTexture = BGFX_INVALID_HANDLE;

	bgfx::TextureHandle m_easuTexture16F = BGFX_INVALID_HANDLE;
	bgfx::TextureHandle m_rcasTexture16F = BGFX_INVALID_HANDLE;
	bgfx::TextureHandle m_easuTexture32F = BGFX_INVALID_HANDLE;
	bgfx::TextureHandle m_rcasTexture32F = BGFX_INVALID_HANDLE;
};


Fsr::Fsr()
{
	m_resources = new FsrResources();
}

Fsr::~Fsr()
{
	delete m_resources;
}

void Fsr::init(uint32_t _width, uint32_t _height)
{
	resize(_width, _height);

	// Create uniforms for screen passes and models
	m_resources->m_uniforms.init();

	// Create texture sampler uniforms (used when we bind textures)
	m_resources->s_inputTexture = bgfx::createUniform("InputTexture", bgfx::UniformType::Sampler);

	// Create program from shaders.
	m_resources->m_bilinear32Program = bgfx::createProgram(loadShader("cs_fsr_bilinear_32"), true);
	m_resources->m_easu32Program     = bgfx::createProgram(loadShader("cs_fsr_easu_32"), true);
	m_resources->m_rcas32Program     = bgfx::createProgram(loadShader("cs_fsr_rcas_32"), true);

	m_support16BitPrecision = (bgfx::getRendererType() != bgfx::RendererType::OpenGL);

	if (m_support16BitPrecision)
	{
		m_resources->m_bilinear16Program = bgfx::createProgram(loadShader("cs_fsr_bilinear_16"), true);
		m_resources->m_easu16Program     = bgfx::createProgram(loadShader("cs_fsr_easu_16"), true);
		m_resources->m_rcas16Program     = bgfx::createProgram(loadShader("cs_fsr_rcas_16"), true);
	}
}

void Fsr::destroy()
{
	if (m_support16BitPrecision)
	{
		bgfx::destroy(m_resources->m_bilinear16Program);
		bgfx::destroy(m_resources->m_easu16Program);
		bgfx::destroy(m_resources->m_rcas16Program);
	}

	bgfx::destroy(m_resources->m_bilinear32Program);
	bgfx::destroy(m_resources->m_easu32Program);
	bgfx::destroy(m_resources->m_rcas32Program);

	m_resources->m_uniforms.destroy();

	bgfx::destroy(m_resources->s_inputTexture);

	if (bgfx::isValid(m_resources->m_easuTexture16F) )
	{
		bgfx::destroy(m_resources->m_easuTexture16F);
		bgfx::destroy(m_resources->m_rcasTexture16F);
	}

	if (bgfx::isValid(m_resources->m_easuTexture32F) )
	{
		bgfx::destroy(m_resources->m_easuTexture32F);
		bgfx::destroy(m_resources->m_rcasTexture32F);
	}
}

void Fsr::resize(uint32_t _width, uint32_t _height)
{
	m_resources->m_width  = _width;
	m_resources->m_height = _height;

	if (bgfx::isValid(m_resources->m_easuTexture16F) )
	{
		bgfx::destroy(m_resources->m_easuTexture16F);
		bgfx::destroy(m_resources->m_rcasTexture16F);
	}

	if (bgfx::isValid(m_resources->m_easuTexture32F) )
	{
		bgfx::destroy(m_resources->m_easuTexture32F);
		bgfx::destroy(m_resources->m_rcasTexture32F);
	}

	if (m_support16BitPrecision)
	{
		m_resources->m_easuTexture16F = bgfx::createTexture2D(
			  uint16_t(m_resources->m_width)
			, uint16_t(m_resources->m_height)
			, false
			, 1
			, bgfx::TextureFormat::RGBA16F
			, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
			);

		m_resources->m_rcasTexture16F = bgfx::createTexture2D(
			  uint16_t(m_resources->m_width)
			, uint16_t(m_resources->m_height)
			, false
			, 1
			, bgfx::TextureFormat::RGBA16F
			, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
			);
	}

	m_resources->m_easuTexture32F = bgfx::createTexture2D(
		  uint16_t(m_resources->m_width)
		, uint16_t(m_resources->m_height)
		, false
		, 1
		, bgfx::TextureFormat::RGBA32F
		, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
		);

	m_resources->m_rcasTexture32F = bgfx::createTexture2D(
		  uint16_t(m_resources->m_width)
		, uint16_t(m_resources->m_height)
		, false
		, 1
		, bgfx::TextureFormat::RGBA32F
		, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
		);
}

bgfx::ViewId Fsr::computeFsr(bgfx::ViewId _pass, bgfx::TextureHandle _colorTexture)
{
	updateUniforms();

	bgfx::ViewId view = _pass;

	// This value is the image region dimension that each thread group of the FSR shader operates on
	constexpr int threadGroupWorkRegionDim = 16;

	const int32_t dispatchX = (m_resources->m_width  + (threadGroupWorkRegionDim - 1) ) / threadGroupWorkRegionDim;
	const int32_t dispatchY = (m_resources->m_height + (threadGroupWorkRegionDim - 1) ) / threadGroupWorkRegionDim;

	bgfx::TextureFormat::Enum const format = m_config.m_fsr16Bit
		? bgfx::TextureFormat::RGBA16F
		: bgfx::TextureFormat::RGBA32F
		;

	bgfx::TextureHandle fsrEasuTexture = m_config.m_fsr16Bit
		? m_resources->m_easuTexture16F
		: m_resources->m_easuTexture32F
		;

	// EASU pass (upscale)
	{
		bgfx::ProgramHandle program = m_config.m_fsr16Bit
			? m_resources->m_easu16Program
			: m_resources->m_easu32Program
			;

		if (!m_config.m_applyFsr)
		{
			program = m_resources->m_bilinear32Program;
		}

		bgfx::setViewName(view, "fsr easu");
		m_resources->m_uniforms.submit();
		bgfx::setTexture(0, m_resources->s_inputTexture, _colorTexture);
		bgfx::setImage(1, fsrEasuTexture, 0, bgfx::Access::Write, format);
		bgfx::dispatch(view, program, dispatchX, dispatchY, 1);
		++view;
	}

	// RCAS pass (sharpening)
	if (m_config.m_applyFsrRcas)
	{
		bgfx::ProgramHandle program = m_config.m_fsr16Bit
			? m_resources->m_rcas16Program
			: m_resources->m_rcas32Program
			;

		bgfx::setViewName(view, "fsr rcas");
		m_resources->m_uniforms.submit();
		bgfx::setTexture(0, m_resources->s_inputTexture, fsrEasuTexture);
		bgfx::setImage(
			  1
			, m_config.m_fsr16Bit? m_resources->m_rcasTexture16F: m_resources->m_rcasTexture32F
			, 0
			, bgfx::Access::Write
			, format
			);
		bgfx::dispatch(view, program, dispatchX, dispatchY, 1);
		++view;
	}

	return view;
}

bgfx::TextureHandle Fsr::getResultTexture() const
{
	if (m_config.m_applyFsr && m_config.m_applyFsrRcas)
	{
		return m_config.m_fsr16Bit
			? m_resources->m_rcasTexture16F
			: m_resources->m_rcasTexture32F
			;
	}

	return m_config.m_fsr16Bit
		? m_resources->m_easuTexture16F
		: m_resources->m_easuTexture32F
		;
}

bool Fsr::supports16BitPrecision() const
{
	return m_support16BitPrecision;
}

void Fsr::updateUniforms()
{
	const float srcWidth = static_cast<float>(m_resources->m_width) / m_config.m_superSamplingFactor;
	const float srcHeight = static_cast<float>(m_resources->m_height) / m_config.m_superSamplingFactor;

	m_resources->m_uniforms.ViewportSizeRcasAttenuation.x = srcWidth;
	m_resources->m_uniforms.ViewportSizeRcasAttenuation.y = srcHeight;
	m_resources->m_uniforms.ViewportSizeRcasAttenuation.z = m_config.m_rcasAttenuation;
	m_resources->m_uniforms.SrcSize.x = static_cast<float>(m_resources->m_width);
	m_resources->m_uniforms.SrcSize.y = static_cast<float>(m_resources->m_height);
	m_resources->m_uniforms.DstSize.x = static_cast<float>(m_resources->m_width);
	m_resources->m_uniforms.DstSize.y = static_cast<float>(m_resources->m_height);
}
