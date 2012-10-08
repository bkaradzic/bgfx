#version 130
/*
 * 8.1 - Angle and Trigonometry Functions
 */
float radians(float degrees);
vec2  radians(vec2  degrees);
vec3  radians(vec3  degrees);
vec4  radians(vec4  degrees);

float degrees(float radians);
vec2  degrees(vec2  radians);
vec3  degrees(vec3  radians);
vec4  degrees(vec4  radians);

float sin(float angle);
vec2  sin(vec2  angle);
vec3  sin(vec3  angle);
vec4  sin(vec4  angle);

float cos(float angle);
vec2  cos(vec2  angle);
vec3  cos(vec3  angle);
vec4  cos(vec4  angle);

float tan(float angle);
vec2  tan(vec2  angle);
vec3  tan(vec3  angle);
vec4  tan(vec4  angle);

float asin(float angle);
vec2  asin(vec2  angle);
vec3  asin(vec3  angle);
vec4  asin(vec4  angle);

float acos(float angle);
vec2  acos(vec2  angle);
vec3  acos(vec3  angle);
vec4  acos(vec4  angle);

float atan(float y, float x);
vec2  atan(vec2  y, vec2  x);
vec3  atan(vec3  y, vec3  x);
vec4  atan(vec4  y, vec4  x);

float atan(float y_over_x);
vec2  atan(vec2  y_over_x);
vec3  atan(vec3  y_over_x);
vec4  atan(vec4  y_over_x);

float sinh(float x);
vec2  sinh(vec2  x);
vec3  sinh(vec3  x);
vec4  sinh(vec4  x);

float cosh(float x);
vec2  cosh(vec2  x);
vec3  cosh(vec3  x);
vec4  cosh(vec4  x);

float tanh(float x);
vec2  tanh(vec2  x);
vec3  tanh(vec3  x);
vec4  tanh(vec4  x);

float asinh(float x);
vec2  asinh(vec2  x);
vec3  asinh(vec3  x);
vec4  asinh(vec4  x);

float acosh(float x);
vec2  acosh(vec2  x);
vec3  acosh(vec3  x);
vec4  acosh(vec4  x);

float atanh(float x);
vec2  atanh(vec2  x);
vec3  atanh(vec3  x);
vec4  atanh(vec4  x);

/*
 * 8.2 - Exponential Functions
 */
float pow(float x, float y);
vec2  pow(vec2  x, vec2  y);
vec3  pow(vec3  x, vec3  y);
vec4  pow(vec4  x, vec4  y);

float exp(float x);
vec2  exp(vec2  x);
vec3  exp(vec3  x);
vec4  exp(vec4  x);

float log(float x);
vec2  log(vec2  x);
vec3  log(vec3  x);
vec4  log(vec4  x);

float exp2(float x);
vec2  exp2(vec2  x);
vec3  exp2(vec3  x);
vec4  exp2(vec4  x);

float log2(float x);
vec2  log2(vec2  x);
vec3  log2(vec3  x);
vec4  log2(vec4  x);

float sqrt(float x);
vec2  sqrt(vec2  x);
vec3  sqrt(vec3  x);
vec4  sqrt(vec4  x);

float inversesqrt(float x);
vec2  inversesqrt(vec2  x);
vec3  inversesqrt(vec3  x);
vec4  inversesqrt(vec4  x);

/*
 * 8.3 - Common Functions
 */
float abs(float x);
vec2  abs(vec2  x);
vec3  abs(vec3  x);
vec4  abs(vec4  x);
int   abs(int   x);
ivec2 abs(ivec2 x);
ivec3 abs(ivec3 x);
ivec4 abs(ivec4 x);

float sign(float x);
vec2  sign(vec2  x);
vec3  sign(vec3  x);
vec4  sign(vec4  x);
int   sign(int   x);
ivec2 sign(ivec2 x);
ivec3 sign(ivec3 x);
ivec4 sign(ivec4 x);

float floor(float x);
vec2  floor(vec2  x);
vec3  floor(vec3  x);
vec4  floor(vec4  x);

float trunc(float x);
vec2  trunc(vec2  x);
vec3  trunc(vec3  x);
vec4  trunc(vec4  x);

float round(float x);
vec2  round(vec2  x);
vec3  round(vec3  x);
vec4  round(vec4  x);

float roundEven(float x);
vec2  roundEven(vec2  x);
vec3  roundEven(vec3  x);
vec4  roundEven(vec4  x);

float ceil(float x);
vec2  ceil(vec2  x);
vec3  ceil(vec3  x);
vec4  ceil(vec4  x);

float fract(float x);
vec2  fract(vec2  x);
vec3  fract(vec3  x);
vec4  fract(vec4  x);

float mod(float x, float y);
vec2  mod(vec2  x, float y);
vec3  mod(vec3  x, float y);
vec4  mod(vec4  x, float y);

vec2  mod(vec2  x, vec2  y);
vec3  mod(vec3  x, vec3  y);
vec4  mod(vec4  x, vec4  y);

float modf(float x, out float i);
vec2  modf(vec2  x, out vec2  i);
vec3  modf(vec3  x, out vec3  i);
vec4  modf(vec4  x, out vec4  i);

float min(float x, float y);
vec2  min(vec2  x, vec2  y);
vec3  min(vec3  x, vec3  y);
vec4  min(vec4  x, vec4  y);

vec2  min(vec2  x, float y);
vec3  min(vec3  x, float y);
vec4  min(vec4  x, float y);

int   min(int   x, int   y);
ivec2 min(ivec2 x, ivec2 y);
ivec3 min(ivec3 x, ivec3 y);
ivec4 min(ivec4 x, ivec4 y);

