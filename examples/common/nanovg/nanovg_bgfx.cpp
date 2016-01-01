/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

//
// Copyright (c) 2009-2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
#define NVG_ANTIALIAS 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "nanovg.h"

#include <bgfx/bgfx.h>

#include <bx/bx.h>

BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4244); // warning C4244: '=' : conversion from '' to '', possible loss of data

namespace
{
#include "vs_nanovg_fill.bin.h"
#include "fs_nanovg_fill.bin.h"

	static bgfx::VertexDecl s_nvgDecl;

	enum GLNVGshaderType
	{
		NSVG_SHADER_FILLGRAD,
		NSVG_SHADER_FILLIMG,
		NSVG_SHADER_SIMPLE,
		NSVG_SHADER_IMG
	};

	// These are additional flags on top of NVGimageFlags.
	enum NVGimageFlagsGL {
		NVG_IMAGE_NODELETE = 1<<16, // Do not delete GL texture handle.
	};

	struct GLNVGtexture
	{
		bgfx::TextureHandle id;
		int width, height;
		int type;
		int flags;
	};

	enum GLNVGcallType
	{
		GLNVG_FILL,
		GLNVG_CONVEXFILL,
		GLNVG_STROKE,
		GLNVG_TRIANGLES,
	};

	struct GLNVGcall
	{
		int type;
		int image;
		int pathOffset;
		int pathCount;
		int vertexOffset;
		int vertexCount;
		int uniformOffset;
	};

	struct GLNVGpath
	{
		int fillOffset;
		int fillCount;
		int strokeOffset;
		int strokeCount;
	};

	struct GLNVGfragUniforms
	{
		float scissorMat[12]; // matrices are actually 3 vec4s
		float paintMat[12];
		NVGcolor innerCol;
		NVGcolor outerCol;

		// u_scissorExtScale
		float scissorExt[2];
		float scissorScale[2];

		// u_extentRadius
		float extent[2];
		float radius;

		// u_params
		float feather;
		float strokeMult;
		float texType;
		float type;
	};

	struct GLNVGcontext
	{
		bgfx::ProgramHandle prog;
		bgfx::UniformHandle u_scissorMat;
		bgfx::UniformHandle u_paintMat;
		bgfx::UniformHandle u_innerCol;
		bgfx::UniformHandle u_outerCol;
		bgfx::UniformHandle u_viewSize;
		bgfx::UniformHandle u_scissorExtScale;
		bgfx::UniformHandle u_extentRadius;
		bgfx::UniformHandle u_params;
		bgfx::UniformHandle u_halfTexel;

		bgfx::UniformHandle s_tex;

		uint64_t state;
		bgfx::TextureHandle th;

		bgfx::TransientVertexBuffer tvb;
		uint8_t viewid;

		struct GLNVGtexture* textures;
		float view[2];
		int ntextures;
		int ctextures;
		int textureId;
		int vertBuf;
		int fragSize;
		int edgeAntiAlias;

		// Per frame buffers
		struct GLNVGcall* calls;
		int ccalls;
		int ncalls;
		struct GLNVGpath* paths;
		int cpaths;
		int npaths;
		struct NVGvertex* verts;
		int cverts;
		int nverts;
		unsigned char* uniforms;
		int cuniforms;
		int nuniforms;
	};

	static struct GLNVGtexture* glnvg__allocTexture(struct GLNVGcontext* gl)
	{
		struct GLNVGtexture* tex = NULL;
		int i;

		for (i = 0; i < gl->ntextures; i++)
		{
			if (gl->textures[i].id.idx == bgfx::invalidHandle)
			{
				tex = &gl->textures[i];
				break;
			}
		}

		if (tex == NULL)
		{
			if (gl->ntextures+1 > gl->ctextures)
			{
				int old = gl->ctextures;
				gl->ctextures = (gl->ctextures == 0) ? 2 : gl->ctextures*2;
				gl->textures = (struct GLNVGtexture*)realloc(gl->textures, sizeof(struct GLNVGtexture)*gl->ctextures);
				memset(&gl->textures[old], 0xff, (gl->ctextures-old)*sizeof(struct GLNVGtexture) );

				if (gl->textures == NULL)
				{
					return NULL;
				}
			}
			tex = &gl->textures[gl->ntextures++];
		}

		memset(tex, 0, sizeof(*tex) );

		return tex;
	}

	static struct GLNVGtexture* glnvg__findTexture(struct GLNVGcontext* gl, int id)
	{
		int i;
		for (i = 0; i < gl->ntextures; i++)
		{
			if (gl->textures[i].id.idx == id)
			{
				return &gl->textures[i];
			}
		}

