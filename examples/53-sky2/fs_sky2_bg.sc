$input v_texcoord0

/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

// Reference: Hillaire, Sébastien. "A Scalable and Production Ready Sky and Atmosphere Rendering Technique.
// https://sebh.github.io/publications/egsr2020.pdf

#include <bgfx_shader.sh>
#include "atmosphere.sh"
#include "sky2_common.sh"

SAMPLER2D(s_sky_view,           0);
SAMPLER2D(s_atmo_transmittance, 1);

uniform mat4 u_skyInvViewProj;
uniform vec4 u_skyParams;    // x: view radius (km), y: cos sun angular radius, z: sun disc scale
uniform vec4 u_sunDirection;
uniform vec4 u_sunRadiance;

// sun relative azimuth of dir 
float sun_relative_azimuth(vec3 dir, vec3 to_sun) {
	vec2 d = vec2(dir.x, dir.z);
	vec2 s = vec2(to_sun.x, to_sun.z);

	float dl = length(d);
	float sl = length(s);
	if (dl < 1e-5 || sl < 1e-5)
		return 0.0;

	d /= dl;
	s /= sl;

	return atan2(d.x * s.y - d.y * s.x, dot(d, s));
}

void main() {
	// reconstruct the world space view ray
	vec4 nearp = mul(u_skyInvViewProj, vec4(v_texcoord0.xy, 0.0, 1.0));
	vec4 farp  = mul(u_skyInvViewProj, vec4(v_texcoord0.xy, 1.0, 1.0));
	vec3 eye   = nearp.xyz / nearp.w;
	vec3 at    = farp.xyz  / farp.w;
	vec3 dir   = normalize(at - eye);

	float r      = u_skyParams.x;
	vec3  to_sun = -normalize(u_sunDirection.xyz);

	vec2 uv = atmosphere_skyview_uv(r, dir.y, sun_relative_azimuth(dir, to_sun));
	vec3 radiance = texture2DLod(s_sky_view, uv, 0.0).rgb;

	// Sun disc, circumsolar halo
	float cos_view_sun = dot(dir, to_sun);
	if (!atmosphere_hits_ground(r, dir.y)) {
		vec3 transmittance = texture2DLod(s_atmo_transmittance, atmosphere_transmittance_uv(r, dir.y), 0.0).rgb;

		float halo = exp2(-(1.0 - cos_view_sun) * 12000.0);
		radiance += u_sunRadiance.rgb * transmittance * (u_skyParams.z * 0.03) * halo;

		if (cos_view_sun >= u_skyParams.y) {
			float x2   = saturate((1.0 - cos_view_sun) / max(1.0 - u_skyParams.y, 1e-7));
			float limb = pow(max(1.0 - x2, 0.0), 0.3);
			radiance += u_sunRadiance.rgb * u_skyParams.z * transmittance * limb;
		}
	}

	gl_FragColor = vec4(sky2_tonemap(radiance), 1.0);
}
