/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef AVIWRITER_H_HEADER_GUARD
#define AVIWRITER_H_HEADER_GUARD

#include <bx/readerwriter.h>

// Simple AVI writer. VideoLAN and VirtualDub can decode it.
// Needs some bits to get jiggled to work with other players. But it's good
// enough for an example.
struct AviWriter
{
	AviWriter(bx::FileWriterI* _writer)
		: m_writer(_writer)
		, m_frame(NULL)
		, m_frameSize(0)
		, m_numFrames(0)
		, m_width(0)
		, m_height(0)
		, m_yflip(false)
	{
	}

	bool open(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _fps, bool _yflip)
	{
		if (!bx::open(m_writer, _filePath) )
		{
			return false;
		}

		m_frameSize = _width * _height * 3;
		m_frame = new uint8_t[m_frameSize + 8];
		m_numFrames = 0;
		m_width = _width;
		m_height = _height;

		// Bgfx returns _yflip true for OpenGL since bottom left corner is 0, 0. In D3D top left corner
		// is 0, 0. DIB expect OpenGL style coordinates, so this is inverted logic for AVI writer.
		m_yflip = !_yflip;

		bx::Error err;

		bx::StaticMemoryBlockWriter mem(m_frame, 8);
		// Stream Data (LIST 'movi' Chunk) http://msdn.microsoft.com/en-us/library/ms899496.aspx
		bx::write(&mem, BX_MAKEFOURCC('0', '0', 'd', 'b'), &err);
		bx::write(&mem, m_frameSize, &err);

		bx::write(m_writer, BX_MAKEFOURCC('R', 'I', 'F', 'F'), &err);
		m_riffSizeOffset = m_writer->seek();
		bx::write(m_writer, uint32_t(0), &err);

		bx::write(m_writer, BX_MAKEFOURCC('A', 'V', 'I', ' '), &err);

		// AVI RIFF Form http://msdn.microsoft.com/en-us/library/ms899422.aspx
		bx::write(m_writer, BX_MAKEFOURCC('L', 'I', 'S', 'T'), &err);
		bx::write(m_writer, uint32_t(192), &err);
		bx::write(m_writer, BX_MAKEFOURCC('h', 'd', 'r', 'l'), &err);

		// AVI Main Header http://msdn.microsoft.com/en-us/library/ms779632.aspx
		bx::write(m_writer, BX_MAKEFOURCC('a', 'v', 'i', 'h'), &err);
		bx::write(m_writer, uint32_t(56), &err);
		bx::write(m_writer, uint32_t(0), &err);      // dwMicroSecPerFrame
		bx::write(m_writer, uint32_t(0), &err);      // dwMaxBytesPerSec
		bx::write(m_writer, uint32_t(0), &err);      // dwPaddingGranularity
		bx::write(m_writer, uint32_t(0x110), &err);  // dwFlags

		m_totalFramesOffset = m_writer->seek();
		bx::write(m_writer, uint32_t(0), &err);      // dwTotalFrames

		bx::write(m_writer, uint32_t(0), &err);      // dwInitialFrames
		bx::write(m_writer, uint32_t(1), &err);      // dwStreams
		bx::write(m_writer, uint32_t(0), &err);      // dwSuggestedBufferSize
		bx::write(m_writer, _width, &err);           // dwWidth
		bx::write(m_writer, _height, &err);          // dwHeight
		bx::write(m_writer, uint32_t(0), &err);      // dwReserved0
		bx::write(m_writer, uint32_t(0), &err);      // dwReserved1
		bx::write(m_writer, uint32_t(0), &err);      // dwReserved2
		bx::write(m_writer, uint32_t(0), &err);      // dwReserved3

		bx::write(m_writer, BX_MAKEFOURCC('L', 'I', 'S', 'T'), &err);
		bx::write(m_writer, uint32_t(116), &err);
		bx::write(m_writer, BX_MAKEFOURCC('s', 't', 'r', 'l'), &err);

		// AVISTREAMHEADER Structure http://msdn.microsoft.com/en-us/library/ms779638.aspx
		bx::write(m_writer, BX_MAKEFOURCC('s', 't', 'r', 'h'), &err);
		bx::write(m_writer, uint32_t(56), &err);
		// AVI Stream Headers http://msdn.microsoft.com/en-us/library/ms899423.aspx
		bx::write(m_writer, BX_MAKEFOURCC('v', 'i', 'd', 's'), &err); // fccType
		bx::write(m_writer, BX_MAKEFOURCC('D', 'I', 'B', ' '), &err); // fccHandler
		bx::write(m_writer, uint32_t(0), &err);      // dwFlags
		bx::write(m_writer, uint16_t(0), &err);      // wPriority
		bx::write(m_writer, uint16_t(0), &err);      // wLanguage
		bx::write(m_writer, uint32_t(0), &err);      // dwInitialFrames
		bx::write(m_writer, uint32_t(1), &err);      // dwScale
		bx::write(m_writer, _fps, &err);             // dwRate
		bx::write(m_writer, uint32_t(0), &err);      // dwStart

		m_lengthOffset = m_writer->seek();
		bx::write(m_writer, uint32_t(0), &err);      // dwLength

		bx::write(m_writer, m_frameSize, &err);      // dwSuggestedBufferSize
		bx::write(m_writer, UINT32_MAX, &err);       // dwQuality
		bx::write(m_writer, uint32_t(0), &err);      // dwSampleSize
		bx::write(m_writer, int16_t(0), &err);       // rcFrame.left
		bx::write(m_writer, int16_t(0), &err);       // rcFrame.top
		bx::write(m_writer, uint16_t(_width), &err); // rcFrame.right
		bx::write(m_writer, uint16_t(_height), &err);// rcFrame.bottom

		bx::write(m_writer, BX_MAKEFOURCC('s', 't', 'r', 'f'), &err);
		bx::write(m_writer, uint32_t(40), &err);

		// BITMAPINFOHEADER structure http://msdn.microsoft.com/en-us/library/windows/desktop/dd318229%28v=vs.85%29.aspx
		bx::write(m_writer, uint32_t(40), &err);     // biSize
		bx::write(m_writer, _width, &err);           // biWidth
		bx::write(m_writer, _height, &err);          // biHeight
		bx::write(m_writer, uint16_t(1), &err);      // biPlanes
		bx::write(m_writer, uint16_t(24), &err);     // biBitCount
		bx::write(m_writer, uint32_t(0), &err);      // biCompression
		bx::write(m_writer, m_frameSize, &err);      // biSizeImage
		bx::write(m_writer, uint32_t(0), &err);      // biXPelsPerMeter
		bx::write(m_writer, uint32_t(0), &err);      // biYPelsPerMeter
		bx::write(m_writer, uint32_t(0), &err);      // biClrUsed
		bx::write(m_writer, uint32_t(0), &err);      // biClrImportant

		bx::write(m_writer, BX_MAKEFOURCC('L', 'I', 'S', 'T'), &err);

		m_moviListOffset = m_writer->seek();
		bx::write(m_writer, uint32_t(0), &err);
		bx::write(m_writer, BX_MAKEFOURCC('m', 'o', 'v', 'i'), &err);

		return true;
	}

