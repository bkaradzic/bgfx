cbuffer {
    float4 v1;
};

tbuffer {
    float4 v2;
};

cbuffer cbufName : register(b2, space10) {
    float4 v3;
    int i3 : packoffset(c1.y);
} // no semicolon is okay

tbuffer tbufName : register(b8) {
    float4 v4 : packoffset(c1);
    int i4    : packoffset(c3);
    float f1  : packoffset(c3.w);
    float f3  : packoffset(c4.x);
    float f4  : packoffset(c4.y);
    float f5  : packoffset(c4.z);
    float f6  : packoffset(c);
    float f7;
                 float3x4 m1;
       row_major float3x4 m2;
    column_major float3x4 m3;
                 float3x4 m4;
}  // no semicolon is okay

float4 PixelShaderFunction(float4 input) : COLOR0
{
    return input + v1 + v2 + v3 + v4;
}
