#version 100
vec4 texture2DLod    (sampler2D sampler, vec2 coord, float lod);
vec4 texture2DProjLod(sampler2D sampler, vec3 coord, float lod);
vec4 texture2DProjLod(sampler2D sampler, vec4 coord, float lod);

vec4 textureCubeLod  (samplerCube sampler, vec3 coord, float lod);
