#include<Terrain.hpp>

// Constructors
Terrain::Terrain(GLuint seed)
{
    // TODO: Noise function that generates heightmap
}

Terrain::Terrain(const char* filePath, Shader* terrainShader)
{
    texture.setParameters(filePath, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_RGBA, 0);
    texture.loadTexture();

    this->height = texture.getHeight();
    this->width = texture.getWidth();
    this->nChannels = texture.getNChannels();
    
    terrainShader->setInt("heightMap", 0);
    std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
}

void Terrain::readData(const char* filePath)
{

}

void Terrain::initializeVertices()
{
    for(GLuint i=0; i<rez; i++)
    {
        for(GLuint j=0; j<rez; i++)
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
}

void Terrain::draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_PATCHES, 0, 4*rez*rez);
}