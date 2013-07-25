/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef GL_IMPORT
#	error GL_IMPORT(_optional, _proto, _func) must be defined!
#endif // GL_IMPORT

#if BGFX_CONFIG_RENDERER_OPENGL
// OpenGL 2.1 Reference Pages
// http://www.opengl.org/sdk/docs/man/

#if BX_PLATFORM_WINDOWS
GL_IMPORT(false, PFNGLGETERRORPROC,                       glGetError);
GL_IMPORT(false, PFNGLREADPIXELSPROC,                     glReadPixels);
GL_IMPORT(false, PFNGLTEXIMAGE2DPROC,                     glTexImage2D);
GL_IMPORT(false, PFNGLTEXSUBIMAGE2DPROC,                  glTexSubImage2D);
GL_IMPORT(false, PFNGLPIXELSTOREIPROC,                    glPixelStorei);
GL_IMPORT(false, PFNGLTEXPARAMETERIPROC,                  glTexParameteri);
GL_IMPORT(false, PFNGLTEXPARAMETERIVPROC,                 glTexParameteriv);
GL_IMPORT(false, PFNGLTEXPARAMETERFPROC,                  glTexParameterf);
GL_IMPORT(false, PFNGLBINDTEXTUREPROC,                    glBindTexture);
GL_IMPORT(false, PFNGLGENTEXTURESPROC,                    glGenTextures);
GL_IMPORT(false, PFNGLDELETETEXTURESPROC,                 glDeleteTextures);
GL_IMPORT(false, PFNGLCOLORMASKPROC,                      glColorMask);
GL_IMPORT(false, PFNGLDEPTHFUNCPROC,                      glDepthFunc);
GL_IMPORT(false, PFNGLDISABLEPROC,                        glDisable);
GL_IMPORT(false, PFNGLVIEWPORTPROC,                       glViewport);
GL_IMPORT(false, PFNGLDRAWELEMENTSPROC,                   glDrawElements);
GL_IMPORT(false, PFNGLGETINTEGERVPROC,                    glGetIntegerv);
GL_IMPORT(false, PFNGLGETFLOATVPROC,                      glGetFloatv);
GL_IMPORT(false, PFNGLGETSTRINGPROC,                      glGetString);
GL_IMPORT(false, PFNGLDRAWARRAYSPROC,                     glDrawArrays);
GL_IMPORT(false, PFNGLBLENDFUNCPROC,                      glBlendFunc);
GL_IMPORT(false, PFNGLBLENDEQUATIONPROC,                  glBlendEquation);
GL_IMPORT(false, PFNGLPOINTSIZEPROC,                      glPointSize);
GL_IMPORT(false, PFNGLCULLFACEPROC,                       glCullFace);
GL_IMPORT(false, PFNGLCLEARPROC,                          glClear);
GL_IMPORT(false, PFNGLSCISSORPROC,                        glScissor);
GL_IMPORT(false, PFNGLENABLEPROC,                         glEnable);
GL_IMPORT(false, PFNGLCLEARSTENCILPROC,                   glClearStencil);
GL_IMPORT(false, PFNGLDEPTHMASKPROC,                      glDepthMask);
GL_IMPORT(false, PFNGLCLEARDEPTHPROC,                     glClearDepth);
GL_IMPORT(false, PFNGLCLEARCOLORPROC,                     glClearColor);
GL_IMPORT(false, PFNGLSTENCILFUNCPROC,                    glStencilFunc);
GL_IMPORT(false, PFNGLSTENCILMASKPROC,                    glStencilMask);
GL_IMPORT(false, PFNGLSTENCILOPPROC,                      glStencilOp);
#endif // BX_PLATFORM_WINDOWS

