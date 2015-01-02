--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project "shaderc"
	uuid "f3cd2e90-52a4-11e1-b86c-0800200c9a66"
	kind "ConsoleApp"

	local GLSL_OPTIMIZER = (BGFX_DIR .. "3rdparty/glsl-optimizer/")
	local FCPP_DIR = (BGFX_DIR .. "3rdparty/fcpp/")

	includedirs {
		GLSL_OPTIMIZER .. "src",
	}

	configuration { "vs*" }
		includedirs {
			GLSL_OPTIMIZER .. "src/glsl/msvc",
		}

		defines { -- glsl-optimizer
			"__STDC__",
			"__STDC_VERSION__=199901L",
			"strdup=_strdup",
			"alloca=_alloca",
			"isascii=__isascii",
		}

		buildoptions {
			"/wd4996" -- warning C4996: 'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup.
		}

	configuration { "mingw* or linux or osx" }
		buildoptions {
			"-fno-strict-aliasing" -- glsl-optimizer has bugs if strict aliasing is used.
		}

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration { "windows", "vs*" }
		includedirs {
			GLSL_OPTIMIZER .. "include/c99",
		}

	configuration { "windows" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}

		links {
			"d3dx9",
			"d3dcompiler",
			"dxguid",
		}

	configuration {}

	defines { -- fcpp
		"NINCLUDE=64",
		"NWORK=65536",
		"NBUFF=65536",
		"OLD_PREPROCESSOR=0",
	}

	includedirs {
		BX_DIR   .. "include",
		BGFX_DIR .. "include",

		FCPP_DIR,

		GLSL_OPTIMIZER .. "include",
		GLSL_OPTIMIZER .. "src/mesa",
		GLSL_OPTIMIZER .. "src/mapi",
		GLSL_OPTIMIZER .. "src/glsl",
	}

	files {
		BGFX_DIR .. "tools/shaderc/**.cpp",
		BGFX_DIR .. "tools/shaderc/**.h",
		BGFX_DIR .. "src/vertexdecl.**",

		FCPP_DIR .. "**.h",
		FCPP_DIR .. "cpp1.c",
		FCPP_DIR .. "cpp2.c",
		FCPP_DIR .. "cpp3.c",
		FCPP_DIR .. "cpp4.c",
		FCPP_DIR .. "cpp5.c",
		FCPP_DIR .. "cpp6.c",
		FCPP_DIR .. "cpp6.c",

		GLSL_OPTIMIZER .. "src/mesa/**.c",
		GLSL_OPTIMIZER .. "src/glsl/**.cpp",
		GLSL_OPTIMIZER .. "src/mesa/**.h",
		GLSL_OPTIMIZER .. "src/glsl/**.c",
		GLSL_OPTIMIZER .. "src/glsl/**.cpp",
		GLSL_OPTIMIZER .. "src/glsl/**.h",
		GLSL_OPTIMIZER .. "src/util/**.c",
		GLSL_OPTIMIZER .. "src/util/**.h",
	}

	excludes {
		GLSL_OPTIMIZER .. "src/glsl/glcpp/glcpp.c",
		GLSL_OPTIMIZER .. "src/glsl/glcpp/tests/**",
		GLSL_OPTIMIZER .. "src/glsl/glcpp/**.l",
		GLSL_OPTIMIZER .. "src/glsl/glcpp/**.y",
		GLSL_OPTIMIZER .. "src/glsl/ir_set_program_inouts.cpp",
		GLSL_OPTIMIZER .. "src/glsl/main.cpp",
		GLSL_OPTIMIZER .. "src/glsl/builtin_stubs.cpp",
	}

	strip()
