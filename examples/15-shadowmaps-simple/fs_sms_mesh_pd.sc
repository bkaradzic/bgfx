$input v_view, v_normal, v_shadowcoord

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

#define SHADOW_PACKED_DEPTH 1
#include "fs_sms_shadow.sh"
