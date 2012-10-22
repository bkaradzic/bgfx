project "example-01-cubes"
	uuid "fec3bc94-e1e5-11e1-9c59-c7eeec2c1c51"
	kind "WindowedApp"

	debugdir (BGFX_DIR .. "examples/runtime/")

	includedirs {
		BGFX_DIR .. "../bx/include",
		BGFX_DIR .. "include",
	}

	files {
		BGFX_DIR .. "examples/common/**.cpp",
		BGFX_DIR .. "examples/common/**.h",
		BGFX_DIR .. "examples/01-cubes/**.cpp",
		BGFX_DIR .. "examples/01-cubes/**.h",
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
