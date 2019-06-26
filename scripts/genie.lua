--
-- Copyright 2010-2019 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

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

		os.exit()
	end
}

newaction {
	trigger = "c#-idl",
	description = "Generate bgfx C# bindings.",
	execute = function ()

		local idl = require "idl"

		do
			local doxygen = require "doxygen"
			local source = doxygen.load "bgfx.idl"
			local f = assert(load(source, "bgfx.idl" , "t", idl))
			f()

			local codegen = require "codegen"
			codegen.nameconversion(idl.types, idl.funcs)
		end

		print("using System;")
		print("using System.Runtime.InteropServices;")
		print("using System.Security;")
		print("")

		print("internal struct NativeFunctions")
		print("{")

		local function ends_with(str, ending)
			return ending == "" or str:sub(-#ending) == ending
		end

		local function convert_type_0(arg)

			if arg.ctype == "uint64_t" then
				return "ulong"
			elseif arg.ctype == "uint32_t" then
				return "uint"
			elseif arg.ctype == "uint16_t" then
				return "ushort"
			elseif arg.ctype == "uint8_t" then
				return "byte"
			elseif arg.ctype == "const char*" then
				return "[MarshalAs(UnmanagedType.LPStr)] string"
			elseif ends_with(arg.fulltype, "Handle") then
				return arg.fulltype
			elseif ends_with(arg.fulltype, "::Enum") then
				return arg.fulltype:gsub("::Enum", "")
			end

			return arg.ctype
		end

		local function convert_type(arg)
			local ctype = convert_type_0(arg)
			return ctype:gsub("const ", "")
		end

		for _, typ in ipairs(idl.types) do
			if typ.handle then
				print("\tpublic struct " .. typ.name .. "{ public ushort idx; }")
			elseif ends_with(typ.name, "::Enum") then
				print("\tpublic enum " .. typ.typename)
				print("\t{")
				for _, enum in ipairs(typ.enum) do
					print("\t\t" .. enum.name .. ",")
				end
				print("\t}")
				print("")
			elseif typ.bits ~= nil then

				print("\t[Flags]")

				local format = "0x%08x"
				if typ.bits == 64 then
					format = "0x%016x"
					print("\tpublic enum " .. typ.name .. " : long")
				elseif typ.bits == 16 then
					format = "0x%04x"
					print("\tpublic enum " .. typ.name .. " : short")
				else
					print("\tpublic enum " .. typ.name)
				end

				print("\t{")

--				local shift = typ.flag.shift
--				local base = typ.flag.base or 0
--				local cap = 1 << (typ.flag.range or 0)
				if typ.const then
					for _, flag in ipairs(typ.flag) do
						print("\t\t"
							.. flag.name
							.. string.rep(" ", 22 - #(flag.name))
							.. " = "
							.. string.format(format, flag.value)
							.. ","
							)
					end
				else
					for idx, flag in ipairs(typ.flag) do
						local hex = 1<<(idx-1)
						if flag.value then
							hex = 1<<(flag.value-1)
						end

						print("\t\t"
							.. flag.name
							.. string.rep(" ", 22 - #(flag.name))
							.. " = "
							.. string.format(format, hex)
							.. ","
							)
					end
				end
				print("\t}")
				print("")
			end
		end

		print("");

		for idx, func in ipairs(idl.funcs) do

			print("\t[DllImport(DllName, CallingConvention = CallingConvention.Cdecl)]")

			if func.ret.cpptype == "bool" then
				print("\t[return: MarshalAs(UnmanagedType:I1)]")
			end

			local first = ""
			local args  = "("

			for _, arg in ipairs(func.args) do

				local argtype = convert_type(arg)

				args = args .. first .. argtype .. " " .. arg.name
				first = ", "
			end

			print("\tinternal static extern unsafe " .. convert_type(func.ret) .. " bgfx_" .. func.cname .. args .. ");")
			print("")
		end

		print("#if DEBUG")
		print("\tconst string DllName = \"bgfx_debug.dll\";")
		print("#else")
		print("\tconst string DllName = \"bgfx.dll\";")
		print("#endif")
		print("}")

--		printtable("idl types", idl.types)
--		printtable("idl funcs", idl.funcs)

		os.exit()
	end
}

solution "bgfx"
	configurations {
		"Debug",
		"Release",
	}

	if _ACTION:match "xcode*" then
		platforms {
			"Universal",
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

MODULE_DIR = path.getabsolute("../")
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
		print("bx not found at " .. BX_DIR)
	end

	if not os.isdir(BIMG_DIR) then
		print("bimg not found at " .. BIMG_DIR)
	end

	print("For more info see: https://bkaradzic.github.io/bgfx/build.html")
	os.exit()
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
		"example-common",
		"example-glue",
		"bgfx",
		"bimg_decode",
		"bimg",
		"bx",
	}

	if _OPTIONS["with-sdl"] then
		defines { "ENTRY_CONFIG_USE_SDL=1" }
		links   { "SDL2" }

		configuration { "linux or freebsd" }
			if _OPTIONS["with-wayland"]  then
				links {
					"wayland-egl",
				}
			end

		configuration { "osx" }
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

		configuration { "osx" }
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

	configuration { "asmjs" }
		kind "ConsoleApp"
		targetextension ".bc"

	configuration { "linux-* or freebsd", "not linux-steamlink" }
		links {
			"X11",
			"GL",
			"pthread",
		}

	configuration { "linux-steamlink" }
		links {
			"EGL",
			"GLESv2",
			"SDL2",
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

	configuration { "osx" }
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
bgfxProject("", "StaticLib", {})

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
		, "17-drawstress"
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
		)

	-- C99 source doesn't compile under WinRT settings
	if not premake.vstudio.iswinrt() then
		exampleProject(false, "25-c99")
	end
end

if _OPTIONS["with-shared-lib"] then
	group "libs"
	bgfxProject("-shared-lib", "SharedLib", {})
end

if _OPTIONS["with-tools"] then
	group "tools"
	dofile "shaderc.lua"
	dofile "texturec.lua"
	dofile "texturev.lua"
	dofile "geometryc.lua"
	dofile "geometryv.lua"
end
