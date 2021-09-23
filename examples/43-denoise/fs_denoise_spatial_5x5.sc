$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

// use 5x5 sample pattern for spatial denoise
#define USE_SPATIAL_5X5     1

// includes main function to implement spatial pattern
#include "fs_denoise_spatial_implementation.sh"
