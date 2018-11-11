//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  File:       D3DCompiler.h
//  Content:    D3D Compilation Types and APIs
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3DCOMPILER_H__
#define __D3DCOMPILER_H__

#include <winapifamily.h>

// Current name of the DLL shipped in the same SDK as this header.



#define D3DCOMPILER_DLL_W L"d3dcompiler_47.dll"
#define D3DCOMPILER_DLL_A "d3dcompiler_47.dll"

// Current HLSL compiler version.

#define D3D_COMPILER_VERSION 47

#ifdef UNICODE
    #define D3DCOMPILER_DLL D3DCOMPILER_DLL_W 
#else
    #define D3DCOMPILER_DLL D3DCOMPILER_DLL_A
#endif

#include "d3d11shader.h"
#include "d3d12shader.h"

//////////////////////////////////////////////////////////////////////////////
// APIs //////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


#pragma region Application Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

//----------------------------------------------------------------------------
// D3DReadFileToBlob:
// -----------------
// Simple helper routine to read a file on disk into memory
// for passing to other routines in this API.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DReadFileToBlob(_In_ LPCWSTR pFileName,
                  _Out_ ID3DBlob** ppContents);

//----------------------------------------------------------------------------
// D3DWriteBlobToFile:
// ------------------
// Simple helper routine to write a memory blob to a file on disk.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DWriteBlobToFile(_In_ ID3DBlob* pBlob,
                   _In_ LPCWSTR pFileName,
                   _In_ BOOL bOverwrite);

//----------------------------------------------------------------------------
// D3DCOMPILE flags:
// -----------------
// D3DCOMPILE_DEBUG
//   Insert debug file/line/type/symbol information.
//
// D3DCOMPILE_SKIP_VALIDATION
//   Do not validate the generated code against known capabilities and
//   constraints.  This option is only recommended when compiling shaders
//   you KNOW will work.  (ie. have compiled before without this option.)
//   Shaders are always validated by D3D before they are set to the device.
//
// D3DCOMPILE_SKIP_OPTIMIZATION 
//   Instructs the compiler to skip optimization steps during code generation.
//   Unless you are trying to isolate a problem in your code using this option 
//   is not recommended.
//
// D3DCOMPILE_PACK_MATRIX_ROW_MAJOR
//   Unless explicitly specified, matrices will be packed in row-major order
//   on input and output from the shader.
//
// D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR
//   Unless explicitly specified, matrices will be packed in column-major 
//   order on input and output from the shader.  This is generally more 
//   efficient, since it allows vector-matrix multiplication to be performed
//   using a series of dot-products.
//
// D3DCOMPILE_PARTIAL_PRECISION
//   Force all computations in resulting shader to occur at partial precision.
//   This may result in faster evaluation of shaders on some hardware.
//
// D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT
//   Force compiler to compile against the next highest available software
//   target for vertex shaders.  This flag also turns optimizations off, 
//   and debugging on.  
//
// D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT
//   Force compiler to compile against the next highest available software
//   target for pixel shaders.  This flag also turns optimizations off, 
//   and debugging on.
//
// D3DCOMPILE_NO_PRESHADER
//   Disables Preshaders. Using this flag will cause the compiler to not 
//   pull out static expression for evaluation on the host cpu
//
// D3DCOMPILE_AVOID_FLOW_CONTROL
//   Hint compiler to avoid flow-control constructs where possible.
//
// D3DCOMPILE_PREFER_FLOW_CONTROL
//   Hint compiler to prefer flow-control constructs where possible.
//
// D3DCOMPILE_ENABLE_STRICTNESS
//   By default, the HLSL/Effect compilers are not strict on deprecated syntax.
//   Specifying this flag enables the strict mode. Deprecated syntax may be
//   removed in a future release, and enabling syntax is a good way to make
//   sure your shaders comply to the latest spec.
//
// D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY
//   This enables older shaders to compile to 4_0 targets.
//
// D3DCOMPILE_DEBUG_NAME_FOR_SOURCE
//   This enables a debug name to be generated based on source information.
//   It requires D3DCOMPILE_DEBUG to be set, and is exclusive with
//   D3DCOMPILE_DEBUG_NAME_FOR_BINARY.
//
// D3DCOMPILE_DEBUG_NAME_FOR_BINARY
//   This enables a debug name to be generated based on compiled information.
//   It requires D3DCOMPILE_DEBUG to be set, and is exclusive with
//   D3DCOMPILE_DEBUG_NAME_FOR_SOURCE.
//
//----------------------------------------------------------------------------

