#include <Imgui.hpp>

UiManager::UiManager(){}

UiManager::UiManager(const char* window_title, GLFWwindow* window)
{
    m_window = window;
    
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Setup ImGui binding
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

UiManager::~UiManager()
{
    // Cleanup ImGui binding
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Cleanup GLFW
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool UiManager::should_close() const
{
    return glfwWindowShouldClose(m_window);
}

void UiManager::begin_frame()
{
    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UiManager::end_frame()
{
    // Render the ImGui frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(m_window);
}

void UiManager::open_imgui_window()
{
    // Create separate ImGui window
    m_imgui_window = ImGui::Begin("ImGui Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // ImGui window content goes here

    ImGui::End();
}
