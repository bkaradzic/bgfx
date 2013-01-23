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

dofile (BX_DIR .. "premake/toolchain.lua")
toolchain(BGFX_BUILD_DIR, BGFX_THIRD_PARTY_DIR)

function copyLib()
end

dofile "bgfx.lua"
dofile "example-00-helloworld.lua"
dofile "example-01-cubes.lua"
dofile "example-02-metaballs.lua"
dofile "example-03-raymarch.lua"
dofile "example-04-mesh.lua"
dofile "example-05-instancing.lua"
dofile "example-06-bump.lua"
dofile "example-07-callback.lua"
dofile "example-08-update.lua"
dofile "makedisttex.lua"
dofile "shaderc.lua"
dofile "texturec.lua"
dofile "geometryc.lua"
