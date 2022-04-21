/*
 * Copyright 2021 Richard Schubert. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 *
 * AMD FidelityFX Super Resolution 1.0 (FSR)
 * Based on https://github.com/GPUOpen-Effects/FidelityFX-FSR/blob/master/sample/
 */

#ifndef __FSR_H__
#define __FSR_H__

#include <bgfx/bgfx.h>

class Fsr
{
public:

	struct Config
	{
		float m_superSamplingFactor = 2.0f;
		float m_rcasAttenuation     = 0.2f;
		bool  m_applyFsr            = true;
		bool  m_applyFsrRcas        = true;
		bool  m_fsr16Bit            = false;
	};

	Config m_config;

	Fsr();
	~Fsr();

	void init(uint32_t _width, uint32_t _height);
	void destroy();
	void resize(uint32_t _width, uint32_t _height);

	bgfx::ViewId computeFsr(bgfx::ViewId _pass, bgfx::TextureHandle _colorTexture);
	bgfx::TextureHandle getResultTexture() const;
	bool supports16BitPrecision() const;

private:
	void updateUniforms();

	struct FsrResources *m_resources;
};

#endif // __FSR_H__
