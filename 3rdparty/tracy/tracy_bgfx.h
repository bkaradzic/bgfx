#ifndef TRACY_BGFX_H_HEADER_GUARD
#define TRACY_BGFX_H_HEADER_GUARD

// This header glues bgfx profiler macros to the Tracy profiler.

#define TRACY_ENABLE 1
#include "public/tracy/Tracy.hpp"

#define BGFX_ABGR_TO_RGB(_abgr) ((_abgr >> 8))

#define BGFX_PROFILER_TRACY_SCOPE(_name, _abgr)         \
	BX_PRAGMA_DIAGNOSTIC_PUSH();                        \
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow"); \
	ZoneScopedNC(_name, BGFX_ABGR_TO_RGB(_abgr));       \
	BX_PRAGMA_DIAGNOSTIC_POP()


tracy_force_inline void __bgfx_tracy_begin(uint32_t line, const char *source, size_t sourceSz, const char *function, size_t functionSz, const char *name, size_t nameSz, uint32_t _abgr) {
	using namespace tracy;
	TracyQueuePrepare( QueueType::ZoneBeginAllocSrcLocCallstack );
	const auto srcloc = Profiler::AllocSourceLocation( line, source, sourceSz, function, functionSz, name, nameSz, BGFX_ABGR_TO_RGB(_abgr) );
	MemWrite( &item->zoneBegin.time, Profiler::GetTime() );
	MemWrite( &item->zoneBegin.srcloc, srcloc );
	TracyQueueCommit( zoneBeginThread );
}

tracy_force_inline void __bgfx_tracy_end() {
	using namespace tracy;
	TracyQueuePrepare( QueueType::ZoneEnd );               \
	MemWrite( &item->zoneEnd.time, Profiler::GetTime() );  \
	TracyQueueCommit( zoneEndThread );                     \
}


#define BGFX_PROFILER_TRACY_BEGIN(_name, _abgr)                    \
	BX_MACRO_BLOCK_BEGIN                                           \
	__bgfx_tracy_begin(TracyLine                                   \
		              , TracyFile, bx::strLen( TracyFile )         \
		              , TracyFunction, bx::strLen( TracyFunction ) \
		              , _name, bx::strLen(_name)                   \
		              , _abgr                                      \
		              );                                           \
	BX_MACRO_BLOCK_END

#define BGFX_PROFILER_TRACY_BEGIN_LITERAL(_name, _abgr)            \
	BX_MACRO_BLOCK_BEGIN                                           \
		using namespace tracy;                                     \
		constexpr static SourceLocationData __tracy_source_location { nullptr, _name, __FILE__, (uint32_t)__LINE__, BGFX_ABGR_TO_RGB(_abgr) }; \
        TracyQueuePrepare( QueueType::ZoneBegin );                 \
        MemWrite( &item->zoneBegin.time, tracy::Profiler::GetTime() );    \
        MemWrite( &item->zoneBegin.srcloc, (uint64_t)&__tracy_source_location ); \
        TracyQueueCommit( zoneBeginThread ); \
	BX_MACRO_BLOCK_END

#define BGFX_PROFILER_TRACY_END()  __bgfx_tracy_end()
#endif // TRACY_BGFX_H_HEADER_GUARD
