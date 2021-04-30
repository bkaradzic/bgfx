$input a_position
$output v_lightCenterScale, v_color0

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_sphereInfo;
uniform mat4 u_invMvpShadow;


// Note texture binding starts at slot 2.  Problem is that vert textures and frag textures are different.
SAMPLER2D(s_shadowMap, 2);  // Used to reconstruct 3d position for lights
SAMPLER2D(s_rsm,       3);  // Reflective shadow map, used to scale/color light

void main()
{
	// Calculate vertex position
	vec3 objectSpacePos = a_position;
	vec2 texCoord       = u_sphereInfo.xy;

	// Get world position using the shadow map
	float deviceDepth = texture2DLod(s_shadowMap, texCoord, 0).x;
	float depth       = toClipSpaceDepth(deviceDepth);
	vec3 clip = vec3(texCoord * 2.0 - 1.0, depth);
#if !BGFX_SHADER_LANGUAGE_GLSL
	clip.y = -clip.y;
#endif // !BGFX_SHADER_LANGUAGE_GLSL
	vec3 wPos = clipToWorld(u_invMvpShadow, clip);
	wPos.y -= 0.001;  // Would be much better to perturb in normal direction, but I didn't do that.

	// Scale and color are already in the rsm
	vec4 rsm = texture2DLod(s_rsm, texCoord, 0).xyzw;
	float radScale = u_sphereInfo.z;
	float rad = rsm.w * radScale;

	gl_Position = mul(u_viewProj, vec4(wPos+objectSpacePos*rad, 1.0) );

	v_lightCenterScale.xyz = wPos.xyz;
	v_lightCenterScale.w = rad;
	v_color0.xyz = rsm.xyz;
}