		return NULL;
	}

	static int glnvg__deleteTexture(struct GLNVGcontext* gl, int id)
	{
		for (int ii = 0; ii < gl->ntextures; ii++)
		{
			if (gl->textures[ii].id.idx == id)
			{
				if (bgfx::isValid(gl->textures[ii].id)
				&& (gl->textures[ii].flags & NVG_IMAGE_NODELETE) == 0)
				{
					bgfx::destroyTexture(gl->textures[ii].id);
				}
				memset(&gl->textures[ii], 0, sizeof(gl->textures[ii]) );
				gl->textures[ii].id.idx = bgfx::invalidHandle;
				return 1;
			}
		}

		return 0;
	}

	static int nvgRenderCreate(void* _userPtr)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;

		const bgfx::Memory* vs_nanovg_fill;
		const bgfx::Memory* fs_nanovg_fill;

		switch (bgfx::getRendererType() )
		{
		case bgfx::RendererType::Direct3D9:
			vs_nanovg_fill = bgfx::makeRef(vs_nanovg_fill_dx9, sizeof(vs_nanovg_fill_dx9) );
			fs_nanovg_fill = bgfx::makeRef(fs_nanovg_fill_dx9, sizeof(fs_nanovg_fill_dx9) );
			break;

		case bgfx::RendererType::Direct3D11:
		case bgfx::RendererType::Direct3D12:
			vs_nanovg_fill = bgfx::makeRef(vs_nanovg_fill_dx11, sizeof(vs_nanovg_fill_dx11) );
			fs_nanovg_fill = bgfx::makeRef(fs_nanovg_fill_dx11, sizeof(fs_nanovg_fill_dx11) );
			break;

		case bgfx::RendererType::Metal:
			vs_nanovg_fill = bgfx::makeRef(vs_nanovg_fill_mtl, sizeof(vs_nanovg_fill_mtl) );
			fs_nanovg_fill = bgfx::makeRef(fs_nanovg_fill_mtl, sizeof(fs_nanovg_fill_mtl) );
			break;

		default:
			vs_nanovg_fill = bgfx::makeRef(vs_nanovg_fill_glsl, sizeof(vs_nanovg_fill_glsl) );
			fs_nanovg_fill = bgfx::makeRef(fs_nanovg_fill_glsl, sizeof(fs_nanovg_fill_glsl) );
			break;
		}

		gl->prog = bgfx::createProgram(
						  bgfx::createShader(vs_nanovg_fill)
						, bgfx::createShader(fs_nanovg_fill)
						, true
						);

		gl->u_scissorMat      = bgfx::createUniform("u_scissorMat",      bgfx::UniformType::Mat3);
		gl->u_paintMat        = bgfx::createUniform("u_paintMat",        bgfx::UniformType::Mat3);
		gl->u_innerCol        = bgfx::createUniform("u_innerCol",        bgfx::UniformType::Vec4);
		gl->u_outerCol        = bgfx::createUniform("u_outerCol",        bgfx::UniformType::Vec4);
		gl->u_viewSize        = bgfx::createUniform("u_viewSize",        bgfx::UniformType::Vec4);
		gl->u_scissorExtScale = bgfx::createUniform("u_scissorExtScale", bgfx::UniformType::Vec4);
		gl->u_extentRadius    = bgfx::createUniform("u_extentRadius",    bgfx::UniformType::Vec4);
		gl->u_params          = bgfx::createUniform("u_params",          bgfx::UniformType::Vec4);
		gl->s_tex             = bgfx::createUniform("s_tex",             bgfx::UniformType::Int1);

		if (bgfx::getRendererType() == bgfx::RendererType::Direct3D9)
		{
			gl->u_halfTexel   = bgfx::createUniform("u_halfTexel",       bgfx::UniformType::Vec4);
		}
		else
		{
			gl->u_halfTexel.idx = bgfx::invalidHandle;
		}

		s_nvgDecl
			.begin()
			.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		int align = 16;
		gl->fragSize = sizeof(struct GLNVGfragUniforms) + align - sizeof(struct GLNVGfragUniforms) % align;

