/*
    Terrain.hpp:

        - It implements a class responsible for generating terrains according to a height map. This height map can be imported from an image or simply generated automatically using a seed.
*/

#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Textures.hpp>
#include <Shader.hpp>
#include <Camera.hpp>
#include <Scene.hpp>
#include "noise.h"
#include "stb_image.h"
#include <iostream>

class Terrain
{
    public:
        Terrain();
        Terrain(Shader* terrainShader, GLuint seed = 1000);
        Terrain(const char* filePath, Shader* terrainShader);
        void draw(Shader* terrainShader, Camera camera);
        void draw(Shader* terrainShader, Camera camera, glm::vec3 translation, glm::vec3 scale, float rotation);
        void readData(const char* filePath, Shader* terrainShader);
    private:
        std::vector<float> vertices;

        // Tessellation variables
        GLuint rez = 20;
        GLuint NUM_PATCH_PTS = 4;
        
        // Heightmap variables
        const int noiseSize = 700;
        float frequency = 0.005f;
        int octaves = 8; //[1-10]
        float lacunarity = 0.80f; //[0.0 - 5.0]
        float gain = 0.40f; // [0.0-2.0]
        float weightedStrength = 0.5f; // [0.0-1.0]


        // Terrain variables
        int height, width, nChannels;
        unsigned char *heightmapData;
        GLuint VAO, VBO;
        Texture texture;
        FastNoiseLite noise;
        float* noiseData;

        void initializeVertices();
        void transferDataToGPU();
        void generateHeightmap(GLuint seed, Shader* terrainShader);
};