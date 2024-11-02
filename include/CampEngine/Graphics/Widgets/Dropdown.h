//
// Created by Noah Campagne on 28/09/2024.
//

#ifndef CE_DROPDOWN_H
#define CE_DROPDOWN_H

#include <CampEngine/Graphics/Core/Text/TextRenderer.h>
#include <CampEngine/Graphics/Core/Widget.h>

class Image;

class Dropdown : public Widget {
public:
    std::vector<std::string> values;
    std::string selectedValue;
    TextPos* textAlign;
    int* textSize;
    glm::vec4* textColor;
    float outlineThickness;
    glm::vec4 outlineColor;
    glm::vec4 hoverModifier;

    Dropdown(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string initialValue);
    Dropdown(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string initialValue, std::vector<std::string> values);

    virtual void update(glm::mat4 projection);
    void addValues(std::vector<std::string> values);
    Dropdown* with_onClick(std::function<void(Widget* self)> onClick);
    Dropdown* with_onRelease(std::function<void(Widget* self)> onRelease);
    Dropdown* with_color(glm::vec4 color);
    Dropdown* with_theme(Color color);
    Dropdown* with_outline(float thickness=1, glm::vec4 color=glm::vec4(0.4, 0.4, 0.4, 1.0));
    Dropdown* with_textAlign(TextPos alignment);
    Dropdown* with_textSize(int size);
    Dropdown* with_textColor(glm::vec4 color);
    Dropdown* with_hoverColorModifier(glm::vec4 color);

private:
    Image* arrow;
};

#endif
