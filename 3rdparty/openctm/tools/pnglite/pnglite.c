/*  pnglite.c - pnglite library
    For conditions of distribution and use, see copyright notice in pnglite.h
*/
#define DO_CRC_CHECKS 1
#define USE_ZLIB 1

#if USE_ZLIB
#include "../zlib/zlib.h"
#else
#include "zlite.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pnglite.h"



static png_alloc_t png_alloc;
static png_free_t png_free;

static size_t file_read(png_t* png, void* out, size_t size, size_t numel)
{
	size_t result;
	if(png->read_fun)
	{
		result = png->read_fun(out, size, numel, png->user_pointer);
	}
	else
	{
		if(!out)
		{
			result = fseek(png->user_pointer, (long)(size*numel), SEEK_CUR);
		}
		else
		{
			result = fread(out, size, numel, png->user_pointer);
		}
	}

	return result;
}

static size_t file_write(png_t* png, void* p, size_t size, size_t numel)
{
	size_t result;

	if(png->write_fun)
	{
		result = png->write_fun(p, size, numel, png->user_pointer);
	}
	else
	{
		result = fwrite(p, size, numel, png->user_pointer);
	}

	return result;
}

static int file_read_ul(png_t* png, unsigned *out)
{
	unsigned char buf[4];

	if(file_read(png, buf, 1, 4) != 4)
		return PNG_FILE_ERROR;

	*out = (buf[0]<<24) | (buf[1]<<16) | (buf[2]<<8) | buf[3];

	return PNG_NO_ERROR;
}

static int file_write_ul(png_t* png, unsigned in)
{
	unsigned char buf[4];

	buf[0] = (in>>24) & 0xff;
	buf[1] = (in>>16) & 0xff;
	buf[2] = (in>>8) & 0xff;
	buf[3] = (in) & 0xff;

	if(file_write(png, buf, 1, 4) != 4)
		return PNG_FILE_ERROR;

	return PNG_NO_ERROR;
}
	

static unsigned get_ul(unsigned char* buf)
{
	unsigned result;
	unsigned char foo[4];

	memcpy(foo, buf, 4);

	result = (foo[0]<<24) | (foo[1]<<16) | (foo[2]<<8) | foo[3];

	return result;
}

static unsigned set_ul(unsigned char* buf, unsigned in)
{
	buf[0] = (in>>24) & 0xff;
	buf[1] = (in>>16) & 0xff;
	buf[2] = (in>>8) & 0xff;
	buf[3] = (in) & 0xff;

	return PNG_NO_ERROR;
}

int png_init(png_alloc_t pngalloc, png_free_t pngfree)
{
	if(pngalloc)
		png_alloc = pngalloc;
	else
		png_alloc = &malloc;

	if(pngfree)
		png_free = pngfree;
	else
		png_free = &free;

	return PNG_NO_ERROR;
}

static int png_get_bpp(png_t* png)
{
	int bpp;

	switch(png->color_type)
	{
	case PNG_GREYSCALE:
		bpp = 1; break;
	case PNG_TRUECOLOR:
		bpp = 3; break;
	case PNG_INDEXED:
		bpp = 1; break;
	case PNG_GREYSCALE_ALPHA:
		bpp = 2; break;
	case PNG_TRUECOLOR_ALPHA:
		bpp = 4; break;
	default:
		return PNG_FILE_ERROR;
	}

	bpp *= png->depth/8;

	return bpp;
}

static int png_read_ihdr(png_t* png)
{
	unsigned length;
#if DO_CRC_CHECKS
	unsigned orig_crc;
	unsigned calc_crc;
#endif
	unsigned char ihdr[13+4];		 /* length should be 13, make room for type (IHDR) */

	file_read_ul(png, &length);

	if(length != 13)
	{
		printf("%d\n", length);
		return PNG_CRC_ERROR;
	}

	if(file_read(png, ihdr, 1, 13+4) != 13+4)
		return PNG_EOF_ERROR;
#if DO_CRC_CHECKS
	file_read_ul(png, &orig_crc);

	calc_crc = crc32(0L, 0, 0);
	calc_crc = crc32(calc_crc, ihdr, 13+4);

	if(orig_crc != calc_crc)
		return PNG_CRC_ERROR;
#else
	file_read_ul(png);
#endif

	png->width = get_ul(ihdr+4);
	png->height = get_ul(ihdr+8);
	png->depth = ihdr[12];
	png->color_type = ihdr[13];
	png->compression_method = ihdr[14];
	png->filter_method = ihdr[15];
	png->interlace_method = ihdr[16];

	if(png->color_type == PNG_INDEXED)
		return PNG_NOT_SUPPORTED;

	if(png->depth != 8 && png->depth != 16)
		return PNG_NOT_SUPPORTED;

	if(png->interlace_method)
		return PNG_NOT_SUPPORTED;
	
	return PNG_NO_ERROR;
}

