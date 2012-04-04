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
uniform vec4 _MainTex_ST;


v2f vert( in appdata v );
v2f vert( in appdata v ) {
    v2f o;
    o.pos = ( gl_ModelViewProjectionMatrix * v.vertex );
    o.texcoord = ((v.texcoord.xy  * _MainTex_ST.xy ) + _MainTex_ST.zw );
    o.cubenormal = vec3( ( gl_ModelViewMatrix * vec4( v.normal, 0.000000) ));
    return o;
}
void main() {
    v2f xl_retval;
    appdata xlt_v;
    xlt_v.vertex = vec4( gl_Vertex);
    xlt_v.texcoord = vec2( gl_MultiTexCoord0);
    xlt_v.normal = vec3( gl_Normal);
    xl_retval = vert( xlt_v);
    gl_Position = vec4( xl_retval.pos);
    gl_TexCoord[0] = vec4( xl_retval.texcoord, 0.0, 0.0);
    gl_TexCoord[1] = vec4( xl_retval.cubenormal, 0.0);
}
