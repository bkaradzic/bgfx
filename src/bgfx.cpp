/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_WINDOWS
HWND g_bgfxHwnd = NULL;
#endif // BX_PLATFORM_WINDOWS

#if BGFX_CONFIG_USE_TINYSTL
namespace tinystl
{
	void* bgfx_allocator::static_allocate(size_t _bytes)
	{
		return bgfx::g_realloc(NULL, _bytes);
	}

	void bgfx_allocator::static_deallocate(void* _ptr, size_t /*_bytes*/)
	{
		bgfx::g_free(_ptr);
	}

} // namespace tinystl
#endif // BGFX_CONFIG_USE_TINYSTL

namespace bgfx
{
#define BGFX_MAIN_THREAD_MAGIC 0x78666762

#if BGFX_CONFIG_MULTITHREADED
#	define BGFX_MAIN_THREAD() BX_CHECK(BGFX_MAIN_THREAD_MAGIC == s_threadIndex, "Must be called from main thread.")
#	define BGFX_RENDER_THREAD() BX_CHECK(BGFX_MAIN_THREAD_MAGIC != s_threadIndex, "Must be called from render thread.")
#else
#	define BGFX_MAIN_THREAD()
#	define BGFX_RENDER_THREAD()
#endif // BGFX_CONFIG_MULTITHREADED

	void fatalStub(bgfx::Fatal::Enum _code, const char* _str)
	{
		BX_TRACE("0x%08x: %s", _code, _str);
	}

	void* reallocStub(void* _ptr, size_t _size)
	{
		void* ptr = ::realloc(_ptr, _size);
		BX_CHECK(NULL != ptr, "Out of memory!");
		//	BX_TRACE("alloc %d, %p", _size, ptr);
		return ptr;
	}

	void freeStub(void* _ptr)
	{
		//	BX_TRACE("free %p", _ptr);
		::free(_ptr);
	}

	void cacheStub(uint64_t _id, bool _store, void* _data, uint32_t& _length)
	{
		_length = 0;
	}

	fatalFn g_fatal = fatalStub;
	reallocFn g_realloc = reallocStub;
	freeFn g_free = freeStub;
	cacheFn g_cache = cacheStub;

	static BX_THREAD uint32_t s_threadIndex = 0;
	static Context s_ctx;

	void fatal(bgfx::Fatal::Enum _code, const char* _format, ...)
	{
		char temp[8192];

		va_list argList;
		va_start(argList, _format);
		vsnprintf(temp, sizeof(temp), _format, argList);
		va_end(argList);

		temp[sizeof(temp)-1] = '\0';

		g_fatal(_code, temp);
	}

	inline void vec_mul_mtx(float* __restrict _result, const float* __restrict _vec, const float* __restrict _mat)
	{
		_result[0] = _vec[0] * _mat[ 0] + _vec[1] * _mat[4] + _vec[2] * _mat[ 8] + _vec[3] * _mat[12];
		_result[1] = _vec[0] * _mat[ 1] + _vec[1] * _mat[5] + _vec[2] * _mat[ 9] + _vec[3] * _mat[13];
		_result[2] = _vec[0] * _mat[ 2] + _vec[1] * _mat[6] + _vec[2] * _mat[10] + _vec[3] * _mat[14];
		_result[3] = _vec[0] * _mat[ 3] + _vec[1] * _mat[7] + _vec[2] * _mat[11] + _vec[3] * _mat[15];
	}

