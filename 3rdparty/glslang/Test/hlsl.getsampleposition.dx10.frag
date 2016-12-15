SamplerState       g_sSamp : register(s0);

Texture2DMS      <float4>  g_tTex2dmsf4;
Texture2DMSArray <float4>  g_tTex2dmsf4a;

struct PS_OUTPUT
{
    float4 Color : SV_Target0;
    float  Depth : SV_Depth;
};

PS_OUTPUT main()
{
   PS_OUTPUT psout;

   float2 r00 = g_tTex2dmsf4.GetSamplePosition(1);
   float2 r01 = g_tTex2dmsf4a.GetSamplePosition(2);

   psout.Color = 1.0;
   psout.Depth = 1.0;

   return psout;
}
