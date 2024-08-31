#include <CampEngine/Graphics/Core/Widget.h>

#include <CampEngine/Game/Game.h>
#include <CampEngine/Game/Events/Categories/KeyboardEvents.h>
#include <CampEngine/Game/Events/Categories/MouseEvents.h>
#include <CampEngine/Game/Events/Categories/WidgetEvents.h>

#include <functional>
#include <iostream>
#include <locale>
#include <map>
#include <string>
#include <utility>
#include <vector>


Widget::Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float z_depth, float xscale, float yscale, Action action, AnchorPoint anchor) : Widget(window, shader, xpos, ypos, z_depth, texture.width, texture.height, xscale, yscale, action, anchor) {
    this->texture = texture;
}

Widget::Widget(GLFWwindow* window, Shader shader, float xpos, float ypos, float z_depth, float xsize, float ysize, float xscale, float yscale, Action action, AnchorPoint anchor) : IWidget(window, shader, xpos, ypos, z_depth, xsize, ysize, xscale, yscale, action, anchor) {
    this->boxSize = glm::vec2(xsize * xscale, ysize * yscale);
    this->action = action;
    this->id = 100000 + rand() % (1000000 - 100000);
    this->selected = false;
    
    // Add listeners
    ADD_LISTENER(MouseClickEvent(), Widget::onMouseClick, this);
    ADD_LISTENER(MouseReleaseEvent(), Widget::onMouseRelease, this);
    ADD_LISTENER(MouseMoveEvent(), Widget::onMouseMove, this);
    ADD_LISTENER(KeyPressEvent(), Widget::onKeyPress, this);
    ADD_LISTENER(CharacterInputEvent(), Widget::onCharInput, this);
    ADD_LISTENER(WidgetClickEvent(), Widget::onWidgetClick, this);
    ADD_LISTENER(WidgetReleaseEvent(), Widget::onWidgetRelease, this);
}

Widget::Widget(GLFWwindow* window, float xpos, float ypos, float z_depth, AnchorPoint anchor) : Widget(window, Shader(), xpos, ypos, z_depth, 0, 0, 1, 1, Action(), anchor) {

}


void Widget::update(glm::mat4 projection) {
    this->render(projection);
    
    for(const std::shared_ptr<IWidget>& w : children) {
        w->update(projection);
    }
}

void Widget::onMouseClick(const Event &e) {
    auto event = e.as<MouseClickEvent>();
    selected = false;

    if(this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        this->action.isClicked = true;
        selected = true;
        this->action.onClick(this);
        
        WidgetClickEvent event_;
        event_.widget = this;
        event_.mouseX = event.mouseX;
        event_.mouseY = event.mouseY;
        event_.mouseButton = event.mouseButton;
        SEND_EVENT(event_);
    } else {
        this->action.isClicked = false;
    }
}

void Widget::onMouseRelease(const Event &e) {
    auto event = e.as<MouseReleaseEvent>();
    if(this->action.isClicked && selected && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        this->action.isClicked = false;
        this->action.onRelease(this);
        
        WidgetReleaseEvent event_;
        event_.widget = this;
        event_.mouseX = event.mouseX;
        event_.mouseY = event.mouseY;
        event_.mouseButton = event.mouseButton;
        SEND_EVENT(event_);
    }
    this->action.isClicked = false;
}

void Widget::onMouseMove(const Event &e) {
    auto event = e.as<MouseMoveEvent>();
    std::function<void()> quitHoveringfunc = [this, event]() {
        if(this->action.isHovered) {
            this->action.onQuitHovering(this);
            
            WidgetStopHoveringEvent event_;
            event_.widget = this;
            event_.mouseX = event.mouseX;
            event_.mouseY = event.mouseY;
            SEND_EVENT(event_);
        }
        this->action.isHovered = false;
    };
    
    if(position.x - boxSize.x/2 <= event.mouseX && event.mouseX <= position.x + boxSize.x/2) {
        if((Game::activeGame->frame.height - position.y) - boxSize.y/2 <= event.mouseY && event.mouseY <= (Game::activeGame->frame.height - position.y) + boxSize.y/2) {
            if(!this->action.isHovered) {
                this->action.isHovered = true;
                this->action.onStartHovering(this);
                
                WidgetStartHoveringEvent event_;
                event_.widget = this;
                event_.mouseX = event.mouseX;
                event_.mouseY = event.mouseY;
                SEND_EVENT(event_);
            }
        } else {
            quitHoveringfunc();
        }
    } else {
        quitHoveringfunc();
    }
}

void Widget::onStartHovering(const Event &e) {
    auto event = e.as<WidgetStartHoveringEvent>();
}

void Widget::onStopHovering(const Event &e) {
    auto event = e.as<WidgetStopHoveringEvent>();
}

void Widget::onKeyPress(const Event &e) {
    auto event = e.as<KeyPressEvent>();
}

void Widget::onCharInput(const Event &e) {
    auto event = e.as<CharacterInputEvent>();
    this->action.onCharType(this);
}

Widget* Widget::with_zDepth(float z_depth) {
    this->position.z = z_depth;
    return this;
}

