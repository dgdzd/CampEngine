#include <CampEngine/Utils/ResourceManager.h>

#include <CampEngine/Utils/FileUtils.h>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, PostProcessor> ResourceManager::post_processors;
ResourceManager ResourceManager::standard;

ResourceManager::ResourceManager() {
    
}

Shader* ResourceManager::loadShader(std::string name, const char* vertexShaderPath, const char* fragmentShaderPath) {
    Shader shader(vertexShaderPath, fragmentShaderPath);
    shaders[name] = shader;
    
    return &shaders[name];
}

Shader* ResourceManager::getShader(std::string name) {
    return &shaders[name];
}

Texture* ResourceManager::loadTexture(std::string name, const char* texturePath) {
    Texture texture(texturePath);
    textures[name] = texture;
    
    return &textures[name];
}

Texture* ResourceManager::getTexture(std::string name) {
    return &textures[name];
}

PostProcessor* ResourceManager::loadPostProcessor(std::string name, Shader shader, unsigned int width, unsigned int height) {
    PostProcessor processor(shader, width, height);
    post_processors[name] = processor;
    
    return &post_processors[name];
}

PostProcessor* ResourceManager::getPostProcessor(std::string name) {
    return &post_processors[name];
}

void ResourceManager::startEmbedding(const char* pathToFile) {
    embedFile = new File(pathToFile);
    embedFile->open(std::ios::out | std::ios::binary);
    embedFile->write("Coubeh10");
}

void ResourceManager::stopEmbedding() {
    embedFile->write("EOF");
    embedFile->flush();
    embedFile->close();
}


void ResourceManager::embedShader(std::string name) {
    Shader* shader = getShader(name);
    if(shader) {
        embedFile->write("Shader");
        embedFile->write(name);
        embedFile->write(shader);
    }
}

void ResourceManager::embedTexture(std::string name) {
    Texture* texture = getTexture(name);
    if(texture) {
        embedFile->write("Texture");
        embedFile->write(name);
        embedFile->write(texture);
    }
}

void ResourceManager::embedPostProcessor(std::string name) {
    PostProcessor* pp = getPostProcessor(name);
    if(pp) {
        embedFile->write("PostProc");
        embedFile->write(name);
        embedFile->write(pp);
    }
}

void ResourceManager::loadEmbeddedData(const char* pathToFile) {
    File file(pathToFile);
    file.open(std::ios::out | std::ios::binary);
    if(file.read<std::string>(8) != "Coubeh10") {
        Logger::CampEngine.error("Invalid signature of file at: "+std::string(pathToFile));
        return;
    }
    for(auto arg = file.read<std::string>(); arg != "EOF"; arg = file.read<std::string>()) {
        auto name = file.read<std::string>();
        if(arg == "Shader") {
            shaders[name] = file.read<Shader>();
            break;
        } else if(arg == "Texture") {
            textures[name] = file.read<Texture>();
            break;
        } else if(arg == "PostProc") {
            post_processors[name] = file.read<PostProcessor>();
            break;
        }
    }
}