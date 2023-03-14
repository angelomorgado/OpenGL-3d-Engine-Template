#version 460 core

in float Height;

out vec4 FragColor;

void main()
{
	float scale = 64.0; // This scale should be transfered from the previous shader
	float h = (Height + 16) / scale;
	FragColor = vec4(h,h,h, 1.0);
}