#include <CampEngine/Graphics/Screen.h>

#include <CampEngine/Graphics/Core/Text/TextRenderer.h>
#include <CampEngine/Utils/ResourceManager.h>
#include <CampEngine/Utils/SortUtils.h>

ResourceManager rm;

Screen::Screen(GLFWwindow* window) {
    this->window = window;
    init();
}

void Screen::addRenderableWidget(IWidget* widget) {
    std::shared_ptr<IWidget> w = std::shared_ptr<IWidget>(widget);
    this->widgets.push_back(w);
}

void Screen::init() {
    // Interface function which will be modified by child classes
}

void Screen::render(glm::mat4 projection) {
    for(const auto& widget : widgets) {
        widget->update(projection);
    }
}

std::vector<std::shared_ptr<IWidget>> Screen::sortWidgets() {
    auto sorted = std::vector<std::shared_ptr<IWidget>>();
    Sorter<std::shared_ptr<IWidget>>::quickSort(widgets, [](auto t1, auto t2) { return t1->position.z < t2->position.z; });
}
