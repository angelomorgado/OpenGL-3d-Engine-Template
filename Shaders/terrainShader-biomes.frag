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
    // Get the correct height according to the scale and shift (Makes it dynamic)
    float h = (Height + shift) / scale;
    
    // Water/Ocean biome
    if (h < waterLevel) {
        FragColor = vec4(0.0, 0.0, h*1.5, 1.0); // Blue color
    }
    // Beach biome
    else if (h < beachLevel) {
        FragColor = vec4(1.0, h+0.1, h-0.1, 1.0); // Sand colored
    }
    // Forest Mountain biome
    else if (h < forestMountainLevel) {
        FragColor = vec4(0.0, h+0.1, 0.0, 1.0); // Green color
    }
    // Snowy Mountain biome
    else if (h < snowyMountainLevel) {
        FragColor = vec4(h*1.2, h*1.2, h*1.2, 1.0); // Snow colored
    }
    // Higher than snowy mountain level
    else {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White color
    }
}