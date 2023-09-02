--
-- Copyright 2010-2018 Branimir Karadzic. All rights reserved.
-- License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
--

local GLSL_OPTIMIZER = path.join(BGFX_DIR, "3rdparty/glsl-optimizer")
local FCPP_DIR = path.join(BGFX_DIR, "3rdparty/fcpp")
local GLSLANG = path.join(BGFX_DIR, "3rdparty/glslang")
local SPIRV_CROSS = path.join(BGFX_DIR, "3rdparty/spirv-cross")
local SPIRV_HEADERS  = path.join(BGFX_DIR, "3rdparty/spirv-headers")
local SPIRV_TOOLS = path.join(BGFX_DIR, "3rdparty/spirv-tools")
local WEBGPU = path.join(BGFX_DIR, "3rdparty/webgpu")

group "libs"

project "brtshaderc"
	kind "StaticLib"

    files {
        path.join(BGFX_DIR, "tools/brtshaderc/brtshaderc.cpp"),
    }

-- project "webgpu"
--     kind "StaticLib"

    includedirs {
        path.join(WEBGPU, "include"),
    }

-- project "spirv-opt"
--     kind "StaticLib"

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
        path.join(SPIRV_TOOLS, "source/enum_string_mapping.cpp"),
        path.join(SPIRV_TOOLS, "source/enum_string_mapping.h"),
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
        path.join(SPIRV_TOOLS, "source/text.cpp"),
        path.join(SPIRV_TOOLS, "source/text.h"),
        path.join(SPIRV_TOOLS, "source/text_handler.cpp"),
        path.join(SPIRV_TOOLS, "source/text_handler.h"),
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

