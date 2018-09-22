#version 460
#extension GL_NVX_raytracing : enable
hitAttributeNVX vec4 payload;                               
layout(binding = 0, set = 0) uniform accelerationStructureNVX accNV;

void main()
{
    payload.x = 1.0f;                                       // ERROR, cannot write to hitattributeNVX in stage
    reportIntersectionNVX(1.0, 1U);                         // ERROR, unsupported builtin in stage 
    terminateRayNVX();
    ignoreIntersectionNVX();
}
