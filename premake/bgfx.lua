project "bgfx"
	uuid "2dc7fd80-ed76-11e0-be50-0800200c9a66"
	kind "StaticLib"

	includedirs {
		BGFX_DIR .. "../tinystl/include",
		BGFX_DIR .. "../bx/include",
		BGFX_DIR .. "3rdparty/glext",
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

	configuration {}

	includedirs {
		BGFX_DIR .. "include",
	}

	files {
		BGFX_DIR .. "include/**.h",
		BGFX_DIR .. "src/**.cpp",
		BGFX_DIR .. "src/**.h",
	}

--	copyLib()
