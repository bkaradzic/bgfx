float4 PixelShaderFunction(float4 input) : COLOR0
{
    [unroll] do {} while (false);
    [unroll] do {;} while (false);
    do { return input; } while (all(input == input));
}
