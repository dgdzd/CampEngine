#include <textures/texture.h>

Texture::Texture(const char* pathToImage, bool autogenerate) {
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &id);
    data = stbi_load(pathToImage, &width, &height, &nrChannels, 0);

    if(data) {
        if(autogenerate) {
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            generatedImg = true;
            generatedMipmap = true;
        }
    } else {
        std::cout << "Failed to load image" << std::endl;
    }
}

void Texture::generateTextureImage() {
    if(!generatedImg) {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        generatedImg = true;
    } else {
        std::cout << "ERROR: Already generated texture image!" << std::endl;
    }
}

void Texture::generateMipmap() {
    if(generatedImg) {
        if(!generatedMipmap) {
            glBindTexture(GL_TEXTURE_2D, id);
            glGenerateMipmap(GL_TEXTURE_2D);

            generatedMipmap = true;
        } else {
            std::cout << "ERROR: Already generated texture mipmap!" << std::endl;
        }
    } else {
        std::cout << "ERROR: Please generate the texture image before generating the mipmap!" << std::endl;

    }
}

void Texture::use() {
    glBindTexture(GL_TEXTURE_2D, id);
}