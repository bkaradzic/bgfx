/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/allocator.h>
#include <bx/readerwriter.h>
#include <bx/endian.h>

#include <bgfx/bgfx.h>

#include "image.h"

#include <libsquish/squish.h>
#include <etc1/etc1.h>
#include <etc2/ProcessRGB.hpp>
#include <nvtt/nvtt.h>
#include <pvrtc/PvrTcEncoder.h>

#include <edtaa3/edtaa3func.h>

extern "C" {
#include <iqa.h>
}

#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_NO_COMPILE_DISK
#define LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#define LODEPNG_NO_COMPILE_ERROR_TEXT
#define LODEPNG_NO_COMPILE_ALLOCATORS
#define LODEPNG_NO_COMPILE_CPP
#include <lodepng/lodepng.cpp>

void* lodepng_malloc(size_t _size)
{
	return ::malloc(_size);
}

void* lodepng_realloc(void* _ptr, size_t _size)
{
	return ::realloc(_ptr, _size);
}

void lodepng_free(void* _ptr)
{
	::free(_ptr);
}

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wmissing-field-initializers");
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wint-to-pointer-cast")
#define STBI_MALLOC(_size)        lodepng_malloc(_size)
#define STBI_REALLOC(_ptr, _size) lodepng_realloc(_ptr, _size)
#define STBI_FREE(_ptr)           lodepng_free(_ptr)
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.c>
BX_PRAGMA_DIAGNOSTIC_POP();

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-parameter")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-value")
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4100) // error C4100: '' : unreferenced formal parameter
#define MINIZ_NO_STDIO
#define TINYEXR_IMPLEMENTATION
#include <tinyexr/tinyexr.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#if 0
#	define BX_TRACE(_format, ...) fprintf(stderr, "" _format "\n", ##__VA_ARGS__)
#endif // DEBUG

#include <bx/bx.h>
#include <bx/commandline.h>
#include <bx/crtimpl.h>
#include <bx/uint32_t.h>

namespace bgfx
{
	bool imageParse(ImageContainer& _imageContainer, const void* _data, uint32_t _size, void** _out)
	{
		*_out = NULL;
		bool loaded = imageParse(_imageContainer, _data, _size);
		if (!loaded)
		{
			bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8;
			uint32_t bpp = 32;

			uint32_t width  = 0;
			uint32_t height = 0;

			uint8_t* out = NULL;
			static uint8_t pngMagic[] = { 0x89, 0x50, 0x4E, 0x47, 0x0d, 0x0a };
			if (0 == memcmp(_data, pngMagic, sizeof(pngMagic) ) )
			{
				unsigned error;
				LodePNGState state;
				lodepng_state_init(&state);
				state.decoder.color_convert = 0;
				error = lodepng_decode(&out, &width, &height, &state, (uint8_t*)_data, _size);

				if (0 == error)
				{
					*_out = out;

					switch (state.info_raw.bitdepth)
					{
					case 8:
						switch (state.info_raw.colortype)
						{
						case LCT_GREY:
							format = bgfx::TextureFormat::R8;
							bpp    = 8;
							break;

						case LCT_GREY_ALPHA:
							format = bgfx::TextureFormat::RG8;
							bpp    = 16;
							break;

						case LCT_RGB:
							format = bgfx::TextureFormat::RGB8;
							bpp    = 24;
							break;

						case LCT_RGBA:
							format = bgfx::TextureFormat::RGBA8;
							bpp    = 32;
							break;

						case LCT_PALETTE:
							break;
						}
						break;

					case 16:
						switch (state.info_raw.colortype)
						{
						case LCT_GREY:
							for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
							{
								uint16_t* rgba = (uint16_t*)out + ii;
								rgba[0] = bx::toHostEndian(rgba[0], false);
							}
							format = bgfx::TextureFormat::R16;
							bpp    = 16;
							break;

						case LCT_GREY_ALPHA:
							for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
							{
								uint16_t* rgba = (uint16_t*)out + ii*2;
								rgba[0] = bx::toHostEndian(rgba[0], false);
								rgba[1] = bx::toHostEndian(rgba[1], false);
							}
							format = bgfx::TextureFormat::RG16;
							bpp    = 32;
							break;

						case LCT_RGBA:
							for (uint32_t ii = 0, num = width*height; ii < num; ++ii)
							{
								uint16_t* rgba = (uint16_t*)out + ii*4;
								rgba[0] = bx::toHostEndian(rgba[0], false);
								rgba[1] = bx::toHostEndian(rgba[1], false);
								rgba[2] = bx::toHostEndian(rgba[2], false);
								rgba[3] = bx::toHostEndian(rgba[3], false);
							}
							format = bgfx::TextureFormat::RGBA16;
							bpp    = 64;
							break;

						case LCT_RGB:
						case LCT_PALETTE:
							break;
						}
						break;

					default:
						break;
					}
				}

				lodepng_state_cleanup(&state);
			}
			else
			{
				int comp = 0;
				*_out = stbi_load_from_memory( (uint8_t*)_data, _size, (int*)&width, (int*)&height, &comp, 4);
			}

			loaded = NULL != *_out;

			if (loaded)
			{
				_imageContainer.m_data      = *_out;
				_imageContainer.m_size      = width*height*bpp/8;
				_imageContainer.m_offset    = 0;
				_imageContainer.m_width     = width;
				_imageContainer.m_height    = height;
				_imageContainer.m_depth     = 1;
				_imageContainer.m_numLayers = 1;
				_imageContainer.m_format    = format;
				_imageContainer.m_numMips   = 1;
				_imageContainer.m_hasAlpha  = true;
				_imageContainer.m_cubeMap   = false;
				_imageContainer.m_ktx       = false;
				_imageContainer.m_ktxLE     = false;
				_imageContainer.m_srgb      = false;
			}
		}

		return loaded;
	}