	void close()
	{
		if (NULL != m_frame)
		{
			bx::Error err;

			int64_t pos = m_writer->seek();
			m_writer->seek(m_moviListOffset, bx::Whence::Begin);
			bx::write(m_writer, uint32_t(pos-m_moviListOffset-4), &err);
			m_writer->seek(pos, bx::Whence::Begin);

			bx::write(m_writer, BX_MAKEFOURCC('i', 'd', 'x', '1'), &err);
			bx::write(m_writer, m_numFrames*16, &err);

			for (uint32_t ii = 0, offset = 4; ii < m_numFrames; ++ii)
			{
				bx::write(m_writer, BX_MAKEFOURCC('0', '0', 'd', 'b'), &err);
				bx::write(m_writer, uint32_t(16), &err);
				bx::write(m_writer, offset, &err);
				bx::write(m_writer, m_frameSize, &err);
				offset += m_frameSize + 8;
			}

			pos = m_writer->seek();
			m_writer->seek(m_riffSizeOffset, bx::Whence::Begin);
			bx::write(m_writer, uint32_t(pos-m_riffSizeOffset-4), &err);

			m_writer->seek(m_totalFramesOffset, bx::Whence::Begin);
			bx::write(m_writer, m_numFrames, &err);

			m_writer->seek(m_lengthOffset, bx::Whence::Begin);
			bx::write(m_writer, m_numFrames, &err);

			bx::close(m_writer);

			delete [] m_frame;
			m_frame = NULL;
			m_frameSize = 0;
		}
	}

	void frame(const void* _data)
	{
		if (NULL != m_frame)
		{
			++m_numFrames;
			uint32_t width = m_width;
			uint32_t height = m_height;

			uint8_t* bgr = &m_frame[8];

			if (m_yflip)
			{
				for (uint32_t yy = 0; yy < height; ++yy)
				{
					const uint8_t* bgra = (const uint8_t*)_data + (height-1-yy)*width*4;

					for (uint32_t ii = 0; ii < width; ++ii)
					{
						bgr[0] = bgra[0];
						bgr[1] = bgra[1];
						bgr[2] = bgra[2];
						bgr += 3;
						bgra += 4;
					}
				}
			}
			else
			{
				const uint8_t* bgra = (const uint8_t*)_data;
				for (uint32_t ii = 0, num = m_frameSize/3; ii < num; ++ii)
				{
					bgr[0] = bgra[0];
					bgr[1] = bgra[1];
					bgr[2] = bgra[2];
					bgr += 3;
					bgra += 4;
				}
			}

			bx::Error err;
			bx::write(m_writer, m_frame, m_frameSize+8, &err);
		}
	}

	bx::FileWriterI* m_writer;
	int64_t m_riffSizeOffset;
	int64_t m_totalFramesOffset;
	int64_t m_lengthOffset;
	int64_t m_moviListOffset;
	uint8_t* m_frame;
	uint32_t m_frameSize;
	uint32_t m_numFrames;
	uint32_t m_width;
	uint32_t m_height;
	bool m_yflip;
};

#endif // AVIWRITER_H_HEADER_GUARD