ivec2 min(ivec2 x, int   y);
ivec3 min(ivec3 x, int   y);
ivec4 min(ivec4 x, int   y);

uint  min(uint  x, uint  y);
uvec2 min(uvec2 x, uvec2 y);
uvec3 min(uvec3 x, uvec3 y);
uvec4 min(uvec4 x, uvec4 y);

uvec2 min(uvec2 x, uint  y);
uvec3 min(uvec3 x, uint  y);
uvec4 min(uvec4 x, uint  y);

float max(float x, float y);
vec2  max(vec2  x, vec2  y);
vec3  max(vec3  x, vec3  y);
vec4  max(vec4  x, vec4  y);

vec2  max(vec2  x, float y);
vec3  max(vec3  x, float y);
vec4  max(vec4  x, float y);

int   max(int   x, int   y);
ivec2 max(ivec2 x, ivec2 y);
ivec3 max(ivec3 x, ivec3 y);
ivec4 max(ivec4 x, ivec4 y);

ivec2 max(ivec2 x, int   y);
ivec3 max(ivec3 x, int   y);
ivec4 max(ivec4 x, int   y);

uint  max(uint  x, uint  y);
uvec2 max(uvec2 x, uvec2 y);
uvec3 max(uvec3 x, uvec3 y);
uvec4 max(uvec4 x, uvec4 y);

uvec2 max(uvec2 x, uint  y);
uvec3 max(uvec3 x, uint  y);
uvec4 max(uvec4 x, uint  y);

float clamp(float x, float minVal, float maxVal);
vec2  clamp(vec2  x, vec2  minVal, vec2  maxVal);
vec3  clamp(vec3  x, vec3  minVal, vec3  maxVal);
vec4  clamp(vec4  x, vec4  minVal, vec4  maxVal);

vec2  clamp(vec2  x, float minVal, float maxVal);
vec3  clamp(vec3  x, float minVal, float maxVal);
vec4  clamp(vec4  x, float minVal, float maxVal);

int   clamp(int   x, int   minVal, int   maxVal);
ivec2 clamp(ivec2 x, ivec2 minVal, ivec2 maxVal);
ivec3 clamp(ivec3 x, ivec3 minVal, ivec3 maxVal);
ivec4 clamp(ivec4 x, ivec4 minVal, ivec4 maxVal);

ivec2 clamp(ivec2 x, int   minVal, int   maxVal);
ivec3 clamp(ivec3 x, int   minVal, int   maxVal);
ivec4 clamp(ivec4 x, int   minVal, int   maxVal);

uint  clamp(uint  x, uint  minVal, uint  maxVal);
uvec2 clamp(uvec2 x, uvec2 minVal, uvec2 maxVal);
uvec3 clamp(uvec3 x, uvec3 minVal, uvec3 maxVal);
uvec4 clamp(uvec4 x, uvec4 minVal, uvec4 maxVal);

uvec2 clamp(uvec2 x, uint  minVal, uint  maxVal);
uvec3 clamp(uvec3 x, uint  minVal, uint  maxVal);
uvec4 clamp(uvec4 x, uint  minVal, uint  maxVal);

float mix(float x, float y, float a);
vec2  mix(vec2  x, vec2  y, vec2  a);
vec3  mix(vec3  x, vec3  y, vec3  a);
vec4  mix(vec4  x, vec4  y, vec4  a);

vec2  mix(vec2  x, vec2  y, float a);
vec3  mix(vec3  x, vec3  y, float a);
vec4  mix(vec4  x, vec4  y, float a);

float mix(float x, float y, bool  a);
vec2  mix(vec2  x, vec2  y, bvec2 a);
vec3  mix(vec3  x, vec3  y, bvec3 a);
vec4  mix(vec4  x, vec4  y, bvec4 a);

float step(float edge, float x);
vec2  step(vec2  edge, vec2  x);
vec3  step(vec3  edge, vec3  x);
vec4  step(vec4  edge, vec4  x);

vec2  step(float edge, vec2  x);
vec3  step(float edge, vec3  x);
vec4  step(float edge, vec4  x);

float smoothstep(float edge0, float edge1, float x);
vec2  smoothstep(vec2  edge0, vec2  edge1, vec2  x);
vec3  smoothstep(vec3  edge0, vec3  edge1, vec3  x);
vec4  smoothstep(vec4  edge0, vec4  edge1, vec4  x);

vec2  smoothstep(float edge0, float edge1, vec2  x);
vec3  smoothstep(float edge0, float edge1, vec3  x);
vec4  smoothstep(float edge0, float edge1, vec4  x);

bool  isnan(float x);
bvec2 isnan(vec2  x);
bvec3 isnan(vec3  x);
bvec4 isnan(vec4  x);

bool  isinf(float x);
bvec2 isinf(vec2  x);
bvec3 isinf(vec3  x);
bvec4 isinf(vec4  x);

/*
 * 8.4 - Geometric Functions
 */
float length(float x);
float length(vec2  x);
float length(vec3  x);
float length(vec4  x);

float distance(float p0, float p1);
float distance(vec2  p0, vec2  p1);
float distance(vec3  p0, vec3  p1);
float distance(vec4  p0, vec4  p1);

float dot(float x, float y);
float dot(vec2  x, vec2  y);
float dot(vec3  x, vec3  y);
float dot(vec4  x, vec4  y);

vec3 cross(vec3 x, vec3 y);

float normalize(float x);
vec2  normalize(vec2  x);
vec3  normalize(vec3  x);
vec4  normalize(vec4  x);

