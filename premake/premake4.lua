--
-- Copyright 2010-2011 Branimir Karadzic. All rights reserved.
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
		{ "mingw", "MinGW" },
		{ "nacl", "Google Native Client" },
	}
}

-- Avoid error when invoking premake4 --help.
if (_ACTION == nil) then return end

BGFX_DIR = (path.getabsolute("..") .. "/")
local BGFX_BUILD_DIR = (BGFX_DIR .. ".build/")
local BGFX_THIRD_PARTY_DIR = (BGFX_DIR .. "3rdparty/")

local XEDK = os.getenv("XEDK")
if not XEDK then XEDK = "<you must install XBOX SDK>" end

location (BGFX_BUILD_DIR .. "projects/" .. _ACTION)

if _ACTION == "gmake" then

	flags {
		"ExtraWarnings",
	}

	if "linux" ~= os.get() and nil == _OPTIONS["gcc"] then
		print("GCC flavor must be specified!")
		os.exit(1)
	end

	if "mingw" == _OPTIONS["gcc"] then
		premake.gcc.cc = "$(MINGW)/bin/mingw32-gcc"
		premake.gcc.cxx = "$(MINGW)/bin/mingw32-g++"
		premake.gcc.ar = "$(MINGW)/bin/ar"
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

configuration "Debug"
	targetsuffix "Debug"

configuration "Release"
	flags {
		"OptimizeSpeed",
	}
	targetsuffix "Release"

configuration { "vs*" }
	defines {
		"_HAS_EXCEPTIONS=0",
		"_HAS_ITERATOR_DEBUGGING=0",
		"_SCL_SECURE=0",
		"_CRT_SECURE_NO_WARNINGS",
		"_CRT_SECURE_NO_DEPRECATE",
		"__STDC_LIMIT_MACROS",
		"__STDC_FORMAT_MACROS",
		"__STDC_CONSTANT_MACROS",
	}

configuration { "x32", "vs*" }
	defines { "WIN32" }
	targetdir (BGFX_BUILD_DIR .. "win32_" .. _ACTION .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win32_" .. _ACTION .. "/obj")
	includedirs { BGFX_THIRD_PARTY_DIR .. "compiler/msvc" }

configuration { "x64", "vs*" }
	defines { "WIN32" }
	targetdir (BGFX_BUILD_DIR .. "win64_" .. _ACTION .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win64_" .. _ACTION .. "/obj")
	includedirs { BGFX_THIRD_PARTY_DIR .. "compiler/msvc" }

configuration { "x32", "mingw" }
	defines { "WIN32" }
	targetdir (BGFX_BUILD_DIR .. "win32_mingw" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win32_mingw" .. "/obj")
	includedirs { BGFX_THIRD_PARTY_DIR .. "compiler/mingw" }

configuration { "x64", "mingw" }
	defines { "WIN32" }
	targetdir (BGFX_BUILD_DIR .. "win64_mingw" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "win64_mingw" .. "/obj")
	includedirs { BGFX_THIRD_PARTY_DIR .. "compiler/mingw" }

configuration { "nacl" }
	defines { "_BSD_SOURCE=1", "_POSIX_C_SOURCE=199506", "_XOPEN_SOURCE=600" }
	links {
		"ppapi",
		"ppapi_gles2",
	}
	includedirs { BGFX_THIRD_PARTY_DIR .. "compiler/nacl" }
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
	linkoptions {
		"-melf32_nacl",
	}

configuration { "x64", "nacl" }
	targetdir (BGFX_BUILD_DIR .. "nacl-x64" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "nacl-x64" .. "/obj")
	libdirs { BGFX_THIRD_PARTY_DIR .. "lib/nacl-x64" }
	linkoptions {
		"-melf64_nacl",
	}

configuration { "x32", "linux" }
	targetdir (BGFX_BUILD_DIR .. "linux32" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "linux32" .. "/obj")

configuration { "x64", "linux" }
	targetdir (BGFX_BUILD_DIR .. "linux64" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "linux64" .. "/obj")

configuration { "Xbox360" }
	defines { "_XBOX", "NOMINMAX" }
	targetdir (BGFX_BUILD_DIR .. "xbox360" .. "/bin")
	objdir (BGFX_BUILD_DIR .. "xbox360" .. "/obj")
	includedirs { BGFX_THIRD_PARTY_DIR .. "compiler/msvc" }

configuration {} -- reset configuration

function copyLib()
end

dofile "bgfx.lua"
dofile "ddsdump.lua"
dofile "helloworld.lua"
dofile "makedisttex.lua"
dofile "shaderc.lua"
