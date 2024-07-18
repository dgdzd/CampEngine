#ifndef CE_WIDGET_H
#define CE_WIDGET_H

#include <CampEngine/Game/Game.h>
#include <CampEngine/Graphics/Core/Renderable.h>
#include <CampEngine/Utils/conversions.h>

#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <locale>
#include <codecvt>
#include <string>
#include <map>

class Action {
    public:
    std::function<void()> onAction;
    std::function<void()> onClick;
    std::function<void()> onStartHovering;
    std::function<void()> onSubmit;
    std::function<void()> onQuitHovering;
    std::function<void()> onRelease;
    std::function<void()> onCharType;
    
    bool isClicked;
    bool isHovered;
    
    Action(std::function<void()> onAction=[]() {},
           std::function<void()> onClick=[]() {},
           std::function<void()> onStartHovering=[]() {},
           std::function<void()> onSubmit=[]() {},
           std::function<void()> onQuitHovering=[]() {},
           std::function<void()> onRelease=[]() {},
           std::function<void()> onCharType=[]() {}) {
        this->onAction = std::move(onAction);
        this->onClick = std::move(onClick);
        this->onStartHovering = std::move(onStartHovering);
        this->onSubmit = std::move(onSubmit);
        this->onQuitHovering = std::move(onQuitHovering);
        this->onRelease = std::move(onRelease);
        this->onCharType = std::move(onCharType);
    }
};

enum ButtonState {
    IDLE,
    HOVER,
    PRESSED,
    RELEASED
};

enum Color {
    normal,
    primary,
    success,
    warning,
    danger
};

class Widget : public Renderable {
public:
    int id;
    Action action;
    glm::vec2 position;
    glm::vec2 boxSize;
    std::vector<std::shared_ptr<Widget>> children;
    bool selected;
    
    Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action);
    Widget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xscale, float yscale, float xsize, float ysize, Action action);
    
    virtual void update(glm::mat4 projection);
    virtual void onMouseClick(const Event &e);
    virtual void onMouseRelease(const Event &e);
    virtual void onMouseMove(const Event &e);
    virtual void onKeyPress(const Event &e);
    virtual void onCharInput(const Event &e);
};

#endif
