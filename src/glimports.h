/*
* Copyright 2011-2013 Branimir Karadzic. All rights reserved.
* License: http://www.opensource.org/licenses/BSD-2-Clause
*/

#ifndef GL_IMPORT
#	error GL_IMPORT(_optional, _proto, _func, _import) must be defined!
#endif // GL_IMPORT

#define GL_IMPORT____(_optional, _proto, _func) GL_IMPORT(_optional, _proto, _func, _func)
#define GL_IMPORT_ARB(_optional, _proto, _func) GL_IMPORT(_optional, _proto, _func, _func ## ARB)
#define GL_IMPORT_EXT(_optional, _proto, _func) GL_IMPORT(_optional, _proto, _func, _func ## EXT)

#if BGFX_CONFIG_RENDERER_OPENGL
// OpenGL 2.1 Reference Pages
// http://www.opengl.org/sdk/docs/man/

#if BX_PLATFORM_WINDOWS
GL_IMPORT____(false, PFNGLGETERRORPROC,                          glGetError);
GL_IMPORT____(false, PFNGLREADPIXELSPROC,                        glReadPixels);
GL_IMPORT____(false, PFNGLTEXIMAGE2DPROC,                        glTexImage2D);
GL_IMPORT____(false, PFNGLTEXSUBIMAGE2DPROC,                     glTexSubImage2D);
GL_IMPORT____(false, PFNGLPIXELSTOREIPROC,                       glPixelStorei);
GL_IMPORT____(false, PFNGLTEXPARAMETERIPROC,                     glTexParameteri);
GL_IMPORT____(false, PFNGLTEXPARAMETERIVPROC,                    glTexParameteriv);
GL_IMPORT____(false, PFNGLTEXPARAMETERFPROC,                     glTexParameterf);
GL_IMPORT____(false, PFNGLBINDTEXTUREPROC,                       glBindTexture);
GL_IMPORT____(false, PFNGLGENTEXTURESPROC,                       glGenTextures);
GL_IMPORT____(false, PFNGLDELETETEXTURESPROC,                    glDeleteTextures);
GL_IMPORT____(false, PFNGLCOLORMASKPROC,                         glColorMask);
GL_IMPORT____(false, PFNGLDEPTHFUNCPROC,                         glDepthFunc);
GL_IMPORT____(false, PFNGLDISABLEPROC,                           glDisable);
GL_IMPORT____(false, PFNGLVIEWPORTPROC,                          glViewport);
GL_IMPORT____(false, PFNGLDRAWELEMENTSPROC,                      glDrawElements);
GL_IMPORT____(false, PFNGLGETINTEGERVPROC,                       glGetIntegerv);
GL_IMPORT____(false, PFNGLGETFLOATVPROC,                         glGetFloatv);
GL_IMPORT____(false, PFNGLGETSTRINGPROC,                         glGetString);
GL_IMPORT____(false, PFNGLDRAWARRAYSPROC,                        glDrawArrays);
GL_IMPORT____(false, PFNGLBLENDFUNCPROC,                         glBlendFunc);
GL_IMPORT____(false, PFNGLBLENDEQUATIONPROC,                     glBlendEquation);
GL_IMPORT____(false, PFNGLPOINTSIZEPROC,                         glPointSize);
GL_IMPORT____(false, PFNGLCULLFACEPROC,                          glCullFace);
GL_IMPORT____(false, PFNGLCLEARPROC,                             glClear);
GL_IMPORT____(false, PFNGLSCISSORPROC,                           glScissor);
GL_IMPORT____(false, PFNGLENABLEPROC,                            glEnable);
GL_IMPORT____(false, PFNGLCLEARSTENCILPROC,                      glClearStencil);
GL_IMPORT____(false, PFNGLDEPTHMASKPROC,                         glDepthMask);
GL_IMPORT____(false, PFNGLCLEARDEPTHPROC,                        glClearDepth);
GL_IMPORT____(false, PFNGLCLEARCOLORPROC,                        glClearColor);
GL_IMPORT____(false, PFNGLSTENCILFUNCPROC,                       glStencilFunc);
GL_IMPORT____(false, PFNGLSTENCILMASKPROC,                       glStencilMask);
GL_IMPORT____(false, PFNGLSTENCILOPPROC,                         glStencilOp);
#endif // BX_PLATFORM_WINDOWS