#define D3DCOMPILE_DEBUG                                (1 << 0)
#define D3DCOMPILE_SKIP_VALIDATION                      (1 << 1)
#define D3DCOMPILE_SKIP_OPTIMIZATION                    (1 << 2)
#define D3DCOMPILE_PACK_MATRIX_ROW_MAJOR                (1 << 3)
#define D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR             (1 << 4)
#define D3DCOMPILE_PARTIAL_PRECISION                    (1 << 5)
#define D3DCOMPILE_FORCE_VS_SOFTWARE_NO_OPT             (1 << 6)
#define D3DCOMPILE_FORCE_PS_SOFTWARE_NO_OPT             (1 << 7)
#define D3DCOMPILE_NO_PRESHADER                         (1 << 8)
#define D3DCOMPILE_AVOID_FLOW_CONTROL                   (1 << 9)
#define D3DCOMPILE_PREFER_FLOW_CONTROL                  (1 << 10)
#define D3DCOMPILE_ENABLE_STRICTNESS                    (1 << 11)
#define D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY       (1 << 12)
#define D3DCOMPILE_IEEE_STRICTNESS                      (1 << 13)
#define D3DCOMPILE_OPTIMIZATION_LEVEL0                  (1 << 14)
#define D3DCOMPILE_OPTIMIZATION_LEVEL1                  0
#define D3DCOMPILE_OPTIMIZATION_LEVEL2                  ((1 << 14) | (1 << 15))
#define D3DCOMPILE_OPTIMIZATION_LEVEL3                  (1 << 15)
#define D3DCOMPILE_RESERVED16                           (1 << 16)
#define D3DCOMPILE_RESERVED17                           (1 << 17)
#define D3DCOMPILE_WARNINGS_ARE_ERRORS                  (1 << 18)
#define D3DCOMPILE_RESOURCES_MAY_ALIAS                  (1 << 19)
#define D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES   (1 << 20)
#define D3DCOMPILE_ALL_RESOURCES_BOUND                  (1 << 21)
#define D3DCOMPILE_DEBUG_NAME_FOR_SOURCE                (1 << 22)
#define D3DCOMPILE_DEBUG_NAME_FOR_BINARY                (1 << 23)

//----------------------------------------------------------------------------
// D3DCOMPILE_EFFECT flags:
// -------------------------------------
// These flags are passed in when creating an effect, and affect
// either compilation behavior or runtime effect behavior
//
// D3DCOMPILE_EFFECT_CHILD_EFFECT
//   Compile this .fx file to a child effect. Child effects have no
//   initializers for any shared values as these are initialied in the
//   master effect (pool).
//
// D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS
//   By default, performance mode is enabled.  Performance mode
//   disallows mutable state objects by preventing non-literal
//   expressions from appearing in state object definitions.
//   Specifying this flag will disable the mode and allow for mutable
//   state objects.
//
//----------------------------------------------------------------------------

#define D3DCOMPILE_EFFECT_CHILD_EFFECT              (1 << 0)
#define D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS            (1 << 1)

//----------------------------------------------------------------------------
// D3DCOMPILE Flags2:
// -----------------
// Root signature flags. (passed in Flags2)
#define D3DCOMPILE_FLAGS2_FORCE_ROOT_SIGNATURE_LATEST		0
#define D3DCOMPILE_FLAGS2_FORCE_ROOT_SIGNATURE_1_0			(1 << 4)
#define D3DCOMPILE_FLAGS2_FORCE_ROOT_SIGNATURE_1_1			(1 << 5)

//----------------------------------------------------------------------------
// D3DCompile:
// ----------
// Compile source text into bytecode appropriate for the given target.
//----------------------------------------------------------------------------

// D3D_COMPILE_STANDARD_FILE_INCLUDE can be passed for pInclude in any
// API and indicates that a simple default include handler should be
// used.  The include handler will include files relative to the
// current directory and files relative to the directory of the initial source
// file.  When used with APIs like D3DCompile pSourceName must be a
// file name and the initial relative directory will be derived from it.
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

HRESULT WINAPI
D3DCompile(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
           _In_ SIZE_T SrcDataSize,
           _In_opt_ LPCSTR pSourceName,
           _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
           _In_opt_ ID3DInclude* pInclude,
           _In_opt_ LPCSTR pEntrypoint,
           _In_ LPCSTR pTarget,
           _In_ UINT Flags1,
           _In_ UINT Flags2,
           _Out_ ID3DBlob** ppCode,
           _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs);

