#ifndef CE_RESOURCE_MANAGER_H
#define CE_RESOURCE_MANAGER_H

#include <shaders/shader.h>
#include <textures/texture.h>

#include <map>

#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path

#pragma once

class ResourceManager {
    public:
    static std::map<const char*, Shader> shaders;
    static std::map<const char*, Texture> textures;
    
    ResourceManager();
    
    Shader loadShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath);
    Shader getShader(const char* name);
    
    Texture loadTexture(const char* name, const char* texturePath);
    Texture getTexture(const char* name);
};

#endif /* ResourceManager_h */
