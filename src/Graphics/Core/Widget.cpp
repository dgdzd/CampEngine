#include <CampEngine/Graphics/Core/Widget.h>

#include <CampEngine/Game/Game.h>

#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <locale>
#include <codecvt>
#include <string>
#include <map>

/*---- Forward Declaration ----*/
class Game;
class Renderable;
class TextInput;
class TextBox;
/*-----------------------------*/

Widget::Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action) : IWidget(window, shader, xpos, ypos, texture.width, texture.height, xscale, yscale, action) {
    
}

Widget::Widget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xsize, float ysize, float xscale, float yscale, Action action) : IWidget(window, shader, xpos, ypos, xscale, yscale, xsize, ysize, action) {
    this->position = glm::vec2(xpos, ypos);
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
}

void Widget::update(glm::mat4 projection) {
    this->render(projection);
    
    for(int w = 0; w < children.size(); w++) {
        children.at(w).get()->update(projection);
        //std::cout << "CHILDRENS\n";
    }
}

void Widget::onMouseClick(const Event &e) {
    auto event = e.as<MouseClickEvent>();
    selected = false;
    
    if(this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        this->action.isClicked = true;
        selected = true;
        this->action.onClick();
        
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
    if(this->action.isClicked && this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        this->action.isClicked = false;
        this->action.onRelease();
        
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
            this->action.onQuitHovering();
            
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
                this->action.onStartHovering();
                
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

void Widget::onKeyPress(const Event &e) {
    auto event = e.as<KeyPressEvent>();
}

void Widget::onCharInput(const Event &e) {
    auto event = e.as<CharacterInputEvent>();
    this->action.onCharType();
}