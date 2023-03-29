#pragma once

#ifndef CALLBACKS_STANDARD_H
#define CALLBACKS_STANDARD_H

#include <Camera.hpp>
#include <Utils.hpp>
#include <Skybox.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

Camera* cam;
CameraPos* cam_pos;
bool* is_filtered;
bool is_wireframe = false;
bool is_cursor = false;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    cam->ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (cam_pos->firstMouse)
    {
        cam_pos->lastX = xpos;
        cam_pos->lastY = ypos;
        cam_pos->firstMouse = false;
    }

    float xoffset = xpos - cam_pos->lastX;
    float yoffset = cam_pos->lastY - ypos; // reversed since y-coordinates go from bottom to top

    cam_pos->lastX = xpos;
    cam_pos->lastY = ypos;
    
    cam->ProcessMouseMovement(xoffset, yoffset);
}

// This callback function can't be used for things like movement because it doesn't work while pressing
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Leave the program
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	// Keybinds
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		*is_filtered = !*is_filtered;
	}
	// Keybinds
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
        is_wireframe = !is_wireframe;
        if (is_wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
		    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

    // Check if alt is being pressed
    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
    {
        is_cursor = !is_cursor;
        if(is_cursor)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPosCallback(window, NULL);
        }
        else
        {
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            // Reset the mouse position to the last position before toggling is_cursor
            glfwSetCursorPos(window, cam_pos->lastX, cam_pos->lastY);
        }
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, Camera* camera)
{
    // Exit program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->ProcessKeyboard(UP, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->MovementSpeed = EXTRA_SPEED;
    else
        camera->MovementSpeed = SPEED;
    
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera->ProcessKeyboard(DOWN, camera->deltaTime);
    
}

void processCallbacks(GLFWwindow* window, Camera* camera, CameraPos* cameraPos, bool* isFiltered){
    cam = camera;
    cam_pos = cameraPos;
    is_filtered = isFiltered;

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
}

#endif