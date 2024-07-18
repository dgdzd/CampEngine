//
// Created by Noah Campagne on 14/07/2024.
//


#include <CampEngine/Graphics/Widgets/TexturedButton.h>
#include <CampEngine/Graphics/Widgets/TextBox.h>

TexturedButton::TexturedButton(GLFWwindow* window, Shader shader, Texture idle, Texture hover, float xpos, float ypos, float xscale, float yscale, std::string label) : Widget(window, shader, idle, xpos, ypos, xscale, yscale, Action()) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    TextBox* tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, texture.width * xscale, texture.height * yscale, converter.from_bytes(label));
    std::shared_ptr shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);

    this->textAlign = &shared_tb.get()->textAlign;
    this->textSize = &shared_tb.get()->textSize;
    this->textColor = &shared_tb.get()->textColor;

    /* Creating textures for idle, hover and maybe click */
    buttonTextures[IDLE] = idle;
    buttonTextures[HOVER] = hover;
}

TexturedButton::TexturedButton(GLFWwindow* window, Shader shader, std::string pathToImages, float xpos, float ypos, float xscale, float yscale, std::string label) : TexturedButton(window, shader, Texture((pathToImages + "/idle.png").c_str()), Texture((pathToImages + "/hover.png").c_str()), xpos, ypos, xscale, yscale, label) {
}

void TexturedButton::update(glm::mat4 projection) {
    if(this->action.isHovered) {
        texture = buttonTextures[HOVER];
    } else {
        texture = buttonTextures[IDLE];
    }

    Widget::update(projection);
}

TexturedButton* TexturedButton::with_onClick(std::function<void ()> onClick) {
    this->action.onClick = onClick;
    return this;
}

TexturedButton* TexturedButton::with_onRelease(std::function<void ()> onRelease) {
    this->action.onRelease = onRelease;
    return this;
}

TexturedButton* TexturedButton::with_color(glm::vec4 color) {
    this->color = color;
    return this;
}

TexturedButton* TexturedButton::with_textSize(int size) {
    *this->textSize = size;
    return this;
}

TexturedButton* TexturedButton::with_textColor(glm::vec3 color) {
    *this->textColor = color;
    return this;
}