/*
 * Copyright (c) 2023 Wayve Technologies. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_CUDA_H_HEADER_GUARD
#define BGFX_CUDA_H_HEADER_GUARD

#include <bgfx/bgfx.h>

namespace bgfx
{
	void cudaInit(const uint8_t* _deviceUUID);

	void cudaImportImage(
		int _width,
		int _height,
		int _mips,
		TextureFormat::Enum _format,
		int _memoryHandle,
		uint64_t _memorySize,
		CudaImage* _cudaImage
	);

	void cudaDestroyImage(CudaImage* _cudaImage);
	void cudaCopyImage(const CudaImage* _srcImage, CudaImage* _dstImage);

	void cudaImportSemaphores(int _waitHandle, int _signalHandle, CudaSemaphore* _cudaSemaphore);
	void cudaDestroySemaphores(CudaSemaphore* _cudaSemaphore);

} // namespace bgfx

#endif // BGFX_CUDA_H_HEADER_GUARD
