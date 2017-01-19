--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

project "texturec"
	uuid "838801ee-7bc3-11e1-9f19-eae7d36e7d26"
	kind "ConsoleApp"

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "src"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "3rdparty/nvtt"),
		path.join(BGFX_DIR, "3rdparty/iqa/include"),
	}

	files {
		path.join(BGFX_DIR, "src/image.*"),
		path.join(BGFX_DIR, "3rdparty/libsquish/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/libsquish/**.h"),
		path.join(BGFX_DIR, "3rdparty/edtaa3/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/edtaa3/**.h"),
		path.join(BGFX_DIR, "3rdparty/etc1/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/etc1/**.h"),
		path.join(BGFX_DIR, "3rdparty/etc2/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/etc2/**.hpp"),
		path.join(BGFX_DIR, "3rdparty/nvtt/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/nvtt/**.h"),
		path.join(BGFX_DIR, "3rdparty/pvrtc/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/pvrtc/**.h"),
		path.join(BGFX_DIR, "3rdparty/tinyexr/**.h"),
		path.join(BGFX_DIR, "3rdparty/iqa/include/**.h"),
		path.join(BGFX_DIR, "3rdparty/iqa/source/**.c"),
		path.join(BGFX_DIR, "tools/texturec/**.cpp"),
		path.join(BGFX_DIR, "tools/texturec/**.h"),
	}

	links {
		"bx",
	}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration { "vs20* or mingw*" }
		links {
			"psapi",
		}

	configuration {}