typedef HRESULT (WINAPI *pD3DCompile)
    (LPCVOID                         pSrcData,
     SIZE_T                          SrcDataSize,
     LPCSTR                          pFileName,
     CONST D3D_SHADER_MACRO*         pDefines,
     ID3DInclude*                    pInclude,
     LPCSTR                          pEntrypoint,
     LPCSTR                          pTarget,
     UINT                            Flags1,
     UINT                            Flags2,
     ID3DBlob**                      ppCode,
     ID3DBlob**                      ppErrorMsgs);

#define D3DCOMPILE_SECDATA_MERGE_UAV_SLOTS              0x00000001
#define D3DCOMPILE_SECDATA_PRESERVE_TEMPLATE_SLOTS      0x00000002
#define D3DCOMPILE_SECDATA_REQUIRE_TEMPLATE_MATCH       0x00000004

HRESULT WINAPI
D3DCompile2(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
            _In_ SIZE_T SrcDataSize,
            _In_opt_ LPCSTR pSourceName,
            _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
            _In_opt_ ID3DInclude* pInclude,
            _In_ LPCSTR pEntrypoint,
            _In_ LPCSTR pTarget,
            _In_ UINT Flags1,
            _In_ UINT Flags2,
            _In_ UINT SecondaryDataFlags,
            _In_reads_bytes_opt_(SecondaryDataSize) LPCVOID pSecondaryData,
            _In_ SIZE_T SecondaryDataSize,
            _Out_ ID3DBlob** ppCode,
            _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs);

HRESULT WINAPI
D3DCompileFromFile(_In_ LPCWSTR pFileName,
                   _In_reads_opt_(_Inexpressible_(pDefines->Name != NULL)) CONST D3D_SHADER_MACRO* pDefines,
                   _In_opt_ ID3DInclude* pInclude,
                   _In_ LPCSTR pEntrypoint,
                   _In_ LPCSTR pTarget,
                   _In_ UINT Flags1,
                   _In_ UINT Flags2,
                   _Out_ ID3DBlob** ppCode,
                   _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs);

//----------------------------------------------------------------------------
// D3DPreprocess:
// -------------
// Process source text with the compiler's preprocessor and return
// the resulting text.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DPreprocess(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
              _In_ SIZE_T SrcDataSize,
              _In_opt_ LPCSTR pSourceName,
              _In_opt_ CONST D3D_SHADER_MACRO* pDefines,
              _In_opt_ ID3DInclude* pInclude,
              _Out_ ID3DBlob** ppCodeText,
              _Always_(_Outptr_opt_result_maybenull_) ID3DBlob** ppErrorMsgs);

typedef HRESULT (WINAPI *pD3DPreprocess)
    (LPCVOID                      pSrcData,
     SIZE_T                       SrcDataSize,
     LPCSTR                       pFileName,
     CONST D3D_SHADER_MACRO*      pDefines,
     ID3DInclude*                 pInclude,
     ID3DBlob**                   ppCodeText,
     ID3DBlob**                   ppErrorMsgs);

//----------------------------------------------------------------------------
// D3DGetDebugInfo:
// -----------------------
// Gets shader debug info.  Debug info is generated by D3DCompile and is
// embedded in the body of the shader.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DGetDebugInfo(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                _In_ SIZE_T SrcDataSize,
                _Out_ ID3DBlob** ppDebugInfo);

//----------------------------------------------------------------------------
// D3DReflect:
// ----------
// Shader code contains metadata that can be inspected via the
// reflection APIs.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DReflect(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
           _In_ SIZE_T SrcDataSize,
           _In_ REFIID pInterface,
           _Out_ void** ppReflector);

//----------------------------------------------------------------------------
// D3DReflectLibrary:
// ----------
// Library code contains metadata that can be inspected via the library
// reflection APIs.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DReflectLibrary(__in_bcount(SrcDataSize) LPCVOID pSrcData,
                  __in SIZE_T SrcDataSize,
	              __in REFIID riid,
                  __out LPVOID * ppReflector);

//----------------------------------------------------------------------------
// D3DDisassemble:
// ----------------------
// Takes a binary shader and returns a buffer containing text assembly.
//----------------------------------------------------------------------------

#define D3D_DISASM_ENABLE_COLOR_CODE            0x00000001
#define D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS  0x00000002
#define D3D_DISASM_ENABLE_INSTRUCTION_NUMBERING 0x00000004
#define D3D_DISASM_ENABLE_INSTRUCTION_CYCLE     0x00000008
#define D3D_DISASM_DISABLE_DEBUG_INFO           0x00000010
#define D3D_DISASM_ENABLE_INSTRUCTION_OFFSET    0x00000020
#define D3D_DISASM_INSTRUCTION_ONLY             0x00000040
#define D3D_DISASM_PRINT_HEX_LITERALS           0x00000080

