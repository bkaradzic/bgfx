#version 300 es

float xll_mod( float x, float y ) {
  float d = x / y;
  float f = fract (abs(d)) * y;
  return d >= 0.0 ? f : -f;
}
vec2 xll_mod( vec2 x, vec2 y ) {
  vec2 d = x / y;
  vec2 f = fract (abs(d)) * y;
  return vec2 (d.x >= 0.0 ? f.x : -f.x, d.y >= 0.0 ? f.y : -f.y);
}
vec3 xll_mod( vec3 x, vec3 y ) {
  vec3 d = x / y;
  vec3 f = fract (abs(d)) * y;
  return vec3 (d.x >= 0.0 ? f.x : -f.x, d.y >= 0.0 ? f.y : -f.y, d.z >= 0.0 ? f.z : -f.z);
}
vec4 xll_mod( vec4 x, vec4 y ) {
  vec4 d = x / y;
  vec4 f = fract (abs(d)) * y;
  return vec4 (d.x >= 0.0 ? f.x : -f.x, d.y >= 0.0 ? f.y : -f.y, d.z >= 0.0 ? f.z : -f.z, d.w >= 0.0 ? f.w : -f.w);
}
float xll_saturate( float x) {
  return clamp( x, 0.0, 1.0);
}
vec2 xll_saturate( vec2 x) {
  return clamp( x, 0.0, 1.0);
}
vec3 xll_saturate( vec3 x) {
  return clamp( x, 0.0, 1.0);
}
vec4 xll_saturate( vec4 x) {
  return clamp( x, 0.0, 1.0);
}
mat2 xll_saturate(mat2 m) {
  return mat2( clamp(m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0));
}
mat3 xll_saturate(mat3 m) {
  return mat3( clamp(m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0), clamp(m[2], 0.0, 1.0));
}
mat4 xll_saturate(mat4 m) {
  return mat4( clamp(m[0], 0.0, 1.0), clamp(m[1], 0.0, 1.0), clamp(m[2], 0.0, 1.0), clamp(m[3], 0.0, 1.0));
}
struct v2f {
    highp vec4 pos;
    highp vec2 uv;
    lowp vec4 color;
};
struct appdata_full {
    highp vec4 vertex;
    highp vec4 tangent;
    highp vec3 normal;
    highp vec4 texcoord;
    highp vec4 texcoord1;
    highp vec4 color;
};
uniform highp float _Bias;
uniform highp float _BlinkingTimeOffsScale;
uniform highp vec4 _Color;
uniform highp float _FadeOutDistFar;
uniform highp float _FadeOutDistNear;
uniform highp float _MaxGrowSize;
uniform highp float _Multiplier;
uniform highp float _NoiseAmount;
uniform highp float _SizeGrowEndDist;
uniform highp float _SizeGrowStartDist;
uniform highp vec4 _Time;
uniform highp float _TimeOffDuration;
uniform highp float _TimeOnDuration;
uniform highp float _VerticalBillboarding;
uniform highp mat4 _World2Object;
uniform highp vec3 _WorldSpaceCameraPos;
uniform highp mat4 glstate_matrix_mvp;
void CalcOrthonormalBasis( in highp vec3 dir, out highp vec3 right, out highp vec3 up );
highp float CalcFadeOutFactor( in highp float dist );
highp float CalcDistScale( in highp float dist );
v2f xlat_main( in appdata_full v );
void CalcOrthonormalBasis( in highp vec3 dir, out highp vec3 right, out highp vec3 up ) {
    up = (( (abs( dir.y  ) > 0.999000) ) ? ( vec3( 0.0, 0.0, 1.0) ) : ( vec3( 0.0, 1.0, 0.0) ));
    right = normalize( cross( up, dir) );
    up = cross( dir, right);
}
highp float CalcFadeOutFactor( in highp float dist ) {
    highp float nfadeout;
    highp float ffadeout;
    nfadeout = xll_saturate( (dist / _FadeOutDistNear) );
    ffadeout = (1.00000 - xll_saturate( (max( (dist - _FadeOutDistFar), 0.00000) * 0.200000) ));
    ffadeout *= ffadeout;
    nfadeout *= nfadeout;
    nfadeout *= nfadeout;
    nfadeout *= ffadeout;
    return nfadeout;
}
highp float CalcDistScale( in highp float dist ) {
    highp float distScale;
    distScale = min( (max( (dist - _SizeGrowStartDist), 0.00000) / _SizeGrowEndDist), 1.00000);
    return ((distScale * distScale) * _MaxGrowSize);
}
v2f xlat_main( in appdata_full v ) {
    highp vec3 centerOffs;
    highp vec3 centerLocal;
    highp vec3 viewerLocal;
    highp vec3 localDir;
    highp float localDirLength;
    highp vec3 rightLocal;
    highp vec3 upLocal;
    highp float distScale;
    highp vec3 BBNormal;
    highp vec3 BBLocalPos;
    highp float time;
    highp float fracTime;
    highp float wave;
    highp float noiseTime;
    highp float noise;
    highp float noiseWave;
    v2f o;
    centerOffs = (vec3( (vec2( 0.500000) - v.color.xy ), 0.00000) * v.texcoord1.xyy );
    centerLocal = (v.vertex.xyz  + centerOffs.xyz );
    viewerLocal = vec3( ( _World2Object * vec4( _WorldSpaceCameraPos, 1.00000) ));
    localDir = (viewerLocal - centerLocal);
    localDir.y  = mix( 0.00000, localDir.y , _VerticalBillboarding);
    localDirLength = length( localDir );
    CalcOrthonormalBasis( (localDir / localDirLength), rightLocal, upLocal);
    distScale = (CalcDistScale( localDirLength) * v.color.w );
    BBNormal = ((rightLocal * v.normal.x ) + (upLocal * v.normal.y ));
    BBLocalPos = ((centerLocal - ((rightLocal * centerOffs.x ) + (upLocal * centerOffs.y ))) + (BBNormal * distScale));
    time = (_Time.y  + (_BlinkingTimeOffsScale * v.color.z ));
    fracTime = xll_mod( time, (_TimeOnDuration + _TimeOffDuration));
    wave = (smoothstep( 0.00000, (_TimeOnDuration * 0.250000), fracTime) * (1.00000 - smoothstep( (_TimeOnDuration * 0.750000), _TimeOnDuration, fracTime)));
    noiseTime = (time * (6.28319 / _TimeOnDuration));
    noise = (sin( noiseTime ) * ((0.500000 * cos( ((noiseTime * 0.636600) + 56.7272) )) + 0.500000));
    noiseWave = ((_NoiseAmount * noise) + (1.00000 - _NoiseAmount));
    wave = (( (_NoiseAmount < 0.0100000) ) ? ( wave ) : ( noiseWave ));
    wave += _Bias;
    o.uv = v.texcoord.xy ;
    o.pos = ( glstate_matrix_mvp * vec4( BBLocalPos, 1.00000) );
    o.color = (((CalcFadeOutFactor( localDirLength) * _Color) * _Multiplier) * wave);
    return o;
}
in highp vec4 _inVertex;
in mediump vec3 _inNormal;
in highp vec4 _uv0;
in highp vec4 _uv1;
in lowp vec4 _color;
in vec4 TANGENT;
out highp vec2 xlv_TEXCOORD0;
out lowp vec4 xlv_TEXCOORD1;
void main() {
    v2f xl_retval;
    appdata_full xlt_v;
    xlt_v.vertex = _inVertex;
    xlt_v.tangent = TANGENT;
    xlt_v.normal = _inNormal;
    xlt_v.texcoord = _uv0;
    xlt_v.texcoord1 = _uv1;
    xlt_v.color = _color;
    xl_retval = xlat_main( xlt_v);
    gl_Position = vec4(xl_retval.pos);
    xlv_TEXCOORD0 = vec2( xl_retval.uv);
    xlv_TEXCOORD1 = vec4( xl_retval.color);
}
