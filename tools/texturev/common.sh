/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

uniform vec4 u_params0;
#define u_textureLod   u_params0.x
#define u_textureLayer u_params0.y
#define u_inLinear     u_params0.z
#define u_ev           u_params0.w

uniform vec4 u_params1;
#define u_outputFormat u_params1.x
#define u_sdrWhiteNits u_params1.y

vec3 toLinear(vec3 _rgb)
{
	return pow(abs(_rgb), vec3_splat(2.2) );
}

vec3 toGamma(vec3 _rgb)
{
	return pow(abs(_rgb), vec3_splat(1.0/2.2) );
}

vec3 applyExposure(vec3 _rgb)
{
	vec3 rgb = mix(toLinear(_rgb.xyz), _rgb.xyz, u_inLinear);
	return (rgb * pow(2.0, u_ev) );
}

vec4 toEv(vec4 _color)
{
	return vec4(toGamma(applyExposure(_color.xyz) ), _color.w);
}

float toSrgbGamma(float _val)
{
	if (_val <= 0.0031308)
	{
		return 12.92 * _val;
	}
	else
	{
		return 1.055 * pow(_val, (1.0/2.4) ) - 0.055;
	}
}

vec3 toSrgbGamma(vec3 _rgb)
{
	_rgb.x = toSrgbGamma(_rgb.x);
	_rgb.y = toSrgbGamma(_rgb.y);
	_rgb.z = toSrgbGamma(_rgb.z);
	return _rgb;
}

vec3 toXyzFromSrgb(vec3 _rgb)
{
	mat3 toXYZ = mat3(
		0.4125564, 0.3575761, 0.1804375,
		0.2126729, 0.7151522, 0.0721750,
		0.0193339, 0.1191920, 0.9503041
	);
	return mul(toXYZ, _rgb);
}

vec3 toRec2020FromXyz(vec3 _xyz)
{
	mat3 toRec2020 = mat3(
		1.7166512, -0.3556708, -0.2533663,
	   -0.6666844,  1.6164812,  0.0157685,
	    0.0176399, -0.0427706,  0.9421031
	);
	return mul(toRec2020, _xyz);
}


vec3 toPqOetf(vec3 _color)
{
	// reference PQ OETF will yield reference OOTF when
	// displayed on  a reference monitor employing EOTF

	float m1 = 0.1593017578125;
	float m2 = 78.84375;
	float c1 = 0.8359375;
	float c2 = 18.8515625;
	float c3 = 18.6875;

	vec3 Ym1 = pow(_color.xyz * (1.0/10000.0), vec3_splat(m1) );
	_color = pow((c1 + c2*Ym1) / (vec3_splat(1.0) + c3*Ym1), vec3_splat(m2) );

	return _color;
}

vec4 toOutput(vec4 _color, float _outputFormat, float _sdrWhiteNits)
{
	// assumed that _color is linear with sRGB/rec709 primaries
	// and 1.0 is SDR white point

	vec3 outColor = vec3_splat(0.0);

	if (_outputFormat < 0.5)
	{
		// output == 0 -> sRGB/rec709, apply gamma
		// values over 1.0 will saturate
		outColor = toSrgbGamma(saturate(_color.xyz));
	}
	else if (_outputFormat < 1.5)
	{
		// output == 1 -> scRGB, remains linear.
		// values over 1.0 will appear as HDR
		outColor = _color.xyz;
	}
	else if (_outputFormat < 2.5)
	{
		// output == 2 -> PQ
		
		// change primaries from sRGB/rec709 to rec2020
		vec3 _xyz = toXyzFromSrgb(_color.xyz);
		outColor = toRec2020FromXyz(_xyz);

		// if 1.0 is SDR white, should map to 80 nits
		// but that could lead to dim results as SDR
		// monitors tend to be brighter than standard
		outColor = toPqOetf(outColor * _sdrWhiteNits);
	}

	return vec4(outColor, _color.w);
}
