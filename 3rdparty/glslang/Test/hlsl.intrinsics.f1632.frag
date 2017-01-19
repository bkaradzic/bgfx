float PixelShaderFunctionS(float inF0)
{
    f32tof16(inF0);

    return 0.0;
}

float1 PixelShaderFunction1(float1 inF0)
{
    // TODO: ... add when float1 prototypes are generated
    return 0.0;
}

float2 PixelShaderFunction2(float2 inF0)
{
    f32tof16(inF0);

    return float2(1,2);
}

float3 PixelShaderFunction3(float3 inF0)
{
    f32tof16(inF0);

    return float3(1,2,3);
}

float4 PixelShaderFunction(float4 inF0)
{
    f32tof16(inF0);

    return float4(1,2,3,4);
}

