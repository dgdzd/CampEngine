//
// Created by Noah Campagne on 08/08/2024.
//

#include <CampEngine/Graphics/Widgets/Slider.h>

#include <CampEngine/Game/Game.h>
#include <CampEngine/Graphics/Widgets/Internal/Circle.h>
#include <CampEngine/Graphics/Widgets/Internal/Rectangle.h>
#include <CampEngine/Utils/ResourceManager.h>

#include "CampEngine/Game/Events/Categories/WidgetEvents.h"


Slider::Slider(GLFWwindow* window, float value, float xpos, float ypos, float xsize, float ysize, int direction, AnchorPoint anchor) : Widget(window, CE_WIDGET_SHADER, xpos, ypos, 127.0f, xsize, ysize, 1, 1, Action()) {
    this->decayX = 0.0f;
    this->decayY = 0.0f;
    this->oldValue = 0.0f;
    this->minValue = std::numeric_limits<float>::min();
    this->maxValue = std::numeric_limits<float>::max();
    this->value = value;
    this->direction = direction;

    this->body = new Rectangle(window, xpos, ypos, xsize, ysize, anchor);
    this->body->as<Rectangle>()
    ->with_onClick([this](Widget* self) {
        this->decayX = Game::activeGame->mouse.xpos - self->position.x;
        this->decayY = Game::activeGame->mouse.ypos - self->position.y;
        this->sliding = true;
    });

    float size = 3.0f;
    this->beginBullet = new Rectangle(window, xpos - xsize/2, ypos, ysize * size, ysize * size);
    beginBullet->with_zDepth(position.z - 1);

    this->finalBullet = new Rectangle(window, xpos + xsize/2, ypos, ysize * size, ysize * size);
    finalBullet->with_zDepth(position.z - 1);

    this->bullet = new Rectangle(window, xpos + xsize/2, ypos, ysize * size, ysize * size);
    bullet->with_zDepth(position.z - 1);
    this->bullet->as<Rectangle>()
    ->with_onClick([this](Widget* self) {
        this->decayX = Game::activeGame->mouse.xpos - self->position.x;
        this->decayY = Game::activeGame->mouse.ypos - self->position.y;
        this->sliding = true;
    })
    ->with_onRelease([this](Widget* self) {
        this->sliding = false;
    });

    a = value;
}

void Slider::update(glm::mat4 projection) {
    // Calculate slider's value
    if(sliding) {
        updateAlpha();
    }
    if(oldValue != value) {
        updateSlider();
        oldValue = value;

        action.onValueChange(this);
        WidgetValueChangeEvent event;
        event.widget = this;
        event.oldValue = oldValue;
        event.value = value;
        SEND_EVENT(event);
    }

    body->update(projection);
    bullet->update(projection);
    for(const std::shared_ptr<IWidget>& w : children) {
        w->update(projection);
    }
}

void Slider::updateAlpha() {
    float d;
    if(direction == DIR_HORIZONTAL) {
        d = Game::activeGame->mouse.xpos - position.x + boxSize.x/2;
        a = d / boxSize.x;
    }
    else if(direction == DIR_VERTICAL) {
        d = Game::activeGame->mouse.ypos - position.y + boxSize.y/2;
        a = d / boxSize.y;
    }
    a = std::max(std::min(a, 1.0f), 0.0f);
    value = a * maxValue + (1 - a) * minValue;
}


void Slider::updateSlider() {
    // Position
    glm::vec3 dPos = finalBullet->position - beginBullet->position;
    glm::vec3 newPos = beginBullet->position + a * dPos;
    this->bullet->position = newPos;

    // Rotation
    glm::vec3 dRot = finalBullet->rotation - beginBullet->rotation;
    glm::vec3 newRot = beginBullet->rotation + a * dRot;
    this->bullet->rotation = newRot;

    // Scale
    glm::vec3 dScale = finalBullet->scale - beginBullet->scale;
    glm::vec3 newScale = beginBullet->scale + a * dScale;
    this->bullet->scale = newScale;

    // Color
    glm::vec4 dColor = finalBullet->color - beginBullet->color;
    glm::vec4 newColor = beginBullet->color + a * dColor;
    this->bullet->color = newColor;

    // // Outline Color
    // glm::vec4 dOutlineColor = finalBullet->outlineColor - beginBullet->outlineColor;
    // glm::vec4 newOutlineColor = beginBullet->outlineColor + a * dOutlineColor;
    // this->b->outlineColor = newOutlineColor;
    //
    // // Outline Color
    // float dOutlineThickness = finalBullet->outlineThickness - beginBullet->outlineThickness;
    // float newOutlineThickness = beginBullet->outlineThickness + a * dOutlineThickness;
    // this->base->outlineThickness = newOutlineThickness;
}

Slider* Slider::with_minValue(float minValue) {
    this->minValue = minValue;
    a = (value - minValue) / (maxValue - minValue);
    a = std::max(0.0f, std::min(1.0f, a));
    return this;
}

Slider* Slider::with_maxValue(float maxValue) {
    this->maxValue = maxValue;
    a = (value - minValue) / (maxValue - minValue);
    a = std::max(0.0f, std::min(1.0f, a));
    return this;
}

Slider* Slider::with_value(float value) {
    this->value = value;
    a = (value - minValue) / (maxValue - minValue);
    a = std::max(0.0f, std::min(1.0f, a));
    return this;
}

Slider* Slider::with_onValueChange(std::function<void(Widget* self)> onValueChange) {
    this->action.onValueChange = std::move(onValueChange);
    return this;
}


Slider* Slider::with_beginState(Widget* state) {
    this->beginBullet = state;
    return this;
}

Slider* Slider::with_finalState(Widget* state) {
    this->finalBullet = state;
    return this;
}

Slider* Slider::with_hoverColorModifier(glm::vec4 color) {
    bullet->as<Circle>()->hoverModifier = color;
    body->as<Rectangle>()->hoverModifier = color;
    return this;
}