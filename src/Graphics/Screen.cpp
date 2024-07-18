#include <CampEngine/Utils/resource_manager.h>
#include <CampEngine/Graphics/Screen.h>

#include <CampEngine/Graphics/Core/Widget.h>
#include <CampEngine/Graphics/Core/Text/TextRenderer.h>

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