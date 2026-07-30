$input v_normal, v_wpos

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

// Reference: Hillaire, Sébastien. "A Scalable and Production Ready Sky and Atmosphere Rendering Technique.
// https://sebh.github.io/publications/egsr2020.pdf

#include <bgfx_shader.sh>
#include "atmosphere.sh"
#include "sky2_common.sh"

#define TERRAIN_TILE        0.5 // in km
#define TERRAIN_ROCK_SLOPE  0.1

SAMPLER2D(s_atmo_transmittance, 0);
SAMPLER2D(s_atmo_multiscatter,  1);
SAMPLER2D(s_sky_view,           2);
SAMPLER2D(s_grass,              3);
SAMPLER2D(s_rock,               4);

uniform vec4 u_sunDirection;
uniform vec4 u_sunRadiance;
uniform vec4 u_cameraPos;     // (km)
uniform vec4 u_skyParams;     // x: view radius (km)
uniform vec4 u_aerialParams;  // x: in-scatter, y: density, z: ambient

#define AERIAL_STEPS 16

vec3 tr_lut(float r, float mu) {
	return texture2DLod(s_atmo_transmittance, atmosphere_transmittance_uv(r, mu), 0.0).rgb;
}

vec3 ms_lut(float r, float mu_sun) {
	vec2 uv = vec2(mu_sun * 0.5 + 0.5, (r - ATMO_BOTTOM_RADIUS) / (ATMO_TOP_RADIUS - ATMO_BOTTOM_RADIUS));
	return texture2DLod(s_atmo_multiscatter, uv, 0.0).rgb;
}

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

	// srgb -> linear
	grass = pow(grass, vec3_splat(2.2));
	rock  = pow(rock,  vec3_splat(2.2));

	float slope  = 1.0 - N.y;
	float rockW  = smoothstep(TERRAIN_ROCK_SLOPE, TERRAIN_ROCK_SLOPE + 0.2, slope);
	vec3  albedo = mix(grass, rock, rockW);

	vec3  to_sun = -normalize(u_sunDirection.xyz);
	float mu_sun = to_sun.y;

	float frag_alt = max(v_wpos.y, 0.0);
	float surf_r   = ATMO_BOTTOM_RADIUS + frag_alt;

	// direct sun Lambert BRDF
	vec3  sun_t  = tr_lut(surf_r, mu_sun);
	float ndotl  = max(dot(N, to_sun), 0.0);
	vec3  direct = albedo * (1.0 / ATMO_PI) * u_sunRadiance.rgb * sun_t * ndotl;

	float lut_r = u_skyParams.x;
	vec3  sky_avg = texture2DLod(s_sky_view, atmosphere_skyview_uv(lut_r, 1.00, 0.0), 0.0).rgb
	              + texture2DLod(s_sky_view, atmosphere_skyview_uv(lut_r, 0.35, 0.0), 0.0).rgb
	              + texture2DLod(s_sky_view, atmosphere_skyview_uv(lut_r, 0.35, ATMO_PI), 0.0).rgb;
	sky_avg *= 1.0 / 3.0;

	vec3 ambient = albedo * sky_avg * (0.4 + 0.6 * saturate(N.y) ) * u_aerialParams.z;

	vec3 lit = direct + ambient;

	// aerial perspective march camera -> fragment
	vec3  cam  = u_cameraPos.xyz;
	vec3  ray  = v_wpos - cam;
	float dist = length(ray);
	vec3  vdir = ray / max(dist, 1e-6);

	float cos_sun_view = dot(vdir, to_sun);
	float phase_r = atmosphere_phase_rayleigh(cos_sun_view);
	float phase_m = atmosphere_phase_mie(cos_sun_view);

	float density = u_aerialParams.y;
	float dt      = dist / float(AERIAL_STEPS);

	vec3 throughput = vec3(1.0, 1.0, 1.0);
	vec3 inscatter  = vec3(0.0, 0.0, 0.0);

	for (int i = 0; i < AERIAL_STEPS; i++) {
		float t   = (float(i) + 0.5) * dt;
		vec3  p   = cam + vdir * t;
		float alt = max(p.y, 0.0);
		float sr  = ATMO_BOTTOM_RADIUS + alt;

		vec3  scatter_r;
		float scatter_m;
		vec3  extinction;
		atmosphere_medium(alt, scatter_r, scatter_m, extinction);

		scatter_r  *= density;
		scatter_m  *= density;
		extinction *= density;

		vec3 st  = tr_lut(sr, mu_sun);
		vec3 psi = ms_lut(sr, mu_sun) * ATMO_MS_STRENGTH;

		vec3 S = (scatter_r * phase_r + vec3_splat(scatter_m * phase_m)) * st
		       + (scatter_r + vec3_splat(scatter_m)) * psi;
		S *= u_sunRadiance.rgb;

		vec3 step_t = exp(-extinction * dt);
		vec3 safe_e = max(extinction, vec3_splat(1e-7));

		inscatter  += throughput * (S - S * step_t) / safe_e;
		throughput *= step_t;
	}

	vec3 color = lit * throughput + inscatter * u_aerialParams.x;

	gl_FragColor = vec4(sky2_tonemap(color), 1.0);
}
