/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_NVAPI_H_HEADER_GUARD
#define BGFX_NVAPI_H_HEADER_GUARD

struct ID3D11DeviceContext;
struct ID3D11Buffer;

namespace bgfx
{
	struct NvPhysicalGpuHandle;

	typedef void (* NvMultiDrawIndirectFn)(ID3D11DeviceContext* _deviceCtx, uint32_t _numDrawIndirect, ID3D11Buffer* _ptr, uint32_t _offset, uint32_t _stride);

	///
	struct NvApi
	{
		///
		NvApi();

		///
		void init();

		///
		void shutdown();

		///
		bool isInitialized() const { return NULL != m_nvGpu; }

		///
		void getMemoryInfo(int64_t& _gpuMemoryUsed, int64_t& _gpuMemoryMax);

		///
		void* m_nvApiDll;
		NvPhysicalGpuHandle* m_nvGpu;

		NvMultiDrawIndirectFn nvApiD3D11MultiDrawInstancedIndirect;
		NvMultiDrawIndirectFn nvApiD3D11MultiDrawIndexedInstancedIndirect;
	};

} // namespace bgfx

#endif // BGFX_NVAPI_H_HEADER_GUARD
