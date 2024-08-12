#ifndef CE_RESOURCE_MANAGER_H
#define CE_RESOURCE_MANAGER_H

#include <CampEngine/Graphics/Shader.h>
#include <CampEngine/Graphics/Texture.h>
#include <CampEngine/Graphics/Level.h>
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

class File;

class ResourceManager {
private:
    File* embedFile;

public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;
    static std::map<std::string, PostProcessor> post_processors;
    static std::map<std::string, Level> levels;
    static ResourceManager standard;
    
    ResourceManager();
    
    Shader* loadShader(std::string name, const char* vertexShaderPath, const char* fragmentShaderPath);
    Shader* getShader(std::string name);
    
    Texture* loadTexture(std::string name, const char* texturePath);
    Texture* getTexture(std::string name);
    
    PostProcessor* loadPostProcessor(std::string name, Shader shader, unsigned int width, unsigned int height);
    PostProcessor* getPostProcessor(std::string name);

    Level* loadLevel(std::string name, Camera &activeCamera);
    Level* getLevel(std::string name);

    void startEmbedding(const char* pathToFile);
    void stopEmbedding();
    void embedShader(std::string name);
    void embedTexture(std::string name);
    void embedPostProcessor(std::string name);
    void embedLevel(std::string name);
    void loadEmbeddedData(const char* pathToFile);
};

#endif
