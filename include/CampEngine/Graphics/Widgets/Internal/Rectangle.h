//
// Created by Noah Campagne on 23/07/2024.
//

#ifndef CE_RECTANGLE_H
#define CE_RECTANGLE_H

#include <glm/glm.hpp>

#include <CampEngine/Graphics/Core/Widget.h>

class Rectangle : public Widget {
public:
    float outlineThickness;
    glm::vec4 outlineColor;
    glm::vec4 hoverModifier;

    Rectangle(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor=CENTER);

    virtual void update(glm::mat4 projection);
    Rectangle* with_onClick(std::function<void(Widget* self)> onClick);
    Rectangle* with_onRelease(std::function<void(Widget* self)> onRelease);
    Rectangle* with_color(glm::vec4 color);
    Rectangle* with_theme(Color theme);
    Rectangle* with_outline(float thickness=1, glm::vec4 color=glm::vec4(0.4, 0.4, 0.4, 1.0));
    Rectangle* with_hoverColorModifier(glm::vec4 color);
};

#endif
