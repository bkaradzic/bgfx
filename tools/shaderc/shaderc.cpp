/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"
#include <bx/commandline.h>
#include <bx/filepath.h>

#define MAX_TAGS 256
extern "C"
{
#include <fpp.h>
} // extern "C"

#define BGFX_CHUNK_MAGIC_CSH BX_MAKEFOURCC('C', 'S', 'H', 0x3)
#define BGFX_CHUNK_MAGIC_FSH BX_MAKEFOURCC('F', 'S', 'H', 0x5)
#define BGFX_CHUNK_MAGIC_VSH BX_MAKEFOURCC('V', 'S', 'H', 0x5)

#define BGFX_SHADERC_VERSION_MAJOR 1
#define BGFX_SHADERC_VERSION_MINOR 12

namespace bgfx
{
	bool g_verbose = false;

	static const char* s_ARB_shader_texture_lod[] =
	{
		"texture2DLod",
		"texture2DArrayLod", // BK - interacts with ARB_texture_array.
		"texture2DProjLod",
		"texture2DGrad",
		"texture2DProjGrad",
		"texture3DLod",
		"texture3DProjLod",
		"texture3DGrad",
		"texture3DProjGrad",
		"textureCubeLod",
		"textureCubeGrad",
		"shadow2DLod",
		"shadow2DProjLod",
		NULL
		// "texture1DLod",
		// "texture1DProjLod",
		// "shadow1DLod",
		// "shadow1DProjLod",
	};

	static const char* s_EXT_shader_texture_lod[] =
	{
		"texture2DLod",
		"texture2DProjLod",
		"textureCubeLod",
		"texture2DGrad",
		"texture2DProjGrad",
		"textureCubeGrad",
		NULL
	};

	static const char* s_EXT_shadow_samplers[] =
	{
		"shadow2D",
		"shadow2DProj",
		"sampler2DShadow",
		NULL
	};

	static const char* s_OES_standard_derivatives[] =
	{
		"dFdx",
		"dFdy",
		"fwidth",
		NULL
	};

	static const char* s_OES_texture_3D[] =
	{
		"texture3D",
		"texture3DProj",
		"texture3DLod",
		"texture3DProjLod",
		NULL
	};

	static const char* s_EXT_gpu_shader4[] =
	{
		"gl_VertexID",
		"gl_InstanceID",
		NULL
	};

	static const char* s_ARB_gpu_shader5[] =
	{
		"bitfieldReverse",
		"floatBitsToInt",
		"floatBitsToUint",
		"intBitsToFloat",
		"uintBitsToFloat",
		NULL
	};

	static const char* s_ARB_shading_language_packing[] =
	{
		"packHalf2x16",
		"unpackHalf2x16",
		NULL
	};

	static const char* s_130[] =
	{
		"uint",
		"uint2",
		"uint3",
		"uint4",
		"isampler3D",
		"usampler3D",
		NULL
	};

	static const char* s_textureArray[] =
	{
		"texture2DArray",
		"texture2DArrayLod",
		"shadow2DArray",
		NULL
	};

	static const char* s_ARB_texture_multisample[] =
	{
		"sampler2DMS",
		"isampler2DMS",
		"usampler2DMS",
		NULL
	};

	static const char* s_texelFetch[] =
	{
		"texelFetch",
		"texelFetchOffset",
		NULL
	};

