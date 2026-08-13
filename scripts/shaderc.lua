--
-- Copyright 2010-2026 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
--

group "tools/shaderc"

local GLSLANG        = path.join(BGFX_DIR, "3rdparty/glslang")
local SPIRV_CROSS    = path.join(BGFX_DIR, "3rdparty/spirv-cross")
local SPIRV_HEADERS  = path.join(BGFX_DIR, "3rdparty/spirv-headers")
local SPIRV_TOOLS    = path.join(BGFX_DIR, "3rdparty/spirv-tools")
local TINT           = path.join(BGFX_DIR, "3rdparty/dawn")
local D3D4LINUX      = path.join(BGFX_DIR, "3rdparty/d3d4linux")

project "tint-core"
	kind "StaticLib"

	includedirs {
		path.join(TINT),
		path.join(TINT, "src/tint"),
		path.join(TINT, "third_party/protobuf/src"),
		path.join(TINT, "third_party/abseil-cpp"),
		path.join(SPIRV_TOOLS),
		path.join(SPIRV_TOOLS, "include"),
		path.join(SPIRV_TOOLS, "include/generated"),
		path.join(SPIRV_HEADERS, "include"),
	}

	defines {
		"TINT_BUILD_GLSL_WRITER=0",
		"TINT_BUILD_HLSL_WRITER=0",
		"TINT_BUILD_MSL_WRITER=0",
		"TINT_BUILD_NULL_WRITER=0",

		"TINT_BUILD_SPV_READER=1",
		"TINT_BUILD_SPV_WRITER=0",

		"TINT_BUILD_WGSL_READER=0",
		"TINT_BUILD_WGSL_WRITER=1",

		"TINT_BUILD_IS_LINUX=1",
		"TINT_BUILD_IS_MAC=0",
		"TINT_BUILD_IS_WIN=0",

		"TINT_ENABLE_IR_VALIDATION=0",
	}

	files {
		path.join(TINT, "src/tint/utils/**.cc"),
		path.join(TINT, "src/tint/utils/**.h"),
		path.join(TINT, "src/tint/lang/core/**.cc"),
		path.join(TINT, "src/tint/lang/core/**.h"),
		path.join(TINT, "src/tint/lang/null/**.cc"),
		path.join(TINT, "src/tint/lang/null/**.h"),
	}

	configuration { "osx*" }
		buildoptions {
			"-Wno-unknown-warning-option",
		}

project "tint-lang"
	kind "StaticLib"

	includedirs {
		path.join(TINT),
		path.join(TINT, "src/tint"),
		path.join(TINT, "third_party/protobuf/src"),
		path.join(TINT, "third_party/abseil-cpp"),
		path.join(SPIRV_TOOLS),
		path.join(SPIRV_TOOLS, "include"),
		path.join(SPIRV_TOOLS, "include/generated"),
		path.join(SPIRV_HEADERS, "include"),
	}

	defines {
		"TINT_BUILD_GLSL_WRITER=0",
		"TINT_BUILD_HLSL_WRITER=0",
		"TINT_BUILD_MSL_WRITER=0",
		"TINT_BUILD_NULL_WRITER=0",

		"TINT_BUILD_SPV_READER=1",
		"TINT_BUILD_SPV_WRITER=0",

		"TINT_BUILD_WGSL_READER=0",
		"TINT_BUILD_WGSL_WRITER=1",

		"TINT_BUILD_IS_LINUX=1",
		"TINT_BUILD_IS_MAC=0",
		"TINT_BUILD_IS_WIN=0",

		"TINT_ENABLE_IR_VALIDATION=0",
	}

	files {
		path.join(TINT, "src/tint/lang/spirv/**.cc"),
		path.join(TINT, "src/tint/lang/spirv/**.h"),
		path.join(TINT, "src/tint/lang/wgsl/**.cc"),
		path.join(TINT, "src/tint/lang/wgsl/**.h"),
	}

	configuration { "osx*" }
		buildoptions {
			"-Wno-unknown-warning-option",
		}