	bool imageEncodeFromRgba8(void* _dst, const void* _src, uint32_t _width, uint32_t _height, uint8_t _format)
	{
		TextureFormat::Enum format = TextureFormat::Enum(_format);

		switch (format)
		{
		case TextureFormat::BC1:
		case TextureFormat::BC2:
		case TextureFormat::BC3:
		case TextureFormat::BC4:
		case TextureFormat::BC5:
			squish::CompressImage( (const uint8_t*)_src, _width, _height, _dst
				, format == TextureFormat::BC2 ? squish::kDxt3
				: format == TextureFormat::BC3 ? squish::kDxt5
				: format == TextureFormat::BC4 ? squish::kBc4
				: format == TextureFormat::BC5 ? squish::kBc5
				:                                squish::kDxt1
				);
			return true;

		case TextureFormat::BC6H:
			nvtt::compressBC6H( (const uint8_t*)_src, _width, _height, 4, _dst);
			return true;

		case TextureFormat::BC7:
			nvtt::compressBC7( (const uint8_t*)_src, _width, _height, 4, _dst);
			return true;

		case TextureFormat::ETC1:
			etc1_encode_image( (const uint8_t*)_src, _width, _height, 4, _width*4, (uint8_t*)_dst);
			return true;

		case TextureFormat::ETC2:
			{
				const uint32_t blockWidth  = (_width +3)/4;
				const uint32_t blockHeight = (_height+3)/4;
				const uint32_t pitch = _width*4;
				const uint8_t* src = (const uint8_t*)_src;
				uint64_t* dst = (uint64_t*)_dst;
				for (uint32_t yy = 0; yy < blockHeight; ++yy)
				{
					for (uint32_t xx = 0; xx < blockWidth; ++xx)
					{
						uint8_t block[4*4*4];
						const uint8_t* ptr = &src[(yy*pitch+xx*4)*4];

						for (uint32_t ii = 0; ii < 16; ++ii)
						{ // BGRx
							memcpy(&block[ii*4], &ptr[(ii%4)*pitch + (ii&~3)], 4);
							bx::xchg(block[ii*4+0], block[ii*4+2]);
						}

						*dst++ = ProcessRGB_ETC2(block);
					}
				}
			}
			return true;

		case TextureFormat::PTC14:
			{
				using namespace Javelin;
				RgbaBitmap bmp;
				bmp.width  = _width;
				bmp.height = _height;
				bmp.data   = (uint8_t*)const_cast<void*>(_src);
				PvrTcEncoder::EncodeRgb4Bpp(_dst, bmp);
				bmp.data = NULL;
			}
			return true;

		case TextureFormat::PTC14A:
			{
				using namespace Javelin;
				RgbaBitmap bmp;
				bmp.width  = _width;
				bmp.height = _height;
				bmp.data   = (uint8_t*)const_cast<void*>(_src);
				PvrTcEncoder::EncodeRgba4Bpp(_dst, bmp);
				bmp.data = NULL;
			}
			return true;

		case TextureFormat::BGRA8:
			imageSwizzleBgra8(_dst, _width, _height, _width*4, _src);
			return true;

		case TextureFormat::RGBA8:
			memcpy(_dst, _src, _width*_height*4);
			return true;

		default:
			return imageConvert(_dst, format, _src, TextureFormat::RGBA8, _width, _height);
		}

		return false;
	}

