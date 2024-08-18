//
// Created by Noah Campagne on 26/07/2024.
//

#include <CampEngine/Graphics/Widgets/ProgressBar.h>

ProgressBar::ProgressBar(GLFWwindow* window, float value, float xpos, float ypos, float xsize, float ysize, AnchorPoint anchor) : Widget(window, xpos, ypos, anchor) {
    this->value = value;
    this->oldValue = 0.0f;
    this->minValue = std::numeric_limits<float>::min();
    this->maxValue = std::numeric_limits<float>::max();

    this->background = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
    background->with_color(glm::vec4(0.0f))
    ->with_outline(1.5f, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

    this->baseStart = new Rectangle(window, xpos - xsize/2, ypos, xsize, ysize, anchor);
    baseStart->scale = glm::vec3(0.0f, 1.0f, 1.0f);
    baseStart->with_theme(danger);

    this->baseFinal = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
    baseFinal->scale = glm::vec3(1.0f, 1.0f, 1.0f);
    baseFinal->with_theme(success);

    this->base = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
}

void ProgressBar::update(glm::mat4 projection) {
    if(oldValue != value) this->updateBar();
    background->update(projection);
    base->update(projection);
    for(const std::shared_ptr<IWidget>& w : children) {
        w->update(projection);
    }
    oldValue = value;
}

inline void ProgressBar::updateBar() {
    /* First step: calculate alpha value */

    float d = maxValue - minValue;
    float a = (value - minValue) / d;
    a = std::max(std::min(a, 1.0f), 0.0f);

    // Position
    glm::vec3 dPos = baseFinal->position - baseStart->position;
    glm::vec3 newPos = baseStart->position + a * dPos;
    this->base->position = newPos;

    // Rotation
    glm::vec3 dRot = baseFinal->rotation - baseStart->rotation;
    glm::vec3 newRot = baseStart->rotation + a * dRot;
    this->base->rotation = newRot;

    // Scale
    glm::vec3 dScale = baseFinal->scale - baseStart->scale;
    glm::vec3 newScale = baseStart->scale + a * dScale;
    this->base->scale = newScale;

    // Color
    glm::vec4 dColor = baseFinal->color - baseStart->color;
    glm::vec4 newColor = baseStart->color + a * dColor;
    this->base->color = newColor;

    // Outline Color
    glm::vec4 dOutlineColor = baseFinal->outlineColor - baseStart->outlineColor;
    glm::vec4 newOutlineColor = baseStart->outlineColor + a * dOutlineColor;
    this->base->outlineColor = newOutlineColor;

    // Outline Color
    float dOutlineThickness = baseFinal->outlineThickness - baseStart->outlineThickness;
    float newOutlineThickness = baseStart->outlineThickness + a * dOutlineThickness;
    this->base->outlineThickness = newOutlineThickness;
}

ProgressBar* ProgressBar::with_minValue(float minValue) {
    this->minValue = minValue;
    return this;
}

ProgressBar* ProgressBar::with_maxValue(float maxValue) {
    this->maxValue = maxValue;
    return this;
}

ProgressBar* ProgressBar::with_value(float value) {
    this->value = value;
    return this;
}

ProgressBar* ProgressBar::with_beginState(Rectangle* state) {
    this->baseStart = state;
    return this;
}

ProgressBar* ProgressBar::with_finalState(Rectangle* state) {
    this->baseFinal = state;
    return this;
}

ProgressBar* ProgressBar::with_hoverColorModifier(glm::vec4 color) {
    base->hoverModifier = color;
    background->hoverModifier = color;
    return this;
}

