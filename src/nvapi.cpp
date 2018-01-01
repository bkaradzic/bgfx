/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"
#include "nvapi.h"

namespace bgfx
{
	/*
	 * NVAPI
	 *
	 * Reference:
	 * http://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/index.html
	 * https://github.com/jNizM/AHK_NVIDIA_NvAPI/blob/master/info/NvAPI_IDs.txt
	 */
	struct NvPhysicalGpuHandle;

#define NVAPI_MAX_PHYSICAL_GPUS 64

#if BX_PLATFORM_WINDOWS
#	define NVAPICALL __cdecl
#else
#	define NVAPICALL
#endif // BX_PLATFORM_WINDOWS

	enum NvApiStatus
	{
		NVAPI_OK    =  0,
		NVAPI_ERROR = -1,
	};

	struct NvMemoryInfoV2
	{
		NvMemoryInfoV2()
			: version(sizeof(NvMemoryInfoV2) | (2 << 16) )
		{
		}

		uint32_t version;
		uint32_t dedicatedVideoMemory;
		uint32_t availableDedicatedVideoMemory;
		uint32_t systemVideoMemory;
		uint32_t sharedSystemMemory;
		uint32_t curAvailableDedicatedVideoMemory;
	};

	typedef void*       (NVAPICALL* PFN_NVAPI_QUERYINTERFACE)(uint32_t _functionOffset);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_INITIALIZE)();
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_UNLOAD)();
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_ENUMPHYSICALGPUS)(NvPhysicalGpuHandle* _handle[NVAPI_MAX_PHYSICAL_GPUS], uint32_t* _gpuCount);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_GPUGETMEMORYINFO)(NvPhysicalGpuHandle* _handle, NvMemoryInfoV2* _memoryInfo);
	typedef NvApiStatus (NVAPICALL* PFN_NVAPI_GPUGETFULLNAME)(NvPhysicalGpuHandle* _physicalGpu, char _name[64]);

#define NVAPI_INITIALIZE       UINT32_C(0x0150e828)
#define NVAPI_UNLOAD           UINT32_C(0xd22bdd7e)
#define NVAPI_ENUMPHYSICALGPUS UINT32_C(0xe5ac921f)
#define NVAPI_GPUGETMEMORYINFO UINT32_C(0x07f9b368)
#define NVAPI_GPUGETFULLNAME   UINT32_C(0xceee8e9f)

	static PFN_NVAPI_QUERYINTERFACE   nvApiQueryInterface;
	static PFN_NVAPI_INITIALIZE       nvApiInitialize;
	static PFN_NVAPI_UNLOAD           nvApiUnload;
	static PFN_NVAPI_ENUMPHYSICALGPUS nvApiEnumPhysicalGPUs;
	static PFN_NVAPI_GPUGETMEMORYINFO nvApiGpuGetMemoryInfo;
	static PFN_NVAPI_GPUGETFULLNAME   nvApiGpuGetFullName;

	NvApi::NvApi()
		: m_nvApiDll(NULL)
		, m_nvGpu(NULL)
	{
	}

	void NvApi::init()
	{
		m_nvGpu = NULL;
		m_nvApiDll = bx::dlopen(
#if BX_ARCH_32BIT
			"nvapi.dll"
#else
			"nvapi64.dll"
#endif // BX_ARCH_32BIT
			);

		if (NULL != m_nvApiDll)
		{
			nvApiQueryInterface = (PFN_NVAPI_QUERYINTERFACE)bx::dlsym(m_nvApiDll, "nvapi_QueryInterface");

			bool initialized = NULL != nvApiQueryInterface;

			if (initialized)
			{
				nvApiInitialize       = (PFN_NVAPI_INITIALIZE       )nvApiQueryInterface(NVAPI_INITIALIZE);
				nvApiUnload           = (PFN_NVAPI_UNLOAD           )nvApiQueryInterface(NVAPI_UNLOAD);
				nvApiEnumPhysicalGPUs = (PFN_NVAPI_ENUMPHYSICALGPUS )nvApiQueryInterface(NVAPI_ENUMPHYSICALGPUS);
				nvApiGpuGetMemoryInfo = (PFN_NVAPI_GPUGETMEMORYINFO )nvApiQueryInterface(NVAPI_GPUGETMEMORYINFO);
				nvApiGpuGetFullName   = (PFN_NVAPI_GPUGETFULLNAME   )nvApiQueryInterface(NVAPI_GPUGETFULLNAME);

				initialized = true
					&& NULL != nvApiInitialize
					&& NULL != nvApiUnload
					&& NULL != nvApiEnumPhysicalGPUs
					&& NULL != nvApiGpuGetMemoryInfo
					&& NULL != nvApiGpuGetFullName
					&& NVAPI_OK == nvApiInitialize()
					;

				if (initialized)
				{
					NvPhysicalGpuHandle* physicalGpus[NVAPI_MAX_PHYSICAL_GPUS];
					uint32_t numGpus = 0;
					nvApiEnumPhysicalGPUs(physicalGpus, &numGpus);

					initialized = 0 < numGpus;
					if (initialized)
					{
						m_nvGpu = physicalGpus[0];
					}

					char name[64];
					nvApiGpuGetFullName(m_nvGpu, name);
					BX_TRACE("%s", name);
				}

				initialized = NULL != m_nvGpu;

				if (!initialized)
				{
					nvApiUnload();
				}
			}

			if (!initialized)
			{
				bx::dlclose(m_nvApiDll);
				m_nvApiDll = NULL;
			}

			BX_WARN(!initialized, "NVAPI supported.");
		}
	}

	void NvApi::shutdown()
	{
		if (NULL != m_nvGpu)
		{
			nvApiUnload();
			m_nvGpu = NULL;
		}

		if (NULL != m_nvApiDll)
		{
			bx::dlclose(m_nvApiDll);
			m_nvApiDll = NULL;
		}
	}

	void NvApi::getMemoryInfo(int64_t& _gpuMemoryUsed, int64_t& _gpuMemoryMax)
	{
		if (NULL != m_nvGpu)
		{
			NvMemoryInfoV2 memInfo;
			NvApiStatus status = nvApiGpuGetMemoryInfo(m_nvGpu, &memInfo);
			if (NVAPI_OK == status)
			{
				_gpuMemoryMax  = 1024 *  memInfo.availableDedicatedVideoMemory;
				_gpuMemoryUsed = 1024 * (memInfo.availableDedicatedVideoMemory - memInfo.curAvailableDedicatedVideoMemory);
//				BX_TRACE("            dedicatedVideoMemory: %d KiB", memInfo.dedicatedVideoMemory);
//				BX_TRACE("   availableDedicatedVideoMemory: %d KiB", memInfo.availableDedicatedVideoMemory);
//				BX_TRACE("               systemVideoMemory: %d KiB", memInfo.systemVideoMemory);
//				BX_TRACE("              sharedSystemMemory: %d KiB", memInfo.sharedSystemMemory);
//				BX_TRACE("curAvailableDedicatedVideoMemory: %d KiB", memInfo.curAvailableDedicatedVideoMemory);
			}
		}
		else
		{
			_gpuMemoryMax  = -INT64_MAX;
			_gpuMemoryUsed = -INT64_MAX;
		}
	}

} // namespace bgfx
