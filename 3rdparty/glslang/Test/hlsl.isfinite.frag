
uniform float f;

float4 main() : SV_Target0
{
    isfinite(f);

    return 0;
}
