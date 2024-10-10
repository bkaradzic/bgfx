--
-- Copyright 2010-2024 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
--

project "texturec"
	uuid (os.uuid("texturec"))
	kind "ConsoleApp"

	includedirs {
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BIMG_DIR, "3rdparty/iqa/include"),
	}

	files {
		path.join(BIMG_DIR, "tools/texturec/texturec.cpp"),
	}

	links {
		"bimg_decode",
		"bimg_encode",
		"bimg",
	}

	if _OPTIONS["with-libheif"] then
		links {
			"heif",
		}

		configuration {}
	end

	using_bx()

	configuration { "mingw-*" }
		targetextension ".exe"
		links {
			"psapi",
		}

	configuration { "osx*" }
		links {
			"Cocoa.framework",
		}

	configuration { "vs20*" }
		links {
			"psapi",
		}

	configuration {}