GL_IMPORT____(false, PFNGLACTIVETEXTUREPROC,                     glActiveTexture);
GL_IMPORT____(false, PFNGLCOMPRESSEDTEXIMAGE2DPROC,              glCompressedTexImage2D);
GL_IMPORT____(false, PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC,           glCompressedTexSubImage2D);
GL_IMPORT____(false, PFNGLCOMPRESSEDTEXIMAGE3DPROC,              glCompressedTexImage3D);
GL_IMPORT____(false, PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,           glCompressedTexSubImage3D);
GL_IMPORT____(false, PFNGLBINDBUFFERPROC,                        glBindBuffer);
GL_IMPORT____(false, PFNGLDELETEBUFFERSPROC,                     glDeleteBuffers);
GL_IMPORT____(false, PFNGLGENBUFFERSPROC,                        glGenBuffers);
GL_IMPORT____(false, PFNGLBUFFERDATAPROC,                        glBufferData);
GL_IMPORT____(false, PFNGLBUFFERSUBDATAPROC,                     glBufferSubData);
GL_IMPORT____(false, PFNGLCREATEPROGRAMPROC,                     glCreateProgram);
GL_IMPORT____(false, PFNGLCREATESHADERPROC,                      glCreateShader);
GL_IMPORT____(false, PFNGLDELETEPROGRAMPROC,                     glDeleteProgram);
GL_IMPORT____(false, PFNGLDELETESHADERPROC,                      glDeleteShader);
GL_IMPORT____(false, PFNGLATTACHSHADERPROC,                      glAttachShader);
GL_IMPORT____(false, PFNGLDETACHSHADERPROC,                      glDetachShader);
GL_IMPORT____(false, PFNGLCOMPILESHADERPROC,                     glCompileShader);
GL_IMPORT____(false, PFNGLSHADERSOURCEPROC,                      glShaderSource);
GL_IMPORT____(false, PFNGLGETSHADERIVPROC,                       glGetShaderiv);
GL_IMPORT____(false, PFNGLGETSHADERINFOLOGPROC,                  glGetShaderInfoLog);
GL_IMPORT____(false, PFNGLLINKPROGRAMPROC,                       glLinkProgram);
GL_IMPORT____(false, PFNGLGETPROGRAMIVPROC,                      glGetProgramiv);
GL_IMPORT____(false, PFNGLGETPROGRAMINFOLOGPROC,                 glGetProgramInfoLog);
GL_IMPORT____(false, PFNGLUSEPROGRAMPROC,                        glUseProgram);
GL_IMPORT____(false, PFNGLGETACTIVEATTRIBPROC,                   glGetActiveAttrib);
GL_IMPORT____(false, PFNGLGETATTRIBLOCATIONPROC,                 glGetAttribLocation);
GL_IMPORT____(false, PFNGLGETACTIVEUNIFORMPROC,                  glGetActiveUniform);
GL_IMPORT____(false, PFNGLGETUNIFORMLOCATIONPROC,                glGetUniformLocation);
GL_IMPORT____(false, PFNGLENABLEVERTEXATTRIBARRAYPROC,           glEnableVertexAttribArray);
GL_IMPORT____(false, PFNGLDISABLEVERTEXATTRIBARRAYPROC,          glDisableVertexAttribArray);
GL_IMPORT____(false, PFNGLVERTEXATTRIBPOINTERPROC,               glVertexAttribPointer);
GL_IMPORT____(false, PFNGLVERTEXATTRIB1FPROC,                    glVertexAttrib1f);
GL_IMPORT____(false, PFNGLVERTEXATTRIB2FPROC,                    glVertexAttrib2f);
GL_IMPORT____(false, PFNGLVERTEXATTRIB3FPROC,                    glVertexAttrib3f);
GL_IMPORT____(false, PFNGLVERTEXATTRIB4FPROC,                    glVertexAttrib4f);

