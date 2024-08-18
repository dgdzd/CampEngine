//
// Created by Noah Campagne on 19/07/2024.
//

#ifndef CE_IWIDGET_H
#define CE_IWIDGET_H

#include <CampEngine/Graphics/Core/Renderable.h>
#include <CampEngine/Game/Events/Event.h>

class Widget;
class ITooltip;

class Action {
public:
    std::function<void(Widget* self)> onAction;
    std::function<void(Widget* self)> onClick;
    std::function<void(Widget* self)> onStartHovering;
    std::function<void(Widget* self)> onSubmit;
    std::function<void(Widget* self)> onQuitHovering;
    std::function<void(Widget* self)> onRelease;
    std::function<void(Widget* self)> onCharType;
    std::function<void(Widget* self)> onValueChange;

    bool isClicked;
    bool isHovered;

    Action(std::function<void(Widget* self)> onAction=[](Widget* self) {},
           std::function<void(Widget* self)> onClick=[](Widget* self) {},
           std::function<void(Widget* self)> onStartHovering=[](Widget* self) {},
           std::function<void(Widget* self)> onSubmit=[](Widget* self) {},
           std::function<void(Widget* self)> onQuitHovering=[](Widget* self) {},
           std::function<void(Widget* self)> onRelease=[](Widget* self) {},
           std::function<void(Widget* self)> onCharType=[](Widget* self) {},
           std::function<void(Widget* self)> onValueChange=[](Widget* self) {}) {
        this->onAction = std::move(onAction);
        this->onClick = std::move(onClick);
        this->onStartHovering = std::move(onStartHovering);
        this->onSubmit = std::move(onSubmit);
        this->onQuitHovering = std::move(onQuitHovering);
        this->onRelease = std::move(onRelease);
        this->onCharType = std::move(onCharType);
        this->onValueChange = std::move(onValueChange);
        isClicked = false;
        isHovered = false;
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
    glm::vec2 boxSize;
    std::vector<std::shared_ptr<IWidget>> children;
    bool selected;

    IWidget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action, AnchorPoint anchor=CENTER);
    IWidget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xsize, float ysize, float xscale, float yscale, Action action, AnchorPoint anchor=CENTER);
    IWidget(GLFWwindow* window, float xpos, float ypos, AnchorPoint anchor=CENTER);

    virtual void update(glm::mat4 projection);
    virtual void onMouseClick(const Event &e);
    virtual void onMouseRelease(const Event &e);
    virtual void onMouseMove(const Event &e);
    virtual void onStartHovering(const Event &e);
    virtual void onStopHovering(const Event &e);
    virtual void onKeyPress(const Event &e);
    virtual void onCharInput(const Event &e);
    virtual void onWidgetClick(const Event &e);
    virtual void onWidgetRelease(const Event &e);
    void addTooltip(ITooltip* tooltip);
};

#endif
