/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <edtaa3/edtaa3func.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.c>

#define BX_NAMESPACE 1
#include <bx/bx.h>
#include <bx/commandline.h>
#include <bx/uint32_t.h>

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

void edtaa3(double* _img, uint16_t _width, uint16_t _height, double* _out)
{
	uint32_t size = _width*_height;

	short* xdist = (short*)malloc(size*sizeof(short) );
	short* ydist = (short*)malloc(size*sizeof(short) );
	double* gx = (double*)malloc(size*sizeof(double) );
	double* gy = (double*)malloc(size*sizeof(double) );

	computegradient(_img, _width, _height, gx, gy);
	edtaa3(_img, gx, gy, _width, _height, xdist, ydist, _out);

	for (uint32_t ii = 0; ii < size; ++ii)
	{
		if (_out[ii] < 0.0)
		{
			_out[ii] = 0.0;
		}
	}

	free(xdist);
	free(ydist);
	free(gx);
	free(gy);
}

void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, bool _grayscale, const void* _data)
{
	FILE* file = fopen(_filePath, "wb");
	if ( NULL != file )
	{
		uint8_t type = _grayscale ? 3 : 2;
		uint8_t bpp = _grayscale ? 8 : 32;
		uint8_t xorig = 0;
		uint8_t yorig = 0;

		putc(0, file);
		putc(0, file);
		putc(type, file);
		putc(0, file);
		putc(0, file);
		putc(0, file);
		putc(0, file);
		putc(0, file);
		putc(0, file);
		putc(xorig, file);
		putc(0, file);
		putc(yorig, file);
		putc(_width&0xff, file);
		putc( (_width>>8)&0xff, file);
		putc(_height&0xff, file);
		putc( (_height>>8)&0xff, file);
		putc(bpp, file);
		putc(32, file);

		uint32_t width = _width * bpp / 8;
		uint8_t* data = (uint8_t*)_data;
		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			fwrite(data, width, 1, file);
			data += _pitch;
		}

		fclose(file);
	}
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

inline double saturate(double _val)
{
	return clamp(_val, 0.0, 1.0);
}

int main(int _argc, const char* _argv[])
{
	bx::CommandLine cmdLine(_argc, _argv);

	const char* inFilePath = cmdLine.findOption('i');
	if (NULL == inFilePath)
	{
		fprintf(stderr, "Input file name must be specified.\n");
		return EXIT_FAILURE;
	}

	const char* outFilePath = cmdLine.findOption('o');
	if (NULL == outFilePath)
	{
		fprintf(stderr, "Output file name must be specified.\n");
		return EXIT_FAILURE;
	}

	double edge = 16.0;
	const char* edgeOpt = cmdLine.findOption('e');
	if (NULL != edgeOpt)
	{
		edge = atof(edgeOpt);
	}

	int width;
	int height;
	int comp;

	stbi_uc* img = stbi_load(inFilePath, &width, &height, &comp, 1);

	if (NULL == img)
	{
		fprintf(stderr, "Failed to load %s.\n", inFilePath);
		return EXIT_FAILURE;
	}

	uint32_t size = width*height;

	double* imgIn = (double*)malloc(size*sizeof(double) );
	double* outside = (double*)malloc(size*sizeof(double) );
	double* inside = (double*)malloc(size*sizeof(double) );

	for (uint32_t ii = 0; ii < size; ++ii)
	{
		imgIn[ii] = double(img[ii])/255.0;
	}

	edtaa3(imgIn, width, height, outside);

	for (uint32_t ii = 0; ii < size; ++ii)
	{
		imgIn[ii] = 1.0 - imgIn[ii];
	}

	edtaa3(imgIn, width, height, inside);

	free(imgIn);

	uint8_t* grayscale = (uint8_t*)malloc(size);

	double edgeOffset = edge*0.5;
	double invEdge = 1.0/edge;

	for (uint32_t ii = 0; ii < size; ++ii)
	{
		double dist = saturate( ( (outside[ii] - inside[ii])+edgeOffset) * invEdge);
		grayscale[ii] = 255-uint8_t(dist * 255.0);
	}

	free(inside);
	free(outside);

	saveTga(outFilePath, width, height, width, true, grayscale);

	free(grayscale);

	return EXIT_SUCCESS;
}
