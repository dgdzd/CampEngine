//
// Created by Noah Campagne on 19/07/2024.
//

#ifndef CE_IWIDGET_H
#define CE_IWIDGET_H

#include <CampEngine/Graphics/Core/Renderable.h>
#include <CampEngine/Game/Events/Event.h>

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

class IWidget : public Renderable {
public:
    int id;
    Action action;
    glm::vec2 position;
    glm::vec2 boxSize;
    std::vector<std::shared_ptr<IWidget>> children;
    bool selected;

    IWidget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action);
    IWidget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xsize, float ysize, float xscale, float yscale, Action action);
    IWidget(GLFWwindow* window, float xpos, float ypos);

    virtual void update(glm::mat4 projection);
    virtual void onMouseClick(const Event &e);
    virtual void onMouseRelease(const Event &e);
    virtual void onMouseMove(const Event &e);
    virtual void onKeyPress(const Event &e);
    virtual void onCharInput(const Event &e);
    virtual void onWidgetClick(const Event &e);
    virtual void onWidgetRelease(const Event &e);
};

#endif