	bool imageEncodeFromRgba32f(bx::AllocatorI* _allocator, void* _dst, const void* _src, uint32_t _width, uint32_t _height, uint8_t _format)
	{
		TextureFormat::Enum format = TextureFormat::Enum(_format);

		const uint8_t* src = (const uint8_t*)_src;

		switch (format)
		{
		case TextureFormat::RGBA8:
			{
				uint8_t* dst = (uint8_t*)_dst;
				for (uint32_t yy = 0; yy < _height; ++yy)
				{
					for (uint32_t xx = 0; xx < _width; ++xx)
					{
						const uint32_t offset = yy*_width + xx;
						const float* input = (const float*)&src[offset * 16];
						uint8_t* output    = &dst[offset * 4];
						output[0] = uint8_t(input[0]*255.0f + 0.5f);
						output[1] = uint8_t(input[1]*255.0f + 0.5f);
						output[2] = uint8_t(input[2]*255.0f + 0.5f);
						output[3] = uint8_t(input[3]*255.0f + 0.5f);
					}
				}
			}
			return true;

		case TextureFormat::BC5:
			{
				uint8_t* temp = (uint8_t*)BX_ALLOC(_allocator, _width*_height*4);
				for (uint32_t yy = 0; yy < _height; ++yy)
				{
					for (uint32_t xx = 0; xx < _width; ++xx)
					{
						const uint32_t offset = yy*_width + xx;
						const float* input = (const float*)&src[offset * 16];
						uint8_t* output    = &temp[offset * 4];
						output[0] = uint8_t(input[0]*255.0f + 0.5f);
						output[1] = uint8_t(input[1]*255.0f + 0.5f);
						output[2] = uint8_t(input[2]*255.0f + 0.5f);
						output[3] = uint8_t(input[3]*255.0f + 0.5f);
					}
				}

				imageEncodeFromRgba8(_dst, temp, _width, _height, _format);
				BX_FREE(_allocator, temp);
			}
			return true;

		default:
			return imageConvert(_dst, format, _src, TextureFormat::RGBA32F, _width, _height);
		}

		return false;
	}

