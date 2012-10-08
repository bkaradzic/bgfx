#include <string>
#include <vector>
#include <time.h>
#include "../src/glsl/glsl_optimizer.h"

#if __linux__
#define GOT_GFX 0
#else
#define GOT_GFX 1
#endif

#if GOT_GFX

#ifdef _MSC_VER
#define GOT_MORE_THAN_GLSL_120 1
#include <windows.h>
#include <gl/GL.h>
extern "C" {
typedef char GLcharARB;		/* native character */
typedef unsigned int GLhandleARB;	/* shader object handle */
#define GL_VERTEX_SHADER_ARB              0x8B31
#define GL_FRAGMENT_SHADER_ARB            0x8B30
#define GL_OBJECT_COMPILE_STATUS_ARB      0x8B81
typedef void (WINAPI * PFNGLDELETEOBJECTARBPROC) (GLhandleARB obj);
typedef GLhandleARB (WINAPI * PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void (WINAPI * PFNGLSHADERSOURCEARBPROC) (GLhandleARB shaderObj, GLsizei count, const GLcharARB* *string, const GLint *length);
typedef void (WINAPI * PFNGLCOMPILESHADERARBPROC) (GLhandleARB shaderObj);
typedef void (WINAPI * PFNGLGETINFOLOGARBPROC) (GLhandleARB obj, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
typedef void (WINAPI * PFNGLGETOBJECTPARAMETERIVARBPROC) (GLhandleARB obj, GLenum pname, GLint *params);
static PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
static PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
static PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
static PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
static PFNGLGETINFOLOGARBPROC glGetInfoLogARB;
static PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
}
#else
#define GOT_MORE_THAN_GLSL_120 0
#include <OpenGL/OpenGL.h>
#include <AGL/agl.h>
#include <dirent.h>
#endif

#else // GOT_GFX
#define GOT_MORE_THAN_GLSL_120 0
#include <cstdio>
#include <cstring>
#include "dirent.h"
#include "GL/gl.h"
#include "GL/glext.h"
#endif


#ifndef _MSC_VER
#include <unistd.h>
#endif


static bool InitializeOpenGL ()
{
	bool hasGLSL = false;

#if GOT_GFX

#ifdef _MSC_VER
	// setup minimal required GL
	HWND wnd = CreateWindowA(
		"STATIC",
		"GL",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
		0, 0, 16, 16,
		NULL, NULL,
		GetModuleHandle(NULL), NULL );
	HDC dc = GetDC( wnd );

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA, 32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		16, 0,
		0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	int fmt = ChoosePixelFormat( dc, &pfd );
	SetPixelFormat( dc, fmt, &pfd );

	HGLRC rc = wglCreateContext( dc );
	wglMakeCurrent( dc, rc );

#else
	GLint attributes[16];
	int i = 0;
	attributes[i++]=AGL_RGBA;
	attributes[i++]=AGL_PIXEL_SIZE;
	attributes[i++]=32;
	attributes[i++]=AGL_NO_RECOVERY;
	attributes[i++]=AGL_NONE;
	
	AGLPixelFormat pixelFormat = aglChoosePixelFormat(NULL,0,attributes);
	AGLContext agl = aglCreateContext(pixelFormat, NULL);
	aglSetCurrentContext (agl);

#endif

	// check if we have GLSL
	const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
	hasGLSL = strstr(extensions, "GL_ARB_shader_objects") && strstr(extensions, "GL_ARB_vertex_shader") && strstr(extensions, "GL_ARB_fragment_shader");
	
#ifdef _MSC_VER
	if (hasGLSL)
	{
		glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC)wglGetProcAddress("glDeleteObjectARB");
		glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
		glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB");
		glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB");
		glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB");
		glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB");
	}
#endif

#endif
	return hasGLSL;
}

static void replace_string (std::string& target, const std::string& search, const std::string& replace, size_t startPos)
{
	if (search.empty())
		return;
	
	std::string::size_type p = startPos;
	while ((p = target.find (search, p)) != std::string::npos)
	{
		target.replace (p, search.size (), replace);
		p += replace.size ();
	}
}

static bool CheckGLSL (bool vertex, bool gles, const std::string& testName, const char* prefix, const std::string& source)
{
	#if !GOT_GFX
	return true; // just assume it's ok
	#endif

	#if !GOT_MORE_THAN_GLSL_120
	if (source.find("#version 140") != std::string::npos)
		return true;
	#endif
	
	std::string src;
	if (gles)
	{
		src += "#define lowp\n";
		src += "#define mediump\n";
		src += "#define highp\n";
		src += "#define texture2DLodEXT texture2DLod\n";
		src += "#define texture2DProjLodEXT texture2DProjLod\n";
		src += "float shadow2DEXT (sampler2DShadow s, vec3 p) { return shadow2D(s,p).r; }\n";
		src += "float shadow2DProjEXT (sampler2DShadow s, vec4 p) { return shadow2DProj(s,p).r; }\n";
	}
	src += source;
	if (gles)
	{
		replace_string (src, "GL_EXT_shader_texture_lod", "GL_ARB_shader_texture_lod", 0);
		replace_string (src, "#extension GL_OES_standard_derivatives : require", "", 0);
		replace_string (src, "#extension GL_EXT_shadow_samplers : require", "", 0);
	}
	const char* sourcePtr = src.c_str();

	
	GLhandleARB shader = glCreateShaderObjectARB (vertex ? GL_VERTEX_SHADER_ARB : GL_FRAGMENT_SHADER_ARB);
	glShaderSourceARB (shader, 1, &sourcePtr, NULL);
	glCompileShaderARB (shader);
	GLint status;
	glGetObjectParameterivARB (shader, GL_OBJECT_COMPILE_STATUS_ARB, &status);
	bool res = true;
	if (status == 0)
	{
		char log[4096];
		GLsizei logLength;
		glGetInfoLogARB (shader, sizeof(log), &logLength, log);
		printf ("\n  %s: real glsl compiler error on %s:\n%s\n", testName.c_str(), prefix, log);
		res = false;
	}
	glDeleteObjectARB (shader);
	return res;
}


static bool ReadStringFromFile (const char* pathName, std::string& output)
{
	FILE* file = fopen( pathName, "rb" );
	if (file == NULL)
		return false;
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (length < 0)
	{
		fclose( file );
		return false;
	}
	output.resize(length);
	int readLength = fread(&*output.begin(), 1, length, file);
	fclose(file);
	if (readLength != length)
	{
		output.clear();
		return false;
	}
	return true;
}

bool EndsWith (const std::string& str, const std::string& sub)
{
	return (str.size() >= sub.size()) && (strncmp (str.c_str()+str.size()-sub.size(), sub.c_str(), sub.size())==0);
}

typedef std::vector<std::string> StringVector;

static StringVector GetFiles (const std::string& folder, const std::string& endsWith)
{
	StringVector res;

	#ifdef _MSC_VER
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA ((folder+"/*"+endsWith).c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return res;

	do {
		res.push_back (FindFileData.cFileName);
	} while (FindNextFileA (hFind, &FindFileData));

	FindClose (hFind);
	
	#else
	
	DIR *dirp;
	struct dirent *dp;

	if ((dirp = opendir(folder.c_str())) == NULL)
		return res;

	while ( (dp = readdir(dirp)) )
	{
		std::string fname = dp->d_name;
		if (fname == "." || fname == "..")
			continue;
		if (!EndsWith (fname, endsWith))
			continue;
		res.push_back (fname);
	}
	closedir(dirp);
	
	#endif

	return res;
}

static void DeleteFile (const std::string& path)
{
	#ifdef _MSC_VER
	DeleteFileA (path.c_str());
	#else
	unlink (path.c_str());
	#endif
}

static void MassageVertexForGLES (std::string& s)
{
	std::string pre;
	pre += "#define gl_Vertex _glesVertex\nattribute highp vec4 _glesVertex;\n";
	pre += "#define gl_Normal _glesNormal\nattribute mediump vec3 _glesNormal;\n";
	pre += "#define gl_MultiTexCoord0 _glesMultiTexCoord0\nattribute highp vec4 _glesMultiTexCoord0;\n";
	pre += "#define gl_MultiTexCoord1 _glesMultiTexCoord1\nattribute highp vec4 _glesMultiTexCoord1;\n";
	pre += "#define gl_Color _glesColor\nattribute lowp vec4 _glesColor;\n";
	s = pre + s;
}

static void MassageFragmentForGLES (std::string& s)
{
	std::string pre;
	s = pre + s;
}

static bool TestFile (glslopt_ctx* ctx, bool vertex,
	const std::string& testName,
	const std::string& inputPath,
	const std::string& hirPath,
	const std::string& outputPath,
	bool gles,
	bool doCheckGLSL)
{
	std::string input;
	if (!ReadStringFromFile (inputPath.c_str(), input))
	{
		printf ("\n  %s: failed to read input file\n", testName.c_str());
		return false;
	}
	if (doCheckGLSL)
	{
		if (!CheckGLSL (vertex, gles, testName, "input", input.c_str()))
			return false;
	}

	if (gles)
	{
		if (vertex)
			MassageVertexForGLES (input);
		else
			MassageFragmentForGLES (input);
	}

	bool res = true;

	glslopt_shader_type type = vertex ? kGlslOptShaderVertex : kGlslOptShaderFragment;
	glslopt_shader* shader = glslopt_optimize (ctx, type, input.c_str(), 0);

	bool optimizeOk = glslopt_get_status(shader);
	if (optimizeOk)
	{
		std::string textHir = glslopt_get_raw_output (shader);
		std::string textOpt = glslopt_get_output (shader);
		std::string outputHir;
		ReadStringFromFile (hirPath.c_str(), outputHir);
		std::string outputOpt;
		ReadStringFromFile (outputPath.c_str(), outputOpt);

		if (textHir != outputHir)
		{
			// write output
			FILE* f = fopen (hirPath.c_str(), "wb");
			if (!f)
			{
				printf ("\n  %s: can't write to IR file!\n", testName.c_str());
			}
			else
			{
				fwrite (textHir.c_str(), 1, textHir.size(), f);
				fclose (f);
			}
			printf ("\n  %s: does not match raw output\n", testName.c_str());
			res = false;
		}

		if (textOpt != outputOpt)
		{
			// write output
			FILE* f = fopen (outputPath.c_str(), "wb");
			if (!f)
			{
				printf ("\n  %s: can't write to optimized file!\n", testName.c_str());
			}
			else
			{
				fwrite (textOpt.c_str(), 1, textOpt.size(), f);
				fclose (f);
			}
			printf ("\n  %s: does not match optimized output\n", testName.c_str());
			res = false;
		}
		if (res && doCheckGLSL && !CheckGLSL (vertex, gles, testName, "raw", textHir.c_str()))
			res = false;
		if (res && doCheckGLSL && !CheckGLSL (vertex, gles, testName, "optimized", textOpt.c_str()))
			res = false;
	}
	else
	{
		printf ("\n  %s: optimize error: %s\n", testName.c_str(), glslopt_get_log(shader));
		res = false;
	}

	glslopt_shader_delete (shader);

	return res;
}


int main (int argc, const char** argv)
{
	if (argc < 2)
	{
		printf ("USAGE: glsloptimizer testfolder\n");
		return 1;
	}

	bool hasOpenGL = InitializeOpenGL ();
	glslopt_ctx* ctx[2] = {
		glslopt_initialize(true),
		glslopt_initialize(false),
	};

	std::string baseFolder = argv[1];

	clock_t time0 = clock();

	static const char* kTypeName[2] = { "vertex", "fragment" };
	size_t tests = 0;
	size_t errors = 0;
	for (int type = 0; type < 2; ++type)
	{
		std::string testFolder = baseFolder + "/" + kTypeName[type];

		static const char* kAPIName[2] = { "OpenGL ES 2.0", "OpenGL" };
		static const char* kApiIn [2] = {"-inES.txt", "-in.txt"};
		static const char* kApiIR [2] = {"-irES.txt", "-ir.txt"};
		static const char* kApiOut[2] = {"-outES.txt", "-out.txt"};
		for (int api = 0; api < 2; ++api)
		{
			printf ("\n** running %s tests for %s...\n", kTypeName[type], kAPIName[api]);
			StringVector inputFiles = GetFiles (testFolder, kApiIn[api]);

			size_t n = inputFiles.size();
			for (size_t i = 0; i < n; ++i)
			{
				std::string inname = inputFiles[i];
				//if (inname != "ast-in.txt")
				//	continue;
				std::string hirname = inname.substr (0,inname.size()-strlen(kApiIn[api])) + kApiIR[api];
				std::string outname = inname.substr (0,inname.size()-strlen(kApiIn[api])) + kApiOut[api];
				bool ok = TestFile (ctx[api], type==0, inname, testFolder + "/" + inname, testFolder + "/" + hirname, testFolder + "/" + outname, api==0, hasOpenGL);
				if (!ok)
				{
					++errors;
				}
				++tests;
			}
		}
	}
	clock_t time1 = clock();
	float timeDelta = float(time1-time0)/CLOCKS_PER_SEC;

	if (errors != 0)
		printf ("\n**** %i tests (%.2fsec), %i !!!FAILED!!!\n", tests, timeDelta, errors);
	else
		printf ("\n**** %i tests (%.2fsec) succeeded\n", tests, timeDelta);
	
	// 3.25s
	// with builtin call linking, 3.84s

	for (int i = 0; i < 2; ++i)
		glslopt_cleanup (ctx[i]);

	return errors ? 1 : 0;
}
