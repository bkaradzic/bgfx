//
//  D3D4Linux — access Direct3D DLLs from Linux programs
//
//  Copyright © 2016 Sam Hocevar <sam@hocevar.net>
//
//  This library is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it
//  and/or modify it under the terms of the Do What the Fuck You Want
//  to Public License, Version 2, as published by the WTFPL Task Force.
//  See http://www.wtfpl.net/ for more details.
//

#pragma once

#include <cstdint> /* for uint32_t */
#include <cstddef> /* for size_t */
#include <cstring> /* for strcmp */

#include <vector> /* for std::vector */
#include <string> /* for std::string */
#include <wchar.h>

/*
 * Default values for some runtime settings
 */

#if !defined D3D4LINUX_DLL
    // NOTE: this variable has a Z: prefix because it will be interpreted by
    // a Windows process run by Wine, so it needs a Windows path.
#   define D3D4LINUX_DLL "z:/usr/lib/d3d4linux/d3dcompiler_47.dll"
#endif

#if !defined D3D4LINUX_EXE
#   define D3D4LINUX_EXE "/usr/lib/d3d4linux/d3d4linux.exe"
#endif

#if !defined D3D4LINUX_WINE
    // Wine 11+ uses "wine" for both 32/64-bit, older versions use "wine64"
#   define D3D4LINUX_WINE "/usr/bin/wine"
#   define D3D4LINUX_WINE_FALLBACK "/usr/bin/wine64"
#endif

#ifndef WSL_WINADAPTER_H
/*
 * Types and macros that come from Windows
 */

typedef long HRESULT;
typedef long HMODULE;
typedef void const * LPCVOID;
typedef char const * LPCSTR;

typedef long GUID;
typedef GUID REFIID; /* FIXME */

#define CONST const

#define S_FALSE ((HRESULT)1)
#define S_OK ((HRESULT)0)
#define E_FAIL ((HRESULT)0x80004005)

#define SUCCEEDED(x) ((HRESULT)(x) == S_OK)
#define FAILED(x) (!SUCCEEDED(x))

#define EXCEPTION_EXECUTE_HANDLER 1

#define MAKE_HRESULT(x, y, z) ((HRESULT) (((unsigned long)(x)<<31) | ((unsigned long)(y)<<16) | ((unsigned long)(z))) )

/*
 * Fake values; we don’t care
 */

#define IID_ID3D11ShaderReflection D3D4LINUX_IID_SHADER_REFLECTION
#endif // WSL_WINADAPTER_H

/*
 * Types that come from D3D
 */

#include <d3d4linux_enums.h>
#include <d3d4linux_types.h>

struct ID3DInclude
{
    // FIXME: unimplemented
};

struct ID3D11ShaderReflectionType
{
    HRESULT GetDesc(D3D11_SHADER_TYPE_DESC *desc)
    {
        *desc = m_desc;
        desc->Name = m_name.empty() ? nullptr : m_name.c_str();
        return S_OK;
    }

    D3D11_SHADER_TYPE_DESC m_desc;
    std::string m_name;
};

struct ID3D11ShaderReflectionVariable
{
    HRESULT GetDesc(D3D11_SHADER_VARIABLE_DESC *desc)
    {
        *desc = m_desc;
        desc->Name = m_strings[0].c_str();
        desc->DefaultValue = m_has_default ? m_default_value.data() : nullptr;
        return S_OK;
    }

    ID3D11ShaderReflectionType *GetType()
    {
        return &m_type;
    }

    D3D11_SHADER_VARIABLE_DESC m_desc;
    ID3D11ShaderReflectionType m_type;
    std::vector<std::string> m_strings;
    int m_has_default;
    std::vector<uint8_t> m_default_value;
};

struct ID3D11ShaderReflectionConstantBuffer
{
    HRESULT GetDesc(D3D11_SHADER_BUFFER_DESC *desc)
    {
        *desc = m_desc;
        desc->Name = m_strings[0].c_str();
        return S_OK;
    }

    struct ID3D11ShaderReflectionVariable *GetVariableByIndex(uint32_t index)
    {
        return index < m_variables.size() ? &m_variables[index] : nullptr;
    }

    struct ID3D11ShaderReflectionVariable *GetVariableByName(char const *name)
    {
        for (size_t i = 0; i < m_variables.size(); ++i)
            if (!strcmp(m_variables[i].m_strings[0].c_str(), name))
                return &m_variables[i];

        return nullptr;
    }

    D3D11_SHADER_BUFFER_DESC m_desc;
    std::vector<ID3D11ShaderReflectionVariable> m_variables;
    std::vector<std::string> m_strings;
};

struct ID3D11ShaderReflection
{
    ID3D11ShaderReflection() : m_refcount(1) {}

    HRESULT GetDesc(D3D11_SHADER_DESC *Desc)
    {
        *Desc = m_desc;
        Desc->Creator = m_strings[0].c_str();
        return S_OK;
    }

    HRESULT GetInputParameterDesc(uint32_t index, D3D11_SIGNATURE_PARAMETER_DESC *desc)
    {
        if (index >= m_input_params.size())
            return E_FAIL;

        *desc = m_input_params[index];
        desc->SemanticName = m_strings[1 + index].c_str();
        return S_OK;
    }

    HRESULT GetOutputParameterDesc(uint32_t index, D3D11_SIGNATURE_PARAMETER_DESC *desc)
    {
        if (index >= m_output_params.size())
            return E_FAIL;

        *desc = m_output_params[index];
        desc->SemanticName = m_strings[1 + m_input_params.size() + index].c_str();
        return S_OK;
    }

