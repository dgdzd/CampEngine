//
// Created by Noah Campagne on 26/07/2024.
//

#ifndef CE_CIRCLE_H
#define CE_CIRCLE_H

#include <CampEngine/Graphics/Core/Widget.h>

class Circle : public Widget {
public:
    float radius{};
    float outlineThickness{};
    glm::vec4 outlineColor;
    glm::vec4 hoverModifier;

    Circle(GLFWwindow* window, float xpos, float ypos, float radius);

    virtual void update(glm::mat4 projection);
    Circle* with_color(glm::vec4 color);
    Circle* with_theme(Color color);
    Circle* with_outline(float thickness=1, glm::vec4 color);
};

#endif
