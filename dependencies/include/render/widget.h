#ifndef CE_WIDGET_H
#define CE_WIDGET_H

#include <render/renderable.h>
#include <event/categories/mouse_events.h>
#include <event/categories/keyboard_events.h>
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
        this->onAction = onAction;
        this->onClick = onClick;
        this->onStartHovering = onStartHovering;
        this->onSubmit = onSubmit;
        this->onQuitHovering = onQuitHovering;
        this->onRelease = onRelease;
        this->onCharType = onCharType;
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
    void onMouseClick(const Event &e);
    void onMouseRelease(const Event &e);
    void onMouseMove(const Event &e);
    void onKeyPress(const Event &e);
    void onCharInput(const Event &e);
};

class TextBox : public Widget {
public:
    std::wstring text;
    TextPos textAlign;
    int textSize;
    glm::vec3 textColor;
    
    TextBox(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float boundX, float boundY, std::wstring text);
    
    virtual void update(glm::mat4 projection);
    TextBox* with_text(std::wstring text);
    TextBox* with_textColor(glm::vec3 color);
    TextBox* with_textAlign(TextPos alignment);
    TextBox* with_textSize(int size);
};

class Button : public Widget {
public:
    TextPos* textAlign;
    int* textSize;
    glm::vec3* textColor;
    float outlineThickness;
    glm::vec4 outlineColor;
    glm::vec4 hoverModifier;
    
    Button(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label);
    
    virtual void update(glm::mat4 projection);
    Button* with_onClick(std::function<void()> onClick);
    Button* with_onRelease(std::function<void()> onRelease);
    Button* with_color(glm::vec4 color);
    Button* with_theme(Color color);
    Button* with_outline(float thickness=0.05, glm::vec4 color=glm::vec4(0.4, 0.4, 0.4, 1.0));
    Button* with_textAlign(TextPos alignment);
    Button* with_textSize(int size);
    Button* with_textColor(glm::vec3 color);
};

class TexturedButton : public Widget {
public:
    std::map<ButtonState, Texture> buttonTextures;
    TextPos* textAlign;
    int* textSize;
    glm::vec3* textColor;
    
    TexturedButton(GLFWwindow* window, Shader shader, std::string pathToImages, float xpos, float ypos, float xscale, float yscale, std::string label);
    TexturedButton(GLFWwindow* window, Shader shader, Texture idle, Texture hover, float xpos, float ypos, float xscale, float yscale, std::string label);
    
    virtual void update(glm::mat4 projection);
    TexturedButton* with_onClick(std::function<void()> onClick);
    TexturedButton* with_onRelease(std::function<void()> onRelease);
    TexturedButton* with_color(glm::vec4 color);
    TexturedButton* with_color(Color color);
    TexturedButton* with_textSize(int size);
    TexturedButton* with_textColor(glm::vec3 color);
};

class TextInput : public Widget {
public:
    std::wstring* input;
    std::wstring floatingLabel;
    std::wstring text;
    int cursorPos;
    
    TextPos* textAlign;
    int* textSize;
    glm::vec3* textColor;
    
    float outlineThickness;
    glm::vec4 outlineColor;
    glm::vec4 hoverModifier;
    glm::vec3 baseTextColor;
    glm::vec3 labelColor;
    
    TextInput(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize);
    
    virtual void update(glm::mat4 projection);
    TextInput* with_onClick(std::function<void()> onClick);
    TextInput* with_onRelease(std::function<void()> onRelease);
    TextInput* with_onCharType(std::function<void()> onCharType);
    TextInput* with_color(glm::vec4 color);
    TextInput* with_color(Color color);
    TextInput* with_text(std::wstring text);
    TextInput* with_textSize(int size);
    TextInput* with_textColor(glm::vec3 color);
    TextInput* with_floatingLabel(std::wstring label);
    TextInput* with_floatingLabelColor(glm::vec3 color);
    
    double lastTypeTime;
};

#endif
