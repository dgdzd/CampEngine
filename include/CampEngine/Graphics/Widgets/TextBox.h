//
// Created by Noah Campagne on 14/07/2024.
//

#ifndef CE_TEXT_BOX_H
#define CE_TEXT_BOX_H

#include <CampEngine/Graphics/Core/Widget.h>
#include <CampEngine/Graphics/Core/Text/TextRenderer.h>

class TextBox : public Widget {
public:
    std::wstring text;
    TextPos textAlign;
    int textSize;
    glm::vec4 textColor;

    TextBox(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float z_depth, float boundX, float boundY, std::wstring text);

    virtual void update(glm::mat4 projection);
    TextBox* with_text(std::wstring text);
    TextBox* with_textColor(glm::vec4 color);
    TextBox* with_textAlign(TextPos alignment);
    TextBox* with_textSize(int size);
};

#endif
