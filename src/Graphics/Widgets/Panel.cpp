//
// Created by Noah Campagne on 22/07/2024.
//

#include <CampEngine/Graphics/Widgets/Panel.h>
#include <CampEngine/Utils/ResourceManager.h>

Panel::Panel(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor) : Widget(window, CE_WIDGET_SHADER, xpos, ypos, xsize, ysize, 1, 1, Action(), anchor) {
    this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
    this->outlineThickness = 1;
    this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
}

void Panel::update(glm::mat4 projection) {
    Widget::update(projection);
}


Panel* Panel::with_color(glm::vec4 color) {
    this->color = color;
    return this;
}

Panel* Panel::with_outline(float thickness, glm::vec4 color) {
    this->outlineThickness = thickness;
    this->outlineColor = color;
    return this;
}

