//
// Created by Noah Campagne on 20/07/2024.
//

#include <CampEngine/Game/Events/Categories/WidgetEvents.h>
#include <CampEngine/Graphics/Widgets/TabButton.h>
#include <CampEngine/Graphics/Widgets/TabGroup.h>

TabButton::TabButton(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label) : Button(window, xpos, ypos, xsize, ysize, label) {
    tab = nullptr;
}

void TabButton::onWidgetClick(const Event &e) {
    auto event = e.as<WidgetClickEvent>();
    if(event.widget == this) {
        tab->group->activeTab = tab;
    }
}

TabButton* TabButton::with_tab(Tab* tab) {
    this->tab = tab;
    return this;
}
