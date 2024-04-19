#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utils/filereader.h>
#include <textures/texture.h>

#include <string>

#pragma once
class Shader {
    public:
    unsigned int id;
    char* vertexShaderSource;
    char* fragmentShaderSource;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    bool compiled;

    Shader(const char* pathToVertexShader, const char* pathToFragmentShader, bool autocompile=true);

    void compile();
    void use();
    void setInt(const std::string &name, int value);
    void setBool(const std::string &name, bool value);
    void setFloat(const std::string &name, float value);
    void setTexture(const std::string &name, Texture value);
    void setVec2(const std::string &name, glm::vec2 value);
    void setVec3(const std::string &name, glm::vec3 value);
    void setVec4(const std::string &name, glm::vec4 value);
};