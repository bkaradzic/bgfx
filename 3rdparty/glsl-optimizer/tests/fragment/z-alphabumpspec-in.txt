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
struct SurfaceOutput {
    vec3 Albedo;
    vec3 Normal;
    vec3 Emission;
    float Specular;
    float Gloss;
    float Alpha;
};
struct Input {
    vec2 uv_MainTex;
    vec2 uv_BumpMap;
};
struct v2f_surf {
    vec4 pos;
    float fog;
    vec4 hip_pack0;
    vec3 viewDir;
    vec3 lightDir;
    vec3 vlight;
};
struct appdata_full {
    vec4 vertex;
    vec4 tangent;
    vec3 normal;
    vec4 texcoord;
    vec4 texcoord1;
    vec4 color;
};
uniform sampler2D _BumpMap;
uniform vec4 _Color;
uniform vec4 _LightColor0;
uniform sampler2D _MainTex;
uniform float _Shininess;
uniform vec4 _SpecColor;
vec4 UnpackNormal( in vec4 packednormal );
void surf( in Input IN, inout SurfaceOutput o );
vec4 LightingBlinnPhong( in SurfaceOutput s, in vec3 lightDir, in vec3 viewDir, in float atten );
vec4 frag_surf( in v2f_surf IN );
vec4 UnpackNormal( in vec4 packednormal ) {
    vec4 normal;
    normal.xy  = ((packednormal.wy  * 2.00000) - 1.00000);
    normal.z  = sqrt( ((1.00000 - (normal.x  * normal.x )) - (normal.y  * normal.y )) );
    return normal;
}
void surf( in Input IN, inout SurfaceOutput o ) {
    vec4 tex;
    tex = texture2D( _MainTex, IN.uv_MainTex);
    o.Albedo = (tex.xyz  * _Color.xyz );
    o.Gloss = tex.w ;
    o.Alpha = (tex.w  * _Color.w );
    o.Specular = _Shininess;
    o.Normal = vec3( UnpackNormal( texture2D( _BumpMap, IN.uv_BumpMap)));
}
vec4 LightingBlinnPhong( in SurfaceOutput s, in vec3 lightDir, in vec3 viewDir, in float atten ) {
    vec3 h;
    float diff;
    float nh;
    float spec;
    vec4 c;
    h = normalize( (lightDir + viewDir) );
    diff = max( 0.000000, dot( s.Normal, lightDir));
    nh = max( 0.000000, dot( s.Normal, h));
    spec = (pow( nh, (s.Specular * 128.000)) * s.Gloss);
    c.xyz  = ((((s.Albedo * _LightColor0.xyz ) * diff) + ((_LightColor0.xyz  * _SpecColor.xyz ) * spec)) * (atten * 2.00000));
    c.w  = (s.Alpha + (((_LightColor0.w  * _SpecColor.w ) * spec) * atten));
    return c;
}
vec4 frag_surf( in v2f_surf IN ) {
    Input surfIN;
    SurfaceOutput o;
    float atten = 1.00000;
    vec4 c;
    surfIN.uv_MainTex = IN.hip_pack0.xy ;
    surfIN.uv_BumpMap = IN.hip_pack0.zw ;
    o.Albedo = vec3( 0.000000);
    o.Emission = vec3( 0.000000);
    o.Specular = 0.000000;
    o.Alpha = 0.000000;
    o.Gloss = 0.000000;
    surf( surfIN, o);
    c = LightingBlinnPhong( o, IN.lightDir, normalize( vec3( IN.viewDir) ), atten);
    c.xyz  += (o.Albedo * IN.vlight);
    c.w  = o.Alpha;
    return c;
}
varying vec4 xlv_FOG;
void main() {
    vec4 xl_retval;
    v2f_surf xlt_IN;
    xlt_IN.pos = vec4(0.0);
    xlt_IN.fog = float( xlv_FOG);
    xlt_IN.hip_pack0 = vec4( gl_TexCoord[0]);
    xlt_IN.viewDir = vec3( gl_TexCoord[1]);
    xlt_IN.lightDir = vec3( gl_TexCoord[2]);
    xlt_IN.vlight = vec3( gl_TexCoord[3]);
    xl_retval = frag_surf( xlt_IN);
    gl_FragData[0] = vec4( xl_retval);
}
