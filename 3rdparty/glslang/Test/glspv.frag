#version 450

#ifdef GL_SPIRV
#error GL_SPIRV is set ( correct, not an error )
#if GL_SPIRV == 100
#error GL_SPIR is 100
#endif
#endif

void main()
{
}

uniform float f; // ERROR, no location
layout(location = 2) uniform float g;
uniform sampler2D s1;
layout(location = 3) uniform sampler2D s2;

void noise()
{
    noise1(vec4(1));
    noise2(4.0);
    noise3(vec2(3));
    noise4(1);
}

layout(input_attachment_index = 1) uniform subpassInput sub; // ERROR, no inputs