	void imageRgba32f11to01(void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src)
	{
		const uint8_t* src = (const uint8_t*)_src;
		uint8_t* dst = (uint8_t*)_dst;

		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			for (uint32_t xx = 0; xx < _width; ++xx)
			{
				const uint32_t offset = yy*_pitch + xx * 16;
				const float* input = (const float*)&src[offset];
				float* output = (float*)&dst[offset];
				output[0] = input[0]*0.5f + 0.5f;
				output[1] = input[1]*0.5f + 0.5f;
				output[2] = input[2]*0.5f + 0.5f;
				output[3] = input[3]*0.5f + 0.5f;
			}
		}
	}

	static void edtaa3(bx::AllocatorI* _allocator, double* _dst, uint32_t _width, uint32_t _height, double* _src)
	{
		const uint32_t numPixels = _width*_height;

		short* xdist = (short *)BX_ALLOC(_allocator, numPixels*sizeof(short) );
		short* ydist = (short *)BX_ALLOC(_allocator, numPixels*sizeof(short) );
		double* gx   = (double*)BX_ALLOC(_allocator, numPixels*sizeof(double) );
		double* gy   = (double*)BX_ALLOC(_allocator, numPixels*sizeof(double) );

		::computegradient(_src, _width, _height, gx, gy);
		::edtaa3(_src, gx, gy, _width, _height, xdist, ydist, _dst);

		for (uint32_t ii = 0; ii < numPixels; ++ii)
		{
			if (_dst[ii] < 0.0)
			{
				_dst[ii] = 0.0;
			}
		}

		BX_FREE(_allocator, xdist);
		BX_FREE(_allocator, ydist);
		BX_FREE(_allocator, gx);
		BX_FREE(_allocator, gy);
	}

	inline double min(double _a, double _b)
	{
		return _a > _b ? _b : _a;
	}

	inline double max(double _a, double _b)
	{
		return _a > _b ? _a : _b;
	}

	inline double clamp(double _val, double _min, double _max)
	{
		return max(min(_val, _max), _min);
	}

	void imageMakeDist(bx::AllocatorI* _allocator, void* _dst, uint32_t _width, uint32_t _height, uint32_t _pitch, float _edge, const void* _src)
	{
		const uint32_t numPixels = _width*_height;

		double* imgIn   = (double*)BX_ALLOC(_allocator, numPixels*sizeof(double) );
		double* outside = (double*)BX_ALLOC(_allocator, numPixels*sizeof(double) );
		double* inside  = (double*)BX_ALLOC(_allocator, numPixels*sizeof(double) );

		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			const uint8_t* src = (const uint8_t*)_src + yy*_pitch;
			double* dst = &imgIn[yy*_width];
			for (uint32_t xx = 0; xx < _width; ++xx)
			{
				dst[xx] = double(src[xx])/255.0;
			}
		}

		edtaa3(_allocator, outside, _width, _height, imgIn);

		for (uint32_t ii = 0; ii < numPixels; ++ii)
		{
			imgIn[ii] = 1.0 - imgIn[ii];
		}

		edtaa3(_allocator, inside, _width, _height, imgIn);

		BX_FREE(_allocator, imgIn);

		uint8_t* dst = (uint8_t*)_dst;

		double edgeOffset = _edge*0.5;
		double invEdge = 1.0/_edge;

		for (uint32_t ii = 0; ii < numPixels; ++ii)
		{
			double dist = clamp( ( (outside[ii] - inside[ii])+edgeOffset) * invEdge, 0.0, 1.0);
			dst[ii] = 255-uint8_t(dist * 255.0);
		}

		BX_FREE(_allocator, inside);
		BX_FREE(_allocator, outside);
	}

} // namespace bgfx

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
		using namespace bgfx;

		uint8_t* decodedImage = NULL;
		ImageContainer input;

		bool loaded = imageParse(input, inputData, inputSize, (void**)&decodedImage);
		if (NULL != decodedImage)
		{
			BX_FREE(&allocator, inputData);

			inputData = (uint8_t*)input.m_data;
			inputSize = input.m_size;
		}

		if (loaded)
		{
			const char* type = cmdLine.findOption('t');
			bgfx::TextureFormat::Enum format = input.m_format;

			if (NULL != type)
			{
				format = bgfx::getFormat(type);

				if (!isValid(format) )
				{
					help("Invalid format specified.");
					return EXIT_FAILURE;
				}
			}

			ImageContainer* output = NULL;

			ImageMip mip;
			if (imageGetRawData(input, 0, 0, inputData, inputSize, mip) )
			{
				uint8_t numMips = mips
					? imageGetNumMips(format, mip.m_width, mip.m_height)
					: 1
					;

				void* temp = NULL;

				if (normalMap)
				{
					output = imageAlloc(&allocator, format, mip.m_width, mip.m_height, 0, 1, false, mips);

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
						, dstMip.m_width
						, dstMip.m_height
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
				else if (8 != getBlockInfo(input.m_format).rBits)
				{
					output = imageAlloc(&allocator, format, mip.m_width, mip.m_height, 0, 1, false, mips);

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
						, dstMip.m_width
						, dstMip.m_height
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
					output = imageAlloc(&allocator, format, mip.m_width, mip.m_height, 0, 1, false, mips);

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
						, dstMip.m_width
						, dstMip.m_height
						, 0
						, false
						, false
						, 1
						, TextureFormat::RGBA8
						);
					temp = BX_ALLOC(&allocator, size);
					memset(temp, 0, size);
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
						memcpy(ref, rgba, size);
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

		BX_FREE(&allocator, inputData);
	}

	return EXIT_SUCCESS;
}
