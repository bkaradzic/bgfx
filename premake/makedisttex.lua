project "makedisttex"
	uuid "b0561b30-91bb-11e1-b06e-023ad46e7d26"
	kind "ConsoleApp"

	includedirs {
		BX_DIR .. "include",
		BGFX_DIR .. "3rdparty/edtaa3",
		BGFX_DIR .. "3rdparty/stb_image",
	}

	files {
		BGFX_DIR .. "3rdparty/edtaa3/**.cpp",
		BGFX_DIR .. "3rdparty/edtaa3/**.h",
		BGFX_DIR .. "tools/makedisttex.cpp",
	}
