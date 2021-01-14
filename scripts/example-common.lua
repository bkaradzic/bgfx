--
-- Copyright 2010-2021 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

project ("example-glue")
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
	}

	files {
		path.join(BGFX_DIR, "examples/common/example-glue.cpp"),
	}

project ("example-common")
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
	}

	files {
		path.join(BGFX_DIR, "3rdparty/meshoptimizer/src/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/meshoptimizer/src/**.h"),
		path.join(BGFX_DIR, "3rdparty/dear-imgui/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/dear-imgui/**.h"),
		path.join(BGFX_DIR, "examples/common/**.cpp"),
		path.join(BGFX_DIR, "examples/common/**.h"),
	}

	if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-gnm"),
		{ path.join(BGFX_DIR, "../bgfx-gnm/examples/common/entry/entry_orbis.cpp") }) then

		files {
			path.join(BGFX_DIR, "../bgfx-gnm/examples/common/entry/entry_orbis.cpp"),
		}
	end

	if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-nvn"),
		{ path.join(BGFX_DIR, "../bgfx-gnm/examples/common/entry/entry_nx.cpp") }) then

		files {
			path.join(BGFX_DIR, "../bgfx-gnm/examples/common/entry/entry_nx.cpp"),
		}
	end

	removefiles {
		path.join(BGFX_DIR, "examples/common/example-glue.cpp"),
	}

	if _OPTIONS["with-sdl"] then
		defines {
			"ENTRY_CONFIG_USE_SDL=1",
		}
		includedirs {
			"$(SDL2_DIR)/include",
		}
	end

	if _OPTIONS["with-glfw"] then
		defines {
			"ENTRY_CONFIG_USE_GLFW=1",
		}
	end

	if _OPTIONS["with-wayland"] then
		defines {
			"ENTRY_CONFIG_USE_WAYLAND=1",
		}
	end

	configuration { "osx* or ios* or tvos*" }
		files {
			path.join(BGFX_DIR, "examples/common/**.mm"),
		}

	configuration { "winstore* or durango"}
		files {
			path.join(BGFX_DIR, "examples/common/**.cx"),
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}
		premake.vstudio.splashpath = "../../../examples/runtime/images/SplashScreen.png"
