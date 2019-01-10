#version 450

layout(rgba8, binding = 0) uniform readonly imageBuffer buf;

layout(location = 0) out vec4 FragColor;

void main()
{
	FragColor = imageLoad(buf, 0);
}