project "tint-api"
	kind "StaticLib"

	includedirs {
		path.join(TINT),
		path.join(TINT, "src/tint"),
		path.join(TINT, "third_party/protobuf/src"),
		path.join(TINT, "third_party/abseil-cpp"),
		path.join(SPIRV_TOOLS),
		path.join(SPIRV_TOOLS, "include"),
		path.join(SPIRV_TOOLS, "include/generated"),
		path.join(SPIRV_HEADERS, "include"),
	}

	defines {
		"TINT_BUILD_GLSL_WRITER=0",
		"TINT_BUILD_HLSL_WRITER=0",
		"TINT_BUILD_MSL_WRITER=0",
		"TINT_BUILD_NULL_WRITER=0",

		"TINT_BUILD_SPV_READER=1",
		"TINT_BUILD_SPV_WRITER=0",

		"TINT_BUILD_WGSL_READER=0",
		"TINT_BUILD_WGSL_WRITER=1",

		"TINT_BUILD_IS_LINUX=1",
		"TINT_BUILD_IS_MAC=0",
		"TINT_BUILD_IS_WIN=0",

		"TINT_ENABLE_IR_VALIDATION=0",
	}

	files {
		path.join(TINT, "src/tint/api/**.cc"),
		path.join(TINT, "src/tint/api/**.h"),
	}

	configuration { "osx*" }
		buildoptions {
			"-Wno-unknown-warning-option",
		}

