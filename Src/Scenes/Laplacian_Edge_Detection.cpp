#include <Scenes/Laplacian_Edge_Detection.hpp>

Laplacian_Edge_Detection::Laplacian_Edge_Detection()
{
    std::cout << "1" << std::endl;
    setupScene();
    std::cout << "69" << std::endl;
}

void Laplacian_Edge_Detection::setupScene()
{
    std::cout << "2" << std::endl;
    // Window initialization
    setupWindow();
    std::cout << "3" << std::endl;

    // Extra variables initialization
    is_filtered = false;
    is_wireframe = false;
    cameraInitialPos = glm::vec3(-1.99221f, 1.42674f, 5.2215f);
	cameraInitialTarget = glm::vec3(7.0f, 2.0f, 0.0f);
    
    loadModels();
    loadShaders();
    loadFramebuffers();
    setupLightingAndMaterials();
    setupCamera();
}

void Laplacian_Edge_Detection::renderScene()
{
    // Update camera delta time
    camera.updateDeltaTime();

    // Bind to framebuffer
    framebuffer->bind();

    // Clear the screen
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the objects
    // Pyramid  
    objectShader->use();
    setView(objectShader, camera.GetViewMatrix());
    setProjection(objectShader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    setModel(
        objectShader, // shader
        glm::vec3(0.0f,0.5f,0.0f), // translation
        glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
        0.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
        glm::vec3(1.0f) // scale
        );
    cube->Draw(*objectShader);

    // Skull  
    setModel(
        objectShader, // shader
        glm::vec3(2.0f,2.0f, 2.0f), // translation
        glm::vec3(1.0f, 0.0f, 0.0f), // rotation axis
        -90.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
        glm::vec3(0.05f) // scale
    );
    skull->Draw(*objectShader);

    // Alien  
    setModel(
        objectShader, // shader
        glm::vec3(-2.0f, 1.0f, -2.0f), // translation
        glm::vec3(1.0f, 0.0f, 0.0f), // rotation axis
        0.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
        glm::vec3(0.5f) // scale
    );
    alien->Draw(*objectShader);
    
    // Plane  
    setModel(
        objectShader, // shader
        glm::vec3(0.0f), // translation
        glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
        0.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
        glm::vec3(1.0f) // scale
    );
    objectShader->setVec3("material.ambient", default_mat.Ambient);
    objectShader->setVec3("material.diffuse", default_mat.Diffuse);
    objectShader->setVec3("material.specular", default_mat.Specular);
    objectShader->setFloat("material.shininess", default_mat.Shininess);
    plane->Draw(*objectShader);
    
    // Skybox 
    skybox->Draw(*skyboxShader, camera);

    // Bind to default framebuffer
    framebuffer->unbind();

    // Draw quad using the framebuffer texture
    if (is_filtered) {
        framebuffer->drawQuad(*screenShader_noFilter);
    }
    else {
        framebuffer->drawQuad(*screenShader);
    }

    // Swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Laplacian_Edge_Detection::loadModels()
{
    cube = new Model(cubePath);
    cube->changeTexture("random.jpg", "Media/Textures");
    plane = new Model(planePath);
    plane->changeTexture("wood_floor.png", "Media/Textures");
    skull = new Model(skullPath);
    alien = new Model(alienPath);
    skybox = new Skybox(skyboxPath);
}

void Laplacian_Edge_Detection::loadShaders()
{
    objectShader = new Shader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
    skyboxShader = new Shader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    screenShader = new Shader("Shaders/Screen/simpleScreen.vert", "Shaders/Screen/laplacian_edge_detection_filter.frag");
    screenShader_noFilter = new Shader("Shaders/Screen/simpleScreen.vert", "Shaders/Screen/simpleScreen.frag");
}

void Laplacian_Edge_Detection::loadFramebuffers()
{
    framebuffer = new Framebuffer();
}

void Laplacian_Edge_Detection::setupLightingAndMaterials()
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

void Laplacian_Edge_Detection::setupCamera()
{
    camera = Camera(
        cameraInitialPos,
		cameraInitialTarget 
    );
}

void Laplacian_Edge_Detection::setupWindow()
{
    glfw_setup();
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Reflections using cubemaps", NULL, NULL);
    window_setup(window);
    glad_setup();
	printGPUinfo();
}