--
-- Copyright 2010-2026 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
--

group "tools/texturev"

project "l-smash"
	kind "StaticLib"

	removeflags { "FatalWarnings" }

	includedirs {
		path.join(MODULE_DIR, "3rdparty/l-smash"),
	}

	files {
		path.join(MODULE_DIR, "3rdparty/l-smash/**.c"),
		path.join(MODULE_DIR, "3rdparty/l-smash/**.h"),
	}

	configuration { "vs*" }
		buildoptions {
			"/wd4005", -- warning C4005: '_CRT_SECURE_NO_WARNINGS': macro redefinition
			"/wd4018", -- warning C4018: '<=': signed/unsigned mismatch
			"/wd4100", -- warning C4100: 'class': unreferenced parameter
			"/wd4116", -- warning C4116: unnamed type definition in parentheses
			"/wd4125", -- warning C4125: decimal digit terminates octal escape sequence
			"/wd4133", -- warning C4133: '=': incompatible types - from 'lsmash_brand_type *' to 'uint32_t *'
			"/wd4210", -- warning C4210: nonstandard extension used: function given file scope
			"/wd4244", -- warning C4244: 'initializing': conversion from 'uint64_t' to 'uint32_t', possible loss of data
			"/wd4245", -- warning C4245: '=': conversion from 'int' to 'uint32_t', signed/unsigned mismatch
			"/wd4267", -- warning C4267: 'initializing': conversion from 'size_t' to 'int', possible loss of data
			"/wd4389", -- warning C4389: '!=': signed/unsigned mismatch
			"/wd4701", -- warning C4701: potentially uninitialized local variable 'src_movie_timescale' used
		}

	configuration { "*-gcc or *-clang" }
		buildoptions {
			"-Wno-empty-body",
			"-Wno-implicit-fallthrough",
			"-Wno-missing-field-initializers",
			"-Wno-pragmas",
			"-Wno-sign-compare",
			"-Wno-type-limits",
			"-Wno-undef",
			"-Wno-unused-function",
			"-Wno-unused-parameter",
		}

	configuration { "mingw*" }
		buildoptions {
			"-Wno-maybe-uninitialized",
			"-Wno-stringop-overflow",
		}

project "texturev"
	uuid (os.uuid("texturev") )
	kind "ConsoleApp"

	configuration {}

	includedirs {
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
		path.join(MODULE_DIR, "include"),
		path.join(MODULE_DIR, "3rdparty"),
	}

	files {
		path.join(MODULE_DIR, "tools/texturev/**"),
	}

	links {
		"l-smash",
		"example-common",
		"bimg_decode",
		"bimg",
		"bgfx",
	}

	using_bx()

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

		configuration { "x32", "windows" }
			libdirs { "$(SDL2_DIR)/lib/x86" }

		configuration { "x64", "windows" }
			libdirs { "$(SDL2_DIR)/lib/x64" }

		configuration {}
	end

	if _OPTIONS["with-glfw"] then
		defines { "ENTRY_CONFIG_USE_GLFW=1" }
		links   { "glfw3" }

		configuration { "osx*" }
			linkoptions {
				"-framework CoreVideo",
			}

		configuration {}
	end

	if _OPTIONS["with-libheif"] then
		links {
			"heif",
		}

		configuration {}
	end

	configuration { "vs*" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

	configuration { "vs201*" }
		linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
			"/DELAYLOAD:\"libEGL.dll\"",
			"/DELAYLOAD:\"libGLESv2.dll\"",
		}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "vs20* or mingw*" }
		links {
			"comdlg32",
			"gdi32",
			"psapi",
		}

	configuration { "winstore*" }
		removelinks {
			"DelayImp",
			"gdi32",
			"psapi"
		}
		links {
			"d3d11",
			"d3d12",
			"dxgi"
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}
		-- WinRT targets need their own output directories are build files stomp over each other
		targetdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "obj", _name))

	configuration { "mingw-clang" }
		kind "ConsoleApp"

	configuration { "android*" }
		kind "ConsoleApp"
		targetextension ".so"
		linkoptions {
			"-shared",
		}
		links {
			"EGL",
			"GLESv2",
		}

	configuration { "wasm*" }
		kind "ConsoleApp"

	configuration { "linux-* or freebsd" }
		links {
			"X11",
			"GL",
			"pthread",
		}

	configuration { "rpi" }
		links {
			"X11",
			"GLESv2",
			"EGL",
			"bcm_host",
			"vcos",
			"vchiq_arm",
			"pthread",
		}

	configuration { "osx*" }
		linkoptions {
			"-framework Cocoa",
			"-framework IOKit",
			"-framework Metal",
			"-framework OpenGL",
			"-framework QuartzCore",
			"-weak_framework VideoToolbox",
			"-weak_framework CoreMedia",
			"-weak_framework CoreVideo",
		}

	configuration { "ios*" }
		kind "ConsoleApp"
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
			"-framework IOKit",
			"-framework OpenGLES",
			"-framework QuartzCore",
			"-framework UIKit",
		}

	configuration { "xcode*", "ios" }
		kind "WindowedApp"

	configuration { "qnx*" }
		targetextension ""
		links {
			"EGL",
			"GLESv2",
		}

	configuration {}

	strip()

group "tools"
