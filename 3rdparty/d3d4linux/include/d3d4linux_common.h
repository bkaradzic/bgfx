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

#include <vector>
#include <cstdio>

#define D3D4LINUX_FINISHED 0x42000000

#define D3D4LINUX_OP_COMPILE     0x42001000
#define D3D4LINUX_OP_REFLECT     0x42001001
#define D3D4LINUX_OP_STRIP       0x42001002
#define D3D4LINUX_OP_DISASSEMBLE 0x42001003

#define D3D4LINUX_IID_SHADER_REFLECTION 0x42002000

//
// Support class for low-level serialization through stdio streams.
//
// These functions cannot crash in case of bad data, but they may
// return garbage.
// We do not care about endianness (because the guest runs on the same
// machine) and we do not care about read errors (because the protocol
// above us does the necessary checks).
//
struct interop
{
    interop(FILE *in, FILE *out)
      : m_in(in),
        m_out(out)
    {}

    //
    // Simple read/write methods for arbitrary data
    //

    void read_raw(void *ptr, size_t len)
    {
        fread(ptr, len, 1, m_in);
    }

    void write_raw(void const *data, size_t size)
    {
        fwrite(data, size, 1, m_out);
    }

    //
    // Type-specific read/write methods
    //

    int64_t read_i64()
    {
        int64_t ret;
        read_raw(&ret, sizeof(ret));
        return ret;
    }

    std::string read_string()
    {
        std::string ret;
        size_t len = read_i64();
        ret.resize(len);
        read_raw(&ret[0], len);
        return ret;
    }

    std::vector<uint8_t> *read_data()
    {
        size_t len = (size_t)read_i64();
        if (len < 0)
            return nullptr;
        std::vector<uint8_t> *v = new std::vector<uint8_t>();
        v->resize(len);
        read_raw(v->data(), (int)v->size());
        return v;
    }

    void write_i64(int64_t x)
    {
        write_raw(&x, sizeof(x));
        if (x == D3D4LINUX_FINISHED)
            fflush(m_out);
    }

    void write_string(char const *s)
    {
        size_t len = strlen(s);
        write_i64(len);
        write_raw(s, len);
    }

    void write_blob(ID3DBlob *blob)
    {
        write_i64(blob ? blob->GetBufferSize() : -1);
        if (blob)
            write_raw(blob->GetBufferPointer(), blob->GetBufferSize());
    }

protected:
    FILE *m_in, *m_out;
};