float faceforward(float N, float I, float Nref);
vec2  faceforward(vec2  N, vec2  I, vec2  Nref);
vec3  faceforward(vec3  N, vec3  I, vec3  Nref);
vec4  faceforward(vec4  N, vec4  I, vec4  Nref);

float reflect(float I, float N);
vec2  reflect(vec2  I, vec2  N);
vec3  reflect(vec3  I, vec3  N);
vec4  reflect(vec4  I, vec4  N);

float refract(float I, float N, float eta);
vec2  refract(vec2  I, vec2  N, float eta);
vec3  refract(vec3  I, vec3  N, float eta);
vec4  refract(vec4  I, vec4  N, float eta);


/*
 * 8.5 - Matrix Functions
 */
mat2   matrixCompMult(mat2   x, mat2   y);
mat3   matrixCompMult(mat3   x, mat3   y);
mat4   matrixCompMult(mat4   x, mat4   y);
mat2x3 matrixCompMult(mat2x3 x, mat2x3 y);
mat2x4 matrixCompMult(mat2x4 x, mat2x4 y);
mat3x2 matrixCompMult(mat3x2 x, mat3x2 y);
mat3x4 matrixCompMult(mat3x4 x, mat3x4 y);
mat4x2 matrixCompMult(mat4x2 x, mat4x2 y);
mat4x3 matrixCompMult(mat4x3 x, mat4x3 y);

mat2   outerProduct(vec2 c, vec2 r);
mat3   outerProduct(vec3 c, vec3 r);
mat4   outerProduct(vec4 c, vec4 r);

mat2x3 outerProduct(vec3 c, vec2 r);
mat3x2 outerProduct(vec2 c, vec3 r);

mat2x4 outerProduct(vec4 c, vec2 r);
mat4x2 outerProduct(vec2 c, vec4 r);

mat3x4 outerProduct(vec4 c, vec3 r);
mat4x3 outerProduct(vec3 c, vec4 r);

mat2   transpose(mat2 m);
mat3   transpose(mat3 m);
mat4   transpose(mat4 m);

mat2x3 transpose(mat3x2 m);
mat3x2 transpose(mat2x3 m);

mat2x4 transpose(mat4x2 m);
mat4x2 transpose(mat2x4 m);

mat3x4 transpose(mat4x3 m);
mat4x3 transpose(mat3x4 m);

/*
 * 8.6 - Vector Relational Functions
 */
bvec2 lessThan( vec2 x,  vec2 y);
bvec3 lessThan( vec3 x,  vec3 y);
bvec4 lessThan( vec4 x,  vec4 y);
bvec2 lessThan(ivec2 x, ivec2 y);
bvec3 lessThan(ivec3 x, ivec3 y);
bvec4 lessThan(ivec4 x, ivec4 y);
bvec2 lessThan(uvec2 x, uvec2 y);
bvec3 lessThan(uvec3 x, uvec3 y);
bvec4 lessThan(uvec4 x, uvec4 y);

bvec2 lessThanEqual( vec2 x,  vec2 y);
bvec3 lessThanEqual( vec3 x,  vec3 y);
bvec4 lessThanEqual( vec4 x,  vec4 y);
bvec2 lessThanEqual(ivec2 x, ivec2 y);
bvec3 lessThanEqual(ivec3 x, ivec3 y);
bvec4 lessThanEqual(ivec4 x, ivec4 y);
bvec2 lessThanEqual(uvec2 x, uvec2 y);
bvec3 lessThanEqual(uvec3 x, uvec3 y);
bvec4 lessThanEqual(uvec4 x, uvec4 y);

bvec2 greaterThan( vec2 x,  vec2 y);
bvec3 greaterThan( vec3 x,  vec3 y);
bvec4 greaterThan( vec4 x,  vec4 y);
bvec2 greaterThan(ivec2 x, ivec2 y);
bvec3 greaterThan(ivec3 x, ivec3 y);
bvec4 greaterThan(ivec4 x, ivec4 y);
bvec2 greaterThan(uvec2 x, uvec2 y);
bvec3 greaterThan(uvec3 x, uvec3 y);
bvec4 greaterThan(uvec4 x, uvec4 y);

bvec2 greaterThanEqual( vec2 x,  vec2 y);
bvec3 greaterThanEqual( vec3 x,  vec3 y);
bvec4 greaterThanEqual( vec4 x,  vec4 y);
bvec2 greaterThanEqual(ivec2 x, ivec2 y);
bvec3 greaterThanEqual(ivec3 x, ivec3 y);
bvec4 greaterThanEqual(ivec4 x, ivec4 y);
bvec2 greaterThanEqual(uvec2 x, uvec2 y);
bvec3 greaterThanEqual(uvec3 x, uvec3 y);
bvec4 greaterThanEqual(uvec4 x, uvec4 y);

bvec2 equal( vec2 x,  vec2 y);
bvec3 equal( vec3 x,  vec3 y);
bvec4 equal( vec4 x,  vec4 y);
bvec2 equal(ivec2 x, ivec2 y);
bvec3 equal(ivec3 x, ivec3 y);
bvec4 equal(ivec4 x, ivec4 y);
bvec2 equal(uvec2 x, uvec2 y);
bvec3 equal(uvec3 x, uvec3 y);
bvec4 equal(uvec4 x, uvec4 y);
bvec2 equal(bvec2 x, bvec2 y);
bvec3 equal(bvec3 x, bvec3 y);
bvec4 equal(bvec4 x, bvec4 y);

