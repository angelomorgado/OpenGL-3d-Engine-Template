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
    // terrain = new Terrain(heightmapPath, terrainShader);
    terrain = new Terrain(terrainShader, 100);
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
    ImGui::Begin("Parameter Manager", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::Text("Heightmap Parameters:");
    ImGui::SliderFloat("Shift", &shift, -20.0f, 20.0f);
    ImGui::SliderFloat("Scale", &scale, -20.0f, 100.0f);
    ImGui::SliderFloat("Min Distance", &MIN_DISTANCE, 0.0f, 100.0f);
    ImGui::SliderFloat("Max Distance", &MAX_DISTANCE, 101.0f, 800.0f);
    ImGui::Text("Noise parameters:");
    ImGui::InputInt("Seed", &terrain->seed);
    ImGui::SliderFloat("Frequency", &terrain->frequency, 0.0f, 0.1f);
    ImGui::SliderInt("Octaves", &terrain->octaves, 1, 10);
    ImGui::SliderFloat("Lacunarity", &terrain->lacunarity, 0.0f, 5.0f);
    ImGui::SliderFloat("Gain", &terrain->gain, 0.0f, 2.0f);
    ImGui::SliderFloat("Weighted Strength", &terrain->weightedStrength, 0.0f, 1.0f);
    if (ImGui::Button("Generate"))
    {
        terrain->setNoiseParameters();
        terrain->generateHeightmap(terrainShader, terrain->seed);
        std::cout << "Generated new heigthmap" << std::endl;
    }
    ImGui::End();

    // Imgui render frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Procedural_Terrain_Generation_Scene::loadShaders()
{
    objectShader = new Shader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
    skyboxShader = new Shader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    terrainShader = new Shader("Shaders/terrainShader.vert", "Shaders/terrainShader-biomes.frag", nullptr, "Shaders/terrainShader-dynamic.tesc", "Shaders/terrainShader.tese");
}

void Procedural_Terrain_Generation_Scene::loadFramebuffers()
{
    // framebuffer = new Framebuffer();
}

void Procedural_Terrain_Generation_Scene::setupLightingAndMaterials()
{
    // Target shader
    objectShader->use();
    //Lighting
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