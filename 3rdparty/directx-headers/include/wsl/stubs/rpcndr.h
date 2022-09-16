// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

// Stub header to satisfy d3d12.h include
#pragma once

#include "basetsd.h"

#define __RPCNDR_H_VERSION__

#ifdef CONST_VTABLE
#define CONST_VTBL const
#else
#define CONST_VTBL
#endif

/* Macros for __uuidof template-based emulation */
#if defined(__cplusplus)
#if __cpp_constexpr >= 200704l && __cpp_inline_variables >= 201606L
#define __wsl_stub_uuidof_use_constexpr 1
#else
#define __wsl_stub_uuidof_use_constexpr 0
#endif
#ifndef __GNUC__
#error "Only support for compilers that support for `GNU C++ extension`"
#endif
extern "C++"                                                         {
#if __wsl_stub_uuidof_use_constexpr
    __extension__ template<typename T> struct __wsl_stub_uuidof_s;
    __extension__ template<typename T> constexpr const GUID &__wsl_stub_uuidof();
#else
    __extension__ template<typename T> const GUID &__wsl_stub_uuidof();
#endif
}

#if __wsl_stub_uuidof_use_constexpr
#define __CRT_UUID_DECL(type, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern "C++"                                                         \
    {                                                                    \
        template <>                                                      \
        struct __wsl_stub_uuidof_s<type>                                 \
        {                                                                \
            static constexpr IID __uuid_inst = {                         \
                l, w1, w2, {b1, b2, b3, b4, b5, b6, b7, b8}};            \
        };                                                               \
        template <>                                                      \
        constexpr const GUID &__wsl_stub_uuidof<type>()                  \
        {                                                                \
            return __wsl_stub_uuidof_s<type>::__uuid_inst;               \
        }                                                                \
        template <>                                                      \
        constexpr const GUID &__wsl_stub_uuidof<type *>()                \
        {                                                                \
            return __wsl_stub_uuidof_s<type>::__uuid_inst;               \
        }                                                                \
    }
#else
#define __CRT_UUID_DECL(type, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern "C++"                                                         \
    {                                                                    \
        template <>                                                      \
        inline const GUID &__wsl_stub_uuidof<type>()                     \
        {                                                                \
            static const IID __uuid_inst = {                             \
                l, w1, w2, {b1, b2, b3, b4, b5, b6, b7, b8}};            \
            return __uuid_inst;                                          \
        }                                                                \
        template <>                                                      \
        inline const GUID &__wsl_stub_uuidof<type *>()                   \
        {                                                                \
            return __wsl_stub_uuidof<type>();                            \
        }                                                                \
    }
#endif
#define __uuidof(type) __wsl_stub_uuidof<__typeof(type)>()
#else
#define __CRT_UUID_DECL(type, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)
#endif
