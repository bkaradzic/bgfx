project "shaderc"
	uuid "f3cd2e90-52a4-11e1-b86c-0800200c9a66"
	kind "ConsoleApp"

	local GLSL_OPTIMIZER = (BGFX_DIR .. "3rdparty/glsl-optimizer/")
	local FCPP_DIR = (BGFX_DIR .. "3rdparty/fcpp/")

	configuration { "vs*" }
		includedirs {
			GLSL_OPTIMIZER .. "src/glsl/msvc",
		}

	configuration {}

	includedirs {
		BGFX_DIR .. "../bx/include",

		FCPP_DIR,

		GLSL_OPTIMIZER .. "include",
		GLSL_OPTIMIZER .. "include/c99",
		GLSL_OPTIMIZER .. "src/mesa",
		GLSL_OPTIMIZER .. "src/mapi",
		GLSL_OPTIMIZER .. "src/glsl",
	}

	files {
		BGFX_DIR .. "tools/shaderc.cpp",
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
		GLSL_OPTIMIZER .. "src/glsl/main.cpp",
		GLSL_OPTIMIZER .. "src/glsl/builtin_stubs.cpp",
	}

	links {
		"d3dx9",
		"d3dcompiler",
		"dxguid",
	}
