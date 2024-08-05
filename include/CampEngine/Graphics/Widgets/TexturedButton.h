//
// Created by Noah Campagne on 14/07/2024.
//

#ifndef CE_TEXTURED_BUTTON_H
#define CE_TEXTURED_BUTTON_H

#include <CampEngine/Graphics/Core/Widget.h>
#include <CampEngine/Graphics/Core/Text/TextRenderer.h>

class TexturedButton : public Widget {
public:
    std::map<ButtonState, Texture> buttonTextures;
    TextPos* textAlign;
    int* textSize;
    glm::vec3* textColor;

    TexturedButton(GLFWwindow* window, Shader shader, std::string pathToImages, float xpos, float ypos, float xscale, float yscale, std::string label);
    TexturedButton(GLFWwindow* window, Shader shader, Texture idle, Texture hover, float xpos, float ypos, float xscale, float yscale, std::string label);

    virtual void update(glm::mat4 projection);
    TexturedButton* with_onClick(std::function<void(Widget* self)> onClick);
    TexturedButton* with_onRelease(std::function<void(Widget* self)> onRelease);
    TexturedButton* with_color(glm::vec4 color);
    TexturedButton* with_textSize(int size);
    TexturedButton* with_textColor(glm::vec3 color);
};

#endif