	void matrix_mul(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
	{
		vec_mul_mtx(&_result[ 0], &_a[ 0], _b);
		vec_mul_mtx(&_result[ 4], &_a[ 4], _b);
		vec_mul_mtx(&_result[ 8], &_a[ 8], _b);
		vec_mul_mtx(&_result[12], &_a[12], _b);
	}

	void matrix_ortho(float* _result, float _left, float _right, float _bottom, float _top, float _near, float _far)
	{
		const float aa = 2.0f/(_right - _left);
		const float bb = 2.0f/(_top - _bottom);
		const float cc = 1.0f/(_far - _near);
		const float dd = (_left + _right)/(_left - _right);
		const float ee = (_top + _bottom)/(_bottom - _top);
		const float ff = _near / (_near - _far);

		memset(_result, 0, sizeof(float)*16);
		_result[0] = aa;
		_result[5] = bb;
		_result[10] = cc;
		_result[12] = dd;
		_result[13] = ee;
		_result[14] = ff;
		_result[15] = 1.0f;
	}

	void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
	{
		FILE* file = fopen(_filePath, "wb");
		if ( NULL != file )
		{
			uint8_t type = _grayscale ? 3 : 2;
			uint8_t bpp = _grayscale ? 8 : 32;

			putc(0, file);
			putc(0, file);
			putc(type, file);
			putc(0, file); 
			putc(0, file);
			putc(0, file); 
			putc(0, file);
			putc(0, file);
			putc(0, file); 
			putc(0, file);
			putc(0, file); 
			putc(0, file);
			putc(_width&0xff, file);
			putc( (_width>>8)&0xff, file);
			putc(_height&0xff, file);
			putc( (_height>>8)&0xff, file);
			putc(bpp, file);
			putc(32, file);

			uint32_t dstPitch = _width*bpp/8;
			if (_yflip)
			{
				uint8_t* data = (uint8_t*)_src + dstPitch*_height - _srcPitch;
				for (uint32_t yy = 0; yy < _height; ++yy)
				{
					fwrite(data, dstPitch, 1, file);
					data -= _srcPitch;
				}
			}
			else
			{
				uint8_t* data = (uint8_t*)_src;
				for (uint32_t yy = 0; yy < _height; ++yy)
				{
					fwrite(data, dstPitch, 1, file);
					data += _srcPitch;
				}
			}

			fclose(file);
		}
	}

#include "charset.h"

	void charsetFillTexture(const uint8_t* _charset, uint8_t* _rgba, uint32_t _height, uint32_t _pitch, uint32_t _bpp)
	{
		for (uint32_t ii = 0; ii < 256; ++ii)
		{
			uint8_t* pix = &_rgba[ii*8*_bpp];
			for (uint32_t yy = 0; yy < _height; ++yy)
			{
				for (uint32_t xx = 0; xx < 8; ++xx)
				{
					uint8_t bit = 1<<(7-xx);
					memset(&pix[xx*_bpp], _charset[ii*_height+yy]&bit ? 255 : 0, _bpp);
				}

				pix += _pitch;
			}
		}
	}

	static const uint32_t numCharsPerBatch = 1024;
	static const uint32_t numBatchVertices = numCharsPerBatch*4;
	static const uint32_t numBatchIndices = numCharsPerBatch*6;

	void TextVideoMemBlitter::init()
	{
		m_decl.begin();
		m_decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		m_decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8);
		m_decl.add(bgfx::Attrib::Color1, 4, bgfx::AttribType::Uint8);
		m_decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
		m_decl.end();

		uint16_t width = 2048;
		uint16_t height = 24;
		uint8_t bpp = 1;
		uint32_t pitch = width*bpp;

		const bgfx::Memory* mem;

		mem = alloc(pitch*height+16);

		StreamWrite stream(mem->data, mem->size);
		uint32_t magic = BGFX_MAGIC;
		stream.write(magic);
		stream.write(width);
		stream.write(height);
		stream.write(bpp);
		uint8_t numMips = 1;
		stream.write(numMips);
		stream.align(16);
		uint8_t* rgba = stream.getDataPtr();
		charsetFillTexture(vga8x8, rgba, 8, pitch, bpp);
		charsetFillTexture(vga8x16, &rgba[8*pitch], 16, pitch, bpp);
		m_texture = s_ctx.createTexture(mem, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT, NULL, NULL);

#if BGFX_CONFIG_RENDERER_DIRECT3D
		mem = bgfx::alloc(sizeof(vs_debugfont_hlsl)+1);
		memcpy(mem->data, vs_debugfont_hlsl, mem->size-1);
#else
		mem = bgfx::alloc(sizeof(vs_debugfont_glsl)+1);
		memcpy(mem->data, vs_debugfont_glsl, mem->size-1);
#endif // BGFX_CONFIG_RENDERER_
		mem->data[mem->size-1] = '\0';
		bgfx::VertexShaderHandle vsh = bgfx::createVertexShader(mem);

#if BGFX_CONFIG_RENDERER_DIRECT3D
		mem = bgfx::alloc(sizeof(fs_debugfont_hlsl)+1);
		memcpy(mem->data, fs_debugfont_hlsl, mem->size-1);
#else
		mem = bgfx::alloc(sizeof(fs_debugfont_glsl)+1);
		memcpy(mem->data, fs_debugfont_glsl, mem->size-1);
#endif // BGFX_CONFIG_RENDERER_
		mem->data[mem->size-1] = '\0';
		bgfx::FragmentShaderHandle fsh = bgfx::createFragmentShader(mem);

		m_material = bgfx::createMaterial(vsh, fsh);

		m_vb = s_ctx.createTransientVertexBuffer(numBatchVertices*m_decl.m_stride, &m_decl);
		m_ib = s_ctx.createTransientIndexBuffer(numBatchIndices*2);
	}

