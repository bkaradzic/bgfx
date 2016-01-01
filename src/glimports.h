/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#if !defined(GL_IMPORT) && !defined(GL_EXTENSION)
#	error GL_IMPORT or GL_EXTENSION must be defined!
#endif // !defined(GL_IMPORT) && !defined(GL_DEFINE)

#ifdef GL_EXTENSION
#	undef GL_IMPORT
#	define GL_IMPORT GL_EXTENSION
#else
#	if !BGFX_USE_GL_DYNAMIC_LIB
#		define GL_EXTENSION GL_IMPORT
#	else
#		define GL_EXTENSION(_optional, _proto, _func, _import)
#	endif // !BGFX_USE_GL_DYNAMIC_LIB
#endif // GL_EXTENSION

#ifndef GL_IMPORT_TYPEDEFS
#	define GL_IMPORT_TYPEDEFS 0
#endif // GL_IMPORT_TYPEDEFS

#define GL_IMPORT______(_optional, _proto, _func) GL_IMPORT(_optional, _proto, _func, _func)
#define GL_IMPORT_ANGLE(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## ANGLE)
#define GL_IMPORT_ARB__(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## ARB)
#define GL_IMPORT_EXT__(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## EXT)
#define GL_IMPORT_KHR__(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## KHR)
#define GL_IMPORT_NV___(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## NV)
#define GL_IMPORT_OES__(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## OES)
#define GL_IMPORT_____x(_optional, _proto, _func) GL_EXTENSION(_optional, _proto, _func, _func ## XXXXX)

