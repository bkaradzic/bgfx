/*
 * The existing isotropic vertex texture functions are added to the
 * built-in functions for fragment shaders.
 */
vec4 texture2DLodEXT    (sampler2D sampler, vec2 coord, float lod);
vec4 texture2DProjLodEXT(sampler2D sampler, vec3 coord, float lod);
vec4 texture2DProjLodEXT(sampler2D sampler, vec4 coord, float lod);
vec4 textureCubeLodEXT  (samplerCube sampler, vec3 coord, float lod);

/* New anisotropic texture functions, providing explicit derivatives: */
vec4 texture2DGradEXT        (sampler2D sampler,
                              vec2  P, vec2  dPdx, vec2  dPdy);
vec4 texture2DProjGradEXT    (sampler2D sampler,
                              vec3  P, vec2  dPdx, vec2  dPdy);
vec4 texture2DProjGradEXT    (sampler2D sampler,
                              vec4  P, vec2  dPdx, vec2  dPdy);

vec4 textureCubeGradEXT      (samplerCube sampler,
                              vec3  P, vec3  dPdx, vec3  dPdy);
