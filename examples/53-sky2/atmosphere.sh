#ifndef ATMOSPHERE_SH
#define ATMOSPHERE_SH

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

// Reference: Hillaire, Sébastien. "A Scalable and Production Ready Sky and Atmosphere Rendering Technique.
// https://sebh.github.io/publications/egsr2020.pdf

uniform vec4 u_atmoRayleigh; // xyz: rayleigh scatter (1/km), w: rayleigh scale height (km)
uniform vec4 u_atmoMie;      // x: mie scatter, y: mie extinction (1/km), z: mie scale height (km), w: mie phase g
uniform vec4 u_atmoOzone;    // xyz: ozone absorption (1/km), w: multiple scattering strength
uniform vec4 u_atmoPlanet;   // x: bottom radius, y: top radius (km), z: ozone center, w: ozone half-width (km)
uniform vec4 u_atmoGround;

#define ATMO_PI 3.14159265359

#define ATMO_BOTTOM_RADIUS u_atmoPlanet.x
#define ATMO_TOP_RADIUS    u_atmoPlanet.y
#define ATMO_OZONE_CENTER  u_atmoPlanet.z
#define ATMO_OZONE_HALF    u_atmoPlanet.w

#define ATMO_RAYLEIGH_SCATTER u_atmoRayleigh.xyz
#define ATMO_RAYLEIGH_H       u_atmoRayleigh.w

#define ATMO_MIE_SCATTER    u_atmoMie.x
#define ATMO_MIE_EXTINCTION u_atmoMie.y
#define ATMO_MIE_H          u_atmoMie.z
#define ATMO_MIE_G          u_atmoMie.w

#define ATMO_OZONE_ABSORB   u_atmoOzone.xyz
#define ATMO_MS_STRENGTH    u_atmoOzone.w

#define ATMO_GROUND_ALBEDO  u_atmoGround.xyz

void atmosphere_medium(float h, out vec3 scatter_rayleigh, out float scatter_mie, out vec3 extinction) {
	float density_r = exp(-h / ATMO_RAYLEIGH_H);
	float density_m = exp(-h / ATMO_MIE_H);
	float density_o = max(0.0, 1.0 - abs(h - ATMO_OZONE_CENTER) / ATMO_OZONE_HALF);

	scatter_rayleigh = ATMO_RAYLEIGH_SCATTER * density_r;
	scatter_mie      = ATMO_MIE_SCATTER * density_m;

	extinction = ATMO_RAYLEIGH_SCATTER * density_r
			   + vec3_splat(ATMO_MIE_EXTINCTION * density_m)
			   + ATMO_OZONE_ABSORB * density_o;
}

float atmosphere_phase_rayleigh(float cos_theta) {
	return 3.0 / (16.0 * ATMO_PI) * (1.0 + cos_theta * cos_theta);
}

float atmosphere_phase_mie(float cos_theta) {
	float g  = ATMO_MIE_G;
	float g2 = g * g;
	float d  = 1.0 + g2 - 2.0 * g * cos_theta;
	return 3.0 / (8.0 * ATMO_PI) * ((1.0 - g2) * (1.0 + cos_theta * cos_theta)) / ((2.0 + g2) * d * sqrt(max(d, 1e-6)));
}

float atmosphere_dist_to_sphere(float r, float mu, float R) {
	float disc = r * r * (mu * mu - 1.0) + R * R;
	return max(0.0, -r * mu + sqrt(max(disc, 0.0)));
}

bool atmosphere_hits_ground(float r, float mu) {
	return mu < 0.0 && (r * r * (mu * mu - 1.0) + ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS) >= 0.0;
}

// transmittance lut parameterization Bruneton's distance based mapping.
vec2 atmosphere_transmittance_uv(float r, float mu) {
	float H   = sqrt(ATMO_TOP_RADIUS * ATMO_TOP_RADIUS - ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS);
	float rho = sqrt(max(r * r - ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS, 0.0));

	float d     = atmosphere_dist_to_sphere(r, mu, ATMO_TOP_RADIUS);
	float d_min = ATMO_TOP_RADIUS - r;
	float d_max = rho + H;

	return vec2((d - d_min) / (d_max - d_min), rho / H);
}

void atmosphere_transmittance_params(vec2 uv, out float r, out float mu) {
	float H   = sqrt(ATMO_TOP_RADIUS * ATMO_TOP_RADIUS - ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS);
	float rho = uv.y * H;

	r = sqrt(rho * rho + ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS);

	float d_min = ATMO_TOP_RADIUS - r;
	float d_max = rho + H;
	float d     = d_min + uv.x * (d_max - d_min);

	mu = (d <= 0.0) ? 1.0 : clamp((H * H - rho * rho - d * d) / (2.0 * r * d), -1.0, 1.0);
}

// sky view ly parameterization.
vec2 atmosphere_skyview_uv(float r, float view_zenith_cos, float sun_rel_azimuth) {
	float v_horizon      = sqrt(max(r * r - ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS, 0.0));
	float beta           = acos(clamp(v_horizon / r, -1.0, 1.0));
	float zenith_horizon = ATMO_PI - beta;
	float view_zenith    = acos(clamp(view_zenith_cos, -1.0, 1.0));

	float v;
	if (view_zenith < zenith_horizon) {
		float coord = view_zenith / zenith_horizon;
		v = (1.0 - sqrt(1.0 - coord)) * 0.5;
	}
	else {
		float coord = (view_zenith - zenith_horizon) / max(beta, 1e-4);
		v = sqrt(saturate(coord)) * 0.5 + 0.5;
	}

	float u = sun_rel_azimuth / (2.0 * ATMO_PI) + 0.5;
	return vec2(u, v);
}

void atmosphere_skyview_params(vec2 uv, float r, out float view_zenith_cos, out float sun_rel_azimuth) {
	float v_horizon      = sqrt(max(r * r - ATMO_BOTTOM_RADIUS * ATMO_BOTTOM_RADIUS, 0.0));
	float beta           = acos(clamp(v_horizon / r, -1.0, 1.0));
	float zenith_horizon = ATMO_PI - beta;

	float view_zenith;
	if (uv.y < 0.5) {
		float coord = 1.0 - uv.y * 2.0;
		view_zenith = zenith_horizon * (1.0 - coord * coord);
	}
	else {
		float coord = uv.y * 2.0 - 1.0;
		view_zenith = zenith_horizon + beta * coord * coord;
	}

	view_zenith_cos = cos(view_zenith);
	sun_rel_azimuth = (uv.x - 0.5) * 2.0 * ATMO_PI;
}

#endif // ATMOSPHERE_SH
