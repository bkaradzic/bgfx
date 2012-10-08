project "example-04-mesh"
	uuid "546bbc76-0c4a-11e2-ab09-debcdd6a022f"
	kind "WindowedApp"

	debugdir (BGFX_DIR .. "examples/runtime/")

	defines {
		"OPENCTM_STATIC",
	}

	includedirs {
		BGFX_DIR .. "../bx/include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "3rdparty/openctm/lib",
	}

	files {
		BGFX_DIR .. "examples/common/**.cpp",
		BGFX_DIR .. "examples/common/**.h",
		BGFX_DIR .. "examples/04-mesh/**.cpp",
		BGFX_DIR .. "examples/04-mesh/**.h",
	}

	links {
		"bgfx",
		"openctm",
	}

	configuration { "nacl" }
		targetextension ".nexe"

	configuration { "nacl", "Release" }
		postbuildcommands {
			"@echo Stripping symbols.",
			"@$(NACL)/bin/x86_64-nacl-strip -s \"$(TARGET)\""
		}

	configuration { "linux" }
		links {
			"GL",
			"pthread",
		}
