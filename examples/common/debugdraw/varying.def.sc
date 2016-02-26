vec3  a_position  : POSITION;
vec4  a_color0    : COLOR0;
float a_texcoord0 : TEXCOORD0;

vec4  v_color0    : COLOR = vec4(1.0, 0.0, 0.0, 1.0);
float v_stipple   : TEXCOORD0 = 0.0;
vec3  v_view      : TEXCOORD0 = vec3(0.0, 0.0, 0.0);
vec3  v_world     : TEXCOORD1 = vec3(0.0, 0.0, 0.0);
