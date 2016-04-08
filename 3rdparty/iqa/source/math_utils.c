/*
 * Copyright (c) 2011, Tom Distler (http://tdistler.com)
 * All rights reserved.
 *
 * The BSD License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * - Neither the name of the tdistler.com nor the names of its contributors may
 *   be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "math_utils.h"
#include <math.h>

int _round(float a)
{
    int sign_a = a > 0.0f ? 1 : -1;
    return a-(int)a >= 0.5 ? (int)a + sign_a : (int)a;
}

int _max(int x, int y)
{
    return x >= y ? x : y;
}

int _min(int x, int y)
{
    return x <= y ? x : y;
}

int _cmp_float(float a, float b, int digits)
{
    /* Round */
    int sign_a = a > 0.0f ? 1 : -1;
    int sign_b = b > 0.0f ? 1 : -1;
    double scale = pow(10.0, (double)digits);
    double ax = a * scale;
    double bx = b * scale;
    int ai = ax-(int)ax >= 0.5 ? (int)ax + sign_a : (int)ax;
    int bi = bx-(int)bx >= 0.5 ? (int)bx + sign_b : (int)bx;

    /* Compare */
    return ai == bi ? 0 : 1;
}

int _matrix_cmp(const float *a, const float *b, int w, int h, int digits)
{
    int offset;
    int result=0;
    int len=w*h;
    for (offset=0; offset<len; ++offset) {
        if (_cmp_float(a[offset], b[offset], digits)) {
            result = 1;
            break;
        }
    }

    return result;
}

