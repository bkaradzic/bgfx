#include <limits>
#include <new>
#include <stdio.h>
#include <string.h>
#include "TracyCallstack.hpp"
#include "TracyDebug.hpp"
#include "TracyFastVector.hpp"
#include "TracyStringHelpers.hpp"
#include "../common/TracyAlloc.hpp"
#include "../common/TracySystem.hpp"


#ifdef TRACY_HAS_CALLSTACK

#if TRACY_HAS_CALLSTACK == 1
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  include <windows.h>
#  include <psapi.h>
#  include <algorithm>
#  ifdef _MSC_VER
#    pragma warning( push )
#    pragma warning( disable : 4091 )
#  endif
#  include <dbghelp.h>
#  ifdef _MSC_VER
#    pragma warning( pop )
#  endif
#elif TRACY_HAS_CALLSTACK == 2 || TRACY_HAS_CALLSTACK == 3 || TRACY_HAS_CALLSTACK == 4 || TRACY_HAS_CALLSTACK == 6
#  include "../libbacktrace/backtrace.hpp"
#  include <algorithm>
#  include <dlfcn.h>
#  include <cxxabi.h>
#  include <stdlib.h>
#elif TRACY_HAS_CALLSTACK == 5
#  include <dlfcn.h>
#  include <cxxabi.h>
#endif

#ifdef TRACY_DBGHELP_LOCK
#  include "TracyProfiler.hpp"

#  define DBGHELP_INIT TracyConcat( TRACY_DBGHELP_LOCK, Init() )
#  define DBGHELP_LOCK TracyConcat( TRACY_DBGHELP_LOCK, Lock() );
#  define DBGHELP_UNLOCK TracyConcat( TRACY_DBGHELP_LOCK, Unlock() );

extern "C"
{
    void DBGHELP_INIT;
    void DBGHELP_LOCK;
    void DBGHELP_UNLOCK;
};
#endif

#if TRACY_HAS_CALLSTACK == 2 || TRACY_HAS_CALLSTACK == 3 || TRACY_HAS_CALLSTACK == 4 || TRACY_HAS_CALLSTACK == 5 || TRACY_HAS_CALLSTACK == 6
// If you want to use your own demangling functionality (e.g. for another language),
// define TRACY_DEMANGLE and provide your own implementation of the __tracy_demangle
// function. The input parameter is a function name. The demangle function must
// identify whether this name is mangled, and fail if it is not. Failure is indicated
// by returning nullptr. If demangling succeeds, a pointer to the C string containing
// demangled function must be returned. The demangling function is responsible for
// managing memory for this string. It is expected that it will be internally reused.
// When a call to ___tracy_demangle is made, previous contents of the string memory
// do not need to be preserved. Function may return string of any length, but the
// profiler can choose to truncate it.
extern "C" const char* ___tracy_demangle( const char* mangled );

#ifndef TRACY_DEMANGLE
constexpr size_t ___tracy_demangle_buffer_len = 1024*1024;
char* ___tracy_demangle_buffer;

void ___tracy_init_demangle_buffer()
{
    ___tracy_demangle_buffer = (char*)tracy::tracy_malloc( ___tracy_demangle_buffer_len );
}

void ___tracy_free_demangle_buffer()
{
    tracy::tracy_free( ___tracy_demangle_buffer );
}

extern "C" const char* ___tracy_demangle( const char* mangled )
{
    if( !mangled || mangled[0] != '_' ) return nullptr;
    if( strlen( mangled ) > ___tracy_demangle_buffer_len ) return nullptr;
    int status;
    size_t len = ___tracy_demangle_buffer_len;
    return abi::__cxa_demangle( mangled, ___tracy_demangle_buffer, &len, &status );
}
#endif
#endif

#if TRACY_HAS_CALLSTACK == 3
#   define TRACY_USE_IMAGE_CACHE
#   include <link.h>
#endif

namespace tracy
{

#ifdef TRACY_USE_IMAGE_CACHE
// when we have access to dl_iterate_phdr(), we can build a cache of address ranges to image paths
// so we can quickly determine which image an address falls into.
// We refresh this cache only when we hit an address that doesn't fall into any known range.
class ImageCache
{
public:
    struct ImageEntry
    {
        void* m_startAddress = nullptr;
        void* m_endAddress = nullptr;
        char* m_name = nullptr;
    };

    ImageCache()
        : m_images( 512 )
    {
        Refresh();
    }

    ~ImageCache()
    {
        Clear();
    }

    const ImageEntry* GetImageForAddress( void* address )
    {
        const ImageEntry* entry = GetImageForAddressImpl( address );
        if( !entry )
        {
            Refresh();
            return GetImageForAddressImpl( address );
        }
        return entry;
    }

private:
    tracy::FastVector<ImageEntry> m_images;
    bool m_updated = false;
    bool m_haveMainImageName = false;

    static int Callback( struct dl_phdr_info* info, size_t size, void* data )
    {
        ImageCache* cache = reinterpret_cast<ImageCache*>( data );

        const auto startAddress = reinterpret_cast<void*>( info->dlpi_addr );
        if( cache->Contains( startAddress ) ) return 0;

        const uint32_t headerCount = info->dlpi_phnum;
        assert( headerCount > 0);
        const auto endAddress = reinterpret_cast<void*>( info->dlpi_addr +
            info->dlpi_phdr[info->dlpi_phnum - 1].p_vaddr + info->dlpi_phdr[info->dlpi_phnum - 1].p_memsz);

        ImageEntry* image = cache->m_images.push_next();
        image->m_startAddress = startAddress;
        image->m_endAddress = endAddress;

        // the base executable name isn't provided when iterating with dl_iterate_phdr,
        // we will have to patch the executable image name outside this callback
        if( info->dlpi_name && info->dlpi_name[0] != '\0' )
        {
            size_t sz = strlen( info->dlpi_name ) + 1;
            image->m_name = (char*)tracy_malloc( sz );
            memcpy( image->m_name,  info->dlpi_name, sz );
        }
        else
        {
            image->m_name = nullptr;
        }

        cache->m_updated = true;

        return 0;
    }

