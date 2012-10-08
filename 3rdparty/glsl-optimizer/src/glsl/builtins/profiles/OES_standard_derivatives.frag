#version 100
#extension GL_OES_standard_derivatives : enable

/*
 * 8.8 - Fragment Processing Functions
 */
float dFdx(float p);
vec2  dFdx(vec2  p);
vec3  dFdx(vec3  p);
vec4  dFdx(vec4  p);

float dFdy(float p);
vec2  dFdy(vec2  p);
vec3  dFdy(vec3  p);
vec4  dFdy(vec4  p);

float fwidth(float p);
vec2  fwidth(vec2  p);
vec3  fwidth(vec3  p);
vec4  fwidth(vec4  p);
