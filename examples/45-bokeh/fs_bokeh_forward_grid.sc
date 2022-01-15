$input v_normal, v_texcoord0, v_texcoord1, v_texcoord2

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"

// struct ModelUniforms
uniform vec4 u_modelParams[2];

#define u_color				(u_modelParams[0].xyz)
#define u_lightPosition		(u_modelParams[1].xyz)


int ModHelper (float a, float b)
{
	return int( a - (b*floor(a/b)));
}

vec3 GetGridColor (vec2 position, float width, vec3 color)
{
	position = abs(floor( position + vec2(-width, -width) ));
	int posXMod = ModHelper(position.x, 2.0);
	int posYMod = ModHelper(position.y, 2.0);
	float gridColorScale = (posXMod == posYMod) ? 0.75 : 1.25;
	return toLinear(color) * gridColorScale;
}

void main()
{
	vec3 worldSpacePosition = v_texcoord1.xyz; // contains ws pos
	vec2 gridCoord = worldSpacePosition.xz; // assuming y is up
	vec3 gridColor = GetGridColor(gridCoord.xy, 0.002, u_color);

	// get vertex normal
	vec3 normal = normalize(v_normal);

	vec3 light = (u_lightPosition - worldSpacePosition);
	light = normalize(light);

	float NdotL = saturate(dot(normal, light));
	float diffuse = NdotL * 1.0;

	vec3 V = v_texcoord2.xyz; // contains view vector
	vec3 H = normalize(V+light);
	float NdotH = saturate(dot(normal, H));
	float specular = 5.0 * pow(NdotH, 256);
	float ambient = 0.1;

	float lightAmount = ambient + diffuse;
	vec3 color = gridColor * lightAmount + specular;

	// leave color in linear space for better dof filter result

	gl_FragColor = vec4(color, 1.0);
}
