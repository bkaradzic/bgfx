/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "../bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NVN

#include "textures_samplers_pool.h"
#include <nvn/nvn.h>

namespace bgfx { namespace nvn
{
	void TexturesSamplersPool::init(NVNdevice* _device)
	{
		int textureSize = 0;
		int samplerSize = 0;
		int maxTextures = 0;
		int maxSamplers = 0;
		int totalNumSamplers = 0;
		int totalNumTextures = 0;

		/* Queries the size of a single texture/sampler descriptor. */
		nvnDeviceGetInteger(_device, NVN_DEVICE_INFO_TEXTURE_DESCRIPTOR_SIZE, &textureSize);
		nvnDeviceGetInteger(_device, NVN_DEVICE_INFO_SAMPLER_DESCRIPTOR_SIZE, &samplerSize);

		/*
		 * Grabs the number of texture/sampler entries that
		 * are reserved for internal use by NVN.
		 */
		nvnDeviceGetInteger(_device, NVN_DEVICE_INFO_RESERVED_TEXTURE_DESCRIPTORS, &m_numReservedTextures);
		nvnDeviceGetInteger(_device, NVN_DEVICE_INFO_RESERVED_SAMPLER_DESCRIPTORS, &m_numReservedSamplers);

		/*
		 * Grabs maximum number of texture/sampler entries
		 * allowed (including reserved entries)
		 */
		nvnDeviceGetInteger(_device, NVN_DEVICE_INFO_MAX_TEXTURE_POOL_SIZE, &maxTextures);
		nvnDeviceGetInteger(_device, NVN_DEVICE_INFO_MAX_SAMPLER_POOL_SIZE, &maxSamplers);

		/*
		 * The texture pool supports a max of 1048576 and the
		 * sampler pool supports a max of 4096 descriptors.
		 */
		totalNumTextures = m_numReservedTextures + BGFX_CONFIG_MAX_TEXTURES;
		totalNumSamplers = maxSamplers - m_numReservedSamplers;

		BX_ASSERT(totalNumTextures <= maxTextures, "The platform doesn't support the maximum number of textures. Desired: %d, Supported: %d", totalNumTextures, maxTextures);
		BX_ASSERT(totalNumSamplers <= maxSamplers, "The platform doesn't support the maximum number of samplers. Desired: %d, Supported: %d", totalNumSamplers, maxSamplers);

		m_pool.Init(nullptr, totalNumSamplers * samplerSize + totalNumTextures * textureSize, NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT, _device);

		/* Initialize the sampler pool. */
		const ptrdiff_t samplerPoolOffset = m_pool.GetNewMemoryChunkOffset(totalNumSamplers * samplerSize, samplerSize);
		NVNboolean samplerPoolSuccess = nvnSamplerPoolInitialize(&m_SamplerPool, m_pool.GetMemoryPool(), samplerPoolOffset, totalNumSamplers);
		BX_ASSERT(samplerPoolSuccess, "Failed to initialize Sampler descriptor pool");
		BX_UNUSED(samplerPoolSuccess);

		/* Initialize the texture pool. */
		const ptrdiff_t texturePoolOffset = m_pool.GetNewMemoryChunkOffset(totalNumTextures * textureSize, textureSize);
		NVNboolean texturePoolSuccess = nvnTexturePoolInitialize(&m_TexturePool, m_pool.GetMemoryPool(), texturePoolOffset, totalNumTextures);
		BX_ASSERT(texturePoolSuccess, "Failed to initialize Texture descriptor pool");
		BX_UNUSED(texturePoolSuccess);
	}

	void TexturesSamplersPool::shutdown()
	{
		m_pool.Shutdown();
	}

	void TexturesSamplersPool::set(const int _index, NVNsampler* _sampler)
	{
		nvnSamplerPoolRegisterSampler(&m_SamplerPool, m_numReservedSamplers + _index, _sampler);
	}

	void TexturesSamplersPool::set(const int _index, NVNtexture* _texture)
	{
		nvnTexturePoolRegisterTexture(&m_TexturePool, m_numReservedTextures + _index, _texture, nullptr);
	}

	void TexturesSamplersPool::bind(NVNcommandBuffer* _cmd)
	{
		nvnCommandBufferSetSamplerPool(_cmd, &m_SamplerPool);
		nvnCommandBufferSetTexturePool(_cmd, &m_TexturePool);
	}
} }

#endif // BGFX_CONFIG_RENDERER_NVN
