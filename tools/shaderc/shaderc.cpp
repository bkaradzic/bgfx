/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "shaderc.h"
#include <cstdio>

static long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
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

	virtual int32_t close() BX_OVERRIDE
	{
		generate();
		return bx::CrtFileWriter::close();
	}

	virtual int32_t write(const void* _data, int32_t _size) BX_OVERRIDE
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

		int32_t size = bx::CrtFileWriter::write(out, len);

		va_end(argList);

		return size;
	}

	std::string m_filePath;
	std::string m_name;
	typedef std::vector<uint8_t> Buffer;
	Buffer m_buffer;
};



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
		  "Copyright 2011-2015 Branimir Karadzic. All rights reserved.\n"
		  "License: http://www.opensource.org/licenses/BSD-2-Clause\n\n"
		);

	fprintf(stderr
		, "Usage: shaderc -f <in> -o <out> --type <v/f> --platform <platform>\n"

		  "\n"
		  "Options:\n"
		  "  -f <file path>                Input file path.\n"
		  "  -i <include path>             Include path (for multiple paths use semicolon).\n"
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

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	if (cmdLine.hasArg('h', "help") )
	{
		help();
		return EXIT_FAILURE;
	}

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

	bx::CrtFileReader* reader = new bx::CrtFileReader;
	if (0 != reader->open(filePath)) 
	{
		fprintf(stderr, "Unable to open input file '%s'.", filePath);
		delete reader;
		return EXIT_FAILURE;
	}

	bx::CrtFileWriter* writer = NULL;

	if (NULL != bin2c)
	{
		writer = new Bin2cWriter(bin2c);
	}
	else
	{
		writer = new bx::CrtFileWriter;
	}

	if (0 != writer->open(outFilePath) )
	{
		fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
		delete writer;
		delete reader;
		return EXIT_FAILURE;
	}

	int result = compileShader (cmdLine, reader, writer);

	reader->close();
	delete reader;

	writer->close();
	delete writer;

	return result;
}
