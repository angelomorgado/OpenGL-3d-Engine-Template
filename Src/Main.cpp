// Include Scenes
#include <Scenes/Laplacian_Edge_Detection.hpp>

// Include Callbacks
#include <Callbacks/Laplacian_Callback.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

int main()
{
    Laplacian_Edge_Detection scene;
    processCallbacks(scene.window, &(scene.camera), &(scene.cameraPos), &(scene.is_filtered));

    while (!glfwWindowShouldClose(scene.window))
    {
        processInput(scene.window, &(scene.camera));
        scene.renderScene();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}