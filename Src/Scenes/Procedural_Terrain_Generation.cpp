#include <Scenes/Procedural_Terrain_Generation.hpp>

Procedural_Terrain_Generation_Scene::Procedural_Terrain_Generation_Scene()
{
}

void Procedural_Terrain_Generation_Scene::setupScene(GLFWwindow* window)
{
    // Extra variables initialization
    this->window = window;
    
    loadShaders();
    loadModels();
    loadFramebuffers();
    setupLightingAndMaterials();
    setupCamera();

    // Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.WantCaptureMouse = true;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

    // ui = new UiManager("window!", window);
}

void Procedural_Terrain_Generation_Scene::loadModels()
{
    skybox = new Skybox(skyboxPath);

    // Setup terrain
    terrain = new Terrain(heightmapPath, terrainShader);
}

void Procedural_Terrain_Generation_Scene::renderScene()
{
    // Update camera delta time
    camera.updateDeltaTime();

    // Clear the screen
    glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw the objects
    // Pyramid  

    // Customizable draw function
    // terrain->draw(terrainShader,
    //     	camera,
    //         glm::vec3(0.0f), // Translation
    //         glm::vec3(0.02f), // Scale
    //         0.0f // Rotation angle
    //         );

    // Default draw function
    int MIN_TESS_LEVEL = 4;
    int MAX_TESS_LEVEL = 64;
    float MIN_DISTANCE = 20.0f;
    float MAX_DISTANCE = 800.0f;
    float scale = 64.0f;
    float shift = 0.0f;

    terrainShader->use();
    terrainShader->setInt("MIN_TESS_LEVEL", MIN_TESS_LEVEL);
    terrainShader->setInt("MAX_TESS_LEVEL", MAX_TESS_LEVEL);
    terrainShader->setFloat("MIN_DISTANCE", MIN_DISTANCE);
    terrainShader->setFloat("MAX_DISTANCE", MAX_DISTANCE);
    terrainShader->setFloat("scale", scale);
    terrainShader->setFloat("shift", shift);
    terrain->draw(terrainShader, camera);
    
    objectShader->use();
    setView(objectShader, camera.GetViewMatrix());
    setProjection(objectShader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    
    // Skybox 
    skybox->Draw(*skyboxShader, camera);
    
    // Imgui window initialization
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Imgui configure frame
    ImGui::Begin("This is a window!", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
        std::cout << "Saved!" << std::endl;
    // char *buf;
    // ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    // ImGui::SliderFloat("shift", &shift, 0.0f, 20.0f);
    ImGui::End();

    // Imgui render frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // // Begin ImGui frame
    // ui->begin_frame();

    // // Create ImGui window
    // ui->open_imgui_window();

    // // End ImGui frame
    // ui->end_frame();

    // Swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}


void Procedural_Terrain_Generation_Scene::loadShaders()
{
    objectShader = new Shader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
    skyboxShader = new Shader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    terrainShader = new Shader("Shaders/terrainShader.vert", "Shaders/terrainShader-grayscale.frag", nullptr, "Shaders/terrainShader-dynamic.tesc", "Shaders/terrainShader.tese");
}

void Procedural_Terrain_Generation_Scene::loadFramebuffers()
{
    // framebuffer = new Framebuffer();
}

void Procedural_Terrain_Generation_Scene::setupLightingAndMaterials()
{
    // Target shader
    objectShader->use();
    //Lighting, TODO: MAKE A LIGHT STRUCT
    objectShader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    objectShader->setVec3("light.position", 1.0f, 5.0f, 1.0f);
    objectShader->setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
    objectShader->setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    objectShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // Materials
    default_mat.Ambient   = glm::vec3(1.0f);
    default_mat.Diffuse   = glm::vec3(0.6f);
    default_mat.Specular  = glm::vec3(0.6f);
    default_mat.Shininess = 0.6f;
}

void Procedural_Terrain_Generation_Scene::setupCamera()
{
    camera = Camera(
        cameraInitialPos,
		cameraInitialTarget 
    );
}

void Procedural_Terrain_Generation_Scene::terminateScene()
{
    // Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}