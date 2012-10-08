#version 130

/* texture - bias variants */
 vec4 texture( sampler1D sampler, float P, float bias);
ivec4 texture(isampler1D sampler, float P, float bias);
uvec4 texture(usampler1D sampler, float P, float bias);

 vec4 texture( sampler2D sampler, vec2 P, float bias);
ivec4 texture(isampler2D sampler, vec2 P, float bias);
uvec4 texture(usampler2D sampler, vec2 P, float bias);

 vec4 texture( sampler3D sampler, vec3 P, float bias);
ivec4 texture(isampler3D sampler, vec3 P, float bias);
uvec4 texture(usampler3D sampler, vec3 P, float bias);

 vec4 texture( samplerCube sampler, vec3 P, float bias);
ivec4 texture(isamplerCube sampler, vec3 P, float bias);
uvec4 texture(usamplerCube sampler, vec3 P, float bias);

float texture(sampler1DShadow   sampler, vec3 P, float bias);
float texture(sampler2DShadow   sampler, vec3 P, float bias);
float texture(samplerCubeShadow sampler, vec4 P, float bias);

 vec4 texture( sampler1DArray sampler, vec2 P, float bias);
ivec4 texture(isampler1DArray sampler, vec2 P, float bias);
uvec4 texture(usampler1DArray sampler, vec2 P, float bias);

 vec4 texture( sampler2DArray sampler, vec3 P, float bias);
ivec4 texture(isampler2DArray sampler, vec3 P, float bias);
uvec4 texture(usampler2DArray sampler, vec3 P, float bias);

float texture(sampler1DArrayShadow sampler, vec3 P, float bias);

/* textureProj - bias variants */
 vec4 textureProj( sampler1D sampler, vec2 P, float bias);
ivec4 textureProj(isampler1D sampler, vec2 P, float bias);
uvec4 textureProj(usampler1D sampler, vec2 P, float bias);
 vec4 textureProj( sampler1D sampler, vec4 P, float bias);
ivec4 textureProj(isampler1D sampler, vec4 P, float bias);
uvec4 textureProj(usampler1D sampler, vec4 P, float bias);

 vec4 textureProj( sampler2D sampler, vec3 P, float bias);
ivec4 textureProj(isampler2D sampler, vec3 P, float bias);
uvec4 textureProj(usampler2D sampler, vec3 P, float bias);
 vec4 textureProj( sampler2D sampler, vec4 P, float bias);
ivec4 textureProj(isampler2D sampler, vec4 P, float bias);
uvec4 textureProj(usampler2D sampler, vec4 P, float bias);

 vec4 textureProj( sampler3D sampler, vec4 P, float bias);
ivec4 textureProj(isampler3D sampler, vec4 P, float bias);
uvec4 textureProj(usampler3D sampler, vec4 P, float bias);

float textureProj(sampler1DShadow sampler, vec4 P, float bias);
float textureProj(sampler2DShadow sampler, vec4 P, float bias);

/* textureOffset - bias variants */
 vec4 textureOffset( sampler1D sampler, float P, int offset, float bias);
ivec4 textureOffset(isampler1D sampler, float P, int offset, float bias);
uvec4 textureOffset(usampler1D sampler, float P, int offset, float bias);

 vec4 textureOffset( sampler2D sampler, vec2 P, ivec2 offset, float bias);
ivec4 textureOffset(isampler2D sampler, vec2 P, ivec2 offset, float bias);
uvec4 textureOffset(usampler2D sampler, vec2 P, ivec2 offset, float bias);

 vec4 textureOffset( sampler3D sampler, vec3 P, ivec3 offset, float bias);
ivec4 textureOffset(isampler3D sampler, vec3 P, ivec3 offset, float bias);
uvec4 textureOffset(usampler3D sampler, vec3 P, ivec3 offset, float bias);

float textureOffset(sampler1DShadow sampler, vec3 P, int offset, float bias);
float textureOffset(sampler2DShadow sampler, vec3 P, ivec2 offset, float bias);

 vec4 textureOffset( sampler1DArray sampler, vec2 P, int offset, float bias);
ivec4 textureOffset(isampler1DArray sampler, vec2 P, int offset, float bias);
uvec4 textureOffset(usampler1DArray sampler, vec2 P, int offset, float bias);

 vec4 textureOffset( sampler2DArray sampler, vec3 P, ivec2 offset, float bias);
ivec4 textureOffset(isampler2DArray sampler, vec3 P, ivec2 offset, float bias);
uvec4 textureOffset(usampler2DArray sampler, vec3 P, ivec2 offset, float bias);

float textureOffset(sampler1DArrayShadow samp, vec3 P, int offset, float bias);

/* textureProjOffsetOffset - bias variants */
 vec4 textureProjOffset( sampler1D sampler, vec2 P, int offset, float bias);
ivec4 textureProjOffset(isampler1D sampler, vec2 P, int offset, float bias);
uvec4 textureProjOffset(usampler1D sampler, vec2 P, int offset, float bias);
 vec4 textureProjOffset( sampler1D sampler, vec4 P, int offset, float bias);
ivec4 textureProjOffset(isampler1D sampler, vec4 P, int offset, float bias);
uvec4 textureProjOffset(usampler1D sampler, vec4 P, int offset, float bias);

 vec4 textureProjOffset( sampler2D sampler, vec3 P, ivec2 offset, float bias);
ivec4 textureProjOffset(isampler2D sampler, vec3 P, ivec2 offset, float bias);
uvec4 textureProjOffset(usampler2D sampler, vec3 P, ivec2 offset, float bias);
 vec4 textureProjOffset( sampler2D sampler, vec4 P, ivec2 offset, float bias);
ivec4 textureProjOffset(isampler2D sampler, vec4 P, ivec2 offset, float bias);
uvec4 textureProjOffset(usampler2D sampler, vec4 P, ivec2 offset, float bias);

 vec4 textureProjOffset( sampler3D sampler, vec4 P, ivec3 offset, float bias);
ivec4 textureProjOffset(isampler3D sampler, vec4 P, ivec3 offset, float bias);
uvec4 textureProjOffset(usampler3D sampler, vec4 P, ivec3 offset, float bias);

float textureProjOffset(sampler1DShadow s, vec4 P, int offset, float bias);
float textureProjOffset(sampler2DShadow s, vec4 P, ivec2 offset, float bias);

/*
 * The following texture functions are deprecated:
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
