/*
 * Copyright (c) 2023 Wayve Technologies. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "cuda_interop.h"
#include "config.h"

#if BGFX_CONFIG_CUDA_INTEROP

#include <cuda.h>
#include <cuda_runtime.h>

#include <bx/bx.h>
#include <bimg/bimg.h>
#include <cstring>

namespace
{
	// CUDA helpers, modified from the NVidia CUDA samples (https://github.com/NVIDIA/cuda-samples)
	// Copyright (c) 2022, NVIDIA CORPORATION. All rights reserved.
	template <typename T>
	void check(T result, char const *const func, const char *const file,
						int const line) {
		// shuts up compiler warnings, for some reason BX_ASSERT doesn't count towards the arguments being used.
		BX_UNUSED(result);
		BX_UNUSED(func);
		BX_UNUSED(file);
		BX_UNUSED(line);

		BX_ASSERT(result == 0, "CUDA error at %s:%d code=%d(%s) \"%s\" \n", file, line,
						static_cast<unsigned int>(result), cudaGetErrorName(result), func);
	}

	#define checkCudaErrors(val) check((val), #val, __FILE__, __LINE__)


	cudaChannelFormatDesc makeCudaFormat(bgfx::TextureFormat::Enum _format)
	{
		cudaChannelFormatDesc formatDesc;

		switch (_format)
		{
			case bgfx::TextureFormat::RGBA8:
			case bgfx::TextureFormat::BGRA8:
				formatDesc.x = 8;
				formatDesc.y = 8;
				formatDesc.z = 8;
				formatDesc.w = 8;
				formatDesc.f = cudaChannelFormatKindUnsigned;

				break;

			case bgfx::TextureFormat::RGB8:
				formatDesc.x = 8;
				formatDesc.y = 8;
				formatDesc.z = 8;
				formatDesc.w = 0;
				formatDesc.f = cudaChannelFormatKindUnsigned;

				break;

			case bgfx::TextureFormat::RGBA16:
				formatDesc.x = 16;
				formatDesc.y = 16;
				formatDesc.z = 16;
				formatDesc.w = 16;
				formatDesc.f = cudaChannelFormatKindUnsigned;

				break;

			default:
				BX_TRACE("makeCudaFormat: texture format %d is not supported.", (int)_format);
				return formatDesc;
		}

		return formatDesc;
	}

}  // namespace

namespace bgfx
{
	void cudaInit(const uint8_t* _deviceUUID)
	{
		int deviceCount = 0;
		checkCudaErrors(cudaGetDeviceCount(&deviceCount));

		BX_ASSERT(deviceCount > 0, "CUDA Error: No devices found that support CUDA.");

		cudaDeviceProp deviceProp;
		for (int device = 0; device < deviceCount; ++device)
		{
			cudaGetDeviceProperties(&deviceProp, device);

			if (deviceProp.computeMode == cudaComputeModeProhibited)
				continue;

			if (0 == memcmp(&deviceProp.uuid, _deviceUUID, sizeof(deviceProp.uuid))) {
				checkCudaErrors(cudaSetDevice(device));
				return;
			}
		}

		BX_ASSERT(false, "CUDA Error: No devices found that support CUDA Interop.");
	}

	void cudaImportImage(int _width, int _height, int _mips, TextureFormat::Enum _format, int _memoryHandle, uint64_t _memorySize, CudaImage* _cudaImage)
	{
		_cudaImage->width = _width;
		_cudaImage->height = _height;
		_cudaImage->mips = _mips;
		_cudaImage->format = _format;

		cudaExternalMemoryHandleDesc mhd;
		mhd.type = cudaExternalMemoryHandleTypeOpaqueFd;
		mhd.handle.fd = _memoryHandle;
		mhd.size = _memorySize;
		mhd.flags = 0;

		cudaExternalMemory_t* memory = reinterpret_cast<cudaExternalMemory_t*>(&_cudaImage->externalMemory);
		cudaMipmappedArray_t* mipmappedArray = reinterpret_cast<cudaMipmappedArray_t*>(&_cudaImage->mipmappedArray);
		cudaArray_t* imageLayer = reinterpret_cast<cudaArray_t*>(&_cudaImage->array);

		checkCudaErrors(cudaImportExternalMemory(memory, &mhd) );

		cudaExtent extent = make_cudaExtent(_width, _height, 0);
		cudaChannelFormatDesc formatDesc = makeCudaFormat(_format);

		_cudaImage->channels = formatDesc.w > 0 ? 4 : 3;

		cudaExternalMemoryMipmappedArrayDesc mipArrayDesc;
		mipArrayDesc.offset = 0;
		mipArrayDesc.formatDesc = formatDesc;
		mipArrayDesc.extent = extent;
		mipArrayDesc.flags = 0;
		mipArrayDesc.numLevels = _mips;

		checkCudaErrors(
			cudaExternalMemoryGetMappedMipmappedArray(mipmappedArray, *memory, &mipArrayDesc)
		);

		// utility: get the base layer as it's the one most likely to be used, but the callers can manage image.mipmappedArray on their own
		checkCudaErrors(cudaGetMipmappedArrayLevel(imageLayer, *mipmappedArray, 0));
	}

	void cudaDestroyImage(CudaImage* _cudaImage)
	{
		if (!_cudaImage->isValid())
			return;

		cudaMipmappedArray_t mipmappedArray = reinterpret_cast<cudaMipmappedArray_t>(_cudaImage->mipmappedArray);
		cudaArray_t imageLayer = reinterpret_cast<cudaArray_t>(_cudaImage->array);

		checkCudaErrors(cudaFreeArray(imageLayer));
		checkCudaErrors(cudaFreeMipmappedArray(mipmappedArray));

		_cudaImage->array = NULL;
		_cudaImage->mipmappedArray = NULL;

		if (NULL != _cudaImage->externalMemory)
		{
			cudaExternalMemory_t memory = reinterpret_cast<cudaExternalMemory_t>(_cudaImage->externalMemory);
			checkCudaErrors(cudaDestroyExternalMemory(memory));
			_cudaImage->externalMemory = NULL;
		}
	}

	void cudaCopyImage(const CudaImage* _srcImage, CudaImage* _dstImage)
	{
		_dstImage->width = _srcImage->width;
		_dstImage->height = _srcImage->height;
		_dstImage->channels = _srcImage->channels;
		_dstImage->mips = _srcImage->mips;
		_dstImage->format = _srcImage->format;

		const cudaMipmappedArray_t srcMipmappedArray = reinterpret_cast<cudaMipmappedArray_t>(_srcImage->mipmappedArray);
		cudaMipmappedArray_t* dstMipmappedArray = reinterpret_cast<cudaMipmappedArray_t*>(&_dstImage->mipmappedArray);

		cudaExtent extent = make_cudaExtent(_dstImage->width, _dstImage->height, 0);
		cudaChannelFormatDesc formatDesc = makeCudaFormat(_dstImage->format );

		checkCudaErrors(cudaMallocMipmappedArray(dstMipmappedArray, &formatDesc, extent, _dstImage->mips));

		for (int mipLevel = 0; mipLevel < _dstImage->mips; ++mipLevel) {
			cudaArray_t srcArray, dstArray;

			checkCudaErrors(cudaGetMipmappedArrayLevel(&srcArray, srcMipmappedArray, mipLevel));
      checkCudaErrors(cudaGetMipmappedArrayLevel(&dstArray, *dstMipmappedArray, mipLevel));

			uint32_t levelWidth = (_dstImage->width >> mipLevel) ? (_dstImage->width >> mipLevel) : 1;
      uint32_t levelHeight = (_dstImage->height >> mipLevel) ? (_dstImage->height >> mipLevel) : 1;
			const uint8_t channels = bimg::getBitsPerPixel((bimg::TextureFormat::Enum)_dstImage->format ) / 8;

			checkCudaErrors(cudaMemcpy2DArrayToArray(dstArray, 0, 0, srcArray, 0, 0, levelWidth * channels, levelHeight, cudaMemcpyDeviceToDevice));
		}

		// utility: get the base layer as it's the one most likely to be used, but the callers can manage image.mipmappedArray on their own
		cudaArray_t* dstImageLayer = reinterpret_cast<cudaArray_t*>(&_dstImage->array);
		checkCudaErrors(cudaGetMipmappedArrayLevel(dstImageLayer, *dstMipmappedArray, 0));
	}

	void cudaImportSemaphores(int _waitHandle, int _signalHandle, CudaSemaphore* _cudaSemaphore)
	{
		cudaExternalSemaphoreHandleDesc shd;
		shd.type = cudaExternalSemaphoreHandleTypeOpaqueFd;
		shd.handle.fd = _waitHandle;
		shd.flags = 0;

		cudaExternalSemaphore_t* cudaWaitSemaphore = reinterpret_cast<cudaExternalSemaphore_t*>(&_cudaSemaphore->waitSemaphore);
		checkCudaErrors(cudaImportExternalSemaphore(cudaWaitSemaphore, &shd));

		shd.handle.fd = _signalHandle;
		cudaExternalSemaphore_t* cudaSignalSemaphore = reinterpret_cast<cudaExternalSemaphore_t*>(&_cudaSemaphore->signalSemaphore);
		checkCudaErrors(cudaImportExternalSemaphore(cudaSignalSemaphore, &shd));
	}

	void cudaDestroySemaphores(CudaSemaphore* _cudaSemaphore)
	{
		if (NULL != _cudaSemaphore->waitSemaphore)
		{
			cudaExternalSemaphore_t cudaWaitSemaphore = reinterpret_cast<cudaExternalSemaphore_t>(_cudaSemaphore->waitSemaphore);
			checkCudaErrors(cudaDestroyExternalSemaphore(cudaWaitSemaphore));
			_cudaSemaphore->waitSemaphore = NULL;
		}
		if (NULL != _cudaSemaphore->signalSemaphore)
		{
			cudaExternalSemaphore_t cudaSignalSemaphore = reinterpret_cast<cudaExternalSemaphore_t>(_cudaSemaphore->signalSemaphore);
    	checkCudaErrors(cudaDestroyExternalSemaphore(cudaSignalSemaphore));
			_cudaSemaphore->signalSemaphore = NULL;
		}

	}

} // namespace bgfx

#else

namespace bgfx {

	void cudaInit(const uint8_t* /*_deviceUUID*/)
	{
	}

	void cudaImportImage(int /*_width*/, int /*_height*/, int /*_mips*/, TextureFormat::Enum /*_format*/, int /*_memoryHandle*/, uint64_t /*_memorySize*/, CudaImage* /*_cudaImage*/)
	{
	}

	void cudaDestroyImage(CudaImage* /*cudaImage*/)
	{
	}

	void cudaCopyImage(const CudaImage* /*srcImage*/, CudaImage* /*dstImage*/)
	{
	}

	void cudaImportSemaphores(int /*_waitHandle*/, int /*_signalHandle*/, CudaSemaphore* /*_cudaSemaphore*/)
	{
	}

	void cudaDestroySemaphores(CudaSemaphore* /*_cudaSemaphore*/)
	{
	}

}  // namespace bgfx

#endif // BGFX_CONFIG_CUDA_INTEROP
