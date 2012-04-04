vec4 xlat_main(  );
vec4 xlat_main(  ) {
    return vec4( 1.00000);
}
void main() {
    vec4 xl_retval;
    xl_retval = xlat_main( );
    gl_FragData[0] = vec4( xl_retval);
}
