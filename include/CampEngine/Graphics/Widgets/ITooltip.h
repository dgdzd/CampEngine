//
// Created by Noah Campagne on 15/08/2024.
//

#ifndef CE_ITOOLTIP_H
#define CE_ITOOLTIP_H

#include <CampEngine/Graphics/Core/Widget.h>

class ITooltip : public Widget {
private:
    float oldX;
    float oldY;
    bool oldHovered;
    bool fadingIn;
    bool fadingOut;
    double hoverBeginTime;
    double hoverEndTime;
    inline void fadeIn();
    inline void fadeOut();

protected:
    float a;
    glm::vec4 savedColor;

public:
    float cooldown;
    float delayIn;
    float delayOut;
    float fadeInTime;
    float fadeOutTime;
    IWidget* parent;

    ITooltip(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, IWidget* parent,
        float delayIn=0.0f, float delayOut=0.0f, float fadeInTime=0.0f, float fadeOutTime=0.0f, float cooldown=0.0f);

    virtual void update(glm::mat4 projection);
};

#endif
