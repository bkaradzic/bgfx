project "helloworld"
	uuid "ff2c8450-ebf4-11e0-9572-0800200c9a66"
	kind "WindowedApp"

	includedirs {
		BGFX_DIR .. "../bx/include",
		BGFX_DIR .. "include",
	}

	files {
		BGFX_DIR .. "examples/common/**.cpp",
		BGFX_DIR .. "examples/common/**.h",
		BGFX_DIR .. "examples/helloworld/**.cpp",
		BGFX_DIR .. "examples/helloworld/**.h",
	}

	links {
		"bgfx",
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