static int png_write_ihdr(png_t* png)
{
	unsigned char ihdr[13+4];
	unsigned char *p = ihdr;
	unsigned crc;
	
	file_write(png, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 1, 8);

	file_write_ul(png, 13);
    
	*p = 'I';			p++;
	*p = 'H';			p++;
	*p = 'D';			p++;
	*p = 'R';			p++;
	set_ul(p, png->width);	p+=4;
	set_ul(p, png->height);	p+=4;
	*p = png->depth;			p++;
	*p = png->color_type;	p++;
	*p = 0;				p++;
	*p = 0;				p++;
	*p = 0;				p++;

	file_write(png, ihdr, 1, 13+4);

	crc = crc32(0L, 0, 0);
	crc = crc32(crc, ihdr, 13+4);

	file_write_ul(png, crc);

	return PNG_NO_ERROR;
}

void png_print_info(png_t* png)
{
	printf("PNG INFO:\n");
	printf("\twidth:\t\t%d\n", png->width);
	printf("\theight:\t\t%d\n", png->height);
	printf("\tdepth:\t\t%d\n", png->depth);
	printf("\tcolor:\t\t");

	switch(png->color_type)
	{
	case PNG_GREYSCALE:			printf("greyscale\n"); break;
	case PNG_TRUECOLOR:			printf("truecolor\n"); break;
	case PNG_INDEXED:			printf("palette\n"); break;
	case PNG_GREYSCALE_ALPHA:	printf("greyscale with alpha\n"); break;
	case PNG_TRUECOLOR_ALPHA:	printf("truecolor with alpha\n"); break;
	default:					printf("unknown, this is not good\n"); break;
	}

	printf("\tcompression:\t%s\n",	png->compression_method?"unknown, this is not good":"inflate/deflate");
	printf("\tfilter:\t\t%s\n",		png->filter_method?"unknown, this is not good":"adaptive");
	printf("\tinterlace:\t%s\n",	png->interlace_method?"interlace":"no interlace");
}

int png_open_read(png_t* png, png_read_callback_t read_fun, void* user_pointer)
{
	char header[8];
	int result;

	png->read_fun = read_fun;
	png->write_fun = 0;
	png->user_pointer = user_pointer;

	if(!read_fun && !user_pointer)
		return PNG_WRONG_ARGUMENTS;

	if(file_read(png, header, 1, 8) != 8)
		return PNG_EOF_ERROR;

	if(memcmp(header, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 8) != 0)
		return PNG_HEADER_ERROR;

	result = png_read_ihdr(png);

	png->bpp = (unsigned char)png_get_bpp(png);

	return result;
}

int png_open_write(png_t* png, png_write_callback_t write_fun, void* user_pointer)
{
	png->write_fun = write_fun;
	png->read_fun = 0;
	png->user_pointer = user_pointer;

	if(!write_fun && !user_pointer)
		return PNG_WRONG_ARGUMENTS;

	return PNG_NO_ERROR;
}

int png_open(png_t* png, png_read_callback_t read_fun, void* user_pointer)
{
	return png_open_read(png, read_fun, user_pointer);
}

int png_open_file_read(png_t *png, const char* filename)
{
	FILE* fp = fopen(filename, "rb");

	if(!fp)
		return PNG_FILE_ERROR;

	return png_open_read(png, 0, fp);
}

int png_open_file_write(png_t *png, const char* filename)
{
	FILE* fp = fopen(filename, "wb");

	if(!fp)
		return PNG_FILE_ERROR;

	return png_open_write(png, 0, fp);
}

int png_open_file(png_t *png, const char* filename)
{
	return png_open_file_read(png, filename);
}

int png_close_file(png_t* png)
{
	fclose(png->user_pointer);

	return PNG_NO_ERROR;
}

