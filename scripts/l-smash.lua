project "l-smash"
	kind "StaticLib"

	removeflags { "FatalWarnings" }

	includedirs {
		path.join(MODULE_DIR, "3rdparty/l-smash"),
	}

	files {
		path.join(MODULE_DIR, "3rdparty/l-smash/**.c"),
		path.join(MODULE_DIR, "3rdparty/l-smash/**.h"),
	}

	configuration { "vs*" }
		buildoptions {
			"/wd4005",
			"/wd4018",
			"/wd4100",
			"/wd4116",
			"/wd4125",
			"/wd4133",
			"/wd4210",
			"/wd4244",
			"/wd4245",
			"/wd4267",
			"/wd4389",
			"/wd4701",
		}

	configuration { "*-gcc or *-clang" }
		buildoptions {
			"-Wno-empty-body",
			"-Wno-implicit-fallthrough",
			"-Wno-missing-field-initializers",
			"-Wno-pragmas",
			"-Wno-sign-compare",
			"-Wno-type-limits",
			"-Wno-undef",
			"-Wno-unused-function",
			"-Wno-unused-parameter",
		}

	configuration { "mingw*" }
		buildoptions {
			"-Wno-maybe-uninitialized",
			"-Wno-stringop-overflow",
		}

	configuration {}