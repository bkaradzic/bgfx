// This code is in the public domain -- Ignacio Castaño <castano@gmail.com>

#ifndef NV_CORE_MEMORY_H
#define NV_CORE_MEMORY_H

#include "nvcore.h"
#include <stdlib.h>

namespace nv {

    // C++ helpers.
    template <typename T> inline T * malloc(size_t count) {
        return (T *)::malloc(sizeof(T) * count);
    }

    template <typename T> inline T * realloc(T * ptr, size_t count) {
        return (T *)::realloc(ptr, sizeof(T) * count);
    }

    template <typename T> inline void free(const T * ptr) {
        ::free((void *)ptr);
    }

    template <typename T> inline void zero(T & data) {
        memset(&data, 0, sizeof(T));
    }

} // nv namespace

#endif // NV_CORE_MEMORY_H
