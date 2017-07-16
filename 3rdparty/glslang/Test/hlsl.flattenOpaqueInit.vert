struct FxaaTex { SamplerState smpl; Texture2D tex; };
SamplerState g_tInputTexture_sampler; Texture2D g_tInputTexture;

float4 lookUp(FxaaTex tex)
{
    return tex.tex.Sample(tex.smpl, float2(0.3, 0.4));
}

float4 main() : SV_TARGET0
{
    FxaaTex tex = { g_tInputTexture_sampler, g_tInputTexture };
    return lookUp(tex);
}