project "spirv-opt"
	kind "StaticLib"

	includedirs {
		SPIRV_TOOLS,

		path.join(SPIRV_TOOLS, "include"),
		path.join(SPIRV_TOOLS, "include/generated"),
		path.join(SPIRV_TOOLS, "source"),
		path.join(SPIRV_HEADERS, "include"),
	}

	files {
		path.join(SPIRV_TOOLS, "source/opt/**.cpp"),
		path.join(SPIRV_TOOLS, "source/opt/**.h"),
		path.join(SPIRV_TOOLS, "source/reduce/**.cpp"),
		path.join(SPIRV_TOOLS, "source/reduce/**.h"),
		path.join(SPIRV_TOOLS, "source/val/**.cpp"),
		path.join(SPIRV_TOOLS, "source/val/**.h"),

		-- libspirv
		path.join(SPIRV_TOOLS, "source/assembly_grammar.cpp"),
		path.join(SPIRV_TOOLS, "source/assembly_grammar.h"),
		path.join(SPIRV_TOOLS, "source/binary.cpp"),
		path.join(SPIRV_TOOLS, "source/binary.h"),
		path.join(SPIRV_TOOLS, "source/cfa.h"),
		path.join(SPIRV_TOOLS, "source/diagnostic.cpp"),
		path.join(SPIRV_TOOLS, "source/diagnostic.h"),
		path.join(SPIRV_TOOLS, "source/disassemble.cpp"),
		path.join(SPIRV_TOOLS, "source/disassemble.h"),
		path.join(SPIRV_TOOLS, "source/enum_set.h"),
		path.join(SPIRV_TOOLS, "source/ext_inst.cpp"),
		path.join(SPIRV_TOOLS, "source/ext_inst.h"),
		path.join(SPIRV_TOOLS, "source/extensions.cpp"),
		path.join(SPIRV_TOOLS, "source/extensions.h"),
		path.join(SPIRV_TOOLS, "source/instruction.h"),
		path.join(SPIRV_TOOLS, "source/latest_version_glsl_std_450_header.h"),
		path.join(SPIRV_TOOLS, "source/latest_version_opencl_std_header.h"),
		path.join(SPIRV_TOOLS, "source/latest_version_spirv_header.h"),
		path.join(SPIRV_TOOLS, "source/libspirv.cpp"),
		path.join(SPIRV_TOOLS, "source/macro.h"),
		path.join(SPIRV_TOOLS, "source/name_mapper.cpp"),
		path.join(SPIRV_TOOLS, "source/name_mapper.h"),
		path.join(SPIRV_TOOLS, "source/opcode.cpp"),
		path.join(SPIRV_TOOLS, "source/opcode.h"),
		path.join(SPIRV_TOOLS, "source/operand.cpp"),
		path.join(SPIRV_TOOLS, "source/operand.h"),
		path.join(SPIRV_TOOLS, "source/parsed_operand.cpp"),
		path.join(SPIRV_TOOLS, "source/parsed_operand.h"),
		path.join(SPIRV_TOOLS, "source/print.cpp"),
		path.join(SPIRV_TOOLS, "source/print.h"),
		path.join(SPIRV_TOOLS, "source/software_version.cpp"),
		path.join(SPIRV_TOOLS, "source/spirv_constant.h"),
		path.join(SPIRV_TOOLS, "source/spirv_definition.h"),
		path.join(SPIRV_TOOLS, "source/spirv_endian.cpp"),
		path.join(SPIRV_TOOLS, "source/spirv_endian.h"),
		path.join(SPIRV_TOOLS, "source/spirv_optimizer_options.cpp"),
		path.join(SPIRV_TOOLS, "source/spirv_reducer_options.cpp"),
		path.join(SPIRV_TOOLS, "source/spirv_target_env.cpp"),
		path.join(SPIRV_TOOLS, "source/spirv_target_env.h"),
		path.join(SPIRV_TOOLS, "source/spirv_validator_options.cpp"),
		path.join(SPIRV_TOOLS, "source/spirv_validator_options.h"),
		path.join(SPIRV_TOOLS, "source/table.cpp"),
		path.join(SPIRV_TOOLS, "source/table.h"),
		path.join(SPIRV_TOOLS, "source/table2.cpp"),
		path.join(SPIRV_TOOLS, "source/table2.h"),
		path.join(SPIRV_TOOLS, "source/text.cpp"),
		path.join(SPIRV_TOOLS, "source/text.h"),
		path.join(SPIRV_TOOLS, "source/text_handler.cpp"),
		path.join(SPIRV_TOOLS, "source/text_handler.h"),
		path.join(SPIRV_TOOLS, "source/to_string.cpp"),
		path.join(SPIRV_TOOLS, "source/to_string.h"),
		path.join(SPIRV_TOOLS, "source/util/bit_vector.cpp"),
		path.join(SPIRV_TOOLS, "source/util/bit_vector.h"),
		path.join(SPIRV_TOOLS, "source/util/bitutils.h"),
		path.join(SPIRV_TOOLS, "source/util/hex_float.h"),
		path.join(SPIRV_TOOLS, "source/util/parse_number.cpp"),
		path.join(SPIRV_TOOLS, "source/util/parse_number.h"),
		path.join(SPIRV_TOOLS, "source/util/string_utils.cpp"),
		path.join(SPIRV_TOOLS, "source/util/string_utils.h"),
		path.join(SPIRV_TOOLS, "source/util/timer.h"),
	}

	configuration { "vs*" }
		buildoptions {
			"/wd4127", -- warning C4127: conditional expression is constant
			"/wd4267", -- warning C4267: 'argument': conversion from '' to '', possible loss of data
			"/wd4389", -- warning C4389: '==': signed/unsigned mismatch
			"/wd4702", -- warning C4702: unreachable code
			"/wd4706", -- warning C4706: assignment within conditional expression
		}

	configuration { "mingw* or linux* or osx*" }
		buildoptions {
			"-Wno-switch",
		}

	configuration { "mingw* or linux-gcc-*" }
		buildoptions {
			"-Wno-misleading-indentation",
		}

	configuration {}

