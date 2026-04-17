/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// Both dimensions odd: four bilinear samples to avoid undersampling.
#define NON_POWER_OF_TWO 3
#include "cs_mipgen.sh"