static int png_init_deflate(png_t* png, unsigned char* data, int datalen)
{
	z_stream *stream;
	png->zs = png_alloc(sizeof(z_stream));

	stream = png->zs;

	if(!stream)
		return PNG_MEMORY_ERROR;

	memset(stream, 0, sizeof(z_stream));

	if(deflateInit(stream, Z_DEFAULT_COMPRESSION) != Z_OK)
		return PNG_ZLIB_ERROR;

	stream->next_in = data;
	stream->avail_in = datalen;

	return PNG_NO_ERROR;
}

static int png_init_inflate(png_t* png)
{
#if USE_ZLIB
	z_stream *stream;
	png->zs = png_alloc(sizeof(z_stream));
#else
	zl_stream *stream;
	png->zs = png_alloc(sizeof(zl_stream));
#endif

	stream = png->zs;

	if(!stream)
		return PNG_MEMORY_ERROR;

	

#if USE_ZLIB
	memset(stream, 0, sizeof(z_stream));
	if(inflateInit(stream) != Z_OK)
		return PNG_ZLIB_ERROR;
#else
	memset(stream, 0, sizeof(zl_stream));
	if(z_inflateInit(stream) != Z_OK)
		return PNG_ZLIB_ERROR;
#endif

	stream->next_out = png->png_data;
	stream->avail_out = png->png_datalen;

	return PNG_NO_ERROR;
}

static int png_end_deflate(png_t* png)
{
	z_stream *stream = png->zs;

	if(!stream)
		return PNG_MEMORY_ERROR;

	deflateEnd(stream);

	png_free(png->zs);

	return PNG_NO_ERROR;
}

static int png_end_inflate(png_t* png)
{
#if USE_ZLIB
	z_stream *stream = png->zs;
#else
	zl_stream *stream = png->zs;
#endif

	if(!stream)
		return PNG_MEMORY_ERROR;

#if USE_ZLIB
	if(inflateEnd(stream) != Z_OK)
#else
	if(z_inflateEnd(stream) != Z_OK)
#endif
	{
		printf("ZLIB says: %s\n", stream->msg);
		return PNG_ZLIB_ERROR;
	}

	png_free(png->zs);

	return PNG_NO_ERROR;
}

static int png_inflate(png_t* png, char* data, int len)
{
	int result;
#if USE_ZLIB
	z_stream *stream = png->zs;
#else
	zl_stream *stream = png->zs;
#endif

	if(!stream)
		return PNG_MEMORY_ERROR;

	stream->next_in = (unsigned char*)data;
	stream->avail_in = len;
	
#if USE_ZLIB
	result = inflate(stream, Z_SYNC_FLUSH);
#else
	result = z_inflate(stream);
#endif

	if(result != Z_STREAM_END && result != Z_OK)
	{
		printf("%s\n", stream->msg);
		return PNG_ZLIB_ERROR;
	}

	if(stream->avail_in != 0)
		return PNG_ZLIB_ERROR;

	return PNG_NO_ERROR;
}

static int png_deflate(png_t* png, char* outdata, int outlen, int *outwritten)
{
	int result;

	z_stream *stream = png->zs;


	if(!stream)
		return PNG_MEMORY_ERROR;

	stream->next_out = (unsigned char*)outdata;
	stream->avail_out = outlen;

	result = deflate(stream, Z_SYNC_FLUSH);

	*outwritten = outlen - stream->avail_out;

	if(result != Z_STREAM_END && result != Z_OK)
	{
		printf("%s\n", stream->msg);
		return PNG_ZLIB_ERROR;
	}

	return result;
}

static int png_write_idats(png_t* png, unsigned char* data)
{
	unsigned char *chunk;
	unsigned long written;
	unsigned long crc;
	unsigned size = png->width * png->height * png->bpp + png->height;
	
	(void)png_init_deflate;
	(void)png_end_deflate;
	(void)png_deflate;

	chunk = png_alloc(size);
	memcpy(chunk, "IDAT", 4);
	
	written = size;
	compress(chunk+4, &written, data, size);
	
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, chunk, written+4);
	set_ul(chunk+written+4, crc);
	file_write_ul(png, written);
	file_write(png, chunk, 1, written+8);
	png_free(chunk);

	file_write_ul(png, 0);
	file_write(png, "IEND", 1, 4);
	crc = crc32(0L, (const unsigned char *)"IEND", 4);
	file_write_ul(png, crc);
	
	return PNG_NO_ERROR;
}

