--
-- Copyright 2010-2014 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

project "bgfx"
	uuid "2dc7fd80-ed76-11e0-be50-0800200c9a66"
	kind "StaticLib"

	includedirs {
		BGFX_DIR .. "../bx/include",
	}

	defines {
--		"BGFX_CONFIG_RENDERER_OPENGL=1",
	}

	configuration { "Debug" }
		defines {
			"BGFX_CONFIG_DEBUG=1",
		}

	configuration { "windows" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}

	configuration { "osx or ios*" }
		files {
			BGFX_DIR .. "src/**.mm",
		}

	configuration { "vs* or linux or mingw or osx or ios*" }
		includedirs {
			--nacl has GLES2 headers modified...
			BGFX_DIR .. "3rdparty/khronos",
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

project "bgfx-shared-lib"
	uuid "09986168-e9d9-11e3-9c8e-f2aef940a72a"
	kind "SharedLib"

	includedirs {
		BGFX_DIR .. "../bx/include",
	}

	defines {
		"BGFX_SHARED_LIB_BUILD=1",
--		"BGFX_CONFIG_RENDERER_OPENGL=1",
	}

	configuration { "Debug" }
		defines {
			"BGFX_CONFIG_DEBUG=1",
		}

	configuration { "windows" }
		includedirs {
			"$(DXSDK_DIR)/include",
		}

	configuration { "osx or ios*" }
		files {
			BGFX_DIR .. "src/**.mm",
		}

	configuration { "vs* or linux or mingw or osx or ios*" }
		includedirs {
			--nacl has GLES2 headers modified...
			BGFX_DIR .. "3rdparty/khronos",
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
