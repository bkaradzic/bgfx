/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// Odd height: two bilinear samples along Y to avoid undersampling.
#define NON_POWER_OF_TWO 2
#include "cs_mipgen.sh"
