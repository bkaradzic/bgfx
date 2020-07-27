--
-- Copyright 2010-2020 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

project "geometryc"
	uuid (os.uuid("geometryc"))
	kind "ConsoleApp"

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
	}

	files {
		path.join(BGFX_DIR, "3rdparty/meshoptimizer/src/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/meshoptimizer/src/**.h"),
		path.join(BGFX_DIR, "src/vertexlayout.**"),
		path.join(BGFX_DIR, "tools/geometryc/**.cpp"),
		path.join(BGFX_DIR, "tools/geometryc/**.h"),
		path.join(BGFX_DIR, "examples/common/bounds.**"),
	}

	links {
		"bx",
	}

	configuration { "mingw-*" }
		targetextension ".exe"
		links {
			"psapi",
		}

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration { "vs20*" }
		links {
			"psapi",
		}

	configuration {}

	strip()