		return 1;
	}

	static int nvgRenderCreateTexture(void* _userPtr, int _type, int _width, int _height, int _flags, const unsigned char* _rgba)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;
		struct GLNVGtexture* tex = glnvg__allocTexture(gl);

		if (tex == NULL)
		{
			return 0;
		}

		tex->width  = _width;
		tex->height = _height;
		tex->type   = _type;
		tex->flags  = _flags;

		uint32_t bytesPerPixel = NVG_TEXTURE_RGBA == tex->type ? 4 : 1;
		uint32_t pitch = tex->width * bytesPerPixel;

		const bgfx::Memory* mem = NULL;
		if (NULL != _rgba)
		{
			mem = bgfx::copy(_rgba, tex->height * pitch);
		}

		tex->id = bgfx::createTexture2D(tex->width
						, tex->height
						, 1
						, NVG_TEXTURE_RGBA == _type ? bgfx::TextureFormat::RGBA8 : bgfx::TextureFormat::R8
						, BGFX_TEXTURE_NONE
						, mem
						);

		return bgfx::isValid(tex->id) ? tex->id.idx : 0;
	}

	static int nvgRenderDeleteTexture(void* _userPtr, int image)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;
		return glnvg__deleteTexture(gl, image);
	}

	static int nvgRenderUpdateTexture(void* _userPtr, int image, int x, int y, int w, int h, const unsigned char* data)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;
		struct GLNVGtexture* tex = glnvg__findTexture(gl, image);
		if (tex == NULL)
		{
			return 0;
		}

		uint32_t bytesPerPixel = NVG_TEXTURE_RGBA == tex->type ? 4 : 1;
		uint32_t pitch = tex->width * bytesPerPixel;

		bgfx::updateTexture2D(tex->id, 0, x, y, w, h
				, bgfx::copy(data + y*pitch + x*bytesPerPixel, h*pitch)
				, pitch
				);

		return 1;
	}

	static int nvgRenderGetTextureSize(void* _userPtr, int image, int* w, int* h)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;
		struct GLNVGtexture* tex = glnvg__findTexture(gl, image);

		if (!bgfx::isValid(tex->id) )
		{
			return 0;
		}

		*w = tex->width;
		*h = tex->height;

		return 1;
	}

	static void glnvg__xformIdentity(float* t)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	static void glnvg__xformInverse(float* inv, float* t)
	{
		double invdet, det = (double)t[0] * t[3] - (double)t[2] * t[1];
		if (det > -1e-6 && det < 1e-6) {
			glnvg__xformIdentity(t);
			return;
		}
		invdet = 1.0 / det;
		inv[0] = (float)(t[3] * invdet);
		inv[2] = (float)(-t[2] * invdet);
		inv[4] = (float)( ((double)t[2] * t[5] - (double)t[3] * t[4]) * invdet);
		inv[1] = (float)(-t[1] * invdet);
		inv[3] = (float)(t[0] * invdet);
		inv[5] = (float)( ((double)t[1] * t[4] - (double)t[0] * t[5]) * invdet);
	}

	static void glnvg__xformToMat3x4(float* m3, float* t)
	{
		m3[0] = t[0];
		m3[1] = t[1];
		m3[2] = 0.0f;
		m3[3] = 0.0f;
		m3[4] = t[2];
		m3[5] = t[3];
		m3[6] = 0.0f;
		m3[7] = 0.0f;
		m3[8] = t[4];
		m3[9] = t[5];
		m3[10] = 1.0f;
		m3[11] = 0.0f;
	}

	static int glnvg__convertPaint(struct GLNVGcontext* gl, struct GLNVGfragUniforms* frag, struct NVGpaint* paint,
								   struct NVGscissor* scissor, float width, float fringe)
	{
		struct GLNVGtexture* tex = NULL;
		float invxform[6] = {};

		memset(frag, 0, sizeof(*frag) );

		frag->innerCol = paint->innerColor;
		frag->outerCol = paint->outerColor;

		glnvg__xformInverse(invxform, paint->xform);
		glnvg__xformToMat3x4(frag->paintMat, invxform);

		if (scissor->extent[0] < 0.5f || scissor->extent[1] < 0.5f)
		{
			memset(frag->scissorMat, 0, sizeof(frag->scissorMat) );
			frag->scissorExt[0] = 1.0f;
			frag->scissorExt[1] = 1.0f;
			frag->scissorScale[0] = 1.0f;
			frag->scissorScale[1] = 1.0f;
		}
		else
		{
			glnvg__xformInverse(invxform, scissor->xform);
			glnvg__xformToMat3x4(frag->scissorMat, invxform);
			frag->scissorExt[0] = scissor->extent[0];
			frag->scissorExt[1] = scissor->extent[1];
			frag->scissorScale[0] = sqrtf(scissor->xform[0]*scissor->xform[0] + scissor->xform[2]*scissor->xform[2]) / fringe;
			frag->scissorScale[1] = sqrtf(scissor->xform[1]*scissor->xform[1] + scissor->xform[3]*scissor->xform[3]) / fringe;
		}
		memcpy(frag->extent, paint->extent, sizeof(frag->extent) );
		frag->strokeMult = (width*0.5f + fringe*0.5f) / fringe;

		bgfx::TextureHandle invalid = BGFX_INVALID_HANDLE;
		gl->th = invalid;
		if (paint->image != 0)
		{
			tex = glnvg__findTexture(gl, paint->image);
			if (tex == NULL)
			{
				return 0;
			}
			frag->type = NSVG_SHADER_FILLIMG;
			frag->texType = tex->type == NVG_TEXTURE_RGBA ? 0.0f : 1.0f;
			gl->th = tex->id;
		}
		else
		{
			frag->type = NSVG_SHADER_FILLGRAD;
			frag->radius = paint->radius;
			frag->feather = paint->feather;
		}

		return 1;
	}

	static void glnvg__mat3(float* dst, float* src)
	{
		dst[0] = src[0];
		dst[1] = src[1];
		dst[2] = src[2];

		dst[3] = src[4];
		dst[4] = src[5];
		dst[5] = src[6];

		dst[6] = src[8];
		dst[7] = src[9];
		dst[8] = src[10];
	}

	static struct GLNVGfragUniforms* nvg__fragUniformPtr(struct GLNVGcontext* gl, int i)
	{
		return (struct GLNVGfragUniforms*)&gl->uniforms[i];
	}

	static void nvgRenderSetUniforms(struct GLNVGcontext* gl, int uniformOffset, int image)
	{
		struct GLNVGfragUniforms* frag = nvg__fragUniformPtr(gl, uniformOffset);
		float tmp[9]; // Maybe there's a way to get rid of this...
		glnvg__mat3(tmp, frag->scissorMat);
		bgfx::setUniform(gl->u_scissorMat, tmp);
		glnvg__mat3(tmp, frag->paintMat);
		bgfx::setUniform(gl->u_paintMat, tmp);

		bgfx::setUniform(gl->u_innerCol,        frag->innerCol.rgba);
		bgfx::setUniform(gl->u_outerCol,        frag->outerCol.rgba);
		bgfx::setUniform(gl->u_scissorExtScale, &frag->scissorExt[0]);
		bgfx::setUniform(gl->u_extentRadius,    &frag->extent[0]);
		bgfx::setUniform(gl->u_params,          &frag->feather);

		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

		if (image != 0)
		{
			struct GLNVGtexture* tex = glnvg__findTexture(gl, image);
			if (tex != NULL)
			{
				handle = tex->id;

				if (bgfx::isValid(gl->u_halfTexel) )
				{
					float halfTexel[4] = { 0.5f / tex->width, 0.5f / tex->height };
					bgfx::setUniform(gl->u_halfTexel, halfTexel);
				}
			}
		}

		gl->th = handle;
	}

	static void nvgRenderViewport(void* _userPtr, int width, int height)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;
		gl->view[0] = (float)width;
		gl->view[1] = (float)height;
		bgfx::setViewRect(gl->viewid, 0, 0, width, height);
	}

	static void fan(uint32_t _start, uint32_t _count)
	{
		uint32_t numTris = _count-2;
		bgfx::TransientIndexBuffer tib;
		bgfx::allocTransientIndexBuffer(&tib, numTris*3);
		uint16_t* data = (uint16_t*)tib.data;
		for (uint32_t ii = 0; ii < numTris; ++ii)
		{
			data[ii*3+0] = _start;
			data[ii*3+1] = _start + ii + 1;
			data[ii*3+2] = _start + ii + 2;
		}

		bgfx::setIndexBuffer(&tib);
	}

	static void glnvg__fill(struct GLNVGcontext* gl, struct GLNVGcall* call)
	{
		struct GLNVGpath* paths = &gl->paths[call->pathOffset];
		int i, npaths = call->pathCount;

		// set bindpoint for solid loc
		nvgRenderSetUniforms(gl, call->uniformOffset, 0);

		for (i = 0; i < npaths; i++)
		{
			if (2 < paths[i].fillCount)
			{
				bgfx::setState(0);
				bgfx::setStencil(0
					| BGFX_STENCIL_TEST_ALWAYS
					| BGFX_STENCIL_FUNC_RMASK(0xff)
					| BGFX_STENCIL_OP_FAIL_S_KEEP
					| BGFX_STENCIL_OP_FAIL_Z_KEEP
					| BGFX_STENCIL_OP_PASS_Z_INCR
					, 0
					| BGFX_STENCIL_TEST_ALWAYS
					| BGFX_STENCIL_FUNC_RMASK(0xff)
					| BGFX_STENCIL_OP_FAIL_S_KEEP
					| BGFX_STENCIL_OP_FAIL_Z_KEEP
					| BGFX_STENCIL_OP_PASS_Z_DECR
					);
				bgfx::setVertexBuffer(&gl->tvb);
				bgfx::setTexture(0, gl->s_tex, gl->th);
				fan(paths[i].fillOffset, paths[i].fillCount);
				bgfx::submit(gl->viewid, gl->prog);
			}
		}

		// Draw aliased off-pixels
		nvgRenderSetUniforms(gl, call->uniformOffset + gl->fragSize, call->image);

		if (gl->edgeAntiAlias)
		{
			// Draw fringes
			for (i = 0; i < npaths; i++)
			{
				bgfx::setState(gl->state
					| BGFX_STATE_PT_TRISTRIP
					);
				bgfx::setStencil(0
					| BGFX_STENCIL_TEST_EQUAL
					| BGFX_STENCIL_FUNC_RMASK(0xff)
					| BGFX_STENCIL_OP_FAIL_S_KEEP
					| BGFX_STENCIL_OP_FAIL_Z_KEEP
					| BGFX_STENCIL_OP_PASS_Z_KEEP
					);
				bgfx::setVertexBuffer(&gl->tvb, paths[i].strokeOffset, paths[i].strokeCount);
				bgfx::setTexture(0, gl->s_tex, gl->th);
				bgfx::submit(gl->viewid, gl->prog);
			}
		}

		// Draw fill
		bgfx::setState(gl->state);
		bgfx::setVertexBuffer(&gl->tvb, call->vertexOffset, call->vertexCount);
		bgfx::setTexture(0, gl->s_tex, gl->th);
		bgfx::setStencil(0
				| BGFX_STENCIL_TEST_NOTEQUAL
				| BGFX_STENCIL_FUNC_RMASK(0xff)
				| BGFX_STENCIL_OP_FAIL_S_ZERO
				| BGFX_STENCIL_OP_FAIL_Z_ZERO
				| BGFX_STENCIL_OP_PASS_Z_ZERO
				);
		bgfx::submit(gl->viewid, gl->prog);
	}

	static void glnvg__convexFill(struct GLNVGcontext* gl, struct GLNVGcall* call)
	{
		struct GLNVGpath* paths = &gl->paths[call->pathOffset];
		int i, npaths = call->pathCount;

		nvgRenderSetUniforms(gl, call->uniformOffset, call->image);

		for (i = 0; i < npaths; i++)
		{
			if (paths[i].fillCount == 0) continue;
			bgfx::setState(gl->state);
			bgfx::setVertexBuffer(&gl->tvb);
			bgfx::setTexture(0, gl->s_tex, gl->th);
			fan(paths[i].fillOffset, paths[i].fillCount);
			bgfx::submit(gl->viewid, gl->prog);
		}

		if (gl->edgeAntiAlias)
		{
			// Draw fringes
			for (i = 0; i < npaths; i++)
			{
				bgfx::setState(gl->state
					| BGFX_STATE_PT_TRISTRIP
					);
				bgfx::setVertexBuffer(&gl->tvb, paths[i].strokeOffset, paths[i].strokeCount);
				bgfx::setTexture(0, gl->s_tex, gl->th);
				bgfx::submit(gl->viewid, gl->prog);
			}
		}
	}

	static void glnvg__stroke(struct GLNVGcontext* gl, struct GLNVGcall* call)
	{
		struct GLNVGpath* paths = &gl->paths[call->pathOffset];
		int npaths = call->pathCount, i;

		nvgRenderSetUniforms(gl, call->uniformOffset, call->image);

		// Draw Strokes
		for (i = 0; i < npaths; i++)
		{
			bgfx::setState(gl->state
				| BGFX_STATE_PT_TRISTRIP
				);
			bgfx::setVertexBuffer(&gl->tvb, paths[i].strokeOffset, paths[i].strokeCount);
			bgfx::setTexture(0, gl->s_tex, gl->th);
			bgfx::submit(gl->viewid, gl->prog);
		}
	}

	static void glnvg__triangles(struct GLNVGcontext* gl, struct GLNVGcall* call)
	{
		if (3 <= call->vertexCount)
		{
			nvgRenderSetUniforms(gl, call->uniformOffset, call->image);

			bgfx::setState(gl->state);
			bgfx::setVertexBuffer(&gl->tvb, call->vertexOffset, call->vertexCount);
			bgfx::setTexture(0, gl->s_tex, gl->th);
			bgfx::submit(gl->viewid, gl->prog);
		}
	}

	static void nvgRenderFlush(void* _userPtr)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;

		if (gl->ncalls > 0)
		{
			bgfx::allocTransientVertexBuffer(&gl->tvb, gl->nverts, s_nvgDecl);

			int allocated = gl->tvb.size/gl->tvb.stride;

			if (allocated < gl->nverts) {
				gl->nverts = allocated;
				BX_WARN(true, "Vertex number truncated due to transient vertex buffer overflow");
			}


			memcpy(gl->tvb.data, gl->verts, gl->nverts * sizeof(struct NVGvertex) );

			gl->state = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				;

// 			if (alphaBlend == NVG_PREMULTIPLIED_ALPHA)
// 			{
// 				gl->state |= BGFX_STATE_BLEND_FUNC_SEPARATE(
// 								  BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA
// 								, BGFX_STATE_BLEND_ONE,       BGFX_STATE_BLEND_INV_SRC_ALPHA
// 								);
// 			}
// 			else
			{
				gl->state |= BGFX_STATE_BLEND_FUNC(
								BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA
								);
			}

			bgfx::setUniform(gl->u_viewSize, gl->view);

			for (uint32_t ii = 0, num = gl->ncalls; ii < num; ++ii)
			{
				struct GLNVGcall* call = &gl->calls[ii];
				switch (call->type)
				{
				case GLNVG_FILL:
					glnvg__fill(gl, call);
					break;

				case GLNVG_CONVEXFILL:
					glnvg__convexFill(gl, call);
					break;

				case GLNVG_STROKE:
					glnvg__stroke(gl, call);
					break;

				case GLNVG_TRIANGLES:
					glnvg__triangles(gl, call);
					break;
				}
			}
		}

		// Reset calls
		gl->nverts    = 0;
		gl->npaths    = 0;
		gl->ncalls    = 0;
		gl->nuniforms = 0;
	}

	static int glnvg__maxVertCount(const struct NVGpath* paths, int npaths)
	{
		int i, count = 0;
		for (i = 0; i < npaths; i++)
		{
			count += paths[i].nfill;
			count += paths[i].nstroke;
		}
		return count;
	}

	static int glnvg__maxi(int a, int b) { return a > b ? a : b; }

	static struct GLNVGcall* glnvg__allocCall(struct GLNVGcontext* gl)
	{
		struct GLNVGcall* ret = NULL;
		if (gl->ncalls+1 > gl->ccalls)
		{
			gl->ccalls = gl->ccalls == 0 ? 32 : gl->ccalls * 2;
			gl->calls = (struct GLNVGcall*)realloc(gl->calls, sizeof(struct GLNVGcall) * gl->ccalls);
		}
		ret = &gl->calls[gl->ncalls++];
		memset(ret, 0, sizeof(struct GLNVGcall) );
		return ret;
	}

	static int glnvg__allocPaths(struct GLNVGcontext* gl, int n)
	{
		int ret = 0;
		if (gl->npaths + n > gl->cpaths) {
			GLNVGpath* paths;
			int cpaths = glnvg__maxi(gl->npaths + n, 128) + gl->cpaths / 2; // 1.5x Overallocate
			paths = (GLNVGpath*)realloc(gl->paths, sizeof(GLNVGpath) * cpaths);
			if (paths == NULL) return -1;
			gl->paths = paths;
			gl->cpaths = cpaths;
		}
		ret = gl->npaths;
		gl->npaths += n;
		return ret;
	}

	static int glnvg__allocVerts(GLNVGcontext* gl, int n)
	{
		int ret = 0;
		if (gl->nverts+n > gl->cverts)
		{
			NVGvertex* verts;
			int cverts = glnvg__maxi(gl->nverts + n, 4096) + gl->cverts/2; // 1.5x Overallocate
			verts = (NVGvertex*)realloc(gl->verts, sizeof(NVGvertex) * cverts);
			if (verts == NULL) return -1;
			gl->verts = verts;
			gl->cverts = cverts;
		}
		ret = gl->nverts;
		gl->nverts += n;
		return ret;
	}

	static int glnvg__allocFragUniforms(struct GLNVGcontext* gl, int n)
	{
		int ret = 0, structSize = gl->fragSize;
		if (gl->nuniforms+n > gl->cuniforms)
		{
			gl->cuniforms = gl->cuniforms == 0 ? glnvg__maxi(n, 32) : gl->cuniforms * 2;
			gl->uniforms = (unsigned char*)realloc(gl->uniforms, gl->cuniforms * structSize);
		}
		ret = gl->nuniforms * structSize;
		gl->nuniforms += n;
		return ret;
	}

	static void glnvg__vset(struct NVGvertex* vtx, float x, float y, float u, float v)
	{
		vtx->x = x;
		vtx->y = y;
		vtx->u = u;
		vtx->v = v;
	}

	static void nvgRenderFill(void* _userPtr, struct NVGpaint* paint, struct NVGscissor* scissor, float fringe,
								  const float* bounds, const struct NVGpath* paths, int npaths)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;

		struct GLNVGcall* call = glnvg__allocCall(gl);
		struct NVGvertex* quad;
		struct GLNVGfragUniforms* frag;
		int i, maxverts, offset;

		call->type = GLNVG_FILL;
		call->pathOffset = glnvg__allocPaths(gl, npaths);
		call->pathCount = npaths;
		call->image = paint->image;

		if (npaths == 1 && paths[0].convex)
		{
			call->type = GLNVG_CONVEXFILL;
		}

		// Allocate vertices for all the paths.
		maxverts = glnvg__maxVertCount(paths, npaths) + 6;
		offset = glnvg__allocVerts(gl, maxverts);

		for (i = 0; i < npaths; i++)
		{
			struct GLNVGpath* copy = &gl->paths[call->pathOffset + i];
			const struct NVGpath* path = &paths[i];
			memset(copy, 0, sizeof(struct GLNVGpath) );
			if (path->nfill > 0)
			{
				copy->fillOffset = offset;
				copy->fillCount = path->nfill;
				memcpy(&gl->verts[offset], path->fill, sizeof(struct NVGvertex) * path->nfill);
				offset += path->nfill;
			}

			if (path->nstroke > 0)
			{
				copy->strokeOffset = offset;
				copy->strokeCount = path->nstroke;
				memcpy(&gl->verts[offset], path->stroke, sizeof(struct NVGvertex) * path->nstroke);
				offset += path->nstroke;
			}
		}

		// Quad
		call->vertexOffset = offset;
		call->vertexCount = 6;
		quad = &gl->verts[call->vertexOffset];
		glnvg__vset(&quad[0], bounds[0], bounds[3], 0.5f, 1.0f);
		glnvg__vset(&quad[1], bounds[2], bounds[3], 0.5f, 1.0f);
		glnvg__vset(&quad[2], bounds[2], bounds[1], 0.5f, 1.0f);

		glnvg__vset(&quad[3], bounds[0], bounds[3], 0.5f, 1.0f);
		glnvg__vset(&quad[4], bounds[2], bounds[1], 0.5f, 1.0f);
		glnvg__vset(&quad[5], bounds[0], bounds[1], 0.5f, 1.0f);

		// Setup uniforms for draw calls
		if (call->type == GLNVG_FILL)
		{
			call->uniformOffset = glnvg__allocFragUniforms(gl, 2);
			// Simple shader for stencil
			frag = nvg__fragUniformPtr(gl, call->uniformOffset);
			memset(frag, 0, sizeof(*frag) );
			frag->type = NSVG_SHADER_SIMPLE;
			// Fill shader
			glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset + gl->fragSize), paint, scissor, fringe, fringe);
		}
		else
		{
			call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
			// Fill shader
			glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, fringe, fringe);
		}
	}

	static void nvgRenderStroke(void* _userPtr, struct NVGpaint* paint, struct NVGscissor* scissor, float fringe,
									float strokeWidth, const struct NVGpath* paths, int npaths)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;

		struct GLNVGcall* call = glnvg__allocCall(gl);
		int i, maxverts, offset;

		call->type = GLNVG_STROKE;
		call->pathOffset = glnvg__allocPaths(gl, npaths);
		call->pathCount = npaths;
		call->image = paint->image;

		// Allocate vertices for all the paths.
		maxverts = glnvg__maxVertCount(paths, npaths);
		offset = glnvg__allocVerts(gl, maxverts);

		for (i = 0; i < npaths; i++)
		{
			struct GLNVGpath* copy = &gl->paths[call->pathOffset + i];
			const struct NVGpath* path = &paths[i];
			memset(copy, 0, sizeof(struct GLNVGpath) );
			if (path->nstroke)
			{
				copy->strokeOffset = offset;
				copy->strokeCount = path->nstroke;
				memcpy(&gl->verts[offset], path->stroke, sizeof(struct NVGvertex) * path->nstroke);
				offset += path->nstroke;
			}
		}

		// Fill shader
		call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
		glnvg__convertPaint(gl, nvg__fragUniformPtr(gl, call->uniformOffset), paint, scissor, strokeWidth, fringe);
	}

	static void nvgRenderTriangles(void* _userPtr, struct NVGpaint* paint, struct NVGscissor* scissor,
									   const struct NVGvertex* verts, int nverts)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;
		struct GLNVGcall* call = glnvg__allocCall(gl);
		struct GLNVGfragUniforms* frag;

		call->type = GLNVG_TRIANGLES;
		call->image = paint->image;

		// Allocate vertices for all the paths.
		call->vertexOffset = glnvg__allocVerts(gl, nverts);
		call->vertexCount = nverts;
		memcpy(&gl->verts[call->vertexOffset], verts, sizeof(struct NVGvertex) * nverts);

		// Fill shader
		call->uniformOffset = glnvg__allocFragUniforms(gl, 1);
		frag = nvg__fragUniformPtr(gl, call->uniformOffset);
		glnvg__convertPaint(gl, frag, paint, scissor, 1.0f, 1.0f);
		frag->type = NSVG_SHADER_IMG;
	}

	static void nvgRenderDelete(void* _userPtr)
	{
		struct GLNVGcontext* gl = (struct GLNVGcontext*)_userPtr;

		if (gl == NULL)
		{
			return;
		}

		bgfx::destroyProgram(gl->prog);

		bgfx::destroyUniform(gl->u_scissorMat);
		bgfx::destroyUniform(gl->u_paintMat);
		bgfx::destroyUniform(gl->u_innerCol);
		bgfx::destroyUniform(gl->u_outerCol);
		bgfx::destroyUniform(gl->u_viewSize);
		bgfx::destroyUniform(gl->u_scissorExtScale);
		bgfx::destroyUniform(gl->u_extentRadius);
		bgfx::destroyUniform(gl->u_params);
		bgfx::destroyUniform(gl->s_tex);

		if (bgfx::isValid(gl->u_halfTexel) )
		{
			bgfx::destroyUniform(gl->u_halfTexel);
		}

		for (uint32_t ii = 0, num = gl->ntextures; ii < num; ++ii)
		{
			if (bgfx::isValid(gl->textures[ii].id)
			&& (gl->textures[ii].flags & NVG_IMAGE_NODELETE) == 0)
			{
				bgfx::destroyTexture(gl->textures[ii].id);
			}
		}

		free(gl->textures);

		free(gl);
	}

} // namespace