    bool Contains( void* startAddress ) const
    {
        return std::any_of( m_images.begin(), m_images.end(), [startAddress]( const ImageEntry& entry ) { return startAddress == entry.m_startAddress; } );
    }

    void Refresh()
    {
        m_updated = false;
        dl_iterate_phdr( Callback, this );

        if( m_updated )
        {
            std::sort( m_images.begin(), m_images.end(),
                []( const ImageEntry& lhs, const ImageEntry& rhs ) { return lhs.m_startAddress > rhs.m_startAddress; } );

            // patch the main executable image name here, as calling dl_* functions inside the dl_iterate_phdr callback might cause deadlocks
            UpdateMainImageName();
        }
    }

    void UpdateMainImageName()
    {
        if( m_haveMainImageName )
        {
            return;
        }

        for( ImageEntry& entry : m_images )
        {
            if( entry.m_name == nullptr )
            {
                Dl_info dlInfo;
                if( dladdr( (void *)entry.m_startAddress, &dlInfo ) )
                {
                    if( dlInfo.dli_fname )
                    {
                        size_t sz = strlen( dlInfo.dli_fname ) + 1;
                        entry.m_name = (char*)tracy_malloc( sz );
                        memcpy( entry.m_name, dlInfo.dli_fname, sz );
                    }
                }

                // we only expect one entry to be null for the main executable entry
                break;
            }
        }

        m_haveMainImageName = true;
    }

    const ImageEntry* GetImageForAddressImpl( void* address ) const
    {
        auto it = std::lower_bound( m_images.begin(), m_images.end(), address,
            []( const ImageEntry& lhs, const void* rhs ) { return lhs.m_startAddress > rhs; } );

        if( it != m_images.end() && address < it->m_endAddress )
        {
            return it;
        }
        return nullptr;
    }

