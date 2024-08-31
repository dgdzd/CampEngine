//
// Created by Noah Campagne on 16/08/2024.
//

#include <CampEngine/Graphics/Widgets/Tooltip.h>

#include <CampEngine/Utils/ResourceManager.h>
#include <CampEngine/Graphics/Widgets/TextBox.h>

#include <codecvt>


Tooltip::Tooltip(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label) : ITooltip(window, CE_WIDGET_SHADER, Texture(xsize, ysize), xpos, ypos, 1, 1, nullptr) {
    this->outlineThickness = 1;
    this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
    this->hoverModifier = glm::vec4(1.0);
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, position.z - 0.5f, xsize, ysize, converter.from_bytes(label));
    std::shared_ptr<TextBox> shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);
    savedTextColor = tb->textColor;

    savedOutline = outlineColor;
}

void Tooltip::update(glm::mat4 projection) {
    shader.use();
    shader.setFloat("outlineThickness", outlineThickness);
    shader.setVec4("outlineColor", outlineColor);
    shader.setVec2("dimensions", boxSize);
    shader.setBool("hovered", action.isHovered);
    shader.setVec4("hoverModifier", hoverModifier);

    outlineColor.a = a * savedOutline.a;
    tb->textColor.a = a * savedColor.a;

    ITooltip::update(projection);
}

Tooltip* Tooltip::with_delayIn(float delay) {
    delayIn = delay;
    return this;
}

Tooltip* Tooltip::with_delayOut(float delay) {
    delayOut = delay;
    return this;
}

Tooltip* Tooltip::with_fadeInTime(float time) {
    fadeInTime = time;
    return this;
}

Tooltip* Tooltip::with_fadeOutTime(float time) {
    fadeOutTime = time;
    return this;
}

Tooltip* Tooltip::with_cooldown(float cooldown) {
    this->cooldown = cooldown;
    return this;
}
