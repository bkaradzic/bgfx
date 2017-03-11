/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "shaderc.h"
#include <bx/commandline.h>

#define MAX_TAGS 256
extern "C"
{
#include <fpp.h>
} // extern "C"

namespace bgfx
{
	bool g_verbose = false;

	#define BGFX_CHUNK_MAGIC_CSH BX_MAKEFOURCC('C', 'S', 'H', 0x2)
	#define BGFX_CHUNK_MAGIC_FSH BX_MAKEFOURCC('F', 'S', 'H', 0x4)
	#define BGFX_CHUNK_MAGIC_VSH BX_MAKEFOURCC('V', 'S', 'H', 0x4)

	static const char* s_ARB_shader_texture_lod[] =
	{
		"texture2DLod",
		"texture2DArrayLod", // BK - interacts with ARB_texture_array.
		"texture2DProjLod",
		"texture3DLod",
		"texture3DProjLod",
		"textureCubeLod",
		"shadow2DLod",
		"shadow2DProjLod",
		NULL
		// "texture1DLod",
		// "texture1DProjLod",
		// "shadow1DLod",
		// "shadow1DProjLod",
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

	const char* interpolationDx11(const char* _glsl)
	{
		if (0 == strcmp(_glsl, "smooth") )
		{
			return "linear";
		}
		else if (0 == strcmp(_glsl, "flat") )
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
			&&  0 == strcmp(_name, s_uniformTypeName[ii]) )
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

	class Bin2cWriter : public bx::CrtFileWriter
	{
	public:
		Bin2cWriter(const char* _name)
			: m_name(_name)
		{
		}

		virtual ~Bin2cWriter()
		{
		}

		virtual void close() BX_OVERRIDE
		{
			generate();
			return bx::CrtFileWriter::close();
		}

		virtual int32_t write(const void* _data, int32_t _size, bx::Error*) BX_OVERRIDE
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
			int32_t size = bx::CrtFileWriter::write(out, len, &err);

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
			bx::CrtFileReader reader;
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
					memmove(m_data, &m_data[3], m_size-3);
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
		size_t len = strlen(_insert);
		memmove(&_str[len], _str, strlen(_str) );
		memcpy(_str, _insert, len);
		return _str + len;
	}

	void strReplace(char* _str, const char* _find, const char* _replace)
	{
		const size_t len = strlen(_find);

		char* replace = (char*)alloca(len+1);
		bx::strlcpy(replace, _replace, len+1);
		for (size_t ii = strlen(replace); ii < len; ++ii)
		{
			replace[ii] = ' ';
		}
		replace[len] = '\0';

		BX_CHECK(len >= strlen(_replace), "");
		for (char* ptr = strstr(_str, _find); NULL != ptr; ptr = strstr(ptr + len, _find) )
		{
			memcpy(ptr, replace, len);
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

		LineReader lr(_code);
		for (int32_t line = 1; !lr.isEof() && line < _end; ++line)
		{
			if (line >= _start)
			{
				if (_line == line)
				{
					fprintf(stderr, "\n");
					fprintf(stderr, ">>> %3d: %s", line, lr.getLine().c_str() );
					if (-1 != _column)
					{
						fprintf(stderr, ">>> %3d: %*s\n", _column, _column, "^");
					}
					fprintf(stderr, "\n");
				}
				else
				{
					fprintf(stderr, "    %3d: %s", line, lr.getLine().c_str() );
				}
			}
			else
			{
				lr.skipLine();
			}
		}

		fprintf(stderr, "---\n");
	}

	void writeFile(const char* _filePath, const void* _data, int32_t _size)
	{
		bx::CrtFileWriter out;
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

			for (char* split = strchr(start, ';'); NULL != split; split = strchr(start, ';') )
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

			size_t len = strlen(_input)+1;
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
			strcpy(result, _str);
			m_scratchPos += (uint32_t)strlen(_str)+1;

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
		bx::snprintf(replace, sizeof(replace), "gl_FragData_%d_", _idx);

		strReplace(_data, find, replace);

		_preprocessor.writef(
			" \\\n\t%sout vec4 gl_FragData_%d_ : SV_TARGET%d"
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
			, "shaderc, bgfx shader compiler tool\n"
			  "Copyright 2011-2017 Branimir Karadzic. All rights reserved.\n"
			  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
			);

		fprintf(stderr
			, "Usage: shaderc -f <in> -o <out> --type <v/f> --platform <platform>\n"

			  "\n"
			  "Options:\n"
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

	int compileShader(int _argc, const char* _argv[])
	{
		bx::CommandLine cmdLine(_argc, _argv);

		if (cmdLine.hasArg('h', "help") )
		{
			help();
			return EXIT_FAILURE;
		}

		g_verbose = cmdLine.hasArg("verbose");

		const char* filePath = cmdLine.findOption('f');
		if (NULL == filePath)
		{
			help("Shader file name must be specified.");
			return EXIT_FAILURE;
		}

		const char* outFilePath = cmdLine.findOption('o');
		if (NULL == outFilePath)
		{
			help("Output file name must be specified.");
			return EXIT_FAILURE;
		}

		const char* type = cmdLine.findOption('\0', "type");
		if (NULL == type)
		{
			help("Must specify shader type.");
			return EXIT_FAILURE;
		}

		const char* platform = cmdLine.findOption('\0', "platform");
		if (NULL == platform)
		{
			platform = "";
		}

		bool raw = cmdLine.hasArg('\0', "raw");

		uint32_t glsl  = 0;
		uint32_t essl  = 0;
		uint32_t hlsl  = 0;
		uint32_t d3d   = 11;
		uint32_t metal = 0;
		uint32_t pssl  = 0;
		uint32_t spirv = 0;
		const char* profile = cmdLine.findOption('p', "profile");
		if (NULL != profile)
		{
			if (0 == strncmp(&profile[1], "s_4_0_level", 11) )
			{
				hlsl = 2;
			}
			else if (0 == strncmp(&profile[1], "s_3", 3) )
			{
				hlsl = 3;
				d3d  = 9;
			}
			else if (0 == strncmp(&profile[1], "s_4", 3) )
			{
				hlsl = 4;
			}
			else if (0 == strncmp(&profile[1], "s_5", 3) )
			{
				hlsl = 5;
			}
			else if (0 == strcmp(profile, "metal") )
			{
				metal = 1;
			}
			else if (0 == strcmp(profile, "pssl") )
			{
				pssl = 1;
			}
			else if (0 == strcmp(profile, "spirv") )
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

		const char* bin2c = NULL;
		if (cmdLine.hasArg("bin2c") )
		{
			bin2c = cmdLine.findOption("bin2c");
			if (NULL == bin2c)
			{
				bin2c = bx::baseName(outFilePath);
				uint32_t len = (uint32_t)strlen(bin2c);
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

		bool depends = cmdLine.hasArg("depends");
		bool preprocessOnly = cmdLine.hasArg("preprocess");
		const char* includeDir = cmdLine.findOption('i');

		BX_TRACE("depends: %d", depends);
		BX_TRACE("preprocessOnly: %d", preprocessOnly);
		BX_TRACE("includeDir: %s", includeDir);

		Preprocessor preprocessor(filePath, 0 != essl);

		for (int ii = 1; NULL != includeDir; ++ii)
		{
			preprocessor.addInclude(includeDir);
			includeDir = cmdLine.findOption(ii, 'i');
		}

		std::string dir;
		{
			const char* base = bx::baseName(filePath);

			if (base != filePath)
			{
				dir.assign(filePath, base-filePath);
				preprocessor.addInclude(dir.c_str() );
			}
		}

		const char* defines = cmdLine.findOption("define");
		while (NULL != defines
		&&    '\0'  != *defines)
		{
			defines = bx::strws(defines);
			const char* eol = strchr(defines, ';');
			if (NULL == eol)
			{
				eol = defines + strlen(defines);
			}
			std::string define(defines, eol);
			preprocessor.setDefine(define.c_str() );
			defines = ';' == *eol ? eol+1 : eol;
		}

		preprocessor.setDefaultDefine("BX_PLATFORM_ANDROID");
		preprocessor.setDefaultDefine("BX_PLATFORM_EMSCRIPTEN");
		preprocessor.setDefaultDefine("BX_PLATFORM_IOS");
		preprocessor.setDefaultDefine("BX_PLATFORM_LINUX");
		preprocessor.setDefaultDefine("BX_PLATFORM_NACL");
		preprocessor.setDefaultDefine("BX_PLATFORM_OSX");
		preprocessor.setDefaultDefine("BX_PLATFORM_PS4");
		preprocessor.setDefaultDefine("BX_PLATFORM_WINDOWS");
		preprocessor.setDefaultDefine("BX_PLATFORM_XBOX360");
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

		if (0 == bx::strincmp(platform, "android") )
		{
			preprocessor.setDefine("BX_PLATFORM_ANDROID=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strincmp(platform, "asm.js") )
		{
			preprocessor.setDefine("BX_PLATFORM_EMSCRIPTEN=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strincmp(platform, "ios") )
		{
			preprocessor.setDefine("BX_PLATFORM_IOS=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strincmp(platform, "linux") )
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
		else if (0 == bx::strincmp(platform, "nacl") )
		{
			preprocessor.setDefine("BX_PLATFORM_NACL=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_GLSL=1");
		}
		else if (0 == bx::strincmp(platform, "osx") )
		{
			preprocessor.setDefine("BX_PLATFORM_OSX=1");
			preprocessor.setDefine(glslDefine);
			char temp[256];
			bx::snprintf(temp, sizeof(temp), "BGFX_SHADER_LANGUAGE_METAL=%d", metal);
			preprocessor.setDefine(temp);
		}
		else if (0 == bx::strincmp(platform, "windows") )
		{
			preprocessor.setDefine("BX_PLATFORM_WINDOWS=1");
			char temp[256];
			bx::snprintf(temp, sizeof(temp), "BGFX_SHADER_LANGUAGE_HLSL=%d", hlsl);
			preprocessor.setDefine(temp);
		}
		else if (0 == bx::strincmp(platform, "xbox360") )
		{
			preprocessor.setDefine("BX_PLATFORM_XBOX360=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_HLSL=3");
		}
		else if (0 == bx::strincmp(platform, "orbis") )
		{
			preprocessor.setDefine("BX_PLATFORM_PS4=1");
			preprocessor.setDefine("BGFX_SHADER_LANGUAGE_PSSL=1");
			preprocessor.setDefine("lit=lit_reserved");
		}

		preprocessor.setDefine("M_PI=3.1415926535897932384626433832795");

		char shaderType = bx::toLower(type[0]);
		switch (shaderType)
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
			fprintf(stderr, "Unknown type: %s?!", type);
			return EXIT_FAILURE;
		}

		bool compiled = false;

		bx::CrtFileReader reader;
		if (!bx::open(&reader, filePath) )
		{
			fprintf(stderr, "Unable to open file '%s'.\n", filePath);
		}
		else
		{
			VaryingMap varyingMap;

			std::string defaultVarying = dir + "varying.def.sc";
			const char* varyingdef = cmdLine.findOption("varyingdef", defaultVarying.c_str() );
			File attribdef(varyingdef);
			const char* parse = attribdef.getData();
			if (NULL != parse
			&&  *parse != '\0')
			{
				preprocessor.addDependency(varyingdef);
			}
			else
			{
				fprintf(stderr, "ERROR: Failed to parse varying def file: \"%s\" No input/output semantics will be generated in the code!\n", varyingdef);
			}

			while (NULL != parse
			   &&  *parse != '\0')
			{
				parse = bx::strws(parse);
				const char* eol = strchr(parse, ';');
				if (NULL == eol)
				{
					eol = bx::streol(parse);
				}

				if (NULL != eol)
				{
					const char* precision = NULL;
					const char* interpolation = NULL;
					const char* typen = parse;

					if (0 == strncmp(typen, "lowp", 4)
					||  0 == strncmp(typen, "mediump", 7)
					||  0 == strncmp(typen, "highp", 5) )
					{
						precision = typen;
						typen = parse = bx::strws(bx::strword(parse) );
					}

					if (0 == strncmp(typen, "flat", 4)
					||  0 == strncmp(typen, "smooth", 6)
					||  0 == strncmp(typen, "noperspective", 13)
					||  0 == strncmp(typen, "centroid", 8) )
					{
						interpolation = typen;
						typen = parse = bx::strws(bx::strword(parse) );
					}

					const char* name      = parse = bx::strws(bx::strword(parse) );
					const char* column    = parse = bx::strws(bx::strword(parse) );
					const char* semantics = parse = bx::strws( (*parse == ':' ? ++parse : parse) );
					const char* assign    = parse = bx::strws(bx::strword(parse) );
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
							var.m_precision.assign(precision, bx::strword(precision)-precision);
						}

						if (NULL != interpolation)
						{
							var.m_interpolation.assign(interpolation, bx::strword(interpolation)-interpolation);
						}

						var.m_type.assign(typen, bx::strword(typen)-typen);
						var.m_name.assign(name, bx::strword(name)-name);
						var.m_semantics.assign(semantics, bx::strword(semantics)-semantics);

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

			InOut shaderInputs;
			InOut shaderOutputs;
			uint32_t inputHash = 0;
			uint32_t outputHash = 0;

			char* data;
			char* input;
			{
				const size_t padding = 4096;
				uint32_t size = (uint32_t)bx::getSize(&reader);
				data = new char[size+padding+1];
				size = (uint32_t)bx::read(&reader, data, size);

				if (data[0] == '\xef'
				&&  data[1] == '\xbb'
				&&  data[2] == '\xbf')
				{
					memmove(data, &data[3], size-3);
					size -= 3;
				}

				// Compiler generates "error X3000: syntax error: unexpected end of file"
				// if input doesn't have empty line at EOF.
				data[size] = '\n';
				memset(&data[size+1], 0, padding);
				bx::close(&reader);

				if (!raw)
				{
					// To avoid commented code being recognized as used feature,
					// first preprocess pass is used to strip all comments before
					// substituting code.
					preprocessor.run(data);
					delete [] data;

					size = (uint32_t)preprocessor.m_preprocessed.size();
					data = new char[size+padding+1];
					memcpy(data, preprocessor.m_preprocessed.c_str(), size);
					memset(&data[size], 0, padding+1);
				}

				strNormalizeEol(data);

				input = const_cast<char*>(bx::strws(data) );
				while (input[0] == '$')
				{
					const char* str = bx::strws(input+1);
					const char* eol = bx::streol(str);
					const char* nl  = bx::strnl(eol);
					input = const_cast<char*>(nl);

					if (0 == strncmp(str, "input", 5) )
					{
						str += 5;
						const char* comment = strstr(str, "//");
						eol = NULL != comment && comment < eol ? comment : eol;
						inputHash = parseInOut(shaderInputs, str, eol);
					}
					else if (0 == strncmp(str, "output", 6) )
					{
						str += 6;
						const char* comment = strstr(str, "//");
						eol = NULL != comment && comment < eol ? comment : eol;
						outputHash = parseInOut(shaderOutputs, str, eol);
					}
					else if (0 == strncmp(str, "raw", 3) )
					{
						raw = true;
						str += 3;
					}

					input = const_cast<char*>(bx::strws(input) );
				}
			}

			if (raw)
			{
				bx::CrtFileWriter* writer = NULL;

				if (NULL != bin2c)
				{
					writer = new Bin2cWriter(bin2c);
				}
				else
				{
					writer = new bx::CrtFileWriter;
				}

				if (!bx::open(writer, outFilePath) )
				{
					fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
					return EXIT_FAILURE;
				}

				if ('f' == shaderType)
				{
					bx::write(writer, BGFX_CHUNK_MAGIC_FSH);
					bx::write(writer, inputHash);
				}
				else if ('v' == shaderType)
				{
					bx::write(writer, BGFX_CHUNK_MAGIC_VSH);
					bx::write(writer, outputHash);
				}
				else
				{
					bx::write(writer, BGFX_CHUNK_MAGIC_CSH);
					bx::write(writer, outputHash);
				}

				if (0 != glsl)
				{
					bx::write(writer, uint16_t(0) );

					uint32_t shaderSize = (uint32_t)strlen(input);
					bx::write(writer, shaderSize);
					bx::write(writer, input, shaderSize);
					bx::write(writer, uint8_t(0) );

					compiled = true;
				}
				else if (0 != pssl)
				{
					compiled = compilePSSLShader(cmdLine, 0, input, writer);
				}
				else
				{
					compiled = compileHLSLShader(cmdLine, d3d, input, writer);
				}

				bx::close(writer);
				delete writer;
			}
			else if ('c' == shaderType) // Compute
			{
				char* entry = strstr(input, "void main()");
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

						const bool hasLocalInvocationID    = NULL != strstr(input, "gl_LocalInvocationID");
						const bool hasLocalInvocationIndex = NULL != strstr(input, "gl_LocalInvocationIndex");
						const bool hasGlobalInvocationID   = NULL != strstr(input, "gl_GlobalInvocationID");
						const bool hasWorkGroupID          = NULL != strstr(input, "gl_WorkGroupID");

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
						BX_TRACE("Input file: %s", filePath);
						BX_TRACE("Output file: %s", outFilePath);

						if (preprocessOnly)
						{
							bx::CrtFileWriter writer;

							if (!bx::open(&writer, outFilePath) )
							{
								fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
								return EXIT_FAILURE;
							}

							bx::write(&writer, preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );
							bx::close(&writer);

							return EXIT_SUCCESS;
						}

						{
							bx::CrtFileWriter* writer = NULL;

							if (NULL != bin2c)
							{
								writer = new Bin2cWriter(bin2c);
							}
							else
							{
								writer = new bx::CrtFileWriter;
							}

							if (!bx::open(writer, outFilePath) )
							{
								fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
								return EXIT_FAILURE;
							}

							bx::write(writer, BGFX_CHUNK_MAGIC_CSH);
							bx::write(writer, outputHash);

							if (0 != glsl
							||  0 != essl)
							{
								std::string code;

								if (essl)
								{
									bx::stringPrintf(code, "#version 310 es\n");
								}
								else
								{
									bx::stringPrintf(code, "#version %d\n", glsl == 0 ? 430 : glsl);
								}

								code += preprocessor.m_preprocessed;
	#if 1
								bx::write(writer, uint16_t(0) );

								uint32_t shaderSize = (uint32_t)code.size();
								bx::write(writer, shaderSize);
								bx::write(writer, code.c_str(), shaderSize);
								bx::write(writer, uint8_t(0) );

								compiled = true;
	#else
								compiled = compileGLSLShader(cmdLine, essl, code, writer);
	#endif // 0
							}
							else if (0 != spirv)
							{
								compiled = compileSPIRVShader(cmdLine, 0, preprocessor.m_preprocessed, writer);
							}
							else if (0 != pssl)
							{
								compiled = compilePSSLShader(cmdLine, 0, preprocessor.m_preprocessed, writer);
							}
							else
							{
								compiled = compileHLSLShader(cmdLine, d3d, preprocessor.m_preprocessed, writer);
							}

							bx::close(writer);
							delete writer;
						}

						if (compiled)
						{
							if (depends)
							{
								std::string ofp = outFilePath;
								ofp += ".d";
								bx::CrtFileWriter writer;
								if (bx::open(&writer, ofp.c_str() ) )
								{
									writef(&writer, "%s : %s\n", outFilePath, preprocessor.m_depends.c_str() );
									bx::close(&writer);
								}
							}
						}
					}
				}
			}
			else // Vertex/Fragment
			{
				char* entry = strstr(input, "void main()");
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

								if (0 == strncmp(name, "a_", 2)
								||  0 == strncmp(name, "i_", 2) )
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

						if ('f' == shaderType)
						{
							const char* insert = strstr(entry, "{");
							if (NULL != insert)
							{
								insert = strInsert(const_cast<char*>(insert+1), "\nvec4 bgfx_VoidFrag = vec4_splat(0.0);\n");
							}

							const bool hasFragColor   = NULL != strstr(input, "gl_FragColor");
							const bool hasFragCoord   = NULL != strstr(input, "gl_FragCoord") || hlsl > 3 || hlsl == 2;
							const bool hasFragDepth   = NULL != strstr(input, "gl_FragDepth");
							const bool hasFrontFacing = NULL != strstr(input, "gl_FrontFacing");
							const bool hasPrimitiveId = NULL != strstr(input, "gl_PrimitiveID");

							bool hasFragData[8] = {};
							uint32_t numFragData = 0;
							for (uint32_t ii = 0; ii < BX_COUNTOF(hasFragData); ++ii)
							{
								char temp[32];
								bx::snprintf(temp, BX_COUNTOF(temp), "gl_FragData[%d]", ii);
								hasFragData[ii] = NULL != strstr(input, temp);
								numFragData += hasFragData[ii];
							}

							if (0 == numFragData)
							{
								// GL errors when both gl_FragColor and gl_FragData is used.
								// This will trigger the same error with HLSL compiler too.
								preprocessor.writef("#define gl_FragColor gl_FragData_0_\n");

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
									fprintf(stderr, "PrimitiveID builtin is not supported by this D3D9 HLSL.\n");
									return EXIT_FAILURE;
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
						else if ('v' == shaderType)
						{
							const char* brace = strstr(entry, "{");
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
									preprocessor.writef("\t%s %s : %s;\n", var.m_type.c_str(), var.m_name.c_str(), var.m_semantics.c_str() );
									preprocessor.writef("#define %s _varying_.%s\n", var.m_name.c_str(), var.m_name.c_str() );
								}
							}
							preprocessor.writef(
								"};\n"
								);

							preprocessor.writef("#define void_main() \\\n");
							preprocessor.writef("Output main(");
							bool first = true;
							for (InOut::const_iterator it = shaderInputs.begin(), itEnd = shaderInputs.end(); it != itEnd; ++it)
							{
								VaryingMap::const_iterator varyingIt = varyingMap.find(*it);
								if (varyingIt != varyingMap.end() )
								{
									const Varying& var = varyingIt->second;
									preprocessor.writef("%s%s %s : %s\\\n", first ? "" : "\t, ", var.m_type.c_str(), var.m_name.c_str(), var.m_semantics.c_str() );
									first = false;
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

							preprocessor.writef(
								"\treturn _varying_"
								);
						}
					}

					if (preprocessor.run(input) )
					{
						BX_TRACE("Input file: %s", filePath);
						BX_TRACE("Output file: %s", outFilePath);

						if (preprocessOnly)
						{
							bx::CrtFileWriter writer;

							if (!bx::open(&writer, outFilePath) )
							{
								fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
								return EXIT_FAILURE;
							}

							if (0 != glsl)
							{
								if (NULL == profile)
								{
									writef(&writer
										, "#ifdef GL_ES\n"
										  "precision highp float;\n"
										  "#endif // GL_ES\n\n"
										);
								}
							}
							bx::write(&writer, preprocessor.m_preprocessed.c_str(), (int32_t)preprocessor.m_preprocessed.size() );
							bx::close(&writer);

							return EXIT_SUCCESS;
						}

						{
							bx::CrtFileWriter* writer = NULL;

							if (NULL != bin2c)
							{
								writer = new Bin2cWriter(bin2c);
							}
							else
							{
								writer = new bx::CrtFileWriter;
							}

							if (!bx::open(writer, outFilePath) )
							{
								fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
								return EXIT_FAILURE;
							}

							if ('f' == shaderType)
							{
								bx::write(writer, BGFX_CHUNK_MAGIC_FSH);
								bx::write(writer, inputHash);
							}
							else if ('v' == shaderType)
							{
								bx::write(writer, BGFX_CHUNK_MAGIC_VSH);
								bx::write(writer, outputHash);
							}
							else
							{
								bx::write(writer, BGFX_CHUNK_MAGIC_CSH);
								bx::write(writer, outputHash);
							}

							if (0 != glsl
							||  0 != essl
							||  0 != metal)
							{
								std::string code;

								const bool usesGpuShader5   = !!bx::findIdentifierMatch(input, s_ARB_gpu_shader5);
								const bool usesTexelFetch   = !!bx::findIdentifierMatch(input, s_texelFetch);
								const bool usesTextureLod   = !!bx::findIdentifierMatch(input, s_ARB_shader_texture_lod /*EXT_shader_texture_lod*/);
								const bool usesTextureMS    = !!bx::findIdentifierMatch(input, s_ARB_texture_multisample);
								const bool usesTextureArray = !!bx::findIdentifierMatch(input, s_textureArray);
								const bool usesPacking      = !!bx::findIdentifierMatch(input, s_ARB_shading_language_packing);

								if (0 == essl)
								{
									const bool need130 = 120 == glsl && (false
										|| bx::findIdentifierMatch(input, s_130)
										|| usesTexelFetch
										);

									if (0 != metal)
									{
										bx::stringPrintf(code, "#version 120\n");
									}
									else
									{
										bx::stringPrintf(code, "#version %s\n", need130 ? "130" : profile);
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

									if (usesTextureLod
									&&  130 > glsl)
									{
										bx::stringPrintf(code
											, "#extension GL_ARB_shader_texture_lod : enable\n"
											);
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

									bx::stringPrintf(code
										, "#define bgfxShadow2D shadow2D\n"
										  "#define bgfxShadow2DProj shadow2DProj\n"
										);
								}
								else
								{
									// Pretend that all extensions are available.
									// This will be stripped later.
									if (usesTextureLod)
									{
										bx::stringPrintf(code
											, "#extension GL_EXT_shader_texture_lod : enable\n"
											  "#define texture2DLod texture2DLodEXT\n"
											  "#define texture2DProjLod texture2DProjLodEXT\n"
											  "#define textureCubeLod textureCubeLodEXT\n"
	//										  "#define texture2DGrad texture2DGradEXT\n"
	//										  "#define texture2DProjGrad texture2DProjGradEXT\n"
	//										  "#define textureCubeGrad textureCubeGradEXT\n"
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

									bx::stringPrintf(code,
											"#define ivec2 vec2\n"
											"#define ivec3 vec3\n"
											"#define ivec4 vec4\n"
											);
								}

								code += preprocessor.m_preprocessed;

								compiled = compileGLSLShader(cmdLine
									, metal ? BX_MAKEFOURCC('M', 'T', 'L', 0) : essl
									, code
									, writer
									);
							}
							else if (0 != spirv)
							{
								compiled = compileSPIRVShader(cmdLine
									, 0
									, preprocessor.m_preprocessed
									, writer
									);
							}
							else if (0 != pssl)
							{
								compiled = compilePSSLShader(cmdLine
									, 0
									, preprocessor.m_preprocessed
									, writer
									);
							}
							else
							{
								compiled = compileHLSLShader(cmdLine
									, d3d
									, preprocessor.m_preprocessed
									, writer
									);
							}

							bx::close(writer);
							delete writer;
						}

						if (compiled)
						{
							if (depends)
							{
								std::string ofp = outFilePath;
								ofp += ".d";
								bx::CrtFileWriter writer;
								if (bx::open(&writer, ofp.c_str() ) )
								{
									writef(&writer, "%s : %s\n", outFilePath, preprocessor.m_depends.c_str() );
									bx::close(&writer);
								}
							}
						}
					}
				}
			}

			delete [] data;
		}

		if (compiled)
		{
			return EXIT_SUCCESS;
		}

		remove(outFilePath);

		fprintf(stderr, "Failed to build shader.\n");
		return EXIT_FAILURE;
	}

} // namespace bgfx

int main(int _argc, const char* _argv[])
{
	return bgfx::compileShader(_argc, _argv);
}
