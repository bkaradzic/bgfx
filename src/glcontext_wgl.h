/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_GLCONTEXT_WGL_H_HEADER_GUARD
#define BGFX_GLCONTEXT_WGL_H_HEADER_GUARD

#if BGFX_USE_WGL

#include <wgl/wglext.h>

namespace bgfx { namespace gl
{
typedef PROC (APIENTRYP PFNWGLGETPROCADDRESSPROC) (LPCSTR lpszProc);
typedef BOOL (APIENTRYP PFNWGLMAKECURRENTPROC) (HDC hdc, HGLRC hglrc);
typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTPROC) (HDC hdc);
typedef BOOL  (APIENTRYP PFNWGLDELETECONTEXTPROC) (HGLRC hglrc);
//
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *params);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble depth);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);

	extern PFNWGLGETPROCADDRESSPROC wglGetProcAddress;
	extern PFNWGLMAKECURRENTPROC wglMakeCurrent;
	extern PFNWGLCREATECONTEXTPROC wglCreateContext;
	extern PFNWGLDELETECONTEXTPROC wglDeleteContext;

	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
			: m_current(NULL)
			, m_opengl32dll(NULL)
			, m_context(NULL)
			, m_hdc(NULL)
		{
		}

		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, uint32_t _flags);

		uint64_t getCaps() const;
		SwapChainGL* createSwapChain(void* _nwh);
		void destroySwapChain(SwapChainGL*  _swapChain);
		void swap(SwapChainGL* _swapChain = NULL);
		void makeCurrent(SwapChainGL* _swapChain = NULL);

		void import();

		bool isValid() const
		{
			return NULL != m_context;
		}

		int32_t m_contextAttrs[9];
		int m_pixelFormat;
		PIXELFORMATDESCRIPTOR m_pfd;
		SwapChainGL* m_current;
		void* m_opengl32dll;
		HGLRC m_context;
		HDC m_hdc;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BGFX_USE_WGL

#endif // BGFX_GLCONTEXT_WGL_H_HEADER_GUARD
