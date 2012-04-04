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
uniform sampler2D _FlareTexture;
vec4 xlat_main( in vec4 color, in vec2 texcoord );
vec4 xlat_main( in vec4 color, in vec2 texcoord ) {
    return (texture2D( _FlareTexture, texcoord) * color);
}
void main() {
    vec4 xl_retval;
    xl_retval = xlat_main( vec4(gl_Color), vec2(gl_TexCoord[0]));
    gl_FragData[0] = vec4( xl_retval);
}
