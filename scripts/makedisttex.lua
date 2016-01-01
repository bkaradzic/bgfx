--
-- Copyright 2010-2016 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

project "makedisttex"
	uuid "b0561b30-91bb-11e1-b06e-023ad46e7d26"
	kind "ConsoleApp"

	includedirs {
		path.join(BX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
	}

	files {
		path.join(BGFX_DIR, "3rdparty/edtaa3/**.cpp"),
		path.join(BGFX_DIR, "3rdparty/edtaa3/**.h"),
		path.join(BGFX_DIR, "tools/makedisttex.cpp"),
	}
