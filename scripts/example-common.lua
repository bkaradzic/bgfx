--
-- Copyright 2010-2014 Branimir Karadzic. All rights reserved.
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

	configuration { "xcode4" }
		includedirs {
			BX_DIR .. "include/compat/osx",
		}
