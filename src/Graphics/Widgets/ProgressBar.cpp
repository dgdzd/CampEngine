//
// Created by Noah Campagne on 26/07/2024.
//

#include <CampEngine/Graphics/Widgets/ProgressBar.h>

ProgressBar::ProgressBar(GLFWwindow* window, float &value, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor) : Widget(window, xpos, ypos, anchor), value(value) {
    this->oldValue = 0.0f;
    this->minValue = std::numeric_limits<float>::min();
    this->maxValue = std::numeric_limits<float>::max();

    this->background = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
    background->with_color(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
    ->with_outline(0.0f, background->color);

    this->baseStart = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
    baseStart->scale = glm::vec3(0.0f, 0.0f, 1.0f);
    baseStart->with_theme(danger);

    this->baseFinal = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
    baseStart->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    baseStart->with_theme(success);

    this->base = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
}

void ProgressBar::update(glm::mat4 projection) {
    if(oldValue != value) this->updateBar();
    Widget::update(projection);
    oldValue = value;
}

inline void ProgressBar::updateBar() {
    /* First step: calculate alpha value */

    float d = maxValue - minValue;
    float a = (value - minValue) / d;

    // Position
    glm::vec3 dPos = baseFinal->transform - baseStart->transform;
    glm::vec3 newPos = baseStart->transform + a * dPos;
    this->base->transform = newPos;

    // Rotation
    glm::vec3 dRot = baseFinal->rotation - baseStart->rotation;
    glm::vec3 newRot = baseStart->rotation + a * dRot;
    this->base->rotation = newRot;

    // Scale
    glm::vec3 dScale = baseFinal->scale - baseStart->scale;
    glm::vec3 newScale = baseStart->scale + a * dScale;
    this->base->scale = newScale;

    // Color
    glm::vec3 dColor = baseFinal->scale - baseStart->scale;
    glm::vec3 newColor = baseStart->scale + a * dColor;
    this->base->scale = newColor;
}

