#ifndef CE_TEXTURE_H
#define CE_TEXTURE_H

class Texture {
public:
    unsigned int id;
    int width, height, nrChannels;
    unsigned char* data;
    bool generatedImg = false;
    bool generatedMipmap = false;

    Texture();
    Texture(int width, int height);
    Texture(const char* pathToImage, bool autogenerate=true);

    void generateMipmap();
    void generateTextureImage();
    void use();
    
    void generate(int width, int height, unsigned char* data);
};

#endif
