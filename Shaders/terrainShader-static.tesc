#version 460 core

// Specify the number of control points per patch output
// This value controls the size of the input and output arrays
layout (vertices=4) out;

// Varying input from vertex shader
in vec2 TexCoord[];

// Varying output to tessellation evaluation shader
out vec2 TextureCoord[];

void main()
{
	// Pass the attributes
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	TextureCoord[gl_InvocationID] = TexCoord[gl_InvocationID];

	// Invocation zero controls tessellation levels for the entire patch (hardcoded)
	gl_TessLevelOuter[0] = 16;
	gl_TessLevelOuter[1] = 16;
	gl_TessLevelOuter[2] = 16;
	gl_TessLevelOuter[3] = 16;
	
	gl_TessLevelInner[0] = 16;
	gl_TessLevelInner[1] = 16;
}