#ifndef CE_WIDGET_H
#define CE_WIDGET_H

#include <render/renderable.h>
#include <event/events.h>
#include <utils/conversions.h>
#include <render/text/text_renderer.h>
#include <game/game.h>

#include <functional>
#include <iostream>
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
    
    bool isClicked;
    bool isHovered;
    
    Action(std::function<void()> onAction=[]() {},
           std::function<void()> onClick=[]() {},
           std::function<void()> onStartHovering=[]() {},
           std::function<void()> onSubmit=[]() {},
           std::function<void()> onQuitHovering=[]() {},
           std::function<void()> onRelease=[]() {}) {
        this->onAction = onAction;
        this->onClick = onClick;
        this->onStartHovering = onStartHovering;
        this->onSubmit = onSubmit;
        this->onQuitHovering = onQuitHovering;
        this->onRelease = onRelease;
    }
};

enum ButtonState {
    IDLE,
    HOVER,
    PRESSED,
    RELEASED
};

class Widget : public Renderable {
    public:
    int id;
    Action action;
    glm::vec2 position;
    glm::vec2 boxSize;
    std::vector<std::shared_ptr<Widget>> children;
    
    Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xsize, float ysize, Action action);
    
    virtual void update(glm::mat4 projection);
    void receiveEvent(Event* e);
};

class TextBox : public Widget {
    public:
    std::wstring text;
    int textSize;
    glm::vec3 textColor;
    
    TextBox(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float boundX, float boundY, std::wstring text, int textSize, glm::vec3 textColor);
    
    virtual void update(glm::mat4 projection);
};

class Button : public Widget {
    public:
    std::map<ButtonState, Texture> buttonTextures;
    int* textSize;
    glm::vec3* textColor;
    
    Button(GLFWwindow* window, Shader shader, std::string pathToImages, float xpos, float ypos, float xscale, float yscale, std::string label, std::function<void()> onClick=[]() {}, std::function<void()> onRelease=[]() {});
    Button(GLFWwindow* window, Shader shader, Texture idle, Texture hover, float xpos, float ypos, float xscale, float yscale, std::string label, std::function<void()> onClick=[]() {}, std::function<void()> onRelease=[]() {});
    
    virtual void update(glm::mat4 projection);
    
};

#endif
