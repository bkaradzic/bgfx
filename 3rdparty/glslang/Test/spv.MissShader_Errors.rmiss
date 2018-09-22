#version 460
#extension GL_NVX_raytracing : enable
hitAttributeNVX vec4 payload;                               // ERROR, hitattributeNVX unsupported in this stage 
void main()
{
    int e0 = gl_PrimitiveID;                                // ERROR, unsupported builtin in stage
    int e1 = gl_InstanceID;                                 // ERROR, unsupported builtin in stage
    int e3 = gl_InstanceCustomIndexNVX;                     // ERROR, unsupported builtin in stage
    mat4x3 e10 = gl_ObjectToWorldNVX;                       // ERROR, unsupported builtin in stage
    mat4x3 e11 = gl_WorldToObjectNVX;                       // ERROR, unsupported builtin in stage
    float e12 = gl_HitTNVX;                                 // ERROR, unsupported builtin in stage
    float e13 = gl_HitKindNVX;                              // ERROR, unsupported builtin in stage
    reportIntersectionNVX(1.0, 1U);                         // ERROR, unsupported builtin in stage
    ignoreIntersectionNVX();                                // ERROR, unsupported builtin in stage
    terminateRayNVX();                                      // ERROR, unsupported builtin in stage
}
