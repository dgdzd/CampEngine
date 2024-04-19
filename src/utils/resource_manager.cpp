#include <utils/resource_manager.h>

std::map<const char*, Shader> ResourceManager::shaders;
std::map<const char*, Texture> ResourceManager::textures;

ResourceManager::ResourceManager() {
    
}

Shader ResourceManager::loadShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath) {
    Shader shader(vertexShaderPath, fragmentShaderPath);
    shaders[name] = shader;
    
    return shader;
}

Shader ResourceManager::getShader(const char *name) {
    return shaders[name];
}

Texture ResourceManager::loadTexture(const char* name, const char* texturePath) {
    Texture texture(texturePath);
    textures[name] = texture;
    
    return texture;
}

Texture ResourceManager::getTexture(const char* name) {
    return textures[name];
}
