void main() {
	if (gl_FragCoord.x==1.0)
		discard;
	float a;
	if (2==3)
		a = 2.0;
	if (3==4)
		a = 3.0;
	else
		a = 4.0;
	for (int i = 0; i < 10; ++i)
		a += 1.0;
	do {
		a += 2.0;
	} while (0==1);
	a += 1.0;
	a *= a;
	a = -a;
	--a;
	a = sqrt(a);
	a = 1.0 / a;
    gl_FragColor = vec4(a);
}
