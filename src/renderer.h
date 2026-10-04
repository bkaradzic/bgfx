/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_RENDERER_H_HEADER_GUARD
#define BGFX_RENDERER_H_HEADER_GUARD

#include "bgfx_p.h"
#include <bx/pixelformat.h>

namespace bgfx
{
	inline void setViewType(char* _viewName, const bx::StringView _str)
	{
		bx::memCopy(&_viewName[4], _str.getPtr(), _str.getLength() );
	}

	inline bool isIntegerFormat(TextureFormat::Enum _format)
	{
		const bx::EncodingType::Enum encoding = bx::EncodingType::Enum(bimg::getBlockInfo(bimg::TextureFormat::Enum(_format) ).encoding);
		return bx::EncodingType::Int  == encoding
			|| bx::EncodingType::Uint == encoding
			;
	}

	inline void getClearColor(float _rgba[4], const Clear& _clear, const float _palette[][4], uint32_t _attachment, bool _integer)
	{
		if (BGFX_CLEAR_COLOR_USE_PALETTE & _clear.m_flags)
		{
			const uint8_t index = bx::min<uint8_t>(BGFX_CONFIG_MAX_COLOR_PALETTE-1, _clear.m_index[_attachment]);
			bx::memCopy(_rgba, _palette[index], sizeof(float)*4);
		}
		else
		{
			const float scale = _integer ? 1.0f : 1.0f/255.0f;
			_rgba[0] = _clear.m_index[0]*scale;
			_rgba[1] = _clear.m_index[1]*scale;
			_rgba[2] = _clear.m_index[2]*scale;
			_rgba[3] = _clear.m_index[3]*scale;
		}
	}

	inline uint32_t packIntegerTexel(uint8_t* _out, TextureFormat::Enum _format, const float _rgba[4])
	{
		const bimg::ImageBlockInfo& info = bimg::getBlockInfo(bimg::TextureFormat::Enum(_format) );
		const uint8_t bits[4] = { info.rBits, info.gBits, info.bBits, info.aBits };

		uint32_t size = 0;

		for (uint32_t ii = 0; ii < 4; ++ii)
		{
			const int64_t value = int64_t(_rgba[ii]);

			for (uint32_t bb = 0, num = bits[ii]/8; bb < num; ++bb)
			{
				_out[size++] = uint8_t(value >> (bb*8) );
			}
		}

		return size;
	}

	static constexpr uint32_t kTimerQueryBlock = 64;
	static constexpr uint32_t kMaxTimerQueries = BGFX_CONFIG_MAX_VIEWS*4;
	static constexpr uint32_t kMinTimerQueries = bx::min<uint32_t>(kTimerQueryBlock, kMaxTimerQueries);

	inline uint32_t getNumTimerQueries(const Frame* _frame, uint32_t _num)
	{
		const bool profiler     = 0 != (_frame->m_debug & BGFX_DEBUG_PROFILER);
		const uint32_t numViews = profiler ? _frame->m_numUsedViews : 0;
		const uint32_t spare    = profiler ? kTimerQueryBlock : 0;
		const uint32_t num      = bx::min<uint32_t>(bx::alignUp( (numViews+1)*4, kTimerQueryBlock) + spare, kMaxTimerQueries);

		return profiler
			? bx::max(num, _num)
			: num
			;
	}

	inline void resize(bx::RingBufferControl& _control, uint32_t _size)
	{
		_control.reset();
		_control.resize(int32_t(_size) - int32_t(_control.getSize() ) );
	}

	template<typename ResultT>
	class TimerResultT
	{
	public:
		TimerResultT()
			: m_result(NULL)
			, m_num(0)
		{
			m_frame.reset();
		}

		~TimerResultT()
		{
			bx::free(g_allocator, m_result);
		}

		void reset()
		{
			for (uint32_t ii = 0; ii < m_num; ++ii)
			{
				m_result[ii].reset();
			}

			m_frame.reset();
		}

		void resetPending()
		{
			for (uint32_t ii = 0; ii < m_num; ++ii)
			{
				m_result[ii].m_pending = 0;
			}

			m_frame.m_pending = 0;
		}

		ResultT& operator[](uint32_t _idx)
		{
			if (BGFX_CONFIG_MAX_VIEWS == _idx)
			{
				return m_frame;
			}

			if (_idx >= m_num)
			{
				grow(_idx + 1);
			}

			return m_result[_idx];
		}

