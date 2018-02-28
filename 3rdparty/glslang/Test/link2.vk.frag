#version 450

layout(binding=1) uniform sampler2D s2D;

vec4 getColor()
{
  return texture(s2D, vec2(0.5));
}
