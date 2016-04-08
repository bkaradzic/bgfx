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

#ifndef _CONVOLVE_H_
#define _CONVOLVE_H_

typedef float (*_iqa_get_pixel)(const float *img, int w, int h, int x, int y, float bnd_const);

/** Out-of-bounds array values are a mirrored reflection of the border values*/
float KBND_SYMMETRIC(const float *img, int w, int h, int x, int y, float bnd_const);
/** Out-of-bounds array values are set to the nearest border value */
float KBND_REPLICATE(const float *img, int w, int h, int x, int y, float bnd_const);
/** Out-of-bounds array values are set to 'bnd_const' */
float KBND_CONSTANT(const float *img, int w, int h, int x, int y, float bnd_const);


/** Defines a convolution kernel */
struct _kernel {
    float *kernel;          /**< Pointer to the kernel values */
    int w;                  /**< The kernel width */
    int h;                  /**< The kernel height */
    int normalized;         /**< 1 if the kernel values add up to 1. 0 otherwise */
    _iqa_get_pixel bnd_opt; /**< Defines how out-of-bounds image values are handled */
    float bnd_const;        /**< If 'bnd_opt' is KBND_CONSTANT, this specifies the out-of-bounds value */
};

/**
 * @brief Applies the specified kernel to the image.
 * The kernel will be applied to all areas where it fits completely within
 * the image. The resulting image will be smaller by half the kernel width 
 * and height (w - kw/2 and h - kh/2).
 *
 * @param img Image to modify
 * @param w Image width
 * @param h Image height
 * @param k The kernel to apply
 * @param result Buffer to hold the resulting image ((w-kw)*(h-kh), where kw
 *               and kh are the kernel width and height). If 0, the result
 *               will be written to the original image buffer.
 * @param rw Optional. The width of the resulting image will be stored here.
 * @param rh Optional. The height of the resulting image will be stored here.
 */
void _iqa_convolve(float *img, int w, int h, const struct _kernel *k, float *result, int *rw, int *rh);

/**
 * The same as _iqa_convolve() except the kernel is applied to the entire image.
 * In other words, the kernel is applied to all areas where the top-left corner
 * of the kernel is in the image. Out-of-bound pixel value (off the right and
 * bottom edges) are chosen based on the 'bnd_opt' and 'bnd_const' members of
 * the kernel structure. The resulting array is the same size as the input
 * image.
 *
 * @param img Image to modify
 * @param w Image width
 * @param h Image height
 * @param k The kernel to apply
 * @param result Buffer to hold the resulting image ((w-kw)*(h-kh), where kw
 *               and kh are the kernel width and height). If 0, the result
 *               will be written to the original image buffer.
 * @return 0 if successful. Non-zero otherwise.
 */
int _iqa_img_filter(float *img, int w, int h, const struct _kernel *k, float *result);

/**
 * Returns the filtered version of the specified pixel. If no kernel is given,
 * the raw pixel value is returned.
 * 
 * @param img Source image
 * @param w Image width
 * @param h Image height
 * @param x The x location of the pixel to filter
 * @param y The y location of the pixel to filter
 * @param k Optional. The convolution kernel to apply to the pixel.
 * @param kscale The scale of the kernel (for normalization). 1 for normalized
 *               kernels. Required if 'k' is not null.
 * @return The filtered pixel value.
 */
float _iqa_filter_pixel(const float *img, int w, int h, int x, int y, const struct _kernel *k, const float kscale);


#endif /*_CONVOLVE_H_*/
