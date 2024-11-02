//
// Created by Noah Campagne on 08/08/2024.
//

#ifndef CE_SLIDER_H
#define CE_SLIDER_H

#include <CampEngine/Graphics/Core/Widget.h>

#define DIR_HORIZONTAL 0x1
#define DIR_VERTICAL 0x2

class Slider : public Widget {
private:
    bool sliding;
    Widget* beginBullet;
    Widget* finalBullet;
    Widget* bullet;
    Widget* body;
    float oldValue;
    float decayX;
    float decayY;
    float a;

    void updateAlpha();

public:
    int direction;
    float value;
    float minValue;
    float maxValue;

    Slider(GLFWwindow* window, float value, float xpos, float ypos, float xsize, float ysize, int direction, AnchorPoint anchor=CENTER);

    virtual void update(glm::mat4 projection);
    void updateSlider();
    Slider* with_minValue(float minValue);
    Slider* with_maxValue(float maxValue);
    Slider* with_value(float value);
    Slider* with_onValueChange(std::function<void(Widget* self)> onValueChange);
    Slider* with_beginState(Widget* state);
    Slider* with_finalState(Widget* state);
    Slider* with_hoverColorModifier(glm::vec4 color);
};

#endif
