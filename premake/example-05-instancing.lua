project "example-05-instancing"
	uuid "5d3da660-1105-11e2-aece-71e4dd6a022f"
	kind "WindowedApp"

	debugdir (BGFX_DIR .. "examples/runtime/")

	includedirs {
		BGFX_DIR .. "../bx/include",
		BGFX_DIR .. "include",
	}

	files {
		BGFX_DIR .. "examples/common/**.cpp",
		BGFX_DIR .. "examples/common/**.h",
		BGFX_DIR .. "examples/05-instancing/**.cpp",
		BGFX_DIR .. "examples/05-instancing/**.h",
	}

	links {
		"bgfx",
	}

	configuration { "emscripten" }
		targetextension ".bc"

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
