//
// Created by Noah Campagne on 14/07/2024.
//

#include <CampEngine/Graphics/Widgets/Button.h>

#include <codecvt>

Button::Button(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label) : Widget(window, *ResourceManager::standard.getShader("widget"), xpos, ypos, xsize, ysize, 1, 1, Action()) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    auto* tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, xsize, ysize, converter.from_bytes(label));
    std::shared_ptr<TextBox> shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);

    this->textAlign = &shared_tb->textAlign;
    this->textSize = &shared_tb->textSize;
    this->textColor = &shared_tb->textColor;
    this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
    this->outlineThickness = 1;
    this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
    this->hoverModifier = glm::vec4(1.2, 1.2, 1.2, 1.0);
}

void Button::update(glm::mat4 projection) {
    shader.use();
    shader.setFloat("outlineThickness", outlineThickness);
    shader.setVec4("outlineColor", outlineColor);
    shader.setVec2("dimensions", boxSize);
    shader.setBool("hovered", action.isHovered);
    shader.setVec4("hoverModifier", hoverModifier);

    Widget::update(projection);
}

Button* Button::with_onClick(std::function<void()> onClick) {
    this->action.onClick = onClick;
    return this;
}

Button* Button::with_onRelease(std::function<void()> onRelease) {
    this->action.onRelease = onRelease;
    return this;
}

Button* Button::with_color(glm::vec4 color) {
    this->color = color;
    return this;
}

Button* Button::with_theme(Color color) {
    switch(color) {
        case normal:
            this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
            this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
            return this;

        case primary:
            this->color = glm::vec4(0.1, 0.46, 0.82, 1.0);
            this->outlineColor = glm::vec4(0.25, 0.64, 0.96, 1.0);
            return this;

        case success:
            this->color = glm::vec4(0.18, 0.49, 0.2, 1.0);
            this->outlineColor = glm::vec4(0.3, 0.69, 0.31, 1.0);
            return this;

        case warning:
            this->color = glm::vec4(0.93, 0.42, 0.01, 1.0);
            this->outlineColor = glm::vec4(1.0, 0.6, 0.0, 1.0);
            return this;

        case danger:
            this->color = glm::vec4(0.83, 0.18, 0.18, 1.0);
            this->outlineColor = glm::vec4(0.94, 0.33, 0.31, 1.0);
            return this;

        default:
            return this;
    }
}

Button* Button::with_outline(float thickness, glm::vec4 color) {
    this->outlineThickness = thickness;
    this->outlineColor = color;
    return this;
}

Button* Button::with_textAlign(TextPos alignment) {
    *this->textAlign = alignment;
    return this;
}

Button* Button::with_textSize(int size) {
    *this->textSize = size;
    return this;
}

Button* Button::with_textColor(glm::vec3 color) {
    *this->textColor = color;
    return this;
}