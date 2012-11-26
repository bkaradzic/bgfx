project "texturec"
	uuid "838801ee-7bc3-11e1-9f19-eae7d36e7d26"
	kind "ConsoleApp"

	includedirs {
		BGFX_DIR .. "../bx/include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "src",
	}

	files {
		BGFX_DIR .. "src/dds.*",
		BGFX_DIR .. "tools/texturec/**.cpp",
		BGFX_DIR .. "tools/texturec/**.h",
	}

	links {
--		"bgfx",
	}