project "spirv-cross"
	kind "StaticLib"

	defines {
		"SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS",
	}

	includedirs {
		path.join(SPIRV_CROSS, "include"),
	}

	files {
		path.join(SPIRV_CROSS, "spirv.hpp"),
		path.join(SPIRV_CROSS, "spirv_cfg.cpp"),
		path.join(SPIRV_CROSS, "spirv_cfg.hpp"),
		path.join(SPIRV_CROSS, "spirv_common.hpp"),
		path.join(SPIRV_CROSS, "spirv_cpp.cpp"),
		path.join(SPIRV_CROSS, "spirv_cpp.hpp"),
		path.join(SPIRV_CROSS, "spirv_cross.cpp"),
		path.join(SPIRV_CROSS, "spirv_cross.hpp"),
		path.join(SPIRV_CROSS, "spirv_cross_parsed_ir.cpp"),
		path.join(SPIRV_CROSS, "spirv_cross_parsed_ir.hpp"),
		path.join(SPIRV_CROSS, "spirv_cross_util.cpp"),
		path.join(SPIRV_CROSS, "spirv_cross_util.hpp"),
		path.join(SPIRV_CROSS, "spirv_glsl.cpp"),
		path.join(SPIRV_CROSS, "spirv_glsl.hpp"),
		path.join(SPIRV_CROSS, "spirv_hlsl.cpp"),
		path.join(SPIRV_CROSS, "spirv_hlsl.hpp"),
		path.join(SPIRV_CROSS, "spirv_msl.cpp"),
		path.join(SPIRV_CROSS, "spirv_msl.hpp"),
		path.join(SPIRV_CROSS, "spirv_parser.cpp"),
		path.join(SPIRV_CROSS, "spirv_parser.hpp"),
		path.join(SPIRV_CROSS, "spirv_reflect.cpp"),
		path.join(SPIRV_CROSS, "spirv_reflect.hpp"),
	}

	configuration { "vs*" }
		buildoptions {
			"/wd4018", -- warning C4018: '<': signed/unsigned mismatch
			"/wd4245", -- warning C4245: 'return': conversion from 'int' to 'unsigned int', signed/unsigned mismatch
			"/wd4706", -- warning C4706: assignment within conditional expression
			"/wd4715", -- warning C4715: '': not all control paths return a value
		}

	configuration { "mingw* or linux* or osx*" }
		buildoptions {
			"-Wno-type-limits",
		}


	configuration { "osx*" }
		buildoptions {
			"-Wno-deprecated-this-capture",
			"-Wno-nan-infinity-disabled",
		}

	configuration {}

project "glslang"
	kind "StaticLib"

	defines {
		"ENABLE_OPT=1", -- spirv-tools
		"ENABLE_HLSL=1",
	}

	includedirs {
		GLSLANG,
		path.join(GLSLANG, ".."),
		path.join(SPIRV_TOOLS, "include"),
		path.join(SPIRV_TOOLS, "source"),
	}

	files {
		path.join(GLSLANG, "glslang/**.cpp"),
		path.join(GLSLANG, "glslang/**.h"),

		path.join(GLSLANG, "hlsl/**.cpp"),
		path.join(GLSLANG, "hlsl/**.h"),

		path.join(GLSLANG, "SPIRV/**.cpp"),
		path.join(GLSLANG, "SPIRV/**.h"),

		path.join(GLSLANG, "OGLCompilersDLL/**.cpp"),
		path.join(GLSLANG, "OGLCompilersDLL/**.h"),
	}

	configuration { "windows" }
		removefiles {
			path.join(GLSLANG, "glslang/OSDependent/Unix/**.cpp"),
			path.join(GLSLANG, "glslang/OSDependent/Unix/**.h"),
		}

	configuration { "not windows" }
		removefiles {
			path.join(GLSLANG, "glslang/OSDependent/Windows/**.cpp"),
			path.join(GLSLANG, "glslang/OSDependent/Windows/**.h"),
		}

	configuration { "vs*" }
		buildoptions {
			"/wd4005", -- warning C4005: '_CRT_SECURE_NO_WARNINGS': macro redefinition
			"/wd4065", -- warning C4065: switch statement contains 'default' but no 'case' labels
			"/wd4100", -- warning C4100: 'inclusionDepth' : unreferenced formal parameter
			"/wd4127", -- warning C4127: conditional expression is constant
			"/wd4189", -- warning C4189: 'isFloat': local variable is initialized but not referenced
			"/wd4244", -- warning C4244: '=': conversion from 'int' to 'char', possible loss of data
			"/wd4310", -- warning C4310: cast truncates constant value
			"/wd4389", -- warning C4389: '==': signed/unsigned mismatch
			"/wd4456", -- warning C4456: declaration of 'feature' hides previous local declaration
			"/wd4457", -- warning C4457: declaration of 'token' hides function parameter
			"/wd4458", -- warning C4458: declaration of 'language' hides class member
			"/wd4702", -- warning C4702: unreachable code
			"/wd4715", -- warning C4715: 'spv::Builder::makeFpConstant': not all control paths return a value
			"/wd4838", -- warning C4838: conversion from 'spv::GroupOperation' to 'unsigned int' requires a narrowing conversion
		}

	configuration { "mingw-gcc or linux-gcc" }
		buildoptions {
			"-Wno-logical-op",
			"-Wno-maybe-uninitialized",
		}

	configuration { "mingw* or linux* or osx*" }
		buildoptions {
			"-fno-strict-aliasing", -- glslang has bugs if strict aliasing is used.
			"-Wno-ignored-qualifiers",
			"-Wno-implicit-fallthrough",
			"-Wno-missing-field-initializers",
			"-Wno-reorder",
			"-Wno-return-type",
			"-Wno-shadow",
			"-Wno-sign-compare",
			"-Wno-switch",
			"-Wno-undef",
			"-Wno-unknown-pragmas",
			"-Wno-unused-function",
			"-Wno-unused-parameter",
			"-Wno-unused-variable",
		}

	configuration { "osx*" }
		buildoptions {
			"-Wno-c++11-extensions",
			"-Wno-unused-const-variable",
			"-Wno-deprecated-register",
		}

	configuration { "linux-gcc-*" }
		buildoptions {
			"-Wno-unused-but-set-variable",
		}

	configuration {}