	void TextVideoMemBlitter::blit(const TextVideoMem& _mem)
	{
		struct FontVertex
		{
			float m_x;
			float m_y;
			float m_z;
			uint32_t m_fg;
			uint32_t m_bg;
			float m_u;
			float m_v;
		};

		static uint32_t palette[16] =
		{
			0x0,
			0xff0000cc,
			0xff069a4e,
			0xff00a0c4,
			0xffa46534,
			0xff7b5075,
			0xff9a9806,
			0xffcfd7d3,
			0xff535755,
			0xff2929ef,
			0xff34e28a,
			0xff4fe9fc,
			0xffcf9f72,
			0xffa87fad,
			0xffe2e234,
			0xffeceeee,
		};

		uint32_t yy = 0;
		uint32_t xx = 0;

		const float texelWidth = 1.0f/2048.0f;
		const float texelWidthHalf = texelWidth*0.5f;
		const float texelHeight = 1.0f/24.0f;
		const float texelHeightHalf = texelHeight*0.5f;
		const float utop = (_mem.m_small ? 0.0f : 8.0f)*texelHeight + texelHeightHalf;
		const float ubottom = (_mem.m_small ? 8.0f : 24.0f)*texelHeight + texelHeightHalf;
		const float fontHeight = (_mem.m_small ? 8.0f : 16.0f);

		setup();

		for (;yy < _mem.m_height;)
		{
			FontVertex* vertex = (FontVertex*)m_vb->data;
			uint16_t* indices = (uint16_t*)m_ib->data;
			uint32_t startVertex = 0;
			uint32_t numIndices = 0;

			for (; yy < _mem.m_height && numIndices < numBatchIndices; ++yy)
			{
				xx = xx < _mem.m_width ? xx : 0;
				const uint8_t* line = &_mem.m_mem[(yy*_mem.m_width+xx)*2];

				for (; xx < _mem.m_width && numIndices < numBatchIndices; ++xx)
				{
					uint8_t ch = line[0];
					uint8_t attr = line[1];

					if (0 != (ch|attr)
					&& (' ' != ch || 0 != (attr&0xf0) ) )
					{
						uint32_t fg = palette[attr&0xf];
						uint32_t bg = palette[(attr>>4)&0xf];

						FontVertex vert[4] = 
						{
							{ (xx  )*8.0f, (yy  )*fontHeight, 0.0f, fg, bg, (ch  )*8.0f*texelWidth - texelWidthHalf, utop },
							{ (xx+1)*8.0f, (yy  )*fontHeight, 0.0f, fg, bg, (ch+1)*8.0f*texelWidth - texelWidthHalf, utop },
							{ (xx+1)*8.0f, (yy+1)*fontHeight, 0.0f, fg, bg, (ch+1)*8.0f*texelWidth - texelWidthHalf, ubottom },
							{ (xx  )*8.0f, (yy+1)*fontHeight, 0.0f, fg, bg, (ch  )*8.0f*texelWidth - texelWidthHalf, ubottom },
						};

						memcpy(vertex, vert, sizeof(vert) );
						vertex += 4;

						indices[0] = startVertex+0;
						indices[1] = startVertex+1;
						indices[2] = startVertex+2;
						indices[3] = startVertex+2;
						indices[4] = startVertex+3;
						indices[5] = startVertex+0;

						startVertex += 4;
						indices += 6;

						numIndices += 6;
					}

					line += 2;
				}

				if (numIndices >= numBatchIndices)
				{
					break;
				}
			}

			render(numIndices);
		}
	}