static int png_read_idat(png_t* png, unsigned firstlen) 
{
	unsigned type = 0;
	char *chunk;
	int result;
	unsigned length = firstlen;
	unsigned old_len = length;

#if DO_CRC_CHECKS
	unsigned orig_crc;
	unsigned calc_crc;
#endif

	chunk = png_alloc(firstlen); 

	result = png_init_inflate(png);

	if(result != PNG_NO_ERROR)
	{
		png_end_inflate(png);
		png_free(chunk); 
		return result;
	}

	do
	{
		if(file_read(png, chunk, 1, length) != length)
		{
			png_end_inflate(png);
			png_free(chunk); 
			return PNG_FILE_ERROR;
		}

#if DO_CRC_CHECKS
		calc_crc = crc32(0L, Z_NULL, 0);
		calc_crc = crc32(calc_crc, (unsigned char*)"IDAT", 4);
		calc_crc = crc32(calc_crc, (unsigned char*)chunk, length);

		file_read_ul(png, &orig_crc);

		if(orig_crc != calc_crc)
		{
			result = PNG_CRC_ERROR;
			break;
		}
#else
		file_read_ul(png);
#endif

		result = png_inflate(png, chunk, length);

		if(result != PNG_NO_ERROR) break;
		
		file_read_ul(png, &length);

		if(length > old_len)
		{
			png_free(chunk); 
			chunk = png_alloc(length); 
			old_len = length;
		}

		if(file_read(png, &type, 1, 4) != 4)
		{
			result = PNG_FILE_ERROR;
			break;
		}

	}while(type == *(unsigned int*)"IDAT");

	if(type == *(unsigned int*)"IEND")
		result = PNG_DONE;

	png_free(chunk);
	png_end_inflate(png);

	return result;
}

static int png_process_chunk(png_t* png)
{
	int result = PNG_NO_ERROR;
	unsigned type;
	unsigned length;

	file_read_ul(png, &length);

	if(file_read(png, &type, 1, 4) != 4)
		return PNG_FILE_ERROR;

	if(type == *(unsigned int*)"IDAT")	/* if we found an idat, all other idats should be followed with no other chunks in between */
	{
		png->png_datalen = png->width * png->height * png->bpp + png->height;
		png->png_data = png_alloc(png->png_datalen);
		
		if(!png->png_data)
			return PNG_MEMORY_ERROR;

		return png_read_idat(png, length);
	}
	else if(type == *(unsigned int*)"IEND")
	{
		return PNG_DONE;
	}
	else
	{
		file_read(png, 0, 1, length + 4);		/* unknown chunk */
	}

	return result;
}

static void png_filter_sub(int stride, unsigned char* in, unsigned char* out, int len)
{
	int i;
	unsigned char a = 0;

	for(i = 0; i < len; i++)
	{
		if(i >= stride)
			a = out[i - stride];
		
		out[i] = in[i] + a;
	}
}

static void png_filter_up(int stride, unsigned char* in, unsigned char* out, unsigned char* prev_line, int len)
{
	int i;

	if(prev_line) 
    { 
        for(i = 0; i < len; i++) 
            out[i] = in[i] + prev_line[i]; 
    } 
    else 
        memcpy(out, in, len);
}

static void png_filter_average(int stride, unsigned char* in, unsigned char* out, unsigned char* prev_line, int len)
{
	int i;
	unsigned char a = 0;
	unsigned char b = 0;
	unsigned int sum = 0;

	for(i = 0; i < len; i++)
	{
		if(prev_line)
			b = prev_line[i];

		if(i >= stride)
			a = out[i - stride];

		sum = a;
		sum += b;

		out[i] = (char)(in[i] + sum/2);
	}
}

static unsigned char png_paeth(unsigned char a, unsigned char b, unsigned char c)
{
	int p = (int)a + b - c;
	int pa = abs(p - a);
	int pb = abs(p - b);
	int pc = abs(p - c);

	int pr;

	if(pa <= pb && pa <= pc)
		pr = a;
	else if(pb <= pc)
		pr = b;
	else
		pr = c;

	return (char)pr;
}

static void png_filter_paeth(int stride, unsigned char* in, unsigned char* out, unsigned char* prev_line, int len)
{
	int i;
	unsigned char a;
	unsigned char b;
	unsigned char c;

	for(i = 0; i < len; i++)
	{
		if(prev_line && i >= stride)
		{
			a = out[i - stride];
			b = prev_line[i];
			c = prev_line[i - stride];
		}
		else
		{
			if(prev_line)
				b = prev_line[i];
			else
				b = 0;
	
			if(i >= stride)
				a = out[i - stride];
			else
				a = 0;

			c = 0;
		}

		out[i] = in[i] + png_paeth(a, b, c);
	}
}