GL_IMPORT(false, PFNGLACTIVETEXTUREPROC,                  glActiveTexture);
GL_IMPORT(false, PFNGLCOMPRESSEDTEXIMAGE2DPROC,           glCompressedTexImage2D);
GL_IMPORT(false, PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC,        glCompressedTexSubImage2D);
GL_IMPORT(false, PFNGLCOMPRESSEDTEXIMAGE3DPROC,           glCompressedTexImage3D);
GL_IMPORT(false, PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,        glCompressedTexSubImage3D);
GL_IMPORT(false, PFNGLBINDBUFFERPROC,                     glBindBuffer);
GL_IMPORT(false, PFNGLDELETEBUFFERSPROC,                  glDeleteBuffers);
GL_IMPORT(false, PFNGLGENBUFFERSPROC,                     glGenBuffers);
GL_IMPORT(false, PFNGLBUFFERDATAPROC,                     glBufferData);
GL_IMPORT(false, PFNGLBUFFERSUBDATAPROC,                  glBufferSubData);
GL_IMPORT(false, PFNGLCREATEPROGRAMPROC,                  glCreateProgram);
GL_IMPORT(false, PFNGLCREATESHADERPROC,                   glCreateShader);
GL_IMPORT(false, PFNGLDELETEPROGRAMPROC,                  glDeleteProgram);
GL_IMPORT(false, PFNGLDELETESHADERPROC,                   glDeleteShader);
GL_IMPORT(false, PFNGLATTACHSHADERPROC,                   glAttachShader);
GL_IMPORT(false, PFNGLDETACHSHADERPROC,                   glDetachShader);
GL_IMPORT(false, PFNGLCOMPILESHADERPROC,                  glCompileShader);
GL_IMPORT(false, PFNGLSHADERSOURCEPROC,                   glShaderSource);
GL_IMPORT(false, PFNGLGETSHADERIVPROC,                    glGetShaderiv);
GL_IMPORT(false, PFNGLGETSHADERINFOLOGPROC,               glGetShaderInfoLog);
GL_IMPORT(false, PFNGLLINKPROGRAMPROC,                    glLinkProgram);
GL_IMPORT(false, PFNGLGETPROGRAMIVPROC,                   glGetProgramiv);
GL_IMPORT(false, PFNGLGETPROGRAMINFOLOGPROC,              glGetProgramInfoLog);
GL_IMPORT(false, PFNGLUSEPROGRAMPROC,                     glUseProgram);
GL_IMPORT(false, PFNGLGETACTIVEATTRIBPROC,                glGetActiveAttrib);
GL_IMPORT(false, PFNGLGETATTRIBLOCATIONPROC,              glGetAttribLocation);
GL_IMPORT(false, PFNGLGETACTIVEUNIFORMPROC,               glGetActiveUniform);
GL_IMPORT(false, PFNGLGETUNIFORMLOCATIONPROC,             glGetUniformLocation);
GL_IMPORT(false, PFNGLENABLEVERTEXATTRIBARRAYPROC,        glEnableVertexAttribArray);
GL_IMPORT(false, PFNGLDISABLEVERTEXATTRIBARRAYPROC,       glDisableVertexAttribArray);
GL_IMPORT(false, PFNGLVERTEXATTRIBPOINTERPROC,            glVertexAttribPointer);
GL_IMPORT(false, PFNGLVERTEXATTRIB1FPROC,                 glVertexAttrib1f);
GL_IMPORT(false, PFNGLVERTEXATTRIB2FPROC,                 glVertexAttrib2f);
GL_IMPORT(false, PFNGLVERTEXATTRIB3FPROC,                 glVertexAttrib3f);
GL_IMPORT(false, PFNGLVERTEXATTRIB4FPROC,                 glVertexAttrib4f);
GL_IMPORT(false, PFNGLBINDFRAMEBUFFERPROC,                glBindFramebuffer);
GL_IMPORT(false, PFNGLGENFRAMEBUFFERSPROC,                glGenFramebuffers);
GL_IMPORT(false, PFNGLDELETEFRAMEBUFFERSPROC,             glDeleteFramebuffers);
GL_IMPORT(false, PFNGLCHECKFRAMEBUFFERSTATUSPROC,         glCheckFramebufferStatus);
GL_IMPORT(false, PFNGLFRAMEBUFFERRENDERBUFFERPROC,        glFramebufferRenderbuffer);
GL_IMPORT(false, PFNGLFRAMEBUFFERTEXTURE2DPROC,           glFramebufferTexture2D);
GL_IMPORT(false, PFNGLBINDRENDERBUFFERPROC,               glBindRenderbuffer);
GL_IMPORT(false, PFNGLGENRENDERBUFFERSPROC,               glGenRenderbuffers);
GL_IMPORT(false, PFNGLDELETERENDERBUFFERSPROC,            glDeleteRenderbuffers);
GL_IMPORT(false, PFNGLRENDERBUFFERSTORAGEPROC,            glRenderbufferStorage);
GL_IMPORT(false, PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample);
GL_IMPORT(false, PFNGLUNIFORM1IPROC,                      glUniform1i);
GL_IMPORT(false, PFNGLUNIFORM1IVPROC,                     glUniform1iv);
GL_IMPORT(false, PFNGLUNIFORM1FPROC,                      glUniform1f);
GL_IMPORT(false, PFNGLUNIFORM1FVPROC,                     glUniform1fv);
GL_IMPORT(false, PFNGLUNIFORM2FVPROC,                     glUniform2fv);
GL_IMPORT(false, PFNGLUNIFORM3FVPROC,                     glUniform3fv);
GL_IMPORT(false, PFNGLUNIFORM4FVPROC,                     glUniform4fv);
GL_IMPORT(false, PFNGLUNIFORMMATRIX3FVPROC,               glUniformMatrix3fv);
GL_IMPORT(false, PFNGLUNIFORMMATRIX4FVPROC,               glUniformMatrix4fv);
GL_IMPORT(false, PFNGLTEXIMAGE3DPROC,                     glTexImage3D);
GL_IMPORT(false, PFNGLTEXSUBIMAGE3DPROC,                  glTexSubImage3D);
GL_IMPORT(false, PFNGLCOPYTEXSUBIMAGE3DPROC,              glCopyTexSubImage3D);

