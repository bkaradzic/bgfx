$input v_dir

/*
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"

SAMPLERCUBE(s_texCube, 0);
SAMPLERCUBE(s_texCubeIrr, 1);

// Ref: http://the-witness.net/news/2012/02/seamless-cube-map-filtering/
vec3 fixCubeLookup(vec3 _v, float _lod, float _topLevelCubeSize)
{
	float ax = abs(_v.x);
	float ay = abs(_v.y);
	float az = abs(_v.z);
	float vmax = max(max(ax, ay), az);
	float scale = 1.0 - exp2(_lod) / _topLevelCubeSize;
	if (ax != vmax) { _v.x *= scale; }
	if (ay != vmax) { _v.y *= scale; }
	if (az != vmax) { _v.z *= scale; }
	return _v;
}

void main()
{
	vec3 dir = normalize(v_dir);

	vec4 color;
	if (u_bgType == 7.0)
	{
		color = toLinear(textureCube(s_texCubeIrr, dir));
	}
	else
	{
		float lod = u_bgType;
		dir = fixCubeLookup(dir, lod, 256.0);
		color = toLinear(textureCubeLod(s_texCube, dir, lod));
	}
	color *= exp2(u_exposure);

	gl_FragColor = toFilmic(color);
}