    void Clear()
    {
        for( ImageEntry& entry : m_images )
        {
            tracy_free( entry.m_name );
        }

        m_images.clear();
        m_haveMainImageName = false;
    }
};
#endif //#ifdef TRACY_USE_IMAGE_CACHE

// when "TRACY_SYMBOL_OFFLINE_RESOLVE" is set, instead of fully resolving symbols at runtime,
// simply resolve the offset and image name (which will be enough the resolving to be done offline)
#ifdef TRACY_SYMBOL_OFFLINE_RESOLVE
constexpr bool s_shouldResolveSymbolsOffline = true;
#else
static bool s_shouldResolveSymbolsOffline = false;
bool ShouldResolveSymbolsOffline()
{
    const char* symbolOfflineResolve = GetEnvVar( "TRACY_SYMBOL_OFFLINE_RESOLVE" );
    return (symbolOfflineResolve && symbolOfflineResolve[0] == '1');
}
#endif // #ifdef TRACY_SYMBOL_OFFLINE_RESOLVE

#if TRACY_HAS_CALLSTACK == 1

enum { MaxCbTrace = 64 };
enum { MaxNameSize = 8*1024 };

int cb_num;
CallstackEntry cb_data[MaxCbTrace];

extern "C"
{
    typedef DWORD (__stdcall *t_SymAddrIncludeInlineTrace)( HANDLE hProcess, DWORD64 Address );
    typedef BOOL (__stdcall *t_SymQueryInlineTrace)( HANDLE hProcess, DWORD64 StartAddress, DWORD StartContext, DWORD64 StartRetAddress, DWORD64 CurAddress, LPDWORD CurContext, LPDWORD CurFrameIndex );
    typedef BOOL (__stdcall *t_SymFromInlineContext)( HANDLE hProcess, DWORD64 Address, ULONG InlineContext, PDWORD64 Displacement, PSYMBOL_INFO Symbol );
    typedef BOOL (__stdcall *t_SymGetLineFromInlineContext)( HANDLE hProcess, DWORD64 qwAddr, ULONG InlineContext, DWORD64 qwModuleBaseAddress, PDWORD pdwDisplacement, PIMAGEHLP_LINE64 Line64 );

    t_SymAddrIncludeInlineTrace _SymAddrIncludeInlineTrace = 0;
    t_SymQueryInlineTrace _SymQueryInlineTrace = 0;
    t_SymFromInlineContext _SymFromInlineContext = 0;
    t_SymGetLineFromInlineContext _SymGetLineFromInlineContext = 0;

    TRACY_API ___tracy_t_RtlWalkFrameChain ___tracy_RtlWalkFrameChain = 0;
}

struct ModuleCache
{
    uint64_t start;
    uint64_t end;
    char* name;
};

static FastVector<ModuleCache>* s_modCache;


struct KernelDriver
{
    uint64_t addr;
    const char* mod;
    const char* path;
};

KernelDriver* s_krnlCache = nullptr;
size_t s_krnlCacheCnt;

void InitCallstackCritical()
{
    ___tracy_RtlWalkFrameChain = (___tracy_t_RtlWalkFrameChain)GetProcAddress( GetModuleHandleA( "ntdll.dll" ), "RtlWalkFrameChain" );
}

void DbgHelpInit()
{
    if( s_shouldResolveSymbolsOffline ) return;

    _SymAddrIncludeInlineTrace = (t_SymAddrIncludeInlineTrace)GetProcAddress(GetModuleHandleA("dbghelp.dll"), "SymAddrIncludeInlineTrace");
    _SymQueryInlineTrace = (t_SymQueryInlineTrace)GetProcAddress(GetModuleHandleA("dbghelp.dll"), "SymQueryInlineTrace");
    _SymFromInlineContext = (t_SymFromInlineContext)GetProcAddress(GetModuleHandleA("dbghelp.dll"), "SymFromInlineContext");
    _SymGetLineFromInlineContext = (t_SymGetLineFromInlineContext)GetProcAddress(GetModuleHandleA("dbghelp.dll"), "SymGetLineFromInlineContext");

#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_INIT;
    DBGHELP_LOCK;
#endif

    SymInitialize( GetCurrentProcess(), nullptr, true );
    SymSetOptions( SYMOPT_LOAD_LINES );

#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_UNLOCK;
#endif
}

DWORD64 DbgHelpLoadSymbolsForModule( const char* imageName, uint64_t baseOfDll, uint32_t bllSize )
{
    if( s_shouldResolveSymbolsOffline ) return 0;
    return SymLoadModuleEx( GetCurrentProcess(), nullptr, imageName, nullptr, baseOfDll, bllSize, nullptr, 0 );
}

ModuleCache* LoadSymbolsForModuleAndCache( const char* imageName, uint32_t imageNameLength, uint64_t baseOfDll, uint32_t dllSize )
{
    DbgHelpLoadSymbolsForModule( imageName, baseOfDll, dllSize );

    ModuleCache* cachedModule = s_modCache->push_next();
    cachedModule->start = baseOfDll;
    cachedModule->end = baseOfDll + dllSize;

    // when doing offline symbol resolution, we must store the full path of the dll for the resolving to work
    if( s_shouldResolveSymbolsOffline )
    {
        cachedModule->name = (char*)tracy_malloc_fast(imageNameLength + 1);
        memcpy(cachedModule->name, imageName, imageNameLength);
        cachedModule->name[imageNameLength] = '\0';
    }
    else
    {
        auto ptr = imageName + imageNameLength;
        while (ptr > imageName && *ptr != '\\' && *ptr != '/') ptr--;
        if (ptr > imageName) ptr++;
        const auto namelen = imageName + imageNameLength - ptr;
        cachedModule->name = (char*)tracy_malloc_fast(namelen + 3);
        cachedModule->name[0] = '[';
        memcpy(cachedModule->name + 1, ptr, namelen);
        cachedModule->name[namelen + 1] = ']';
        cachedModule->name[namelen + 2] = '\0';
    }

    return cachedModule;
}

void InitCallstack()
{
#ifndef TRACY_SYMBOL_OFFLINE_RESOLVE
    s_shouldResolveSymbolsOffline = ShouldResolveSymbolsOffline();
#endif //#ifndef TRACY_SYMBOL_OFFLINE_RESOLVE
    if( s_shouldResolveSymbolsOffline )
    {
        TracyDebug("TRACY: enabling offline symbol resolving!\n");
    }

    DbgHelpInit();

#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_LOCK;
#endif

    // use TRACY_NO_DBGHELP_INIT_LOAD=1 to disable preloading of driver
    // and process module symbol loading at startup time - they will be loaded on demand later
    // Sometimes this process can take a very long time and prevent resolving callstack frames
    // symbols during that time.
    const char* noInitLoadEnv = GetEnvVar( "TRACY_NO_DBGHELP_INIT_LOAD" );
    const bool initTimeModuleLoad = !( noInitLoadEnv && noInitLoadEnv[0] == '1' );
    if ( !initTimeModuleLoad )
    {
        TracyDebug("TRACY: skipping init time dbghelper module load\n");
    }

    DWORD needed;
    LPVOID dev[4096];
    if( initTimeModuleLoad && EnumDeviceDrivers( dev, sizeof(dev), &needed ) != 0 )
    {
        char windir[MAX_PATH];
        if( !GetWindowsDirectoryA( windir, sizeof( windir ) ) ) memcpy( windir, "c:\\windows", 11 );
        const auto windirlen = strlen( windir );

        const auto sz = needed / sizeof( LPVOID );
        s_krnlCache = (KernelDriver*)tracy_malloc( sizeof(KernelDriver) * sz );
        int cnt = 0;
        for( size_t i=0; i<sz; i++ )
        {
            char fn[MAX_PATH];
            const auto len = GetDeviceDriverBaseNameA( dev[i], fn, sizeof( fn ) );
            if( len != 0 )
            {
                auto buf = (char*)tracy_malloc_fast( len+3 );
                buf[0] = '<';
                memcpy( buf+1, fn, len );
                memcpy( buf+len+1, ">", 2 );
                s_krnlCache[cnt] = KernelDriver { (uint64_t)dev[i], buf };

                const auto len = GetDeviceDriverFileNameA( dev[i], fn, sizeof( fn ) );
                if( len != 0 )
                {
                    char full[MAX_PATH];
                    char* path = fn;

                    if( memcmp( fn, "\\SystemRoot\\", 12 ) == 0 )
                    {
                        memcpy( full, windir, windirlen );
                        strcpy( full + windirlen, fn + 11 );
                        path = full;
                    }

                    DbgHelpLoadSymbolsForModule( path, (DWORD64)dev[i], 0 );

                    const auto psz = strlen( path );
                    auto pptr = (char*)tracy_malloc_fast( psz+1 );
                    memcpy( pptr, path, psz );
                    pptr[psz] = '\0';
                    s_krnlCache[cnt].path = pptr;
                }

                cnt++;
            }
        }
        s_krnlCacheCnt = cnt;
        std::sort( s_krnlCache, s_krnlCache + s_krnlCacheCnt, []( const KernelDriver& lhs, const KernelDriver& rhs ) { return lhs.addr > rhs.addr; } );
    }

    s_modCache = (FastVector<ModuleCache>*)tracy_malloc( sizeof( FastVector<ModuleCache> ) );
    new(s_modCache) FastVector<ModuleCache>( 512 );

    HANDLE proc = GetCurrentProcess();
    HMODULE mod[1024];
    if( initTimeModuleLoad && EnumProcessModules( proc, mod, sizeof( mod ), &needed ) != 0 )
    {
        const auto sz = needed / sizeof( HMODULE );
        for( size_t i=0; i<sz; i++ )
        {
            MODULEINFO info;
            if( GetModuleInformation( proc, mod[i], &info, sizeof( info ) ) != 0 )
            {
                char name[1024];
                const auto nameLength = GetModuleFileNameA( mod[i], name, 1021 );
                if( nameLength > 0 )
                {
                    // This may be a new module loaded since our call to SymInitialize.
                    // Just in case, force DbgHelp to load its pdb !
                    LoadSymbolsForModuleAndCache( name, nameLength, (DWORD64)info.lpBaseOfDll, info.SizeOfImage );
                }
            }
        }
    }

#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_UNLOCK;
#endif
}

void EndCallstack()
{
}

const char* DecodeCallstackPtrFast( uint64_t ptr )
{
    if( s_shouldResolveSymbolsOffline ) return "[unresolved]";

    static char ret[MaxNameSize];
    const auto proc = GetCurrentProcess();

    char buf[sizeof( SYMBOL_INFO ) + MaxNameSize];
    auto si = (SYMBOL_INFO*)buf;
    si->SizeOfStruct = sizeof( SYMBOL_INFO );
    si->MaxNameLen = MaxNameSize;

#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_LOCK;
#endif
    if( SymFromAddr( proc, ptr, nullptr, si ) == 0 )
    {
        *ret = '\0';
    }
    else
    {
        memcpy( ret, si->Name, si->NameLen );
        ret[si->NameLen] = '\0';
    }
#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_UNLOCK;
#endif
    return ret;
}

const char* GetKernelModulePath( uint64_t addr )
{
    assert( addr >> 63 != 0 );
    if( !s_krnlCache ) return nullptr;
    auto it = std::lower_bound( s_krnlCache, s_krnlCache + s_krnlCacheCnt, addr, []( const KernelDriver& lhs, const uint64_t& rhs ) { return lhs.addr > rhs; } );
    if( it == s_krnlCache + s_krnlCacheCnt ) return nullptr;
    return it->path;
}

struct ModuleNameAndBaseAddress
{
    const char* name;
    uint64_t baseAddr;
};

ModuleNameAndBaseAddress GetModuleNameAndPrepareSymbols( uint64_t addr )
{
    if( ( addr >> 63 ) != 0 )
    {
        if( s_krnlCache )
        {
            auto it = std::lower_bound( s_krnlCache, s_krnlCache + s_krnlCacheCnt, addr, []( const KernelDriver& lhs, const uint64_t& rhs ) { return lhs.addr > rhs; } );
            if( it != s_krnlCache + s_krnlCacheCnt )
            {
                return ModuleNameAndBaseAddress{ it->mod, it->addr };
            }
        }
        return ModuleNameAndBaseAddress{ "<kernel>", addr };
    }

    for( auto& v : *s_modCache )
    {
        if( addr >= v.start && addr < v.end )
        {
            return ModuleNameAndBaseAddress{ v.name, v.start };
        }
    }

    HMODULE mod[1024];
    DWORD needed;
    HANDLE proc = GetCurrentProcess();

    InitRpmalloc();
    if( EnumProcessModules( proc, mod, sizeof( mod ), &needed ) != 0 )
    {
        const auto sz = needed / sizeof( HMODULE );
        for( size_t i=0; i<sz; i++ )
        {
            MODULEINFO info;
            if( GetModuleInformation( proc, mod[i], &info, sizeof( info ) ) != 0 )
            {
                const auto base = uint64_t( info.lpBaseOfDll );
                if( addr >= base && addr < base + info.SizeOfImage )
                {
                    char name[1024];
                    const auto nameLength = GetModuleFileNameA( mod[i], name, 1021 );
                    if( nameLength > 0 )
                    {
                        // since this is the first time we encounter this module, load its symbols (needed for modules loaded after SymInitialize)
                        ModuleCache* cachedModule = LoadSymbolsForModuleAndCache( name, nameLength, (DWORD64)info.lpBaseOfDll, info.SizeOfImage );
                        return ModuleNameAndBaseAddress{ cachedModule->name, cachedModule->start };
                    }
                }
            }
        }
    }

    return ModuleNameAndBaseAddress{ "[unknown]", 0x0 };
}

CallstackSymbolData DecodeSymbolAddress( uint64_t ptr )
{
    CallstackSymbolData sym;

    if( s_shouldResolveSymbolsOffline )
    {
        sym.file = "[unknown]";
        sym.line = 0;
        sym.needFree = false;
        return sym;
    }

    IMAGEHLP_LINE64 line;
    DWORD displacement = 0;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_LOCK;
#endif
    const auto res = SymGetLineFromAddr64( GetCurrentProcess(), ptr, &displacement, &line );
    if( res == 0 || line.LineNumber >= 0xF00000 )
    {
        sym.file = "[unknown]";
        sym.line = 0;
        sym.needFree = false;
    }
    else
    {
        sym.file = CopyString( line.FileName );
        sym.line = line.LineNumber;
        sym.needFree = true;
    }
#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_UNLOCK;
#endif
    return sym;
}

CallstackEntryData DecodeCallstackPtr( uint64_t ptr )
{
#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_LOCK;
#endif

    InitRpmalloc();

    const ModuleNameAndBaseAddress moduleNameAndAddress = GetModuleNameAndPrepareSymbols( ptr );

    if( s_shouldResolveSymbolsOffline )
    {
#ifdef TRACY_DBGHELP_LOCK
        DBGHELP_UNLOCK;
#endif

        cb_data[0].symAddr = ptr - moduleNameAndAddress.baseAddr;
        cb_data[0].symLen = 0;

        cb_data[0].name = CopyStringFast("[unresolved]");
        cb_data[0].file = CopyStringFast("[unknown]");
        cb_data[0].line = 0;

        return { cb_data, 1, moduleNameAndAddress.name };
    }

    int write;
    const auto proc = GetCurrentProcess();

#if !defined TRACY_NO_CALLSTACK_INLINES
    BOOL doInline = FALSE;
    DWORD ctx = 0;
    DWORD inlineNum = 0;
    if( _SymAddrIncludeInlineTrace )
    {
        inlineNum = _SymAddrIncludeInlineTrace( proc, ptr );
        if( inlineNum > MaxCbTrace - 1 ) inlineNum = MaxCbTrace - 1;
        DWORD idx;
        if( inlineNum != 0 ) doInline = _SymQueryInlineTrace( proc, ptr, 0, ptr, ptr, &ctx, &idx );
    }
    if( doInline )
    {
        write = inlineNum;
        cb_num = 1 + inlineNum;
    }
    else
#endif
    {
        write = 0;
        cb_num = 1;
    }

    char buf[sizeof( SYMBOL_INFO ) + MaxNameSize];
    auto si = (SYMBOL_INFO*)buf;
    si->SizeOfStruct = sizeof( SYMBOL_INFO );
    si->MaxNameLen = MaxNameSize;

    const auto symValid = SymFromAddr( proc, ptr, nullptr, si ) != 0;

    IMAGEHLP_LINE64 line;
    DWORD displacement = 0;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    {
        const char* filename;
        const auto res = SymGetLineFromAddr64( proc, ptr, &displacement, &line );
        if( res == 0 || line.LineNumber >= 0xF00000 )
        {
            filename = "[unknown]";
            cb_data[write].line = 0;
        }
        else
        {
            filename = line.FileName;
            cb_data[write].line = line.LineNumber;
        }

        cb_data[write].name = symValid ? CopyStringFast( si->Name, si->NameLen ) : CopyStringFast( moduleNameAndAddress.name );
        cb_data[write].file = CopyStringFast( filename );
        if( symValid )
        {
            cb_data[write].symLen = si->Size;
            cb_data[write].symAddr = si->Address;
        }
        else
        {
            cb_data[write].symLen = 0;
            cb_data[write].symAddr = 0;
        }
    }

#if !defined TRACY_NO_CALLSTACK_INLINES
    if( doInline )
    {
        for( DWORD i=0; i<inlineNum; i++ )
        {
            auto& cb = cb_data[i];
            const auto symInlineValid = _SymFromInlineContext( proc, ptr, ctx, nullptr, si ) != 0;
            const char* filename;
            if( _SymGetLineFromInlineContext( proc, ptr, ctx, 0, &displacement, &line ) == 0 )
            {
                filename = "[unknown]";
                cb.line = 0;
            }
            else
            {
                filename = line.FileName;
                cb.line = line.LineNumber;
            }

            cb.name = symInlineValid ? CopyStringFast( si->Name, si->NameLen ) : CopyStringFast( moduleNameAndAddress.name );
            cb.file = CopyStringFast( filename );
            if( symInlineValid )
            {
                cb.symLen = si->Size;
                cb.symAddr = si->Address;
            }
            else
            {
                cb.symLen = 0;
                cb.symAddr = 0;
            }

            ctx++;
        }
    }
#endif
#ifdef TRACY_DBGHELP_LOCK
    DBGHELP_UNLOCK;
#endif

    return { cb_data, uint8_t( cb_num ), moduleNameAndAddress.name };
}

#elif TRACY_HAS_CALLSTACK == 2 || TRACY_HAS_CALLSTACK == 3 || TRACY_HAS_CALLSTACK == 4 || TRACY_HAS_CALLSTACK == 6

enum { MaxCbTrace = 64 };

struct backtrace_state* cb_bts = nullptr;

int cb_num;
CallstackEntry cb_data[MaxCbTrace];
int cb_fixup;
#ifdef TRACY_USE_IMAGE_CACHE
static ImageCache* s_imageCache = nullptr;
#endif //#ifdef TRACY_USE_IMAGE_CACHE

#ifdef TRACY_DEBUGINFOD
debuginfod_client* s_debuginfod;

struct DebugInfo
{
    uint8_t* buildid;
    size_t buildid_size;
    char* filename;
    int fd;
};

static FastVector<DebugInfo>* s_di_known;
#endif

#ifdef __linux
struct KernelSymbol
{
    uint64_t addr;
    uint32_t size;
    const char* name;
    const char* mod;
};

KernelSymbol* s_kernelSym = nullptr;
size_t s_kernelSymCnt;

static void InitKernelSymbols()
{
    FILE* f = fopen( "/proc/kallsyms", "rb" );
    if( !f ) return;
    tracy::FastVector<KernelSymbol> tmpSym( 512 * 1024 );
    size_t linelen = 16 * 1024;     // linelen must be big enough to prevent reallocs in getline()
    auto linebuf = (char*)tracy_malloc( linelen );
    ssize_t sz;
    size_t validCnt = 0;
    while( ( sz = getline( &linebuf, &linelen, f ) ) != -1 )
    {
        auto ptr = linebuf;
        uint64_t addr = 0;
        while( *ptr != ' ' )
        {
            auto v = *ptr;
            if( v >= '0' && v <= '9' )
            {
                v -= '0';
            }
            else if( v >= 'a' && v <= 'f' )
            {
                v -= 'a';
                v += 10;
            }
            else if( v >= 'A' && v <= 'F' )
            {
                v -= 'A';
                v += 10;
            }
            else
            {
                assert( false );
            }
            assert( ( v & ~0xF ) == 0 );
            addr <<= 4;
            addr |= v;
            ptr++;
        }
        if( addr == 0 ) continue;
        ptr++;
        const bool valid = *ptr == 'T' || *ptr == 't';
        ptr += 2;
        const auto namestart = ptr;
        while( *ptr != '\t' && *ptr != '\n' ) ptr++;
        const auto nameend = ptr;
        const char* modstart = nullptr;
        const char* modend;
        if( *ptr == '\t' )
        {
            ptr += 2;
            modstart = ptr;
            while( *ptr != ']' ) ptr++;
            modend = ptr;
        }

        char* strname = nullptr;
        char* strmod = nullptr;

        if( valid )
        {
            validCnt++;

            strname = (char*)tracy_malloc_fast( nameend - namestart + 1 );
            memcpy( strname, namestart, nameend - namestart );
            strname[nameend-namestart] = '\0';

            if( modstart )
            {
                strmod = (char*)tracy_malloc_fast( modend - modstart + 1 );
                memcpy( strmod, modstart, modend - modstart );
                strmod[modend-modstart] = '\0';
            }
        }

        auto sym = tmpSym.push_next();
        sym->addr = addr;
        sym->size = 0;
        sym->name = strname;
        sym->mod = strmod;
    }
    tracy_free_fast( linebuf );
    fclose( f );
    if( tmpSym.empty() ) return;

    std::sort( tmpSym.begin(), tmpSym.end(), []( const KernelSymbol& lhs, const KernelSymbol& rhs ) { return lhs.addr < rhs.addr; } );
    for( size_t i=0; i<tmpSym.size()-1; i++ )
    {
        if( tmpSym[i].name ) tmpSym[i].size = tmpSym[i+1].addr - tmpSym[i].addr;
    }

    s_kernelSymCnt = validCnt;
    s_kernelSym = (KernelSymbol*)tracy_malloc_fast( sizeof( KernelSymbol ) * validCnt );
    auto dst = s_kernelSym;
    for( auto& v : tmpSym )
    {
        if( v.name ) *dst++ = v;
    }
    assert( dst == s_kernelSym + validCnt );

    TracyDebug( "Loaded %zu kernel symbols (%zu code sections)\n", tmpSym.size(), validCnt );
}
#endif

char* NormalizePath( const char* path )
{
    if( path[0] != '/' ) return nullptr;

    const char* ptr = path;
    const char* end = path;
    while( *end ) end++;

    char* res = (char*)tracy_malloc( end - ptr + 1 );
    size_t rsz = 0;

    while( ptr < end )
    {
        const char* next = ptr;
        while( next < end && *next != '/' ) next++;
        size_t lsz = next - ptr;
        switch( lsz )
        {
        case 2:
            if( memcmp( ptr, "..", 2 ) == 0 )
            {
                const char* back = res + rsz - 1;
                while( back > res && *back != '/' ) back--;
                rsz = back - res;
                ptr = next + 1;
                continue;
            }
            break;
        case 1:
            if( *ptr == '.' )
            {
                ptr = next + 1;
                continue;
            }
            break;
        case 0:
            ptr = next + 1;
            continue;
        }
        if( rsz != 1 ) res[rsz++] = '/';
        memcpy( res+rsz, ptr, lsz );
        rsz += lsz;
        ptr = next + 1;
    }

    if( rsz == 0 )
    {
        memcpy( res, "/", 2 );
    }
    else
    {
        res[rsz] = '\0';
    }
    return res;
}

void InitCallstackCritical()
{
}

void InitCallstack()
{
    InitRpmalloc();

#ifdef TRACY_USE_IMAGE_CACHE
    s_imageCache = (ImageCache*)tracy_malloc( sizeof( ImageCache ) );
    new(s_imageCache) ImageCache();
#endif //#ifdef TRACY_USE_IMAGE_CACHE

#ifndef TRACY_SYMBOL_OFFLINE_RESOLVE
    s_shouldResolveSymbolsOffline = ShouldResolveSymbolsOffline();
#endif //#ifndef TRACY_SYMBOL_OFFLINE_RESOLVE
    if( s_shouldResolveSymbolsOffline )
    {
        cb_bts = nullptr; // disable use of libbacktrace calls
        TracyDebug("TRACY: enabling offline symbol resolving!\n");
    }
    else
    {
        cb_bts = backtrace_create_state( nullptr, 0, nullptr, nullptr );
    }

#ifndef TRACY_DEMANGLE
    ___tracy_init_demangle_buffer();
#endif

#ifdef __linux
    InitKernelSymbols();
#endif
#ifdef TRACY_DEBUGINFOD
    s_debuginfod = debuginfod_begin();
    s_di_known = (FastVector<DebugInfo>*)tracy_malloc( sizeof( FastVector<DebugInfo> ) );
    new (s_di_known) FastVector<DebugInfo>( 16 );
#endif
}

#ifdef TRACY_DEBUGINFOD
void ClearDebugInfoVector( FastVector<DebugInfo>& vec )
{
    for( auto& v : vec )
    {
        tracy_free( v.buildid );
        tracy_free( v.filename );
        if( v.fd >= 0 ) close( v.fd );
    }
    vec.clear();
}

DebugInfo* FindDebugInfo( FastVector<DebugInfo>& vec, const uint8_t* buildid_data, size_t buildid_size )
{
    for( auto& v : vec )
    {
        if( v.buildid_size == buildid_size && memcmp( v.buildid, buildid_data, buildid_size ) == 0 )
        {
            return &v;
        }
    }
    return nullptr;
}

int GetDebugInfoDescriptor( const char* buildid_data, size_t buildid_size, const char* filename )
{
    auto buildid = (uint8_t*)buildid_data;
    auto it = FindDebugInfo( *s_di_known, buildid, buildid_size );
    if( it ) return it->fd >= 0 ? dup( it->fd ) : -1;

    int fd = debuginfod_find_debuginfo( s_debuginfod, buildid, buildid_size, nullptr );
    it = s_di_known->push_next();
    it->buildid_size = buildid_size;
    it->buildid = (uint8_t*)tracy_malloc( buildid_size );
    memcpy( it->buildid, buildid, buildid_size );
    const auto fnsz = strlen( filename ) + 1;
    it->filename = (char*)tracy_malloc( fnsz );
    memcpy( it->filename, filename, fnsz );
    it->fd = fd >= 0 ? fd : -1;
    TracyDebug( "DebugInfo descriptor query: %i, fn: %s\n", fd, filename );
    return it->fd;
}

const uint8_t* GetBuildIdForImage( const char* image, size_t& size )
{
    assert( image );
    for( auto& v : *s_di_known )
    {
        if( strcmp( image, v.filename ) == 0 )
        {
            size = v.buildid_size;
            return v.buildid;
        }
    }
    return nullptr;
}

debuginfod_client* GetDebuginfodClient()
{
    return s_debuginfod;
}
#endif

void EndCallstack()
{
#ifdef TRACY_USE_IMAGE_CACHE
    if( s_imageCache )
    {
        s_imageCache->~ImageCache();
        tracy_free( s_imageCache );
    }
#endif //#ifdef TRACY_USE_IMAGE_CACHE
#ifndef TRACY_DEMANGLE
    ___tracy_free_demangle_buffer();
#endif
#ifdef TRACY_DEBUGINFOD
    ClearDebugInfoVector( *s_di_known );
    s_di_known->~FastVector<DebugInfo>();
    tracy_free( s_di_known );

    debuginfod_end( s_debuginfod );
#endif
}

const char* DecodeCallstackPtrFast( uint64_t ptr )
{
    static char ret[1024];
    auto vptr = (void*)ptr;
    const char* symname = nullptr;
    Dl_info dlinfo;
    if( dladdr( vptr, &dlinfo ) && dlinfo.dli_sname )
    {
        symname = dlinfo.dli_sname;
    }
    if( symname )
    {
        strcpy( ret, symname );
    }
    else
    {
        *ret = '\0';
    }
    return ret;
}

static int SymbolAddressDataCb( void* data, uintptr_t pc, uintptr_t lowaddr, const char* fn, int lineno, const char* function )
{
    auto& sym = *(CallstackSymbolData*)data;
    if( !fn )
    {
        sym.file = "[unknown]";
        sym.line = 0;
        sym.needFree = false;
    }
    else
    {
        sym.file = NormalizePath( fn );
        if( !sym.file ) sym.file = CopyString( fn );
        sym.line = lineno;
        sym.needFree = true;
    }

    return 1;
}

static void SymbolAddressErrorCb( void* data, const char* /*msg*/, int /*errnum*/ )
{
    auto& sym = *(CallstackSymbolData*)data;
    sym.file = "[unknown]";
    sym.line = 0;
    sym.needFree = false;
}

CallstackSymbolData DecodeSymbolAddress( uint64_t ptr )
{
    CallstackSymbolData sym;
    if( cb_bts )
    {
        backtrace_pcinfo( cb_bts, ptr, SymbolAddressDataCb, SymbolAddressErrorCb, &sym );
    }
    else
    {
        SymbolAddressErrorCb(&sym, nullptr, 0);
    }

    return sym;
}

static int CallstackDataCb( void* /*data*/, uintptr_t pc, uintptr_t lowaddr, const char* fn, int lineno, const char* function )
{
    cb_data[cb_num].symLen = 0;
    cb_data[cb_num].symAddr = (uint64_t)lowaddr;

    if( !fn && !function )
    {
        const char* symname = nullptr;
        auto vptr = (void*)pc;
        ptrdiff_t symoff = 0;

        Dl_info dlinfo;
        if( dladdr( vptr, &dlinfo ) )
        {
            symname = dlinfo.dli_sname;
            symoff = (char*)pc - (char*)dlinfo.dli_saddr;
            const char* demangled = ___tracy_demangle( symname );
            if( demangled ) symname = demangled;
        }

        if( !symname ) symname = "[unknown]";

        if( symoff == 0 )
        {
            const auto len = std::min<size_t>( strlen( symname ), std::numeric_limits<uint16_t>::max() );
            cb_data[cb_num].name = CopyStringFast( symname, len );
        }
        else
        {
            char buf[32];
            const auto offlen = sprintf( buf, " + %td", symoff );
            const auto namelen = std::min<size_t>( strlen( symname ), std::numeric_limits<uint16_t>::max() - offlen );
            auto name = (char*)tracy_malloc_fast( namelen + offlen + 1 );
            memcpy( name, symname, namelen );
            memcpy( name + namelen, buf, offlen );
            name[namelen + offlen] = '\0';
            cb_data[cb_num].name = name;
        }

        cb_data[cb_num].file = CopyStringFast( "[unknown]" );
        cb_data[cb_num].line = 0;
    }
    else
    {
        if( !fn ) fn = "[unknown]";
        if( !function )
        {
            function = "[unknown]";
        }
        else
        {
            const char* demangled = ___tracy_demangle( function );
            if( demangled ) function = demangled;
        }

        const auto len = std::min<size_t>( strlen( function ), std::numeric_limits<uint16_t>::max() );
        cb_data[cb_num].name = CopyStringFast( function, len );
        cb_data[cb_num].file = NormalizePath( fn );
        if( !cb_data[cb_num].file ) cb_data[cb_num].file = CopyStringFast( fn );
        cb_data[cb_num].line = lineno;
    }

    if( ++cb_num >= MaxCbTrace )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void CallstackErrorCb( void* /*data*/, const char* /*msg*/, int /*errnum*/ )
{
    for( int i=0; i<cb_num; i++ )
    {
        tracy_free_fast( (void*)cb_data[i].name );
        tracy_free_fast( (void*)cb_data[i].file );
    }

    cb_data[0].name = CopyStringFast( "[error]" );
    cb_data[0].file = CopyStringFast( "[error]" );
    cb_data[0].line = 0;

    cb_num = 1;
}

void SymInfoCallback( void* /*data*/, uintptr_t pc, const char* symname, uintptr_t symval, uintptr_t symsize )
{
    cb_data[cb_num-1].symLen = (uint32_t)symsize;
    cb_data[cb_num-1].symAddr = (uint64_t)symval;
}

void SymInfoError( void* /*data*/, const char* /*msg*/, int /*errnum*/ )
{
    cb_data[cb_num-1].symLen = 0;
    cb_data[cb_num-1].symAddr = 0;
}

void GetSymbolForOfflineResolve(void* address, uint64_t imageBaseAddress, CallstackEntry& cbEntry)
{
    // tagged with a string that we can identify as an unresolved symbol
    cbEntry.name = CopyStringFast( "[unresolved]" );
    // set .so relative offset so it can be resolved offline
    cbEntry.symAddr = (uint64_t)address - imageBaseAddress;
    cbEntry.symLen = 0x0;
    cbEntry.file = CopyStringFast( "[unknown]" );
    cbEntry.line = 0;
}

CallstackEntryData DecodeCallstackPtr( uint64_t ptr )
{
    InitRpmalloc();
    if( ptr >> 63 == 0 )
    {
        const char* imageName = nullptr;
        uint64_t imageBaseAddress = 0x0;

#ifdef TRACY_USE_IMAGE_CACHE
        const auto* image = s_imageCache->GetImageForAddress((void*)ptr);
        if( image )
        {
            imageName = image->m_name;
            imageBaseAddress = uint64_t(image->m_startAddress);
        }
#else
        Dl_info dlinfo;
        if( dladdr( (void*)ptr, &dlinfo ) )
        {
            imageName = dlinfo.dli_fname;
            imageBaseAddress = uint64_t( dlinfo.dli_fbase );
        }
#endif

        if( s_shouldResolveSymbolsOffline )
        {
            cb_num = 1;
            GetSymbolForOfflineResolve( (void*)ptr, imageBaseAddress, cb_data[0] );
        }
        else
        {
            cb_num = 0;
            backtrace_pcinfo( cb_bts, ptr, CallstackDataCb, CallstackErrorCb, nullptr );
            assert( cb_num > 0 );

            backtrace_syminfo( cb_bts, ptr, SymInfoCallback, SymInfoError, nullptr );
        }

        return { cb_data, uint8_t( cb_num ), imageName ? imageName : "[unknown]" };
    }
#ifdef __linux
    else if( s_kernelSym )
    {
        auto it = std::lower_bound( s_kernelSym, s_kernelSym + s_kernelSymCnt, ptr, []( const KernelSymbol& lhs, const uint64_t& rhs ) { return lhs.addr + lhs.size < rhs; } );
        if( it != s_kernelSym + s_kernelSymCnt )
        {
            cb_data[0].name = CopyStringFast( it->name );
            cb_data[0].file = CopyStringFast( "<kernel>" );
            cb_data[0].line = 0;
            cb_data[0].symLen = it->size;
            cb_data[0].symAddr = it->addr;
            return { cb_data, 1, it->mod ? it->mod : "<kernel>" };
        }
    }
#endif

    cb_data[0].name = CopyStringFast( "[unknown]" );
    cb_data[0].file = CopyStringFast( "<kernel>" );
    cb_data[0].line = 0;
    cb_data[0].symLen = 0;
    cb_data[0].symAddr = 0;
    return { cb_data, 1, "<kernel>" };
}

#elif TRACY_HAS_CALLSTACK == 5

void InitCallstackCritical()
{
}

void InitCallstack()
{
    ___tracy_init_demangle_buffer();
}

void EndCallstack()
{
    ___tracy_free_demangle_buffer();
}

const char* DecodeCallstackPtrFast( uint64_t ptr )
{
    static char ret[1024];
    auto vptr = (void*)ptr;
    const char* symname = nullptr;
    Dl_info dlinfo;
    if( dladdr( vptr, &dlinfo ) && dlinfo.dli_sname )
    {
        symname = dlinfo.dli_sname;
    }
    if( symname )
    {
        strcpy( ret, symname );
    }
    else
    {
        *ret = '\0';
    }
    return ret;
}

CallstackSymbolData DecodeSymbolAddress( uint64_t ptr )
{
    const char* symloc = nullptr;
    Dl_info dlinfo;
    if( dladdr( (void*)ptr, &dlinfo ) ) symloc = dlinfo.dli_fname;
    if( !symloc ) symloc = "[unknown]";
    return CallstackSymbolData { symloc, 0, false, 0 };
}

CallstackEntryData DecodeCallstackPtr( uint64_t ptr )
{
    static CallstackEntry cb;
    cb.line = 0;

    const char* symname = nullptr;
    const char* symloc = nullptr;
    auto vptr = (void*)ptr;
    ptrdiff_t symoff = 0;
    void* symaddr = nullptr;

    Dl_info dlinfo;
    if( dladdr( vptr, &dlinfo ) )
    {
        symloc = dlinfo.dli_fname;
        symname = dlinfo.dli_sname;
        symoff = (char*)ptr - (char*)dlinfo.dli_saddr;
        symaddr = dlinfo.dli_saddr;
        const char* demangled = ___tracy_demangle( symname );
        if( demangled ) symname = demangled;
    }

    if( !symname ) symname = "[unknown]";
    if( !symloc ) symloc = "[unknown]";

    if( symoff == 0 )
    {
        const auto len = std::min<size_t>( strlen( symname ), std::numeric_limits<uint16_t>::max() );
        cb.name = CopyString( symname, len );
    }
    else
    {
        char buf[32];
        const auto offlen = sprintf( buf, " + %td", symoff );
        const auto namelen = std::min<size_t>( strlen( symname ), std::numeric_limits<uint16_t>::max() - offlen );
        auto name = (char*)tracy_malloc( namelen + offlen + 1 );
        memcpy( name, symname, namelen );
        memcpy( name + namelen, buf, offlen );
        name[namelen + offlen] = '\0';
        cb.name = name;
    }

    cb.file = CopyString( "[unknown]" );
    cb.symLen = 0;
    cb.symAddr = (uint64_t)symaddr;

    return { &cb, 1, symloc };
}

#endif

}

#endif