#if BGFX_CONFIG_RENDERER_OPENGL >= 31
GL_IMPORT____(false, PFNGLBINDFRAMEBUFFERPROC,                   glBindFramebuffer);
GL_IMPORT____(false, PFNGLGENFRAMEBUFFERSPROC,                   glGenFramebuffers);
GL_IMPORT____(false, PFNGLDELETEFRAMEBUFFERSPROC,                glDeleteFramebuffers);
GL_IMPORT____(false, PFNGLCHECKFRAMEBUFFERSTATUSPROC,            glCheckFramebufferStatus);
GL_IMPORT____(false, PFNGLFRAMEBUFFERRENDERBUFFERPROC,           glFramebufferRenderbuffer);
GL_IMPORT____(false, PFNGLFRAMEBUFFERTEXTURE2DPROC,              glFramebufferTexture2D);
GL_IMPORT____(false, PFNGLBINDRENDERBUFFERPROC,                  glBindRenderbuffer);
GL_IMPORT____(false, PFNGLGENRENDERBUFFERSPROC,                  glGenRenderbuffers);
GL_IMPORT____(false, PFNGLDELETERENDERBUFFERSPROC,               glDeleteRenderbuffers);
GL_IMPORT____(false, PFNGLRENDERBUFFERSTORAGEPROC,               glRenderbufferStorage);
GL_IMPORT____(false, PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC,    glRenderbufferStorageMultisample);
#else
GL_IMPORT_EXT(false, PFNGLBINDFRAMEBUFFEREXTPROC,                glBindFramebuffer);
GL_IMPORT_EXT(false, PFNGLGENFRAMEBUFFERSEXTPROC,                glGenFramebuffers);
GL_IMPORT_EXT(false, PFNGLDELETEFRAMEBUFFERSEXTPROC,             glDeleteFramebuffers);
GL_IMPORT_EXT(false, PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC,         glCheckFramebufferStatus);
GL_IMPORT_EXT(false, PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC,        glFramebufferRenderbuffer);
GL_IMPORT_EXT(false, PFNGLFRAMEBUFFERTEXTURE2DEXTPROC,           glFramebufferTexture2D);
GL_IMPORT_EXT(false, PFNGLBINDRENDERBUFFEREXTPROC,               glBindRenderbuffer);
GL_IMPORT_EXT(false, PFNGLGENRENDERBUFFERSEXTPROC,               glGenRenderbuffers);
GL_IMPORT_EXT(false, PFNGLDELETERENDERBUFFERSEXTPROC,            glDeleteRenderbuffers);
GL_IMPORT_EXT(false, PFNGLRENDERBUFFERSTORAGEEXTPROC,            glRenderbufferStorage);
GL_IMPORT_EXT(false, PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC, glRenderbufferStorageMultisample);
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31

GL_IMPORT____(false, PFNGLUNIFORM1IPROC,                         glUniform1i);
GL_IMPORT____(false, PFNGLUNIFORM1IVPROC,                        glUniform1iv);
GL_IMPORT____(false, PFNGLUNIFORM1FPROC,                         glUniform1f);
GL_IMPORT____(false, PFNGLUNIFORM1FVPROC,                        glUniform1fv);
GL_IMPORT____(false, PFNGLUNIFORM2FVPROC,                        glUniform2fv);
GL_IMPORT____(false, PFNGLUNIFORM3FVPROC,                        glUniform3fv);
GL_IMPORT____(false, PFNGLUNIFORM4FVPROC,                        glUniform4fv);
GL_IMPORT____(false, PFNGLUNIFORMMATRIX3FVPROC,                  glUniformMatrix3fv);
GL_IMPORT____(false, PFNGLUNIFORMMATRIX4FVPROC,                  glUniformMatrix4fv);
GL_IMPORT____(false, PFNGLTEXIMAGE3DPROC,                        glTexImage3D);
GL_IMPORT____(false, PFNGLTEXSUBIMAGE3DPROC,                     glTexSubImage3D);
GL_IMPORT____(false, PFNGLCOPYTEXSUBIMAGE3DPROC,                 glCopyTexSubImage3D);

GL_IMPORT____(false, PFNGLGENQUERIESPROC,                        glGenQueries);
GL_IMPORT____(false, PFNGLDELETEQUERIESPROC,                     glDeleteQueries);
GL_IMPORT____(false, PFNGLBEGINQUERYPROC,                        glBeginQuery);
GL_IMPORT____(false, PFNGLENDQUERYPROC,                          glEndQuery);
GL_IMPORT____(false, PFNGLGETQUERYIVPROC,                        glGetQueryiv);
GL_IMPORT____(false, PFNGLGETQUERYOBJECTIVPROC,                  glGetQueryObjectiv);
GL_IMPORT____(false, PFNGLGETQUERYOBJECTUIVPROC,                 glGetQueryObjectuiv);

GL_IMPORT____(true,  PFNGLGETPROGRAMBINARYPROC,                  glGetProgramBinary);
GL_IMPORT____(true,  PFNGLPROGRAMBINARYPROC,                     glProgramBinary);
GL_IMPORT____(true,  PFNGLPROGRAMPARAMETERIPROC,                 glProgramParameteri);

GL_IMPORT____(true,  PFNGLBLITFRAMEBUFFERPROC,                   glBlitFramebuffer);

GL_IMPORT____(true,  PFNGLQUERYCOUNTERPROC,                      glQueryCounter);
GL_IMPORT____(true,  PFNGLGETQUERYOBJECTI64VPROC,                glGetQueryObjecti64v);
GL_IMPORT____(true,  PFNGLGETQUERYOBJECTUI64VPROC,               glGetQueryObjectui64v);

GL_IMPORT____(true,  PFNGLBINDVERTEXARRAYPROC,                   glBindVertexArray);
GL_IMPORT____(true,  PFNGLDELETEVERTEXARRAYSPROC,                glDeleteVertexArrays);
GL_IMPORT____(true,  PFNGLGENVERTEXARRAYSPROC,                   glGenVertexArrays);

