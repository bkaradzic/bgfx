project "geometryc"
	uuid "8794dc3a-2d57-11e2-ba18-368d09e48fda"
	kind "ConsoleApp"

	includedirs {
		BX_DIR .. "include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "3rdparty/forsyth-too",
	}

	files {
		BGFX_DIR .. "3rdparty/forsyth-too/**.cpp",
		BGFX_DIR .. "3rdparty/forsyth-too/**.h",
		BGFX_DIR .. "src/vertexdecl.**",
		BGFX_DIR .. "tools/geometryc/**.cpp",
		BGFX_DIR .. "tools/geometryc/**.h",
	}

	strip()
