#include<Terrain.hpp>

// Constructors
Terrain::Terrain(){}

// Procedural terrain constructor
Terrain::Terrain(Shader* terrainShader, GLuint seed)
{
    std::cout << "Generating heightmap with seed " << seed << std::endl;
    this->seed = seed;
    generateHeightmap(terrainShader, seed);
}

// Non-procedural terrain constructor
Terrain::Terrain(const char* filePath, Shader* terrainShader)
{
    readData(filePath, terrainShader);
}

void Terrain::setNoiseParameters()
{
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(seed);
    noise.SetFrequency(frequency);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(octaves);
    noise.SetFractalLacunarity(lacunarity);
    noise.SetFractalGain(gain);
    noise.SetFractalWeightedStrength(weightedStrength);
}

void Terrain::generateHeightmap(Shader* terrainShader, GLuint seed)
{
    // Set up noise
    setNoiseParameters();

    noiseData = new float[noiseSize * noiseSize];
    for (int y = 0; y < noiseSize; y++)
    {
        for (int x = 0; x < noiseSize; x++)
        {
            noiseData[y * noiseSize + x] = noise.GetNoise((float)x, (float)y);
        }
    }
    std::cout << "Generated heightmap of size " << noiseSize << " x " << noiseSize << std::endl;

    this->height = noiseSize;
    this->width = noiseSize;
    this->nChannels = 1;

    texture.loadTextureFromNoiseData(noiseData, noiseSize, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGB);
    terrainShader->setInt("heightmap", texture.textureNumber);
    std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;

    initializeVertices();
    transferDataToGPU();
}


void Terrain::readData(const char* filePath, Shader* terrainShader)
{
    texture.setParameters(filePath, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    texture.loadTexture();

    this->height = texture.getHeight();
    this->width = texture.getWidth();
    this->nChannels = texture.getNChannels();
    
    terrainShader->setInt("heightmap", texture.textureNumber);
    std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;

    initializeVertices();
    transferDataToGPU();
}

void Terrain::transferDataToGPU()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Position attribute - 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);
}

void Terrain::initializeVertices()
{
    for(GLuint i=0; i<rez; i++)
    {
        for(GLuint j=0; j<rez; j++)
        {
            // Vertex 1 (Top left)
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v
            
            // Vertex 2 (
            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            // Vertex 3
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v
            
            // Vertex 4
            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back(0.0f); // v.y
            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v
        }
    }

    std::cout << "Loaded " << rez*rez << " patches of 4 control points each" << std::endl;
    std::cout << "Processing " << rez*rez*4 << " vertices in vertex shader" << std::endl;
}

// Default draw function
void Terrain::draw(Shader* terrainShader, Camera camera)
{    
    terrainShader->use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    terrainShader->setMat4("projection", projection);
    terrainShader->setMat4("view", view);

    texture.bind();

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    terrainShader->setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS*rez*rez);
}

// Customizable draw function
void Terrain::draw(Shader* terrainShader, Camera camera, glm::vec3 translation, glm::vec3 scale, float rotation)
{
    terrainShader->use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    terrainShader->setMat4("projection", projection);
    terrainShader->setMat4("view", view);

    texture.bind();

    // world transformation
    setModel(terrainShader, translation, glm::vec3(0.0f,1.0f,0.0f), rotation, scale);

    glBindVertexArray(VAO);
    glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS*rez*rez);
}