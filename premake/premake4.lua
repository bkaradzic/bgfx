--
-- Copyright 2010-2012 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

solution "bgfx"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64",
		"Xbox360",
	}

	language "C++"

BGFX_DIR = (path.getabsolute("..") .. "/")
local BGFX_BUILD_DIR = (BGFX_DIR .. ".build/")
local BGFX_THIRD_PARTY_DIR = (BGFX_DIR .. "3rdparty/")
BX_DIR = (BGFX_DIR .. "../bx/")

defines {
	"BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS=1"
}

dofile (BX_DIR .. "premake/toolchain.lua")
toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR)

function copyLib()
end

function exampleProject(_name, _uuid)

	project ("example-" .. _name)
		uuid (_uuid)
		kind "WindowedApp"

	configuration {}

	debugdir (BGFX_DIR .. "examples/runtime/")

	includedirs {
		BX_DIR .. "include",
		BGFX_DIR .. "include",
	}

	files {
		BGFX_DIR .. "examples/common/**.cpp",
		BGFX_DIR .. "examples/common/**.h",
		BGFX_DIR .. "examples/" .. _name .. "/**.cpp",
		BGFX_DIR .. "examples/" .. _name .. "/**.h",
	}

	links {
		"bgfx",
	}

	configuration { "emscripten" }
		targetextension ".bc"

	configuration { "nacl or nacl-arm or pnacl" }
		targetextension ".nexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

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

	configuration { "macosx" }
		files {
			BGFX_DIR .. "examples/common/**.mm",
		}
		links {
			"Cocoa.framework",
			"OpenGL.framework",
		}
end

dofile "bgfx.lua"
exampleProject("00-helloworld", "ff2c8450-ebf4-11e0-9572-0800200c9a66")
exampleProject("01-cubes",      "fec3bc94-e1e5-11e1-9c59-c7eeec2c1c51")
exampleProject("02-metaballs",  "413b2cb4-f7db-11e1-bf5f-a716de6a022f")
exampleProject("03-raymarch",   "1cede802-0220-11e2-91ba-e108de6a022f")
exampleProject("04-mesh",       "546bbc76-0c4a-11e2-ab09-debcdd6a022f")
exampleProject("05-instancing", "5d3da660-1105-11e2-aece-71e4dd6a022f")
exampleProject("06-bump",       "ffb23e6c-167b-11e2-81df-94c4dd6a022f")
exampleProject("07-callback",   "acc53bbc-52f0-11e2-9781-ad8edd4b7d02")
exampleProject("08-update",     "e011e246-5862-11e2-b202-b7cb257a7926")
dofile "makedisttex.lua"
dofile "shaderc.lua"
dofile "texturec.lua"
dofile "geometryc.lua"
