/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef GL_IMPORT
#	error GL_IMPORT must be defined!
#endif // GL_IMPORT

GL_IMPORT(PFNGLACTIVETEXTUREPROC,            glActiveTexture);
GL_IMPORT(PFNGLCOMPRESSEDTEXIMAGE2DPROC,     glCompressedTexImage2D);
GL_IMPORT(PFNGLBINDBUFFERPROC,               glBindBuffer);
GL_IMPORT(PFNGLDELETEBUFFERSPROC,            glDeleteBuffers);
GL_IMPORT(PFNGLGENBUFFERSPROC,               glGenBuffers);
GL_IMPORT(PFNGLBUFFERDATAPROC,               glBufferData);
GL_IMPORT(PFNGLBUFFERSUBDATAPROC,            glBufferSubData);
GL_IMPORT(PFNGLCREATEPROGRAMPROC,            glCreateProgram);
GL_IMPORT(PFNGLCREATESHADERPROC,             glCreateShader);
GL_IMPORT(PFNGLDELETEPROGRAMPROC,            glDeleteProgram);
GL_IMPORT(PFNGLDELETESHADERPROC,             glDeleteShader);
GL_IMPORT(PFNGLATTACHSHADERPROC,             glAttachShader);
GL_IMPORT(PFNGLCOMPILESHADERPROC,            glCompileShader);
GL_IMPORT(PFNGLSHADERSOURCEPROC,             glShaderSource);
GL_IMPORT(PFNGLGETSHADERIVPROC,              glGetShaderiv);
GL_IMPORT(PFNGLGETSHADERINFOLOGPROC,         glGetShaderInfoLog);
GL_IMPORT(PFNGLLINKPROGRAMPROC,              glLinkProgram);
GL_IMPORT(PFNGLGETPROGRAMIVPROC,             glGetProgramiv);
GL_IMPORT(PFNGLGETPROGRAMINFOLOGPROC,        glGetProgramInfoLog);
GL_IMPORT(PFNGLUSEPROGRAMPROC,               glUseProgram);
GL_IMPORT(PFNGLGETACTIVEATTRIBPROC,          glGetActiveAttrib);
GL_IMPORT(PFNGLGETATTRIBLOCATIONPROC,        glGetAttribLocation);
GL_IMPORT(PFNGLGETACTIVEUNIFORMPROC,         glGetActiveUniform);
GL_IMPORT(PFNGLGETUNIFORMLOCATIONPROC,       glGetUniformLocation);
GL_IMPORT(PFNGLENABLEVERTEXATTRIBARRAYPROC,  glEnableVertexAttribArray);
GL_IMPORT(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
GL_IMPORT(PFNGLVERTEXATTRIBPOINTERPROC,      glVertexAttribPointer);
GL_IMPORT(PFNGLVERTEXATTRIB1FPROC,           glVertexAttrib1f);
GL_IMPORT(PFNGLVERTEXATTRIB2FPROC,           glVertexAttrib2f);
GL_IMPORT(PFNGLVERTEXATTRIB3FPROC,           glVertexAttrib3f);
GL_IMPORT(PFNGLVERTEXATTRIB4FPROC,           glVertexAttrib4f);
GL_IMPORT(PFNGLBINDFRAMEBUFFERPROC,          glBindFramebuffer);
GL_IMPORT(PFNGLGENFRAMEBUFFERSPROC,          glGenFramebuffers);
GL_IMPORT(PFNGLDELETEFRAMEBUFFERSPROC,       glDeleteFramebuffers);
GL_IMPORT(PFNGLCHECKFRAMEBUFFERSTATUSPROC,   glCheckFramebufferStatus);
GL_IMPORT(PFNGLFRAMEBUFFERRENDERBUFFERPROC,  glFramebufferRenderbuffer);
GL_IMPORT(PFNGLFRAMEBUFFERTEXTURE2DPROC,     glFramebufferTexture2D);
GL_IMPORT(PFNGLBINDRENDERBUFFERPROC,         glBindRenderbuffer);
GL_IMPORT(PFNGLGENRENDERBUFFERSPROC,         glGenRenderbuffers);
GL_IMPORT(PFNGLDELETERENDERBUFFERSPROC,      glDeleteRenderbuffers);
GL_IMPORT(PFNGLRENDERBUFFERSTORAGEPROC,      glRenderbufferStorage);
GL_IMPORT(PFNGLUNIFORM1IPROC,                glUniform1i);
GL_IMPORT(PFNGLUNIFORM1IVPROC,               glUniform1iv);
GL_IMPORT(PFNGLUNIFORM1FPROC,                glUniform1f);
GL_IMPORT(PFNGLUNIFORM1FVPROC,               glUniform1fv);
GL_IMPORT(PFNGLUNIFORM2FVPROC,               glUniform2fv);
GL_IMPORT(PFNGLUNIFORM3FVPROC,               glUniform3fv);
GL_IMPORT(PFNGLUNIFORM4FVPROC,               glUniform4fv);
GL_IMPORT(PFNGLUNIFORMMATRIX3FVPROC,         glUniformMatrix3fv);
GL_IMPORT(PFNGLUNIFORMMATRIX4FVPROC,         glUniformMatrix4fv);