HRESULT WINAPI
D3DDisassemble(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
               _In_ SIZE_T SrcDataSize,
               _In_ UINT Flags,
               _In_opt_ LPCSTR szComments,
               _Out_ ID3DBlob** ppDisassembly);

typedef HRESULT (WINAPI *pD3DDisassemble)
    (_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
     _In_ SIZE_T SrcDataSize,
     _In_ UINT Flags,
     _In_opt_ LPCSTR szComments,
     _Out_ ID3DBlob** ppDisassembly);

HRESULT WINAPI
D3DDisassembleRegion(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                     _In_ SIZE_T SrcDataSize,
                     _In_ UINT Flags,
                     _In_opt_ LPCSTR szComments,
                     _In_ SIZE_T StartByteOffset,
                     _In_ SIZE_T NumInsts,
                     _Out_opt_ SIZE_T* pFinishByteOffset,
                     _Out_ ID3DBlob** ppDisassembly);
    
//----------------------------------------------------------------------------
// Shader linking and Function Linking Graph (FLG) APIs
//----------------------------------------------------------------------------
HRESULT WINAPI
D3DCreateLinker(__out interface ID3D11Linker ** ppLinker);

HRESULT WINAPI
D3DLoadModule(_In_ LPCVOID pSrcData,
              _In_ SIZE_T cbSrcDataSize,
              _Out_ interface ID3D11Module ** ppModule);

HRESULT WINAPI
D3DCreateFunctionLinkingGraph(_In_ UINT uFlags,
                              _Out_ interface ID3D11FunctionLinkingGraph ** ppFunctionLinkingGraph);

//----------------------------------------------------------------------------
// D3DGetTraceInstructionOffsets:
// -----------------------
// Determines byte offsets for instructions within a shader blob.
// This information is useful for going between trace instruction
// indices and byte offsets that are used in debug information.
//----------------------------------------------------------------------------

#define D3D_GET_INST_OFFSETS_INCLUDE_NON_EXECUTABLE 0x00000001

HRESULT WINAPI
D3DGetTraceInstructionOffsets(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                              _In_ SIZE_T SrcDataSize,
                              _In_ UINT Flags,
                              _In_ SIZE_T StartInstIndex,
                              _In_ SIZE_T NumInsts,
                              _Out_writes_to_opt_(NumInsts, min(NumInsts, *pTotalInsts)) SIZE_T* pOffsets,
                              _Out_opt_ SIZE_T* pTotalInsts);

//----------------------------------------------------------------------------
// D3DGetInputSignatureBlob:
// -----------------------
// Retrieve the input signature from a compilation result.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DGetInputSignatureBlob(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                         _In_ SIZE_T SrcDataSize,
                         _Out_ ID3DBlob** ppSignatureBlob);

//----------------------------------------------------------------------------
// D3DGetOutputSignatureBlob:
// -----------------------
// Retrieve the output signature from a compilation result.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DGetOutputSignatureBlob(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                          _In_ SIZE_T SrcDataSize,
                          _Out_ ID3DBlob** ppSignatureBlob);

//----------------------------------------------------------------------------
// D3DGetInputAndOutputSignatureBlob:
// -----------------------
// Retrieve the input and output signatures from a compilation result.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DGetInputAndOutputSignatureBlob(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                                  _In_ SIZE_T SrcDataSize,
                                  _Out_ ID3DBlob** ppSignatureBlob);

//----------------------------------------------------------------------------
// D3DStripShader:
// -----------------------
// Removes unwanted blobs from a compilation result
//----------------------------------------------------------------------------

typedef enum D3DCOMPILER_STRIP_FLAGS
{
    D3DCOMPILER_STRIP_REFLECTION_DATA       = 0x00000001,
    D3DCOMPILER_STRIP_DEBUG_INFO            = 0x00000002,
    D3DCOMPILER_STRIP_TEST_BLOBS            = 0x00000004,
    D3DCOMPILER_STRIP_PRIVATE_DATA          = 0x00000008,
    D3DCOMPILER_STRIP_ROOT_SIGNATURE        = 0x00000010,
    D3DCOMPILER_STRIP_FORCE_DWORD           = 0x7fffffff,
} D3DCOMPILER_STRIP_FLAGS;

