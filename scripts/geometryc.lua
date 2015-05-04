--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project "geometryc"
	uuid "8794dc3a-2d57-11e2-ba18-368d09e48fda"
	kind "ConsoleApp"

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
	}

	files {
		path.join(BGFX_DIR, "3rdparty/forsyth-too/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/forsyth-too/**.h"),
		path.join(BGFX_DIR, "3rdparty/ib-compress/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/ib-compress/**.h"),
		path.join(BGFX_DIR, "src/vertexdecl.**"),
		path.join(BGFX_DIR, "tools/geometryc/**.cpp"),
		path.join(BGFX_DIR, "tools/geometryc/**.h"),
		path.join(BGFX_DIR, "examples/common/bounds.**"),
	}

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	strip()
