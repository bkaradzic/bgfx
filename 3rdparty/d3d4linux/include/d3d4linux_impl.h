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
#include <cstdio> /* for FILE */
#include <cstring> /* for strcmp() */

#include <unistd.h> /* for fork() */
#include <sys/wait.h> /* for waitpid() */
#include <fcntl.h> /* for O_WRONLY */

#include <string> /* for std::string */

#include <d3d4linux_common.h>

struct d3d4linux
{
    static int &compiler_version()
    {
         static int ret = 0;
         return ret;
    }

    static HRESULT compile(void const *pSrcData,
                           size_t SrcDataSize,
                           char const *pFileName,
                           D3D_SHADER_MACRO const *pDefines,
                           ID3DInclude *pInclude,
                           char const *pEntrypoint,
                           char const *pTarget,
                           uint32_t Flags1,
                           uint32_t Flags2,
                           ID3DBlob **ppCode,
                           ID3DBlob **ppErrorMsgs)
    {
        fork_process p;
        if (p.error())
        {
            static char const *error_msg = "Cannot fork in d3d4linux::compile()";
            *ppErrorMsgs = new ID3DBlob(strlen(error_msg));
            memcpy((*ppErrorMsgs)->GetBufferPointer(), error_msg, (*ppErrorMsgs)->GetBufferSize());
            return E_FAIL;
        }

        p.write_i64(D3D4LINUX_OP_COMPILE);
        p.write_string((char const *)pSrcData);
        p.write_i64(pFileName ? 1 : 0);
        p.write_string(pFileName ? pFileName : "");
        p.write_string(pEntrypoint);
        p.write_string(pTarget);
        p.write_i64(Flags1);
        p.write_i64(Flags2);
        p.write_i64(D3D4LINUX_FINISHED);

        HRESULT ret = p.read_i64();
        ID3DBlob *code_blob = p.read_blob();
        ID3DBlob *error_blob = p.read_blob();
        int end = p.read_i64();
        if (end != D3D4LINUX_FINISHED)
            return E_FAIL;

        *ppCode = code_blob;
        *ppErrorMsgs = error_blob;
        return ret;
    }

    static HRESULT reflect(void const *pSrcData,
                           size_t SrcDataSize,
                           REFIID pInterface,
                           void **ppReflector)
    {
        fork_process p;
        if (p.error())
            return E_FAIL;

        p.write_i64(D3D4LINUX_OP_REFLECT);
        p.write_i64(SrcDataSize);
        p.write_raw(pSrcData, SrcDataSize);
        p.write_i64(D3D4LINUX_IID_SHADER_REFLECTION);
        p.write_i64(D3D4LINUX_FINISHED);

        HRESULT ret = p.read_i64();

        if (SUCCEEDED(ret) ) //&& pInterface == IID_ID3D11ShaderReflection)
        {
            ID3D11ShaderReflection *r = new ID3D11ShaderReflection;

            p.read_raw(&r->m_desc, sizeof(r->m_desc));
            r->m_strings.push_back(p.read_string());

            for (uint32_t i = 0; i < r->m_desc.InputParameters; ++i)
            {
                r->m_input_params.push_back(D3D11_SIGNATURE_PARAMETER_DESC());
                p.read_raw(&r->m_input_params.back(), sizeof(r->m_input_params.back()));
                r->m_strings.push_back(p.read_string());
            }

            for (uint32_t i = 0; i < r->m_desc.OutputParameters; ++i)
            {
                r->m_output_params.push_back(D3D11_SIGNATURE_PARAMETER_DESC());
                p.read_raw(&r->m_output_params.back(), sizeof(r->m_output_params.back()));
                r->m_strings.push_back(p.read_string());
            }

            for (uint32_t i = 0; i < r->m_desc.BoundResources; ++i)
            {
                r->m_binds.push_back(D3D11_SHADER_INPUT_BIND_DESC());
                p.read_raw(&r->m_binds.back(), sizeof(r->m_binds.back()));
                r->m_strings.push_back(p.read_string());
            }

            for (uint32_t i = 0; i < r->m_desc.ConstantBuffers; ++i)
            {
                r->m_buffers.push_back(ID3D11ShaderReflectionConstantBuffer());
                ID3D11ShaderReflectionConstantBuffer &buf = r->m_buffers.back();

                p.read_raw(&buf.m_desc, sizeof(buf.m_desc));
                buf.m_strings.push_back(p.read_string());

                for (uint32_t j = 0; j < buf.m_desc.Variables; ++j)
                {
                    buf.m_variables.push_back(ID3D11ShaderReflectionVariable());
                    ID3D11ShaderReflectionVariable &var = buf.m_variables.back();

                    p.read_raw(&var.m_desc, sizeof(var.m_desc));
                    var.m_desc.uFlags |= D3D_SVF_USED;  // Force all uniforms to be marked as used
                    var.m_strings.push_back(p.read_string());
                    var.m_has_default = p.read_i64();
                    if (var.m_has_default)
                    {
                        var.m_default_value.resize(var.m_desc.Size);
                        p.read_raw(var.m_default_value.data(), var.m_desc.Size);
                    }

                    // Read D3D11_SHADER_TYPE_DESC for this variable
                    p.read_raw(&var.m_type.m_desc, sizeof(var.m_type.m_desc));
                    var.m_type.m_name = p.read_string();
                }
            }

            *ppReflector = r;
        }

        int end = p.read_i64();
        if (end != D3D4LINUX_FINISHED)
            return E_FAIL;

        return ret;
    }

