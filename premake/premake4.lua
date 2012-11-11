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

newoption {
	trigger = "gcc",
	value = "GCC",
	description = "Choose GCC flavor",
	allowed = {
		{ "emscripten", "Emscripten" },
		{ "linux", "Linux" },
		{ "mingw", "MinGW" },
		{ "nacl", "Google Native Client" },
	}
}

-- Avoid error when invoking premake4 --help.
if (_ACTION == nil) then return end

BGFX_DIR = (path.getabsolute("..") .. "/")
local BGFX_BUILD_DIR = (BGFX_DIR .. ".build/")
local BGFX_THIRD_PARTY_DIR = (BGFX_DIR .. "3rdparty/")

BX_DIR = (BGFX_DIR .. "/../../bx/")

local XEDK = os.getenv("XEDK")
if not XEDK then XEDK = "<you must install XBOX SDK>" end

location (BGFX_BUILD_DIR .. "projects/" .. _ACTION)

if _ACTION == "clean" then
	os.rmdir(BUILD_DIR)
end

if _ACTION == "gmake" then

	if nil == _OPTIONS["gcc"] then
		print("GCC flavor must be specified!")
		os.exit(1)
	end

	flags {
		"ExtraWarnings",
	}

	if "emscripten" == _OPTIONS["gcc"] then

		if not os.getenv("EMSCRIPTEN") then 
			print("Set EMSCRIPTEN enviroment variables.")
		end

		premake.gcc.cc = "$(EMSCRIPTEN)/emcc"
		premake.gcc.cxx = "$(EMSCRIPTEN)/em++"
		premake.gcc.ar = "$(EMSCRIPTEN)/emar"
		location (BGFX_BUILD_DIR .. "projects/" .. _ACTION .. "-emscripten")
	end

	if "linux" == _OPTIONS["gcc"] then
		location (BGFX_BUILD_DIR .. "projects/" .. _ACTION .. "-linux")
	end

	if "mingw" == _OPTIONS["gcc"] then
		premake.gcc.cc = "$(MINGW)/bin/mingw32-gcc"
		premake.gcc.cxx = "$(MINGW)/bin/mingw32-g++"
		premake.gcc.ar = "$(MINGW)/bin/ar"
		location (BGFX_BUILD_DIR .. "projects/" .. _ACTION .. "-mingw")
	end

	if "nacl" == _OPTIONS["gcc"] then

		if not os.getenv("NACL") then 
			print("Set NACL enviroment variables.")
		end

		premake.gcc.cc = "$(NACL)/bin/x86_64-nacl-gcc"
		premake.gcc.cxx = "$(NACL)/bin/x86_64-nacl-g++"
		premake.gcc.ar = "$(NACL)/bin/x86_64-nacl-ar"
		location (BGFX_BUILD_DIR .. "projects/" .. _ACTION .. "-nacl")
	end
end

flags {
	"StaticRuntime",
	"NoMinimalRebuild",
	"NoPCH",
	"NativeWChar",
	"NoRTTI",
	"NoExceptions",
	"NoEditAndContinue",
	"Symbols",
}

defines {
	"__STDC_LIMIT_MACROS",
	"__STDC_FORMAT_MACROS",
	"__STDC_CONSTANT_MACROS",
}

configuration "Debug"
	targetsuffix "Debug"

configuration "Release"
	flags {
		"OptimizeSpeed",
	}
	targetsuffix "Release"

configuration { "vs*" }
	includedirs { BX_DIR .. "include/compat/msvc" }
	defines {
		"WIN32",
		"_WIN32",
		"_HAS_EXCEPTIONS=0",
		"_HAS_ITERATOR_DEBUGGING=0",
		"_SCL_SECURE=0",
		"_SECURE_SCL=0",
		"_SCL_SECURE_NO_WARNINGS",
		"_CRT_SECURE_NO_WARNINGS",
		"_CRT_SECURE_NO_DEPRECATE",
	}
	buildoptions {
		"/Oy-", -- Suppresses creation of frame pointers on the call stack.
		"/Ob2", -- The Inline Function Expansion
	}

