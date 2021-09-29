/*
* Copyright 2021 Richard Schubert. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
* 
* AMD FidelityFX Super Resolution 1.0 (FSR)
* Based on https://github.com/GPUOpen-Effects/FidelityFX-FSR/blob/master/sample/
*/

#include "fsr.h"

void Fsr::init(uint32_t _width, uint32_t _height)
{
	resize(_width, _height);

	// Create uniforms for screen passes and models
	m_state.m_uniforms.init();

	// Create texture sampler uniforms (used when we bind textures)
	m_state.s_inputTexture = bgfx::createUniform("InputTexture", bgfx::UniformType::Sampler);

	// Create program from shaders.
	m_state.m_bilinear16Program = bgfx::createProgram(loadShader("cs_fsr_bilinear_16"), true);
	m_state.m_bilinear32Program = bgfx::createProgram(loadShader("cs_fsr_bilinear_32"), true);
	m_state.m_easu16Program = bgfx::createProgram(loadShader("cs_fsr_easu_16"), true);
	m_state.m_easu32Program = bgfx::createProgram(loadShader("cs_fsr_easu_32"), true);
	m_state.m_rcas16Program = bgfx::createProgram(loadShader("cs_fsr_rcas_16"), true);
	m_state.m_rcas32Program = bgfx::createProgram(loadShader("cs_fsr_rcas_32"), true);
}

void Fsr::destroy()
{
	bgfx::destroy(m_state.m_bilinear16Program);
	bgfx::destroy(m_state.m_bilinear32Program);
	bgfx::destroy(m_state.m_easu16Program);
	bgfx::destroy(m_state.m_easu32Program);
	bgfx::destroy(m_state.m_rcas16Program);
	bgfx::destroy(m_state.m_rcas32Program);

	m_state.m_uniforms.destroy();

	bgfx::destroy(m_state.s_inputTexture);

	bgfx::destroy(m_state.m_easuTexture16F);
	bgfx::destroy(m_state.m_rcasTexture16F);
	bgfx::destroy(m_state.m_easuTexture32F);
	bgfx::destroy(m_state.m_rcasTexture32F);
}

void Fsr::resize(uint32_t _width, uint32_t _height)
{
	m_state.m_width = _width;
	m_state.m_height = _height;

	if(m_state.m_easuTexture16F.idx != bgfx::kInvalidHandle)
	{
		bgfx::destroy(m_state.m_easuTexture16F);
		bgfx::destroy(m_state.m_rcasTexture16F);
		bgfx::destroy(m_state.m_easuTexture32F);
		bgfx::destroy(m_state.m_rcasTexture32F);
	}

	m_state.m_easuTexture16F = bgfx::createTexture2D(uint16_t(m_state.m_width), uint16_t(m_state.m_height), false, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
	m_state.m_rcasTexture16F = bgfx::createTexture2D(uint16_t(m_state.m_width), uint16_t(m_state.m_height), false, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
	m_state.m_easuTexture32F = bgfx::createTexture2D(uint16_t(m_state.m_width), uint16_t(m_state.m_height), false, 1, bgfx::TextureFormat::RGBA32F, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
	m_state.m_rcasTexture32F = bgfx::createTexture2D(uint16_t(m_state.m_width), uint16_t(m_state.m_height), false, 1, bgfx::TextureFormat::RGBA32F, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
}

bgfx::ViewId Fsr::computeFsr(bgfx::ViewId _pass, bgfx::TextureHandle _colorTexture)
{
	updateUniforms();

	bgfx::ViewId view = _pass;

	// This value is the image region dimension that each thread group of the FSR shader operates on
	static constexpr int threadGroupWorkRegionDim = 16;
	int const dispatchX = (m_state.m_width + (threadGroupWorkRegionDim - 1)) / threadGroupWorkRegionDim;
	int const dispatchY = (m_state.m_height + (threadGroupWorkRegionDim - 1)) / threadGroupWorkRegionDim;
	bgfx::TextureFormat::Enum const format = m_config.m_fsr16Bit ? bgfx::TextureFormat::RGBA16F : bgfx::TextureFormat::RGBA32F;
	bgfx::TextureHandle fsrEasuTexture = m_config.m_fsr16Bit ? m_state.m_easuTexture16F : m_state.m_easuTexture32F;

	// EASU pass (upscale)
	{
		bgfx::ProgramHandle program = m_config.m_fsr16Bit ? m_state.m_easu16Program : m_state.m_easu32Program;

		if (!m_config.m_applyFsr)
		{
			program = m_state.m_bilinear32Program;
		}

		bgfx::setViewName(view, "fsr easu");
		m_state.m_uniforms.submit();
		bgfx::setTexture(0, m_state.s_inputTexture, _colorTexture);
		bgfx::setImage(1, fsrEasuTexture, 0, bgfx::Access::Write, format);
		bgfx::dispatch(view, program, dispatchX, dispatchY, 1);
		++view;
	}

	// RCAS pass (sharpening)
	if (m_config.m_applyFsrRcas)
	{
		bgfx::ProgramHandle program = m_config.m_fsr16Bit ? m_state.m_rcas16Program : m_state.m_rcas32Program;

		bgfx::setViewName(view, "fsr rcas");
		m_state.m_uniforms.submit();
		bgfx::setTexture(0, m_state.s_inputTexture, fsrEasuTexture);
		bgfx::setImage(1, m_config.m_fsr16Bit ? m_state.m_rcasTexture16F : m_state.m_rcasTexture32F, 0, bgfx::Access::Write, format);
		bgfx::dispatch(view, program, dispatchX, dispatchY, 1);
		++view;
	}

	return view;
}

bgfx::TextureHandle Fsr::getResultTexture() const
{
	if (m_config.m_applyFsr && m_config.m_applyFsrRcas)
	{
		return m_config.m_fsr16Bit ? m_state.m_rcasTexture16F : m_state.m_rcasTexture32F;
	}
	else
	{
		return m_config.m_fsr16Bit ? m_state.m_easuTexture16F : m_state.m_easuTexture32F;
	}
}

void Fsr::updateUniforms()
{
	float const srcWidth = static_cast<float>(m_state.m_width) / m_config.m_superSamplingFactor;
	float const srcHeight = static_cast<float>(m_state.m_height) / m_config.m_superSamplingFactor;

	m_state.m_uniforms.ViewportSizeRcasAttenuation.x = srcWidth;
	m_state.m_uniforms.ViewportSizeRcasAttenuation.y = srcHeight;
	m_state.m_uniforms.ViewportSizeRcasAttenuation.z = m_config.m_rcasAttenuation;
	m_state.m_uniforms.SrcSize.x = static_cast<float>(m_state.m_width);
	m_state.m_uniforms.SrcSize.y = static_cast<float>(m_state.m_height);
	m_state.m_uniforms.DstSize.x = static_cast<float>(m_state.m_width);
	m_state.m_uniforms.DstSize.y = static_cast<float>(m_state.m_height);
}
