#version 100
#extension GL_OES_texture_3D : enable

vec4 texture3D (sampler3D sampler, vec3 coord);
vec4 texture3DProj (sampler3D sampler, vec4 coord);
vec4 texture3DLod (sampler3D sampler, vec3 coord, float lod);
vec4 texture3DProjLod (sampler3D sampler, vec4 coord, float lod);
