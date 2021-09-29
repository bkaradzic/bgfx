/*
* Copyright 2021 Richard Schubert. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
* 
* AMD FidelityFX Super Resolution 1.0 (FSR)
* Based on https://github.com/GPUOpen-Effects/FidelityFX-FSR/blob/master/sample/
*/

#ifndef __FSR_H__
#define __FSR_H__

#include <common.h>
#include <bgfx_utils.h>

class Fsr
{
	struct State
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

			bgfx::UniformHandle u_params{ BGFX_INVALID_HANDLE };
		};

		uint32_t m_width{ 0 };
		uint32_t m_height{ 0 };

		// Resource handles
		bgfx::ProgramHandle m_bilinear16Program{ BGFX_INVALID_HANDLE };
		bgfx::ProgramHandle m_bilinear32Program{ BGFX_INVALID_HANDLE };
		bgfx::ProgramHandle m_easu16Program{ BGFX_INVALID_HANDLE };
		bgfx::ProgramHandle m_easu32Program{ BGFX_INVALID_HANDLE };
		bgfx::ProgramHandle m_rcas16Program{ BGFX_INVALID_HANDLE };
		bgfx::ProgramHandle m_rcas32Program{ BGFX_INVALID_HANDLE };

		// Shader uniforms
		Uniforms m_uniforms;

		// Uniforms to indentify texture samplers
		bgfx::UniformHandle s_inputTexture{ BGFX_INVALID_HANDLE };

		bgfx::TextureHandle m_easuTexture16F{ BGFX_INVALID_HANDLE };
		bgfx::TextureHandle m_rcasTexture16F{ BGFX_INVALID_HANDLE };
		bgfx::TextureHandle m_easuTexture32F{ BGFX_INVALID_HANDLE };
		bgfx::TextureHandle m_rcasTexture32F{ BGFX_INVALID_HANDLE };
	};

public:

	struct Config
	{
		bool m_applyFsr{ true };
		bool m_applyFsrRcas{ true };
		float m_superSamplingFactor{ 2.0f };
		float m_rcasAttenuation{ 0.2f };
		bool m_fsr16Bit{ false };
	};

	Config m_config;

	Fsr() {}

	void init(uint32_t _width, uint32_t _height);
	void destroy();
	void resize(uint32_t _width, uint32_t _height);

	bgfx::ViewId computeFsr(bgfx::ViewId _pass, bgfx::TextureHandle _colorTexture);
	bgfx::TextureHandle getResultTexture() const;

private:
	void updateUniforms();

	State m_state;
};

#endif // __FSR_H__