	static const char* s_predefinedName[PredefinedUniform::Count] =
	{
		"u_viewRect",
		"u_viewTexel",
		"u_view",
		"u_viewProj",
		"u_viewProjX",
		"u_model",
		"u_modelViewProj",
		"u_modelViewProjX",
		"u_alphaRef",
	};

	PredefinedUniform::Enum nameToPredefinedUniformEnum(const char* _name)
	{
		for (uint32_t ii = 0; ii < PredefinedUniform::Count; ++ii)
		{
			if (0 == strcmp(_name, s_predefinedName[ii]) )
			{
				return PredefinedUniform::Enum(ii);
			}
		}

		return PredefinedUniform::Count;
	}

	void Frame::submit(uint8_t _id)
	{
		if (m_discard)
		{
			m_discard = false;
			return;
		}

		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= m_num)
		{
			++m_numDropped;
			return;
		}

		m_key.m_view = _id;
		m_key.m_seq = s_ctx.m_seq[_id] & s_ctx.m_seqMask[_id];
		s_ctx.m_seq[_id]++;
		uint64_t key = m_key.encode();
		m_sortKeys[m_num] = key;
		m_sortValues[m_num] = m_numRenderStates;
		++m_num;

		m_state.m_constEnd = m_constantBuffer->getPos();
		m_state.m_flags |= m_flags;
		m_renderState[m_numRenderStates] = m_state;
		++m_numRenderStates;
		m_state.clear();
		m_flags = BGFX_STATE_NONE;
	}

	void Frame::submitMask(uint32_t _viewMask)
	{
		if (m_discard)
		{
			m_discard = false;
			return;
		}

		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= m_num)
		{
			m_numDropped += uint32_cntbits(_viewMask);
			return;
		}

		for (uint32_t id = 0, viewMask = _viewMask, ntz = uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = uint32_cnttz(viewMask) )
		{
			viewMask >>= ntz;
			id += ntz;

			m_key.m_view = id;
			m_key.m_seq = s_ctx.m_seq[id] & s_ctx.m_seqMask[id];
			s_ctx.m_seq[id]++;
			uint64_t key = m_key.encode();
			m_sortKeys[m_num] = key;
			m_sortValues[m_num] = m_numRenderStates;
			++m_num;
		}
		
		m_state.m_constEnd = m_constantBuffer->getPos();
		m_state.m_flags |= m_flags;
		m_renderState[m_numRenderStates] = m_state;
		++m_numRenderStates;
		m_state.clear();
		m_flags = BGFX_STATE_NONE;
	}

	void Frame::sort()
	{
		bx::radixSort64(m_sortKeys, s_ctx.m_tempKeys, m_sortValues, s_ctx.m_tempValues, m_num);
	}

	RendererType::Enum getRendererType()
	{
#if BGFX_CONFIG_RENDERER_DIRECT3D
		return RendererType::Direct3D9;
#elif BGFX_CONFIG_RENDERER_OPENGL
		return RendererType::OpenGL;
#elif BGFX_CONFIG_RENDERER_OPENGLES
		return RendererType::OpenGLES;
#else
		return RendererType::Null;
#endif // BGFX_CONFIG_RENDERER_
	}

	void init(bool _createRenderThread, fatalFn _fatal, reallocFn _realloc, freeFn _free, cacheFn _cache)
	{
		if (NULL != _fatal)
		{
			g_fatal = _fatal;
		}

		if (NULL != _realloc
		&&  NULL != _free)
		{
			g_realloc = _realloc;
			g_free = _free;
		}

		if (NULL != _cache)
		{
			g_cache = _cache;
		}

		s_threadIndex = BGFX_MAIN_THREAD_MAGIC;
		s_ctx.init(_createRenderThread);
	}

	void shutdown()
	{
		BGFX_MAIN_THREAD();
		s_ctx.shutdown();
	}

	void reset(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BGFX_MAIN_THREAD();
		s_ctx.reset(_width, _height, _flags);
	}

	void frame()
	{
		BGFX_MAIN_THREAD();
		s_ctx.frame();
	}

	bool renderFrame()
	{
		BGFX_RENDER_THREAD();
		return s_ctx.renderFrame();
	}

	static const uint32_t s_attribTypeSize[AttribType::Count] =
	{
		1,
		2,
		4,
	};

	void VertexDecl::begin()
	{
		m_hash = 0;
		m_stride = 0;
		memset(m_attributes, 0xff, sizeof(m_attributes) );
		memset(m_offset, 0, sizeof(m_offset) );
	}

	void VertexDecl::end()
	{
		m_hash = hash(m_attributes, sizeof(m_attributes) );
	}

	void VertexDecl::add(Attrib::Enum _attrib, uint8_t _num, AttribType::Enum _type, bool _normalized)
	{
		const uint8_t encoded_norm = (_normalized&1)<<6;
		const uint8_t encoded_type = (_type&3)<<3;
		const uint8_t encoded_num = (_num-1)&3;

		m_attributes[_attrib] = encoded_norm|encoded_type|encoded_num;
		m_offset[_attrib] = m_stride;
		m_stride += s_attribTypeSize[_type]*_num;
	}

	void VertexDecl::decode(Attrib::Enum _attrib, uint8_t& _num, AttribType::Enum& _type, bool& _normalized) const
	{
		uint8_t val = m_attributes[_attrib];
		_num = (val&3)+1;
		_type = AttribType::Enum((val>>3)&3);
		_normalized = !!(val&(1<<6) );
	}

	const char* getAttribName(Attrib::Enum _attr)
	{
		static const char* attrName[Attrib::Count] = 
		{
			"Attrib::Position",
			"Attrib::Normal",
			"Attrib::Color0",
			"Attrib::Color1",
			"Attrib::Indices",
			"Attrib::Weights",
			"Attrib::TexCoord0",
			"Attrib::TexCoord1",
			"Attrib::TexCoord2",
			"Attrib::TexCoord3",
			"Attrib::TexCoord4",
			"Attrib::TexCoord5",
			"Attrib::TexCoord6",
			"Attrib::TexCoord7",
		};

		return attrName[_attr];
	}

	void dump(const VertexDecl& _decl)
	{
#if BGFX_CONFIG_DEBUG
		BX_TRACE("vertexdecl %08x (%08x), stride %d"
			, _decl.m_hash
			, hash(_decl.m_attributes, sizeof(_decl.m_attributes) )
			, _decl.m_stride
			);

		for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
		{
			if (0xff != _decl.m_attributes[attr])
			{
				uint8_t num;
				AttribType::Enum type;
				bool normalized;
				_decl.decode(Attrib::Enum(attr), num, type, normalized);

				BX_TRACE("\tattr %d - %s, num %d, type %d, norm %d, offset %d"
					, attr
					, getAttribName(Attrib::Enum(attr) )
					, num
					, type
					, normalized
					, _decl.m_offset[attr]
				);
			}
		}
#endif // BGFX_CONFIG_DEBUG
	}

	const uint32_t g_constantTypeSize[ConstantType::Count] =
	{
		sizeof(int32_t),
		sizeof(float),
		0,
		1*sizeof(int32_t),
		1*sizeof(float),
		2*sizeof(float),
		3*sizeof(float),
		4*sizeof(float),
		3*3*sizeof(float),
		4*4*sizeof(float),
	};

	void ConstantBuffer::writeUniform(ConstantType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num)
	{
		uint32_t opcode = encodeOpcode(_type, _loc, _num, true);
		write(opcode);
		write(_value, g_constantTypeSize[_type]*_num);
	}

	void ConstantBuffer::writeUniformRef(ConstantType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num)
	{
		uint32_t opcode = encodeOpcode(_type, _loc, _num, false);
		write(opcode);
		write(&_value, sizeof(void*) );
	}