static int png_filter(png_t* png, unsigned char* data)
{


	return PNG_NO_ERROR;
}

static int png_unfilter(png_t* png, unsigned char* data)
{
	unsigned i;
	unsigned pos = 0;
	unsigned outpos = 0;
	unsigned char *filtered = png->png_data;

	int stride = png->bpp;

	while(pos < png->png_datalen)
	{
		unsigned char filter = filtered[pos];

		pos++;

		if(png->depth == 16)
		{
			for(i = 0; i < png->width * stride; i+=2)
			{
				*(short*)(filtered+pos+i) = (filtered[pos+i] << 8) | filtered[pos+i+1];
			}
		}

		switch(filter)
		{
		case 0: /* none */
			memcpy(data+outpos, filtered+pos, png->width * stride);
			break;
		case 1: /* sub */
			png_filter_sub(stride, filtered+pos, data+outpos, png->width * stride);
			break;
		case 2: /* up */
			if(outpos)
				png_filter_up(stride, filtered+pos, data+outpos, data + outpos - (png->width*stride), png->width*stride);
			else
				png_filter_up(stride, filtered+pos, data+outpos, 0, png->width*stride);
			break;
		case 3: /* average */
			if(outpos)
				png_filter_average(stride, filtered+pos, data+outpos, data + outpos - (png->width*stride), png->width*stride);
			else
				png_filter_average(stride, filtered+pos, data+outpos, 0, png->width*stride);
			break;
		case 4: /* paeth */
			if(outpos)
				png_filter_paeth(stride, filtered+pos, data+outpos, data + outpos - (png->width*stride), png->width*stride);
			else
				png_filter_paeth(stride, filtered+pos, data+outpos, 0, png->width*stride);
			break;
		default:
			return PNG_UNKNOWN_FILTER;
		}

		outpos += png->width * stride;
		pos += png->width * stride;
	}

	return PNG_NO_ERROR;
}

int png_get_data(png_t* png, unsigned char* data)
{
	int result = PNG_NO_ERROR;

	while(result == PNG_NO_ERROR)
	{
		result = png_process_chunk(png);
	}

	if(result != PNG_DONE)
	{
		png_free(png->png_data); 
		return result;
	}

	result = png_unfilter(png, data);

	png_free(png->png_data); 

	return result;
}

int png_set_data(png_t* png, unsigned width, unsigned height, char depth, int color, unsigned char* data)
{
	int i;
	unsigned char *filtered;
	png->width = width;
	png->height = height;
	png->depth = depth;
	png->color_type = color;
	png->bpp = png_get_bpp(png);

	filtered = png_alloc(width * height * png->bpp + height);

	for(i = 0; i < png->height; i++)
	{
		filtered[i*png->width*png->bpp+i] = 0;
		memcpy(&filtered[i*png->width*png->bpp+i+1], data + i * png->width*png->bpp, png->width*png->bpp);
	}

	png_filter(png, filtered);
	png_write_ihdr(png);
	png_write_idats(png, filtered);
	
	png_free(filtered);
	return PNG_NO_ERROR;
}


char* png_error_string(int error)
{
	switch(error)
	{
	case PNG_NO_ERROR:
		return "No error";
	case PNG_FILE_ERROR:
		return "Unknown file error.";
	case PNG_HEADER_ERROR:
		return "No PNG header found. Are you sure this is a PNG?";
	case PNG_IO_ERROR:
		return "Failure while reading file.";
	case PNG_EOF_ERROR:
		return "Reached end of file.";
	case PNG_CRC_ERROR:
		return "CRC or chunk length error.";
	case PNG_MEMORY_ERROR:
		return "Could not allocate memory.";
	case PNG_ZLIB_ERROR:
		return "zlib reported an error.";
	case PNG_UNKNOWN_FILTER:
		return "Unknown filter method used in scanline.";
	case PNG_DONE:
		return "PNG done";
	case PNG_NOT_SUPPORTED:
		return "The PNG is unsupported by pnglite, too bad for you!";
	case PNG_WRONG_ARGUMENTS:
		return "Wrong combination of arguments passed to png_open. You must use either a read_function or supply a file pointer to use.";
	default:
		return "Unknown error.";
	};
}
