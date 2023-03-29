#version 460 core

in float Height;

out vec4 FragColor;

uniform float scale;
uniform float shift;

void main()
{
	float h = (Height + shift) / scale;
	FragColor = vec4(h,h,h, 1.0);
}