configuration { "x32", "vs*" }
	targetdir (BGFX_BUILD_DIR .. "win32_" .. _ACTION .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win32_" .. _ACTION .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/win32_" .. _ACTION }

configuration { "x64", "vs*" }
	defines { "_WIN64" }
	targetdir (BGFX_BUILD_DIR .. "win64_" .. _ACTION .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win64_" .. _ACTION .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/win64_" .. _ACTION }

configuration { "mingw" }
	defines { "WIN32" }
	includedirs { BX_DIR .. "include/compat/mingw" }
	buildoptions {
		"-std=c++0x",
		"-U__STRICT_ANSI__",
		"-Wunused-value",
		"-fdata-sections",
		"-ffunction-sections",
--		"-fmerge-all-constants"
	}
	linkoptions {
		"-Wl,--gc-sections",
	}

configuration { "x32", "mingw" }
	targetdir (BGFX_BUILD_DIR .. "win32_mingw" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win32_mingw" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/win32_mingw" }
	buildoptions { "-m32" }

configuration { "x64", "mingw" }
	targetdir (BGFX_BUILD_DIR .. "win64_mingw" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win64_mingw" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/win64_mingw" }
	buildoptions { "-m64" }

configuration { "linux" }
	buildoptions {
		"-std=c++0x",
		"-U__STRICT_ANSI__",
		"-Wunused-value",
		"-mfpmath=sse", -- force SSE to get 32-bit and 64-bit builds deterministic.
		"-msse2",
	}
	links {
		"rt",
	}
	linkoptions {
		"-Wl,--gc-sections",
	}

configuration { "linux", "x32" }
	targetdir (BGFX_BUILD_DIR .. "linux32_gcc" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "linux32_gcc" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/linux32_gcc" }
	buildoptions {
		"-m32",
	}

configuration { "linux", "x64" }
	targetdir (BGFX_BUILD_DIR .. "linux64_gcc" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "linux64_gcc" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/linux64_gcc" }
	buildoptions {
		"-m64",
	}

configuration { "emscripten" }
	targetdir (BGFX_BUILD_DIR .. "emscripten" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "emscripten" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/emscripten" }
	includedirs { "$(EMSCRIPTEN)/system/include" }
	buildoptions {
		"-pthread",
	}

configuration { "nacl" }
	defines { "_BSD_SOURCE=1", "_POSIX_C_SOURCE=199506", "_XOPEN_SOURCE=600" }
	includedirs { BX_DIR .. "include/compat/nacl" }
	buildoptions {
		"-std=c++0x",
		"-U__STRICT_ANSI__",
		"-pthread",
		"-fno-stack-protector",
		"-fdiagnostics-show-option",
		"-Wunused-value",
		"-fdata-sections",
		"-ffunction-sections",
		"-mfpmath=sse", -- force SSE to get 32-bit and 64-bit builds deterministic.
		"-msse2",
--		"-fmerge-all-constants",
	}
	linkoptions {
		"-Wl,--gc-sections",
	}

configuration { "x32", "nacl" }
	targetdir (BGFX_BUILD_DIR .. "nacl-x86" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "nacl-x86" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/nacl-x86" }
	linkoptions { "-melf32_nacl" }

configuration { "x64", "nacl" }
	targetdir (BGFX_BUILD_DIR .. "nacl-x64" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "nacl-x64" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/nacl-x64" }
	linkoptions { "-melf64_nacl" }

configuration { "Xbox360" }
	targetdir (BGFX_BUILD_DIR .. "xbox360" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "xbox360" .. "/obj")
	includedirs { BX_DIR .. "include/compat/msvc" }
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/xbox360" }
	defines {
		"NOMINMAX",
		"_XBOX",
	}

configuration {} -- reset configuration

function copyLib()
end

dofile "bgfx.lua"
dofile "ddsdump.lua"
dofile "makedisttex.lua"
dofile "shaderc.lua"
dofile "openctm.lua"
dofile "example-00-helloworld.lua"
dofile "example-01-cubes.lua"
dofile "example-02-metaballs.lua"
dofile "example-03-raymarch.lua"
dofile "example-04-mesh.lua"
dofile "example-05-instancing.lua"
dofile "example-06-bump.lua"
