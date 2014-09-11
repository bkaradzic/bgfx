--
-- Copyright 2010-2014 Branimir Karadzic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

solution "bgfx"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		"x32",
		"x64",
--		"Xbox360",
		"Native", -- for targets where bitness is not specified
	}

	language "C++"

BGFX_DIR = (path.getabsolute("..") .. "/")
local BGFX_BUILD_DIR = (BGFX_DIR .. ".build/")
local BGFX_THIRD_PARTY_DIR = (BGFX_DIR .. "3rdparty/")
BX_DIR = (BGFX_DIR .. "../bx/")

defines {
	"BX_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS=1"
}

dofile (BX_DIR .. "scripts/toolchain.lua")
toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR)

function copyLib()
end

function exampleProject(_name)

	project ("example-" .. _name)
		uuid (os.uuid("example-" .. _name))
		kind "WindowedApp"

	configuration {}

	debugdir (BGFX_DIR .. "examples/runtime/")

	includedirs {
		BX_DIR .. "include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "3rdparty",
		BGFX_DIR .. "examples/common",
	}

	files {
		BGFX_DIR .. "examples/" .. _name .. "/**.cpp",
		BGFX_DIR .. "examples/" .. _name .. "/**.h",
	}

	links {
		"bgfx",
		"example-common",
	}

	configuration { "vs*" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

	configuration { "vs201*" }
		linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
			"/DELAYLOAD:\"libEGL.dll\"",
			"/DELAYLOAD:\"libGLESv2.dll\"",
		}

	configuration { "android*" }
		kind "ConsoleApp"
		targetextension ".so"
		linkoptions {
			"-shared",
		}
		links {
			"EGL",
			"GLESv2",
		}

	configuration { "nacl or nacl-arm" }
		kind "ConsoleApp"
		targetextension ".nexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "pnacl" }
		kind "ConsoleApp"
		targetextension ".pexe"
		links {
			"ppapi",
			"ppapi_gles2",
			"pthread",
		}

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"

	configuration { "linux-*" }
		links {
			"X11",
			"GL",
			"pthread",
		}

	configuration { "rpi" }
		links {
			"X11",
			"GLESv2",
			"EGL",
			"bcm_host",
			"vcos",
			"vchiq_arm",
			"pthread",
		}

	configuration { "osx" }
		files {
			BGFX_DIR .. "examples/common/**.mm",
		}
		links {
			"Cocoa.framework",
			"OpenGL.framework",
--			"SDL2",
		}

	configuration { "xcode4" }
		platforms {
			"Universal"
		}
		files {
			BGFX_DIR .. "examples/common/**.mm",
		}
		links {
			"Cocoa.framework",
			"Foundation.framework",
			"OpenGL.framework",
		}

	configuration { "ios*" }
		kind "ConsoleApp"
		files {
			BGFX_DIR .. "examples/common/**.mm",
		}
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
		}

	configuration { "qnx*" }
		targetextension ""
		links {
			"EGL",
			"GLESv2",
		}

	configuration {}

	strip()
end

dofile "bgfx.lua"
dofile "example-common.lua"
bgfxProject("", "StaticLib", {})

exampleProject("00-helloworld")
exampleProject("01-cubes")
exampleProject("02-metaballs")
exampleProject("03-raymarch")
exampleProject("04-mesh")
exampleProject("05-instancing")
exampleProject("06-bump")
exampleProject("07-callback")
exampleProject("08-update")
exampleProject("09-hdr")
exampleProject("10-font")
exampleProject("11-fontsdf")
exampleProject("12-lod")
exampleProject("13-stencil")
exampleProject("14-shadowvolumes")
exampleProject("15-shadowmaps-simple")
exampleProject("16-shadowmaps")
exampleProject("17-drawstress")
exampleProject("18-ibl")
exampleProject("19-oit")
exampleProject("20-nanovg")
exampleProject("21-deferred")

if _OPTIONS["with-shared-lib"] then
	bgfxProject("-shared-lib", "SharedLib", {})
end

if _OPTIONS["with-tools"] then
	dofile "makedisttex.lua"
	dofile "shaderc.lua"
	dofile "texturec.lua"
	dofile "geometryc.lua"
end
