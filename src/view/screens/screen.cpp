#include <view/screens/screen.h>

ResourceManager rm;

class Game;

Screen::Screen(GLFWwindow* window) {
    this->window = window;
    init();
}

void Screen::addRenderableWidget(Widget* widget) {
    std::shared_ptr<Widget> w = std::shared_ptr<Widget>(widget);
    this->widgets.push_back(w);
}

void Screen::init() {
    // Interface function which will be modified by child classes
}

void Screen::render(glm::mat4 projection) {
    for(int w = 0; w < widgets.size(); w++) {
        widgets.at(w).get()->update(projection);
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
    
    Button* button = new Button(window, shader, idle, hover, 400, 100, 3, 3, "Quit", []() {}, []() {
        Game::activeGame->quit();
    });
    std::shared_ptr<Button> ptr = std::shared_ptr<Button>(button);
    widgets.push_back(ptr);
}