    static HRESULT strip_shader(void const *pShaderBytecode,
                                size_t BytecodeLength,
                                uint32_t uStripFlags,
                                ID3DBlob **ppStrippedBlob)
    {
        fork_process p;
        if (p.error())
            return E_FAIL;

        p.write_i64(D3D4LINUX_OP_STRIP);
        p.write_i64(BytecodeLength);
        p.write_raw(pShaderBytecode, BytecodeLength);
        p.write_i64(uStripFlags);
        p.write_i64(D3D4LINUX_FINISHED);

        HRESULT ret = p.read_i64();
        ID3DBlob *strip_blob = p.read_blob();
        int end = p.read_i64();
        if (end != D3D4LINUX_FINISHED)
            return E_FAIL;

        *ppStrippedBlob = strip_blob;
        return ret;
    }

    static HRESULT disassemble(void const *pSrcData,
                               size_t SrcDataSize,
                               uint32_t Flags,
                               char const *szComments,
                               ID3DBlob **ppDisassembly)
    {
        fork_process p;
        if (p.error())
            return E_FAIL;

        p.write_i64(D3D4LINUX_OP_DISASSEMBLE);
        p.write_i64(SrcDataSize);
        p.write_raw(pSrcData, SrcDataSize);
        p.write_i64(Flags);
        p.write_i64(szComments ? 1 : 0);
        if (szComments)
            p.write_string(szComments);
        p.write_i64(D3D4LINUX_FINISHED);

        HRESULT ret = p.read_i64();
        ID3DBlob *disassembly_blob = p.read_blob();
        int end = p.read_i64();
        if (end != D3D4LINUX_FINISHED)
            return E_FAIL;

        *ppDisassembly = disassembly_blob;
        return ret;
    }

    static HRESULT create_blob(size_t Size,
                               ID3DBlob **ppBlob)
    {
        *ppBlob = new ID3DBlob(Size);
        return S_OK;
    }

private:
    struct fork_process : interop
    {
    public:
        fork_process()
          : interop(nullptr, nullptr),
            m_pid(-1)
        {
            static thread_local pid_t pid = -1;
            static thread_local int pipe_read[2], pipe_write[2];
            static thread_local FILE *in, *out;

            /* If this is the first run in this thread, then fork a new
             * child process. */
            if (pid < 0)
            {
                pipe(pipe_read);
                pipe(pipe_write);

                pid = fork();

                if (pid == 0)
                {
                    dup2(pipe_write[0], STDIN_FILENO);
                    dup2(pipe_read[1], STDOUT_FILENO);

                    char const *verbose_var = getenv("D3D4LINUX_VERBOSE");
                    if (!verbose_var || *verbose_var != '1')
                        dup2(open("/dev/null", O_WRONLY), STDERR_FILENO);

                    char const *exe_var = getenv("D3D4LINUX_EXE");
                    if (!exe_var)
                        exe_var = D3D4LINUX_EXE;

                    char const *wine_var = getenv("D3D4LINUX_WINE");
                    if (!wine_var)
                    {
                        // Try Wine 11+ path first, then fall back to wine64
                        wine_var = D3D4LINUX_WINE;
                        if (access(wine_var, X_OK) != 0)
                        {
#if defined(D3D4LINUX_WINE_FALLBACK)
                            wine_var = D3D4LINUX_WINE_FALLBACK;
#endif
                        }
                    }

                    close(pipe_read[0]);
                    close(pipe_read[1]);
                    close(pipe_write[0]);
                    close(pipe_write[1]);

                    static char *const argv[] = { (char *)"wine", (char *)exe_var, 0 };
                    execv(wine_var, argv);
                    /* Never going past here */
                }

                close(pipe_write[0]);
                close(pipe_read[1]);

                if (pid > 0)
                {
                    in = fdopen(pipe_read[0], "r");
                    out = fdopen(pipe_write[1], "w");
                }
            }

            m_pid = pid;
            m_pipe_in = pipe_read[0];
            m_pipe_out = pipe_write[1];
            m_in = in;
            m_out = out;
        }

        ~fork_process()
        {
            /* FIXME: we cannot close anything here since the child
             * process is persistent across calls. */
#if 0
            if (m_pid > 0)
            {
                waitpid(m_pid, nullptr, 0);
                fclose(m_in);
                fclose(m_out);
            }

            close(m_pipe_in);
            close(m_pipe_out);
#endif
        }

        bool error() const
        {
            return m_pid <= 0;
        }

        ID3DBlob *read_blob()
        {
            int len = read_i64();
            if (len < 0)
                return nullptr;

            ID3DBlob *blob = new ID3DBlob(len);
            read_raw(blob->GetBufferPointer(), len);
            return blob;
        }

    private:
        int m_pipe_in, m_pipe_out;
        pid_t m_pid;
    };
};
