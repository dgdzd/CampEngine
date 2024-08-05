//
// Created by Noah Campagne on 23/07/2024.
//

#include <CampEngine/Graphics/Widgets/Internal/Rectangle.h>

#include <CampEngine/Utils/ResourceManager.h>

Rectangle::Rectangle(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor) : Widget(window, *ResourceManager::standard.getShader("widget"), xpos, ypos, xsize, ysize, 1, 1, Action(), anchor) {
    this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
    this->outlineThickness = 1;
    this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
    this->hoverModifier = glm::vec4(1.2, 1.2, 1.2, 1.0);
}

void Rectangle::update(glm::mat4 projection) {
    shader.use();
    shader.setFloat("outlineThickness", outlineThickness);
    shader.setVec4("outlineColor", outlineColor);
    shader.setVec2("dimensions", boxSize);
    shader.setBool("hovered", action.isHovered);
    shader.setVec4("hoverModifier", hoverModifier);

    Widget::update(projection);
}

Rectangle* Rectangle::with_color(glm::vec4 color) {
    this->color = color;
}

Rectangle* Rectangle::with_theme(Color color) {
    switch(color) {
        case normal:
            this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
            this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
            return this;

        case primary:
            this->color = glm::vec4(0.1, 0.46, 0.82, 1.0);
            this->outlineColor = glm::vec4(0.25, 0.64, 0.96, 1.0);
            return this;

        case success:
            this->color = glm::vec4(0.18, 0.49, 0.2, 1.0);
            this->outlineColor = glm::vec4(0.3, 0.69, 0.31, 1.0);
            return this;

        case warning:
            this->color = glm::vec4(0.93, 0.42, 0.01, 1.0);
            this->outlineColor = glm::vec4(1.0, 0.6, 0.0, 1.0);
            return this;

        case danger:
            this->color = glm::vec4(0.83, 0.18, 0.18, 1.0);
            this->outlineColor = glm::vec4(0.94, 0.33, 0.31, 1.0);
            return this;

        default:
            return this;
    }
}


Rectangle* Rectangle::with_outline(float thickness, glm::vec4 color) {
    this->outlineThickness = thickness;
    this->outlineColor = color;
    return this;
}

Rectangle* Rectangle::with_hoverColorModifier(glm::vec4 color) {
    this->hoverModifier = color;
    return this;
}
