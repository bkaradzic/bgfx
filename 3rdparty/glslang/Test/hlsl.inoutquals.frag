struct PS_OUTPUT
{
    float4 Color : SV_Target0;
    float  Depth : SV_Depth;
};

void MyFunc(in float x, out float y, inout float z)
{
    y = x;
    z = y;
    x = -1; // no effect since x = in param
}

PS_OUTPUT main(noperspective in float4 inpos : SV_Position, out int sampleMask : SV_Coverage)
{
   PS_OUTPUT psout;

   float x = 7, y, z = 3;
   MyFunc(x, y, z);

   psout.Color = float4(x, y, z, 1);
   psout.Depth = inpos.w;

   return psout;
}