project "shaderc"
	kind "ConsoleApp"

	includedirs {
		path.join(BIMG_DIR, "include"),
		path.join(BGFX_DIR, "include"),

		path.join(BGFX_DIR, "3rdparty/directx-headers/include/directx"),

		path.join(BX_DIR, "3rdparty"),

		path.join(BGFX_DIR, "3rdparty/glslang/glslang/Public"),
		path.join(BGFX_DIR, "3rdparty/glslang/glslang/Include"),
		path.join(BGFX_DIR, "3rdparty/glslang"),

		SPIRV_CROSS,

		path.join(SPIRV_TOOLS, "include"),

		path.join(TINT),
		path.join(TINT, "src"),
	}

	links {
		"glslang",
		"spirv-opt",
		"spirv-cross",
		"tint-api",
		"tint-lang",
		"tint-core",
	}

	using_bx()

	files {
		path.join(BGFX_DIR, "tools/shaderc/**.cpp"),
		path.join(BGFX_DIR, "tools/shaderc/**.h"),
		path.join(BGFX_DIR, "src/vertexlayout.**"),
		path.join(BGFX_DIR, "src/shader**"),
	}

	configuration { "mingw-*" }
		targetextension ".exe"

	configuration { "osx*" }
		links {
			"Cocoa.framework",
		}

	configuration { "vs20* or mingw*" }
		links {
			"psapi",
		}

	configuration { "osx* or linux*" }
		links {
			"pthread",
		}

	-- Linux/macOS: d3d4linux for legacy HLSL (SM 5.0)
	-- Linux only: directx-headers for DXIL (SM 6.0+, no macOS DXC library available)
	configuration { "linux* or osx*" }
		includedirs {
			path.join(D3D4LINUX, "include"),
			path.join(BGFX_DIR, "3rdparty/directx-headers/include"),
			path.join(BGFX_DIR, "3rdparty/directx-headers/include/wsl/stubs"),
		}

	configuration {}

	if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-gnm"), {
		path.join(BGFX_DIR, "scripts/shaderc.lua"), }) then

		if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-gnm"), {
			path.join(BGFX_DIR, "tools/shaderc/shaderc_pssl.cpp"), }) then

			removefiles {
				path.join(BGFX_DIR, "tools/shaderc/shaderc_pssl.cpp"),
			}
		end

		dofile(path.join(BGFX_DIR, "../bgfx-gnm/scripts/shaderc.lua") )
	end

	strip()

group "tools"
