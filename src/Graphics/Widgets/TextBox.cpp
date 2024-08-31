//
// Created by Noah Campagne on 14/07/2024.
//

#include <CampEngine/Graphics/Widgets/TextBox.h>

#include <CampEngine/Graphics/Core/Text/TextRenderer.h>

TextBox::TextBox(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float z_depth, float boundX, float boundY, std::wstring text) : Widget(window, shader, Texture(boundX, boundY), xpos, ypos, z_depth, 1, 1, Action()) {
    this->boxSize = glm::vec2(boundX, boundY);
    this->text = text;
    this->textColor = glm::vec4(1.0);
    this->textSize = 20;
    this->textAlign = ALIGN_LEFT;
}

void TextBox::update(glm::mat4 projection) {
    TextRenderer::common->text(text, position.x, position.y, position.z, boxSize.x, boxSize.y, textSize, textColor, textAlign);
}

TextBox* TextBox::with_text(std::wstring text) {
    this->text = text;
    return this;
}

TextBox* TextBox::with_textSize(int size) {
    this->textSize = size;
    return this;
}

TextBox* TextBox::with_textAlign(TextPos alignment) {
    this->textAlign = alignment;
    return this;
}

TextBox* TextBox::with_textColor(glm::vec4 color) {
    this->textColor = color;
    return this;
}
