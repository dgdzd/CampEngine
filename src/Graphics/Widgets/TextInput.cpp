//
// Created by Noah Campagne on 14/07/2024.
//

#include <CampEngine/Graphics/Widgets/TextInput.h>

TextInput::TextInput(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize) : Widget(window, *ResourceManager::standard.getShader("widget"), Texture(xsize, ysize), xpos, ypos, 1, 1, Action()) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    TextBox* tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, xsize, ysize, converter.from_bytes(""));
    std::shared_ptr shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);

    this->input = &shared_tb.get()->text;
    this->textAlign = &shared_tb.get()->textAlign;
    this->textSize = &shared_tb.get()->textSize;
    this->textColor = &shared_tb.get()->textColor;

    this->color = glm::vec4(0.3, 0.3, 0.3, 1.0);
    this->outlineThickness = 1;
    this->outlineColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
    this->hoverModifier = glm::vec4(1.2, 1.2, 1.2, 1.0);
    this->baseTextColor = *textColor;
    this->labelColor = glm::vec3(0.5);
    this->cursorPos = 0;

    this->lastTypeTime = 0;
}

void TextInput::update(glm::mat4 projection) {
    shader.use();
    shader.setFloat("outlineThickness", selected ? outlineThickness+1 : outlineThickness);
    shader.setVec4("outlineColor", selected ? glm::vec4(1.0) : outlineColor);
    shader.setVec2("dimensions", boxSize);
    shader.setBool("hovered", action.isHovered);
    shader.setVec4("hoverModifier", hoverModifier);

    Widget::update(projection);

    if(selected) {
        *input = text;
        *textColor = baseTextColor;

        int cursor = TextRenderer::common->textLength(text, 0, cursorPos);
        float scale = *textSize/48.0f;
        if(sin((glfwGetTime()-lastTypeTime)*6) > -0.5f) {
            TextRenderer::common->text(L"|", position.x-boxSize.x/2+cursor*scale-1, position.y, boxSize.x, boxSize.y, *textSize, glm::vec3(1.0));
        }
    } else {
        if(text.empty()) {
            *input = floatingLabel;
            *textColor = labelColor;
        } else {
            *input = text;
            *textColor = baseTextColor;
        }
    }
}

TextInput* TextInput::with_onClick(std::function<void ()> onClick) {
    this->action.onClick = onClick;
    return this;
}

TextInput* TextInput::with_onRelease(std::function<void ()> onRelease) {
    this->action.onRelease = onRelease;
    return this;
}

TextInput* TextInput::with_onCharType(std::function<void ()> onCharType) {
    this->action.onCharType = onCharType;
    return this;
}

TextInput* TextInput::with_color(glm::vec4 color) {
    this->color = color;
    return this;
}

TextInput* TextInput::with_text(std::wstring text) {
    this->text = text;
    return this;
}

TextInput* TextInput::with_textSize(int size) {
    *this->textSize = size;
    return this;
}

TextInput* TextInput::with_textColor(glm::vec3 color) {
    *this->textColor = color;
    return this;
}

TextInput* TextInput::with_floatingLabel(std::wstring label) {
    this->floatingLabel = label;
    return this;
}

TextInput* TextInput::with_floatingLabelColor(glm::vec3 color) {
    this->labelColor = color;
    return this;
}

void TextInput::onKeyPress(const Event &e) {
    Widget::onKeyPress(e);

    auto event = e.as<KeyPressEvent>();

    if(instanceof<TextInput>(this)) {
        TextInput* self = dynamic_cast<TextInput*>(this);

        if(self->selected) {
            switch(event.key) {
                case GLFW_KEY_BACKSPACE:
                    if(self->cursorPos > 0) {
                        self->text.erase(self->text.begin() + self->cursorPos-1);
                        self->cursorPos--;
                    }
                break;

                case GLFW_KEY_ENTER: {
                    self->selected = false;
                    WidgetSubmitEvent event_;
                    event_.widget = self;
                    event_.input = self->text;
                    SEND_EVENT(event_);
                    break;
                }

                case GLFW_KEY_ESCAPE:
                    self->selected = false;
                break;

                case GLFW_KEY_LEFT:
                    if(self->cursorPos > 0) self->cursorPos--;
                break;

                case GLFW_KEY_RIGHT:
                    if(self->cursorPos < self->text.size()) self->cursorPos++;
                break;

                default:
                    break;
            }
        }
    }
}

void TextInput::onCharInput(const Event &e) {
    Widget::onCharInput(e);

    auto event = e.as<CharacterInputEvent>();

    if(instanceof<TextInput>(this)) {
        TextInput* self = dynamic_cast<TextInput*>(this);
        if(self->selected) {
            self->text += (wchar_t)event.codepoint;
            self->cursorPos++;
            self->lastTypeTime = glfwGetTime();
        }
    }
}

