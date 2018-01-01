--
-- Copyright 2010-2018 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

group "tools/shaderc"

local GLSL_OPTIMIZER = path.join(BGFX_DIR, "3rdparty/glsl-optimizer")
local FCPP_DIR = path.join(BGFX_DIR, "3rdparty/fcpp")

project "glslang"
	kind "StaticLib"

	local GLSLANG = path.join(BGFX_DIR, "3rdparty/glslang")

	configuration { "vs2012" }
		defines {
			"atoll=_atoi64",
			"strtoll=_strtoi64",
			"strtoull=_strtoui64",
		}

	configuration { "vs*" }
		buildoptions {
			"/wd4005", -- warning C4005: '_CRT_SECURE_NO_WARNINGS': macro redefinition
			"/wd4100", -- warning C4100: 'inclusionDepth' : unreferenced formal parameter
			"/wd4127", -- warning C4127: conditional expression is constant
			"/wd4244", -- warning C4244: '=': conversion from 'int' to 'char', possible loss of data
			"/wd4456", -- warning C4456: declaration of 'feature' hides previous local declaration
			"/wd4457", -- warning C4457: declaration of 'token' hides function parameter
			"/wd4458", -- warning C4458: declaration of 'language' hides class member
			"/wd4702", -- warning C4702: unreachable code
		}

	configuration { "not vs*" }
		buildoptions {
--			"-Wno-deprecated-register",
			"-Wno-ignored-qualifiers",
--			"-Wno-inconsistent-missing-override",
			"-Wno-missing-field-initializers",
			"-Wno-reorder",
			"-Wno-return-type",
			"-Wno-shadow",
			"-Wno-sign-compare",
			"-Wno-undef",
			"-Wno-unknown-pragmas",
			"-Wno-unused-function",
			"-Wno-unused-parameter",
			"-Wno-unused-variable",
		}

	configuration { "osx" }
		buildoptions {
			"-Wno-c++11-extensions",
			"-Wno-unused-const-variable",
		}

	configuration { "linux-*" }
		buildoptions {
			"-Wno-unused-but-set-variable",
		}

	configuration {}
		defines {
			"ENABLE_HLSL=1",
		}

	includedirs {
		GLSLANG,
	}

	files {
		path.join(GLSLANG, "glslang/**.cpp"),
		path.join(GLSLANG, "glslang/**.h"),

		path.join(GLSLANG, "hlsl/**.cpp"),
		path.join(GLSLANG, "hlsl/**.h"),

		path.join(GLSLANG, "SPIRV/**.cpp"),
		path.join(GLSLANG, "SPIRV/**.h"),

		path.join(GLSLANG, "OGLCompilersDLL/**.cpp"),
		path.join(GLSLANG, "OGLCompilersDLL/**.h"),
	}

	removefiles {
		path.join(GLSLANG, "glslang/OSDependent/Unix/main.cpp"),
		path.join(GLSLANG, "glslang/OSDependent/Windows/main.cpp"),
	}

	configuration { "windows" }
		removefiles {
			path.join(GLSLANG, "glslang/OSDependent/Unix/**.cpp"),
			path.join(GLSLANG, "glslang/OSDependent/Unix/**.h"),
		}

	configuration { "not windows" }
		removefiles {
			path.join(GLSLANG, "glslang/OSDependent/Windows/**.cpp"),
			path.join(GLSLANG, "glslang/OSDependent/Windows/**.h"),
		}

	configuration {}

