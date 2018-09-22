#version 460
#extension GL_NVX_raytracing : enable
layout(binding = 0, set = 0) uniform accelerationStructureNVX accNV;
layout(location = 0) rayPayloadNVX vec4 localPayload;
layout(location = 1) rayPayloadInNVX vec4 incomingPayload;
void main()
{
	uvec2 v0 = gl_LaunchIDNVX;
	uvec2 v1 = gl_LaunchSizeNVX;
	vec3 v2 = gl_WorldRayOriginNVX;
	vec3 v3 = gl_WorldRayDirectionNVX;
	vec3 v4 = gl_ObjectRayOriginNVX;
	vec3 v5 = gl_ObjectRayDirectionNVX;
	float v6 = gl_RayTminNVX;
	float v7 = gl_RayTmaxNVX;
	traceNVX(accNV, 0u, 1u, 2u, 3u, 0u, vec3(0.5f), 0.5f, vec3(1.0f), 0.75f, 1);
}
