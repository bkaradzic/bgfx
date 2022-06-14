$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

// don't use 5x5 sample pattern for spatial denoise, use 3x3 instead
#define USE_SPATIAL_5X5     0

// includes main function to implement spatial pattern
#include "fs_denoise_spatial_implementation.sh"