#if BX_PLATFORM_WINDOWS
	LRESULT CALLBACK Context::Window::wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
	{
		return s_ctx.m_window.process(_hwnd, _id, _wparam, _lparam);
	}
#endif // BX_PLATFORM_WINDOWS

	void Context::init(bool _createRenderThread)
	{
		BX_TRACE("init");

		m_submit->create();
		m_render->create();

#if BX_PLATFORM_WINDOWS
		m_window.init();
#endif // BX_PLATFORM_

#if BGFX_CONFIG_MULTITHREADED
		m_renderThread = 0;

		if (_createRenderThread)
		{
#	if BX_PLATFORM_WINDOWS|BX_PLATFORM_XBOX360
			m_renderThread = CreateThread(NULL, 16<<10, renderThread, NULL, 0, NULL);
#	elif BX_PLATFORM_LINUX
			pthread_create(&m_renderThread, NULL, renderThread, NULL);
#	endif // BX_PLATFORM_
		}
#endif // BGFX_CONFIG_MULTITHREADED

		memset(m_rt, 0xff, sizeof(m_rt) );
		memset(m_clear, 0, sizeof(m_clear) );
		memset(m_rect, 0, sizeof(m_rect) );
		memset(m_seq, 0, sizeof(m_seq) );
		memset(m_seqMask, 0, sizeof(m_seqMask) );

		gameSemPost();

		getCommandBuffer(CommandBuffer::RendererInit);

		m_textVideoMemBlitter.init();

		m_submit->m_transientVb = createTransientVertexBuffer(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
		m_submit->m_transientIb = createTransientIndexBuffer(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
		frame();
		m_submit->m_transientVb = createTransientVertexBuffer(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
		m_submit->m_transientIb = createTransientIndexBuffer(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
		frame();
	}

	void Context::shutdown()
	{
		BX_TRACE("shutdown");

		getCommandBuffer(CommandBuffer::RendererShutdown);
		frame();

#if BGFX_CONFIG_MULTITHREADED
		if (0 != m_renderThread)
		{
#	if BX_PLATFORM_WINDOWS|BX_PLATFORM_XBOX360
			WaitForSingleObject(m_renderThread, INFINITE);
			m_renderThread = NULL;
#	elif BX_PLATFORM_LINUX
			pthread_join(m_renderThread, NULL);
			m_renderThread = 0;
#	endif // BX_PLATFORM_*
		}
#endif // BGFX_CONFIG_MULTITHREADED

		m_submit->destroy();
		m_render->destroy();
	}

#if BX_PLATFORM_WINDOWS|BX_PLATFORM_XBOX360
	DWORD WINAPI renderThread(LPVOID)
#else
	void* renderThread(void*)
#endif // BX_PLATFORM_WINDOWS
	{
		while (!renderFrame() );
		return EXIT_SUCCESS;
	}

	const Memory* alloc(uint32_t _size)
	{
		Memory* mem = (Memory*)g_realloc(NULL, sizeof(Memory) + _size);
		mem->size = _size;
		mem->data = (uint8_t*)mem + sizeof(Memory);
		return mem;
	}

	const Memory* makeRef(void* _data, uint32_t _size)
	{
		Memory* mem = (Memory*)g_realloc(NULL, sizeof(Memory) );
		mem->size = _size;
		mem->data = (uint8_t*)_data;
		return mem;
	}

	void release(Memory* _mem)
	{
		g_free(_mem);
	}

	void setDebug(uint32_t _debug)
	{
		s_ctx.m_debug = _debug;
	}

	void dbgTextClear(uint8_t _attr, bool _small)
	{
		s_ctx.dbgTextClear(_attr, _small);
	}

	void dbgTextPrintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);
		s_ctx.dbgTextPrintfVargs(_x, _y, _attr, _format, argList);
		va_end(argList);
	}

	IndexBufferHandle createIndexBuffer(const Memory* _mem)
	{
		return s_ctx.createIndexBuffer(_mem);
	}

	void destroyIndexBuffer(IndexBufferHandle _handle)
	{
		s_ctx.destroyIndexBuffer(_handle);
	}

	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl)
	{
		return s_ctx.createVertexBuffer(_mem, _decl);
	}

	void destroyVertexBuffer(VertexBufferHandle _handle)
	{
		s_ctx.destroyVertexBuffer(_handle);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(uint16_t _num)
	{
		return s_ctx.createDynamicIndexBuffer(_num);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem)
	{
		return s_ctx.createDynamicIndexBuffer(_mem);
	}

	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, const Memory* _mem)
	{
		s_ctx.updateDynamicIndexBuffer(_handle, _mem);
	}

	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		s_ctx.destroyDynamicIndexBuffer(_handle);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(uint16_t _num, const VertexDecl& _decl)
	{
		return s_ctx.createDynamicVertexBuffer(_num, _decl);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl)
	{
		return s_ctx.createDynamicVertexBuffer(_mem, _decl);
	}

	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, const Memory* _mem)
	{
		s_ctx.updateDynamicVertexBuffer(_handle, _mem);
	}

	void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle)
	{
		s_ctx.destroyDynamicVertexBuffer(_handle);
	}

	bool checkAvailTransientIndexBuffer(uint16_t _num)
	{
		return s_ctx.m_submit->checkAvailTransientIndexBuffer(_num);
	}

	const TransientIndexBuffer* allocTransientIndexBuffer(uint16_t _num)
	{
		return s_ctx.allocTransientIndexBuffer(_num);
	}

	bool checkAvailTransientVertexBuffer(uint16_t _num, const VertexDecl& _decl)
	{
		return s_ctx.m_submit->checkAvailTransientVertexBuffer(_num, _decl.m_stride);
	}

	const TransientVertexBuffer* allocTransientVertexBuffer(uint16_t _num, const VertexDecl& _decl)
	{
		return s_ctx.allocTransientVertexBuffer(_num, _decl);
	}

	VertexShaderHandle createVertexShader(const Memory* _mem)
	{
		return s_ctx.createVertexShader(_mem);
	}

	void destroyVertexShader(VertexShaderHandle _handle)
	{
		s_ctx.destroyVertexShader(_handle);
	}

	FragmentShaderHandle createFragmentShader(const Memory* _mem)
	{
		return s_ctx.createFragmentShader(_mem);
	}

	void destroyFragmentShader(FragmentShaderHandle _handle)
	{
		s_ctx.destroyFragmentShader(_handle);
	}

	MaterialHandle createMaterial(VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		return s_ctx.createMaterial(_vsh, _fsh);
	}

	void destroyMaterial(MaterialHandle _handle)
	{
		s_ctx.destroyMaterial(_handle);
	}

	TextureHandle createTexture(const Memory* _mem, uint32_t _flags, uint16_t* _width, uint16_t* _height)
	{
		return s_ctx.createTexture(_mem, _flags, _width, _height);
	}

	void destroyTexture(TextureHandle _handle)
	{
		s_ctx.destroyTexture(_handle);
	}

	RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		return s_ctx.createRenderTarget(_width, _height, _flags, _textureFlags);
	}

	void destroyRenderTarget(RenderTargetHandle _handle)
	{
		s_ctx.destroyRenderTarget(_handle);
	}

	UniformHandle createUniform(const char* _name, ConstantType::Enum _type, uint16_t _num)
	{
		return s_ctx.createUniform(_name, _type, _num);
	}

	void destroyUniform(UniformHandle _handle)
	{
		s_ctx.destroyUniform(_handle);
	}

	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		s_ctx.setViewRect(_id, _x, _y, _width, _height);
	}

	void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		s_ctx.setViewRectMask(_viewMask, _x, _y, _width, _height);
	}

	void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		s_ctx.setViewClear(_id, _flags, _rgba, _depth, _stencil);
	}

	void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		s_ctx.setViewClearMask(_viewMask, _flags, _rgba, _depth, _stencil);
	}

	void setViewSeq(uint8_t _id, bool _enabled)
	{
		s_ctx.setViewSeq(_id, _enabled);
	}

	void setViewSeqMask(uint32_t _viewMask, bool _enabled)
	{
		s_ctx.setViewSeqMask(_viewMask, _enabled);
	}

	void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle)
	{
		s_ctx.setViewRenderTarget(_id, _handle);
	}

	void setViewRenderTargetMask(uint32_t _mask, RenderTargetHandle _handle)
	{
		s_ctx.setViewRenderTargetMask(_mask, _handle);
	}

	void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other)
	{
		s_ctx.m_submit->setViewTransform(_id, _view, _proj, _other);
	}

	void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other)
	{
		s_ctx.m_submit->setViewTransformMask(_viewMask, _view, _proj, _other);
	}

	void setState(uint64_t _state)
	{
		s_ctx.m_submit->setState(_state);
	}

	uint32_t setTransform(const void* _mtx, uint16_t _num)
	{
		return s_ctx.m_submit->setTransform(_mtx, _num);
	}

	void setTransform(uint32_t _cache, uint16_t _num)
	{
		s_ctx.m_submit->setTransform(_cache, _num);
	}

	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num)
	{
		s_ctx.setUniform(_handle, _value, _num);
	}

	void setUniform(MaterialHandle _material, UniformHandle _handle, const void* _value)
	{
		s_ctx.setUniform(_material, _handle, _value);
	}

	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		s_ctx.m_submit->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(IndexBufferHandle _handle)
	{
		s_ctx.m_submit->setIndexBuffer(_handle, BGFX_DRAW_WHOLE_INDEX_BUFFER, 0);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		s_ctx.m_submit->setIndexBuffer(s_ctx.m_dynamicIndexBuffers[_handle.idx].m_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		s_ctx.m_submit->setIndexBuffer(s_ctx.m_dynamicIndexBuffers[_handle.idx].m_handle, BGFX_DRAW_WHOLE_INDEX_BUFFER, 0);
	}

	void setIndexBuffer(const TransientIndexBuffer* _ib, uint32_t _numIndices)
	{
		uint32_t numIndices = uint32_min(_numIndices, _ib->size/2);
		s_ctx.m_submit->setIndexBuffer(_ib, numIndices);
	}

	void setVertexBuffer(VertexBufferHandle _handle)
	{
		s_ctx.m_submit->setVertexBuffer(_handle);
	}

	void setVertexBuffer(DynamicVertexBufferHandle _handle)
	{
		s_ctx.m_submit->setVertexBuffer(s_ctx.m_dynamicVertexBuffers[_handle.idx]);
	}

	void setVertexBuffer(const TransientVertexBuffer* _vb)
	{
		s_ctx.m_submit->setVertexBuffer(_vb);
	}

	void setMaterial(MaterialHandle _handle)
	{
		s_ctx.m_submit->setMaterial(_handle);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle)
	{
		s_ctx.m_submit->setTexture(_stage, _sampler, _handle);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth)
	{
		s_ctx.m_submit->setTexture(_stage, _sampler, _handle, _depth);
	}

	void submit(uint8_t _id)
	{
		s_ctx.m_submit->submit(_id);
	}

	void submitMask(uint32_t _viewMask)
	{
		s_ctx.m_submit->submitMask(_viewMask);
	}

	void saveScreenShot(const char* _filePath)
	{
		uint32_t len = (uint32_t)strlen(_filePath)+1;
		const Memory* mem = alloc(len);
		memcpy(mem->data, _filePath, mem->size);
		return s_ctx.saveScreenShot(mem);
	}
}