-- project "spirv-cross"
-- 	kind "StaticLib"

	defines {
		"SPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS",
	}

	includedirs {
        SPIRV_CROSS,
		-- path.join(SPIRV_CROSS, "include/spirv_cross"),
		path.join(SPIRV_CROSS, "include"),
	}

    files {
        path.join(SPIRV_CROSS, "**.h"),
        path.join(SPIRV_CROSS, "**.hpp"),
        path.join(SPIRV_CROSS, "**.cpp"),
        path.join(SPIRV_CROSS, "include/spirv_cross/**.hpp"),
        path.join(SPIRV_CROSS, "include/spirv_cross/**.h"),
    }

    removefiles {
        path.join(SPIRV_CROSS, "main.cpp"),
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

	configuration {}

--project "glslang"
--    kind "StaticLib"

    defines {
        "ENABLE_OPT=1", -- spirv-tools
        "ENABLE_HLSL=1",
        "BRTSHADERC_LIBRARY",
    }
    
    includedirs {
        GLSLANG,
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

    removefiles {
        path.join(GLSLANG, "glslang/OSDependent/Unix/main.cpp"),
        path.join(GLSLANG, "glslang/OSDependent/Windows/main.cpp"),
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
            "/wd4100", -- warning C4100: 'inclusionDepth' : unreferenced formal parameter
            "/wd4127", -- warning C4127: conditional expression is constant
            "/wd4189", -- warning C4189: 'isFloat': local variable is initialized but not referenced
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'char', possible loss of data
            "/wd4310", -- warning C4310: cast truncates constant value
            "/wd4456", -- warning C4456: declaration of 'feature' hides previous local declaration
            "/wd4457", -- warning C4457: declaration of 'token' hides function parameter
            "/wd4458", -- warning C4458: declaration of 'language' hides class member
            "/wd4702", -- warning C4702: unreachable code
            "/wd4715", -- warning C4715: 'spv::Builder::makeFpConstant': not all control paths return a value
        }

    configuration { "mingw* or linux or osx" }
        buildoptions {
            "-Wno-ignored-qualifiers",
            "-Wno-missing-field-initializers",
            "-Wno-reorder",
            "-Wno-return-type",
            "-Wno-shadow",
            "-Wno-sign-compare",
            "-Wno-undef",
            "-Wno-unknown-pragmas",
            "-Wno-unused-function",
            "-Wno-unused-parameter",
            "-Wno-unused-variable",
        }

    configuration { "osx" }
        buildoptions {
            "-Wno-c++11-extensions",
            "-Wno-unused-const-variable",
            "-Wno-deprecated-register",
        }

    configuration { "linux-*" }
        buildoptions {
            "-Wno-unused-but-set-variable",
        }

    configuration { "mingw* or linux or osx" }
        buildoptions {
            "-fno-strict-aliasing", -- glslang has bugs if strict aliasing is used.
        }

    configuration {}

--project "glsl-optimizer"
--   kind "StaticLib"

    includedirs {
        path.join(GLSL_OPTIMIZER, "src"),
        path.join(GLSL_OPTIMIZER, "include"),
        path.join(GLSL_OPTIMIZER, "src/mesa"),
        path.join(GLSL_OPTIMIZER, "src/mapi"),
        path.join(GLSL_OPTIMIZER, "src/glsl"),
    }

    files {
        path.join(GLSL_OPTIMIZER, "src/mesa/**.c"),
        path.join(GLSL_OPTIMIZER, "src/glsl/**.cpp"),
        path.join(GLSL_OPTIMIZER, "src/mesa/**.h"),
        path.join(GLSL_OPTIMIZER, "src/glsl/**.c"),
        path.join(GLSL_OPTIMIZER, "src/glsl/**.cpp"),
        path.join(GLSL_OPTIMIZER, "src/glsl/**.h"),
        path.join(GLSL_OPTIMIZER, "src/util/**.c"),
        path.join(GLSL_OPTIMIZER, "src/util/**.h"),
    }

    removefiles {
        path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/glcpp.c"),
        path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/tests/**"),
        path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/**.l"),
        path.join(GLSL_OPTIMIZER, "src/glsl/glcpp/**.y"),
        path.join(GLSL_OPTIMIZER, "src/glsl/ir_set_program_inouts.cpp"),
        path.join(GLSL_OPTIMIZER, "src/glsl/main.cpp"),
        path.join(GLSL_OPTIMIZER, "src/glsl/builtin_stubs.cpp"),
    }

    configuration { "Release" }
        flags {
            "Optimize",
        }

        removeflags {
            -- GCC 4.9 -O2 + -fno-strict-aliasing don't work together...
            "OptimizeSpeed",
        }

    configuration { "vs*" }
        includedirs {
            path.join(GLSL_OPTIMIZER, "src/glsl/msvc"),
        }

        defines { -- glsl-optimizer
            "__STDC__",
            "__STDC_VERSION__=199901L",
            "strdup=_strdup",
            "alloca=_alloca",
            "isascii=__isascii",
        }

        buildoptions {
            "/wd4100", -- error C4100: '' : unreferenced formal parameter
            "/wd4127", -- warning C4127: conditional expression is constant
            "/wd4132", -- warning C4132: 'deleted_key_value': const object should be initialized
            "/wd4189", -- warning C4189: 'interface_type': local variable is initialized but not referenced
            "/wd4204", -- warning C4204: nonstandard extension used: non-constant aggregate initializer
            "/wd4244", -- warning C4244: '=': conversion from 'const flex_int32_t' to 'YY_CHAR', possible loss of data
            "/wd4389", -- warning C4389: '!=': signed/unsigned mismatch
            "/wd4245", -- warning C4245: 'return': conversion from 'int' to 'unsigned int', signed/unsigned mismatch
            "/wd4701", -- warning C4701: potentially uninitialized local variable 'lower' used
            "/wd4702", -- warning C4702: unreachable code
            "/wd4706", -- warning C4706: assignment within conditional expression
            "/wd4996", -- warning C4996: 'strdup': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _strdup.
        }

    configuration { "mingw* or linux or osx" }
        buildoptions {
            "-fno-strict-aliasing", -- glsl-optimizer has bugs if strict aliasing is used.

            "-Wno-implicit-fallthrough",
            "-Wno-sign-compare",
            "-Wno-unused-function",
            "-Wno-unused-parameter",
        }

        removebuildoptions {
            "-Wshadow", -- glsl-optimizer is full of -Wshadow warnings ignore it.
        }

    configuration { "osx" }
        buildoptions {
            "-Wno-deprecated-register",
        }

    configuration { "mingw* or linux" }
        buildoptions {
            "-Wno-misleading-indentation",
        }

    configuration {}

--project "fcpp"
--    kind "StaticLib"

    defines { -- fcpp
        "NINCLUDE=64",
        "NWORK=65536",
        "NBUFF=65536",
        "OLD_PREPROCESSOR=0",
    }

    files {
        path.join(FCPP_DIR, "**.h"),
        path.join(FCPP_DIR, "cpp1.c"),
        path.join(FCPP_DIR, "cpp2.c"),
        path.join(FCPP_DIR, "cpp3.c"),
        path.join(FCPP_DIR, "cpp4.c"),
        path.join(FCPP_DIR, "cpp5.c"),
        path.join(FCPP_DIR, "cpp6.c"),
        path.join(FCPP_DIR, "cpp6.c"),
    }

    configuration { "vs*" }

        buildoptions {
            "/wd4055", -- warning C4055: 'type cast': from data pointer 'void *' to function pointer 'void (__cdecl *)(char *,void *)'
            "/wd4244", -- warning C4244: '=': conversion from 'const flex_int32_t' to 'YY_CHAR', possible loss of data
            "/wd4701", -- warning C4701: potentially uninitialized local variable 'lower' used
            "/wd4706", -- warning C4706: assignment within conditional expression
        }

    configuration { "not vs*" }
        buildoptions {
            "-Wno-implicit-fallthrough",
        }

    configuration {}

--project "shaderc"
--    kind "ConsoleApp"

    defines {
        "BRTSHADERC_LIBRARY",
    }

    includedirs {
        path.join(BX_DIR,   "include"),
        path.join(BIMG_DIR, "include"),
        path.join(BGFX_DIR, "include"),

        path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
        FCPP_DIR,

        path.join(BGFX_DIR, "3rdparty/glslang/glslang/Public"),
        path.join(BGFX_DIR, "3rdparty/glslang/glslang/Include"),
        path.join(BGFX_DIR, "3rdparty/glslang"),

        path.join(GLSL_OPTIMIZER, "include"),
        path.join(GLSL_OPTIMIZER, "src/glsl"),
    }

    links {
        "bx",
        "fcpp",
        "glslang",
        "glsl-optimizer",
        "spirv-opt",
    }

    files {
        path.join(BGFX_DIR, "tools/shaderc/**.cpp"),
        path.join(BGFX_DIR, "tools/shaderc/**.h"),
        path.join(BGFX_DIR, "src/vertexdecl.**"),
        path.join(BGFX_DIR, "src/shader_spirv.**"),
    }

    configuration { "mingw-*" }
        targetextension ".exe"

    configuration { "osx" }
        links {
            "Cocoa.framework",
        }

    configuration { "vs*" }
        includedirs {
            path.join(GLSL_OPTIMIZER, "include/c99"),
        }

    configuration { "vs20* or mingw*" }
        links {
            "psapi",
        }

    configuration { "Debug" }
        defines {
            "BX_CONFIG_DEBUG=1",
        }

    configuration { "Release" }
        defines {
            "BX_CONFIG_DEBUG=0",
        }

    configuration {}

    if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-ext"), {
        path.join(BGFX_DIR, "scripts/shaderc.lua"), }) then

        if filesexist(BGFX_DIR, path.join(BGFX_DIR, "../bgfx-ext"), {
            path.join(BGFX_DIR, "tools/shaderc/shaderc_pssl.cpp"), }) then

            removefiles {
                path.join(BGFX_DIR, "tools/shaderc/shaderc_pssl.cpp"),
            }
        end

        dofile(path.join(BGFX_DIR, "../bgfx-ext/scripts/shaderc.lua") )
    end

    configuration { "osx or linux*" }
        links {
            "pthread",
        }

    configuration {}

    strip()


