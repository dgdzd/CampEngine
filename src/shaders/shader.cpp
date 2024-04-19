#include<shaders/shader.h>

Shader::Shader(const char* pathToVertexShader, const char* pathToFragmentShader, bool autocompile) {
    compiled = false;
    vertexShaderSource = getFileContent(pathToVertexShader);
    fragmentShaderSource = getFileContent(pathToFragmentShader);

    if(autocompile) {
        compile();
    }
}

void Shader::compile() {
    if(!compiled) {
        int success;
        char infoLog[512];

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "Failed to compile vertex shader\n" << infoLog << std::endl;
        }

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "Failed to compile fragment shader\n" << infoLog << std::endl;
        }

        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "Failed to link vertex shader and fragment shader\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        compiled = true;
    } else {
        std::cout << "ERROR: Already compiled the shader!" << std::endl;
    }
}
    
void Shader::use() {
    glUseProgram(id);
}

void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setTexture(const std::string &name, Texture value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value.id);
}

void Shader::setVec2(const std::string &name, glm::vec2 value) {
    glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string &name, glm::vec4 value) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}