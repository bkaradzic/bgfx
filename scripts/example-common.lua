--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project ("example-common")
	uuid ("21cc0e26-bf62-11e2-a01e-0291bd4c8125")
	kind "StaticLib"

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
	}

	files {
		path.join(BGFX_DIR, "3rdparty/ib-compress/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/ib-compress/**.h"),
		path.join(BGFX_DIR, "3rdparty/ocornut-imgui/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/ocornut-imgui/**.h"),
		path.join(BGFX_DIR, "examples/common/**.cpp"),
		path.join(BGFX_DIR, "examples/common/**.h"),
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

	configuration { "vs2008" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}
	if (_OPTIONS["vs"] == "vs2012-xp") or (_OPTIONS["vs"] == "vs2013-xp") then
	configuration { "vs201*" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}
	end

	configuration { "winphone8* or winstore8*"}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}
		premake.vstudio.splashpath = "../../../examples/runtime/images/SplashScreen.png"
