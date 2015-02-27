--
-- Copyright 2010-2015 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
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
