$input v_view, v_normal, v_shadowcoord

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

#define SHADOW_PACKED_DEPTH 0
#include "fs_sms_shadow.sh"
