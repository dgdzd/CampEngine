#include <CampEngine/Graphics/Screen.h>

#include <CampEngine/Graphics/Core/Text/TextRenderer.h>
#include <CampEngine/Utils/ResourceManager.h>
#include <CampEngine/Utils/SortUtils.h>

ResourceManager rm;

Screen::Screen(GLFWwindow* window) {
    this->window = window;
    this->shouldSort = true;
    init();
}

void Screen::addRenderableWidget(IWidget* widget) {
    std::shared_ptr w = std::shared_ptr<IWidget>(widget);
    this->widgets.push_back(w);
}

void Screen::init() {
    // Interface function which will be modified by child classes
}

void Screen::render(glm::mat4 projection) {
    if(this->shouldSort) sortWidgets();
    for(const auto& widget : sortedWidgets) {
        widget->update(projection);
    }
}

void Screen::sortWidgets() {
    sortedWidgets.clear();
    for(const auto& widget : widgets) {
        sortedWidgets.push_back(widget);
        getAllChildren(sortedWidgets, widget);
    }
    std::sort(sortedWidgets.begin(), sortedWidgets.end(), [](std::shared_ptr<IWidget> t1, std::shared_ptr<IWidget> t2) { return t1->position.z > t2->position.z; });
}

void Screen::getAllChildren(std::vector<std::shared_ptr<IWidget>>& list, std::shared_ptr<IWidget> widget) {
    list.push_back(widget);
    for(const auto& child : widget->children) {
        getAllChildren(list, child);
    }
    shouldSort = false;
}
