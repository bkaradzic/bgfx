/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef GL_IMPORT
#	error GL_IMPORT(_optional, _proto, _func) must be defined!
#endif // GL_IMPORT

GL_IMPORT(false, PFNGLACTIVETEXTUREPROC,            glActiveTexture);
GL_IMPORT(false, PFNGLCOMPRESSEDTEXIMAGE2DPROC,     glCompressedTexImage2D);
GL_IMPORT(false, PFNGLBINDBUFFERPROC,               glBindBuffer);
GL_IMPORT(false, PFNGLDELETEBUFFERSPROC,            glDeleteBuffers);
GL_IMPORT(false, PFNGLGENBUFFERSPROC,               glGenBuffers);
GL_IMPORT(false, PFNGLBUFFERDATAPROC,               glBufferData);
GL_IMPORT(false, PFNGLBUFFERSUBDATAPROC,            glBufferSubData);
GL_IMPORT(false, PFNGLCREATEPROGRAMPROC,            glCreateProgram);
GL_IMPORT(false, PFNGLCREATESHADERPROC,             glCreateShader);
GL_IMPORT(false, PFNGLDELETEPROGRAMPROC,            glDeleteProgram);
GL_IMPORT(false, PFNGLDELETESHADERPROC,             glDeleteShader);
GL_IMPORT(false, PFNGLATTACHSHADERPROC,             glAttachShader);
GL_IMPORT(false, PFNGLCOMPILESHADERPROC,            glCompileShader);
GL_IMPORT(false, PFNGLSHADERSOURCEPROC,             glShaderSource);
GL_IMPORT(false, PFNGLGETSHADERIVPROC,              glGetShaderiv);
GL_IMPORT(false, PFNGLGETSHADERINFOLOGPROC,         glGetShaderInfoLog);
GL_IMPORT(false, PFNGLLINKPROGRAMPROC,              glLinkProgram);
GL_IMPORT(false, PFNGLGETPROGRAMIVPROC,             glGetProgramiv);
GL_IMPORT(false, PFNGLGETPROGRAMINFOLOGPROC,        glGetProgramInfoLog);
GL_IMPORT(false, PFNGLUSEPROGRAMPROC,               glUseProgram);
GL_IMPORT(false, PFNGLGETACTIVEATTRIBPROC,          glGetActiveAttrib);
GL_IMPORT(false, PFNGLGETATTRIBLOCATIONPROC,        glGetAttribLocation);
GL_IMPORT(false, PFNGLGETACTIVEUNIFORMPROC,         glGetActiveUniform);
GL_IMPORT(false, PFNGLGETUNIFORMLOCATIONPROC,       glGetUniformLocation);
GL_IMPORT(false, PFNGLENABLEVERTEXATTRIBARRAYPROC,  glEnableVertexAttribArray);
GL_IMPORT(false, PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
GL_IMPORT(false, PFNGLVERTEXATTRIBPOINTERPROC,      glVertexAttribPointer);
GL_IMPORT(false, PFNGLVERTEXATTRIB1FPROC,           glVertexAttrib1f);
GL_IMPORT(false, PFNGLVERTEXATTRIB2FPROC,           glVertexAttrib2f);
GL_IMPORT(false, PFNGLVERTEXATTRIB3FPROC,           glVertexAttrib3f);
GL_IMPORT(false, PFNGLVERTEXATTRIB4FPROC,           glVertexAttrib4f);
GL_IMPORT(false, PFNGLBINDFRAMEBUFFERPROC,          glBindFramebuffer);
GL_IMPORT(false, PFNGLGENFRAMEBUFFERSPROC,          glGenFramebuffers);
GL_IMPORT(false, PFNGLDELETEFRAMEBUFFERSPROC,       glDeleteFramebuffers);
GL_IMPORT(false, PFNGLCHECKFRAMEBUFFERSTATUSPROC,   glCheckFramebufferStatus);
GL_IMPORT(false, PFNGLFRAMEBUFFERRENDERBUFFERPROC,  glFramebufferRenderbuffer);
GL_IMPORT(false, PFNGLFRAMEBUFFERTEXTURE2DPROC,     glFramebufferTexture2D);
GL_IMPORT(false, PFNGLBINDRENDERBUFFERPROC,         glBindRenderbuffer);
GL_IMPORT(false, PFNGLGENRENDERBUFFERSPROC,         glGenRenderbuffers);
GL_IMPORT(false, PFNGLDELETERENDERBUFFERSPROC,      glDeleteRenderbuffers);
GL_IMPORT(false, PFNGLRENDERBUFFERSTORAGEPROC,      glRenderbufferStorage);
GL_IMPORT(false, PFNGLUNIFORM1IPROC,                glUniform1i);
GL_IMPORT(false, PFNGLUNIFORM1IVPROC,               glUniform1iv);
GL_IMPORT(false, PFNGLUNIFORM1FPROC,                glUniform1f);
GL_IMPORT(false, PFNGLUNIFORM1FVPROC,               glUniform1fv);
GL_IMPORT(false, PFNGLUNIFORM2FVPROC,               glUniform2fv);
GL_IMPORT(false, PFNGLUNIFORM3FVPROC,               glUniform3fv);
GL_IMPORT(false, PFNGLUNIFORM4FVPROC,               glUniform4fv);
GL_IMPORT(false, PFNGLUNIFORMMATRIX3FVPROC,         glUniformMatrix3fv);
GL_IMPORT(false, PFNGLUNIFORMMATRIX4FVPROC,         glUniformMatrix4fv);

GL_IMPORT(true,  PFNGLGETPROGRAMBINARYPROC,         glGetProgramBinary);
GL_IMPORT(true,  PFNGLPROGRAMBINARYPROC,            glProgramBinary);
GL_IMPORT(true,  PFNGLPROGRAMPARAMETERIPROC,        glProgramParameteri);
