#include <CampEngine/Graphics/Core/Text/TextRenderer.h>

#include <glad/glad.h>

#include <CampEngine/Graphics/Core/Text/Character.h>

#include <codecvt>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

TextRenderer* TextRenderer::common;

TextRenderer::TextRenderer() {
    
}

TextRenderer::TextRenderer(FT_Library* lib) {
    this->lib = lib;
}

void TextRenderer::loadFont(const char* pathToFont, int resolution) {
    this->resolution = resolution;
    if(FT_New_Face(*lib, pathToFont, 0, &face)) {
        Logger::CampEngine.error("Failed to load font at location: " + std::string(pathToFont));
    } else {
        //FT_Select_Charmap(face, ft_encoding_apple_roman);
        FT_Set_Pixel_Sizes(face, 0, 48);
        Logger::CampEngine.info("Loading chars...");
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        unsigned int index = 0;
        unsigned long c = 0;
        while((c = FT_Get_Next_Char(face, c, &index))) {
            if(FT_Load_Glyph(face, index, FT_LOAD_RENDER)) {
                Logger::CampEngine.warn(std::string("Failed to load character \"") + (char)c + "\"");
                continue;
            }
            //std::wcout << "Loading character " << index << "\"\n";
            
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            Character ch = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            
            Character::characters[c] = ch;
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(*lib);
    
    Logger::CampEngine.info("Generating vertex array and vertex buffer objects...");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    Logger::CampEngine.info("Done!");
}

void TextRenderer::text(std::wstring text, float x, float y, float boundX, float boundY, int size, glm::vec4 color, TextPos textAlign) {
    std::wstring::const_iterator c;
    Shader shader = CE_TEXT_SHADER;
    float scale = static_cast<float>(size) / resolution;
    shader.use();
    shader.setVec4("textColor", color);
    glBindVertexArray(VAO);
    
    switch(textAlign) {
        case ALIGN_LEFT: {
            x += 6*scale;
            break;
        }
        case ALIGN_CENTER: {
            x += (boundX - textLength(text)*scale)/2;
            break;
        }
        case ALIGN_RIGHT: {
            x += boundX - textLength(text)*scale;
            break;
        }
    }
    
    y -= (size/2+6)*scale;
    
    // Render all the chars
    for(c = text.begin(); c != text.end(); c++) {
        Character ch = Character::characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        shader.setInt("text", 0);
        shader.setMat4("projection", projection);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDisable(GL_CULL_FACE);
        //glDisable(GL_BLEND);
        // advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int TextRenderer::textLength(std::wstring text) {
    int size = 0;
    std::wstring::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Character ch = Character::characters[*c];
        size += (ch.advance >> 6);
    }
    
    return size;
}

int TextRenderer::textLength(std::wstring text, int begin, int end) {
    if(end == -1) end = text.size()-1;
    int size = 0;
    std::wstring::const_iterator c;
    for(c = text.begin()+begin; c < text.begin()+end; c++) {
        Character ch = Character::characters[*c];
        size += (ch.advance >> 6);
    }
    return size;
}
