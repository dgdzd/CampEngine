//
// Created by Noah Campagne on 02/10/2024.
//

#include <CampEngine/Graphics/Widgets/Dropdown.h>

Dropdown::Dropdown(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string initialValue) : Widget(window, CE_WIDGET_SHADER, xpos, ypos, 127.0f, xsize, ysize, 1, 1, Action()) {
    this->selectedValue = initialValue;
}

Dropdown::Dropdown(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string initialValue, std::vector<std::string> values) : Widget(window, CE_WIDGET_SHADER, xpos, ypos, 127.0f, xsize, ysize, 1, 1, Action()) {
    this->selectedValue = initialValue;
    this->values = values;
}

void Dropdown::update(glm::mat4 projection) {
    shader.use();
    shader.setFloat("outlineThickness", outlineThickness);
    shader.setVec4("outlineColor", outlineColor);
    shader.setVec2("dimensions", boxSize);
    shader.setBool("hovered", action.isHovered);
    shader.setVec4("hoverModifier", hoverModifier);

    Widget::update(projection);
}

