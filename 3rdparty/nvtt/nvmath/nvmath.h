// This code is in the public domain -- castanyo@yahoo.es

#ifndef NV_MATH_H
#define NV_MATH_H

#include <cmath>
#include <float.h>  // finite, isnan

#include "nvcore/utils.h"   // max, clamp

#define NVMATH_API
#define NVMATH_CLASS

#define PI                  float(3.1415926535897932384626433833)
#define NV_EPSILON          (0.0001f)
#define NV_NORMAL_EPSILON   (0.001f)

namespace nv
{
    inline float toRadian(float degree) { return degree * (PI / 180.0f); }
    inline float toDegree(float radian) { return radian * (180.0f / PI); }

    // Robust floating point comparisons:
    // http://realtimecollisiondetection.net/blog/?p=89
    inline bool equal(const float f0, const float f1, const float epsilon = NV_EPSILON)
    {
        //return fabs(f0-f1) <= epsilon;
        return fabs(f0-f1) <= epsilon * max3(1.0f, fabsf(f0), fabsf(f1));
    }

    inline bool isZero(const float f, const float epsilon = NV_EPSILON)
    {
        return fabsf(f) <= epsilon;
    }

    inline bool isFinite(const float f)
    {
		return std::isfinite(f);
    }

    // Eliminates negative zeros from a float array.
    inline void floatCleanup(float * fp, int n)
    {
        for (int i = 0; i < n; i++) {
            //nvDebugCheck(isFinite(fp[i]));
            union { float f; uint32 i; } x = { fp[i] };
            if (x.i == 0x80000000) fp[i] = 0.0f;
        }
    }

    inline float saturate(float f) {
        return clamp(f, 0.0f, 1.0f);
    }
}

#endif // NV_MATH_H
