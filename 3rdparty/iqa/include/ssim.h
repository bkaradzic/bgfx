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

#ifndef _SSIM_H_
#define _SSIM_H_

#include "convolve.h"

/*
 * Circular-symmetric Gaussian weighting.
 * h(x,y) = hg(x,y)/SUM(SUM(hg)) , for normalization to 1.0
 * hg(x,y) = e^( -0.5*( (x^2+y^2)/sigma^2 ) ) , where sigma was 1.5
 */
#define GAUSSIAN_LEN 11
static const float g_gaussian_window[GAUSSIAN_LEN][GAUSSIAN_LEN] = {
    {0.000001f, 0.000008f, 0.000037f, 0.000112f, 0.000219f, 0.000274f, 0.000219f, 0.000112f, 0.000037f, 0.000008f, 0.000001f},
    {0.000008f, 0.000058f, 0.000274f, 0.000831f, 0.001619f, 0.002021f, 0.001619f, 0.000831f, 0.000274f, 0.000058f, 0.000008f},
    {0.000037f, 0.000274f, 0.001296f, 0.003937f, 0.007668f, 0.009577f, 0.007668f, 0.003937f, 0.001296f, 0.000274f, 0.000037f},
    {0.000112f, 0.000831f, 0.003937f, 0.011960f, 0.023294f, 0.029091f, 0.023294f, 0.011960f, 0.003937f, 0.000831f, 0.000112f},
    {0.000219f, 0.001619f, 0.007668f, 0.023294f, 0.045371f, 0.056662f, 0.045371f, 0.023294f, 0.007668f, 0.001619f, 0.000219f},
    {0.000274f, 0.002021f, 0.009577f, 0.029091f, 0.056662f, 0.070762f, 0.056662f, 0.029091f, 0.009577f, 0.002021f, 0.000274f},
    {0.000219f, 0.001619f, 0.007668f, 0.023294f, 0.045371f, 0.056662f, 0.045371f, 0.023294f, 0.007668f, 0.001619f, 0.000219f},
    {0.000112f, 0.000831f, 0.003937f, 0.011960f, 0.023294f, 0.029091f, 0.023294f, 0.011960f, 0.003937f, 0.000831f, 0.000112f},
    {0.000037f, 0.000274f, 0.001296f, 0.003937f, 0.007668f, 0.009577f, 0.007668f, 0.003937f, 0.001296f, 0.000274f, 0.000037f},
    {0.000008f, 0.000058f, 0.000274f, 0.000831f, 0.001619f, 0.002021f, 0.001619f, 0.000831f, 0.000274f, 0.000058f, 0.000008f},
    {0.000001f, 0.000008f, 0.000037f, 0.000112f, 0.000219f, 0.000274f, 0.000219f, 0.000112f, 0.000037f, 0.000008f, 0.000001f},
};

/*
 * Equal weight square window.
 * Each pixel is equally weighted (1/64) so that SUM(x) = 1.0
 */
#define SQUARE_LEN 8
static const float g_square_window[SQUARE_LEN][SQUARE_LEN] = {
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
    {0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f, 0.015625f},
};

/* Holds intermediate SSIM values for map-reduce operation. */
struct _ssim_int {
    double l;
    double c;
    double s;
};

/* Defines the pointers to the map-reduce functions. */
typedef int (*_map)(const struct _ssim_int *, void *);
typedef float (*_reduce)(int, int, void *);

/* Arguments for map-reduce. The 'context' is user-defined. */
struct _map_reduce {
    _map map;
    _reduce reduce;
    void *context;
};

/**
 * Private method that calculates the SSIM value on a pre-processed image.
 *
 * The input images must have stride==width. This method does not scale.
 *
 * @note Image buffers are modified.
 *
 * Map-reduce is used for doing the final SSIM calculation. The map function is
 * called for every pixel, and the reduce is called at the end. The context is
 * caller-defined and *not* modified by this method.
 *
 * @param ref Original reference image
 * @param cmp Distorted image
 * @param w Width of the images
 * @param h Height of the images
 * @param k The kernel used as the window function
 * @param mr Optional map-reduce functions to use to calculate SSIM. Required
 *           if 'args' is not null. Ignored if 'args' is null.
 * @param args Optional SSIM arguments for fine control of the algorithm. 0 for defaults.
 *             Defaults are a=b=g=1.0, L=255, K1=0.01, K2=0.03
 * @return The mean SSIM over the entire image (MSSIM), or INFINITY if error.
 */
float _iqa_ssim(float *ref, float *cmp, int w, int h, const struct _kernel *k, const struct _map_reduce *mr, const struct iqa_ssim_args *args);

#endif /* _SSIM_H_ */
