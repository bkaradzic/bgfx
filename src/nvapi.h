/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_NVAPI_H_HEADER_GUARD
#define BGFX_NVAPI_H_HEADER_GUARD

namespace bgfx
{
	struct NvPhysicalGpuHandle;

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
		void getMemoryInfo(int64_t& _gpuMemoryUsed, int64_t& _gpuMemoryMax);

		void* m_nvApiDll;
		NvPhysicalGpuHandle* m_nvGpu;
	};

} // namespace bgfx

#endif // BGFX_NVAPI_H_HEADER_GUARD
