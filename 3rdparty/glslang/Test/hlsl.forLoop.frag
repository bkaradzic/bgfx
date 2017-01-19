float4 PixelShaderFunction(float4 input) : COLOR0
{
    for (;;) ;
    for (++input; ; ) ;
    [unroll] for (; any(input != input); ) {}
    for (; any(input != input); ) { return -input; }
    for (--input; any(input != input); input += 2) { return -input; }
	for (;;) if (input.x > 2.0) break;
	for (;;) if (input.x > 2.0) continue;
	float ii;
	for (int ii = -1; ii < 3; ++ii) if (ii == 2) continue;
	--ii;
}
