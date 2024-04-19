#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <iostream>

#pragma once
class Texture {
    public:
    unsigned int id;
    int width, height, nrChannels;
    unsigned char* data;
    bool generatedImg = false;
    bool generatedMipmap = false;

    Texture(const char* pathToImage, bool autogenerate=true);

    void generateMipmap();
    void generateTextureImage();
    void use();
};