HRESULT WINAPI
D3DStripShader(_In_reads_bytes_(BytecodeLength) LPCVOID pShaderBytecode,
               _In_ SIZE_T BytecodeLength,
               _In_ UINT uStripFlags,
               _Out_ ID3DBlob** ppStrippedBlob);

//----------------------------------------------------------------------------
// D3DGetBlobPart:
// -----------------------
// Extracts information from a compilation result.
//----------------------------------------------------------------------------

typedef enum D3D_BLOB_PART
{
    D3D_BLOB_INPUT_SIGNATURE_BLOB,
    D3D_BLOB_OUTPUT_SIGNATURE_BLOB,
    D3D_BLOB_INPUT_AND_OUTPUT_SIGNATURE_BLOB,
    D3D_BLOB_PATCH_CONSTANT_SIGNATURE_BLOB,
    D3D_BLOB_ALL_SIGNATURE_BLOB,
    D3D_BLOB_DEBUG_INFO,
    D3D_BLOB_LEGACY_SHADER,
    D3D_BLOB_XNA_PREPASS_SHADER,
    D3D_BLOB_XNA_SHADER,
    D3D_BLOB_PDB,
    D3D_BLOB_PRIVATE_DATA,
    D3D_BLOB_ROOT_SIGNATURE,
    D3D_BLOB_DEBUG_NAME,

    // Test parts are only produced by special compiler versions and so
    // are usually not present in shaders.
    D3D_BLOB_TEST_ALTERNATE_SHADER = 0x8000,
    D3D_BLOB_TEST_COMPILE_DETAILS,
    D3D_BLOB_TEST_COMPILE_PERF,
    D3D_BLOB_TEST_COMPILE_REPORT,
} D3D_BLOB_PART;

HRESULT WINAPI 
D3DGetBlobPart(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
               _In_ SIZE_T SrcDataSize,
               _In_ D3D_BLOB_PART Part,
               _In_ UINT Flags,
               _Out_ ID3DBlob** ppPart);

//----------------------------------------------------------------------------
// D3DSetBlobPart:
// -----------------------
// Update information in a compilation result.
//----------------------------------------------------------------------------

HRESULT WINAPI 
D3DSetBlobPart(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
               _In_ SIZE_T SrcDataSize,
               _In_ D3D_BLOB_PART Part,
               _In_ UINT Flags,
               _In_reads_bytes_(PartSize) LPCVOID pPart,
               _In_ SIZE_T PartSize,
               _Out_ ID3DBlob** ppNewShader);

//----------------------------------------------------------------------------
// D3DCreateBlob:
// -----------------------
// Create an ID3DBlob instance.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DCreateBlob(_In_ SIZE_T Size,
              _Out_ ID3DBlob** ppBlob);

//----------------------------------------------------------------------------
// D3DCompressShaders:
// -----------------------
// Compresses a set of shaders into a more compact form.
//----------------------------------------------------------------------------

typedef struct _D3D_SHADER_DATA
{
    LPCVOID pBytecode;
    SIZE_T BytecodeLength;
} D3D_SHADER_DATA;

#define D3D_COMPRESS_SHADER_KEEP_ALL_PARTS 0x00000001

HRESULT WINAPI
D3DCompressShaders(_In_ UINT uNumShaders,
                   _In_reads_(uNumShaders) D3D_SHADER_DATA* pShaderData,
                   _In_ UINT uFlags,
                   _Out_ ID3DBlob** ppCompressedData);

//----------------------------------------------------------------------------
// D3DDecompressShaders:
// -----------------------
// Decompresses one or more shaders from a compressed set.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DDecompressShaders(_In_reads_bytes_(SrcDataSize) LPCVOID pSrcData,
                     _In_ SIZE_T SrcDataSize,
                     _In_ UINT uNumShaders,	      
                     _In_ UINT uStartIndex,
                     _In_reads_opt_(uNumShaders) UINT* pIndices,
                     _In_ UINT uFlags,
                     _Out_writes_(uNumShaders) ID3DBlob** ppShaders,
                     _Out_opt_ UINT* pTotalShaders);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
#pragma endregion


#pragma region Desktop Family
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

//----------------------------------------------------------------------------
// D3DDisassemble10Effect:
// -----------------------
// Takes a D3D10 effect interface and returns a
// buffer containing text assembly.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DDisassemble10Effect(_In_ interface ID3D10Effect *pEffect, 
                       _In_ UINT Flags,
                       _Out_ ID3DBlob** ppDisassembly);

#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
#pragma endregion


#ifdef __cplusplus
}
#endif //__cplusplus
    
#endif // #ifndef __D3DCOMPILER_H__
