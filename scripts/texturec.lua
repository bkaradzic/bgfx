--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project "texturec"
	uuid "838801ee-7bc3-11e1-9f19-eae7d36e7d26"
	kind "ConsoleApp"

	includedirs {
		BX_DIR .. "include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "src",
	}

	files {
		BGFX_DIR .. "src/image.*",
		BGFX_DIR .. "tools/texturec/**.cpp",
		BGFX_DIR .. "tools/texturec/**.h",
	}

	links {
--		"bgfx",
	}

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}
