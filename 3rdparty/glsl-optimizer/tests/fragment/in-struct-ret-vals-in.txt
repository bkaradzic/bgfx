struct v2f {
    vec4 pos;
    vec2 uv;
    vec4 color;
};
vec4 xlat_main( in v2f i );
vec4 xlat_main( in v2f i ) {
    vec4 c;
    c = i.color;
    c.xy  += i.uv;
    return c;
}
void main() {
    vec4 xl_retval;
    v2f xlt_i;
    xlt_i.pos = vec4(0.0);
    xlt_i.uv = vec2( gl_TexCoord[0]);
    xlt_i.color = vec4( gl_Color);
    xl_retval = xlat_main( xlt_i);
    gl_FragData[0] = vec4( xl_retval);
}
