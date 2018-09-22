#version 460
#extension GL_NVX_raytracing : enable
layout(binding = 0, set = 0) uniform accelerationStructureNVX accNV;
layout(location = 0) rayPayloadNVX vec4 localPayload;
layout(location = 1) rayPayloadInNVX vec4 incomingPayload;
void main()
{
	uvec2 v0 = gl_LaunchIDNVX;
	uvec2 v1 = gl_LaunchSizeNVX;
	int v2 = gl_PrimitiveID;
	int v3 = gl_InstanceID;
	int v4 = gl_InstanceCustomIndexNVX;
	vec3 v5 = gl_WorldRayOriginNVX;
	vec3 v6 = gl_WorldRayDirectionNVX;
	vec3 v7 = gl_ObjectRayOriginNVX;
	vec3 v8 = gl_ObjectRayDirectionNVX;
	float v9 = gl_RayTminNVX;
	float v10 = gl_RayTmaxNVX;
	float v11 = gl_HitTNVX;
	uint v12 = gl_HitKindNVX;
	mat4x3 v13 = gl_ObjectToWorldNVX;
	mat4x3 v14 = gl_WorldToObjectNVX;
	traceNVX(accNV, 0u, 1u, 2u, 3u, 0u, vec3(0.5f), 0.5f, vec3(1.0f), 0.75f, 1);
}
