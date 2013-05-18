--
-- Copyright 2010-2013 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project "bgfx"
	uuid "2dc7fd80-ed76-11e0-be50-0800200c9a66"
	kind "StaticLib"

	includedirs {
		BGFX_DIR .. "../tinystl/include",
		BGFX_DIR .. "../bx/include",
	}

	buildoptions {
--		"-Wall",
	}

	defines {
--		"BGFX_CONFIG_RENDERER_OPENGL=1",
	}

	configuration "Debug"
		defines {
			"BGFX_CONFIG_DEBUG=1",
		}

	configuration { "windows" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}

	configuration { "osx" }
		files {
			BGFX_DIR .. "src/**.mm",
		}

	configuration { "vs* or linux or mingw or osx" }
		includedirs {
			--nacl has GLES2 headers modified...
			BGFX_DIR .. "3rdparty/glext",
		}

	configuration {}

	includedirs {
		BGFX_DIR .. "include",
	}

	files {
		BGFX_DIR .. "include/**.h",
		BGFX_DIR .. "src/**.cpp",
		BGFX_DIR .. "src/**.h",
	}

	excludes {
		BGFX_DIR .. "src/**.bin.h",
	}

	copyLib()
