project "shaderc"
	uuid "f3cd2e90-52a4-11e1-b86c-0800200c9a66"
	kind "ConsoleApp"

	local GLSL_OPTIMIZER = (BGFX_DIR .. "3rdparty/glsl-optimizer/")

	configuration { "vs*" }
		includedirs {
			GLSL_OPTIMIZER .. "src/glsl/msvc",
		}

	configuration {}

	includedirs {
		BGFX_DIR .. "../bx/include",

		BGFX_DIR .. "3rdparty/fcpp",

		GLSL_OPTIMIZER .. "include",
		GLSL_OPTIMIZER .. "include/c99",
		GLSL_OPTIMIZER .. "src/mesa",
		GLSL_OPTIMIZER .. "src/mapi",
		GLSL_OPTIMIZER .. "src/glsl",
	}

	files {
		BGFX_DIR .. "3rdparty/tools/shaderc.cpp",
		BGFX_DIR .. "3rdparty/fcpp/**.h",
		BGFX_DIR .. "3rdparty/fcpp/cpp1.c",
		BGFX_DIR .. "3rdparty/fcpp/cpp2.c",
		BGFX_DIR .. "3rdparty/fcpp/cpp3.c",
		BGFX_DIR .. "3rdparty/fcpp/cpp4.c",
		BGFX_DIR .. "3rdparty/fcpp/cpp5.c",
		BGFX_DIR .. "3rdparty/fcpp/cpp6.c",
		BGFX_DIR .. "3rdparty/fcpp/cpp6.c",

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
	}
