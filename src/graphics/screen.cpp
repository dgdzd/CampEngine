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
    
    GuiHelper gh(window, glm::vec2(0.0, 1070.0));
    gh.setPadding(0);
    gh.setMargin(0);
    
    textFPS = gh.createTextBox(L"FPS: ", 0, 20);
    textDeltaTime = gh.createTextBox(L"DeltaTime: ", 0, 20);
    
    /* Assign objects to shared pointers, and add them to the widget list */
    std::shared_ptr<TextBox> _textFPS = std::shared_ptr<TextBox>(textFPS);
    std::shared_ptr<TextBox> _textDeltaTime = std::shared_ptr<TextBox>(textDeltaTime);
    
    widgets.push_back(_textFPS);
    widgets.push_back(_textDeltaTime);
}

TestScreen::TestScreen(GLFWwindow* window) : Screen(window) {
    this->init();
} 

void TestScreen::init() {
    Screen::init();
    
    /* Initialize GUI Helper */
    GuiHelper gh(window, glm::vec2(0.0, 400.0));
    gh.setPadding(0);
    gh.setMargin(0);
    
    /* Create widgets */
    auto button = gh.createButton("unlitShader.fs (open in Visual Studio Code)", 20)
    ->with_onRelease([]() {
        system("open -a /Applications/Visual\\ Studio\\ Code.app /Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/shaders/unlitShader.fs -F");
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(primary);
    
    auto button1 = gh.createButton("Quit", 20)
    ->with_onRelease([]() {
        Game::activeGame->quit();
    })
    ->with_textAlign(ALIGN_LEFT)
    ->with_theme(danger);
    
    auto input = gh.createTextInput(200, 25)
    ->with_floatingLabel(L"Type anything");
    
    
    
    /* Assign objects to shared pointers, and add them to the widget list */
    std::shared_ptr<Button> _button = std::shared_ptr<Button>(button);
    std::shared_ptr<Button> _button1 = std::shared_ptr<Button>(button1);
    std::shared_ptr<TextInput> _input = std::shared_ptr<TextInput>(input);
    
    widgets.push_back(_button);
    widgets.push_back(_button1);
    widgets.push_back(_input);
}
