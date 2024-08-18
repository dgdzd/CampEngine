//
// Created by Noah Campagne on 16/08/2024.
//

#ifndef CE_TOOLTIP_H
#define CE_TOOLTIP_H

#include <CampEngine/Graphics/Widgets/ITooltip.h>

class TextBox;

class Tooltip : public ITooltip {
private:
    glm::vec4 savedOutline;
    glm::vec4 savedTextColor;

public:
    TextBox* tb;
    glm::vec4 outlineColor;
    float outlineThickness;
    glm::vec4 hoverModifier;

    Tooltip(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label);

    virtual void update(glm::mat4 projection);
    Tooltip* with_delayIn(float delay);
    Tooltip* with_delayOut(float delay);
    Tooltip* with_fadeInTime(float time);
    Tooltip* with_fadeOutTime(float time);
    Tooltip* with_cooldown(float cooldown);
};

#endif
