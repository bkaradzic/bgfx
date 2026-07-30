/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

// Reference: Hillaire, Sébastien. "A Scalable and Production Ready Sky and Atmosphere Rendering Technique.
// https://sebh.github.io/publications/egsr2020.pdf

#include <bgfx_compute.sh>
#include "atmosphere.sh"

IMAGE2D_WO(s_transmittance_out, rgba16f, 0);

#define LUT_WIDTH  256
#define LUT_HEIGHT 64
#define STEPS      40

NUM_THREADS(8, 8, 1)
void main() {
	ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
	if (coord.x >= LUT_WIDTH || coord.y >= LUT_HEIGHT)
		return;

	vec2 uv = (vec2(coord) + vec2(0.5, 0.5)) / vec2(LUT_WIDTH, LUT_HEIGHT);

	float r, mu;
	atmosphere_transmittance_params(uv, r, mu);

	float t_max = atmosphere_dist_to_sphere(r, mu, ATMO_TOP_RADIUS);
	float dt    = t_max / float(STEPS);

	vec3 optical_depth = vec3(0.0, 0.0, 0.0);
	for (int i = 0; i < STEPS; i++) {
		float t = (float(i) + 0.5) * dt;
		float h = sqrt(r * r + t * t + 2.0 * r * mu * t) - ATMO_BOTTOM_RADIUS;

		vec3  scatter_r;
		float scatter_m;
		vec3  extinction;
		atmosphere_medium(max(h, 0.0), scatter_r, scatter_m, extinction);

		optical_depth += extinction * dt;
	}

	imageStore(s_transmittance_out, coord, vec4(exp(-optical_depth), 1.0));
}