GL_IMPORT(false, PFNGLGENQUERIESPROC,                     glGenQueries);
GL_IMPORT(false, PFNGLDELETEQUERIESPROC,                  glDeleteQueries);
GL_IMPORT(false, PFNGLBEGINQUERYPROC,                     glBeginQuery);
GL_IMPORT(false, PFNGLENDQUERYPROC,                       glEndQuery);
GL_IMPORT(false, PFNGLGETQUERYIVPROC,                     glGetQueryiv);
GL_IMPORT(false, PFNGLGETQUERYOBJECTIVPROC,               glGetQueryObjectiv);
GL_IMPORT(false, PFNGLGETQUERYOBJECTUIVPROC,              glGetQueryObjectuiv);

GL_IMPORT(true,  PFNGLGETPROGRAMBINARYPROC,               glGetProgramBinary);
GL_IMPORT(true,  PFNGLPROGRAMBINARYPROC,                  glProgramBinary);
GL_IMPORT(true,  PFNGLPROGRAMPARAMETERIPROC,              glProgramParameteri);

GL_IMPORT(true,  PFNGLBLITFRAMEBUFFERPROC,                glBlitFramebuffer);

GL_IMPORT(true,  PFNGLQUERYCOUNTERPROC,                   glQueryCounter);
GL_IMPORT(true,  PFNGLGETQUERYOBJECTI64VPROC,             glGetQueryObjecti64v);
GL_IMPORT(true,  PFNGLGETQUERYOBJECTUI64VPROC,            glGetQueryObjectui64v);

GL_IMPORT(true,  PFNGLBINDVERTEXARRAYPROC,                glBindVertexArray);
GL_IMPORT(true,  PFNGLDELETEVERTEXARRAYSPROC,             glDeleteVertexArrays);
GL_IMPORT(true,  PFNGLGENVERTEXARRAYSPROC,                glGenVertexArrays);

GL_IMPORT(true,  PFNGLSTENCILFUNCSEPARATEPROC,            glStencilFuncSeparate);
GL_IMPORT(true,  PFNGLSTENCILMASKSEPARATEPROC,            glStencilMaskSeparate);
GL_IMPORT(true,  PFNGLSTENCILOPSEPARATEPROC,              glStencilOpSeparate);