project "glsl-optimizer"
	kind "StaticLib"

	includedirs {
		path.join(GLSL_OPTIMIZER, "src"),
		path.join(GLSL_OPTIMIZER, "include"),
		path.join(GLSL_OPTIMIZER, "src/mesa"),
		path.join(GLSL_OPTIMIZER, "src/mapi"),
		path.join(GLSL_OPTIMIZER, "src/glsl"),
	}

	files {
		path.join(GLSL_OPTIMIZER, "src/mesa/**.c"),
		path.join(GLSL_OPTIMIZER, "src/glsl/**.cpp"),
		path.join(GLSL_OPTIMIZER, "src/mesa/**.h"),
		path.join(GLSL_OPTIMIZER, "src/glsl/**.c"),
		path.join(GLSL_OPTIMIZER, "src/glsl/**.cpp"),
		path.join(GLSL_OPTIMIZER, "src/glsl/**.h"),
		path.join(GLSL_OPTIMIZER, "src/util/**.c"),
		path.join(GLSL_OPTIMIZER, "src/util/**.h"),
	}

	removefiles {
		path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/glcpp.c"),
		path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/tests/**"),
		path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/**.l"),
		path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/**.y"),
		path.join(GLSL_OPTIMIZER, "src/glsl/ir_set_program_inouts.cpp"),
		path.join(GLSL_OPTIMIZER, "src/glsl/main.cpp"),
		path.join(GLSL_OPTIMIZER, "src/glsl/builtin_stubs.cpp"),
	}

	configuration { "Release" }
		flags {
			"Optimize",
		}

		removeflags {
			-- GCC 4.9 -O2 + -fno-strict-aliasing don't work together...
			"OptimizeSpeed",
		}

	configuration { "vs*" }
		includedirs {
			path.join(GLSL_OPTIMIZER, "src/glsl/msvc"),
		}

		defines { -- glsl-optimizer
			"__STDC__",
			"__STDC_VERSION__=199901L",
			"strdup=_strdup",
			"alloca=_alloca",
			"isascii=__isascii",
		}

		buildoptions {
			"/wd4100", -- error C4100: '' : unreferenced formal parameter
			"/wd4127", -- warning C4127: conditional expression is constant
			"/wd4132", -- warning C4132: 'deleted_key_value': const object should be initialized
			"/wd4189", -- warning C4189: 'interface_type': local variable is initialized but not referenced
			"/wd4204", -- warning C4204: nonstandard extension used: non-constant aggregate initializer
			"/wd4244", -- warning C4244: '=': conversion from 'const flex_int32_t' to 'YY_CHAR', possible loss of data
			"/wd4389", -- warning C4389: '!=': signed/unsigned mismatch
			"/wd4245", -- warning C4245: 'return': conversion from 'int' to 'unsigned int', signed/unsigned mismatch
			"/wd4701", -- warning C4701: potentially uninitialized local variable 'lower' used
			"/wd4702", -- warning C4702: unreachable code
			"/wd4706", -- warning C4706: assignment within conditional expression
			"/wd4996" -- warning C4996: 'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup.
		}

	configuration { "mingw* or linux or osx" }
		buildoptions {
			"-fno-strict-aliasing", -- glsl-optimizer has bugs if strict aliasing is used.
			"-Wno-unused-parameter",
		}

		removebuildoptions {
			"-Wshadow", -- glsl-optimizer is full of -Wshadow warnings ignore it.
		}

	configuration {}

project "fcpp"
	kind "StaticLib"

	defines { -- fcpp
		"NINCLUDE=64",
		"NWORK=65536",
		"NBUFF=65536",
		"OLD_PREPROCESSOR=0",
	}

	files {
		path.join(FCPP_DIR, "**.h"),
		path.join(FCPP_DIR, "cpp1.c"),
		path.join(FCPP_DIR, "cpp2.c"),
		path.join(FCPP_DIR, "cpp3.c"),
		path.join(FCPP_DIR, "cpp4.c"),
		path.join(FCPP_DIR, "cpp5.c"),
		path.join(FCPP_DIR, "cpp6.c"),
		path.join(FCPP_DIR, "cpp6.c"),
	}

	configuration { "vs*" }

		buildoptions {
			"/wd4055", -- warning C4055: 'type cast': from data pointer 'void *' to function pointer 'void (__cdecl *)(char *,void *)'
			"/wd4244", -- warning C4244: '=': conversion from 'const flex_int32_t' to 'YY_CHAR', possible loss of data
			"/wd4701", -- warning C4701: potentially uninitialized local variable 'lower' used
			"/wd4706", -- warning C4706: assignment within conditional expression
		}

	configuration { "not vs*" }
		buildoptions {
			"-Wno-implicit-fallthrough",
		}

	configuration {}

project "shaderc"
	kind "ConsoleApp"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),

		path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
		FCPP_DIR,

		path.join(BGFX_DIR, "3rdparty/glslang/glslang/Public"),
		path.join(BGFX_DIR, "3rdparty/glslang/glslang/Include"),
		path.join(BGFX_DIR, "3rdparty/glslang"),

		path.join(GLSL_OPTIMIZER, "include"),
		path.join(GLSL_OPTIMIZER, "src/glsl"),
	}

	links {
		"bx",
		"fcpp",
		"glslang",
		"glsl-optimizer",
	}

	files {
		path.join(BGFX_DIR, "tools/shaderc/**.cpp"),
		path.join(BGFX_DIR, "tools/shaderc/**.h"),
		path.join(BGFX_DIR, "src/vertexdecl.**"),
		path.join(BGFX_DIR, "src/shader_spirv.**"),
	}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration { "vs*" }
		includedirs {
			path.join(GLSL_OPTIMIZER, "include/c99"),
		}

	configuration { "vs20* or mingw*" }
		links {
			"psapi",
		}

	configuration {}

	if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-ext"), {
		path.join(BGFX_DIR, "scripts/shaderc.lua"), }) then

		if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-ext"), {
			path.join(BGFX_DIR, "tools/shaderc/shaderc_pssl.cpp"), }) then

			removefiles {
				path.join(BGFX_DIR, "tools/shaderc/shaderc_pssl.cpp"),
			}
		end

		dofile(path.join(BGFX_DIR, "../bgfx-ext/scripts/shaderc.lua") )
	end

	configuration { "osx or linux*" }
		links {
			"pthread",
		}

	configuration {}

	strip()

group "tools"
