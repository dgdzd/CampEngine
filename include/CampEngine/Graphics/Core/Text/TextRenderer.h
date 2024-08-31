#ifndef CE_TEXT_RENDERER_H
#define CE_TEXT_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <CampEngine/Utils/ResourceManager.h>

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
    void text(std::wstring text, float x, float y, float z_depth, float boundX, float boundY, int size, glm::vec4 color, TextPos textAlign = ALIGN_LEFT);
    int textLength(std::wstring text);
    int textLength(std::wstring text, int begin, int end=-1);
};


#endif