#if GL_IMPORT_TYPEDEFS
typedef void           (GL_APIENTRYP GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void           (GL_APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void           (GL_APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void           (GL_APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void           (GL_APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void           (GL_APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void           (GL_APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void           (GL_APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, const GLchar *name);
typedef void           (GL_APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
typedef void           (GL_APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void           (GL_APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void           (GL_APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
typedef void           (GL_APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
typedef void           (GL_APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void           (GL_APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void           (GL_APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
typedef void           (GL_APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
typedef void           (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void           (GL_APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void           (GL_APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void           (GL_APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void           (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void           (GL_APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void           (GL_APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void           (GL_APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void           (GL_APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef GLenum         (GL_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
typedef void           (GL_APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void           (GL_APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void           (GL_APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble d);
typedef void           (GL_APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
typedef void           (GL_APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
typedef void           (GL_APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void           (GL_APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void           (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void           (GL_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void           (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void           (GL_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void           (GL_APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef GLuint         (GL_APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint         (GL_APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
typedef void           (GL_APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
typedef void           (GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void           (GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void           (GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef void           (GL_APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void           (GL_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint *framebuffers);
typedef void           (GL_APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void           (GL_APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
typedef void           (GL_APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint *renderbuffers);
typedef void           (GL_APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
typedef void           (GL_APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
typedef void           (GL_APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
typedef void           (GL_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void           (GL_APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
typedef void           (GL_APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
typedef void           (GL_APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void           (GL_APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
typedef void           (GL_APIENTRYP PFNGLDISABLEIPROC) (GLenum cap, GLuint index);
typedef void           (GL_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void           (GL_APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void           (GL_APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
typedef void           (GL_APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
typedef void           (GL_APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect);
typedef void           (GL_APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void           (GL_APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum mode);
typedef void           (GL_APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
typedef void           (GL_APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices);
typedef void           (GL_APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect);
typedef void           (GL_APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
typedef void           (GL_APIENTRYP PFNGLENABLEPROC) (GLenum cap);
typedef void           (GL_APIENTRYP PFNGLENABLEIPROC) (GLenum cap, GLuint index);
typedef void           (GL_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void           (GL_APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
typedef void           (GL_APIENTRYP PFNGLFINISHPROC) ();
typedef void           (GL_APIENTRYP PFNGLFLUSHPROC) ();
typedef void           (GL_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void           (GL_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void           (GL_APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void           (GL_APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef void           (GL_APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
typedef void           (GL_APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void           (GL_APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
typedef void           (GL_APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
typedef void           (GL_APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef void           (GL_APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void           (GL_APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef GLint          (GL_APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void           (GL_APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, GLvoid *img);
typedef GLuint         (GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint count, GLsizei bufsize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef GLenum         (GL_APIENTRYP PFNGLGETERRORPROC) (void);
typedef void           (GL_APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
typedef void           (GL_APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
typedef void           (GL_APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params);
typedef void           (GL_APIENTRYP PFNGLGETINTERNALFORMATI64VPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params);
typedef void           (GL_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void           (GL_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void           (GL_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, void **params);
typedef void           (GL_APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void           (GL_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void           (GL_APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void           (GL_APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint         (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void           (GL_APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params);
typedef void           (GL_APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef GLint          (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint          (GL_APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void           (GL_APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void           (GL_APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void           (GL_APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void           (GL_APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void           (GL_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
typedef void           (GL_APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);
typedef void           (GL_APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void           (GL_APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef const GLubyte* (GL_APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
typedef GLint          (GL_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void           (GL_APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void           (GL_APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void           (GL_APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
typedef void           (GL_APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void           (GL_APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void           (GL_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void           (GL_APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void           (GL_APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
typedef void           (GL_APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
typedef void           (GL_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void           (GL_APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void           (GL_APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint value);
typedef void           (GL_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void           (GL_APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void           (GL_APIENTRYP PFNGLREADBUFFERPROC) (GLenum mode);
typedef void           (GL_APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
typedef void           (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void           (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void           (GL_APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void           (GL_APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void           (GL_APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void           (GL_APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void           (GL_APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void           (GL_APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
typedef void           (GL_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void           (GL_APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
typedef void           (GL_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
typedef void           (GL_APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
typedef void           (GL_APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void           (GL_APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void           (GL_APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void           (GL_APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void           (GL_APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat* param);
typedef void           (GL_APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void           (GL_APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void           (GL_APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void           (GL_APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void           (GL_APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void           (GL_APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void           (GL_APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void           (GL_APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void           (GL_APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void           (GL_APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void           (GL_APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint divisor);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
typedef void           (GL_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void           (GL_APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);

typedef void           (GL_APIENTRYP PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef void           (GL_APIENTRYP PFNGLSTRINGMARKERGREMEDYPROC) (GLsizei len, const void *string);
typedef void           (GL_APIENTRYP PFNGLFRAMETERMINATORGREMEDYPROC) (void);

typedef void           (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void           (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void           (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (void);
#endif // GL_IMPORT_TYPEDEFS

#if BGFX_USE_GL_DYNAMIC_LIB
GL_IMPORT______(false, PFNGLACTIVETEXTUREPROC,                     glActiveTexture);
GL_IMPORT______(false, PFNGLATTACHSHADERPROC,                      glAttachShader);
GL_IMPORT______(true,  PFNGLBEGINQUERYPROC,                        glBeginQuery);
GL_IMPORT______(false, PFNGLBINDBUFFERPROC,                        glBindBuffer);
GL_IMPORT______(true,  PFNGLBINDBUFFERBASEPROC,                    glBindBufferBase);
GL_IMPORT______(true,  PFNGLBINDBUFFERRANGEPROC,                   glBindBufferRange);
GL_IMPORT______(true,  PFNGLBINDFRAGDATALOCATIONPROC,              glBindFragDataLocation);
GL_IMPORT______(true,  PFNGLBINDFRAMEBUFFERPROC,                   glBindFramebuffer);
GL_IMPORT______(true,  PFNGLBINDIMAGETEXTUREPROC,                  glBindImageTexture);
GL_IMPORT______(true,  PFNGLBINDRENDERBUFFERPROC,                  glBindRenderbuffer);
GL_IMPORT______(true,  PFNGLBINDSAMPLERPROC,                       glBindSampler);
GL_IMPORT______(false, PFNGLBINDTEXTUREPROC,                       glBindTexture);
GL_IMPORT______(true,  PFNGLBINDVERTEXARRAYPROC,                   glBindVertexArray);
GL_IMPORT______(true,  PFNGLBLENDCOLORPROC,                        glBlendColor);
GL_IMPORT______(false, PFNGLBLENDEQUATIONPROC,                     glBlendEquation);
GL_IMPORT______(true,  PFNGLBLENDEQUATIONIPROC,                    glBlendEquationi);
GL_IMPORT______(true,  PFNGLBLENDEQUATIONSEPARATEPROC,             glBlendEquationSeparate);
GL_IMPORT______(true,  PFNGLBLENDEQUATIONSEPARATEIPROC,            glBlendEquationSeparatei);
GL_IMPORT______(false, PFNGLBLENDFUNCPROC,                         glBlendFunc);
GL_IMPORT______(true,  PFNGLBLENDFUNCIPROC,                        glBlendFunci);
GL_IMPORT______(true,  PFNGLBLENDFUNCSEPARATEPROC,                 glBlendFuncSeparate);
GL_IMPORT______(true,  PFNGLBLENDFUNCSEPARATEIPROC,                glBlendFuncSeparatei);
GL_IMPORT______(true,  PFNGLBLITFRAMEBUFFERPROC,                   glBlitFramebuffer);
GL_IMPORT______(false, PFNGLBUFFERDATAPROC,                        glBufferData);
GL_IMPORT______(false, PFNGLBUFFERSUBDATAPROC,                     glBufferSubData);
GL_IMPORT______(true,  PFNGLCHECKFRAMEBUFFERSTATUSPROC,            glCheckFramebufferStatus);
GL_IMPORT______(false, PFNGLCLEARPROC,                             glClear);
GL_IMPORT______(true,  PFNGLCLEARBUFFERFVPROC,                     glClearBufferfv);
GL_IMPORT______(false, PFNGLCLEARCOLORPROC,                        glClearColor);
GL_IMPORT______(false, PFNGLCLEARSTENCILPROC,                      glClearStencil);
GL_IMPORT______(false, PFNGLCOLORMASKPROC,                         glColorMask);
GL_IMPORT______(false, PFNGLCOMPILESHADERPROC,                     glCompileShader);
GL_IMPORT______(false, PFNGLCOMPRESSEDTEXIMAGE2DPROC,              glCompressedTexImage2D);
GL_IMPORT______(false, PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC,           glCompressedTexSubImage2D);
GL_IMPORT______(true , PFNGLCOMPRESSEDTEXIMAGE3DPROC,              glCompressedTexImage3D);
GL_IMPORT______(true , PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,           glCompressedTexSubImage3D);
GL_IMPORT______(true , PFNGLCOPYIMAGESUBDATAPROC,                  glCopyImageSubData);
GL_IMPORT______(false, PFNGLCREATEPROGRAMPROC,                     glCreateProgram);
GL_IMPORT______(false, PFNGLCREATESHADERPROC,                      glCreateShader);
GL_IMPORT______(false, PFNGLCULLFACEPROC,                          glCullFace);
GL_IMPORT______(true,  PFNGLDEBUGMESSAGECONTROLPROC,               glDebugMessageControl);
GL_IMPORT______(true,  PFNGLDEBUGMESSAGEINSERTPROC,                glDebugMessageInsert);
GL_IMPORT______(true,  PFNGLDEBUGMESSAGECALLBACKPROC,              glDebugMessageCallback);
GL_IMPORT______(false, PFNGLDELETEBUFFERSPROC,                     glDeleteBuffers);
GL_IMPORT______(true,  PFNGLDELETEFRAMEBUFFERSPROC,                glDeleteFramebuffers);
GL_IMPORT______(false, PFNGLDELETEPROGRAMPROC,                     glDeleteProgram);
GL_IMPORT______(true,  PFNGLDELETEQUERIESPROC,                     glDeleteQueries);
GL_IMPORT______(true,  PFNGLDELETERENDERBUFFERSPROC,               glDeleteRenderbuffers);
GL_IMPORT______(true,  PFNGLDELETESAMPLERSPROC,                    glDeleteSamplers);
GL_IMPORT______(false, PFNGLDELETESHADERPROC,                      glDeleteShader);
GL_IMPORT______(false, PFNGLDELETETEXTURESPROC,                    glDeleteTextures);
GL_IMPORT______(true,  PFNGLDELETEVERTEXARRAYSPROC,                glDeleteVertexArrays);
GL_IMPORT______(false, PFNGLDEPTHFUNCPROC,                         glDepthFunc);
GL_IMPORT______(false, PFNGLDEPTHMASKPROC,                         glDepthMask);
GL_IMPORT______(false, PFNGLDETACHSHADERPROC,                      glDetachShader);
GL_IMPORT______(false, PFNGLDISABLEPROC,                           glDisable);
GL_IMPORT______(true,  PFNGLDISABLEIPROC,                          glDisablei);
GL_IMPORT______(false, PFNGLDISABLEVERTEXATTRIBARRAYPROC,          glDisableVertexAttribArray);
GL_IMPORT______(true,  PFNGLDISPATCHCOMPUTEPROC,                   glDispatchCompute);
GL_IMPORT______(true,  PFNGLDISPATCHCOMPUTEINDIRECTPROC,           glDispatchComputeIndirect);
GL_IMPORT______(false, PFNGLDRAWARRAYSPROC,                        glDrawArrays);
GL_IMPORT______(true,  PFNGLDRAWARRAYSINDIRECTPROC,                glDrawArraysIndirect);
GL_IMPORT______(true,  PFNGLDRAWARRAYSINSTANCEDPROC,               glDrawArraysInstanced);
GL_IMPORT______(true,  PFNGLDRAWBUFFERPROC,                        glDrawBuffer);
GL_IMPORT______(true,  PFNGLDRAWBUFFERSPROC,                       glDrawBuffers);
GL_IMPORT______(false, PFNGLDRAWELEMENTSPROC,                      glDrawElements);
GL_IMPORT______(true,  PFNGLDRAWELEMENTSINDIRECTPROC,              glDrawElementsIndirect);
GL_IMPORT______(true,  PFNGLDRAWELEMENTSINSTANCEDPROC,             glDrawElementsInstanced);
GL_IMPORT______(false, PFNGLENABLEPROC,                            glEnable);
GL_IMPORT______(true,  PFNGLENABLEIPROC,                           glEnablei);
GL_IMPORT______(false, PFNGLENABLEVERTEXATTRIBARRAYPROC,           glEnableVertexAttribArray);
GL_IMPORT______(true,  PFNGLENDQUERYPROC,                          glEndQuery);
GL_IMPORT______(false, PFNGLFINISHPROC,                            glFinish);
GL_IMPORT______(false, PFNGLFLUSHPROC,                             glFlush);
GL_IMPORT______(true,  PFNGLFRAMEBUFFERRENDERBUFFERPROC,           glFramebufferRenderbuffer);
GL_IMPORT______(true,  PFNGLFRAMEBUFFERTEXTURE2DPROC,              glFramebufferTexture2D);
GL_IMPORT______(false, PFNGLGENBUFFERSPROC,                        glGenBuffers);
GL_IMPORT______(true,  PFNGLGENFRAMEBUFFERSPROC,                   glGenFramebuffers);
GL_IMPORT______(true,  PFNGLGENRENDERBUFFERSPROC,                  glGenRenderbuffers);
GL_IMPORT______(true,  PFNGLGENQUERIESPROC,                        glGenQueries);
GL_IMPORT______(true,  PFNGLGENSAMPLERSPROC,                       glGenSamplers);
GL_IMPORT______(false, PFNGLGENTEXTURESPROC,                       glGenTextures);
GL_IMPORT______(true,  PFNGLGENVERTEXARRAYSPROC,                   glGenVertexArrays);
GL_IMPORT______(false, PFNGLGETACTIVEATTRIBPROC,                   glGetActiveAttrib);
GL_IMPORT______(false, PFNGLGETATTRIBLOCATIONPROC,                 glGetAttribLocation);
GL_IMPORT______(false, PFNGLGETACTIVEUNIFORMPROC,                  glGetActiveUniform);
GL_IMPORT______(true,  PFNGLGETCOMPRESSEDTEXIMAGEPROC,             glGetCompressedTexImage);
GL_IMPORT______(true,  PFNGLGETDEBUGMESSAGELOGPROC,                glGetDebugMessageLog);
GL_IMPORT______(false, PFNGLGETERRORPROC,                          glGetError);
GL_IMPORT______(false, PFNGLGETFLOATVPROC,                         glGetFloatv);
GL_IMPORT______(false, PFNGLGETINTEGERVPROC,                       glGetIntegerv);
GL_IMPORT______(true,  PFNGLGETINTERNALFORMATIVPROC,               glGetInternalformativ);
GL_IMPORT______(true,  PFNGLGETINTERNALFORMATI64VPROC,             glGetInternalformati64v);
GL_IMPORT______(true,  PFNGLGETOBJECTLABELPROC,                    glGetObjectLabel);
GL_IMPORT______(true,  PFNGLGETOBJECTPTRLABELPROC,                 glGetObjectPtrLabel);
GL_IMPORT______(true,  PFNGLGETPOINTERVPROC,                       glGetPointerv);
GL_IMPORT______(true,  PFNGLGETPROGRAMBINARYPROC,                  glGetProgramBinary);
GL_IMPORT______(false, PFNGLGETPROGRAMIVPROC,                      glGetProgramiv);
GL_IMPORT______(false, PFNGLGETPROGRAMINFOLOGPROC,                 glGetProgramInfoLog);
GL_IMPORT______(true,  PFNGLGETPROGRAMINTERFACEIVPROC,             glGetProgramInterfaceiv);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCEINDEXPROC,           glGetProgramResourceIndex);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCEIVPROC,              glGetProgramResourceiv);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCENAMEPROC,            glGetProgramResourceName);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCELOCATIONPROC,        glGetProgramResourceLocation);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC,   glGetProgramResourceLocationIndex);
GL_IMPORT______(true,  PFNGLGETTEXIMAGEPROC,                       glGetTexImage);
GL_IMPORT______(true,  PFNGLGETQUERYIVPROC,                        glGetQueryiv);
GL_IMPORT______(true,  PFNGLGETQUERYOBJECTIVPROC,                  glGetQueryObjectiv);
GL_IMPORT______(true,  PFNGLGETQUERYOBJECTI64VPROC,                glGetQueryObjecti64v);
GL_IMPORT______(true,  PFNGLGETQUERYOBJECTUIVPROC,                 glGetQueryObjectuiv);
GL_IMPORT______(true,  PFNGLGETQUERYOBJECTUI64VPROC,               glGetQueryObjectui64v);
GL_IMPORT______(false, PFNGLGETSHADERIVPROC,                       glGetShaderiv);
GL_IMPORT______(false, PFNGLGETSHADERINFOLOGPROC,                  glGetShaderInfoLog);
GL_IMPORT______(false, PFNGLGETSTRINGPROC,                         glGetString);
GL_IMPORT______(false, PFNGLGETUNIFORMLOCATIONPROC,                glGetUniformLocation);
#if BGFX_CONFIG_RENDERER_OPENGL || !(BGFX_CONFIG_RENDERER_OPENGLES < 30)
GL_IMPORT______(true,  PFNGLINVALIDATEFRAMEBUFFERPROC,             glInvalidateFramebuffer);
#endif // !(BGFX_CONFIG_RENDERER_OPENGLES < 30)
GL_IMPORT______(false, PFNGLLINKPROGRAMPROC,                       glLinkProgram);
GL_IMPORT______(true,  PFNGLMEMORYBARRIERPROC,                     glMemoryBarrier);
GL_IMPORT______(true,  PFNGLMULTIDRAWARRAYSINDIRECTPROC,           glMultiDrawArraysIndirect);
GL_IMPORT______(true,  PFNGLMULTIDRAWELEMENTSINDIRECTPROC,         glMultiDrawElementsIndirect);
GL_IMPORT______(true,  PFNGLOBJECTLABELPROC,                       glObjectLabel);
GL_IMPORT______(true,  PFNGLOBJECTPTRLABELPROC,                    glObjectPtrLabel);
GL_IMPORT______(false, PFNGLPIXELSTOREIPROC,                       glPixelStorei);
GL_IMPORT______(true,  PFNGLPOPDEBUGGROUPPROC,                     glPopDebugGroup);
GL_IMPORT______(true,  PFNGLPROGRAMBINARYPROC,                     glProgramBinary);
GL_IMPORT______(true,  PFNGLPROGRAMPARAMETERIPROC,                 glProgramParameteri);
GL_IMPORT______(true,  PFNGLPUSHDEBUGGROUPPROC,                    glPushDebugGroup);
GL_IMPORT______(true,  PFNGLQUERYCOUNTERPROC,                      glQueryCounter);
GL_IMPORT______(true,  PFNGLREADBUFFERPROC,                        glReadBuffer);
GL_IMPORT______(false, PFNGLREADPIXELSPROC,                        glReadPixels);
GL_IMPORT______(true,  PFNGLRENDERBUFFERSTORAGEPROC,               glRenderbufferStorage);
GL_IMPORT______(true,  PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC,    glRenderbufferStorageMultisample);
GL_IMPORT______(true,  PFNGLSAMPLERPARAMETERIPROC,                 glSamplerParameteri);
GL_IMPORT______(true,  PFNGLSAMPLERPARAMETERFPROC,                 glSamplerParameterf);
GL_IMPORT______(true,  PFNGLSAMPLERPARAMETERFVPROC,                glSamplerParameterfv);
GL_IMPORT______(false, PFNGLSCISSORPROC,                           glScissor);
GL_IMPORT______(false, PFNGLSHADERSOURCEPROC,                      glShaderSource);
GL_IMPORT______(false, PFNGLSTENCILFUNCPROC,                       glStencilFunc);
GL_IMPORT______(true,  PFNGLSTENCILFUNCSEPARATEPROC,               glStencilFuncSeparate);
GL_IMPORT______(false, PFNGLSTENCILMASKPROC,                       glStencilMask);
GL_IMPORT______(true,  PFNGLSTENCILMASKSEPARATEPROC,               glStencilMaskSeparate);
GL_IMPORT______(false, PFNGLSTENCILOPPROC,                         glStencilOp);
GL_IMPORT______(true,  PFNGLSTENCILOPSEPARATEPROC,                 glStencilOpSeparate);
GL_IMPORT______(false, PFNGLTEXIMAGE2DPROC,                        glTexImage2D);
GL_IMPORT______(true,  PFNGLTEXIMAGE3DPROC,                        glTexImage3D);
GL_IMPORT______(false, PFNGLTEXPARAMETERIPROC,                     glTexParameteri);
GL_IMPORT______(false, PFNGLTEXPARAMETERIVPROC,                    glTexParameteriv);
GL_IMPORT______(false, PFNGLTEXPARAMETERFPROC,                     glTexParameterf);
GL_IMPORT______(false, PFNGLTEXPARAMETERFVPROC,                    glTexParameterfv);
GL_IMPORT______(true,  PFNGLTEXSTORAGE2DPROC,                      glTexStorage2D);
GL_IMPORT______(true,  PFNGLTEXSTORAGE3DPROC,                      glTexStorage3D);
GL_IMPORT______(false, PFNGLTEXSUBIMAGE2DPROC,                     glTexSubImage2D);
GL_IMPORT______(true,  PFNGLTEXSUBIMAGE3DPROC,                     glTexSubImage3D);
GL_IMPORT______(false, PFNGLUNIFORM1IPROC,                         glUniform1i);
GL_IMPORT______(false, PFNGLUNIFORM1IVPROC,                        glUniform1iv);
GL_IMPORT______(false, PFNGLUNIFORM1FPROC,                         glUniform1f);
GL_IMPORT______(false, PFNGLUNIFORM1FVPROC,                        glUniform1fv);
GL_IMPORT______(false, PFNGLUNIFORM2FVPROC,                        glUniform2fv);
GL_IMPORT______(false, PFNGLUNIFORM3FVPROC,                        glUniform3fv);
GL_IMPORT______(false, PFNGLUNIFORM4FVPROC,                        glUniform4fv);
GL_IMPORT______(false, PFNGLUNIFORMMATRIX3FVPROC,                  glUniformMatrix3fv);
GL_IMPORT______(false, PFNGLUNIFORMMATRIX4FVPROC,                  glUniformMatrix4fv);
GL_IMPORT______(false, PFNGLUSEPROGRAMPROC,                        glUseProgram);
GL_IMPORT______(true,  PFNGLVERTEXATTRIBDIVISORPROC,               glVertexAttribDivisor);
GL_IMPORT______(false, PFNGLVERTEXATTRIBPOINTERPROC,               glVertexAttribPointer);
GL_IMPORT______(true,  PFNGLVERTEXATTRIBIPOINTERPROC,              glVertexAttribIPointer);
GL_IMPORT______(false, PFNGLVERTEXATTRIB1FPROC,                    glVertexAttrib1f);
GL_IMPORT______(false, PFNGLVERTEXATTRIB2FPROC,                    glVertexAttrib2f);
GL_IMPORT______(false, PFNGLVERTEXATTRIB3FPROC,                    glVertexAttrib3f);
GL_IMPORT______(false, PFNGLVERTEXATTRIB4FPROC,                    glVertexAttrib4f);
GL_IMPORT______(false, PFNGLVIEWPORTPROC,                          glViewport);

#	if BGFX_CONFIG_RENDERER_OPENGL
GL_IMPORT______(false, PFNGLCLEARDEPTHPROC,                        glClearDepth);
GL_IMPORT______(false, PFNGLPOINTSIZEPROC,                         glPointSize);

GL_IMPORT_ARB__(true,  PFNGLDEBUGMESSAGECONTROLPROC,               glDebugMessageControl);
GL_IMPORT_ARB__(true,  PFNGLDEBUGMESSAGEINSERTPROC,                glDebugMessageInsert);
GL_IMPORT_ARB__(true,  PFNGLDEBUGMESSAGECALLBACKPROC,              glDebugMessageCallback);
GL_IMPORT_ARB__(true,  PFNGLGETDEBUGMESSAGELOGPROC,                glGetDebugMessageLog);
GL_IMPORT_ARB__(true,  PFNGLPUSHDEBUGGROUPPROC,                    glPushDebugGroup);
GL_IMPORT_ARB__(true,  PFNGLPOPDEBUGGROUPPROC,                     glPopDebugGroup);
GL_IMPORT_ARB__(true,  PFNGLOBJECTLABELPROC,                       glObjectLabel);
GL_IMPORT_ARB__(true,  PFNGLGETOBJECTLABELPROC,                    glGetObjectLabel);
GL_IMPORT_ARB__(true,  PFNGLOBJECTPTRLABELPROC,                    glObjectPtrLabel);
GL_IMPORT_ARB__(true,  PFNGLGETOBJECTPTRLABELPROC,                 glGetObjectPtrLabel);
GL_IMPORT_ARB__(true,  PFNGLGETPOINTERVPROC,                       glGetPointerv);

GL_IMPORT_ARB__(true,  PFNGLBLENDEQUATIONIPROC,                    glBlendEquationi);
GL_IMPORT_ARB__(true,  PFNGLBLENDEQUATIONSEPARATEIPROC,            glBlendEquationSeparatei);
GL_IMPORT_ARB__(true,  PFNGLBLENDFUNCIPROC,                        glBlendFunci);
GL_IMPORT_ARB__(true,  PFNGLBLENDFUNCSEPARATEIPROC,                glBlendFuncSeparatei);

GL_IMPORT_ARB__(true,  PFNGLVERTEXATTRIBDIVISORPROC,               glVertexAttribDivisor);
GL_IMPORT_ARB__(true,  PFNGLDRAWARRAYSINSTANCEDPROC,               glDrawArraysInstanced);
GL_IMPORT_ARB__(true,  PFNGLDRAWELEMENTSINSTANCEDPROC,             glDrawElementsInstanced);

GL_IMPORT_ARB__(true,  PFNGLDRAWBUFFERSPROC,                       glDrawBuffers);

GL_IMPORT_ARB__(true,  PFNGLINVALIDATEFRAMEBUFFERPROC,             glInvalidateFramebuffer);

GL_IMPORT_ARB__(true,  PFNGLMULTIDRAWARRAYSINDIRECTPROC,           glMultiDrawArraysIndirect);
GL_IMPORT_ARB__(true,  PFNGLMULTIDRAWELEMENTSINDIRECTPROC,         glMultiDrawElementsIndirect);

GL_IMPORT_EXT__(true,  PFNGLBINDFRAMEBUFFERPROC,                   glBindFramebuffer);
GL_IMPORT_EXT__(true,  PFNGLGENFRAMEBUFFERSPROC,                   glGenFramebuffers);
GL_IMPORT_EXT__(true,  PFNGLDELETEFRAMEBUFFERSPROC,                glDeleteFramebuffers);
GL_IMPORT_EXT__(true,  PFNGLCHECKFRAMEBUFFERSTATUSPROC,            glCheckFramebufferStatus);
GL_IMPORT_EXT__(true,  PFNGLFRAMEBUFFERRENDERBUFFERPROC,           glFramebufferRenderbuffer);
GL_IMPORT_EXT__(true,  PFNGLFRAMEBUFFERTEXTURE2DPROC,              glFramebufferTexture2D);
GL_IMPORT_EXT__(true,  PFNGLBINDRENDERBUFFERPROC,                  glBindRenderbuffer);
GL_IMPORT_EXT__(true,  PFNGLGENRENDERBUFFERSPROC,                  glGenRenderbuffers);
GL_IMPORT_EXT__(true,  PFNGLDELETERENDERBUFFERSPROC,               glDeleteRenderbuffers);
GL_IMPORT_EXT__(true,  PFNGLRENDERBUFFERSTORAGEPROC,               glRenderbufferStorage);
GL_IMPORT_EXT__(true,  PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC,    glRenderbufferStorageMultisample);

#	else // GLES
GL_IMPORT______(false, PFNGLCLEARDEPTHFPROC,                       glClearDepthf);
#	endif // BGFX_CONFIG_RENDERER_OPENGL

GL_IMPORT______(true,  PFNGLINSERTEVENTMARKEREXTPROC,              glInsertEventMarker);
GL_IMPORT______(true,  PFNGLPUSHGROUPMARKEREXTPROC,                glPushGroupMarker);
GL_IMPORT______(true,  PFNGLPOPGROUPMARKEREXTPROC,                 glPopGroupMarker);
#else
GL_IMPORT______(true,  PFNGLVERTEXATTRIBIPOINTERPROC,              glVertexAttribIPointer);
GL_IMPORT______(true,  PFNGLGETINTERNALFORMATIVPROC,               glGetInternalformativ);
GL_IMPORT______(true,  PFNGLGETINTERNALFORMATI64VPROC,             glGetInternalformati64v);
#endif // BGFX_USE_GL_DYNAMIC_LIB

GL_IMPORT______(true,  PFNGLSTRINGMARKERGREMEDYPROC,               glStringMarkerGREMEDY);
GL_IMPORT______(true,  PFNGLFRAMETERMINATORGREMEDYPROC,            glFrameTerminatorGREMEDY);
GL_IMPORT______(true,  PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC,    glGetTranslatedShaderSourceANGLE);

#if !BGFX_CONFIG_RENDERER_OPENGL
GL_IMPORT_ANGLE(true,  PFNGLBLITFRAMEBUFFERPROC,                   glBlitFramebuffer);
GL_IMPORT_ANGLE(true,  PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC,    glRenderbufferStorageMultisample);

GL_IMPORT_EXT__(true , PFNGLCOPYIMAGESUBDATAPROC,                  glCopyImageSubData);

GL_IMPORT_KHR__(true,  PFNGLDEBUGMESSAGECONTROLPROC,               glDebugMessageControl);
GL_IMPORT_KHR__(true,  PFNGLDEBUGMESSAGEINSERTPROC,                glDebugMessageInsert);
GL_IMPORT_KHR__(true,  PFNGLDEBUGMESSAGECALLBACKPROC,              glDebugMessageCallback);
GL_IMPORT_KHR__(true,  PFNGLGETDEBUGMESSAGELOGPROC,                glGetDebugMessageLog);

GL_IMPORT_____x(true,  PFNGLGETCOMPRESSEDTEXIMAGEPROC,             glGetCompressedTexImage);
GL_IMPORT_____x(true,  PFNGLGETTEXIMAGEPROC,                       glGetTexImage);

#	if BGFX_CONFIG_RENDERER_OPENGLES < 30
GL_IMPORT_OES__(true,  PFNGLTEXIMAGE3DPROC,                        glTexImage3D);
GL_IMPORT_OES__(true,  PFNGLTEXSUBIMAGE3DPROC,                     glTexSubImage3D);
GL_IMPORT_OES__(true,  PFNGLCOMPRESSEDTEXIMAGE3DPROC,              glCompressedTexImage3D);
GL_IMPORT_OES__(true,  PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,           glCompressedTexSubImage3D);

GL_IMPORT_EXT__(true,  PFNGLTEXSTORAGE2DPROC,                      glTexStorage2D);
GL_IMPORT_EXT__(true,  PFNGLTEXSTORAGE3DPROC,                      glTexStorage3D);

GL_IMPORT_EXT__(true,  PFNGLINSERTEVENTMARKEREXTPROC,              glInsertEventMarker);
GL_IMPORT_EXT__(true,  PFNGLPUSHGROUPMARKEREXTPROC,                glPushGroupMarker);
GL_IMPORT_EXT__(true,  PFNGLPOPGROUPMARKEREXTPROC,                 glPopGroupMarker);
GL_IMPORT_EXT__(true,  PFNGLOBJECTLABELPROC,                       glObjectLabel);

GL_IMPORT_EXT__(true,  PFNGLDRAWARRAYSINDIRECTPROC,                glDrawArraysIndirect);
GL_IMPORT_EXT__(true,  PFNGLDRAWELEMENTSINDIRECTPROC,              glDrawElementsIndirect);
GL_IMPORT_EXT__(true,  PFNGLMULTIDRAWARRAYSINDIRECTPROC,           glMultiDrawArraysIndirect);
GL_IMPORT_EXT__(true,  PFNGLMULTIDRAWELEMENTSINDIRECTPROC,         glMultiDrawElementsIndirect);

GL_IMPORT_OES__(true,  PFNGLGETPROGRAMBINARYPROC,                  glGetProgramBinary);
GL_IMPORT_OES__(true,  PFNGLPROGRAMBINARYPROC,                     glProgramBinary);

GL_IMPORT_OES__(true,  PFNGLVERTEXATTRIBDIVISORPROC,               glVertexAttribDivisor);
GL_IMPORT_OES__(true,  PFNGLDRAWARRAYSINSTANCEDPROC,               glDrawArraysInstanced);
GL_IMPORT_OES__(true,  PFNGLDRAWELEMENTSINSTANCEDPROC,             glDrawElementsInstanced);

GL_IMPORT_OES__(true,  PFNGLBINDVERTEXARRAYPROC,                   glBindVertexArray);
GL_IMPORT_OES__(true,  PFNGLDELETEVERTEXARRAYSPROC,                glDeleteVertexArrays);
GL_IMPORT_OES__(true,  PFNGLGENVERTEXARRAYSPROC,                   glGenVertexArrays);

GL_IMPORT_____x(true,  PFNGLENABLEIPROC,                           glEnablei);
GL_IMPORT_____x(true,  PFNGLDISABLEIPROC,                          glDisablei);
GL_IMPORT_____x(true,  PFNGLBLENDEQUATIONIPROC,                    glBlendEquationi);
GL_IMPORT_____x(true,  PFNGLBLENDEQUATIONSEPARATEIPROC,            glBlendEquationSeparatei);
GL_IMPORT_____x(true,  PFNGLBLENDFUNCIPROC,                        glBlendFunci);
GL_IMPORT_____x(true,  PFNGLBLENDFUNCSEPARATEIPROC,                glBlendFuncSeparatei);

GL_IMPORT_____x(true,  PFNGLDRAWBUFFERPROC,                        glDrawBuffer);
GL_IMPORT_____x(true,  PFNGLREADBUFFERPROC,                        glReadBuffer);
GL_IMPORT_____x(true,  PFNGLGENSAMPLERSPROC,                       glGenSamplers);
GL_IMPORT_____x(true,  PFNGLDELETESAMPLERSPROC,                    glDeleteSamplers);
GL_IMPORT_____x(true,  PFNGLBINDSAMPLERPROC,                       glBindSampler);
GL_IMPORT_____x(true,  PFNGLSAMPLERPARAMETERFPROC,                 glSamplerParameterf);
GL_IMPORT_____x(true,  PFNGLSAMPLERPARAMETERIPROC,                 glSamplerParameteri);
GL_IMPORT_____x(true,  PFNGLSAMPLERPARAMETERFVPROC,                glSamplerParameterfv);

GL_IMPORT_____x(true,  PFNGLBINDBUFFERBASEPROC,                    glBindBufferBase);
GL_IMPORT_____x(true,  PFNGLBINDBUFFERRANGEPROC,                   glBindBufferRange);
GL_IMPORT_____x(true,  PFNGLBINDIMAGETEXTUREPROC,                  glBindImageTexture);
GL_IMPORT_____x(true,  PFNGLGETPROGRAMINTERFACEIVPROC,             glGetProgramInterfaceiv);
GL_IMPORT_____x(true,  PFNGLGETPROGRAMRESOURCEINDEXPROC,           glGetProgramResourceIndex);
GL_IMPORT_____x(true,  PFNGLGETPROGRAMRESOURCEIVPROC,              glGetProgramResourceiv);
GL_IMPORT_____x(true,  PFNGLGETPROGRAMRESOURCENAMEPROC,            glGetProgramResourceName);
GL_IMPORT_____x(true,  PFNGLGETPROGRAMRESOURCELOCATIONPROC,        glGetProgramResourceLocation);
GL_IMPORT_____x(true,  PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC,   glGetProgramResourceLocationIndex);
GL_IMPORT_____x(true,  PFNGLMEMORYBARRIERPROC,                     glMemoryBarrier);
GL_IMPORT_____x(true,  PFNGLDISPATCHCOMPUTEPROC,                   glDispatchCompute);
GL_IMPORT_____x(true,  PFNGLDISPATCHCOMPUTEINDIRECTPROC,           glDispatchComputeIndirect);

GL_IMPORT_NV___(true,  PFNGLDRAWBUFFERSPROC,                       glDrawBuffers);
GL_IMPORT_NV___(true,  PFNGLGENQUERIESPROC,                        glGenQueries);
GL_IMPORT_NV___(true,  PFNGLDELETEQUERIESPROC,                     glDeleteQueries);
GL_IMPORT_NV___(true,  PFNGLBEGINQUERYPROC,                        glBeginQuery);
GL_IMPORT_NV___(true,  PFNGLENDQUERYPROC,                          glEndQuery);
GL_IMPORT_NV___(true,  PFNGLGETQUERYOBJECTIVPROC,                  glGetQueryObjectiv);
GL_IMPORT_NV___(true,  PFNGLGETQUERYOBJECTUI64VPROC,               glGetQueryObjectui64v);
GL_IMPORT_NV___(true,  PFNGLQUERYCOUNTERPROC,                      glQueryCounter);

GL_IMPORT      (true,  PFNGLINVALIDATEFRAMEBUFFERPROC,             glInvalidateFramebuffer, glDiscardFramebufferEXT);

#	elif !BGFX_USE_GL_DYNAMIC_LIB
GL_IMPORT______(true,  PFNGLTEXIMAGE3DPROC,                        glTexImage3D);
GL_IMPORT______(true,  PFNGLTEXSUBIMAGE3DPROC,                     glTexSubImage3D);
GL_IMPORT______(true,  PFNGLCOMPRESSEDTEXIMAGE3DPROC,              glCompressedTexImage3D);
GL_IMPORT______(true,  PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,           glCompressedTexSubImage3D);

GL_IMPORT______(true,  PFNGLTEXSTORAGE2DPROC,                      glTexStorage2D);
GL_IMPORT______(true,  PFNGLTEXSTORAGE3DPROC,                      glTexStorage3D);

GL_IMPORT______(true,  PFNGLINSERTEVENTMARKEREXTPROC,              glInsertEventMarker);
GL_IMPORT______(true,  PFNGLPUSHGROUPMARKEREXTPROC,                glPushGroupMarker);
GL_IMPORT______(true,  PFNGLPOPGROUPMARKEREXTPROC,                 glPopGroupMarker);
GL_IMPORT______(true,  PFNGLOBJECTLABELPROC,                       glObjectLabel);

GL_IMPORT______(true,  PFNGLGETPROGRAMBINARYPROC,                  glGetProgramBinary);
GL_IMPORT______(true,  PFNGLPROGRAMBINARYPROC,                     glProgramBinary);

GL_IMPORT______(true,  PFNGLVERTEXATTRIBDIVISORPROC,               glVertexAttribDivisor);
GL_IMPORT______(true,  PFNGLDRAWARRAYSINSTANCEDPROC,               glDrawArraysInstanced);
GL_IMPORT______(true,  PFNGLDRAWELEMENTSINSTANCEDPROC,             glDrawElementsInstanced);

GL_IMPORT______(true,  PFNGLBINDVERTEXARRAYPROC,                   glBindVertexArray);
GL_IMPORT______(true,  PFNGLDELETEVERTEXARRAYSPROC,                glDeleteVertexArrays);
GL_IMPORT______(true,  PFNGLGENVERTEXARRAYSPROC,                   glGenVertexArrays);

GL_IMPORT______(true,  PFNGLENABLEIPROC,                           glEnablei);
GL_IMPORT______(true,  PFNGLDISABLEIPROC,                          glDisablei);
GL_IMPORT______(true,  PFNGLBLENDEQUATIONIPROC,                    glBlendEquationi);
GL_IMPORT______(true,  PFNGLBLENDEQUATIONSEPARATEIPROC,            glBlendEquationSeparatei);
GL_IMPORT______(true,  PFNGLBLENDFUNCIPROC,                        glBlendFunci);
GL_IMPORT______(true,  PFNGLBLENDFUNCSEPARATEIPROC,                glBlendFuncSeparatei);

GL_IMPORT______(true,  PFNGLDRAWBUFFERPROC,                        glDrawBuffer);
GL_IMPORT______(true,  PFNGLREADBUFFERPROC,                        glReadBuffer);
GL_IMPORT______(true,  PFNGLGENSAMPLERSPROC,                       glGenSamplers);
GL_IMPORT______(true,  PFNGLDELETESAMPLERSPROC,                    glDeleteSamplers);
GL_IMPORT______(true,  PFNGLBINDSAMPLERPROC,                       glBindSampler);
GL_IMPORT______(true,  PFNGLSAMPLERPARAMETERFPROC,                 glSamplerParameterf);
GL_IMPORT______(true,  PFNGLSAMPLERPARAMETERIPROC,                 glSamplerParameteri);
GL_IMPORT______(true,  PFNGLSAMPLERPARAMETERFVPROC,                glSamplerParameterfv);

GL_IMPORT______(true,  PFNGLBINDBUFFERBASEPROC,                    glBindBufferBase);
GL_IMPORT______(true,  PFNGLBINDBUFFERRANGEPROC,                   glBindBufferRange);
GL_IMPORT______(true,  PFNGLBINDIMAGETEXTUREPROC,                  glBindImageTexture);
GL_IMPORT______(true,  PFNGLGETPROGRAMINTERFACEIVPROC,             glGetProgramInterfaceiv);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCEINDEXPROC,           glGetProgramResourceIndex);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCEIVPROC,              glGetProgramResourceiv);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCENAMEPROC,            glGetProgramResourceName);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCELOCATIONPROC,        glGetProgramResourceLocation);
GL_IMPORT______(true,  PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC,   glGetProgramResourceLocationIndex);
GL_IMPORT______(true,  PFNGLMEMORYBARRIERPROC,                     glMemoryBarrier);
GL_IMPORT______(true,  PFNGLDISPATCHCOMPUTEPROC,                   glDispatchCompute);
GL_IMPORT______(true,  PFNGLDISPATCHCOMPUTEINDIRECTPROC,           glDispatchComputeIndirect);

GL_IMPORT______(true,  PFNGLDRAWBUFFERSPROC,                       glDrawBuffers);
GL_IMPORT______(true,  PFNGLGENQUERIESPROC,                        glGenQueries);
GL_IMPORT______(true,  PFNGLDELETEQUERIESPROC,                     glDeleteQueries);
GL_IMPORT______(true,  PFNGLBEGINQUERYPROC,                        glBeginQuery);
GL_IMPORT______(true,  PFNGLENDQUERYPROC,                          glEndQuery);
GL_IMPORT______(true,  PFNGLGETQUERYOBJECTIVPROC,                  glGetQueryObjectiv);
GL_IMPORT______(true,  PFNGLGETQUERYOBJECTUI64VPROC,               glGetQueryObjectui64v);
GL_IMPORT______(true,  PFNGLQUERYCOUNTERPROC,                      glQueryCounter);

GL_IMPORT______(true,  PFNGLDRAWARRAYSINDIRECTPROC,                glDrawArraysIndirect);
GL_IMPORT______(true,  PFNGLDRAWELEMENTSINDIRECTPROC,              glDrawElementsIndirect);
GL_IMPORT______(true,  PFNGLMULTIDRAWARRAYSINDIRECTPROC,           glMultiDrawArraysIndirect);
GL_IMPORT______(true,  PFNGLMULTIDRAWELEMENTSINDIRECTPROC,         glMultiDrawElementsIndirect);

GL_IMPORT______(true,  PFNGLINVALIDATEFRAMEBUFFERPROC,             glInvalidateFramebuffer);

#	endif // BGFX_CONFIG_RENDERER_OPENGLES < 30
#endif // !BGFX_CONFIG_RENDERER_OPENGL

#undef GL_IMPORT_TYPEDEFS
#undef GL_IMPORT
#undef GL_EXTENSION
#undef GL_IMPORT______
#undef GL_IMPORT_ARB__
#undef GL_IMPORT_EXT__
#undef GL_IMPORT_KHR__
#undef GL_IMPORT_NV___
#undef GL_IMPORT_OES__
#undef GL_IMPORT_____x
