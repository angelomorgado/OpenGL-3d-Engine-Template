#pragma once
#ifndef LAPLACIAN_SCENE_H
#define LAPLACIAN_SCENE_H

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

#include <iostream>
#include <thread>

class Laplacian_Edge_Detection
{
public:
    GLFWwindow* window;
    Camera camera;
    CameraPos cameraPos;
    bool is_filtered;

    Laplacian_Edge_Detection();
    void setupScene(GLFWwindow* window);
    void renderScene();
private:
    // Camera variables
    glm::vec3 cameraInitialPos;
    glm::vec3 cameraInitialTarget;

    // File paths
    const char* cubePath = "Media/Objects/Pyramid/pyramid.obj";
    const char* skullPath = "Media/Objects/Skull/Skull.obj";
    const char* alienPath = "Media/Objects/Alien/alien.obj";
    const char* planePath = "Media/Objects/Plane/plane.obj";
    const char* skyboxPath = "Media/Skyboxes/skybox_galaxy/";

    // Shaders
    Shader* objectShader;
    Shader* skyboxShader;
    Shader* screenShader;
    Shader* screenShader_noFilter;

    // Models
    Skybox* skybox;
    Model* cube;
    Model* skull;
    Model* alien;
    Model* plane;

    // Textures and materials
    Material default_mat;

    // Framebuffers
    Framebuffer* framebuffer;

    // Extra variables
    bool is_wireframe;

    // Setup Methods
    void loadModels();
    void loadShaders();
    void loadFramebuffers();
    void setupLightingAndMaterials();
    void setupCamera();
};

#endif