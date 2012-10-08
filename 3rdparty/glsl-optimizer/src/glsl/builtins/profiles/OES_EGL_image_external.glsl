#version 100
#extension GL_OES_EGL_image_external : enable

vec4 texture2D(samplerExternalOES sampler, vec2 coord);
vec4 texture2DProj(samplerExternalOES sampler, vec3 coord);
vec4 texture2DProj(samplerExternalOES sampler, vec4 coord);
