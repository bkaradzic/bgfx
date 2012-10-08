local OPENCTM_DIR = (BGFX_DIR .. "3rdparty/openctm/")

project "openctm"
	uuid "e03096c4-0c53-11e2-ab09-debcdd6a022f"
	kind "StaticLib"

	defines {
		"OPENCTM_STATIC",
		"OPENCTM_NO_CPP",
	}

	includedirs {
		OPENCTM_DIR .. "lib",
		OPENCTM_DIR .. "lib/liblzma",
	}

	files {
		OPENCTM_DIR .. "lib/**.c",
		OPENCTM_DIR .. "lib/**.h",
	}

project "ctmconv"
	uuid "f50ee8be-0d1d-11e2-b721-905709e48fda"
	kind "ConsoleApp"

	defines {
		"OPENCTM_STATIC",
	}

	includedirs {
		OPENCTM_DIR .. "lib",
		OPENCTM_DIR .. "lib/liblzma",
		OPENCTM_DIR .. "tools/rply",
		OPENCTM_DIR .. "tools/tinyxml",
	}

	links {
		"openctm",
	}

	files {
		OPENCTM_DIR .. "tools/ctmconv.cpp",
		OPENCTM_DIR .. "tools/common.cpp",
		OPENCTM_DIR .. "tools/common.h",
		OPENCTM_DIR .. "tools/systimer.cpp",
		OPENCTM_DIR .. "tools/systimer.h",
		OPENCTM_DIR .. "tools/convoptions.cpp",
		OPENCTM_DIR .. "tools/convoptions.h",
		OPENCTM_DIR .. "tools/mesh.cpp",
		OPENCTM_DIR .. "tools/mesh.h",
		OPENCTM_DIR .. "tools/meshio.cpp",
		OPENCTM_DIR .. "tools/meshio.h",
		OPENCTM_DIR .. "tools/3ds.cpp",
		OPENCTM_DIR .. "tools/3ds.h",
		OPENCTM_DIR .. "tools/ctm.cpp",
		OPENCTM_DIR .. "tools/ctm.h",
		OPENCTM_DIR .. "tools/dae.cpp",
		OPENCTM_DIR .. "tools/dae.h",
		OPENCTM_DIR .. "tools/lwo.cpp",
		OPENCTM_DIR .. "tools/lwo.h",
		OPENCTM_DIR .. "tools/obj.cpp",
		OPENCTM_DIR .. "tools/obj.h",
		OPENCTM_DIR .. "tools/off.cpp",
		OPENCTM_DIR .. "tools/off.h",
		OPENCTM_DIR .. "tools/wrl.cpp",
		OPENCTM_DIR .. "tools/wrl.h",
		OPENCTM_DIR .. "tools/ply.cpp",
		OPENCTM_DIR .. "tools/ply.h",
		OPENCTM_DIR .. "tools/stl.cpp",
		OPENCTM_DIR .. "tools/stl.h",
		OPENCTM_DIR .. "tools/rply/rply.c",
		OPENCTM_DIR .. "tools/rply/rply.h",
		OPENCTM_DIR .. "tools/tinyxml/**.cpp",
		OPENCTM_DIR .. "tools/tinyxml/**.h",
	}
