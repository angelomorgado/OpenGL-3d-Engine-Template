#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.hpp>
#include <Camera.hpp>
#include <Utils.hpp>
#include <Scene.hpp>
#include <Textures.hpp>
#include <Model.hpp>
#include <Skybox.hpp>
#include <Framebuffer.hpp>
#include <Terrain.hpp>

#include <iostream>
#include <thread>

class Procedural_Terrain_Generation_Scene
{
public:
    GLFWwindow* window;
    Camera camera;
    CameraPos cameraPos;
    bool is_filtered;

    Procedural_Terrain_Generation_Scene();
    void setupScene(GLFWwindow* window);
    void renderScene();
private:
    // Camera variables
    glm::vec3 cameraInitialPos;
    glm::vec3 cameraInitialTarget;

    // File paths
    const char* planePath = "Media/Objects/Plane/plane.obj";
    const char* cubePath = "Media/Objects/Cube/cube.obj";
    const char* skyboxPath = "Media/Skyboxes/skybox_sky/";
    const char* heightmapPath = "Media/Textures/Heightmaps/peninsula.png";

    // Shaders
    Shader* objectShader;
    Shader* skyboxShader;
    Shader* terrainShader;

    // Models
    Skybox* skybox;
    Model* plane;
    Model* cube;
    Terrain* terrain;

    // Textures and materials
    Material default_mat;

    // Extra variables
    bool is_wireframe;

    // Setup Methods
    void loadModels();
    void loadShaders();
    void loadFramebuffers();
    void setupLightingAndMaterials();
    void setupCamera();
};