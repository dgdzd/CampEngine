//
// Created by Noah Campagne on 20/07/2024.
//

#include <CampEngine/Graphics/Widgets/Tab.h>
#include <CampEngine/Graphics/Widgets/TabGroup.h>

Tab::Tab(GLFWwindow* window) : Widget(window, 0, 0) {
    group = nullptr;
}

void Tab::update(glm::mat4 projection) {
    for(const auto& child : children) {
        child->update(projection);
    }
}

