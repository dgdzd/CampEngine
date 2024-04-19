#ifndef CE_TEXT_RENDERER_H
#define CE_TEXT_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <render/text/character.h>
#include <utils/resource_manager.h>

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

enum TextPos {
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
};

class TextRenderer {
    public:
    static TextRenderer* common;
    FT_Library* lib;
    FT_Face face;
    ResourceManager rm;
    unsigned int VAO, VBO;
    glm::mat4 projection;
    int resolution;
    
    TextRenderer();
    TextRenderer(FT_Library* lib);
    
    void loadFont(const char* pathToFont, int resolution);
    void text(std::wstring text, int x, int y, int boundX, int boundY, int size, glm::vec3 color, TextPos textAlign = ALIGN_LEFT);
    
    private:
    int textLength(std::wstring text);
};


#endif