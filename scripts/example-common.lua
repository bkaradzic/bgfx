--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project ("example-common")
	uuid ("21cc0e26-bf62-11e2-a01e-0291bd4c8125")
	kind "StaticLib"

	includedirs {
		BX_DIR .. "include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "3rdparty",
	}

	files {
		BGFX_DIR .. "3rdparty/ib-compress/**.cpp",
		BGFX_DIR .. "3rdparty/ib-compress/**.h",
		BGFX_DIR .. "examples/common/**.cpp",
		BGFX_DIR .. "examples/common/**.h",
	}

	if _OPTIONS["with-sdl"] then
		defines {
			"ENTRY_CONFIG_USE_SDL=1",
		}
		includedirs {
			"$(SDL2_DIR)/include",
		}
	end

	configuration { "mingw* or vs2008" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}


	configuration { "winphone8*"}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

-- Uncomment to enable Unicode build

--	configuration { "vs*" }
--		flags {
--			"Unicode",
--		}
--		defines {
--			"UNICODE",
--			"_UNICODE",
--		}