    HRESULT GetResourceBindingDesc(uint32_t index, D3D11_SHADER_INPUT_BIND_DESC *desc)
    {
        if (index >= m_binds.size())
            return E_FAIL;

        *desc = m_binds[index];
        desc->Name = m_strings[1 + m_input_params.size() + m_output_params.size() + index].c_str();
        return S_OK;
    }

    struct ID3D11ShaderReflectionConstantBuffer *GetConstantBufferByName(char const *name)
    {
        for (size_t i = 0; i < m_buffers.size(); ++i)
            if (!strcmp(m_buffers[i].m_strings[0].c_str(), name))
                return &m_buffers[i];
        return nullptr;
    }

    struct ID3D11ShaderReflectionConstantBuffer *GetConstantBufferByIndex(uint32_t index)
    {
        return index < m_buffers.size() ? &m_buffers[index] : nullptr;
    }

    void AddRef() { ++m_refcount; }
    void Release() { /*if (this && --m_refcount <= 0) delete this;*/ }

    D3D11_SHADER_DESC m_desc;
    std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_input_params;
    std::vector<D3D11_SIGNATURE_PARAMETER_DESC> m_output_params;
    std::vector<D3D11_SHADER_INPUT_BIND_DESC> m_binds;
    std::vector<ID3D11ShaderReflectionConstantBuffer> m_buffers;
    std::vector<std::string> m_strings;

private:
    int m_refcount;
};

struct ID3DBlob
{
    ID3DBlob(size_t size) : m_refcount(1) { m_data.resize(size); }

    void const *GetBufferPointer() const { return m_data.data(); }
    void *GetBufferPointer() { return m_data.data(); }
    size_t GetBufferSize() const { return m_data.size(); }
    void AddRef() { ++m_refcount; }
    void Release() { /*if (this && --m_refcount <= 0) delete this;*/ }

private:
    std::vector<uint8_t> m_data;
    int m_refcount;
};

/*
 * Helper class
 */

#include <d3d4linux_impl.h>

/*
 * Functions that come from D3D
 */

static inline
HRESULT D3DCreateBlob(size_t Size, ID3DBlob **ppBlob)
{
    return d3d4linux::create_blob(Size, ppBlob);
}

static inline
HRESULT D3DCompile(void const *pSrcData, size_t SrcDataSize,
                   char const *pFileName,
                   D3D_SHADER_MACRO const *pDefines,
                   ID3DInclude *pInclude,
                   char const *pEntrypoint, char const *pTarget,
                   uint32_t Flags1, uint32_t Flags2,
                   ID3DBlob **ppCode, ID3DBlob **ppErrorMsgs)
{
    return d3d4linux::compile(pSrcData, SrcDataSize, pFileName, pDefines,
                              pInclude, pEntrypoint, pTarget, Flags1,
                              Flags2, ppCode, ppErrorMsgs);
}

static inline
HRESULT D3DDisassemble(void const *pSrcData,
                       size_t SrcDataSize,
                       uint32_t Flags,
                       char const *szComments,
                       ID3DBlob **ppDisassembly)
{
    return d3d4linux::disassemble(pSrcData, SrcDataSize, Flags,
                                  szComments, ppDisassembly);
}

static inline
HRESULT D3DReflect(void const *pSrcData,
                   size_t SrcDataSize,
                   REFIID pInterface,
                   void **ppReflector)
{
    return d3d4linux::reflect(pSrcData, SrcDataSize, pInterface, ppReflector);
}

static inline
HRESULT D3DStripShader(void const *pShaderBytecode,
                       size_t BytecodeLength,
                       uint32_t uStripFlags,
                       ID3DBlob **ppStrippedBlob)
{
    return d3d4linux::strip_shader(pShaderBytecode, BytecodeLength,
                                   uStripFlags, ppStrippedBlob);
}

/*
 * Only Compile, Disassemble and Preprocess have associated types
 */

typedef decltype(&d3d4linux::compile) pD3DCompile;
typedef decltype(&d3d4linux::disassemble) pD3DDisassemble;

/*
 * Helper functions for Windows
 */

static inline HMODULE LoadLibrary(char const *name)
{
    static char const *prefix = "d3dcompiler_";
    char const *pos = strstr(name, prefix);
    if (pos)
        d3d4linux::compiler_version() = atoi(pos + strlen(prefix));
    return (HMODULE)1;
}

static inline HMODULE LoadLibrary(wchar_t const *name)
{
    static wchar_t const *prefix = L"d3dcompiler_";
    wchar_t const *pos = wcsstr(name, prefix);
    if (pos)
        d3d4linux::compiler_version() = wcstol(pos + wcslen(prefix), nullptr, 10);
    return (HMODULE)1;
}

static inline void FreeLibrary(HMODULE handle)
{
}

static void *GetProcAddress(HMODULE, char const *name)
{
    if (!strcmp(name, "D3DCompile"))
        return (void *)&d3d4linux::compile;
    if (!strcmp(name, "D3DReflect"))
        return (void *)&d3d4linux::reflect;
    if (!strcmp(name, "D3DDisassemble"))
        return (void *)&d3d4linux::disassemble;
    if (!strcmp(name, "D3DStripShader"))
        return (void *)&d3d4linux::strip_shader;
    if (!strcmp(name, "D3DCreateBlob"))
        return (void *)&d3d4linux::create_blob;
    return nullptr;
}

