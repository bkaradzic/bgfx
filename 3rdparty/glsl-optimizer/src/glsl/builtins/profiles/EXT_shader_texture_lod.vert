/* New anisotropic texture functions, providing explicit derivatives: */
vec4 texture2DGradEXT        (sampler2D sampler,
                              vec2  P, vec2  dPdx, vec2  dPdy);
vec4 texture2DProjGradEXT    (sampler2D sampler,
                              vec3  P, vec2  dPdx, vec2  dPdy);
vec4 texture2DProjGradEXT    (sampler2D sampler,
                              vec4  P, vec2  dPdx, vec2  dPdy);

vec4 textureCubeGradEXT      (samplerCube sampler,
                              vec3  P, vec3  dPdx, vec3  dPdy);