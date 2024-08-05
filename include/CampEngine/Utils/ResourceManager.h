#ifndef CE_RESOURCE_MANAGER_H
#define CE_RESOURCE_MANAGER_H

#include <CampEngine/Graphics/Shader.h>
#include <CampEngine/Graphics/Texture.h>
#include <CampEngine/Graphics/PostProcessor.h>

#include <map>

#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path

// All default shaders.

#define CE_UNLIT_SHADER *ResourceManager::standard.getShader("unlitShader")
#define CE_LIT_SHADER *ResourceManager::standard.getShader("litShader")
#define CE_TEXT_SHADER *ResourceManager::standard.getShader("text")
#define CE_WIDGET_SHADER *ResourceManager::standard.getShader("widget")
#define CE_RECTANGLE_SHADER *ResourceManager::standard.getShader("rectangle")
#define CE_CIRCLE_SHADER *ResourceManager::standard.getShader("circle")

#define CE_PP_BASIC_SHADER *ResourceManager::standard.getShader("pp.none")
#define CE_PP_REVERSED_COLORS_SHADER *ResourceManager::standard.getShader("pp.reverse_colors")
#define CE_PP_GRAYSCALE_SHADER *ResourceManager::standard.getShader("pp.grayscale")

class ResourceManager {
public:
    static std::map<const char*, Shader> shaders;
    static std::map<const char*, Texture> textures;
    static std::map<const char*, PostProcessor> post_processors;
    static ResourceManager standard;
    
    ResourceManager();
    
    Shader* loadShader(const char* name, const char* vertexShaderPath, const char* fragmentShaderPath);
    Shader* getShader(const char* name);
    
    Texture* loadTexture(const char* name, const char* texturePath);
    Texture* getTexture(const char* name);
    
    PostProcessor* loadPostProcessor(const char* name, Shader shader, unsigned int width, unsigned int height);
    PostProcessor* getPostProcessor(const char* name);
};

#endif