bvec2 notEqual( vec2 x,  vec2 y);
bvec3 notEqual( vec3 x,  vec3 y);
bvec4 notEqual( vec4 x,  vec4 y);
bvec2 notEqual(ivec2 x, ivec2 y);
bvec3 notEqual(ivec3 x, ivec3 y);
bvec4 notEqual(ivec4 x, ivec4 y);
bvec2 notEqual(uvec2 x, uvec2 y);
bvec3 notEqual(uvec3 x, uvec3 y);
bvec4 notEqual(uvec4 x, uvec4 y);
bvec2 notEqual(bvec2 x, bvec2 y);
bvec3 notEqual(bvec3 x, bvec3 y);
bvec4 notEqual(bvec4 x, bvec4 y);

bool any(bvec2 x);
bool any(bvec3 x);
bool any(bvec4 x);

bool all(bvec2 x);
bool all(bvec3 x);
bool all(bvec4 x);

bvec2 not(bvec2 x);
bvec3 not(bvec3 x);
bvec4 not(bvec4 x);

/*
 * 8.7 - Texture Lookup Functions
 */

/* textureSize */
int   textureSize( sampler1D sampler, int lod);
int   textureSize(isampler1D sampler, int lod);
int   textureSize(usampler1D sampler, int lod);

ivec2 textureSize( sampler2D sampler, int lod);
ivec2 textureSize(isampler2D sampler, int lod);
ivec2 textureSize(usampler2D sampler, int lod);

ivec3 textureSize( sampler3D sampler, int lod);
ivec3 textureSize(isampler3D sampler, int lod);
ivec3 textureSize(usampler3D sampler, int lod);

ivec2 textureSize( samplerCube sampler, int lod);
ivec2 textureSize(isamplerCube sampler, int lod);
ivec2 textureSize(usamplerCube sampler, int lod);

int   textureSize(sampler1DShadow   sampler, int lod);
ivec2 textureSize(sampler2DShadow   sampler, int lod);
ivec2 textureSize(samplerCubeShadow sampler, int lod);

ivec2 textureSize( sampler1DArray sampler, int lod);
ivec2 textureSize(isampler1DArray sampler, int lod);
ivec2 textureSize(usampler1DArray sampler, int lod);
ivec3 textureSize( sampler2DArray sampler, int lod);
ivec3 textureSize(isampler2DArray sampler, int lod);
ivec3 textureSize(usampler2DArray sampler, int lod);

ivec2 textureSize(sampler1DArrayShadow sampler, int lod);
ivec3 textureSize(sampler2DArrayShadow sampler, int lod);

/* texture - no bias */
 vec4 texture( sampler1D sampler, float P);
ivec4 texture(isampler1D sampler, float P);
uvec4 texture(usampler1D sampler, float P);

 vec4 texture( sampler2D sampler, vec2 P);
ivec4 texture(isampler2D sampler, vec2 P);
uvec4 texture(usampler2D sampler, vec2 P);

 vec4 texture( sampler3D sampler, vec3 P);
ivec4 texture(isampler3D sampler, vec3 P);
uvec4 texture(usampler3D sampler, vec3 P);

 vec4 texture( samplerCube sampler, vec3 P);
ivec4 texture(isamplerCube sampler, vec3 P);
uvec4 texture(usamplerCube sampler, vec3 P);

float texture(sampler1DShadow   sampler, vec3 P);
float texture(sampler2DShadow   sampler, vec3 P);
float texture(samplerCubeShadow sampler, vec4 P);

 vec4 texture( sampler1DArray sampler, vec2 P);
ivec4 texture(isampler1DArray sampler, vec2 P);
uvec4 texture(usampler1DArray sampler, vec2 P);

 vec4 texture( sampler2DArray sampler, vec3 P);
ivec4 texture(isampler2DArray sampler, vec3 P);
uvec4 texture(usampler2DArray sampler, vec3 P);

float texture(sampler1DArrayShadow sampler, vec3 P);
float texture(sampler2DArrayShadow sampler, vec4 P);

/* textureProj - no bias */
 vec4 textureProj( sampler1D sampler, vec2 P);
ivec4 textureProj(isampler1D sampler, vec2 P);
uvec4 textureProj(usampler1D sampler, vec2 P);
 vec4 textureProj( sampler1D sampler, vec4 P);
ivec4 textureProj(isampler1D sampler, vec4 P);
uvec4 textureProj(usampler1D sampler, vec4 P);

 vec4 textureProj( sampler2D sampler, vec3 P);
ivec4 textureProj(isampler2D sampler, vec3 P);
uvec4 textureProj(usampler2D sampler, vec3 P);
 vec4 textureProj( sampler2D sampler, vec4 P);
ivec4 textureProj(isampler2D sampler, vec4 P);
uvec4 textureProj(usampler2D sampler, vec4 P);

 vec4 textureProj( sampler3D sampler, vec4 P);
ivec4 textureProj(isampler3D sampler, vec4 P);
uvec4 textureProj(usampler3D sampler, vec4 P);

float textureProj(sampler1DShadow sampler, vec4 P);
float textureProj(sampler2DShadow sampler, vec4 P);

/* textureLod */
 vec4 textureLod( sampler1D sampler, float P, float lod);
ivec4 textureLod(isampler1D sampler, float P, float lod);
uvec4 textureLod(usampler1D sampler, float P, float lod);

 vec4 textureLod( sampler2D sampler, vec2 P, float lod);
ivec4 textureLod(isampler2D sampler, vec2 P, float lod);
uvec4 textureLod(usampler2D sampler, vec2 P, float lod);

 vec4 textureLod( sampler3D sampler, vec3 P, float lod);
ivec4 textureLod(isampler3D sampler, vec3 P, float lod);
uvec4 textureLod(usampler3D sampler, vec3 P, float lod);

 vec4 textureLod( samplerCube sampler, vec3 P, float lod);