	private:
		BX_NO_INLINE void grow(uint32_t _num)
		{
			const uint32_t num = bx::alignUp(_num, kTimerQueryBlock);

			ResultT* result = (ResultT*)bx::alloc(g_allocator, sizeof(ResultT)*num);
			bx::memCopy(result, m_result, sizeof(ResultT)*m_num);

			for (uint32_t ii = m_num; ii < num; ++ii)
			{
				result[ii].reset();
			}

			bx::free(g_allocator, m_result);
			m_result = result;
			m_num    = num;
		}

		ResultT* m_result;
		uint32_t m_num;
		ResultT  m_frame;
	};

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
				&& m_key.m_view <= m_frame->m_viewOrder[_view]
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
		uint32_t m_item;
	};

	struct UniformCacheItem
	{
		uint32_t m_offset;
		uint16_t m_size;
		uint16_t m_handle;
	};

	struct UniformCacheState
	{
		UniformCacheState(const Frame* _frame)
			: m_frame(_frame)
			, m_item(0)
		{
			m_key.decode(_frame->m_uniformCacheFrame.m_keys[0]);
		}

		bool hasItem(uint16_t _view) const
		{
			return m_item < m_frame->m_uniformCacheFrame.m_numItems
				&& m_key.m_view <= m_frame->m_viewOrder[_view]
				;
		}

		const UniformCacheItem advance()
		{
			UniformCacheItem item =
			{
				.m_offset = m_key.m_offset,
				.m_size   = m_key.m_size,
				.m_handle = m_key.m_handle,
			};

			++m_item;
			m_key.decode(m_frame->m_uniformCacheFrame.m_keys[m_item]);

			return item;
		}

		const Frame*    m_frame;
		UniformCacheKey m_key;
		uint16_t        m_item;
	};

	struct ViewState
	{
		ViewState()
		{
		}

		ViewState(Frame* _frame)
		{
			reset(_frame);
		}

		void reset(Frame* _frame)
		{
			m_alphaRef = 0.0f;
			m_ndcFixup = 1.0f;
			m_invViewCached = UINT16_MAX;
			m_invProjCached = UINT16_MAX;
			m_invViewProjCached = UINT16_MAX;

			BX_UNUSED(_frame);
		}

		BX_NO_INLINE void setView(const View& _renderView)
		{
			bx::float4x4_mul(&m_viewProj.un.f4x4
				, &_renderView.m_view.un.f4x4
				, &_renderView.m_proj.un.f4x4
				);
		}

		template<uint16_t mtxRegs, typename RendererContext, typename Program, typename Draw>
		void setPredefined(RendererContext* _renderer, uint16_t _view, const View& _renderView, const Program& _program, const Frame* _frame, const Draw& _draw)
		{
			const FrameCache& frameCache = _frame->m_frameCache;

			for (uint32_t ii = 0, num = _program.m_numPredefined; ii < num; ++ii)
			{
				const PredefinedUniform& predefined = _program.m_predefined[ii];
				uint8_t flags = predefined.m_type&kUniformFragmentBit;
				switch (predefined.m_type&(~kUniformFragmentBit) )
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
						// .zw = the view's viewport depth range [minDepth, maxDepth], for
						// shaders that clamp a written depth (WebGPU @builtin(frag_depth)).
						frect[2] = _renderView.m_minDepth;
						frect[3] = _renderView.m_maxDepth;

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
							, _renderView.m_view.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvView:
					{
						if (_view != m_invViewCached)
						{
							m_invViewCached = _view;
							bx::float4x4_inverse(&m_invView.un.f4x4
								, &_renderView.m_view.un.f4x4
								);
						}

						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_invView.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::Proj:
					{
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, _renderView.m_proj.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvProj:
					{
						if (_view != m_invProjCached)
						{
							m_invProjCached = _view;
							bx::float4x4_inverse(&m_invProj.un.f4x4
								, &_renderView.m_proj.un.f4x4
								);
						}

						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_invProj.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ViewProj:
					{
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_viewProj.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvViewProj:
					{
						if (_view != m_invViewProjCached)
						{
							m_invViewProjCached = _view;
							bx::float4x4_inverse(&m_invViewProj.un.f4x4
								, &m_viewProj.un.f4x4
								);
						}

						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, m_invViewProj.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::Model:
					{
						const Matrix4& model = frameCache.m_matrixCache.at(_draw.m_startMatrix);
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, model.un.val
							, bx::min(_draw.m_numMatrices*mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ModelView:
					{
						Matrix4 modelView;
						const Matrix4& model = frameCache.m_matrixCache.at(_draw.m_startMatrix);
						bx::model4x4_mul(&modelView.un.f4x4
							, &model.un.f4x4
							, &_renderView.m_view.un.f4x4
							);
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, modelView.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::InvModelView:
					{
						Matrix4 modelView;
						Matrix4 invModelView;
						const Matrix4& model = frameCache.m_matrixCache.at(_draw.m_startMatrix);
						bx::model4x4_mul(&modelView.un.f4x4
							, &model.un.f4x4
							, &_renderView.m_view.un.f4x4
							);
						bx::float4x4_inverse(&invModelView.un.f4x4
							, &modelView.un.f4x4
							);
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, invModelView.un.val
							, bx::min(mtxRegs, predefined.m_count)
							);
					}
					break;

				case PredefinedUniform::ModelViewProj:
					{
						Matrix4 modelViewProj;
						const Matrix4& model = frameCache.m_matrixCache.at(_draw.m_startMatrix);
						bx::model4x4_mul_viewproj4x4(&modelViewProj.un.f4x4
							, &model.un.f4x4
							, &m_viewProj.un.f4x4
							);
						_renderer->setShaderUniform4x4f(flags
							, predefined.m_loc
							, modelViewProj.un.val
							, bx::min(mtxRegs, predefined.m_count)
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

				case PredefinedUniform::IndirectArgBase:
					{
						const float base[4] =
						{
							bx::bitsToFloat(_draw.m_startIndex),
							0.0f,
							0.0f,
							m_ndcFixup,
						};
						_renderer->setShaderUniform4f(flags
							, predefined.m_loc
							, base
							, 1
							);
					}
					break;

				default:
					BX_ASSERT(false, "predefined %d not handled", predefined.m_type);
					break;
				}
			}
		}

		Rect     m_rect;
		Matrix4  m_viewProj;
		Matrix4  m_invView;
		Matrix4  m_invProj;
		Matrix4  m_invViewProj;
		float    m_alphaRef;
		float    m_ndcFixup;

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

			BX_ASSERT(UINT16_MAX != handle, "Failed to find handle.");

			Data& data = m_data[handle];
			data.m_hash   = _key;
			data.m_value  = _value;
			data.m_parent = _parent;
			m_hashMap.insert(stl::make_pair(_key, handle) );

			return bx::addressOf(m_data[handle].m_value);
		}

		Ty* find(uint64_t _key)
		{
			HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				uint16_t handle = it->second;
				m_alloc.touch(handle);
				return bx::addressOf(m_data[handle].m_value);
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

	template<typename Ty>
	struct StateCacheFuncT
	{
		static void evict(Ty _value)
		{
			release(_value);
		}

		static void validate(Ty /*_value*/, uint64_t /*_key*/)
		{
		}
	};

	template<typename Ty>
	class StateCacheT
	{
	public:
		void add(uint64_t _key, Ty _value, uint16_t _parent = UINT16_MAX)
		{
			invalidate(_key);
			StateCacheFuncT<Ty>::validate(_value, _key);
			m_hashMap.insert(stl::make_pair(_key, Data{_value, _parent}) );
		}

		Ty find(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				return it->second.m_value;
			}

			return Ty(0);
		}

		void invalidate(uint64_t _key)
		{
			typename HashMap::iterator it = m_hashMap.find(_key);
			if (it != m_hashMap.end() )
			{
				StateCacheFuncT<Ty>::evict(it->second.m_value);
				m_hashMap.erase(it);
			}
		}

		void invalidateWithParent(uint16_t _parent)
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd;)
			{
				if (it->second.m_parent == _parent)
				{
					StateCacheFuncT<Ty>::evict(it->second.m_value);
					typename HashMap::iterator itErase = it;
					++it;
					m_hashMap.erase(itErase);
				}
				else
				{
					++it;
				}
			}
		}

		void invalidate()
		{
			for (typename HashMap::iterator it = m_hashMap.begin(), itEnd = m_hashMap.end(); it != itEnd; ++it)
			{
				StateCacheFuncT<Ty>::evict(it->second.m_value);
			}

			m_hashMap.clear();
		}

		uint32_t getCount() const
		{
			return uint32_t(m_hashMap.size() );
		}

	private:
		struct Data
		{
			Ty       m_value;
			uint16_t m_parent;
		};

		typedef stl::unordered_map<uint64_t, Data> HashMap;
		HashMap m_hashMap;
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

	template<typename Derived, typename BufferTy, typename ChunkTy>
	struct ChunkedScratchBufferT
	{
		struct Alloc
		{
			uint32_t offset;
			uint32_t chunkIdx;
		};

		ChunkedScratchBufferT()
			: m_chunkControl(0)
		{
		}

		void create(uint32_t _chunkSize, uint32_t _numChunks, uint32_t _align)
		{
			const uint32_t chunkSize = bx::alignUp(_chunkSize, 1<<20);

			m_chunkPos  = 0;
			m_chunkSize = chunkSize;
			m_align     = _align;

			m_chunkControl.m_size = 0;
			m_chunkControl.reset();

			bx::memSet(m_consume, 0, sizeof(m_consume) );
			m_totalUsed = 0;

			for (uint32_t ii = 0; ii < _numChunks; ++ii)
			{
				addChunk();
			}
		}

		void destroy()
		{
			for (ChunkTy& sbc : m_chunks)
			{
				static_cast<Derived*>(this)->destroyChunk(sbc);
			}
		}

		void addChunk(uint32_t _at = UINT32_MAX)
		{
			ChunkTy sbc;
			static_cast<Derived*>(this)->createChunk(sbc);

			const uint32_t numChunks  = uint32_t(m_chunks.size() );
			const uint32_t chunkIndex = UINT32_MAX == _at
				? numChunks
				: bx::min(_at, numChunks)
				;

			m_chunkControl.resize(m_chunkSize);

			m_chunks.insert(m_chunks.begin() + chunkIndex, sbc);
		}

		Alloc alloc(uint32_t _size)
		{
			BX_ASSERT(_size < m_chunkSize, "Size can't be larger than chunk size (size: %d, chunk size: %d)!", _size, m_chunkSize);

			uint32_t offset     = m_chunkPos;
			uint32_t nextOffset = offset + _size;
			uint32_t chunkIdx   = m_chunkControl.m_write/m_chunkSize;

			if (nextOffset >= m_chunkSize)
			{
				const uint32_t total = m_chunkSize - m_chunkPos + _size;
				uint32_t reserved    = m_chunkControl.reserve(total, true);

				if (total != reserved)
				{
					addChunk(chunkIdx + 1);
					reserved = m_chunkControl.reserve(total, true);
					BX_ASSERT(total == reserved, "Failed to reserve chunk memory after adding chunk.");
				}

				m_chunkPos = 0;
				offset     = 0;
				nextOffset = _size;
				chunkIdx   = m_chunkControl.m_write/m_chunkSize;
			}
			else
			{
				const uint32_t size = m_chunkControl.reserve(_size, true);
				BX_ASSERT(size == _size, "Failed to reserve chunk memory.");
				BX_UNUSED(size);
			}

			m_chunkPos = nextOffset;

			return { .offset = offset, .chunkIdx = chunkIdx };
		}

		template<typename OffsetTy>
		void write(OffsetTy& _outSbo, const void* _vsData, uint32_t _vsSize, const void* _fsData = NULL, uint32_t _fsSize = 0)
		{
			const uint32_t vsSize = bx::strideAlign(_vsSize, m_align);
			const uint32_t fsSize = bx::strideAlign(_fsSize, m_align);
			const uint32_t size   = vsSize + fsSize;

			const Alloc sba = alloc(size);

			const uint32_t offset0 = sba.offset;
			const uint32_t offset1 = offset0 + vsSize;

			const ChunkTy& sbc = m_chunks[sba.chunkIdx];

			_outSbo.buffer = sbc.buffer;
			_outSbo.offsets[0] = offset0;
			_outSbo.offsets[1] = offset1;

			if (NULL != _vsData)
			{
				bx::memCopy(&sbc.data[offset0], _vsData, _vsSize);
			}

			if (NULL != _fsData)
			{
				bx::memCopy(&sbc.data[offset1], _fsData, _fsSize);
			}
		}

		void begin()
		{
			BX_ASSERT(0 == m_chunkPos, "");
			const uint32_t numConsumed = m_consume[static_cast<Derived*>(this)->currentFrameInFlight()];
			m_chunkControl.consume(numConsumed);
		}

		void end()
		{
			uint32_t numFlush = m_chunkControl.getNumReserved();

			if (0 != m_chunkPos)
			{
				for (;;)
				{
					const uint32_t remainder = m_chunkSize - m_chunkPos;
					const uint32_t rem = m_chunkControl.reserve(remainder, true);

					if (rem != remainder)
					{
						const uint32_t chunkIdx = m_chunkControl.m_write/m_chunkSize;
						addChunk(chunkIdx + 1);
						continue;
					}

					break;
				}

				m_chunkPos = 0;
			}

			const uint32_t numReserved = m_chunkControl.getNumReserved();
			BX_ASSERT(0 == numReserved % m_chunkSize, "Number of reserved must always be aligned to chunk size!");

			const uint32_t first = m_chunkControl.m_current / m_chunkSize;

			for (uint32_t ii = first, num = numReserved / m_chunkSize + first; ii < num; ++ii)
			{
				ChunkTy& chunk = m_chunks[ii % m_chunks.size()];

				static_cast<Derived*>(this)->flushChunk(chunk, bx::min(numFlush, m_chunkSize) );

				m_chunkControl.commit(m_chunkSize);
				numFlush = bx::satSub<uint32_t>(numFlush, m_chunkSize);
			}

			m_consume[static_cast<Derived*>(this)->currentFrameInFlight()] = numReserved;

			m_totalUsed = m_chunkControl.getNumUsed();
		}

		void flush()
		{
			end();
			begin();
		}

		stl::vector<ChunkTy> m_chunks;
		bx::RingBufferControl m_chunkControl;

		uint32_t m_chunkPos;
		uint32_t m_chunkSize;
		uint32_t m_align;

		uint32_t m_consume[BGFX_CONFIG_MAX_FRAME_LATENCY < BGFX_CONFIG_MAX_BACK_BUFFERS ? BGFX_CONFIG_MAX_BACK_BUFFERS : BGFX_CONFIG_MAX_FRAME_LATENCY];
		uint32_t m_totalUsed;
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

		if (UINT32_MAX != _new.m_streamMask)
		{
			for (BitMaskToIndexIteratorT it(_new.m_streamMask); !it.isDone(); it.next() )
			{
				const uint8_t idx = it.idx;

				if (_current.m_stream[idx].m_handle.idx       != _new.m_stream[idx].m_handle.idx
				||  _current.m_stream[idx].m_startVertex      != _new.m_stream[idx].m_startVertex
				||  _current.m_stream[idx].m_layoutHandle.idx != _new.m_stream[idx].m_layoutHandle.idx)
				{
					return true;
				}
			}
		}

		return false;
	}

	template<typename Ty>
	struct Profiler
	{
		Profiler(Frame* _frame, Ty& _gpuTimer, bool _enabled = true)
			: m_frame(_frame)
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
				ViewStats& viewStats   = m_frame->m_perfStats.viewStats[m_numViews];
				viewStats.cpuTimeBegin = bx::getHPCounter();

				m_queryIdx = m_gpuTimer.begin(_view, m_frame->m_frameNum);

				viewStats.view = ViewId(_view);
				bx::strCopy(viewStats.name
					, BGFX_CONFIG_MAX_VIEW_NAME
					, getViewName(m_frame, _view)
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

				viewStats.cpuTimeEnd   = bx::getHPCounter();
				viewStats.gpuTimeBegin = result.m_begin;
				viewStats.gpuTimeEnd   = result.m_end;
				viewStats.gpuFrameNum  = result.m_frameNum;

				++m_numViews;
				m_queryIdx = UINT32_MAX;
			}
		}

		Frame*   m_frame;
		Ty&      m_gpuTimer;
		uint32_t m_queryIdx;
		uint16_t m_numViews;
		bool     m_enabled;
	};

} // namespace bgfx

#endif // BGFX_RENDERER_H_HEADER_GUARD
