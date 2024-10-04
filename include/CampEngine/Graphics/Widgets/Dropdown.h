//
// Created by Noah Campagne on 28/09/2024.
//

#ifndef CE_DROPDOWN_H
#define CE_DROPDOWN_H

#include <CampEngine/Graphics/Core/Text/TextRenderer.h>
#include <CampEngine/Graphics/Core/Widget.h>

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
    void addElement(std::string element);
};

#endif
