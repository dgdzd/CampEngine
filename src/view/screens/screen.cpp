#include <view/screens/screen.h>

ResourceManager rm;

class Game;

Screen::Screen(GLFWwindow* window) {
    this->window = window;
    init();
}

void Screen::addRenderableWidget(Widget* widget) {
    auto* w = new 
    this->widgets.push_back(std::shared_ptr<Widget>(widget));
}

void Screen::init() {
    // Interface function which will be modified by child classes
}

void Screen::render(glm::mat4 projection) {
    for(int w = 0; w < widgets.size(); w++) {
        widgets.at(w)->update(projection);
    }
}


TestScreen::TestScreen(GLFWwindow* window) : Screen(window) {
    this->init();
}

void TestScreen::init() {
    Texture idle = rm.getTexture("buttonIdle");
    Texture hover = rm.getTexture("buttonHover");
    Shader shader = rm.getShader("basic");
    Screen::init();
    
    Button button(window, shader, idle, hover, 400, 300, 3, 3, "Button", []() {
        Game::activeGame->quit();
    });
    addRenderableWidget(&button);
}
