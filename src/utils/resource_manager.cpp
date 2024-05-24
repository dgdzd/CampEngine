#include <utils/resource_manager.h>

std::map<const char*, Shader> ResourceManager::shaders;
std::map<const char*, Texture> ResourceManager::textures;
std::map<const char*, PostProcessor> ResourceManager::post_processors;
ResourceManager ResourceManager::standard;

ResourceManager::ResourceManager() {
    
}

Shader* ResourceManager::loadShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath) {
    Shader shader(vertexShaderPath, fragmentShaderPath);
    shaders[name] = shader;
    
    return &shaders[name];
}

Shader* ResourceManager::getShader(const char *name) {
    return &shaders[name];
}

Texture* ResourceManager::loadTexture(const char* name, const char* texturePath) {
    Texture texture(texturePath);
    textures[name] = texture;
    
    return &textures[name];
}

Texture* ResourceManager::getTexture(const char* name) {
    return &textures[name];
}

PostProcessor* ResourceManager::loadPostProcessor(const char* name, Shader shader, unsigned int width, unsigned int height) {
    PostProcessor processor(shader, width, height);
    post_processors[name] = processor;
    
    return &post_processors[name];
}

PostProcessor* ResourceManager::getPostProcessor(const char* name) {
    return &post_processors[name];
}