GL_IMPORT(true,  PFNGLBLENDFUNCSEPARATEPROC,              glBlendFuncSeparate);
GL_IMPORT(true,  PFNGLBLENDEQUATIONSEPARATEPROC,          glBlendEquationSeparate);
GL_IMPORT(true,  PFNGLBLENDCOLORPROC,                     glBlendColor);

GL_IMPORT(true,  PFNGLDEBUGMESSAGECONTROLARBPROC,         glDebugMessageControlARB);
GL_IMPORT(true,  PFNGLDEBUGMESSAGEINSERTARBPROC,          glDebugMessageInsertARB);
GL_IMPORT(true,  PFNGLDEBUGMESSAGECALLBACKARBPROC,        glDebugMessageCallbackARB);
GL_IMPORT(true,  PFNGLGETDEBUGMESSAGELOGARBPROC,          glGetDebugMessageLogARB);

GL_IMPORT(true,  PFNGLGENSAMPLERSPROC,                    glGenSamplers);
GL_IMPORT(true,  PFNGLDELETESAMPLERSPROC,                 glDeleteSamplers);
GL_IMPORT(true,  PFNGLBINDSAMPLERPROC,                    glBindSampler);
GL_IMPORT(true,  PFNGLSAMPLERPARAMETERIPROC,              glSamplerParameteri);
GL_IMPORT(true,  PFNGLSAMPLERPARAMETERFPROC,              glSamplerParameterf);

#if BGFX_CONFIG_DEBUG_GREMEDY
GL_IMPORT(true,  PFNGLSTRINGMARKERGREMEDYPROC,            glStringMarkerGREMEDY);
GL_IMPORT(true,  PFNGLFRAMETERMINATORGREMEDYPROC,         glFrameTerminatorGREMEDY);
#endif // BGFX_CONFIG_DEBUG_GREMEDY

#elif BGFX_CONFIG_RENDERER_OPENGLES2

// OpenGL ES 2.0 Reference Pages
// http://www.khronos.org/opengles/sdk/docs/man/

GL_IMPORT(true,  PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC, glGetTranslatedShaderSourceANGLE);
GL_IMPORT(true,  PFNGLGETPROGRAMBINARYOESPROC,            glGetProgramBinaryOES);
GL_IMPORT(true,  PFNGLPROGRAMBINARYOESPROC,               glProgramBinaryOES);

GL_IMPORT(true,  PFNGLBINDVERTEXARRAYOESPROC,             glBindVertexArrayOES);
GL_IMPORT(true,  PFNGLDELETEVERTEXARRAYSOESPROC,          glDeleteVertexArraysOES);
GL_IMPORT(true,  PFNGLGENVERTEXARRAYSOESPROC,             glGenVertexArraysOES);

#endif // BGFX_CONFIG_RENDERER_

#if BGFX_CONFIG_RENDERER_OPENGL
GL_IMPORT(true,  PFNGLVERTEXATTRIBDIVISORBGFXPROC,        glVertexAttribDivisorARB);
GL_IMPORT(true,  PFNGLDRAWARRAYSINSTANCEDBGFXPROC,        glDrawArraysInstancedARB);
GL_IMPORT(true,  PFNGLDRAWELEMENTSINSTANCEDBGFXPROC,      glDrawElementsInstancedARB);
#elif BGFX_CONFIG_RENDERER_OPENGLES2
GL_IMPORT(true,  PFNGLVERTEXATTRIBDIVISORBGFXPROC,        glVertexAttribDivisor);
GL_IMPORT(true,  PFNGLDRAWARRAYSINSTANCEDBGFXPROC,        glDrawArraysInstanced);
GL_IMPORT(true,  PFNGLDRAWELEMENTSINSTANCEDBGFXPROC,      glDrawElementsInstanced);
#endif // !BGFX_CONFIG_RENDERER_OPENGLES3
