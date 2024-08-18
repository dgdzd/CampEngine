//
// Created by Noah Campagne on 15/08/2024.
//

#include <CampEngine/Graphics/Widgets/ITooltip.h>

#include <CampEngine/Game/Game.h>

ITooltip::ITooltip(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale,
                   IWidget* parent, float delayIn, float delayOut, float fadeInTime, float fadeOutTime, float cooldown) : Widget(window, shader, texture, xpos, ypos, xscale, yscale, Action()) {
    this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
    this->oldX = xpos;
    this->oldY = ypos;
    this->parent = parent;
    this->delayIn = delayIn;
    this->delayOut = delayOut;
    this->fadeInTime = fadeInTime;
    this->fadeOutTime = fadeOutTime;
    this->cooldown = cooldown;
    this->a = 0.0f;
    this->hoverBeginTime = 0.0f;
    this->hoverEndTime = -cooldown;

    savedColor = color;
}

void ITooltip::fadeIn() {
    if(fadeInTime > 0.0f) {
        double dt = Game::activeGame->gameInfos.deltaTime;
        float aPerSec = 1.0f / fadeInTime;
        a += aPerSec * dt;
        if((a = std::min(1.0f, a)) == 1.0f) {
            fadingIn = false;
        }
    } else {
        fadingIn = false;
        a = 1.0f;
    }
}

void ITooltip::fadeOut() {
    if(fadeOutTime > 0.0f) {
        double dt = Game::activeGame->gameInfos.deltaTime;
        float aPerSec = 1.0f / fadeOutTime;
        a -= aPerSec * dt;
        if((a = std::max(0.0f, a)) == 0.0f) {
            fadingOut = false;
        }
    } else {
        fadingOut = false;
        a = 0.0f;
    }
}


void ITooltip::update(glm::mat4 projection) {
    if(!parent) return;
    double time = glfwGetTime();
    position.x = std::min(Game::activeGame->frame.width - boxSize.x/2, std::max((float)Game::activeGame->mouse.xpos, boxSize.x/2));
    position.y = Game::activeGame->frame.height - Game::activeGame->mouse.ypos + boxSize.y/2 + 3;
    if(oldX != position.x || oldY != position.y) {
        float offsetX = position.x - oldX;
        float offsetY = position.y - oldY;

        for(auto child : children) {
            child->position += glm::vec3(offsetX, offsetY, 0.0f);
        }
    }
    if(fadingIn && time >= hoverEndTime + cooldown && time >= hoverBeginTime + delayIn) fadeIn();
    else if(fadingOut && time >= hoverEndTime + delayOut) fadeOut();
    color.a = a * savedColor.a;

    oldX = position.x;
    oldY = position.y;

    if(!parent->action.isHovered) {
        if(oldHovered) {
            fadingOut = true;
            fadingIn = false;
        }
        oldHovered = false;
        hoverEndTime = glfwGetTime();
        if(!fadingOut) {
            return;
        }
    } else {
        if(!oldHovered) {
            fadingIn = true;
            fadingOut = false;
            hoverBeginTime = glfwGetTime();
        }

        oldHovered = true;
    }
    Widget::update(projection);
}