GL_IMPORT____(true,  PFNGLSTENCILFUNCSEPARATEPROC,               glStencilFuncSeparate);
GL_IMPORT____(true,  PFNGLSTENCILMASKSEPARATEPROC,               glStencilMaskSeparate);
GL_IMPORT____(true,  PFNGLSTENCILOPSEPARATEPROC,                 glStencilOpSeparate);

GL_IMPORT____(true,  PFNGLBLENDFUNCSEPARATEPROC,                 glBlendFuncSeparate);
GL_IMPORT____(true,  PFNGLBLENDEQUATIONSEPARATEPROC,             glBlendEquationSeparate);
GL_IMPORT____(true,  PFNGLBLENDCOLORPROC,                        glBlendColor);

GL_IMPORT_ARB(true,  PFNGLDEBUGMESSAGECONTROLARBPROC,            glDebugMessageControl);
GL_IMPORT_ARB(true,  PFNGLDEBUGMESSAGEINSERTARBPROC,             glDebugMessageInsert);
GL_IMPORT_ARB(true,  PFNGLDEBUGMESSAGECALLBACKARBPROC,           glDebugMessageCallback);
GL_IMPORT_ARB(true,  PFNGLGETDEBUGMESSAGELOGARBPROC,             glGetDebugMessageLog);

GL_IMPORT____(true,  PFNGLGENSAMPLERSPROC,                       glGenSamplers);
GL_IMPORT____(true,  PFNGLDELETESAMPLERSPROC,                    glDeleteSamplers);
GL_IMPORT____(true,  PFNGLBINDSAMPLERPROC,                       glBindSampler);
GL_IMPORT____(true,  PFNGLSAMPLERPARAMETERIPROC,                 glSamplerParameteri);
GL_IMPORT____(true,  PFNGLSAMPLERPARAMETERFPROC,                 glSamplerParameterf);

#if BGFX_CONFIG_DEBUG_GREMEDY
GL_IMPORT____(true,  PFNGLSTRINGMARKERGREMEDYPROC,               glStringMarkerGREMEDY);
GL_IMPORT____(true,  PFNGLFRAMETERMINATORGREMEDYPROC,            glFrameTerminatorGREMEDY);
#endif // BGFX_CONFIG_DEBUG_GREMEDY

#elif BGFX_CONFIG_RENDERER_OPENGLES2

// OpenGL ES 2.0 Reference Pages
// http://www.khronos.org/opengles/sdk/docs/man/

GL_IMPORT____(true,  PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC,    glGetTranslatedShaderSourceANGLE);
GL_IMPORT____(true,  PFNGLGETPROGRAMBINARYOESPROC,               glGetProgramBinaryOES);
GL_IMPORT____(true,  PFNGLPROGRAMBINARYOESPROC,                  glProgramBinaryOES);
GL_IMPORT____(true,  PFNGLTEXIMAGE3DOESPROC,                     glTexImage3DOES);
GL_IMPORT____(true,  PFNGLTEXSUBIMAGE3DOESPROC,                  glTexSubImage3DOES);
GL_IMPORT____(true,  PFNGLCOMPRESSEDTEXIMAGE3DOESPROC,           glCompressedTexImage3DOES);
GL_IMPORT____(true,  PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC,        glCompressedTexSubImage3DOES);

GL_IMPORT____(true,  PFNGLBINDVERTEXARRAYOESPROC,                glBindVertexArrayOES);
GL_IMPORT____(true,  PFNGLDELETEVERTEXARRAYSOESPROC,             glDeleteVertexArraysOES);
GL_IMPORT____(true,  PFNGLGENVERTEXARRAYSOESPROC,                glGenVertexArraysOES);

#endif // BGFX_CONFIG_RENDERER_

#if BGFX_CONFIG_RENDERER_OPENGL
GL_IMPORT_ARB(true,  PFNGLVERTEXATTRIBDIVISORBGFXPROC,           glVertexAttribDivisor);
GL_IMPORT_ARB(true,  PFNGLDRAWARRAYSINSTANCEDBGFXPROC,           glDrawArraysInstanced);
GL_IMPORT_ARB(true,  PFNGLDRAWELEMENTSINSTANCEDBGFXPROC,         glDrawElementsInstanced);
#elif BGFX_CONFIG_RENDERER_OPENGLES2
GL_IMPORT____(true,  PFNGLVERTEXATTRIBDIVISORBGFXPROC,           glVertexAttribDivisor);
GL_IMPORT____(true,  PFNGLDRAWARRAYSINSTANCEDBGFXPROC,           glDrawArraysInstanced);
GL_IMPORT____(true,  PFNGLDRAWELEMENTSINSTANCEDBGFXPROC,         glDrawElementsInstanced);
#endif // !BGFX_CONFIG_RENDERER_OPENGLES3

