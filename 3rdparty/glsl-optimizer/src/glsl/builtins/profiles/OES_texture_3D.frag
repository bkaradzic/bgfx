#version 100
#extension GL_OES_texture_3D : enable

vec4 texture3D (sampler3D sampler, vec3 coord);
vec4 texture3DProj (sampler3D sampler, vec4 coord);
vec4 texture3D (sampler3D sampler, vec3 coord, float bias);
vec4 texture3DProj (sampler3D sampler, vec4 coord, float bias);
