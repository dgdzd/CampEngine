#include  <render/widget.h>

/*---- Forward Declaration ----*/
class Game;
class Renderable;
/*-----------------------------*/

Widget::Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action) : Widget(window, shader, xpos, ypos, texture.width, texture.height, xscale, yscale, action) {
    
}

Widget::Widget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xsize, float ysize, float xscale, float yscale, Action action) : Renderable(window, shader, Texture(xsize, ysize), xpos, ypos, xscale, yscale) {
    this->position = glm::vec2(xpos, ypos);
    this->boxSize = glm::vec2(xsize * xscale, ysize * yscale);
    this->action = action;
    this->id = 100000 + rand() % (1000000 - 100000);
    this->selected = false;
    
    // Add listeners
    
    ADD_LISTENER(MouseClickEvent(), Widget::onMouseClick, this);
    ADD_LISTENER(MouseReleaseEvent(), Widget::onMouseRelease, this);
    ADD_LISTENER(MouseMoveEvent(), Widget::onMouseMove, this);
    ADD_LISTENER(KeyPressEvent(), Widget::onKeyPress, this);
    ADD_LISTENER(CharacterInputEvent(), Widget::onCharInput, this);
}

void Widget::update(glm::mat4 projection) {
    this->render(projection);
    
    for(int w = 0; w < children.size(); w++) {
        children.at(w).get()->update(projection);
        //std::cout << "CHILDRENS\n";
    }
}

void Widget::onMouseClick(const Event &e) {
    auto event = e.as<MouseClickEvent>();
    selected = false;
    
    if(this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        this->action.isClicked = true;
        selected = true;
        this->action.onClick();
    } else {
        this->action.isClicked = false;
    }
}

void Widget::onMouseRelease(const Event &e) {
    auto event = e.as<MouseReleaseEvent>();
    if(this->action.isClicked && this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
        this->action.isClicked = false;
        this->action.onRelease();
    }
    this->action.isClicked = false;
}

void Widget::onMouseMove(const Event &e) {
    auto event = e.as<MouseMoveEvent>();
    std::function<void()> quitHoveringfunc = [this]() {
        if(this->action.isHovered) {
            this->action.onQuitHovering();
        }
        this->action.isHovered = false;
    };
    
    if(position.x - boxSize.x/2 <= event.mouseX && event.mouseX <= position.x + boxSize.x/2) {
        if((Game::activeGame->frame.height - position.y) - boxSize.y/2 <= event.mouseY && event.mouseY <= (Game::activeGame->frame.height - position.y) + boxSize.y/2) {
            this->action.isHovered = true;
            this->action.onStartHovering();
        } else {
            quitHoveringfunc();
        }
    } else {
        quitHoveringfunc();
    }
}

void Widget::onKeyPress(const Event &e) {
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
                    
                case GLFW_KEY_ENTER:
                    self->selected = false;
                    break;
                    
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

void Widget::onCharInput(const Event &e) {
    auto event = e.as<CharacterInputEvent>();
    this->action.onCharType();
    
    if(instanceof<TextInput>(this)) {
        TextInput* self = dynamic_cast<TextInput*>(this);
        if(self->selected) {
            self->text += (wchar_t)event.codepoint;
            self->cursorPos++;
            self->lastTypeTime = glfwGetTime();
        }
    }
}

TextBox::TextBox(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float boundX, float boundY, std::wstring text) : Widget(window, shader, texture, xpos, ypos, 1, 1, Action()) {
    this->boxSize = glm::vec2(boundX, boundY);
    this->text = text;
    this->textColor = glm::vec3(1.0);
    this->textSize = 20;
    this->textAlign = ALIGN_LEFT;
}

void TextBox::update(glm::mat4 projection) {
    TextRenderer::common->text(text, position.x, position.y, boxSize.x, boxSize.y, textSize, textColor, textAlign);
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

TextBox* TextBox::with_textColor(glm::vec3 color) {
    this->textColor = color;
    return this;
}

Button::Button(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label) : Widget(window, *ResourceManager::standard.getShader("widget"), Texture(xsize, ysize), xpos, ypos, 1, 1, Action()) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    TextBox* tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, xsize, ysize, converter.from_bytes(label));
    std::shared_ptr shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);
    
    this->textAlign = &shared_tb.get()->textAlign;
    this->textSize = &shared_tb.get()->textSize;
    this->textColor = &shared_tb.get()->textColor;
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
