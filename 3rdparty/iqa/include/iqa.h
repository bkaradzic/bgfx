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

#ifndef _IQA_H_
#define _IQA_H_

#include "iqa_os.h"

/**
 * Allows fine-grain control of the SSIM algorithm.
 */
struct iqa_ssim_args {
    float alpha;    /**< luminance exponent */
    float beta;     /**< contrast exponent */
    float gamma;    /**< structure exponent */
    int L;          /**< dynamic range (2^8 - 1)*/
    float K1;       /**< stabilization constant 1 */
    float K2;       /**< stabilization constant 2 */
    int f;          /**< scale factor. 0=default scaling, 1=no scaling */
};

/**
 * Allows fine-grain control of the MS-SSIM algorithm.
 */
struct iqa_ms_ssim_args {
    int wang;             /**< 1=original algorithm by Wang, et al. 0=MS-SSIM* by Rouse/Hemami (default). */
    int gaussian;         /**< 1=11x11 Gaussian window (default). 0=8x8 linear window. */
    int scales;           /**< Number of scaled images to use. Default is 5. */
    const float *alphas;  /**< Pointer to array of alpha values for each scale. Required if 'scales' isn't 5. */
    const float *betas;   /**< Pointer to array of beta values for each scale. Required if 'scales' isn't 5. */
    const float *gammas;  /**< Pointer to array of gamma values for each scale. Required if 'scales' isn't 5. */
};

/**
 * Calculates the Mean Squared Error between 2 equal-sized 8-bit images.
 * @note The images must have the same width, height, and stride.
 * @param ref Original reference image
 * @param cmp Distorted image
 * @param w Width of the images
 * @param h Height of the images
 * @param stride The length (in bytes) of each horizontal line in the image.
 *               This may be different from the image width.
 * @return The MSE.
 */
float iqa_mse(const unsigned char *ref, const unsigned char *cmp, int w, int h, int stride);

/**
 * Calculates the Peak Signal-to-Noise-Ratio between 2 equal-sized 8-bit
 * images.
 * @note The images must have the same width, height, and stride.
 * @param ref Original reference image
 * @param cmp Distorted image
 * @param w Width of the images
 * @param h Height of the images
 * @param stride The length (in bytes) of each horizontal line in the image.
 *               This may be different from the image width.
 * @return The PSNR.
 */
float iqa_psnr(const unsigned char *ref, const unsigned char *cmp, int w, int h, int stride);

/**
 * Calculates the Structural SIMilarity between 2 equal-sized 8-bit images.
 *
 * See https://ece.uwaterloo.ca/~z70wang/publications/ssim.html
 * @note The images must have the same width, height, and stride.
 * @param ref Original reference image
 * @param cmp Distorted image
 * @param w Width of the images
 * @param h Height of the images
 * @param stride The length (in bytes) of each horizontal line in the image.
 *               This may be different from the image width.
 * @param gaussian 0 = 8x8 square window, 1 = 11x11 circular-symmetric Gaussian
 * weighting.
 * @param args Optional SSIM arguments for fine control of the algorithm. 0 for
 * defaults. Defaults are a=b=g=1.0, L=255, K1=0.01, K2=0.03
 * @return The mean SSIM over the entire image (MSSIM), or INFINITY if error.
 */
float iqa_ssim(const unsigned char *ref, const unsigned char *cmp, int w, int h, int stride, 
    int gaussian, const struct iqa_ssim_args *args);

/**
 * Calculates the Multi-Scale Structural SIMilarity between 2 equal-sized 8-bit
 * images. The default algorithm is MS-SSIM* proposed by Rouse/Hemami 2008.
 *
 * See https://ece.uwaterloo.ca/~z70wang/publications/msssim.pdf and
 * http://foulard.ece.cornell.edu/publications/dmr_hvei2008_paper.pdf
 *
 * @note 1. The images must have the same width, height, and stride.
 * @note 2. The minimum image width or height is 2^(scales-1) * filter, where 'filter' is 11
 * if a Gaussian window is being used, or 9 otherwise.
 * @param ref Original reference image
 * @param cmp Distorted image
 * @param w Width of the images.
 * @param h Height of the images.
 * @param stride The length (in bytes) of each horizontal line in the image.
 *               This may be different from the image width.
 * @param args Optional MS-SSIM arguments for fine control of the algorithm. 0
 * for defaults. Defaults are wang=0, scales=5, gaussian=1.
 * @return The mean MS-SSIM over the entire image, or INFINITY if error.
 */
float iqa_ms_ssim(const unsigned char *ref, const unsigned char *cmp, int w, int h, int stride, 
    const struct iqa_ms_ssim_args *args);

#endif /*_IQA_H_*/
