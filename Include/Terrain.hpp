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
#include<Shader.hpp>
#include "stb_image.h"

class Terrain
{
    public:
        Terrain(GLuint seed);
        Terrain(const char* filePath, Shader* terrainShader);
        void draw();
    private:
        std::vector<float> vertices;
        GLuint rez = 20; // Might make this dynamic in the future
        int height, width, nChannels;
        unsigned char *heightmapData;
        GLuint VAO, VBO;
        Texture texture;

        void readData(const char* filePath);
        void initializeVertices();
};