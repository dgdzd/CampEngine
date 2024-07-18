//
// Created by Noah Campagne on 14/07/2024.
//

#ifndef CE_TEXT_INPUT_H
#define CE_TEXT_INPUT_H

#include <CampEngine/Graphics/Core/Widget.h>
#include <CampEngine/Graphics/Core/Text/TextRenderer.h>
#include <CampEngine/Graphics/Widgets/TextBox.h>

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

    virtual void onKeyPress(const Event &e);
    virtual void onCharInput(const Event &e);

    double lastTypeTime;
};

#endif
