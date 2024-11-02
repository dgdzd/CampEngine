//
// Created by Noah Campagne on 02/10/2024.
//

#include <CampEngine/Graphics/Widgets/Dropdown.h>
#include <CampEngine/Graphics/Widgets/TextBox.h>
#include <CampEngine/Graphics/Widgets/Internal/Image.h>

#include <codecvt>

Dropdown::Dropdown(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string initialValue) : Dropdown(window, xpos, ypos, xsize, ysize, initialValue, {}) {
}

Dropdown::Dropdown(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string initialValue, std::vector<std::string> values) : Widget(window, CE_WIDGET_SHADER, xpos, ypos, 127.0f, xsize, ysize, 1, 1, Action()) {
    this->selectedValue = initialValue;
    this->values = values;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    auto* tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, position.z - 0.1f, xsize, ysize, converter.from_bytes(initialValue));
    std::shared_ptr<TextBox> shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);

    arrow = new Image(window, *ResourceManager::standard.getTexture("dropdown_arrow"), xpos+xsize/2-8, ypos, 1, 1);
    std::shared_ptr<Image> shared_img = std::shared_ptr<Image>(arrow);
    children.push_back(shared_img);

    this->textAlign = &shared_tb->textAlign;
    this->textSize = &shared_tb->textSize;
    this->textColor = &shared_tb->textColor;
    this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
    this->outlineThickness = 1;
    this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
    this->hoverModifier = glm::vec4(1.2, 1.2, 1.2, 1.0);
}

void Dropdown::update(glm::mat4 projection) {
    if(selected) {
        arrow->rotation.z = 180;
    } else {
        arrow->rotation.z = 0;
    }

    shader.use();
    shader.setFloat("outlineThickness", outlineThickness);
    shader.setVec4("outlineColor", outlineColor);
    shader.setVec2("dimensions", boxSize);
    shader.setBool("hovered", action.isHovered);
    shader.setVec4("hoverModifier", hoverModifier);

    Widget::update(projection);
}

void Dropdown::addValues(std::vector<std::string> values) {
    this->values.insert(this->values.end(), values.begin(), values.end());
}

Dropdown* Dropdown::with_onClick(std::function<void(Widget* self)> onClick) {
    this->action.onClick = onClick;
    return this;
}

Dropdown* Dropdown::with_onRelease(std::function<void(Widget* self)> onRelease) {
    this->action.onRelease = onRelease;
    return this;
}

Dropdown* Dropdown::with_color(glm::vec4 color) {
    this->color = color;
    return this;
}

Dropdown* Dropdown::with_theme(Color color) {
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

Dropdown* Dropdown::with_outline(float thickness, glm::vec4 color) {
    this->outlineColor = color;
    this->outlineThickness = thickness;
    return this;
}

Dropdown* Dropdown::with_textAlign(TextPos alignment) {
    *this->textAlign = alignment;
    return this;
}

Dropdown* Dropdown::with_textSize(int size) {
    *this->textSize = size;
    return this;
}

Dropdown* Dropdown::with_textColor(glm::vec4 color) {
    *this->textColor = color;
    return this;
}

Dropdown* Dropdown::with_hoverColorModifier(glm::vec4 color) {
    this->hoverModifier = color;
    return this;
}
