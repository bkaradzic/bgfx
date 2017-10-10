--
-- Copyright 2010-2017 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

project "geometryc"
	uuid "8794dc3a-2d57-11e2-ba18-368d09e48fda"
	kind "ConsoleApp"

	if _OPTIONS["with-assimp"] then

		defines { 
			"GEOMETRYC_USE_ASSIMP=1",
			"ASSIMP_BUILD_NO_C4D_IMPORTER=1",
			"ASSIMP_BUILD_NO_OPENGEX_IMPORTER=1",
		}

		configuration { "vs*" }
			buildoptions {
				"/wd4530", -- warning C4530: C++ exception handler used, but unwind semantics are not enabled
				"/wd4458", -- warning C4458: declaration hides class member
				"/wd4127", -- warning C4127: conditional expression is constant
				"/wd4456", -- warning C4456: declaration hides previous local declaration
				"/wd4244", -- warning C4244: '=': conversion possible loss of data
				"/wd4100", -- warning C4100: unreferenced formal parameter
				"/wd4245", -- warning C4245: 'argument': conversion signed/unsigned mismatch
				"/wd4706", -- warning C4706: assignment within conditional expression
				"/wd4701", -- warning C4701: potentially uninitialized local variable used
				"/wd4702", -- warning C4702: unreachable code
				"/wd4457", -- warning C4457: declaration hides function parameter
				"/wd4459", -- warning C4459: declaration hides global declaration
				"/wd4389", -- warning C4389: '==': signed/unsigned mismatch
				"/wd4065", -- warning C4065: switch statement contains 'default' but no 'case' labels
				"/wd4131", -- warning C4131: 'function': uses old-style declarator
				"/wd4996", -- warning C4996: The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _open. See online help for details.
				"/wd4057", -- warning C4057: '=': 'const unsigned long *' differs in indirection to slightly different base types from 'const z_crc_t *'
				"/wd4189", -- warning C4189: local variable is initialized but not referenced
				"/wd4505", -- warning C4505: unreferenced local function has been removed
			}

		includedirs {
			path.join(BGFX_DIR, "3rdparty/assimp/include"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/irrXML"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/rapidjson/include"),
			path.join(BGFX_DIR, "3rdparty/assimp/"),
		}

		files {
			path.join(BGFX_DIR, "3rdparty/assimp/code/**.cpp"),
			path.join(BGFX_DIR, "3rdparty/assimp/code/**.h"),

			path.join(BGFX_DIR, "3rdparty/assimp/contrib/irrXML/**.cpp"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/irrXML/**.h"),

			path.join(BGFX_DIR, "3rdparty/assimp/contrib/zlib/**.c"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/zlib/**.h"),

			path.join(BGFX_DIR, "3rdparty/assimp/contrib/unzip/**.c"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/unzip/**.h"),

			path.join(BGFX_DIR, "3rdparty/assimp/contrib/poly2tri/poly2tri/**.cc"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/poly2tri/poly2tri/**.h"),

			path.join(BGFX_DIR, "3rdparty/assimp/contrib/clipper/**.cpp"),
			path.join(BGFX_DIR, "3rdparty/assimp/contrib/clipper/**.h"),

		}

		removeflags {
			"NoRTTI",
		}

	end

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

	links {
		"bx",
	}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "osx" }
		links {
			"Cocoa.framework",
		}

	configuration {}

	strip()
