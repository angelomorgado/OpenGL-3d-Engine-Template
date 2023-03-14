#version 460 core

// Inputs
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

void main()
{
	// Convert XYZ vertex to XYZW homogeneous coordinate
	gl_Position = vec4(aPos, 1.0);
	
	// Pass the texture coordinate to other shaders
	TexCoord = aTex;
}