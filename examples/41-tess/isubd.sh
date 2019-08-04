uint findMSB(uint x)
{
	uint i;
	uint mask;
	uint res = -1;

	for (i = 0; i < 32; i++)
	{
		mask = 0x80000000 >> i;

		if ((x & mask) != 0)
		{
			res = 31 - i;
			break;
		}
	}

	return res;
}

uint parentKey(in uint key)
{
	return (key >> 1u);
}

void childrenKeys(in uint key, out uint children[2])
{
	children[0] = (key << 1u) | 0u;
	children[1] = (key << 1u) | 1u;
}

bool isRootKey(in uint key)
{
	return (key == 1u);
}

bool isLeafKey(in uint key)
{
	return findMSB(key) == 31;
}

bool isChildZeroKey(in uint key)
{
	return ((key & 1u) == 0u);
}

// barycentric interpolation
vec3 berp(in vec3 v[3], in vec2 u)
{
	return v[0] + u.x * (v[1] - v[0]) + u.y * (v[2] - v[0]);
}

vec4 berp(in vec4 v[3], in vec2 u)
{
	return v[0] + u.x * (v[1] - v[0]) + u.y * (v[2] - v[0]);
}

// get xform from bit value
mat3 bitToXform(in uint bit)
{
	float b = float(bit);
	float c = 1.0f - b;

	vec3 c1 = vec3(0.0f, c   , b   );
	vec3 c2 = vec3(0.5f, b   , 0.0f);
	vec3 c3 = vec3(0.5f, 0.0f, c   );

	return mtxFromCols(c1, c2, c3);
}

// get xform from key
mat3 keyToXform(in uint key)
{
	vec3 c1 = vec3(1.0f, 0.0f, 0.0f);
	vec3 c2 = vec3(0.0f, 1.0f, 0.0f);
	vec3 c3 = vec3(0.0f, 0.0f, 1.0f);

	mat3 xf = mtxFromCols(c1, c2, c3);

	while (key > 1u) {
		xf = mul(xf, bitToXform(key & 1u));
		key = key >> 1u;
	}

	return xf;
}

// get xform from key as well as xform from parent key
mat3 keyToXform(in uint key, out mat3 xfp)
{
	xfp = keyToXform(parentKey(key));
	return keyToXform(key);
}

// subdivision routine (vertex position only)
void subd(in uint key, in vec4 v_in[3], out vec4 v_out[3])
{
	mat3 xf = keyToXform(key);

	mat4x3 m = mtxFromRows(v_in[0], v_in[1], v_in[2]);

	mat4x3 v = mul(xf, m);

	v_out[0] = mtxGetRow(v, 0);
	v_out[1] = mtxGetRow(v, 1);
	v_out[2] = mtxGetRow(v, 2);
}

// subdivision routine (vertex position only)
// also computes parent position
void subd(in uint key, in vec4 v_in[3], out vec4 v_out[3], out vec4 v_out_p[3])
{
	mat3 xfp; mat3 xf = keyToXform(key, xfp);

	mat4x3 m = mtxFromRows(v_in[0], v_in[1], v_in[2]);

	mat4x3 v = mul(xf, m);
	mat4x3 vp = mul(xfp, m);

	v_out[0] = mtxGetRow(v, 0);
	v_out[1] = mtxGetRow(v, 1);
	v_out[2] = mtxGetRow(v, 2);

	v_out_p[0] = mtxGetRow(vp, 0);
	v_out_p[1] = mtxGetRow(vp, 1);
	v_out_p[2] = mtxGetRow(vp, 2);
}