	const char* s_uniformTypeName[] =
	{
		"int",  "int",
		NULL,   NULL,
		"vec4", "float4",
		"mat3", "float3x3",
		"mat4", "float4x4",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_uniformTypeName) == UniformType::Count*2);


	Options::Options()
		: shaderType(' ')
		, disasm(false)
		, raw(false)
		, preprocessOnly(false)
		, depends(false)
		, debugInformation(false)
		, avoidFlowControl(false)
		, noPreshader(false)
		, partialPrecision(false)
		, preferFlowControl(false)
		, backwardsCompatibility(false)
		, warningsAreErrors(false)
		, optimize(false)
		, optimizationLevel(3)
	{
	}

	void Options::dump()
	{
		BX_TRACE("Options:\n"
			"\t  shaderType: %c\n"
			"\t  platform: %s\n"
			"\t  profile: %s\n"
			"\t  inputFile: %s\n"
			"\t  outputFile: %s\n"
			"\t  disasm: %s\n"
			"\t  raw: %s\n"
			"\t  preprocessOnly: %s\n"
			"\t  depends: %s\n"
			"\t  debugInformation: %s\n"
			"\t  avoidFlowControl: %s\n"
			"\t  noPreshader: %s\n"
			"\t  partialPrecision: %s\n"
			"\t  preferFlowControl: %s\n"
			"\t  backwardsCompatibility: %s\n"
			"\t  warningsAreErrors: %s\n"
			"\t  optimize: %s\n"
			"\t  optimizationLevel: %d\n"

			, shaderType
			, platform.c_str()
			, profile.c_str()
			, inputFilePath.c_str()
			, outputFilePath.c_str()
			, disasm ? "true" : "false"
			, raw ? "true" : "false"
			, preprocessOnly ? "true" : "false"
			, depends ? "true" : "false"
			, debugInformation ? "true" : "false"
			, avoidFlowControl ? "true" : "false"
			, noPreshader ? "true" : "false"
			, partialPrecision ? "true" : "false"
			, preferFlowControl ? "true" : "false"
			, backwardsCompatibility ? "true" : "false"
			, warningsAreErrors ? "true" : "false"
			, optimize ? "true" : "false"
			, optimizationLevel
			);

		for (size_t ii = 0; ii < includeDirs.size(); ++ii)
		{
			BX_TRACE("\t  include :%s\n", includeDirs[ii].c_str());
		}

		for (size_t ii = 0; ii < defines.size(); ++ii)
		{
			BX_TRACE("\t  define :%s\n", defines[ii].c_str());
		}

		for (size_t ii = 0; ii < dependencies.size(); ++ii)
		{
			BX_TRACE("\t  dependency :%s\n", dependencies[ii].c_str());
		}
	}

	const char* interpolationDx11(const char* _glsl)
	{
		if (0 == bx::strCmp(_glsl, "smooth") )
		{
			return "linear";
		}
		else if (0 == bx::strCmp(_glsl, "flat") )
		{
			return "nointerpolation";
		}

		return _glsl; // centroid, noperspective
	}

	const char* getUniformTypeName(UniformType::Enum _enum)
	{
		uint32_t idx = _enum & ~(BGFX_UNIFORM_FRAGMENTBIT|BGFX_UNIFORM_SAMPLERBIT);
		if (idx < UniformType::Count)
		{
			return s_uniformTypeName[idx];
		}

		return "Unknown uniform type?!";
	}

	UniformType::Enum nameToUniformTypeEnum(const char* _name)
	{
		for (uint32_t ii = 0; ii < UniformType::Count*2; ++ii)
		{
			if (NULL != s_uniformTypeName[ii]
			&&  0 == bx::strCmp(_name, s_uniformTypeName[ii]) )
			{
				return UniformType::Enum(ii/2);
			}
		}

		return UniformType::Count;
	}

	int32_t writef(bx::WriterI* _writer, const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);

		char temp[2048];

		char* out = temp;
		int32_t max = sizeof(temp);
		int32_t len = bx::vsnprintf(out, max, _format, argList);
		if (len > max)
		{
			out = (char*)alloca(len);
			len = bx::vsnprintf(out, len, _format, argList);
		}

		len = bx::write(_writer, out, len);

		va_end(argList);

		return len;
	}

	class Bin2cWriter : public bx::FileWriter
	{
	public:
		Bin2cWriter(const char* _name)
			: m_name(_name)
		{
		}

		virtual ~Bin2cWriter()
		{
		}

		virtual void close() override
		{
			generate();
			return bx::FileWriter::close();
		}

		virtual int32_t write(const void* _data, int32_t _size, bx::Error*) override
		{
			const char* data = (const char*)_data;
			m_buffer.insert(m_buffer.end(), data, data+_size);
			return _size;
		}

	private:
		void generate()
		{
#define HEX_DUMP_WIDTH 16
#define HEX_DUMP_SPACE_WIDTH 96
#define HEX_DUMP_FORMAT "%-" BX_STRINGIZE(HEX_DUMP_SPACE_WIDTH) "." BX_STRINGIZE(HEX_DUMP_SPACE_WIDTH) "s"
			const uint8_t* data = &m_buffer[0];
			uint32_t size = (uint32_t)m_buffer.size();

			outf("static const uint8_t %s[%d] =\n{\n", m_name.c_str(), size);

			if (NULL != data)
			{
				char hex[HEX_DUMP_SPACE_WIDTH+1];
				char ascii[HEX_DUMP_WIDTH+1];
				uint32_t hexPos = 0;
				uint32_t asciiPos = 0;
				for (uint32_t ii = 0; ii < size; ++ii)
				{
					bx::snprintf(&hex[hexPos], sizeof(hex)-hexPos, "0x%02x, ", data[asciiPos]);
					hexPos += 6;

					ascii[asciiPos] = isprint(data[asciiPos]) && data[asciiPos] != '\\' ? data[asciiPos] : '.';
					asciiPos++;

					if (HEX_DUMP_WIDTH == asciiPos)
					{
						ascii[asciiPos] = '\0';
						outf("\t" HEX_DUMP_FORMAT "// %s\n", hex, ascii);
						data += asciiPos;
						hexPos = 0;
						asciiPos = 0;
					}
				}

				if (0 != asciiPos)
				{
					ascii[asciiPos] = '\0';
					outf("\t" HEX_DUMP_FORMAT "// %s\n", hex, ascii);
				}
			}

			outf("};\n");
#undef HEX_DUMP_WIDTH
#undef HEX_DUMP_SPACE_WIDTH
#undef HEX_DUMP_FORMAT
		}

		int32_t outf(const char* _format, ...)
		{
			va_list argList;
			va_start(argList, _format);

			char temp[2048];
			char* out = temp;
			int32_t max = sizeof(temp);
			int32_t len = bx::vsnprintf(out, max, _format, argList);
			if (len > max)
			{
				out = (char*)alloca(len);
				len = bx::vsnprintf(out, len, _format, argList);
			}

			bx::Error err;
			int32_t size = bx::FileWriter::write(out, len, &err);

			va_end(argList);

			return size;
		}

		std::string m_filePath;
		std::string m_name;
		typedef std::vector<uint8_t> Buffer;
		Buffer m_buffer;
	};

	struct Varying
	{
		std::string m_precision;
		std::string m_interpolation;
		std::string m_name;
		std::string m_type;
		std::string m_init;
		std::string m_semantics;
	};

	typedef std::unordered_map<std::string, Varying> VaryingMap;

	class File
	{
	public:
		File(const char* _filePath)
			: m_data(NULL)
		{
			bx::FileReader reader;
			if (bx::open(&reader, _filePath) )
			{
				m_size = (uint32_t)bx::getSize(&reader);
				m_data = new char[m_size+1];
				m_size = (uint32_t)bx::read(&reader, m_data, m_size);
				bx::close(&reader);

				if (m_data[0] == '\xef'
				&&  m_data[1] == '\xbb'
				&&  m_data[2] == '\xbf')
				{
					bx::memMove(m_data, &m_data[3], m_size-3);
					m_size -= 3;
				}

				m_data[m_size] = '\0';
			}
		}

		~File()
		{
			delete [] m_data;
		}

		const char* getData() const
		{
			return m_data;
		}

		uint32_t getSize() const
		{
			return m_size;
		}

	private:
		char* m_data;
		uint32_t m_size;
	};

	char* strInsert(char* _str, const char* _insert)
	{
		uint32_t len = bx::strLen(_insert);
		bx::memMove(&_str[len], _str, bx::strLen(_str) );
		bx::memCopy(_str, _insert, len);
		return _str + len;
	}

	void strReplace(char* _str, const char* _find, const char* _replace)
	{
		const int32_t len = bx::strLen(_find);

		char* replace = (char*)alloca(len+1);
		bx::strCopy(replace, len+1, _replace);
		for (int32_t ii = bx::strLen(replace); ii < len; ++ii)
		{
			replace[ii] = ' ';
		}
		replace[len] = '\0';

		BX_CHECK(len >= bx::strLen(_replace), "");
		for (const char* ptr = bx::strFind(_str, _find)
			; NULL != ptr
			; ptr = bx::strFind(ptr + len, _find)
			)
		{
			bx::memCopy(const_cast<char*>(ptr), replace, len);
		}
	}

	void strNormalizeEol(char* _str)
	{
		strReplace(_str, "\r\n", "\n");
		strReplace(_str, "\r",   "\n");
	}

	void printCode(const char* _code, int32_t _line, int32_t _start, int32_t _end, int32_t _column)
	{
		fprintf(stderr, "Code:\n---\n");

		bx::Error err;
		LineReader reader(_code);
		for (int32_t line = 1; err.isOk() && line < _end; ++line)
		{
			char str[4096];
			int32_t len = bx::read(&reader, str, BX_COUNTOF(str), &err);

			if (err.isOk()
			&&  line >= _start)
			{
				std::string strLine(str, len);

				if (_line == line)
				{
					fprintf(stderr, "\n");
					fprintf(stderr, ">>> %3d: %s", line, strLine.c_str() );
					if (-1 != _column)
					{
						fprintf(stderr, ">>> %3d: %*s\n", _column, _column, "^");
					}
					fprintf(stderr, "\n");
				}
				else
				{
					fprintf(stderr, "    %3d: %s", line, strLine.c_str() );
				}
			}
		}

		fprintf(stderr, "---\n");
	}

	void writeFile(const char* _filePath, const void* _data, int32_t _size)
	{
		bx::FileWriter out;
		if (bx::open(&out, _filePath) )
		{
			bx::write(&out, _data, _size);
			bx::close(&out);
		}
	}

	struct Preprocessor
	{
		Preprocessor(const char* _filePath, bool _essl)
			: m_tagptr(m_tags)
			, m_scratchPos(0)
			, m_fgetsPos(0)
		{
			m_tagptr->tag = FPPTAG_USERDATA;
			m_tagptr->data = this;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_DEPENDS;
			m_tagptr->data = (void*)fppDepends;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_INPUT;
			m_tagptr->data = (void*)fppInput;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_OUTPUT;
			m_tagptr->data = (void*)fppOutput;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_ERROR;
			m_tagptr->data = (void*)fppError;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_IGNOREVERSION;
			m_tagptr->data = (void*)0;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_LINE;
			m_tagptr->data = (void*)0;
			m_tagptr++;

			m_tagptr->tag = FPPTAG_INPUT_NAME;
			m_tagptr->data = scratch(_filePath);
			m_tagptr++;

			if (!_essl)
			{
				m_default = "#define lowp\n#define mediump\n#define highp\n";
			}
		}

		void setDefine(const char* _define)
		{
			m_tagptr->tag = FPPTAG_DEFINE;
			m_tagptr->data = scratch(_define);
			m_tagptr++;
		}

		void setDefaultDefine(const char* _name)
		{
			char temp[1024];
			bx::snprintf(temp, BX_COUNTOF(temp)
				, "#ifndef %s\n"
				  "#	define %s 0\n"
				  "#endif // %s\n"
				  "\n"
				, _name
				, _name
				, _name
				);

			m_default += temp;
		}

		void writef(const char* _format, ...)
		{
			va_list argList;
			va_start(argList, _format);
			bx::stringPrintfVargs(m_default, _format, argList);
			va_end(argList);
		}

		void addInclude(const char* _includeDir)
		{
			char* start = scratch(_includeDir);

			for (char* split = const_cast<char*>(bx::strFind(start, ';') )
				; NULL != split
				; split = const_cast<char*>(bx::strFind(start, ';') )
				)
			{
				*split = '\0';
				m_tagptr->tag = FPPTAG_INCLUDE_DIR;
				m_tagptr->data = start;
				m_tagptr++;
				start = split + 1;
			}

			m_tagptr->tag = FPPTAG_INCLUDE_DIR;
			m_tagptr->data = start;
			m_tagptr++;
		}

		void addDependency(const char* _fileName)
		{
			m_depends += " \\\n ";
			m_depends += _fileName;
		}

		bool run(const char* _input)
		{
			m_fgetsPos = 0;

			m_preprocessed.clear();
			m_input = m_default;
			m_input += "\n\n";

			int32_t len = bx::strLen(_input)+1;
			char* temp = new char[len];
			bx::eolLF(temp, len, _input);
			m_input += temp;
			delete [] temp;

			fppTag* tagptr = m_tagptr;

			tagptr->tag = FPPTAG_END;
			tagptr->data = 0;
			tagptr++;

			int result = fppPreProcess(m_tags);

			return 0 == result;
		}

		char* fgets(char* _buffer, int _size)
		{
			int ii = 0;
			for (char ch = m_input[m_fgetsPos]; m_fgetsPos < m_input.size() && ii < _size-1; ch = m_input[++m_fgetsPos])
			{
				_buffer[ii++] = ch;

				if (ch == '\n' || ii == _size)
				{
					_buffer[ii] = '\0';
					m_fgetsPos++;
					return _buffer;
				}
			}

			return NULL;
		}

		static void fppDepends(char* _fileName, void* _userData)
		{
			Preprocessor* thisClass = (Preprocessor*)_userData;
			thisClass->addDependency(_fileName);
		}

		static char* fppInput(char* _buffer, int _size, void* _userData)
		{
			Preprocessor* thisClass = (Preprocessor*)_userData;
			return thisClass->fgets(_buffer, _size);
		}

		static void fppOutput(int _ch, void* _userData)
		{
			Preprocessor* thisClass = (Preprocessor*)_userData;
			thisClass->m_preprocessed += char(_ch);
		}

		static void fppError(void* /*_userData*/, char* _format, va_list _vargs)
		{
			vfprintf(stderr, _format, _vargs);
		}

		char* scratch(const char* _str)
		{
			char* result = &m_scratch[m_scratchPos];
			bx::strCopy(result, uint32_t(sizeof(m_scratch)-m_scratchPos), _str);
			m_scratchPos += (uint32_t)bx::strLen(_str)+1;

			return result;
		}

		fppTag m_tags[MAX_TAGS];
		fppTag* m_tagptr;

		std::string m_depends;
		std::string m_default;
		std::string m_input;
		std::string m_preprocessed;
		char m_scratch[16<<10];
		uint32_t m_scratchPos;
		uint32_t m_fgetsPos;
	};

	typedef std::vector<std::string> InOut;

	uint32_t parseInOut(InOut& _inout, const char* _str, const char* _eol)
	{
		uint32_t hash = 0;
		_str = bx::strws(_str);

		if (_str < _eol)
		{
			const char* delim;
			do
			{
				delim = strpbrk(_str, " ,");
				if (NULL != delim)
				{
					delim = delim > _eol ? _eol : delim;
					std::string token;
					token.assign(_str, delim-_str);
					_inout.push_back(token);
					_str = bx::strws(delim + 1);
				}
			}
			while (delim < _eol && _str < _eol && NULL != delim);

			std::sort(_inout.begin(), _inout.end() );

			bx::HashMurmur2A murmur;
			murmur.begin();
			for (InOut::const_iterator it = _inout.begin(), itEnd = _inout.end(); it != itEnd; ++it)
			{
				murmur.add(it->c_str(), (uint32_t)it->size() );
			}
			hash = murmur.end();
		}

		return hash;
	}

	void addFragData(Preprocessor& _preprocessor, char* _data, uint32_t _idx, bool _comma)
	{
		char find[32];
		bx::snprintf(find, sizeof(find), "gl_FragData[%d]", _idx);

		char replace[32];
		bx::snprintf(replace, sizeof(replace), "bgfx_FragData%d", _idx);

		strReplace(_data, find, replace);

		_preprocessor.writef(
			" \\\n\t%sout vec4 bgfx_FragData%d : SV_TARGET%d"
			, _comma ? ", " : "  "
			, _idx
			, _idx
			);
	}

	void voidFragData(char* _data, uint32_t _idx)
	{
		char find[32];
		bx::snprintf(find, sizeof(find), "gl_FragData[%d]", _idx);

		strReplace(_data, find, "bgfx_VoidFrag");
	}

	const char* baseName(const char* _filePath)
	{
		bx::FilePath fp(_filePath);
		char tmp[bx::kMaxFilePath];
		bx::strCopy(tmp, BX_COUNTOF(tmp), fp.getFileName() );
		const char* base = bx::strFind(_filePath, tmp);
		return base;
	}

	// c - compute
	// d - domain
	// f - fragment
	// g - geometry
	// h - hull
	// v - vertex
	//
	// OpenGL #version Features Direct3D Features Shader Model
	// 2.1    120      vf       9.0      vf       2.0
	// 3.0    130
	// 3.1    140
	// 3.2    150      vgf
	// 3.3    330               10.0     vgf      4.0
	// 4.0    400      vhdgf
	// 4.1    410
	// 4.2    420               11.0     vhdgf+c  5.0
	// 4.3    430      vhdgf+c
	// 4.4    440

	void help(const char* _error = NULL)
	{
		if (NULL != _error)
		{
			fprintf(stderr, "Error:\n%s\n\n", _error);
		}

		fprintf(stderr
			, "shaderc, bgfx shader compiler tool, version %d.%d.%d.\n"
			  "Copyright 2011-2018 Branimir Karadzic. All rights reserved.\n"
			  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
			, BGFX_SHADERC_VERSION_MAJOR
			, BGFX_SHADERC_VERSION_MINOR
			, BGFX_API_VERSION
			);

		fprintf(stderr
			, "Usage: shaderc -f <in> -o <out> --type <v/f> --platform <platform>\n"

			  "\n"
			  "Options:\n"
			  "  -h, --help                    Help.\n"
			  "  -v, --version                 Version information only.\n"
			  "  -f <file path>                Input file path.\n"
			  "  -i <include path>             Include path (for multiple paths use use -i multiple times).\n"
			  "  -o <file path>                Output file path.\n"
			  "      --bin2c <file path>       Generate C header file.\n"
			  "      --depends                 Generate makefile style depends file.\n"
			  "      --platform <platform>     Target platform.\n"
			  "           android\n"
			  "           asm.js\n"
			  "           ios\n"
			  "           linux\n"
			  "           nacl\n"
			  "           osx\n"
			  "           windows\n"
			  "      --preprocess              Preprocess only.\n"
			  "      --define <defines>        Add defines to preprocessor (semicolon separated).\n"
			  "      --raw                     Do not process shader. No preprocessor, and no glsl-optimizer (GLSL only).\n"
			  "      --type <type>             Shader type (vertex, fragment)\n"
			  "      --varyingdef <file path>  Path to varying.def.sc file.\n"
			  "      --verbose                 Verbose.\n"

			  "\n"
			  "Options (DX9 and DX11 only):\n"

			  "\n"
			  "      --debug                   Debug information.\n"
			  "      --disasm                  Disassemble compiled shader.\n"
			  "  -p, --profile <profile>       Shader model (f.e. ps_3_0).\n"
			  "  -O <level>                    Optimization level (0, 1, 2, 3).\n"
			  "      --Werror                  Treat warnings as errors.\n"

			  "\n"
			  "For additional information, see https://github.com/bkaradzic/bgfx\n"
			);
	}

	bool compileShader(const char* _varying, const char* _comment, char* _shader, uint32_t _shaderLen, Options& _options, bx::FileWriter* _writer)
	{
		uint32_t glsl  = 0;
		uint32_t essl  = 0;
		uint32_t hlsl  = 0;
		uint32_t d3d   = 11;
		uint32_t metal = 0;
		uint32_t pssl  = 0;
		uint32_t spirv = 0;
		const char* profile = _options.profile.c_str();
		if ('\0' != profile[0])
		{
			if (0 == bx::strCmp(&profile[1], "s_4_0_level", 11) )
			{
				hlsl = 2;
			}
			else if (0 == bx::strCmp(&profile[1], "s_3", 3) )
			{
				hlsl = 3;
				d3d  = 9;
			}
			else if (0 == bx::strCmp(&profile[1], "s_4", 3) )
			{
				hlsl = 4;
			}
			else if (0 == bx::strCmp(&profile[1], "s_5", 3) )
			{
				hlsl = 5;
			}
			else if (0 == bx::strCmp(profile, "metal") )
			{
				metal = 1;
			}
			else if (0 == bx::strCmp(profile, "pssl") )
			{
				pssl = 1;
			}
			else if (0 == bx::strCmp(profile, "spirv") )
			{
				spirv = 1;
			}
			else
			{
				glsl = atoi(profile);
			}
		}
		else
		{
			essl = 2;
		}

		Preprocessor preprocessor(_options.inputFilePath.c_str(), 0 != essl);

		for (size_t ii = 0; ii < _options.includeDirs.size(); ++ii)
		{
			preprocessor.addInclude(_options.includeDirs[ii].c_str() );
		}

		for (size_t ii = 0; ii < _options.defines.size(); ++ii)
		{
			preprocessor.setDefine(_options.defines[ii].c_str() );
		}

		for (size_t ii = 0; ii < _options.dependencies.size(); ++ii)
		{
			preprocessor.addDependency(_options.dependencies[ii].c_str() );
		}

		preprocessor.setDefaultDefine("BX_PLATFORM_ANDROID");
		preprocessor.setDefaultDefine("BX_PLATFORM_EMSCRIPTEN");
		preprocessor.setDefaultDefine("BX_PLATFORM_IOS");
		preprocessor.setDefaultDefine("BX_PLATFORM_LINUX");
		preprocessor.setDefaultDefine("BX_PLATFORM_OSX");
		preprocessor.setDefaultDefine("BX_PLATFORM_PS4");
		preprocessor.setDefaultDefine("BX_PLATFORM_WINDOWS");
		preprocessor.setDefaultDefine("BX_PLATFORM_XBOXONE");

//		preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_ESSL");
		preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_GLSL");
		preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_HLSL");
		preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_METAL");
		preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_PSSL");
		preprocessor.setDefaultDefine("BGFX_SHADER_LANGUAGE_SPIRV");

		preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_COMPUTE");
		preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_FRAGMENT");
		preprocessor.setDefaultDefine("BGFX_SHADER_TYPE_VERTEX");

		char glslDefine[128];
		bx::snprintf(glslDefine, BX_COUNTOF(glslDefine)
				, "BGFX_SHADER_LANGUAGE_GLSL=%d"
				, essl ? 1 : glsl
				);

		const char* platform = _options.platform.c_str();

		if (0 == bx::strCmpI(platform, "android") )
		{
			preprocessor.setDefine("BX_PLATFORM_ANDROID=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strCmpI(platform, "asm.js") )
		{
			preprocessor.setDefine("BX_PLATFORM_EMSCRIPTEN=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strCmpI(platform, "ios") )
		{
			preprocessor.setDefine("BX_PLATFORM_IOS=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strCmpI(platform, "linux") )
		{
			preprocessor.setDefine("BX_PLATFORM_LINUX=1");
			if (0 != spirv)
			{
				preprocessor.setDefine("BGFX_SHADER_LANGUAGE_SPIRV=1");
			}
			else
			{
				preprocessor.setDefine(glslDefine);
			}
		}
		else if (0 == bx::strCmpI(platform, "osx") )
		{
			preprocessor.setDefine("BX_PLATFORM_OSX=1");
			preprocessor.setDefine(glslDefine);
			char temp[256];
			bx::snprintf(temp, sizeof(temp), "BGFX_SHADER_LANGUAGE_METAL=%d", metal);
			preprocessor.setDefine(temp);
		}
		else if (0 == bx::strCmpI(platform, "windows") )
		{
			preprocessor.setDefine("BX_PLATFORM_WINDOWS=1");
			char temp[256];
			bx::snprintf(temp, sizeof(temp), "BGFX_SHADER_LANGUAGE_HLSL=%d", hlsl);
			preprocessor.setDefine(temp);
		}
		else if (0 == bx::strCmpI(platform, "orbis") )
		{
			preprocessor.setDefine("BX_PLATFORM_PS4=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_PSSL=1");
			preprocessor.setDefine("lit=lit_reserved");
		}

		preprocessor.setDefine("M_PI=3.1415926535897932384626433832795");

		switch (_options.shaderType)
		{
		case 'c':
			preprocessor.setDefine("BGFX_SHADER_TYPE_COMPUTE=1");
			break;

		case 'f':
			preprocessor.setDefine("BGFX_SHADER_TYPE_FRAGMENT=1");
			break;

		case 'v':
			preprocessor.setDefine("BGFX_SHADER_TYPE_VERTEX=1");
			break;

		default:
			fprintf(stderr, "Unknown type: %c?!", _options.shaderType);
			return false;
		}

		bool compiled = false;

		VaryingMap varyingMap;
		const char* parse = _varying;

		bool usesInterpolationQualifiers = false;

		while (NULL !=  parse
		&&     '\0' != *parse)
		{
			parse = bx::strws(parse);
			const char* eol = bx::strFind(parse, ';');
			if (NULL == eol)
			{
				eol = bx::streol(parse);
			}

			if (NULL != eol)
			{
				const char* precision = NULL;
				const char* interpolation = NULL;
				const char* typen = parse;

				if (0 == bx::strCmp(typen, "lowp", 4)
				||  0 == bx::strCmp(typen, "mediump", 7)
				||  0 == bx::strCmp(typen, "highp", 5) )
				{
					precision = typen;
					typen = parse = bx::strws(bx::strSkipWord(parse) );
				}

				if (0 == bx::strCmp(typen, "flat", 4)
				||  0 == bx::strCmp(typen, "smooth", 6)
				||  0 == bx::strCmp(typen, "noperspective", 13)
				||  0 == bx::strCmp(typen, "centroid", 8) )
				{
					interpolation = typen;
					typen = parse = bx::strws(bx::strSkipWord(parse) );
					usesInterpolationQualifiers = true;
				}

				const char* name      = parse = bx::strws(bx::strSkipWord(parse) );
				const char* column    = parse = bx::strws(bx::strSkipWord(parse) );
				const char* semantics = parse = bx::strws( (*parse == ':' ? ++parse : parse) );
				const char* assign    = parse = bx::strws(bx::strSkipWord(parse) );
				const char* init      = parse = bx::strws( (*parse == '=' ? ++parse : parse) );

				if (typen < eol
				&&  name < eol
				&&  column < eol
				&&  ':' == *column
				&&  semantics < eol)
				{
					Varying var;
					if (NULL != precision)
					{
						var.m_precision.assign(precision, bx::strSkipWord(precision)-precision);
					}

					if (NULL != interpolation)
					{
						var.m_interpolation.assign(interpolation, bx::strSkipWord(interpolation)-interpolation);
					}

					var.m_type.assign(typen, bx::strSkipWord(typen)-typen);
					var.m_name.assign(name, bx::strSkipWord(name)-name);
					var.m_semantics.assign(semantics, bx::strSkipWord(semantics)-semantics);

					if (d3d == 9
					&&  var.m_semantics == "BITANGENT")
					{
						var.m_semantics = "BINORMAL";
					}

					if (assign < eol
					&&  '=' == *assign
					&&  init < eol)
					{
						var.m_init.assign(init, eol-init);
					}

					varyingMap.insert(std::make_pair(var.m_name, var) );
				}

				parse = bx::strws(bx::strnl(eol) );
			}
		}

		bool raw = _options.raw;

		InOut shaderInputs;
		InOut shaderOutputs;
		uint32_t inputHash = 0;
		uint32_t outputHash = 0;

		char* data;
		char* input;
		{
			data = _shader;
			uint32_t size = _shaderLen;

			const size_t padding = 16384;

			if (!raw)
			{
				// To avoid commented code being recognized as used feature,
				// first preprocess pass is used to strip all comments before
				// substituting code.
				preprocessor.run(data);
				delete [] data;

				size = (uint32_t)preprocessor.m_preprocessed.size();
				data = new char[size+padding+1];
				bx::memCopy(data, preprocessor.m_preprocessed.c_str(), size);
				bx::memSet(&data[size], 0, padding+1);
			}

			strNormalizeEol(data);

			input = const_cast<char*>(bx::strws(data) );
			while (input[0] == '$')
			{
				const char* str = bx::strws(input+1);
				const char* eol = bx::streol(str);
				const char* nl  = bx::strnl(eol);
				input = const_cast<char*>(nl);

				if (0 == bx::strCmp(str, "input", 5) )
				{
					str += 5;
					const char* comment = bx::strFind(str, "//");
					eol = NULL != comment && comment < eol ? comment : eol;
					inputHash = parseInOut(shaderInputs, str, eol);
				}
				else if (0 == bx::strCmp(str, "output", 6) )
				{
					str += 6;
					const char* comment = bx::strFind(str, "//");
					eol = NULL != comment && comment < eol ? comment : eol;
					outputHash = parseInOut(shaderOutputs, str, eol);
				}
				else if (0 == bx::strCmp(str, "raw", 3) )
				{
					raw = true;
					str += 3;
				}

				input = const_cast<char*>(bx::strws(input) );
			}
		}

		if (raw)
		{
			if ('f' == _options.shaderType)
			{
				bx::write(_writer, BGFX_CHUNK_MAGIC_FSH);
				bx::write(_writer, inputHash);
			}
			else if ('v' == _options.shaderType)
			{
				bx::write(_writer, BGFX_CHUNK_MAGIC_VSH);
				bx::write(_writer, outputHash);
			}
			else
			{
				bx::write(_writer, BGFX_CHUNK_MAGIC_CSH);
				bx::write(_writer, outputHash);
			}

			if (0 != glsl)
			{
				bx::write(_writer, uint16_t(0) );

				uint32_t shaderSize = (uint32_t)bx::strLen(input);
				bx::write(_writer, shaderSize);
				bx::write(_writer, input, shaderSize);
				bx::write(_writer, uint8_t(0) );

				compiled = true;
			}
			else if (0 != pssl)
			{
				compiled = compilePSSLShader(_options, 0, input, _writer);
			}
			else
			{
				compiled = compileHLSLShader(_options, d3d, input, _writer);
			}
		}
		else if ('c' == _options.shaderType) // Compute
		{
			char* entry = const_cast<char*>(bx::strFind(input, "void main()") );
			if (NULL == entry)
			{
				fprintf(stderr, "Shader entry point 'void main()' is not found.\n");
			}
			else
			{
				if (0 != glsl
				||  0 != essl
				||  0 != metal)
				{
				}
				else
				{
					if (0 != pssl)
					{
						preprocessor.writef(getPsslPreamble() );
					}

					preprocessor.writef(
						"#define lowp\n"
						"#define mediump\n"
						"#define highp\n"
						"#define ivec2 int2\n"
						"#define ivec3 int3\n"
						"#define ivec4 int4\n"
						"#define uvec2 uint2\n"
						"#define uvec3 uint3\n"
						"#define uvec4 uint4\n"
						"#define vec2 float2\n"
						"#define vec3 float3\n"
						"#define vec4 float4\n"
						"#define mat2 float2x2\n"
						"#define mat3 float3x3\n"
						"#define mat4 float4x4\n"
						);

					entry[4] = '_';

					preprocessor.writef("#define void_main()");
					preprocessor.writef(" \\\n\tvoid main(");

					uint32_t arg = 0;

					const bool hasLocalInvocationID    = NULL != bx::strFind(input, "gl_LocalInvocationID");
					const bool hasLocalInvocationIndex = NULL != bx::strFind(input, "gl_LocalInvocationIndex");
					const bool hasGlobalInvocationID   = NULL != bx::strFind(input, "gl_GlobalInvocationID");
					const bool hasWorkGroupID          = NULL != bx::strFind(input, "gl_WorkGroupID");

					if (hasLocalInvocationID)
					{
						preprocessor.writef(
							" \\\n\t%sint3 gl_LocalInvocationID : SV_GroupThreadID"
							, arg++ > 0 ? ", " : "  "
							);
					}

					if (hasLocalInvocationIndex)
					{
						preprocessor.writef(
							" \\\n\t%sint gl_LocalInvocationIndex : SV_GroupIndex"
							, arg++ > 0 ? ", " : "  "
							);
					}

					if (hasGlobalInvocationID)
					{
						preprocessor.writef(
							" \\\n\t%sint3 gl_GlobalInvocationID : SV_DispatchThreadID"
							, arg++ > 0 ? ", " : "  "
							);
					}

					if (hasWorkGroupID)
					{
						preprocessor.writef(
							" \\\n\t%sint3 gl_WorkGroupID : SV_GroupID"
							, arg++ > 0 ? ", " : "  "
							);
					}

					preprocessor.writef(
						" \\\n\t)\n"
						);
				}

				if (preprocessor.run(input) )
				{
					if (_options.preprocessOnly)
					{
						bx::write(_writer, preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );

						return true;
					}

					{
						std::string code;

						bx::write(_writer, BGFX_CHUNK_MAGIC_CSH);
						bx::write(_writer, outputHash);

						if (0 != glsl
						||  0 != essl)
						{
							if (essl)
							{
								bx::stringPrintf(code, "#version 310 es\n");
							}
							else
							{
								bx::stringPrintf(code, "#version %d\n", glsl == 0 ? 430 : glsl);
							}

#if 1
							code += preprocessor.m_preprocessed;

							bx::write(_writer, uint16_t(0) );

							uint32_t shaderSize = (uint32_t)code.size();
							bx::write(_writer, shaderSize);
							bx::write(_writer, code.c_str(), shaderSize);
							bx::write(_writer, uint8_t(0) );

							compiled = true;
#else
							code += _comment;
							code += preprocessor.m_preprocessed;

							compiled = compileGLSLShader(cmdLine, essl, code, writer);
#endif // 0
						}
						else
						{
							code += _comment;
							code += preprocessor.m_preprocessed;

							if (0 != spirv)
							{
								compiled = compileSPIRVShader(_options, 0, code, _writer);
							}
							else if (0 != pssl)
							{
								compiled = compilePSSLShader(_options, 0, code, _writer);
							}
							else
							{
								compiled = compileHLSLShader(_options, d3d, code, _writer);
							}
						}
					}

					if (compiled)
					{
						if (_options.depends)
						{
							std::string ofp = _options.outputFilePath;
							ofp += ".d";
							bx::FileWriter writer;
							if (bx::open(&writer, ofp.c_str() ) )
							{
								writef(&writer, "%s : %s\n", _options.outputFilePath.c_str(), preprocessor.m_depends.c_str() );
								bx::close(&writer);
							}
						}
					}
				}
			}
		}
		else // Vertex/Fragment
		{
			char* entry = const_cast<char*>(bx::strFind(input, "void main()") );
			if (NULL == entry)
			{
				fprintf(stderr, "Shader entry point 'void main()' is not found.\n");
			}
			else
			{
				if (0 != glsl
				||  0 != essl
				||  0 != metal)
				{
					if (0 == essl)
					{
						// bgfx shadow2D/Proj behave like EXT_shadow_samplers
						// not as GLSL language 1.2 specs shadow2D/Proj.
						preprocessor.writef(
							"#define shadow2D(_sampler, _coord) bgfxShadow2D(_sampler, _coord).x\n"
							"#define shadow2DProj(_sampler, _coord) bgfxShadow2DProj(_sampler, _coord).x\n"
							);
					}

					for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
					{
						VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
						if (varyingIt != varyingMap.end() )
						{
							const Varying& var = varyingIt->second;
							const char* name = var.m_name.c_str();

							if (0 == bx::strCmp(name, "a_", 2)
							||  0 == bx::strCmp(name, "i_", 2) )
							{
								preprocessor.writef("attribute %s %s %s %s;\n"
										, var.m_precision.c_str()
										, var.m_interpolation.c_str()
										, var.m_type.c_str()
										, name
										);
							}
							else
							{
								preprocessor.writef("%s varying %s %s %s;\n"
										, var.m_interpolation.c_str()
										, var.m_precision.c_str()
										, var.m_type.c_str()
										, name
										);
							}
						}
					}

					for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
					{
						VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
						if (varyingIt != varyingMap.end() )
						{
							const Varying& var = varyingIt->second;
							preprocessor.writef("%s varying %s %s;\n"
								, var.m_interpolation.c_str()
								, var.m_type.c_str()
								, var.m_name.c_str()
								);
						}
					}
				}
				else
				{
					if (0 != pssl)
					{
						preprocessor.writef(getPsslPreamble() );
					}

					preprocessor.writef(
						"#define lowp\n"
						"#define mediump\n"
						"#define highp\n"
						"#define ivec2 int2\n"
						"#define ivec3 int3\n"
						"#define ivec4 int4\n"
						"#define uvec2 uint2\n"
						"#define uvec3 uint3\n"
						"#define uvec4 uint4\n"
						"#define vec2 float2\n"
						"#define vec3 float3\n"
						"#define vec4 float4\n"
						"#define mat2 float2x2\n"
						"#define mat3 float3x3\n"
						"#define mat4 float4x4\n"
						);

					if (hlsl != 0
					&&  hlsl < 4)
					{
						preprocessor.writef(
							"#define centroid\n"
							"#define flat\n"
							"#define noperspective\n"
							"#define smooth\n"
							);
					}

					entry[4] = '_';

					if ('f' == _options.shaderType)
					{
						const char* insert = bx::strFind(entry, "{");
						if (NULL != insert)
						{
							insert = strInsert(const_cast<char*>(insert+1), "\nvec4 bgfx_VoidFrag = vec4_splat(0.0);\n");
						}

						const bool hasFragColor   = NULL != bx::strFind(input, "gl_FragColor");
						const bool hasFragCoord   = NULL != bx::strFind(input, "gl_FragCoord") || hlsl > 3 || hlsl == 2;
						const bool hasFragDepth   = NULL != bx::strFind(input, "gl_FragDepth");
						const bool hasFrontFacing = NULL != bx::strFind(input, "gl_FrontFacing");
						const bool hasPrimitiveId = NULL != bx::strFind(input, "gl_PrimitiveID");

						bool hasFragData[8] = {};
						uint32_t numFragData = 0;
						for (uint32_t ii = 0; ii < BX_COUNTOF(hasFragData); ++ii)
						{
							char temp[32];
							bx::snprintf(temp, BX_COUNTOF(temp), "gl_FragData[%d]", ii);
							hasFragData[ii] = NULL != bx::strFind(input, temp);
							numFragData += hasFragData[ii];
						}

						if (0 == numFragData)
						{
							// GL errors when both gl_FragColor and gl_FragData is used.
							// This will trigger the same error with HLSL compiler too.
							preprocessor.writef("#define gl_FragColor bgfx_FragData0\n");

							// If it has gl_FragData or gl_FragColor, color target at
							// index 0 exists, otherwise shader is not modifying color
							// targets.
							hasFragData[0] |= hasFragColor || d3d < 11;

							if (NULL != insert
							&&  d3d < 11
							&&  !hasFragColor)
							{
								insert = strInsert(const_cast<char*>(insert+1), "\ngl_FragColor = bgfx_VoidFrag;\n");
							}
						}

						preprocessor.writef("#define void_main()");
						preprocessor.writef(" \\\n\tvoid main(");

						uint32_t arg = 0;

						if (hasFragCoord)
						{
							preprocessor.writef(" \\\n\tvec4 gl_FragCoord : SV_POSITION");
							++arg;
						}

						for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef(" \\\n\t%s%s %s %s : %s"
									, arg++ > 0 ? ", " : "  "
									, interpolationDx11(var.m_interpolation.c_str() )
									, var.m_type.c_str()
									, var.m_name.c_str()
									, var.m_semantics.c_str()
									);
							}
						}

						const uint32_t maxRT = d3d > 9 ? BX_COUNTOF(hasFragData) : 4;

						for (uint32_t ii = 0; ii < BX_COUNTOF(hasFragData); ++ii)
						{
							if (ii < maxRT)
							{
								if (hasFragData[ii])
								{
									addFragData(preprocessor, input, ii, arg++ > 0);
								}
							}
							else
							{
								voidFragData(input, ii);
							}
						}

						if (hasFragDepth)
						{
							preprocessor.writef(
								" \\\n\t%sout float gl_FragDepth : SV_DEPTH"
								, arg++ > 0 ? ", " : "  "
								);
						}

						if (hasFrontFacing
						&&  hlsl >= 3)
						{
							preprocessor.writef(
								" \\\n\t%sfloat __vface : VFACE"
								, arg++ > 0 ? ", " : "  "
								);
						}

						if (hasPrimitiveId)
						{
							if (d3d > 9)
							{
								preprocessor.writef(
									" \\\n\t%suint gl_PrimitiveID : SV_PrimitiveID"
									, arg++ > 0 ? ", " : "  "
									);
							}
							else
							{
								fprintf(stderr, "gl_PrimitiveID builtin is not supported by this D3D9 HLSL.\n");
								return false;
							}
						}

						preprocessor.writef(
							" \\\n\t)\n"
							);

						if (hasFrontFacing)
						{
							if (hlsl >= 3)
							{
								preprocessor.writef(
									"#define gl_FrontFacing (__vface <= 0.0)\n"
									);
							}
							else
							{
								preprocessor.writef(
									"#define gl_FrontFacing false\n"
									);
							}
						}
					}
					else if ('v' == _options.shaderType)
					{
						const bool hasVertexId    = NULL != bx::strFind(input, "gl_VertexID");
						const bool hasInstanceId  = NULL != bx::strFind(input, "gl_InstanceID");

						const char* brace = bx::strFind(entry, "{");
						if (NULL != brace)
						{
							const char* end = bx::strmb(brace, '{', '}');
							if (NULL != end)
							{
								strInsert(const_cast<char*>(end), "__RETURN__;\n");
							}
						}

						preprocessor.writef(
							"struct Output\n"
							"{\n"
							"\tvec4 gl_Position : SV_POSITION;\n"
							"#define gl_Position _varying_.gl_Position\n"
							);
						for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef(
									  "\t%s %s %s : %s;\n"
									, interpolationDx11(var.m_interpolation.c_str() )
									, var.m_type.c_str()
									, var.m_name.c_str()
									, var.m_semantics.c_str()
									);
								preprocessor.writef(
									  "#define %s _varying_.%s\n"
									, var.m_name.c_str()
									, var.m_name.c_str()
									);
							}
						}
						preprocessor.writef(
							"};\n"
							);

						preprocessor.writef("#define void_main() \\\n");
						preprocessor.writef("Output main(");
						uint32_t arg = 0;
						for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef(
									" \\\n\t%s%s %s : %s"
									, arg++ > 0 ? ", " : ""
									, var.m_type.c_str()
									, var.m_name.c_str()
									, var.m_semantics.c_str()
									);
							}
						}

						if (hasVertexId)
						{
							if (d3d > 9)
							{
								preprocessor.writef(
									" \\\n\t%suint gl_VertexID : SV_VertexID"
									, arg++ > 0 ? ", " : "  "
									);
							}
							else
							{
								fprintf(stderr, "gl_VertexID builtin is not supported by this D3D9 HLSL.\n");
								return false;
							}
						}

						if (hasInstanceId)
						{
							if (d3d > 9)
							{
								preprocessor.writef(
									" \\\n\t%suint gl_InstanceID : SV_InstanceID"
									, arg++ > 0 ? ", " : "  "
									);
							}
							else
							{
								fprintf(stderr, "gl_InstanceID builtin is not supported by this D3D9 HLSL.\n");
								return false;
							}
						}

						preprocessor.writef(
							") \\\n"
							"{ \\\n"
							"\tOutput _varying_;"
							);

						for (InOut::const_iterator it = shaderOutputs.begin(), itEnd = shaderOutputs.end(); it != itEnd; ++it)
						{
							VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
							if (varyingIt != varyingMap.end() )
							{
								const Varying& var = varyingIt->second;
								preprocessor.writef(" \\\n\t%s", var.m_name.c_str() );
								if (!var.m_init.empty() )
								{
									preprocessor.writef(" = %s", var.m_init.c_str() );
								}
								preprocessor.writef(";");
							}
						}

						preprocessor.writef(
							"\n#define __RETURN__ \\\n"
							"\t} \\\n"
							);

						if (hlsl != 0
						&&  hlsl <= 3)
						{
//								preprocessor.writef(
//									"\tgl_Position.xy += u_viewTexel.xy * gl_Position.w; \\\n"
//									);
						}

						if (0 != spirv)
						{
							preprocessor.writef(
								"\tgl_Position.y = -gl_Position.y; \\\n"
								);
						}

						preprocessor.writef(
							"\treturn _varying_"
							);
					}
				}

				if (preprocessor.run(input) )
				{
					//BX_TRACE("Input file: %s", filePath);
					//BX_TRACE("Output file: %s", outFilePath);

					if (_options.preprocessOnly)
					{
						if (0 != glsl)
						{
							if (essl != 0)
							{
								writef(_writer
									, "#ifdef GL_ES\n"
										"precision highp float;\n"
										"#endif // GL_ES\n\n"
									);
							}
						}
						bx::write(_writer, preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );

						return true;
					}

					{
						std::string code;

						if ('f' == _options.shaderType)
						{
							bx::write(_writer, BGFX_CHUNK_MAGIC_FSH);
							bx::write(_writer, inputHash);
						}
						else if ('v' == _options.shaderType)
						{
							bx::write(_writer, BGFX_CHUNK_MAGIC_VSH);
							bx::write(_writer, outputHash);
						}
						else
						{
							bx::write(_writer, BGFX_CHUNK_MAGIC_CSH);
							bx::write(_writer, outputHash);
						}

						if (0 != glsl
						||  0 != essl
						||  0 != metal)
						{
							if (NULL != bx::strFind(preprocessor.m_preprocessed.c_str(), "layout(std430") )
							{
								glsl = 430;
							}

							if (glsl < 400)
							{
								const bool usesTextureLod   = false
									|| !!bx::findIdentifierMatch(input, s_ARB_shader_texture_lod)
									|| !!bx::findIdentifierMatch(input, s_EXT_shader_texture_lod)
									;
								const bool usesInstanceID   = !!bx::strFind(input, "gl_InstanceID");
								const bool usesGpuShader4   = !!bx::findIdentifierMatch(input, s_EXT_gpu_shader4);
								const bool usesGpuShader5   = !!bx::findIdentifierMatch(input, s_ARB_gpu_shader5);
								const bool usesTexelFetch   = !!bx::findIdentifierMatch(input, s_texelFetch);
								const bool usesTextureMS    = !!bx::findIdentifierMatch(input, s_ARB_texture_multisample);
								const bool usesTextureArray = !!bx::findIdentifierMatch(input, s_textureArray);
								const bool usesPacking      = !!bx::findIdentifierMatch(input, s_ARB_shading_language_packing);

								if (0 == essl)
								{
									const bool need130 = 120 == glsl && (false
										|| bx::findIdentifierMatch(input, s_130)
										|| usesInterpolationQualifiers
										|| usesTexelFetch
										);

									if (0 != metal)
									{
										bx::stringPrintf(code, "#version 120\n");
									}
									else
									{
										bx::stringPrintf(code, "#version %s\n", need130 ? "130" : _options.profile.c_str());
										glsl = 130;
									}

									if (need130)
									{
										bx::stringPrintf(code, "#define varying %s\n"
											, 'f' == _options.shaderType ? "in" : "out"
											);
									}

									if (usesInstanceID)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_draw_instanced : enable\n"
											);
									}

									if (usesGpuShader4)
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_gpu_shader4 : enable\n"
											);
									}

									if (usesGpuShader5)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_gpu_shader5 : enable\n"
											);
									}

									if (usesPacking)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_shading_language_packing : enable\n"
											);
									}

									bool ARB_shader_texture_lod = false;
									bool EXT_shader_texture_lod = false;

									if (usesTextureLod)
									{
										if ('f' == _options.shaderType)
										{
											ARB_shader_texture_lod = true;
											bx::stringPrintf(code
												, "#extension GL_ARB_shader_texture_lod : enable\n"
												);
										}
										else
										{
											EXT_shader_texture_lod = true;
											bx::stringPrintf(code
												, "#extension GL_EXT_shader_texture_lod : enable\n"
												);
										}
									}

									if (usesTextureMS)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_texture_multisample : enable\n"
											);
									}

									if (usesTextureArray)
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_texture_array : enable\n"
											);
									}

									if (130 > glsl)
									{
										bx::stringPrintf(code,
											"#define ivec2 vec2\n"
											"#define ivec3 vec3\n"
											"#define ivec4 vec4\n"
											);
									}

									if (ARB_shader_texture_lod)
									{
										bx::stringPrintf(code,
											"#define texture2DProjLod  texture2DProjLodARB\n"
											"#define texture2DGrad     texture2DGradARB\n"
											"#define texture2DProjGrad texture2DProjGradARB\n"
											"#define textureCubeGrad   textureCubeGradARB\n"
											);
									}
									else if (EXT_shader_texture_lod)
									{
										bx::stringPrintf(code,
											"#define texture2DProjLod  texture2DProjLodEXT\n"
											"#define texture2DGrad     texture2DGradEXT\n"
											"#define texture2DProjGrad texture2DProjGradEXT\n"
											"#define textureCubeGrad   textureCubeGradEXT\n"
											);
									}

									if (need130)
									{
										bx::stringPrintf(code
											, "#define bgfxShadow2D(_sampler, _coord)     vec4_splat(texture(_sampler, _coord))\n"
											  "#define bgfxShadow2DProj(_sampler, _coord) vec4_splat(textureProj(_sampler, _coord))\n"
											);
									}
									else
									{
										bx::stringPrintf(code
											, "#define bgfxShadow2D     shadow2D\n"
												"#define bgfxShadow2DProj shadow2DProj\n"
											);
									}
								}
								else
								{
									if (usesInterpolationQualifiers)
									{
										bx::stringPrintf(code, "#version 300 es\n");
										bx::stringPrintf(code, "#define attribute in\n");
										bx::stringPrintf(code, "#define varying %s\n"
											, 'f' == _options.shaderType ? "in" : "out"
											);
									}
									else if (essl == 2)
									{
										code +=
											"mat2 transpose(mat2 _mtx)\n"
											"{\n"
											"	vec2 v0 = _mtx[0];\n"
											"	vec2 v1 = _mtx[1];\n"
											"\n"
											"	return mat2(\n"
											"		  vec2(v0.x, v1.x)\n"
											"		, vec2(v0.y, v1.y)\n"
											"		);\n"
											"}\n"
											"\n"
											"mat3 transpose(mat3 _mtx)\n"
											"{\n"
											"	vec3 v0 = _mtx[0];\n"
											"	vec3 v1 = _mtx[1];\n"
											"	vec3 v2 = _mtx[2];\n"
											"\n"
											"	return mat3(\n"
											"		  vec3(v0.x, v1.x, v2.x)\n"
											"		, vec3(v0.y, v1.y, v2.y)\n"
											"		, vec3(v0.z, v1.z, v2.z)\n"
											"		);\n"
											"}\n"
											"\n"
											"mat4 transpose(mat4 _mtx)\n"
											"{\n"
											"	vec4 v0 = _mtx[0];\n"
											"	vec4 v1 = _mtx[1];\n"
											"	vec4 v2 = _mtx[2];\n"
											"	vec4 v3 = _mtx[3];\n"
											"\n"
											"	return mat4(\n"
											"		  vec4(v0.x, v1.x, v2.x, v3.x)\n"
											"		, vec4(v0.y, v1.y, v2.y, v3.y)\n"
											"		, vec4(v0.z, v1.z, v2.z, v3.z)\n"
											"		, vec4(v0.w, v1.w, v2.w, v3.w)\n"
											"		);\n"
											"}\n"
											;
									}

									// Pretend that all extensions are available.
									// This will be stripped later.
									if (usesTextureLod)
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_shader_texture_lod : enable\n"
											  "#define texture2DLod      texture2DLodEXT\n"
											  "#define texture2DGrad     texture2DGradEXT\n"
											  "#define texture2DProjLod  texture2DProjLodEXT\n"
											  "#define texture2DProjGrad texture2DProjGradEXT\n"
											  "#define textureCubeLod    textureCubeLodEXT\n"
											  "#define textureCubeGrad   textureCubeGradEXT\n"
											);
									}

									if (NULL != bx::findIdentifierMatch(input, s_OES_standard_derivatives) )
									{
										bx::stringPrintf(code, "#extension GL_OES_standard_derivatives : enable\n");
									}

									if (NULL != bx::findIdentifierMatch(input, s_OES_texture_3D) )
									{
										bx::stringPrintf(code, "#extension GL_OES_texture_3D : enable\n");
									}

									if (NULL != bx::findIdentifierMatch(input, s_EXT_shadow_samplers) )
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_shadow_samplers : enable\n"
											  "#define shadow2D shadow2DEXT\n"
											  "#define shadow2DProj shadow2DProjEXT\n"
											);
									}

									if (usesGpuShader5)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_gpu_shader5 : enable\n"
											);
									}

									if (usesPacking)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_shading_language_packing : enable\n"
											);
									}

									if (NULL != bx::findIdentifierMatch(input, "gl_FragDepth") )
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_frag_depth : enable\n"
											  "#define gl_FragDepth gl_FragDepthEXT\n"
											);
									}

									if (usesTextureArray)
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_texture_array : enable\n"
											);
									}

									bx::stringPrintf(code
										, "#define ivec2 vec2\n"
										  "#define ivec3 vec3\n"
										  "#define ivec4 vec4\n"
										);
								}
							}
							else
							{
								bx::stringPrintf(code, "#version %d\n", glsl);

								bx::stringPrintf(code
									, "#define texture2DLod      textureLod\n"
									  "#define texture2DGrad     textureGrad\n"
									  "#define texture2DProjLod  textureProjLod\n"
									  "#define texture2DProjGrad textureProjGrad\n"
									  "#define textureCubeLod    textureLod\n"
									  "#define textureCubeGrad   textureGrad\n"
									  "#define texture3D         texture\n"
									);

								bx::stringPrintf(code, "#define attribute in\n");
								bx::stringPrintf(code, "#define varying %s\n"
									, 'f' == _options.shaderType ? "in" : "out"
									);

								bx::stringPrintf(code
									, "#define bgfxShadow2D(_sampler, _coord)     vec4_splat(texture(_sampler, _coord))\n"
									  "#define bgfxShadow2DProj(_sampler, _coord) vec4_splat(textureProj(_sampler, _coord))\n"
									);
							}

							if (glsl > 400)
							{
								code += preprocessor.m_preprocessed;

								bx::write(_writer, uint16_t(0) );

								uint32_t shaderSize = (uint32_t)code.size();
								bx::write(_writer, shaderSize);
								bx::write(_writer, code.c_str(), shaderSize);
								bx::write(_writer, uint8_t(0) );

								compiled = true;
							}
							else
							{
								code += _comment;
								code += preprocessor.m_preprocessed;

								compiled = compileGLSLShader(_options, metal ? BX_MAKEFOURCC('M', 'T', 'L', 0) : essl, code, _writer);
							}
						}
						else
						{
							code += _comment;
							code += preprocessor.m_preprocessed;

							if (0 != spirv)
							{
								compiled = compileSPIRVShader(_options, 0, code, _writer);
							}
							else if (0 != pssl)
							{
								compiled = compilePSSLShader(_options, 0, code, _writer);
							}
							else
							{
								compiled = compileHLSLShader(_options, d3d, code, _writer);
							}
						}
					}

					if (compiled)
					{
						if (_options.depends)
						{
							std::string ofp = _options.outputFilePath + ".d";
							bx::FileWriter writer;
							if (bx::open(&writer, ofp.c_str() ) )
							{
								writef(&writer, "%s : %s\n", _options.outputFilePath.c_str(), preprocessor.m_depends.c_str() );
								bx::close(&writer);
							}
						}
					}
				}
			}
		}

		delete [] data;

		return compiled;
	}

	int compileShader(int _argc, const char* _argv[])
	{
		bx::CommandLine cmdLine(_argc, _argv);

		if (cmdLine.hasArg('v', "version") )
		{
			fprintf(stderr
				, "shaderc, bgfx shader compiler tool, version %d.%d.%d.\n"
				, BGFX_SHADERC_VERSION_MAJOR
				, BGFX_SHADERC_VERSION_MINOR
				, BGFX_API_VERSION
				);
			return bx::kExitSuccess;
		}

		if (cmdLine.hasArg('h', "help") )
		{
			help();
			return bx::kExitFailure;
		}

		g_verbose = cmdLine.hasArg("verbose");

		const char* filePath = cmdLine.findOption('f');
		if (NULL == filePath)
		{
			help("Shader file name must be specified.");
			return bx::kExitFailure;
		}

		const char* outFilePath = cmdLine.findOption('o');
		if (NULL == outFilePath)
		{
			help("Output file name must be specified.");
			return bx::kExitFailure;
		}

		const char* type = cmdLine.findOption('\0', "type");
		if (NULL == type)
		{
			help("Must specify shader type.");
			return bx::kExitFailure;
		}

		Options options;
		options.inputFilePath = filePath;
		options.outputFilePath = outFilePath;
		options.shaderType = bx::toLower(type[0]);

		options.disasm = cmdLine.hasArg('\0', "disasm");

		const char* platform = cmdLine.findOption('\0', "platform");
		if (NULL == platform)
		{
			platform = "";
		}

		options.platform = platform;

		options.raw = cmdLine.hasArg('\0', "raw");

		const char* profile = cmdLine.findOption('p', "profile");

		if ( NULL != profile)
		{
			options.profile = profile;
		}

		{	// hlsl only
			options.debugInformation = cmdLine.hasArg('\0', "debug");
			options.avoidFlowControl = cmdLine.hasArg('\0', "avoid-flow-control");
			options.noPreshader = cmdLine.hasArg('\0', "no-preshader");
			options.partialPrecision = cmdLine.hasArg('\0', "partial-precision");
			options.preferFlowControl = cmdLine.hasArg('\0', "prefer-flow-control");
			options.backwardsCompatibility = cmdLine.hasArg('\0', "backwards-compatibility");
			options.warningsAreErrors = cmdLine.hasArg('\0', "Werror");

			uint32_t optimization = 3;
			if (cmdLine.hasArg(optimization, 'O') )
			{
				options.optimize = true;
				options.optimizationLevel = optimization;
			}
		}

		const char* bin2c = NULL;
		if (cmdLine.hasArg("bin2c") )
		{
			bin2c = cmdLine.findOption("bin2c");
			if (NULL == bin2c)
			{
				bin2c = baseName(outFilePath);
				uint32_t len = (uint32_t)bx::strLen(bin2c);
				char* temp = (char*)alloca(len+1);
				for (char *out = temp; *bin2c != '\0';)
				{
					char ch = *bin2c++;
					if (isalnum(ch) )
					{
						*out++ = ch;
					}
					else
					{
						*out++ = '_';
					}
				}
				temp[len] = '\0';

				bin2c = temp;
			}
		}

		options.depends = cmdLine.hasArg("depends");
		options.preprocessOnly = cmdLine.hasArg("preprocess");
		const char* includeDir = cmdLine.findOption('i');

		BX_TRACE("depends: %d", options.depends);
		BX_TRACE("preprocessOnly: %d", options.preprocessOnly);
		BX_TRACE("includeDir: %s", includeDir);

		for (int ii = 1; NULL != includeDir; ++ii)
		{
			options.includeDirs.push_back(includeDir);
			includeDir = cmdLine.findOption(ii, 'i');
		}

		std::string dir;
		{
			const char* base = baseName(filePath);

			if (base != filePath)
			{
				dir.assign(filePath, base-filePath);
				options.includeDirs.push_back(dir.c_str());
			}
		}

		const char* defines = cmdLine.findOption("define");
		while (NULL != defines
		&&    '\0'  != *defines)
		{
			defines = bx::strws(defines);
			const char* eol = bx::strFind(defines, ';');
			if (NULL == eol)
			{
				eol = defines + bx::strLen(defines);
			}
			std::string define(defines, eol);
			options.defines.push_back(define.c_str() );
			defines = ';' == *eol ? eol+1 : eol;
		}

		std::string commandLineComment = "// shaderc command line:\n//";
		for (int32_t ii = 0, num = cmdLine.getNum(); ii < num; ++ii)
		{
			commandLineComment += " ";
			commandLineComment += cmdLine.get(ii);
		}
		commandLineComment += "\n\n";

		bool compiled = false;

		bx::FileReader reader;
		if (!bx::open(&reader, filePath) )
		{
			fprintf(stderr, "Unable to open file '%s'.\n", filePath);
		}
		else
		{
			std::string defaultVarying = dir + "varying.def.sc";
			const char* varyingdef = cmdLine.findOption("varyingdef", defaultVarying.c_str() );
			File attribdef(varyingdef);
			const char* parse = attribdef.getData();
			if (NULL != parse
			&&  *parse != '\0')
			{
				options.dependencies.push_back(varyingdef);
			}
			else
			{
				fprintf(stderr, "ERROR: Failed to parse varying def file: \"%s\" No input/output semantics will be generated in the code!\n", varyingdef);
			}

			const size_t padding    = 16384;
			uint32_t size = (uint32_t)bx::getSize(&reader);
			char* data = new char[size+padding+1];
			size = (uint32_t)bx::read(&reader, data, size);

			if (data[0] == '\xef'
			&&  data[1] == '\xbb'
			&&  data[2] == '\xbf')
			{
				bx::memMove(data, &data[3], size-3);
				size -= 3;
			}

			// Compiler generates "error X3000: syntax error: unexpected end of file"
			// if input doesn't have empty line at EOF.
			data[size] = '\n';
			bx::memSet(&data[size+1], 0, padding);
			bx::close(&reader);

			bx::FileWriter* writer = NULL;

			if (NULL != bin2c)
			{
				writer = new Bin2cWriter(bin2c);
			}
			else
			{
				writer = new bx::FileWriter;
			}

			if (!bx::open(writer, outFilePath) )
			{
				fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
				return bx::kExitFailure;
			}

			compiled = compileShader(attribdef.getData(), commandLineComment.c_str(), data, size, options, writer);

			bx::close(writer);
			delete writer;
		}

		if (compiled)
		{
			return bx::kExitSuccess;
		}

		remove(outFilePath);

		fprintf(stderr, "Failed to build shader.\n");
		return bx::kExitFailure;
	}

} // namespace bgfx

int main(int _argc, const char* _argv[])
{
	return bgfx::compileShader(_argc, _argv);
}
