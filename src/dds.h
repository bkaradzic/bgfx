/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __DDS_H__
#define __DDS_H__

#include <stdint.h>

namespace bgfx
{
	struct Dds
	{
		TextureFormat::Enum m_type;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_depth;
		uint8_t m_blockSize;
		uint8_t m_numMips;
		uint8_t m_bpp;
		bool m_hasAlpha;
		bool m_cubeMap;
	};

	struct Mip
	{
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_blockSize;
		uint32_t m_size;
		uint8_t m_bpp;
		uint8_t m_type;
		bool m_hasAlpha;
		const uint8_t* m_data;

		uint32_t getDecodedSize() const;
		void decode(uint8_t* _dst);
	};

	bool isDds(const Memory* _mem);
	bool parseDds(Dds& _dds, const Memory* _mem);
	bool getRawImageData(const Dds& _dds, uint8_t _side, uint8_t _index, const Memory* _mem, Mip& _mip);

} // namespace bgfx

#endif // __DDS_H__
