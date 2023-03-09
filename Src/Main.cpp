// Include Scenes
#include <Scenes/Standard_Scene.hpp>
#include <Scenes/Laplacian_Edge_Detection.hpp>
#include <Scenes/Procedural_Terrain_Generation.hpp>

// Include Callbacks
#include <Callbacks/Laplacian_Callback.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <Configuration.h>

enum Scene_type
{
    laplacian,
    terrain_generation
};

int main()
{
    // Setup window
    GLFWwindow* window = setupWindow("Hello!");

    Procedural_Terrain_Generation scene;
    scene.setupScene(window);

    processCallbacks(scene.window, &(scene.camera), &(scene.cameraPos), &(scene.is_filtered));

    while (!glfwWindowShouldClose(scene.window))
    {
        processInput(scene.window, &(scene.camera));
        scene.renderScene();
    }

    glfwTerminate();

    return 0;
}