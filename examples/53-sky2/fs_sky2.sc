$input v_normal, v_wpos

/*
 * Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

#define TERRAIN_TILE        0.5 // in km
#define TERRAIN_ROCK_SLOPE  0.1

SAMPLER2D(s_grass, 0);
SAMPLER2D(s_rock,  1);

void main() {
    vec3 N = normalize(v_normal);

    vec3 tw = abs(N);
    tw = tw * tw * tw;
    tw = tw / max(tw.x + tw.y + tw.z, 1e-4);

    vec3 pw = v_wpos * TERRAIN_TILE;

    vec3 grass = texture2D(s_grass, pw.zy).xyz * tw.x
               + texture2D(s_grass, pw.xz).xyz * tw.y
               + texture2D(s_grass, pw.xy).xyz * tw.z;

    vec3 rock  = texture2D(s_rock, pw.zy).xyz * tw.x
               + texture2D(s_rock, pw.xz).xyz * tw.y
               + texture2D(s_rock, pw.xy).xyz * tw.z;

    float slope  = 1.0 - N.y;
    float rockW  = smoothstep(TERRAIN_ROCK_SLOPE, TERRAIN_ROCK_SLOPE + 0.2, slope);
    vec3  albedo = mix(grass, rock, rockW);

    gl_FragColor = vec4(albedo, 1.0);
}
