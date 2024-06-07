#ifndef TRACY_BGFX_VULKAN_H_HEADER_GUARD
#define TRACY_BGFX_VULKAN_H_HEADER_GUARD

#define TRACY_VK_USE_SYMBOL_TABLE 1
#include "public/tracy/TracyVulkan.hpp"

tracy_force_inline void __bgfx_tracy_vulkan_begin_literal( tracy::VkCtx* m_ctx, const tracy::SourceLocationData* srcloc, VkCommandBuffer cmdbuf)
{
	using namespace tracy;
	const auto queryId = m_ctx->NextQueryId();
	CONTEXT_VK_FUNCTION_WRAPPER( vkCmdWriteTimestamp( cmdbuf, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_ctx->GetQueryPool(), queryId ) );

	auto item = Profiler::QueueSerial();
	MemWrite( &item->hdr.type, QueueType::GpuZoneBeginSerial );
	MemWrite( &item->gpuZoneBegin.cpuTime, Profiler::GetTime() );
	MemWrite( &item->gpuZoneBegin.srcloc, (uint64_t)srcloc );
	MemWrite( &item->gpuZoneBegin.thread, GetThreadHandle() );
	MemWrite( &item->gpuZoneBegin.queryId, uint16_t( queryId ) );
	MemWrite( &item->gpuZoneBegin.context, m_ctx->GetId() );
	Profiler::QueueSerialFinish();
}

tracy_force_inline void __bgfx_tracy_vulkan_begin( tracy::VkCtx* m_ctx, uint32_t line, const char* source, size_t sourceSz, const char* function, size_t functionSz, const char* name, size_t nameSz, uint32_t _abgr, VkCommandBuffer cmdbuf)
{
	using namespace tracy;

	const auto queryId = m_ctx->NextQueryId();
	CONTEXT_VK_FUNCTION_WRAPPER( vkCmdWriteTimestamp( cmdbuf, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_ctx->GetQueryPool(), queryId ) );

	const auto srcloc = Profiler::AllocSourceLocation( line, source, sourceSz, function, functionSz, name, nameSz, BGFX_ABGR_TO_RGB(_abgr) );
	auto item = Profiler::QueueSerial();
	MemWrite( &item->hdr.type, QueueType::GpuZoneBeginAllocSrcLocSerial );
	MemWrite( &item->gpuZoneBegin.cpuTime, Profiler::GetTime() );
	MemWrite( &item->gpuZoneBegin.srcloc, srcloc );
	MemWrite( &item->gpuZoneBegin.thread, GetThreadHandle() );
	MemWrite( &item->gpuZoneBegin.queryId, uint16_t( queryId ) );
	MemWrite( &item->gpuZoneBegin.context, m_ctx->GetId() );
	Profiler::QueueSerialFinish();
}

tracy_force_inline void __bgfx_tracy_vulkan_end( tracy::VkCtx *m_ctx, VkCommandBuffer cmdbuf)
{
	using namespace tracy;

	const auto queryId = m_ctx->NextQueryId();
	CONTEXT_VK_FUNCTION_WRAPPER( vkCmdWriteTimestamp( cmdbuf, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_ctx->GetQueryPool(), queryId ) );

	auto item = Profiler::QueueSerial();
	MemWrite( &item->hdr.type, QueueType::GpuZoneEndSerial );
	MemWrite( &item->gpuZoneEnd.cpuTime, Profiler::GetTime() );
	MemWrite( &item->gpuZoneEnd.thread, GetThreadHandle() );
	MemWrite( &item->gpuZoneEnd.queryId, uint16_t( queryId ) );
	MemWrite( &item->gpuZoneEnd.context, m_ctx->GetId() );
	Profiler::QueueSerialFinish();
}

#define BGFX_VK_PROFILER_TRACY_BEGIN(_name, _abgr, _ctx, _cmdBuf)         \
	__bgfx_tracy_vulkan_begin((tracy::VkCtx*)_ctx, TracyLine,             \
		                     , TracyFile, bx::strLen( TracyFile )         \
		                     , TracyFunction, bx::strLen( TracyFunction ) \
		                     , _name, bx::strLen(_name)                   \
		                     , _abgr, _cmdBuf                             \
							 )

#define BGFX_VK_PROFILER_TRACY_BEGIN_LITERAL(_name, _abgr, _ctx, _cmdBuf)                                                                             \
	BX_MACRO_BLOCK_BEGIN                                                                                                                              \
		BX_PRAGMA_DIAGNOSTIC_PUSH();                                                                                                                  \
		BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");                                                                                           \
		constexpr static tracy::SourceLocationData __tracy_source_location { nullptr, _name, __FILE__, (uint32_t)__LINE__, BGFX_ABGR_TO_RGB(_abgr) }; \
		BX_PRAGMA_DIAGNOSTIC_POP();                                                                                                                   \
		__bgfx_tracy_vulkan_begin_literal((tracy::VkCtx*)_ctx, &__tracy_source_location, _cmdBuf);                                                    \
	BX_MACRO_BLOCK_END

#define BGFX_VK_PROFILER_TRACY_END(_ctx, _cmdBuf) __bgfx_tracy_vulkan_end((tracy::VkCtx*)_ctx, _cmdBuf)

#endif
