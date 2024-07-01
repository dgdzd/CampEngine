#include <graphics/screen.h>

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

DebugScreen::DebugScreen(GLFWwindow* window) : Screen(window) {
    this->init();
}

void DebugScreen::init() {
    Screen::init();
    
    GuiHelper gh(window, glm::vec2(0.0, 1070.0), this);
    gh.setPadding(0);
    gh.setMargin(0);
    
    textFPS = gh.createTextBox(L"FPS: ", 0, 20);
    textDeltaTime = gh.createTextBox(L"DeltaTime: ", 0, 20);
}

TestScreen::TestScreen(GLFWwindow* window) : Screen(window) {
    this->init();
} 

void TestScreen::init() {
    Screen::init();
    
    /* Initialize GUI Helper */
    GuiHelper gh(window, glm::vec2(0.0, 400.0), this);
    gh.setPadding(0);
    gh.setMargin(0);
    
    /* Create widgets */
    gh.createButton("unlitShader.fs (open in Visual Studio Code)", 20)
    ->with_onRelease([]() {
        system("open -a /Applications/Visual\\ Studio\\ Code.app /Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/shaders/unlitShader.fs -F");
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(primary);
    
    gh.createButton("Quit", 20)
    ->with_onRelease([]() {
        Game::activeGame->quit();
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(danger);
    
    gh.createTextInput(200, 25)
    ->with_floatingLabel(L"Type anything");
}
