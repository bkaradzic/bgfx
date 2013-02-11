project "shaderc"
	uuid "f3cd2e90-52a4-11e1-b86c-0800200c9a66"
	kind "ConsoleApp"

	local GLSL_OPTIMIZER = (BGFX_DIR .. "3rdparty/glsl-optimizer/")
	local FCPP_DIR = (BGFX_DIR .. "3rdparty/fcpp/")

	configuration { "vs*" }
		includedirs {
			GLSL_OPTIMIZER .. "src/glsl/msvc",
		}

	configuration { "windows", "vs*" }
		buildoptions {
			"/wd\"4005\"", -- disable warning: macro redefinition
			"/wd\"4018\"", -- disable warning: signed/unsigned mismatch
			"/wd\"4065\"", -- disable warning: switch statement contains 'default' but no 'case' labels
			"/wd\"4090\"", -- disable warning: 'function' : different 'const' qualifiers
			"/wd\"4099\"", -- disable warning: type name first seen using 'class' now seen using 'struct'
			"/wd\"4244\"", -- disable warning: conversion from 'double' to 'float'
			"/wd\"4345\"", -- disable warning: behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
			"/wd\"4800\"", -- disable warning: forcing value to bool 'true' or 'false'
		}
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
	}

	includedirs {
		BX_DIR .. "include",

		FCPP_DIR,

		GLSL_OPTIMIZER .. "include",
		GLSL_OPTIMIZER .. "src/mesa",
		GLSL_OPTIMIZER .. "src/mapi",
		GLSL_OPTIMIZER .. "src/glsl",
	}

	files {
		BGFX_DIR .. "tools/shaderc/**.cpp",
		BGFX_DIR .. "tools/shaderc/**.h",
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

