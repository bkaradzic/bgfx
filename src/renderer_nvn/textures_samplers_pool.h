/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_NVN_TEXTURES_SAMPLERS_POOL_H_HEADER_GUARD
#define BGFX_NVN_TEXTURES_SAMPLERS_POOL_H_HEADER_GUARD

#include "memory.h"
#include <nvn/nvn.h>

namespace bgfx { namespace nvn
{
	struct TexturesSamplersPool
	{
		void init(NVNdevice* _device);
		void shutdown();

		void set(const int _index, NVNsampler* _sampler);
		void set(const int _index, NVNtexture* _texture);

		int getSamplerID(const int _index)
		{
			return _index + m_numReservedSamplers;
		}

		int getTextureID(const int _index)
		{
			return _index + m_numReservedTextures;
		}

		void bind(NVNcommandBuffer* _cmd);

		MemoryPool			m_pool;
		NVNtexturePool      m_TexturePool;
		NVNsamplerPool      m_SamplerPool;

		int m_numReservedTextures = 0;
		int m_numReservedSamplers = 0;
	};
} }

#endif // BGFX_NVN_TEXTURES_SAMPLERS_POOL_H_HEADER_GUARD