ivec4 textureLod(isamplerCube sampler, vec3 P, float lod);
uvec4 textureLod(usamplerCube sampler, vec3 P, float lod);

float textureLod(sampler1DShadow sampler, vec3 P, float lod);
float textureLod(sampler2DShadow sampler, vec3 P, float lod);

 vec4 textureLod( sampler1DArray sampler, vec2 P, float lod);
ivec4 textureLod(isampler1DArray sampler, vec2 P, float lod);
uvec4 textureLod(usampler1DArray sampler, vec2 P, float lod);

 vec4 textureLod( sampler2DArray sampler, vec3 P, float lod);
ivec4 textureLod(isampler2DArray sampler, vec3 P, float lod);
uvec4 textureLod(usampler2DArray sampler, vec3 P, float lod);

float textureLod(sampler1DArrayShadow sampler, vec3 P, float lod);

/* textureOffset - no bias */
 vec4 textureOffset( sampler1D sampler, float P, int offset);
ivec4 textureOffset(isampler1D sampler, float P, int offset);
uvec4 textureOffset(usampler1D sampler, float P, int offset);

 vec4 textureOffset( sampler2D sampler, vec2 P, ivec2 offset);
ivec4 textureOffset(isampler2D sampler, vec2 P, ivec2 offset);
uvec4 textureOffset(usampler2D sampler, vec2 P, ivec2 offset);

 vec4 textureOffset( sampler3D sampler, vec3 P, ivec3 offset);
ivec4 textureOffset(isampler3D sampler, vec3 P, ivec3 offset);
uvec4 textureOffset(usampler3D sampler, vec3 P, ivec3 offset);

float textureOffset(sampler1DShadow sampler, vec3 P, int offset);
float textureOffset(sampler2DShadow sampler, vec3 P, ivec2 offset);

 vec4 textureOffset( sampler1DArray sampler, vec2 P, int offset);
ivec4 textureOffset(isampler1DArray sampler, vec2 P, int offset);
uvec4 textureOffset(usampler1DArray sampler, vec2 P, int offset);

 vec4 textureOffset( sampler2DArray sampler, vec3 P, ivec2 offset);
ivec4 textureOffset(isampler2DArray sampler, vec3 P, ivec2 offset);
uvec4 textureOffset(usampler2DArray sampler, vec3 P, ivec2 offset);

float textureOffset(sampler1DArrayShadow sampler, vec3 P, int offset);

/* texelFetch */
 vec4 texelFetch( sampler1D sampler, int P, int lod);
ivec4 texelFetch(isampler1D sampler, int P, int lod);
uvec4 texelFetch(usampler1D sampler, int P, int lod);

 vec4 texelFetch( sampler2D sampler, ivec2 P, int lod);
ivec4 texelFetch(isampler2D sampler, ivec2 P, int lod);
uvec4 texelFetch(usampler2D sampler, ivec2 P, int lod);

 vec4 texelFetch( sampler3D sampler, ivec3 P, int lod);
ivec4 texelFetch(isampler3D sampler, ivec3 P, int lod);
uvec4 texelFetch(usampler3D sampler, ivec3 P, int lod);

 vec4 texelFetch( sampler1DArray sampler, ivec2 P, int lod);
ivec4 texelFetch(isampler1DArray sampler, ivec2 P, int lod);
uvec4 texelFetch(usampler1DArray sampler, ivec2 P, int lod);

 vec4 texelFetch( sampler2DArray sampler, ivec3 P, int lod);
ivec4 texelFetch(isampler2DArray sampler, ivec3 P, int lod);
uvec4 texelFetch(usampler2DArray sampler, ivec3 P, int lod);

/* texelFetchOffset */
 vec4 texelFetchOffset( sampler1D sampler, int P, int lod, int offset);
ivec4 texelFetchOffset(isampler1D sampler, int P, int lod, int offset);
uvec4 texelFetchOffset(usampler1D sampler, int P, int lod, int offset);

 vec4 texelFetchOffset( sampler2D sampler, ivec2 P, int lod, ivec2 offset);
ivec4 texelFetchOffset(isampler2D sampler, ivec2 P, int lod, ivec2 offset);
uvec4 texelFetchOffset(usampler2D sampler, ivec2 P, int lod, ivec2 offset);

 vec4 texelFetchOffset( sampler3D sampler, ivec3 P, int lod, ivec3 offset);
ivec4 texelFetchOffset(isampler3D sampler, ivec3 P, int lod, ivec3 offset);
uvec4 texelFetchOffset(usampler3D sampler, ivec3 P, int lod, ivec3 offset);

 vec4 texelFetchOffset( sampler1DArray sampler, ivec2 P, int lod, int offset);
ivec4 texelFetchOffset(isampler1DArray sampler, ivec2 P, int lod, int offset);
uvec4 texelFetchOffset(usampler1DArray sampler, ivec2 P, int lod, int offset);

 vec4 texelFetchOffset( sampler2DArray sampler, ivec3 P, int lod, ivec2 offset);
ivec4 texelFetchOffset(isampler2DArray sampler, ivec3 P, int lod, ivec2 offset);
uvec4 texelFetchOffset(usampler2DArray sampler, ivec3 P, int lod, ivec2 offset);

/* textureProjOffset - no bias */
 vec4 textureProjOffset( sampler1D sampler, vec2 P, int offset);
ivec4 textureProjOffset(isampler1D sampler, vec2 P, int offset);
uvec4 textureProjOffset(usampler1D sampler, vec2 P, int offset);
 vec4 textureProjOffset( sampler1D sampler, vec4 P, int offset);
