/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef SHADERC_H_HEADER_GUARD
#define SHADERC_H_HEADER_GUARD

namespace bgfx
{
	extern bool g_verbose;
}

#include <bx/bx.h>

// HLSL compilation support:
// - Windows: Native D3DCompiler DLL
// - Linux/macOS: d3d4linux (Wine-based D3DCompiler via IPC)
#ifndef SHADERC_CONFIG_HAS_D3DCOMPILER
#	if BX_PLATFORM_WINDOWS
#		if __has_include(<d3dcompiler.h>)
#			define SHADERC_CONFIG_HAS_D3DCOMPILER 1
#		endif
#	elif BX_PLATFORM_LINUX
#		if __has_include(<d3d4linux.h>)
#			define SHADERC_CONFIG_HAS_D3DCOMPILER 1
#		endif
#	endif
// Still not?
#	ifndef SHADERC_CONFIG_HAS_D3DCOMPILER
#		define SHADERC_CONFIG_HAS_D3DCOMPILER 0
#	endif
#endif // SHADERC_CONFIG_HAS_D3DCOMPILER

// DXIL compilation support (Shader Model 6.0+):
// - Windows: Native DXC (dxcompiler.dll)
// - Linux: DXC (libdxcompiler.so) via directx-headers
// - macOS: Not supported (no DXC dynamic library available)
#ifndef SHADERC_CONFIG_HAS_DXC
#	define SHADERC_CONFIG_HAS_DXC (0  \
		|| BX_PLATFORM_WINDOWS     \
		|| BX_PLATFORM_LINUX       \
		)
#endif // SHADERC_CONFIG_HAS_DXC

#ifndef SHADERC_CONFIG_HAS_TINT
#	if __has_include(<tint/api/tint.h>)
#		define SHADERC_CONFIG_HAS_TINT 1
#	else
#		define SHADERC_CONFIG_HAS_TINT 0
#	endif
#endif

#ifndef SHADERC_CONFIG_HAS_GLSLANG
#	if __has_include(<ShaderLang.h>) \
	&& __has_include(<SPIRV/SpvTools.h>)
#		define SHADERC_CONFIG_HAS_GLSLANG 1
#	else
#		define SHADERC_CONFIG_HAS_GLSLANG 0
#	endif
#endif

#ifndef SHADERC_CONFIG_HAS_GLSL_OPTIMIZER
#	if __has_include("glsl_optimizer.h")
#		define SHADERC_CONFIG_HAS_GLSL_OPTIMIZER 1
#	else
#		define SHADERC_CONFIG_HAS_GLSL_OPTIMIZER 0
#	endif
#endif

#include <bx/debug.h>
#include <bx/commandline.h>
#include <bx/endian.h>
#include <bx/uint32_t.h>
#include <bx/string.h>
#include <bx/hash.h>
#include <bx/file.h>
#include "../../src/vertexlayout.h"

#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

namespace bgfx
{
	extern bool g_verbose;

	bx::StringView nextWord(bx::StringView& _parse);

	constexpr uint16_t kAccessRead  = 0x8000;
	constexpr uint16_t kAccessWrite = 0x4000;
	constexpr uint16_t kAccessMask  = 0
		| kAccessRead
		| kAccessWrite
		;

	constexpr uint8_t kUniformFragmentBit  = 0x10;
	constexpr uint8_t kUniformSamplerBit   = 0x20;
	constexpr uint8_t kUniformReadOnlyBit  = 0x40;
	constexpr uint8_t kUniformCompareBit   = 0x80;
	constexpr uint8_t kUniformMask = 0
		| kUniformFragmentBit
		| kUniformSamplerBit
		| kUniformReadOnlyBit
		| kUniformCompareBit
		;

	const char* getUniformTypeName(UniformType::Enum _enum);
	UniformType::Enum nameToUniformTypeEnum(const char* _name);

	struct Uniform
	{
		Uniform()
			: type(UniformType::Count)
			, num(0)
			, regIndex(0)
			, regCount(0)
			, texComponent(0)
			, texDimension(0)
			, texFormat(0)
		{
		}

		std::string name;
		UniformType::Enum type;
		uint8_t num;
		uint16_t regIndex;
		uint16_t regCount;
		uint8_t texComponent;
		uint8_t texDimension;
		uint16_t texFormat;
	};

	struct Options
	{
		Options();

		void dump();

		char shaderType;
		std::string platform;
		std::string profile;

		std::string	inputFilePath;
		std::string	outputFilePath;

		std::vector<std::string> includeDirs;
		std::vector<std::string> defines;
		std::vector<std::string> dependencies;

		bool disasm;
		bool raw;
		bool preprocessOnly;
		bool keepComments;
		bool depends;

		bool debugInformation;

		bool avoidFlowControl;
		bool noPreshader;
		bool partialPrecision;
		bool preferFlowControl;
		bool backwardsCompatibility;
		bool warningsAreErrors;
		bool keepIntermediate;

		bool optimize;
		uint32_t optimizationLevel;
	};

	typedef std::vector<Uniform> UniformArray;

	void printCode(const char* _code, int32_t _line = 0, int32_t _start = 0, int32_t _end = INT32_MAX, int32_t _column = -1);
	void strReplace(char* _str, const char* _find, const char* _replace);
	int32_t writef(bx::WriterI* _writer, const char* _format, ...);
	void writeFile(const char* _filePath, const void* _data, int32_t _size);

	bool compileGLSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);
	bool compileHLSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);
	bool compileDxilShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);
	bool compileMetalShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);
	bool compilePSSLShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);
	bool compileSPIRVShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);
	bool compileWgslShader(const Options& _options, uint32_t _version, const std::string& _code, bx::WriterI* _writer, bx::WriterI* _messages);

	const char* getPsslPreamble();

} // namespace bgfx

#endif // SHADERC_H_HEADER_GUARD
