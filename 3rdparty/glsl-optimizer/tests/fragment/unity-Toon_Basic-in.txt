struct v2f_vertex_lit {
    vec2 uv;
    vec4 diff;
    vec4 spec;
};
struct v2f_img {
    vec4 pos;
    vec2 uv;
};
struct appdata_img {
    vec4 vertex;
    vec2 texcoord;
};
struct v2f {
    vec4 pos;
    vec2 texcoord;
    vec3 cubenormal;
};
struct appdata {
    vec4 vertex;
    vec2 texcoord;
    vec3 normal;
};
uniform vec4 _Color;
uniform sampler2D _MainTex;
uniform samplerCube _ToonShade;
vec4 frag( in v2f i );
vec4 frag( in v2f i ) {
    vec4 col;
    vec4 cube;
    col = (_Color * texture2D( _MainTex, i.texcoord));
    cube = textureCube( _ToonShade, i.cubenormal);
    return vec4( ((2.00000 * cube.xyz ) * col.xyz ), col.w );
}
void main() {
    vec4 xl_retval;
    v2f xlt_i;
    xlt_i.pos = vec4(0.0);
    xlt_i.texcoord = vec2( gl_TexCoord[0]);
    xlt_i.cubenormal = vec3( gl_TexCoord[1]);
    xl_retval = frag( xlt_i);
    gl_FragData[0] = vec4( xl_retval);
}