ivec4 textureProjOffset(isampler1D sampler, vec4 P, int offset);
uvec4 textureProjOffset(usampler1D sampler, vec4 P, int offset);

 vec4 textureProjOffset( sampler2D sampler, vec3 P, ivec2 offset);
ivec4 textureProjOffset(isampler2D sampler, vec3 P, ivec2 offset);
uvec4 textureProjOffset(usampler2D sampler, vec3 P, ivec2 offset);
 vec4 textureProjOffset( sampler2D sampler, vec4 P, ivec2 offset);
ivec4 textureProjOffset(isampler2D sampler, vec4 P, ivec2 offset);
uvec4 textureProjOffset(usampler2D sampler, vec4 P, ivec2 offset);

 vec4 textureProjOffset( sampler3D sampler, vec4 P, ivec3 offset);
ivec4 textureProjOffset(isampler3D sampler, vec4 P, ivec3 offset);
uvec4 textureProjOffset(usampler3D sampler, vec4 P, ivec3 offset);

float textureProjOffset(sampler1DShadow sampler, vec4 P, int offset);
float textureProjOffset(sampler2DShadow sampler, vec4 P, ivec2 offset);

/* textureLodOffset */
 vec4 textureLodOffset( sampler1D sampler, float P, float lod, int offset);
ivec4 textureLodOffset(isampler1D sampler, float P, float lod, int offset);
uvec4 textureLodOffset(usampler1D sampler, float P, float lod, int offset);

 vec4 textureLodOffset( sampler2D sampler, vec2 P, float lod, ivec2 offset);
ivec4 textureLodOffset(isampler2D sampler, vec2 P, float lod, ivec2 offset);
uvec4 textureLodOffset(usampler2D sampler, vec2 P, float lod, ivec2 offset);

 vec4 textureLodOffset( sampler3D sampler, vec3 P, float lod, ivec3 offset);
ivec4 textureLodOffset(isampler3D sampler, vec3 P, float lod, ivec3 offset);
uvec4 textureLodOffset(usampler3D sampler, vec3 P, float lod, ivec3 offset);

float textureLodOffset(sampler1DShadow samp, vec3 P, float lod, int offset);
float textureLodOffset(sampler2DShadow samp, vec3 P, float lod, ivec2 offset);

 vec4 textureLodOffset( sampler1DArray sampler, vec2 P, float lod, int offset);
ivec4 textureLodOffset(isampler1DArray sampler, vec2 P, float lod, int offset);
uvec4 textureLodOffset(usampler1DArray sampler, vec2 P, float lod, int offset);

 vec4 textureLodOffset( sampler2DArray samp, vec3 P, float lod, ivec2 offset);
ivec4 textureLodOffset(isampler2DArray samp, vec3 P, float lod, ivec2 offset);
uvec4 textureLodOffset(usampler2DArray samp, vec3 P, float lod, ivec2 offset);

float textureLodOffset(sampler1DArrayShadow s, vec3 P, float lod, int offset);

/* textureProjLod */
 vec4 textureProjLod( sampler1D sampler, vec2 P, float lod);
ivec4 textureProjLod(isampler1D sampler, vec2 P, float lod);
uvec4 textureProjLod(usampler1D sampler, vec2 P, float lod);
 vec4 textureProjLod( sampler1D sampler, vec4 P, float lod);
ivec4 textureProjLod(isampler1D sampler, vec4 P, float lod);
uvec4 textureProjLod(usampler1D sampler, vec4 P, float lod);

 vec4 textureProjLod( sampler2D sampler, vec3 P, float lod);
ivec4 textureProjLod(isampler2D sampler, vec3 P, float lod);
uvec4 textureProjLod(usampler2D sampler, vec3 P, float lod);
 vec4 textureProjLod( sampler2D sampler, vec4 P, float lod);
ivec4 textureProjLod(isampler2D sampler, vec4 P, float lod);
uvec4 textureProjLod(usampler2D sampler, vec4 P, float lod);

 vec4 textureProjLod( sampler3D sampler, vec4 P, float lod);
ivec4 textureProjLod(isampler3D sampler, vec4 P, float lod);
uvec4 textureProjLod(usampler3D sampler, vec4 P, float lod);

float textureProjLod(sampler1DShadow sampler, vec4 P, float lod);
float textureProjLod(sampler2DShadow sampler, vec4 P, float lod);

/* textureProjLodOffset */
 vec4 textureProjLodOffset( sampler1D sampler, vec2 P, float lod, int offset);
ivec4 textureProjLodOffset(isampler1D sampler, vec2 P, float lod, int offset);
uvec4 textureProjLodOffset(usampler1D sampler, vec2 P, float lod, int offset);
 vec4 textureProjLodOffset( sampler1D sampler, vec4 P, float lod, int offset);
ivec4 textureProjLodOffset(isampler1D sampler, vec4 P, float lod, int offset);
uvec4 textureProjLodOffset(usampler1D sampler, vec4 P, float lod, int offset);

 vec4 textureProjLodOffset( sampler2D sampler, vec3 P, float lod, ivec2 offset);
ivec4 textureProjLodOffset(isampler2D sampler, vec3 P, float lod, ivec2 offset);
uvec4 textureProjLodOffset(usampler2D sampler, vec3 P, float lod, ivec2 offset);
 vec4 textureProjLodOffset( sampler2D sampler, vec4 P, float lod, ivec2 offset);
