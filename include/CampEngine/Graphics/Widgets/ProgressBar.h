//
// Created by Noah Campagne on 22/07/2024.
//

#ifndef CE_PROGRESS_BAR_H
#define CE_PROGRESS_BAR_H

#include <glm/glm.hpp>

#include <CampEngine/Graphics/Widgets/Internal/Rectangle.h>

class ProgressBar : public Widget {
private:
    float oldValue;
    Rectangle* base;
    Rectangle* baseStart;
    Rectangle* baseFinal;
    Rectangle* background;

    inline void updateBar();

public:
    float &value;
    float minValue;
    float maxValue;
    glm::vec4 backgroundColor;

    ProgressBar(GLFWwindow* window, float &value, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor=CENTER);

    virtual void update(glm::mat4 projection);
    ProgressBar* with_minValue(float minValue);
    ProgressBar* with_maxValue(float maxValue);
    ProgressBar* with_value(float value);
    ProgressBar* with_beginState(Rectangle* state);
    ProgressBar* with_finalState(Rectangle* state);
};

#endif
