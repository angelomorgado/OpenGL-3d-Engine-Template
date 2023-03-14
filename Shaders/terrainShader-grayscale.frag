#version 460 core

in float Height;

out vec4 FragColor;

void main()
{
	float scale = 64.0; // This scale and shift should be transfered from the previous shader
	float shift = 16;
	float h = (Height + shift) / scale;
	FragColor = vec4(h,h,h, 1.0);
}