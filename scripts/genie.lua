--
-- Copyright 2010-2021 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

MODULE_DIR = path.getabsolute("../")

newoption {
	trigger = "with-amalgamated",
	description = "Enable amalgamated build.",
}

newoption {
	trigger = "with-sdl",
	description = "Enable SDL entry.",
}

newoption {
	trigger = "with-glfw",
	description = "Enable GLFW entry.",
}

newoption {
	trigger = "with-wayland",
	description = "Use Wayland backend.",
}

newoption {
	trigger = "with-profiler",
	description = "Enable build with intrusive profiler.",
}

newoption {
	trigger = "with-shared-lib",
	description = "Enable building shared library.",
}

newoption {
	trigger = "with-tools",
	description = "Enable building tools.",
}

newoption {
	trigger = "with-combined-examples",
	description = "Enable building examples (combined as single executable).",
}

newoption {
	trigger = "with-examples",
	description = "Enable building examples.",
}

newoption {
	trigger = "with-webgpu",
	description = "Enable webgpu experimental renderer.",
}

newaction {
	trigger = "idl",
	description = "Generate bgfx interface source code",
	execute = function ()

		local gen = require "bgfx-codegen"

		local function generate(tempfile, outputfile, indent)
			local codes = gen.apply(tempfile)
			codes = gen.format(codes, {indent = indent})
			gen.write(codes, outputfile)
			print("Generating: " .. outputfile)
		end

		generate("temp.bgfx.h" ,      "../include/bgfx/c99/bgfx.h", "    ")
		generate("temp.bgfx.idl.inl", "../src/bgfx.idl.inl",        "\t")
		generate("temp.defines.h",    "../include/bgfx/defines.h",  "\t")

		do
			local csgen = require "bindings-cs"
			csgen.write(csgen.gen(), "../bindings/cs/bgfx.cs")
			csgen.write(csgen.gen_dllname(), "../bindings/cs/bgfx_dllname.cs")

			local dgen = require "bindings-d"
			dgen.write(dgen.gen_types(), "../bindings/d/types.d")
			dgen.write(dgen.gen_funcs(), "../bindings/d/funcs.d")

			local csgen = require "bindings-bf"
			csgen.write(csgen.gen(), "../bindings/bf/bgfx.bf")
		end

		os.exit()
	end
}

newaction {
	trigger = "version",
	description = "Generate bgfx version.h",
	execute = function ()

		local f = io.popen("git rev-list --count HEAD")
		local rev = string.match(f:read("*a"), ".*%S")
		f:close()
		f = io.popen("git log --format=format:%H -1")
		local sha1 = f:read("*a")
		f:close()
		io.output(path.join(MODULE_DIR, "src/version.h"))
		io.write("/*\n")
		io.write(" * Copyright 2011-2021 Branimir Karadzic. All rights reserved.\n")
		io.write(" * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n")
		io.write(" */\n")
		io.write("\n")
		io.write("/*\n")
		io.write(" *\n")
		io.write(" * AUTO GENERATED! DO NOT EDIT!\n")
		io.write(" *\n")
		io.write(" */\n")
		io.write("\n")
		io.write("#define BGFX_REV_NUMBER " .. rev .. "\n")
		io.write("#define BGFX_REV_SHA1   \"" .. sha1 .. "\"\n")
		io.close()

		os.exit()
	end
}

solution "bgfx"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION ~= nil and _ACTION:match "^xcode" then
		platforms {
			"Native", -- let xcode decide based on the target output
		}
	else
		platforms {
			"x32",
			"x64",
--			"Xbox360",
			"Native", -- for targets where bitness is not specified
		}
	end

	language "C++"
	startproject "example-00-helloworld"

BGFX_DIR   = path.getabsolute("..")
BX_DIR     = os.getenv("BX_DIR")
BIMG_DIR   = os.getenv("BIMG_DIR")

local BGFX_BUILD_DIR = path.join(BGFX_DIR, ".build")
local BGFX_THIRD_PARTY_DIR = path.join(BGFX_DIR, "3rdparty")
if not BX_DIR then
	BX_DIR = path.getabsolute(path.join(BGFX_DIR, "../bx"))
end

if not BIMG_DIR then
	BIMG_DIR = path.getabsolute(path.join(BGFX_DIR, "../bimg"))
end

if not os.isdir(BX_DIR) or not os.isdir(BIMG_DIR) then

	if not os.isdir(BX_DIR) then
		print("bx not found at \"" .. BX_DIR .. "\". git clone https://github.com/bkaradzic/bx?")
	end

	if not os.isdir(BIMG_DIR) then
		print("bimg not found at \"" .. BIMG_DIR .. "\". git clone https://github.com/bkaradzic/bimg?")
	end

	print("For more info see: https://bkaradzic.github.io/bgfx/build.html")
	os.exit()
end