NVGcontext* nvgCreate(int edgeaa, unsigned char viewid)
{
	struct NVGparams params;
	struct NVGcontext* ctx = NULL;
	struct GLNVGcontext* gl = (struct GLNVGcontext*)malloc(sizeof(struct GLNVGcontext) );
	if (gl == NULL) goto error;
	memset(gl, 0, sizeof(struct GLNVGcontext) );

	memset(&params, 0, sizeof(params) );
	params.renderCreate         = nvgRenderCreate;
	params.renderCreateTexture  = nvgRenderCreateTexture;
	params.renderDeleteTexture  = nvgRenderDeleteTexture;
	params.renderUpdateTexture  = nvgRenderUpdateTexture;
	params.renderGetTextureSize = nvgRenderGetTextureSize;
	params.renderViewport       = nvgRenderViewport;
	params.renderFlush          = nvgRenderFlush;
	params.renderFill           = nvgRenderFill;
	params.renderStroke         = nvgRenderStroke;
	params.renderTriangles      = nvgRenderTriangles;
	params.renderDelete         = nvgRenderDelete;
	params.userPtr = gl;
	params.edgeAntiAlias = edgeaa;

	gl->edgeAntiAlias = edgeaa;
	gl->viewid = uint8_t(viewid);

	ctx = nvgCreateInternal(&params);
	if (ctx == NULL) goto error;

	return ctx;

error:
	// 'gl' is freed by nvgDeleteInternal.
	if (ctx != NULL)
	{
		nvgDeleteInternal(ctx);
	}

	return NULL;
}

void nvgViewId(struct NVGcontext* ctx, unsigned char viewid)
{
	struct NVGparams* params = nvgInternalParams(ctx);
	struct GLNVGcontext* gl = (struct GLNVGcontext*)params->userPtr;
	gl->viewid = uint8_t(viewid);
}

void nvgDelete(struct NVGcontext* ctx)
{
	nvgDeleteInternal(ctx);
}
