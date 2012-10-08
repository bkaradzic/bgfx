#version 100
vec4 texture2D       (sampler2D sampler, vec2 coord, float bias);
vec4 texture2DProj   (sampler2D sampler, vec3 coord, float bias);
vec4 texture2DProj   (sampler2D sampler, vec4 coord, float bias);

vec4 textureCube     (samplerCube sampler, vec3 coord, float bias);
