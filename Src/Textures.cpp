#include <Textures.hpp>

// Initialize the texture counter
int Texture::textureNumber = GL_TEXTURE0;

Texture::Texture(std::string texturePath, int wrapS, int wrapT , int minFilter , int magFilter , int colorModel , int textureNumber) 
{
    this->id = 0;
    this->texturePath = texturePath;
    this->wrapS = wrapS;
    this->wrapT = wrapT;
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->colorModel = colorModel;
    this->textureNumber++;
    loadTexture();
}

Texture::Texture(){}

Texture::Texture(std::vector<std::string> cubemapFaces, int wrapS , int wrapT , int minFilter , int magFilter , int colorModel , int textureNumber)
{
    this->id = 0;
    this->cubemapFaces = cubemapFaces;
    this->wrapS = wrapS;
    this->wrapT = wrapT;
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->colorModel = colorModel;
    this->textureNumber++;
    loadCubemap();
}

void Texture::loadTexture() {
    glGenTextures(1, &id); // How many textures and where to store them
    glActiveTexture(textureNumber);
    glBindTexture(GL_TEXTURE_2D, id);

    stbi_set_flip_vertically_on_load(true);

    // Wrapping parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    // Filtering parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    // Load and generate the texture
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, colorModel, width, height, 0, colorModel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture!!!! " << texturePath << std::endl;
    }

    stbi_image_free(data);
}

void Texture::loadTextureFromNoiseData(float* noiseData, int noiseSize,  int wrapS, int wrapT , int minFilter , int magFilter , int colorModel)
{
    this->height = noiseSize;
    this->width = noiseSize;
    this->nrChannels = 3;
    
    // Normalize the noise data to be between [0, 255], while keeping the same shape as noiseData (noiseSize x noiseSize)
    float max = -1000000;
    float min = 1000000;
    // Find the max and min values
    for (int i = 0; i < this->height * this->width; i++)
    {
        if (noiseData[i] > max)
            max = noiseData[i];
        if (noiseData[i] < min)
            min = noiseData[i];
    }
    float range = max - min;
    // Normalize the data
    for (int i = 0; i < this->height * this->width; i++)
    {
        noiseData[i] = (noiseData[i] - min) / range;
    }

    // Transform the float array to actually be RGB data (each original value is now repeated 3 times to represent the RGB values)
    noiseData = transformImageData(noiseData, height, width);

    // Print the data
    // for (int i = 0; i < this->height; i++)
    // {
    //     for (int j = 0; j < this->width; j++)
    //     {
    //         std::cout << "(";
    //         std::cout << noiseData[i * this->width + j] << ", ";
    //         std::cout << noiseData[i * this->width + j + 1] << ", ";
    //         std::cout << noiseData[i * this->width + j + 2] << ", ";
    //         std::cout << ") ";
    //     }
    //     std::cout << std::endl;
    // }
    // Create the texture
    glGenTextures(1, &id); // How many textures and where to store them
    glActiveTexture(textureNumber);
    glBindTexture(GL_TEXTURE_2D, id); // Bind the texture before setting any texture parameters or loading the texture data

    // Wrapping parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    // Filtering parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    // Load and generate the texture
    if (noiseData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, noiseData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture!!!! " << texturePath << std::endl;
    }
}

// This function works!
float* Texture::transformImageData(float* data, int height, int width)
{
    float* imageData = new float[width * height * 3];

    GLuint count = 0;

    // Populate the image data vector with the values from the 2D vector, the r, g, and b values must be the same
    for (int i = 0; i < height * width; i++)
    {
            imageData[count++] = data[i];
            imageData[count++] = data[i];
            imageData[count++] = data[i];
    }

    return imageData;
}


void Texture::loadCubemap() {
    glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	// Set the parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilter);

	int width, height, nrChannels;
	
	// Load the 6 textures
    for (unsigned int i = 0; i < cubemapFaces.size(); i++)
	{
		unsigned char* data = stbi_load(cubemapFaces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, colorModel, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << cubemapFaces[i] << std::endl;
			stbi_image_free(data);
		}
	}
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(textureNumber);
}

void Texture::setParameters(std::string texturePath, int wrapS, int wrapT , int minFilter , int magFilter , int colorModel)
{
    this->id = 0;
    this->texturePath = texturePath;
    this->cubemapFaces = cubemapFaces;
    this->wrapS = wrapS;
    this->wrapT = wrapT;
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->colorModel = colorModel;
    this->textureNumber++;
}

int Texture::getHeight()
{
    return this->height;
}

int Texture::getWidth()
{
    return this->width;
}

int Texture::getNChannels()
{
    return this->nrChannels;
}