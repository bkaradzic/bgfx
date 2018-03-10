/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERER_H_HEADER_GUARD
#define BGFX_RENDERER_H_HEADER_GUARD

#include "bgfx_p.h"

namespace bgfx
{
	struct BlitState
	{
		BlitState(const Frame* _frame)
			: m_frame(_frame)
			, m_item(0)
		{
			m_key.decode(_frame->m_blitKeys[0]);
		}

		bool hasItem(uint16_t _view) const
		{
			return m_item < m_frame->m_numBlitItems
				&& m_key.m_view <= _view
				;
		}

		const BlitItem& advance()
		{
			const BlitItem& bi = m_frame->m_blitItem[m_key.m_item];

			++m_item;
			m_key.decode(m_frame->m_blitKeys[m_item]);

			return bi;
		}

		const Frame* m_frame;
		BlitKey  m_key;
		uint16_t m_item;
	};

	struct ViewState
	{
		ViewState()
		{
		}

		ViewState(Frame* _frame, bool _hmdEnabled)
		{
			reset(_frame, _hmdEnabled);
		}

		void reset(Frame* _frame, bool _hmdEnabled)
		{
			m_alphaRef = 0.0f;
			m_invViewCached = UINT16_MAX;
			m_invProjCached = UINT16_MAX;
			m_invViewProjCached = UINT16_MAX;

			m_view[0] = m_viewTmp[0];
			m_view[1] = m_viewTmp[1];

			if (_hmdEnabled)
			{
				HMD& hmd = _frame->m_hmd;

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
						if (BGFX_VIEW_STEREO == (_frame->m_view[ii].m_flags & BGFX_VIEW_STEREO) )
						{
							bx::float4x4_mul(&m_view[eye][ii].un.f4x4
								, &_frame->m_view[ii].m_view.un.f4x4
								, &viewAdjust.un.f4x4
								);
						}
						else
						{
							bx::memCopy(&m_view[0][ii].un.f4x4, &_frame->m_view[ii].m_view.un.f4x4, sizeof(Matrix4) );
						}
					}
				}
			}
			else
			{
				for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
				{
					bx::memCopy(&m_view[0][ii].un.f4x4, &_frame->m_view[ii].m_view.un.f4x4, sizeof(Matrix4) );
				}
			}

			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				for (uint32_t eye = 0; eye < uint32_t(_hmdEnabled)+1; ++eye)
				{
					bx::float4x4_mul(&m_viewProj[eye][ii].un.f4x4
						, &m_view[eye][ii].un.f4x4
						, &_frame->m_view[ii].m_proj[eye].un.f4x4
						);
				}
			}
		}

		template<uint16_t mtxRegs, typename RendererContext, typename Program, typename Draw>
		void setPredefined(RendererContext* _renderer, uint16_t _view, uint8_t _eye, const Program& _program, const Frame* _frame, const Draw& _draw)
		{
			const FrameCache& frameCache = _frame->m_frameCache;

			for (uint32_t ii = 0, num = _program.m_numPredefined; ii < num; ++ii)
			{
				const PredefinedUniform& predefined = _program.m_predefined[ii];
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
							, m_view[_eye][_view].un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvView:
					{
						uint16_t viewEye = (_view << 1) | _eye;
						if (viewEye != m_invViewCached)
						{
							m_invViewCached = viewEye;
							bx::float4x4_inverse(&m_invView.un.f4x4
								, &m_view[_eye][_view].un.f4x4
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
							, _frame->m_view[_view].m_proj[_eye].un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvProj:
					{
						uint16_t viewEye = (_view << 1) | _eye;
						if (viewEye != m_invProjCached)
						{
							m_invProjCached = viewEye;
							bx::float4x4_inverse(&m_invProj.un.f4x4
								, &_frame->m_view[_view].m_proj[_eye].un.f4x4
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
							, m_viewProj[_eye][_view].un.val
							, bx::uint32_min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvViewProj:
					{
						uint16_t viewEye = (_view << 1) | _eye;
						if (viewEye != m_invViewProjCached)
						{
							m_invViewProjCached = viewEye;
							bx::float4x4_inverse(&m_invViewProj.un.f4x4
								, &m_viewProj[_eye][_view].un.f4x4
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
						const Matrix4& model = frameCache.m_matrixCache.m_cache[_draw.m_startMatrix];
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, model.un.val
							, bx::uint32_min(_draw.m_numMatrices*mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ModelView:
					{
						Matrix4 modelView;
						const Matrix4& model = frameCache.m_matrixCache.m_cache[_draw.m_startMatrix];
						bx::float4x4_mul(&modelView.un.f4x4
							, &model.un.f4x4
							, &m_view[_eye][_view].un.f4x4
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
						const Matrix4& model = frameCache.m_matrixCache.m_cache[_draw.m_startMatrix];
						bx::float4x4_mul(&modelViewProj.un.f4x4
							, &model.un.f4x4
							, &m_viewProj[_eye][_view].un.f4x4
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

	template <typename Ty, uint16_t MaxHandleT>
	class StateCacheLru
	{
	public:
		Ty* add(uint64_t _key, const Ty& _value, uint16_t _parent)
		{
			uint16_t handle = m_alloc.alloc();
			if (UINT16_MAX == handle)
			{
				uint16_t back = m_alloc.getBack();
				invalidate(back);
				handle = m_alloc.alloc();
			}

			BX_CHECK(UINT16_MAX != handle, "Failed to find handle.");

			Data& data = m_data[handle];
			data.m_hash   = _key;
			data.m_value  = _value;
			data.m_parent = _parent;
			m_hashMap.insert(stl::make_pair(_key, handle) );

			return &m_data[handle].m_value;
		}

		Ty* find(uint64_t _key)
		{
			HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				uint16_t handle = it->second;
				m_alloc.touch(handle);
				return &m_data[handle].m_value;
			}

			return NULL;
		}

		void invalidate(uint64_t _key)
		{
			HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				uint16_t handle = it->second;
				m_alloc.free(handle);
				m_hashMap.erase(it);
				release(m_data[handle].m_value);
			}
		}

		void invalidate(uint16_t _handle)
		{
			if (m_alloc.isValid(_handle) )
			{
				m_alloc.free(_handle);
				Data& data = m_data[_handle];
				m_hashMap.erase(m_hashMap.find(data.m_hash) );
				release(data.m_value);
			}
		}

		void invalidateWithParent(uint16_t _parent)
		{
			for (uint16_t ii = 0; ii < m_alloc.getNumHandles();)
			{
				uint16_t handle = m_alloc.getHandleAt(ii);
				Data& data = m_data[handle];

				if (data.m_parent == _parent)
				{
					m_alloc.free(handle);
					m_hashMap.erase(m_hashMap.find(data.m_hash) );
					release(data.m_value);
				}
				else
				{
					++ii;
				}
			}
		}

		void invalidate()
		{
			for (uint16_t ii = 0, num = m_alloc.getNumHandles(); ii < num; ++ii)
			{
				uint16_t handle = m_alloc.getHandleAt(ii);
				Data& data = m_data[handle];
				release(data.m_value);
			}

			m_hashMap.clear();
			m_alloc.reset();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint64_t, uint16_t> HashMap;
		HashMap m_hashMap;
		bx::HandleAllocLruT<MaxHandleT> m_alloc;
		struct Data
		{
			uint64_t m_hash;
			Ty m_value;
			uint16_t m_parent;
		};

		Data m_data[MaxHandleT];
	};

	class StateCache
	{
	public:
		void add(uint64_t _key, uint16_t _value)
		{
			invalidate(_key);
			m_hashMap.insert(stl::make_pair(_key, _value) );
		}

		uint16_t find(uint64_t _key)
		{
			HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				return it->second;
			}

			return UINT16_MAX;
		}

		void invalidate(uint64_t _key)
		{
			HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				m_hashMap.erase(it);
			}
		}

		void invalidate()
		{
			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		typedef stl::unordered_map<uint64_t, uint16_t> HashMap;
		HashMap m_hashMap;
	};

	inline bool hasVertexStreamChanged(const RenderDraw& _current, const RenderDraw& _new)
	{
		if (_current.m_streamMask             != _new.m_streamMask
		||  _current.m_instanceDataBuffer.idx != _new.m_instanceDataBuffer.idx
		||  _current.m_instanceDataOffset     != _new.m_instanceDataOffset
		||  _current.m_instanceDataStride     != _new.m_instanceDataStride)
		{
			return true;
		}

		for (uint32_t idx = 0, streamMask = _new.m_streamMask, ntz = bx::uint32_cnttz(streamMask)
			; 0 != streamMask
			; streamMask >>= 1, idx += 1, ntz = bx::uint32_cnttz(streamMask)
			)
		{
			streamMask >>= ntz;
			idx         += ntz;

			if (_current.m_stream[idx].m_handle.idx  != _new.m_stream[idx].m_handle.idx
			||  _current.m_stream[idx].m_startVertex != _new.m_stream[idx].m_startVertex)
			{
				return true;
			}
		}

		return false;
	}

	template<typename Ty>
	struct Profiler
	{
		Profiler(Frame* _frame, Ty& _gpuTimer, const char (*_viewName)[BGFX_CONFIG_MAX_VIEW_NAME], bool _enabled = true)
			: m_viewName(_viewName)
			, m_frame(_frame)
			, m_gpuTimer(_gpuTimer)
			, m_queryIdx(UINT32_MAX)
			, m_numViews(0)
			, m_enabled(_enabled && 0 != (_frame->m_debug & BGFX_DEBUG_PROFILER) )
		{
		}

		~Profiler()
		{
			m_frame->m_perfStats.numViews = m_numViews;
		}

		void begin(uint16_t _view)
		{
			if (m_enabled)
			{
				ViewStats& viewStats = m_frame->m_perfStats.viewStats[m_numViews];
				viewStats.cpuTimeElapsed = -bx::getHPCounter();

				m_queryIdx = m_gpuTimer.begin(_view);

				viewStats.view = ViewId(_view);
				bx::strCopy(viewStats.name
					, BGFX_CONFIG_MAX_VIEW_NAME
					, &m_viewName[_view][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
					);
			}
		}

		void end()
		{
			if (m_enabled
			&&  UINT32_MAX != m_queryIdx)
			{
				m_gpuTimer.end(m_queryIdx);

				ViewStats& viewStats = m_frame->m_perfStats.viewStats[m_numViews];
				const typename Ty::Result& result = m_gpuTimer.m_result[viewStats.view];

				viewStats.cpuTimeElapsed += bx::getHPCounter();
				viewStats.gpuTimeElapsed = result.m_end - result.m_begin;

				++m_numViews;
				m_queryIdx = UINT32_MAX;
			}
		}

		const char (*m_viewName)[BGFX_CONFIG_MAX_VIEW_NAME];
		Frame*   m_frame;
		Ty&      m_gpuTimer;
		uint32_t m_queryIdx;
		uint16_t m_numViews;
		bool     m_enabled;
	};

} // namespace bgfx

#endif // BGFX_RENDERER_H_HEADER_GUARD
