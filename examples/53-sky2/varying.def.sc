vec3 a_position : POSITION;
vec3 a_normal   : NORMAL;

vec3 v_normal     : TEXCOORD0 = vec3(0.0, 1.0, 0.0);
vec3 v_wpos       : TEXCOORD1 = vec3(0.0, 0.0, 0.0);
vec2 v_texcoord0  : TEXCOORD2 = vec2(0.0, 0.0);
vec4 v_shadowcoord: TEXCOORD3 = vec4(0.0, 0.0, 0.0, 1.0);
