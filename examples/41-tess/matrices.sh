

//I decided to keep the non square matrices definition in the example, since I am still not sure how non square matrices should be treated in bgfx (Daniel Gavin)

#ifndef MATRICES_H_HEADER_GUARD
#define MATRICES_H_HEADER_GUARD

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_SPIRV || BGFX_SHADER_LANGUAGE_METAL

#   define mat3x4 float4x3
#   define mat4x3 float3x4

#else


#endif // BGFX_SHADER_LANGUAGE_*

mat4x3 mtxFromRows(vec4 _0, vec4 _1, vec4 _2)
{
#if BGFX_SHADER_LANGUAGE_GLSL
    return transpose(mat3x4(_0, _1, _2) );
#else
	return mat4x3(_0, _1, _2);
#endif // BGFX_SHADER_LANGUAGE_GLSL
}

vec4 mtxGetRow(mat4x3 _0, uint row)
{
#if BGFX_SHADER_LANGUAGE_GLSL
    return vec4(_0[0][row], _0[1][row], _0[2][row], _0[3][row]);
#else
    return vec4(_0[row]);
#endif // BGFX_SHADER_LANGUAGE_GLSL
}

vec4 mtxGetRow(mat4 _0, uint row)
{
#if BGFX_SHADER_LANGUAGE_GLSL
    return vec4(_0[0][row], _0[1][row], _0[2][row], _0[3][row]);
#else
    return vec4(_0[row]);
#endif // BGFX_SHADER_LANGUAGE_GLSL
}

vec4 mtxGetColumn(mat4 _0, uint column)
{
#if BGFX_SHADER_LANGUAGE_GLSL
    return vec4(_0[column]);
#else
    return vec4(_0[0][column], _0[1][column], _0[2][column], _0[3][column]);
#endif // BGFX_SHADER_LANGUAGE_GLSL
}

float mtxGetElement(mat4 _0, uint column, uint row)
{
#if BGFX_SHADER_LANGUAGE_GLSL
    return _0[column][row];
#else
    return _0[row][column];
#endif // BGFX_SHADER_LANGUAGE_GLSL
}


#endif // __cplusplus

#endif // MATRICES_H_HEADER_GUARD