ivec4 textureProjLodOffset(isampler2D sampler, vec4 P, float lod, ivec2 offset);
uvec4 textureProjLodOffset(usampler2D sampler, vec4 P, float lod, ivec2 offset);

 vec4 textureProjLodOffset( sampler3D sampler, vec4 P, float lod, ivec3 offset);
ivec4 textureProjLodOffset(isampler3D sampler, vec4 P, float lod, ivec3 offset);
uvec4 textureProjLodOffset(usampler3D sampler, vec4 P, float lod, ivec3 offset);

float textureProjLodOffset(sampler1DShadow s, vec4 P, float lod, int offset);
float textureProjLodOffset(sampler2DShadow s, vec4 P, float lod, ivec2 offset);

/* textureGrad */
 vec4 textureGrad( sampler1D sampler, float P, float dPdx, float dPdy);
ivec4 textureGrad(isampler1D sampler, float P, float dPdx, float dPdy);
uvec4 textureGrad(usampler1D sampler, float P, float dPdx, float dPdy);

 vec4 textureGrad( sampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy);
ivec4 textureGrad(isampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy);
uvec4 textureGrad(usampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy);

 vec4 textureGrad( sampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy);
ivec4 textureGrad(isampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy);
uvec4 textureGrad(usampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy);

 vec4 textureGrad( samplerCube sampler, vec3 P, vec3 dPdx, vec3 dPdy);
ivec4 textureGrad(isamplerCube sampler, vec3 P, vec3 dPdx, vec3 dPdy);
uvec4 textureGrad(usamplerCube sampler, vec3 P, vec3 dPdx, vec3 dPdy);

float textureGrad(sampler1DShadow   sampler, vec3 P, float dPdx, float dPdy);
float textureGrad(sampler2DShadow   sampler, vec3 P, vec2  dPdx, vec2  dPdy);
float textureGrad(samplerCubeShadow sampler, vec4 P, vec3  dPdx, vec3  dPdy);

 vec4 textureGrad( sampler1DArray sampler, vec2 P, float dPdx, float dPdy);
ivec4 textureGrad(isampler1DArray sampler, vec2 P, float dPdx, float dPdy);
uvec4 textureGrad(usampler1DArray sampler, vec2 P, float dPdx, float dPdy);

 vec4 textureGrad( sampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy);
ivec4 textureGrad(isampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy);
uvec4 textureGrad(usampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy);

float textureGrad(sampler1DArrayShadow sampler, vec3 P, float dPdx, float dPdy);
float textureGrad(sampler2DArrayShadow sampler, vec4 P, vec2  dPdx, vec2  dPdy);

/* textureGradOffset */
 vec4 textureGradOffset( sampler1D s, float P, float dx, float dy, int off);
ivec4 textureGradOffset(isampler1D s, float P, float dx, float dy, int offset);
uvec4 textureGradOffset(usampler1D s, float P, float dx, float dy, int offset);

 vec4 textureGradOffset( sampler2D s, vec2 P, vec2 dx, vec2 dy, ivec2 offset);
ivec4 textureGradOffset(isampler2D s, vec2 P, vec2 dx, vec2 dy, ivec2 offset);
uvec4 textureGradOffset(usampler2D s, vec2 P, vec2 dx, vec2 dy, ivec2 offset);

 vec4 textureGradOffset( sampler3D s, vec3 P, vec3 dx, vec3 dy, ivec3 offset);
ivec4 textureGradOffset(isampler3D s, vec3 P, vec3 dx, vec3 dy, ivec3 offset);
uvec4 textureGradOffset(usampler3D s, vec3 P, vec3 dx, vec3 dy, ivec3 offset);

float textureGradOffset(sampler1DShadow s, vec3 P, float dx, float dy, int off);
float textureGradOffset(sampler2DShadow s, vec3 P, vec2 dx, vec2 dy, ivec2 off);

 vec4 textureGradOffset( sampler1DArray s, vec2 P, float dx, float dy, int off);
ivec4 textureGradOffset(isampler1DArray s, vec2 P, float dx, float dy, int off);
uvec4 textureGradOffset(usampler1DArray s, vec2 P, float dx, float dy, int off);

 vec4 textureGradOffset( sampler2DArray s, vec3 P, vec2 dx, vec2 dy, ivec2 off);
ivec4 textureGradOffset(isampler2DArray s, vec3 P, vec2 dx, vec2 dy, ivec2 off);
uvec4 textureGradOffset(usampler2DArray s, vec3 P, vec2 dx, vec2 dy, ivec2 off);

float textureGradOffset(sampler1DArrayShadow s, vec3 P, float dx, float dy, int o);
float textureGradOffset(sampler2DArrayShadow s, vec4 P, vec2 dx, vec2 dy, ivec2 o);

/* textureProjGrad */
 vec4 textureProjGrad( sampler1D sampler, vec2 P, float dPdx, float dPdy);
ivec4 textureProjGrad(isampler1D sampler, vec2 P, float dPdx, float dPdy);
uvec4 textureProjGrad(usampler1D sampler, vec2 P, float dPdx, float dPdy);
 vec4 textureProjGrad( sampler1D sampler, vec4 P, float dPdx, float dPdy);
ivec4 textureProjGrad(isampler1D sampler, vec4 P, float dPdx, float dPdy);
uvec4 textureProjGrad(usampler1D sampler, vec4 P, float dPdx, float dPdy);

 vec4 textureProjGrad( sampler2D sampler, vec3 P, vec2 dPdx, vec2 dPdy);
ivec4 textureProjGrad(isampler2D sampler, vec3 P, vec2 dPdx, vec2 dPdy);
uvec4 textureProjGrad(usampler2D sampler, vec3 P, vec2 dPdx, vec2 dPdy);
 vec4 textureProjGrad( sampler2D sampler, vec4 P, vec2 dPdx, vec2 dPdy);
