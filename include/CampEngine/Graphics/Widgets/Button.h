//
// Created by Noah Campagne on 14/07/2024.
//

#ifndef CE_BUTTON_H
#define CE_BUTTON_H

#include <CampEngine/Graphics/Widgets/TextBox.h>
#include <CampEngine/Graphics/Core/Widget.h>

class Button : public Widget {
public:
    TextPos* textAlign;
    int* textSize;
    glm::vec3* textColor;
    float outlineThickness;
    glm::vec4 outlineColor;
    glm::vec4 hoverModifier;

    Button(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label);

    virtual void update(glm::mat4 projection);
    Button* with_onClick(std::function<void()> onClick);
    Button* with_onRelease(std::function<void()> onRelease);
    Button* with_color(glm::vec4 color);
    Button* with_theme(Color color);
    Button* with_outline(float thickness=0.05, glm::vec4 color=glm::vec4(0.4, 0.4, 0.4, 1.0));
    Button* with_textAlign(TextPos alignment);
    Button* with_textSize(int size);
    Button* with_textColor(glm::vec3 color);
};



#endif
