/*
 * The existing isotropic vertex texture functions are added to the
 * built-in functions for fragment shaders.
 */
vec4 texture1DLod    (sampler1D sampler, float coord, float lod);
vec4 texture1DProjLod(sampler1D sampler, vec2  coord, float lod);
vec4 texture1DProjLod(sampler1D sampler, vec4  coord, float lod);
vec4 texture2DLod    (sampler2D sampler, vec2 coord, float lod);
vec4 texture2DProjLod(sampler2D sampler, vec3 coord, float lod);
vec4 texture2DProjLod(sampler2D sampler, vec4 coord, float lod);
vec4 texture3DLod    (sampler3D sampler, vec3 coord, float lod);
vec4 texture3DProjLod(sampler3D sampler, vec4 coord, float lod);
vec4 textureCubeLod  (samplerCube sampler, vec3 coord, float lod);
vec4 shadow1DLod    (sampler1DShadow sampler, vec3 coord, float lod);
vec4 shadow2DLod    (sampler2DShadow sampler, vec3 coord, float lod);
vec4 shadow1DProjLod(sampler1DShadow sampler, vec4 coord, float lod);
vec4 shadow2DProjLod(sampler2DShadow sampler, vec4 coord, float lod);
