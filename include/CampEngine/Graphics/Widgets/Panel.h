//
// Created by Noah Campagne on 21/07/2024.
//

#ifndef CE_PANEL_H
#define CE_PANEL_H

#include <CampEngine/Graphics/Core/Widget.h>

class Panel : public Widget {
public:
    float outlineThickness;
    glm::vec4 outlineColor;

    Panel(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor);

    virtual void update(glm::mat4 projection);
    Panel* with_color(glm::vec4 color);
    Panel* with_outline(float thickness=1, glm::vec4 color=glm::vec4(0.4, 0.4, 0.4, 1.0));
};

#endif
