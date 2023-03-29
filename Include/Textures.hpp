/*
    Textures.h:

        - Deals with everything related to textures, such as loading textures.
        - It has a special struct that stores every information related to a certain texture
*/

#pragma once

#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "stb_image.h"

// TODO: Make static variables for the texture numbers

class Texture 
{
public:
	Texture(std::string texturePath, int wrapS = GL_REPEAT, int wrapT = GL_REPEAT, int minFilter = GL_NEAREST, int magFilter = GL_NEAREST, int colorModel = GL_RGBA, int textureNumber = GL_TEXTURE0);

	Texture(std::vector<std::string> cubemapFaces, int wrapS = GL_REPEAT, int wrapT = GL_REPEAT, int minFilter = GL_NEAREST, int magFilter = GL_NEAREST, int colorModel = GL_RGBA, int textureNumber = GL_TEXTURE0);

	Texture();

	void setParameters(std::string texturePath, int wrapS, int wrapT , int minFilter , int magFilter);
	void bind();
	void loadTexture();
	int getHeight();
	int getWidth();
	int getNChannels();
	void loadTextureFromNoiseData(float* noiseData, int noiseSize,  int wrapS, int wrapT , int minFilter , int magFilter , int colorModel);

	static int textureNumber;


private:
	unsigned int id;
	std::string texturePath;
	std::vector<std::string> cubemapFaces;
	int wrapS;
	int wrapT;
	int wrapR;
	int minFilter;
	int magFilter;
	int colorModel;
	int width;
	int height;
	int nrChannels;
	void loadCubemap();
	float* transformImageData(float* data, int width, int height);
};

#endif