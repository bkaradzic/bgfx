#version 120
/*
 * 8.7 - Texture Lookup Functions
 */
vec4 texture1D       (sampler1D sampler, float coord, float bias);
vec4 texture1DProj   (sampler1D sampler, vec2  coord, float bias);
vec4 texture1DProj   (sampler1D sampler, vec4  coord, float bias);

vec4 texture2D       (sampler2D sampler, vec2 coord, float bias);
vec4 texture2DProj   (sampler2D sampler, vec3 coord, float bias);
vec4 texture2DProj   (sampler2D sampler, vec4 coord, float bias);

vec4 texture3D       (sampler3D sampler, vec3 coord, float bias);
vec4 texture3DProj   (sampler3D sampler, vec4 coord, float bias);

vec4 textureCube     (samplerCube sampler, vec3 coord, float bias);

vec4 shadow1D       (sampler1DShadow sampler, vec3 coord, float bias);
vec4 shadow2D       (sampler2DShadow sampler, vec3 coord, float bias);
vec4 shadow1DProj   (sampler1DShadow sampler, vec4 coord, float bias);
vec4 shadow2DProj   (sampler2DShadow sampler, vec4 coord, float bias);

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
