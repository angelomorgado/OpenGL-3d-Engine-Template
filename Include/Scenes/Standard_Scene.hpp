#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Utils.h"
#include "Scene.h"
#include "Textures.h"
#include "Model.h"
#include "Skybox.h"
#include "Framebuffer.h"

#include <iostream>
#include <thread>

class Standard_Scene
{
public:
    GLFWwindow* window;
    Camera camera;
    CameraPos cameraPos;
    bool is_filtered;

    Standard_Scene();
    void setupScene(GLFWwindow* window);
    void renderScene();
private:
    // Camera variables
    glm::vec3 cameraInitialPos;
    glm::vec3 cameraInitialTarget;

    // File paths
    const char* planePath = "Media/Objects/Plane/plane.obj";
    const char* skyboxPath = "Media/Skyboxes/skybox_galaxy/";

    // Shaders
    Shader* objectShader;
    Shader* skyboxShader;

    // Models
    Skybox* skybox;
    Model* plane;

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