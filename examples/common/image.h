/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef IMAGE_H_HEADER_GUARD
#define IMAGE_H_HEADER_GUARD

namespace bgfx
{
	///
	struct ImageContainer
	{
		bx::AllocatorI* m_allocator;
		void*           m_data;

		TextureFormat::Enum m_format;

		uint32_t m_size;
		uint32_t m_offset;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint16_t m_numLayers;
		uint8_t  m_numMips;
		bool     m_hasAlpha;
		bool     m_cubeMap;
		bool     m_ktx;
		bool     m_ktxLE;
		bool     m_srgb;
	};

	///
	ImageContainer* imageParse(
		  bx::AllocatorI* _allocator
		, const void* _data
		, uint32_t _size
		, TextureFormat::Enum _dstFormat = TextureFormat::Count
		);

	///
	ImageContainer* imageAlloc(
		  bx::AllocatorI* _allocator
		, TextureFormat::Enum _format
		, uint16_t _width
		, uint16_t _height
		, uint16_t _depth
		, uint16_t _numLayers
		, bool _cubeMap
		, bool _hasMips
		, const void* _data = NULL
		);

	///
	void imageFree(ImageContainer* _imageContainer);

	/// Converts format to string.
	const char* getName(TextureFormat::Enum _format);

} // namespace bgfx

#endif // IMAGE_H_HEADER_GUARD
