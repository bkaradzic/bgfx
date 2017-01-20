--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

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
			"/wd4100", -- error C4100: 'inclusionDepth' : unreferenced formal parameter
		}

	configuration { "not vs*" }
		buildoptions {
			"-Wno-ignored-qualifiers",
			"-Wno-inconsistent-missing-override",
			"-Wno-missing-field-initializers",
			"-Wno-reorder",
			"-Wno-shadow",
			"-Wno-sign-compare",
			"-Wno-undef",
			"-Wno-unknown-pragmas",
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

project "shaderc"
	kind "ConsoleApp"

	local GLSL_OPTIMIZER = path.join(BGFX_DIR, "3rdparty/glsl-optimizer")
	local FCPP_DIR = path.join(BGFX_DIR, "3rdparty/fcpp")

	includedirs {
		path.join(GLSL_OPTIMIZER, "src"),
	}

	links {
		"bx",
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
			"/wd4996" -- warning C4996: 'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup.
		}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "mingw* or linux or osx" }
		buildoptions {
			"-fno-strict-aliasing", -- glsl-optimizer has bugs if strict aliasing is used.
			"-Wno-unused-parameter",
		}
		removebuildoptions {
			"-Wshadow", -- glsl-optimizer is full of -Wshadow warnings ignore it.
		}

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

	defines { -- fcpp
		"NINCLUDE=64",
		"NWORK=65536",
		"NBUFF=65536",
		"OLD_PREPROCESSOR=0",
	}

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "include"),

		path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
		FCPP_DIR,

		path.join(BGFX_DIR, "3rdparty/glslang/glslang/Public"),
		path.join(BGFX_DIR, "3rdparty/glslang/glslang/Include"),
		path.join(BGFX_DIR, "3rdparty/glslang"),
--		path.join(BGFX_DIR, "3rdparty/spirv-tools/include"),

		path.join(GLSL_OPTIMIZER, "include"),
		path.join(GLSL_OPTIMIZER, "src/mesa"),
		path.join(GLSL_OPTIMIZER, "src/mapi"),
		path.join(GLSL_OPTIMIZER, "src/glsl"),
	}

	files {
		path.join(BGFX_DIR, "tools/shaderc/**.cpp"),
		path.join(BGFX_DIR, "tools/shaderc/**.h"),
		path.join(BGFX_DIR, "src/vertexdecl.**"),
		path.join(BGFX_DIR, "src/shader_spirv.**"),

		path.join(FCPP_DIR, "**.h"),
		path.join(FCPP_DIR, "cpp1.c"),
		path.join(FCPP_DIR, "cpp2.c"),
		path.join(FCPP_DIR, "cpp3.c"),
		path.join(FCPP_DIR, "cpp4.c"),
		path.join(FCPP_DIR, "cpp5.c"),
		path.join(FCPP_DIR, "cpp6.c"),
		path.join(FCPP_DIR, "cpp6.c"),

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

	links {
		"glslang",
	}

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
