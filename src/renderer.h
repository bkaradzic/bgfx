/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_RENDERER_H_HEADER_GUARD
#define BGFX_RENDERER_H_HEADER_GUARD

#include "bgfx_p.h"

namespace bgfx
{
	struct ViewState
	{
		ViewState() { }
		ViewState(Frame* _render, bool _hmdEnabled)
		{
			reset(_render, _hmdEnabled);
		}

		void reset(Frame* _render, bool _hmdEnabled)
		{
			m_alphaRef = 0.0f;
			m_invViewCached = UINT16_MAX;
			m_invProjCached = UINT16_MAX;
			m_invViewProjCached = UINT16_MAX;

			m_view[0] = _render->m_view;
			m_view[1] = m_viewTmp[1];

			if (_hmdEnabled)
			{
				HMD& hmd = _render->m_hmd;

				m_view[0] = m_viewTmp[0];
				Matrix4 viewAdjust;
				bx::mtxIdentity(viewAdjust.un.val);

				for (uint32_t eye = 0; eye < 2; ++eye)
				{
					const HMD::Eye& hmdEye = hmd.eye[eye];
					viewAdjust.un.val[12] = hmdEye.viewOffset[0];
					viewAdjust.un.val[13] = hmdEye.viewOffset[1];
					viewAdjust.un.val[14] = hmdEye.viewOffset[2];

					for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
					{
						if (BGFX_VIEW_STEREO == (_render->m_viewFlags[ii] & BGFX_VIEW_STEREO) )
						{
							bx::float4x4_mul(&m_view[eye][ii].un.f4x4
								, &_render->m_view[ii].un.f4x4
								, &viewAdjust.un.f4x4
								);
						}
						else
						{
							memcpy(&m_view[0][ii].un.f4x4, &_render->m_view[ii].un.f4x4, sizeof(Matrix4) );
						}
					}
				}
			}

			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				for (uint32_t eye = 0; eye < uint32_t(_hmdEnabled)+1; ++eye)
				{
					bx::float4x4_mul(&m_viewProj[eye][ii].un.f4x4
						, &m_view[eye][ii].un.f4x4
						, &_render->m_proj[eye][ii].un.f4x4
						);
				}
			}
		}

		template<uint16_t mtxRegs, typename RendererContext, typename Program, typename Draw>
		void setPredefined(RendererContext* _renderer, uint16_t view, uint8_t eye, Program& _program, Frame* _render, const Draw& _draw)
		{
			for (uint32_t ii = 0, num = _program.m_numPredefined; ii < num; ++ii)
			{
				PredefinedUniform& predefined = _program.m_predefined[ii];
				uint8_t flags = predefined.m_type&BGFX_UNIFORM_FRAGMENTBIT;
				switch (predefined.m_type&(~BGFX_UNIFORM_FRAGMENTBIT) )
				{
				case PredefinedUniform::ViewRect:
					{
						float frect[4];
						frect[0] = m_rect.m_x;
						frect[1] = m_rect.m_y;
						frect[2] = m_rect.m_width;
						frect[3] = m_rect.m_height;

						_renderer->setShaderUniform4f(flags
							, predefined.m_loc
							, &frect[0]
							, 1
							);
					}
					break;

				case PredefinedUniform::ViewTexel:
					{
						float frect[4];
						frect[0] = 1.0f/float(m_rect.m_width);
						frect[1] = 1.0f/float(m_rect.m_height);

						_renderer->setShaderUniform4f(flags
							, predefined.m_loc
							, &frect[0]
							, 1
							);
					}
					break;

				case PredefinedUniform::View:
					{
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_view[eye][view].un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvView:
					{
						uint16_t viewEye = (view << 1) | eye;
						if (viewEye != m_invViewCached)
						{
							m_invViewCached = viewEye;
							bx::float4x4_inverse(&m_invView.un.f4x4
								, &m_view[eye][view].un.f4x4
								);
						}

						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_invView.un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::Proj:
					{
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, _render->m_proj[eye][view].un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvProj:
					{
						uint16_t viewEye = (view << 1) | eye;
						if (viewEye != m_invProjCached)
						{
							m_invProjCached = viewEye;
							bx::float4x4_inverse(&m_invProj.un.f4x4
								, &_render->m_proj[eye][view].un.f4x4
								);
						}

						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_invProj.un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ViewProj:
					{
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_viewProj[eye][view].un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvViewProj:
					{
						uint16_t viewEye = (view << 1) | eye;
						if (viewEye != m_invViewProjCached)
						{
							m_invViewProjCached = viewEye;
							bx::float4x4_inverse(&m_invViewProj.un.f4x4
								, &m_viewProj[eye][view].un.f4x4
								);
						}

						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_invViewProj.un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::Model:
					{
						const Matrix4& model = _render->m_matrixCache.m_cache[_draw.m_matrix];
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, model.un.val
							, bx::uint32_min(_draw.m_num*mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ModelView:
					{
						Matrix4 modelView;
						const Matrix4& model = _render->m_matrixCache.m_cache[_draw.m_matrix];
						bx::float4x4_mul(&modelView.un.f4x4
							, &model.un.f4x4
							, &m_view[eye][view].un.f4x4
							);
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, modelView.un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ModelViewProj:
					{
						Matrix4 modelViewProj;
						const Matrix4& model = _render->m_matrixCache.m_cache[_draw.m_matrix];
						bx::float4x4_mul(&modelViewProj.un.f4x4
							, &model.un.f4x4
							, &m_viewProj[eye][view].un.f4x4
							);
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, modelViewProj.un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::AlphaRef:
					{
						_renderer->setShaderUniform4f(flags
							, predefined.m_loc
							, &m_alphaRef
							, 1
							);
					}
					break;

				default:
					BX_CHECK(false, "predefined %d not handled", predefined.m_type);
					break;
				}
			}
		}

		Matrix4  m_viewTmp[2][BGFX_CONFIG_MAX_VIEWS];
		Matrix4  m_viewProj[2][BGFX_CONFIG_MAX_VIEWS];
		Matrix4* m_view[2];
		Rect     m_rect;
		Matrix4  m_invView;
		Matrix4  m_invProj;
		Matrix4  m_invViewProj;
		float    m_alphaRef;
		uint16_t m_invViewCached;
		uint16_t m_invProjCached;
		uint16_t m_invViewProjCached;
	};

} // namespace bgfx

#endif // BGFX_RENDERER_H_HEADER_GUARD
