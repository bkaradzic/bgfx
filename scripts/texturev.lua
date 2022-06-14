project ("texturev")
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
		"example-common",
		"bimg_decode",
		"bimg",
		"bgfx",
	}

	using_bx()

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

		configuration { "linux or freebsd" }
			if _OPTIONS["with-wayland"]  then
				links {
					"wayland-egl",
				}
			end

		configuration { "x32", "windows" }
			libdirs { "$(SDL2_DIR)/lib/x86" }

		configuration { "x64", "windows" }
			libdirs { "$(SDL2_DIR)/lib/x64" }

		configuration {}
	end

	if _OPTIONS["with-glfw"] then
		defines { "ENTRY_CONFIG_USE_GLFW=1" }
		links   { "glfw3" }

		configuration { "linux or freebsd" }
			links {
				"Xrandr",
				"Xinerama",
				"Xi",
				"Xxf86vm",
				"Xcursor",
			}

		configuration { "osx*" }
			linkoptions {
				"-framework CoreVideo",
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
