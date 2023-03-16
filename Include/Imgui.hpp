#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

class UiManager
{
public:
    UiManager();
    UiManager(const char* window_title, GLFWwindow* window);
    ~UiManager();

    bool should_close() const;

    void begin_frame();
    void end_frame();

    void open_imgui_window();

private:
    GLFWwindow* m_window;
    bool m_show_gui = true;
    bool m_imgui_window = false;
};
