#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <Shader.hpp>
#include <Camera.hpp>
#include <Utils.hpp>
#include <Scene.hpp>
#include <Textures.hpp>
#include <Model.hpp>
#include <Skybox.hpp>
#include <Framebuffer.hpp>
#include <Terrain.hpp>
#include <Imgui.hpp>

#include <iostream>
#include <thread>

class Procedural_Terrain_Generation_Scene
{
public:
    // Public variables
    bool is_filtered = false;
    GLFWwindow* window;
    Camera camera;
    CameraPos cameraPos;

    Procedural_Terrain_Generation_Scene();
    void setupScene(GLFWwindow* window);
    void renderScene();
    void terminateScene();
private:
    // Private variables
    glm::vec3 cameraInitialPos = glm::vec3(-1.99221f, 70.42674f, 5.2215f);
	glm::vec3 cameraInitialTarget = glm::vec3(7.0f, 70.0f, 0.0f);
    bool is_wireframe = false;
    UiManager* ui;

    int MIN_TESS_LEVEL = 4;
    int MAX_TESS_LEVEL = 64;
    float MIN_DISTANCE = 20.0f;
    float MAX_DISTANCE = 800.0f;
    float scale = 64.0f;
    float shift = 0.0f;

    // File paths
    const char* planePath = "Media/Objects/Plane/plane.obj";
    const char* cubePath = "Media/Objects/Cube/cube.obj";
    const char* skyboxPath = "Media/Skyboxes/skybox_sky/";
    const char* heightmapPath = "Media/Textures/Heightmaps/5.png";

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

    // Methods
    void loadModels();
    void loadShaders();
    void loadFramebuffers();
    void setupLightingAndMaterials();
    void setupCamera();
};