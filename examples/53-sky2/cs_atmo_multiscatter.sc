/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

// Reference: Hillaire, Sébastien. "A Scalable and Production Ready Sky and Atmosphere Rendering Technique.
// https://sebh.github.io/publications/egsr2020.pdf

#include <bgfx_compute.sh>
#include "atmosphere.sh"

// multiple scattering lut

SAMPLER2D(s_atmo_transmittance, 0);

IMAGE2D_WO(s_multiscatter_out, rgba16f, 1);

#define LUT_SIZE   32
#define DIR_COUNT  8
#define STEPS      20

vec3 sample_transmittance(float r, float mu) {
	return texture2DLod(s_atmo_transmittance, atmosphere_transmittance_uv(r, mu), 0.0).rgb;
}

NUM_THREADS(8, 8, 1)
void main() {
	ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
	if (coord.x >= LUT_SIZE || coord.y >= LUT_SIZE)
		return;

	vec2 uv = (vec2(coord) + vec2(0.5, 0.5)) / vec2(LUT_SIZE, LUT_SIZE);

	float sun_cos = uv.x * 2.0 - 1.0;
	float r       = ATMO_BOTTOM_RADIUS + uv.y * (ATMO_TOP_RADIUS - ATMO_BOTTOM_RADIUS) + 0.01;

	vec3 sun_dir = vec3(sqrt(max(1.0 - sun_cos * sun_cos, 0.0)), 0.0, sun_cos); // zenith = +Z here

	vec3 luminance = vec3(0.0, 0.0, 0.0);
	vec3 f_ms      = vec3(0.0, 0.0, 0.0);

	const float sphere_solid_angle = 4.0 * ATMO_PI;
	const float inv_samples        = 1.0 / float(DIR_COUNT * DIR_COUNT);
	const float uniform_phase      = 1.0 / sphere_solid_angle;

	for (int a = 0; a < DIR_COUNT; a++) {
		for (int b = 0; b < DIR_COUNT; b++) {
			float cos_theta = 1.0 - 2.0 * (float(a) + 0.5) / float(DIR_COUNT);
			float sin_theta = sqrt(max(1.0 - cos_theta * cos_theta, 0.0));
			float phi       = 2.0 * ATMO_PI * (float(b) + 0.5) / float(DIR_COUNT);

			vec3 dir = vec3(sin_theta * cos(phi), sin_theta * sin(phi), cos_theta);

			bool  ground = atmosphere_hits_ground(r, dir.z);
			float t_max;
			if (ground)
				t_max = max(0.0, -r * dir.z - sqrt(max(r * r * (dir.z * dir.z - 1.0) + ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS, 0.0)));
			else
				t_max = atmosphere_dist_to_sphere(r, dir.z, ATMO_TOP_RADIUS);

			float dt = t_max / float(STEPS);

			vec3 throughput = vec3(1.0, 1.0, 1.0);
			vec3 L          = vec3(0.0, 0.0, 0.0);
			vec3 Lf         = vec3(0.0, 0.0, 0.0);

			float cos_sun = dot(dir, sun_dir);
			float phase_r = atmosphere_phase_rayleigh(cos_sun);
			float phase_m = atmosphere_phase_mie(cos_sun);

			for (int s = 0; s < STEPS; s++) {
				float t = (float(s) + 0.5) * dt;

				vec3  pos      = vec3(0.0, 0.0, r) + dir * t;
				float sample_r = length(pos);
				float h        = sample_r - ATMO_BOTTOM_RADIUS;
				float mu_sun   = dot(pos, sun_dir) / sample_r;

				vec3  scatter_r;
				float scatter_m;
				vec3  extinction;
				atmosphere_medium(max(h, 0.0), scatter_r, scatter_m, extinction);

				vec3 scatter_total = scatter_r + vec3_splat(scatter_m);

				vec3 sun_transmittance = sample_transmittance(sample_r, mu_sun);
				bool sun_shadowed      = atmosphere_hits_ground(sample_r, mu_sun);

				vec3 S = (scatter_r * phase_r + vec3_splat(scatter_m * phase_m)) * sun_transmittance * (sun_shadowed ? 0.0 : 1.0);

				vec3 step_transmittance = exp(-extinction * dt);
				vec3 safe_extinction    = max(extinction, vec3_splat(1e-7));

				L  += throughput * (S             - S             * step_transmittance) / safe_extinction;
				Lf += throughput * (scatter_total - scatter_total * step_transmittance) / safe_extinction;

				throughput *= step_transmittance;
			}

			if (ground) {
				vec3  pos_ground = vec3(0.0, 0.0, r) + dir * t_max;
				float mu_ground  = clamp(dot(pos_ground, sun_dir) / ATMO_BOTTOM_RADIUS, -1.0, 1.0);
				vec3  sun_t      = sample_transmittance(ATMO_BOTTOM_RADIUS, mu_ground);
				L += throughput * sun_t * max(mu_ground, 0.0) * ATMO_GROUND_ALBEDO / ATMO_PI;
			}

			luminance += L * uniform_phase * sphere_solid_angle * inv_samples;
			f_ms      += Lf * uniform_phase * sphere_solid_angle * inv_samples;
		}
	}

	vec3 psi = luminance / max(vec3_splat(1.0) - f_ms, vec3_splat(1e-4));

	imageStore(s_multiscatter_out, coord, vec4(psi, 1.0));
}
