/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#ifndef BGFX_RENDERER_NVN_H_HEADER_GUARD
#define BGFX_RENDERER_NVN_H_HEADER_GUARD

#include <atomic>
#include <array>
#include <vector>

BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunknown-pragmas");
BX_PRAGMA_DIAGNOSTIC_IGNORED_GCC("-Wpragmas");
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4005) // warning C4005: '' : macro redefinition
#include <nn/vi.h>
#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrImpl.h>
#include <nn/mem/mem_StandardAllocator.h>
#include <nn/perf/perf_Profile.h>
#include <nn/oe.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#include "renderer.h"
#include "renderer_nvn/memory.h"
#include "renderer_nvn/textures_samplers_pool.h"

namespace bgfx { namespace nvn
{

	struct TimerQueryNVN
	{
		static constexpr uint32_t kQueryStride = sizeof(NVNcounterData); // nvnCommandBufferReportCounter writes 16 bytes, usually 2 uint64_t except for zcull stats which is 4 uint32_t

		TimerQueryNVN()
			: m_control(BX_COUNTOF(m_query))
		{
		}

		bool init();
		void destroy();

		uint32_t begin(uint32_t _resultIdx);
		void end(uint32_t _idx);

		void update();

		struct Result
		{
			void reset()
			{
				m_begin = 0;
				m_end = 0;
				m_pending = 0;
			}

			uint64_t m_begin;
			uint64_t m_end;
			uint32_t m_pending;
		};

		struct Query
		{
			bool m_ready;
			uint32_t m_resultIdx;
			uint32_t m_completed;
		};

		int64_t m_frequency;

		Result m_result[BGFX_CONFIG_MAX_VIEWS + 1];
		Query m_query[BGFX_CONFIG_MAX_VIEWS * 4];

		BufferNVN m_buffer;
		bx::RingBufferControl m_control;
	};

} }

#endif // BGFX_RENDERER_NVN_H_HEADER_GUARD
