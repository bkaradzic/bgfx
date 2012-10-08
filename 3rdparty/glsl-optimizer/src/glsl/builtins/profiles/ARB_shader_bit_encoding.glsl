#version 130
#extension GL_ARB_shader_bit_encoding : enable

int   floatBitsToInt(float value);
ivec2 floatBitsToInt(vec2  value);
ivec3 floatBitsToInt(vec3  value);
ivec4 floatBitsToInt(vec4  value);

uint  floatBitsToUint(float value);
uvec2 floatBitsToUint(vec2  value);
uvec3 floatBitsToUint(vec3  value);
uvec4 floatBitsToUint(vec4  value);

float intBitsToFloat(int   value);
vec2  intBitsToFloat(ivec2 value);
vec3  intBitsToFloat(ivec3 value);
vec4  intBitsToFloat(ivec4 value);

float uintBitsToFloat(uint  value);
vec2  uintBitsToFloat(uvec2 value);
vec3  uintBitsToFloat(uvec3 value);
vec4  uintBitsToFloat(uvec4 value);