ivec4 textureProjGrad(isampler2D sampler, vec4 P, vec2 dPdx, vec2 dPdy);
uvec4 textureProjGrad(usampler2D sampler, vec4 P, vec2 dPdx, vec2 dPdy);

 vec4 textureProjGrad( sampler3D sampler, vec4 P, vec3 dPdx, vec3 dPdy);
ivec4 textureProjGrad(isampler3D sampler, vec4 P, vec3 dPdx, vec3 dPdy);
uvec4 textureProjGrad(usampler3D sampler, vec4 P, vec3 dPdx, vec3 dPdy);

float textureProjGrad(sampler1DShadow sampler, vec4 P, float dPdx, float dPdy);
float textureProjGrad(sampler2DShadow sampler, vec4 P, vec2  dPdx, vec2  dPdy);

/* textureProjGradOffset */
 vec4 textureProjGradOffset( sampler1D s, vec2 P, float dx, float dy, int off);
ivec4 textureProjGradOffset(isampler1D s, vec2 P, float dx, float dy, int off);
uvec4 textureProjGradOffset(usampler1D s, vec2 P, float dx, float dy, int off);
 vec4 textureProjGradOffset( sampler1D s, vec4 P, float dx, float dy, int off);
ivec4 textureProjGradOffset(isampler1D s, vec4 P, float dx, float dy, int off);
uvec4 textureProjGradOffset(usampler1D s, vec4 P, float dx, float dy, int off);

 vec4 textureProjGradOffset( sampler2D s, vec3 P, vec2 dx, vec2 dy, ivec2 off);
ivec4 textureProjGradOffset(isampler2D s, vec3 P, vec2 dx, vec2 dy, ivec2 off);
uvec4 textureProjGradOffset(usampler2D s, vec3 P, vec2 dx, vec2 dy, ivec2 off);
 vec4 textureProjGradOffset( sampler2D s, vec4 P, vec2 dx, vec2 dy, ivec2 off);
ivec4 textureProjGradOffset(isampler2D s, vec4 P, vec2 dx, vec2 dy, ivec2 off);
uvec4 textureProjGradOffset(usampler2D s, vec4 P, vec2 dx, vec2 dy, ivec2 off);

 vec4 textureProjGradOffset( sampler3D s, vec4 P, vec3 dx, vec3 dy, ivec3 off);
ivec4 textureProjGradOffset(isampler3D s, vec4 P, vec3 dx, vec3 dy, ivec3 off);
uvec4 textureProjGradOffset(usampler3D s, vec4 P, vec3 dx, vec3 dy, ivec3 off);

float textureProjGradOffset(sampler1DShadow s, vec4 P, float dx, float dy, int o);
float textureProjGradOffset(sampler2DShadow s, vec4 P, vec2 dx, vec2 dy, ivec2 o);

/*
 * The following texture functions are deprecated:
 */
vec4 texture1D       (sampler1D sampler, float coord);
vec4 texture1DProj   (sampler1D sampler, vec2  coord);
vec4 texture1DProj   (sampler1D sampler, vec4  coord);
vec4 texture1DLod    (sampler1D sampler, float coord, float lod);
vec4 texture1DProjLod(sampler1D sampler, vec2  coord, float lod);
vec4 texture1DProjLod(sampler1D sampler, vec4  coord, float lod);

vec4 texture2D       (sampler2D sampler, vec2 coord);
vec4 texture2DProj   (sampler2D sampler, vec3 coord);
vec4 texture2DProj   (sampler2D sampler, vec4 coord);
vec4 texture2DLod    (sampler2D sampler, vec2 coord, float lod);
vec4 texture2DProjLod(sampler2D sampler, vec3 coord, float lod);
vec4 texture2DProjLod(sampler2D sampler, vec4 coord, float lod);

vec4 texture3D       (sampler3D sampler, vec3 coord);
vec4 texture3DProj   (sampler3D sampler, vec4 coord);
vec4 texture3DLod    (sampler3D sampler, vec3 coord, float lod);
vec4 texture3DProjLod(sampler3D sampler, vec4 coord, float lod);

vec4 textureCube     (samplerCube sampler, vec3 coord);
vec4 textureCubeLod  (samplerCube sampler, vec3 coord, float lod);

vec4 shadow1D       (sampler1DShadow sampler, vec3 coord);
vec4 shadow2D       (sampler2DShadow sampler, vec3 coord);
vec4 shadow1DProj   (sampler1DShadow sampler, vec4 coord);
vec4 shadow2DProj   (sampler2DShadow sampler, vec4 coord);
vec4 shadow1DLod    (sampler1DShadow sampler, vec3 coord, float lod);
vec4 shadow2DLod    (sampler2DShadow sampler, vec3 coord, float lod);
vec4 shadow1DProjLod(sampler1DShadow sampler, vec4 coord, float lod);
vec4 shadow2DProjLod(sampler2DShadow sampler, vec4 coord, float lod);

/*
 * 8.9 - Noise Functions
 */
float noise1(float x);
float noise1(vec2  x);
float noise1(vec3  x);
float noise1(vec4  x);

vec2  noise2(float x);
vec2  noise2(vec2  x);
vec2  noise2(vec3  x);
vec2  noise2(vec4  x);

vec3  noise3(float x);
vec3  noise3(vec2  x);
vec3  noise3(vec3  x);
vec3  noise3(vec4  x);

vec4  noise4(float x);
vec4  noise4(vec2  x);
vec4  noise4(vec3  x);
vec4  noise4(vec4  x);
