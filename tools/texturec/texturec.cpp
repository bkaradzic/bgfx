/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <stdio.h>
#include <bx/allocator.h>
#include <bx/readerwriter.h>
#include <bx/endian.h>

#include <bimg/decode.h>
#include <bimg/encode.h>

#if 0
#	define BX_TRACE(_format, ...) fprintf(stderr, "" _format "\n", ##__VA_ARGS__)
#endif // DEBUG

#include <bx/bx.h>
#include <bx/commandline.h>
#include <bx/crtimpl.h>
#include <bx/uint32_t.h>

extern "C" {
#include <iqa.h>
}

void help(const char* _error = NULL)
{
	if (NULL != _error)
	{
		fprintf(stderr, "Error:\n%s\n\n", _error);
	}

	fprintf(stderr
		, "texturec, bgfx texture compiler tool\n"
		  "Copyright 2011-2017 Branimir Karadzic. All rights reserved.\n"
		  "License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause\n\n"
		);

	fprintf(stderr
		, "Usage: texturec -f <in> -o <out> [-t <format>]\n"

		  "\n"
		  "Supported input file types:\n"
		  "    *.png                  Portable Network Graphics\n"
		  "    *.tga                  Targa\n"
		  "    *.dds                  Direct Draw Surface\n"
		  "    *.ktx                  Khronos Texture\n"
		  "    *.pvr                  PowerVR\n"

		  "\n"
		  "Options:\n"
		  "  -f <file path>           Input file path.\n"
		  "  -o <file path>           Output file path (file will be written in KTX format).\n"
		  "  -t <format>              Output format type (BC1/2/3/4/5, ETC1, PVR14, etc.).\n"
		  "  -m, --mips               Generate mip-maps.\n"
		  "  -n, --normalmap          Input texture is normal map.\n"
		  "      --sdf <edge>         Compute SDF texture.\n"
		  "      --iqa                Image Quality Assesment\n"

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

	const char* inputFileName = cmdLine.findOption('f');
	if (NULL == inputFileName)
	{
		help("Input file must be specified.");
		return EXIT_FAILURE;
	}

	const char* outputFileName = cmdLine.findOption('o');
	if (NULL == outputFileName)
	{
		help("Output file must be specified.");
		return EXIT_FAILURE;
	}

	bool sdf = false;
	double edge = 16.0;
	const char* edgeOpt = cmdLine.findOption("sdf");
	if (NULL != edgeOpt)
	{
		sdf  = true;
		edge = atof(edgeOpt);
	}
	BX_UNUSED(sdf, edge);

	const bool mips      = cmdLine.hasArg('m',  "mips");
	const bool normalMap = cmdLine.hasArg('n',  "normalmap");
	const bool iqa       = cmdLine.hasArg('\0', "iqa");

	bx::CrtFileReader reader;
	if (!bx::open(&reader, inputFileName) )
	{
		help("Failed to open input file.");
		return EXIT_FAILURE;
	}

	bx::CrtAllocator allocator;

	uint32_t inputSize = (uint32_t)bx::getSize(&reader);
	uint8_t* inputData = (uint8_t*)BX_ALLOC(&allocator, inputSize);

	bx::read(&reader, inputData, inputSize);
	bx::close(&reader);

	{
		using namespace bimg;

		ImageContainer* input = imageParse(&allocator, inputData, inputSize);

		if (NULL != input)
		{
			BX_FREE(&allocator, inputData);

			const char* type = cmdLine.findOption('t');
			bimg::TextureFormat::Enum format = input->m_format;

			if (NULL != type)
			{
				format = bimg::getFormat(type);

				if (!isValid(format) )
				{
					help("Invalid format specified.");
					return EXIT_FAILURE;
				}
			}

			ImageContainer* output = NULL;

			ImageMip mip;
			if (imageGetRawData(*input, 0, 0, input->m_data, input->m_size, mip) )
			{
				uint8_t numMips = mips
					? imageGetNumMips(format, uint16_t(mip.m_width), uint16_t(mip.m_height) )
					: 1
					;

				void* temp = NULL;

				if (normalMap)
				{
					output = imageAlloc(&allocator, format, uint16_t(mip.m_width), uint16_t(mip.m_height), 0, 1, false, mips);

					ImageMip dstMip;
					imageGetRawData(*output, 0, 0, NULL, 0, dstMip);

					if (mip.m_width  != dstMip.m_width
					&&  mip.m_height != dstMip.m_height)
					{
						printf("Invalid input image size %dx%d, it must be at least %dx%d to be converted to %s format.\n"
							, mip.m_width
							, mip.m_height
							, dstMip.m_width
							, dstMip.m_height
							, getName(format)
							);
						return EXIT_FAILURE;
					}

					uint32_t size = imageGetSize(
						  NULL
						, uint16_t(dstMip.m_width)
						, uint16_t(dstMip.m_height)
						, 0
						, false
						, false
						, 1
						, TextureFormat::RGBA32F
						);
					temp = BX_ALLOC(&allocator, size);
					float* rgba = (float*)temp;
					float* rgbaDst = (float*)BX_ALLOC(&allocator, size);

					imageDecodeToRgba32f(&allocator
						, rgba
						, mip.m_data
						, mip.m_width
						, mip.m_height
						, mip.m_width*mip.m_bpp/8
						, mip.m_format
						);

					if (TextureFormat::BC5 != mip.m_format)
					{
						for (uint32_t yy = 0; yy < mip.m_height; ++yy)
						{
							for (uint32_t xx = 0; xx < mip.m_width; ++xx)
							{
								const uint32_t offset = (yy*mip.m_width + xx) * 4;
								float* inout = &rgba[offset];
								inout[0] = inout[0] * 2.0f - 1.0f;
								inout[1] = inout[1] * 2.0f - 1.0f;
								inout[2] = inout[2] * 2.0f - 1.0f;
								inout[3] = inout[3] * 2.0f - 1.0f;
							}
						}
					}

					imageRgba32f11to01(rgbaDst, dstMip.m_width, dstMip.m_height, dstMip.m_width*16, rgba);
					imageEncodeFromRgba32f(&allocator, output->m_data, rgbaDst, dstMip.m_width, dstMip.m_height, format);

					for (uint8_t lod = 1; lod < numMips; ++lod)
					{
						imageRgba32fDownsample2x2NormalMap(rgba, dstMip.m_width, dstMip.m_height, dstMip.m_width*16, rgba);
						imageRgba32f11to01(rgbaDst, dstMip.m_width, dstMip.m_height, dstMip.m_width*16, rgba);
						imageGetRawData(*output, 0, lod, output->m_data, output->m_size, dstMip);
						uint8_t* data = const_cast<uint8_t*>(dstMip.m_data);
						imageEncodeFromRgba32f(&allocator, data, rgbaDst, dstMip.m_width, dstMip.m_height, format);
					}

					BX_FREE(&allocator, rgbaDst);
				}
				else if (8 != getBlockInfo(input->m_format).rBits)
				{
					output = imageAlloc(&allocator, format, uint16_t(mip.m_width), uint16_t(mip.m_height), 0, 1, false, mips);

					ImageMip dstMip;
					imageGetRawData(*output, 0, 0, NULL, 0, dstMip);

					if (mip.m_width  != dstMip.m_width
					&&  mip.m_height != dstMip.m_height)
					{
						printf("Invalid input image size %dx%d, it must be at least %dx%d to be converted to %s format.\n"
							, mip.m_width
							, mip.m_height
							, dstMip.m_width
							, dstMip.m_height
							, getName(format)
							);
						return EXIT_FAILURE;
					}

					uint32_t size = imageGetSize(
						  NULL
						, uint16_t(dstMip.m_width)
						, uint16_t(dstMip.m_height)
						, 0
						, false
						, false
						, 1
						, TextureFormat::RGBA32F
						);
					temp = BX_ALLOC(&allocator, size);
					float* rgba = (float*)temp;
					float* rgbaDst = (float*)BX_ALLOC(&allocator, size);

					imageDecodeToRgba32f(&allocator
						, rgba
						, mip.m_data
						, mip.m_width
						, mip.m_height
						, mip.m_width*mip.m_bpp/8
						, mip.m_format
						);
					imageEncodeFromRgba32f(&allocator, output->m_data, rgba, dstMip.m_width, dstMip.m_height, format);

					imageRgba32fToLinear(rgba
						, mip.m_width
						, mip.m_height
						, mip.m_width*mip.m_bpp/8
						, rgba
						);

					for (uint8_t lod = 1; lod < numMips; ++lod)
					{
						imageRgba32fLinearDownsample2x2(rgba, dstMip.m_width, dstMip.m_height, dstMip.m_width*16, rgba);
						imageGetRawData(*output, 0, lod, output->m_data, output->m_size, dstMip);
						uint8_t* data = const_cast<uint8_t*>(dstMip.m_data);

						imageRgba32fToGamma(rgbaDst
							, mip.m_width
							, mip.m_height
							, mip.m_width*mip.m_bpp/8
							, rgba
							);

						imageEncodeFromRgba32f(&allocator, data, rgbaDst, dstMip.m_width, dstMip.m_height, format);
					}

					BX_FREE(&allocator, rgbaDst);
				}
				else
				{
					output = imageAlloc(&allocator, format, uint16_t(mip.m_width), uint16_t(mip.m_height), 0, 1, false, mips);

					ImageMip dstMip;
					imageGetRawData(*output, 0, 0, NULL, 0, dstMip);

					if (mip.m_width  != dstMip.m_width
					&&  mip.m_height != dstMip.m_height)
					{
						printf("Invalid input image size %dx%d, it must be at least %dx%d to be converted to %s format.\n"
							, mip.m_width
							, mip.m_height
							, dstMip.m_width
							, dstMip.m_height
							, getName(format)
							);
						return EXIT_FAILURE;
					}

					uint32_t size = imageGetSize(
						  NULL
						, uint16_t(dstMip.m_width)
						, uint16_t(dstMip.m_height)
						, 0
						, false
						, false
						, 1
						, TextureFormat::RGBA8
						);
					temp = BX_ALLOC(&allocator, size);
					bx::memSet(temp, 0, size);
					uint8_t* rgba = (uint8_t*)temp;

					imageDecodeToRgba8(rgba
						, mip.m_data
						, mip.m_width
						, mip.m_height
						, mip.m_width*mip.m_bpp/8
						, mip.m_format
						);

					void* ref = NULL;
					if (iqa)
					{
						ref = BX_ALLOC(&allocator, size);
						bx::memCopy(ref, rgba, size);
					}

					imageEncodeFromRgba8(output->m_data, rgba, dstMip.m_width, dstMip.m_height, format);

					for (uint8_t lod = 1; lod < numMips; ++lod)
					{
						imageRgba8Downsample2x2(rgba, dstMip.m_width, dstMip.m_height, dstMip.m_width*4, rgba);
						imageGetRawData(*output, 0, lod, output->m_data, output->m_size, dstMip);
						uint8_t* data = const_cast<uint8_t*>(dstMip.m_data);
						imageEncodeFromRgba8(data, rgba, dstMip.m_width, dstMip.m_height, format);
					}

					if (NULL != ref)
					{
						imageDecodeToRgba8(rgba
							, output->m_data
							, mip.m_width
							, mip.m_height
							, mip.m_width*mip.m_bpp/8
							, format
							);

						static const iqa_ssim_args args =
						{
							0.39f,     // alpha
							0.731f,    // beta
							1.12f,     // gamma
							187,       // L
							0.025987f, // K1
							0.0173f,   // K2
							1          // factor
						};

						float result = iqa_ssim( (uint8_t*)ref
								, rgba
								, mip.m_width
								, mip.m_height
								, mip.m_width*mip.m_bpp/8
								, 0
								, &args
								);
						printf("%f\n", result);

						BX_FREE(&allocator, ref);
					}
				}

				BX_FREE(&allocator, temp);
			}

			if (NULL != output)
			{
				bx::CrtFileWriter writer;
				if (bx::open(&writer, outputFileName) )
				{
					if (NULL != bx::stristr(outputFileName, ".ktx") )
					{
						imageWriteKtx(&writer, *output, output->m_data, output->m_size);
					}

					bx::close(&writer);
				}
				else
				{
					help("Failed to open output file.");
					return EXIT_FAILURE;
				}

				imageFree(output);
			}
			else
			{
				help("No output generated.");
				return EXIT_FAILURE;
			}
		}
		else
		{
			help("Failed to load input file.");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
