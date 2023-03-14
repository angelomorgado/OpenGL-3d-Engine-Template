#include <Scenes/Procedural_Terrain_Generation.hpp>

// TODO: Fazer as cenas da parte do CPU todas :)

Procedural_Terrain_Generation_Scene::Procedural_Terrain_Generation_Scene()
{
}

void Procedural_Terrain_Generation_Scene::setupScene(GLFWwindow* window)
{
    // Extra variables initialization
    this->window = window;
    is_filtered = false;
    is_wireframe = false;
    cameraInitialPos = glm::vec3(-1.99221f, 2.42674f, 5.2215f);
	cameraInitialTarget = glm::vec3(7.0f, 2.0f, 0.0f);
    
    loadShaders();
    loadModels();
    loadFramebuffers();
    setupLightingAndMaterials();
    setupCamera();
}

void Procedural_Terrain_Generation_Scene::loadModels()
{
    plane = new Model(planePath);
    plane->changeTexture("wood_floor.png", "Media/Textures");
    cube = new Model(cubePath);
    cube->changeTexture("container.jpg", "Media/Textures");
    skybox = new Skybox(skyboxPath);

    // Setup terrain
    terrain = new Terrain(heightmapPath, terrainShader);
}

void Procedural_Terrain_Generation_Scene::renderScene()
{
    // Update camera delta time
    camera.updateDeltaTime();

    // Clear the screen
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the objects
    // Pyramid  

    terrain->draw(terrainShader, camera);
    
    objectShader->use();
    setView(objectShader, camera.GetViewMatrix());
    setProjection(objectShader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    
    // Plane  
    setModel(
        objectShader, // shader
        glm::vec3(0.0f), // translation
        glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
        0.0f, // rotation angle
        glm::vec3(1.0f) // scale
    );
    objectShader->setVec3("material.ambient", default_mat.Ambient);
    objectShader->setVec3("material.diffuse", default_mat.Diffuse);
    objectShader->setVec3("material.specular", default_mat.Specular);
    objectShader->setFloat("material.shininess", default_mat.Shininess);
    plane->Draw(*objectShader);

    // Cube  
    setModel(
        objectShader, // shader
        glm::vec3(0.0f), // translation
        glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
        0.0f, // rotation angle
        glm::vec3(1.0f) // scale
    );
    objectShader->setVec3("material.ambient", default_mat.Ambient);
    objectShader->setVec3("material.diffuse", default_mat.Diffuse);
    objectShader->setVec3("material.specular", default_mat.Specular);
    objectShader->setFloat("material.shininess", default_mat.Shininess);
    cube->Draw(*objectShader);

    // Skybox 
    skybox->Draw(*skyboxShader, camera);

    // Swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}


void Procedural_Terrain_Generation_Scene::loadShaders()
{
    objectShader = new Shader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
    skyboxShader = new Shader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    terrainShader = new Shader("Shaders/terrainShader.vert", "Shaders/terrainShader-grayscale.frag", nullptr, "Shaders/terrainShader.tesc", "Shaders/terrainShader.tese");
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