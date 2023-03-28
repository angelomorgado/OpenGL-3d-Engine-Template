#version 460 core

in float Height;

out vec4 FragColor;

const float waterLevel = 0.2;
const float beachLevel = 0.3;
const float forestMountainLevel = 0.6;
const float snowyMountainLevel = 0.8;

uniform float scale;
uniform float shift;

void main()
{
    float h = (Height + shift) / scale;
    
    if (h < waterLevel) {
        // Water/Ocean biome
        FragColor = vec4(0.0, 0.0, h*1.5, 1.0); // Blue color
    }
    else if (h < beachLevel) {
        // Beach biome
        FragColor = vec4(1.0, h+0.1, h-0.1, 1.0); // Sand colored
    }
    else if (h < forestMountainLevel) {
        // Forest Mountain biome
        FragColor = vec4(0.0, h+0.1, 0.0, 1.0); // Green color
    }
    else if (h < snowyMountainLevel) {
        // Snowy Mountain biome
        FragColor = vec4(h*1.2, h*1.2, h*1.2, 1.0); // Snow colored
    }
    else {
        // Higher than snowy mountain level
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White color
    }
}