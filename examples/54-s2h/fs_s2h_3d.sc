$input v_color0, v_texcoord0

// Self-contained fragment-renderer port of Features/3D_example.hlsl.
#include "../common/common.sh"
#include "s2h_bgfx.sh"
#include "s2h.hlsl"
#include "s2h_3d.hlsl"

uniform vec4 u_s2hTime;

void scene(inout Context3D _context)
{
	float3 offset = float3(0.0f, -1.0f, 0.0f);
	s2h_drawCheckerBoard(_context, offset);
	s2h_drawLineWS(_context, float3(-1.0f, 2.0f,  1.0f) + offset, float3(1.0f, 2.0f,  1.0f) + offset, float4(1.0f, 1.0f, 0.0f, 1.0f), 0.09f);
	s2h_drawLineWS(_context, float3(-1.0f, 2.0f, -1.0f) + offset, float3(1.0f, 2.0f, -1.0f) + offset, float4(1.0f, 1.0f, 0.0f, 1.0f), 0.09f);
	s2h_drawLineWS(_context, float3(-1.0f, 2.0f, -1.0f) + offset, float3(-1.0f, 2.0f, 1.0f) + offset, float4(1.0f, 1.0f, 0.0f, 1.0f), 0.09f);
	s2h_drawLineWS(_context, float3( 1.0f, 2.0f, -1.0f) + offset, float3( 1.0f, 2.0f, 1.0f) + offset, float4(1.0f, 1.0f, 0.0f, 1.0f), 0.09f);
}

float3 safeNormalize(float3 _value)
{
	return _value / max(length(_value), 0.0001f);
}

float4x4 lookAt(float3 _eye, float3 _target, float3 _up)
{
	float3 zaxis = safeNormalize(_target - _eye);
	float3 xaxis = safeNormalize(cross(_up, zaxis));
	float3 yaxis = cross(zaxis, xaxis);
	// HLSL float4x4 constructors receive rows, while GLSL mat4 constructors
	// receive columns. s2h_drawBasis expects world-space basis vectors in the
	// matrix columns, so only the HLSL path needs the transpose.
#if BGFX_SHADER_LANGUAGE_GLSL
	return float4x4(float4(xaxis, 0.0f), float4(yaxis, 0.0f), float4(zaxis, 0.0f), float4(_eye, 1.0f));
#else
	return transpose(float4x4(float4(xaxis, 0.0f), float4(yaxis, 0.0f), float4(zaxis, 0.0f), float4(_eye, 1.0f)));
#endif
}

void main()
{
	float2 resolution = u_viewRect.zw;
	float2 pixel = s2h_getPixelCoord(gl_FragCoord.xy);
	float2 uv = pixel / resolution;
	float2 screen = uv * 2.0f - 1.0f;
	screen.x *= resolution.x / resolution.y;
	screen.y = -screen.y;

	float orbit = u_s2hTime.x * 0.35f;
	float3 cameraPosition = float3(sin(orbit) * 5.0f, 2.5f, cos(orbit) * 5.0f);
	float3 cameraForward = safeNormalize(float3(0.0f, 0.4f, 0.0f) - cameraPosition);
	float3 cameraRight = safeNormalize(cross(float3(0.0f, 1.0f, 0.0f), cameraForward));
	float3 cameraUp = cross(cameraForward, cameraRight);
	float3 rayDirection = safeNormalize(cameraForward + screen.x * cameraRight * 0.8f + screen.y * cameraUp * 0.8f);

	Context3D context;
	s2h_init(context, cameraPosition, rayDirection);
	context.dstColor = float4(safeNormalize(rayDirection * 0.5f + 0.5f) * 0.25f, 1.0f);
	sceneWithShadows(context);
	scene(context);

	float s = sin(u_s2hTime.x) * 3.0f;
	float c = cos(u_s2hTime.x) * 3.0f;
	s2h_drawBasis(context, lookAt(float3(s, 1.0f, c), float3(0.0f, 1.0f, 0.0f), float3(0.0f, 1.0f, 0.0f)), 1.0f);

	ContextGather ui;
	s2h_init(ui, pixel);
	s2h_setCursor(ui, float2(10.0f, 10.0f));
	s2h_setScale(ui, 2);
	s2h_printTxt(ui, _P, _o, _s, _COLON);
	s2h_printFloat(ui, cameraPosition.x); s2h_printTxt(ui, _COMMA);
	s2h_printFloat(ui, cameraPosition.y); s2h_printTxt(ui, _COMMA);
	s2h_printFloat(ui, cameraPosition.z);

	float3 color = lerp(float3(0.0f, 0.0f, 0.0f), context.dstColor.rgb, context.dstColor.a);
	color = color * (1.0f - ui.dstColor.a) + ui.dstColor.rgb;
	gl_FragColor = float4(s2h_accurateLinearToSRGB(color), 1.0f);
}
