#include <render/widget.h>

class Game;

Widget::Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action) : Renderable(window, shader, texture, xpos, ypos, xscale, yscale) {
    this->position = glm::vec2(xpos, ypos);
    this->boxSize = glm::vec2(texture.width * xscale, texture.height * yscale);
    this->action = action;
    this->id = 100000 + rand() % (1000000 - 100000);
}

void Widget::update(glm::mat4 projection) {
    
    
    this->render(projection);
    
    for(int w = 0; w < children.size(); w++) {
        children.at(w).get()->update(projection);
        //std::cout << "CHILDRENS\n";
    }
}

void Widget::receiveEvent(Event* e) {
    if(instanceof<CursorMovedEvent>(e)) {
        CursorMovedEvent event = *dynamic_cast<CursorMovedEvent*>(e);
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
    
    else if(instanceof<MouseClickEvent>(e)) {
        MouseClickEvent event = *dynamic_cast<MouseClickEvent*>(e);
        
        if(this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
            this->action.isClicked = true;
            this->action.onClick();
        } else {
            this->action.isClicked = false;
        }
    }
    
    else if(instanceof<MouseReleaseEvent>(e)) {
        MouseReleaseEvent event = *dynamic_cast<MouseReleaseEvent*>(e);
        
        if(this->action.isClicked && this->action.isHovered && event.mouseButton == GLFW_MOUSE_BUTTON_LEFT) {
            this->action.isClicked = false;
            this->action.onRelease();
        }
        this->action.isClicked = false;
    }
}

TextBox::TextBox(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float boundX, float boundY, std::wstring text, int textSize, glm::vec3 textColor) : Widget(window, shader, texture, xpos, ypos, 1, 1, Action()) {
    this->boxSize = glm::vec2(boundX, boundY);
    this->text = text;
    this->textColor = textColor;
    this->textSize = textSize;
}

void TextBox::update(glm::mat4 projection) {
    TextRenderer::common->text(text, position.x, position.y, boxSize.x, boxSize.y, textSize, textColor, ALIGN_CENTER);
}

Button::Button(GLFWwindow* window, Shader shader, Texture idle, Texture hover, float xpos, float ypos, float xscale, float yscale, std::string label, std::function<void()> onClick, std::function<void()> onRelease) : Widget(window, shader, idle, xpos, ypos, xscale, yscale, Action([]() {}, onClick, []() {}, []() {}, []() {}, onRelease)) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    TextBox* tb = new TextBox(window, shader, texture, xpos - boxSize.x/2, ypos, texture.width * xscale, texture.height * yscale, converter.from_bytes(label), 25, glm::vec3(1.0f));
    std::shared_ptr shared_tb = std::shared_ptr<TextBox>(tb);
    children.push_back(shared_tb);
    
    this->textSize = &shared_tb.get()->textSize;
    this->textColor = &shared_tb.get()->textColor;
    
    /* Creating textures for idle, hover and maybe click */
    buttonTextures[IDLE] = idle;
    buttonTextures[HOVER] = hover;
}

Button::Button(GLFWwindow* window, Shader shader, std::string pathToImages, float xpos, float ypos, float xscale, float yscale, std::string label, std::function<void()> onClick, std::function<void()> onRelease) : Button(window, shader, Texture((pathToImages + "/idle.png").c_str()), Texture((pathToImages + "/hover.png").c_str()), xpos, ypos, xscale, yscale, label, onClick, onRelease) {
}

void Button::update(glm::mat4 projection) {
    if(this->action.isHovered) {
        texture = buttonTextures[HOVER];
    } else {
        texture = buttonTextures[IDLE];
    }
    
    Widget::update(projection);
}