if _OPTIONS["with-webgpu"] then
	DAWN_DIR = os.getenv("DAWN_DIR")

	if not DAWN_DIR then
		DAWN_DIR = path.getabsolute(path.join(BGFX_DIR, "../dawn"))
	end

	if not os.isdir(DAWN_DIR) and "wasm*" ~= _OPTIONS["gcc"] then
		print("Dawn not found at \"" .. DAWN_DIR .. "\". git clone https://dawn.googlesource.com/dawn?")

		print("For more info see: https://bkaradzic.github.io/bgfx/build.html")
		os.exit()
	end

	_OPTIONS["with-windows"] = "10.0"
end

dofile (path.join(BX_DIR, "scripts/toolchain.lua"))
if not toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR) then
	return -- no action specified
end

function copyLib()
end

if _OPTIONS["with-wayland"] then
	defines { "WL_EGL_PLATFORM=1" }
end

if _OPTIONS["with-sdl"] then
	if os.is("windows") then
		if not os.getenv("SDL2_DIR") then
			print("Set SDL2_DIR enviroment variable.")
		end
	end
end

if _OPTIONS["with-profiler"] then
	defines {
		"ENTRY_CONFIG_PROFILER=1",
		"BGFX_CONFIG_PROFILER=1",
	}
end

function exampleProjectDefaults()

	debugdir (path.join(BGFX_DIR, "examples/runtime"))

	includedirs {
		path.join(BX_DIR,   "include"),
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),
		path.join(BGFX_DIR, "3rdparty"),
		path.join(BGFX_DIR, "examples/common"),
	}

	flags {
		"FatalWarnings",
	}

	links {
		"example-glue",
		"example-common",
		"bgfx",
		"bimg_decode",
		"bimg",
		"bx",
	}

	if _OPTIONS["with-webgpu"] then
		usesWebGPU()
	end

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

		configuration { "linux or freebsd" }
			if _OPTIONS["with-wayland"]  then
				links {
					"wayland-egl",
				}
			end

		configuration { "osx*" }
			libdirs { "$(SDL2_DIR)/lib" }

		configuration {}
	end

	if _OPTIONS["with-glfw"] then
		defines { "ENTRY_CONFIG_USE_GLFW=1" }
		links   { "glfw3" }

		configuration { "linux or freebsd" }
			if _OPTIONS["with-wayland"] then
				links {
					"wayland-egl",
				}
			else
				links {
					"Xrandr",
					"Xinerama",
					"Xi",
					"Xxf86vm",
					"Xcursor",
				}
			end

		configuration { "osx*" }
			linkoptions {
				"-framework CoreVideo",
				"-framework IOKit",
			}

		configuration {}
	end

	configuration { "vs*", "x32 or x64" }
		linkoptions {
			"/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
		}
		links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
			"DelayImp",
		}

	configuration { "vs201*", "x32 or x64" }
		linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
			"/DELAYLOAD:\"libEGL.dll\"",
			"/DELAYLOAD:\"libGLESv2.dll\"",
		}

	configuration { "mingw*" }
		targetextension ".exe"
		links {
			"gdi32",
			"psapi",
		}

	configuration { "vs20*", "x32 or x64" }
		links {
			"gdi32",
			"psapi",
		}

	configuration { "durango" }
		links {
			"d3d11_x",
			"d3d12_x",
			"combase",
			"kernelx",
		}

	configuration { "winstore*" }
		removelinks {
			"DelayImp",
			"gdi32",
			"psapi"
		}
		links {
			"d3d11",
			"d3d12",
			"dxgi"
		}
		linkoptions {
			"/ignore:4264" -- LNK4264: archiving object file compiled with /ZW into a static library; note that when authoring Windows Runtime types it is not recommended to link with a static library that contains Windows Runtime metadata
		}

	-- WinRT targets need their own output directories or build files stomp over each other
	configuration { "x32", "winstore*" }
		targetdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "win32_" .. _ACTION, "obj", _name))

	configuration { "x64", "winstore*" }
		targetdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "win64_" .. _ACTION, "obj", _name))

	configuration { "ARM", "winstore*" }
		targetdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "bin", _name))
		objdir (path.join(BGFX_BUILD_DIR, "arm_" .. _ACTION, "obj", _name))

	configuration { "mingw-clang" }
		kind "ConsoleApp"

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

	configuration { "wasm*" }
		kind "ConsoleApp"

		linkoptions {
			"-s TOTAL_MEMORY=32MB",
			"-s ALLOW_MEMORY_GROWTH=1",
			"--preload-file ../../../examples/runtime@/"
		}

		removeflags {
			"OptimizeSpeed",
		}

		flags {
			"Optimize"
		}

	configuration { "linux-* or freebsd" }
		links {
			"X11",
			"GL",
			"pthread",
		}

	configuration { "rpi" }
		links {
			"X11",
			"brcmGLESv2",
			"brcmEGL",
			"bcm_host",
			"vcos",
			"vchiq_arm",
			"pthread",
		}

	configuration { "osx*" }
		linkoptions {
			"-framework Cocoa",
			"-framework QuartzCore",
			"-framework OpenGL",
			"-weak_framework Metal",
		}

	configuration { "ios* or tvos*" }
		kind "ConsoleApp"
		linkoptions {
			"-framework CoreFoundation",
			"-framework Foundation",
			"-framework OpenGLES",
			"-framework UIKit",
			"-framework QuartzCore",
			"-weak_framework Metal",
		}

	configuration { "xcode*", "ios" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/iOS-Info.plist"),
		}

	configuration { "xcode*", "tvos" }
		kind "WindowedApp"
		files {
			path.join(BGFX_DIR, "examples/runtime/tvOS-Info.plist"),
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

function exampleProject(_combined, ...)

	if _combined then

		project ("examples")
			uuid (os.uuid("examples"))
			kind "WindowedApp"

		for _, name in ipairs({...}) do

			files {
				path.join(BGFX_DIR, "examples", name, "**.c"),
				path.join(BGFX_DIR, "examples", name, "**.cpp"),
				path.join(BGFX_DIR, "examples", name, "**.h"),
			}

			removefiles {
				path.join(BGFX_DIR, "examples", name, "**.bin.h"),
			}

		end

		files {
			path.join(BGFX_DIR, "examples/25-c99/helloworld.c"), -- hack for _main_
		}

		exampleProjectDefaults()

	else

		for _, name in ipairs({...}) do
			project ("example-" .. name)
				uuid (os.uuid("example-" .. name))
				kind "WindowedApp"

			files {
				path.join(BGFX_DIR, "examples", name, "**.c"),
				path.join(BGFX_DIR, "examples", name, "**.cpp"),
				path.join(BGFX_DIR, "examples", name, "**.h"),
			}

			removefiles {
				path.join(BGFX_DIR, "examples", name, "**.bin.h"),
			}

			defines {
				"ENTRY_CONFIG_IMPLEMENT_MAIN=1",
			}

			exampleProjectDefaults()
		end
	end

end

dofile "bgfx.lua"

group "libs"

local function userdefines()
	local defines = {}
	local BGFX_CONFIG = os.getenv("BGFX_CONFIG")
	if BGFX_CONFIG then
		for def in BGFX_CONFIG:gmatch "[^%s:]+" do
			table.insert(defines, "BGFX_CONFIG_" .. def)
		end
	end

	return defines
end

BGFX_CONFIG = userdefines()

bgfxProject("", "StaticLib", BGFX_CONFIG)

dofile(path.join(BX_DIR,   "scripts/bx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))

if _OPTIONS["with-tools"] then
	dofile(path.join(BIMG_DIR, "scripts/bimg_encode.lua"))
end

if _OPTIONS["with-examples"]
or _OPTIONS["with-combined-examples"]
or _OPTIONS["with-tools"] then
	group "examples"
	dofile "example-common.lua"
end

if _OPTIONS["with-examples"]
or _OPTIONS["with-combined-examples"] then
	group "examples"

	exampleProject(_OPTIONS["with-combined-examples"]
		, "00-helloworld"
		, "01-cubes"
		, "02-metaballs"
		, "03-raymarch"
		, "04-mesh"
		, "05-instancing"
		, "06-bump"
		, "07-callback"
		, "08-update"
		, "09-hdr"
		, "10-font"
		, "11-fontsdf"
		, "12-lod"
		, "13-stencil"
		, "14-shadowvolumes"
		, "15-shadowmaps-simple"
		, "16-shadowmaps"
		, "18-ibl"
		, "19-oit"
		, "20-nanovg"
		, "21-deferred"
		, "22-windows"
		, "23-vectordisplay"
		, "24-nbody"
		, "26-occlusion"
		, "27-terrain"
		, "28-wireframe"
		, "29-debugdraw"
		, "30-picking"
		, "31-rsm"
		, "32-particles"
		, "33-pom"
		, "34-mvs"
		, "35-dynamic"
		, "36-sky"
		, "37-gpudrivenrendering"
		, "38-bloom"
		, "39-assao"
		, "40-svt"
		, "41-tess"
		, "42-bunnylod"
		, "43-denoise"
		, "44-sss"
		, "45-bokeh"
		)

	-- 17-drawstress requires multithreading, does not compile for singlethreaded wasm
--	if platform is not single-threaded then
		exampleProject(false, "17-drawstress")
--	end

	-- C99 source doesn't compile under WinRT settings
	if not premake.vstudio.iswinrt() then
		exampleProject(false, "25-c99")
	end
end

if _OPTIONS["with-shared-lib"] then
	group "libs"
	bgfxProject("-shared-lib", "SharedLib", BGFX_CONFIG)
end

if _OPTIONS["with-tools"] then
	group "tools"
	dofile "shaderc.lua"
	dofile "texturec.lua"
	dofile "texturev.lua"
	dofile "geometryc.lua"
	dofile "geometryv.lua"
end
