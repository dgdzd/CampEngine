//
// Created by Noah Campagne on 20/07/2024.
//

#include <CampEngine/Graphics/Widgets/TabGroup.h>

TabGroup::TabGroup(GLFWwindow* window, int alignment, float xpos, float ypos) : Widget(window, xpos, ypos, 128) {
    this->alignment = alignment;
}

void TabGroup::update(glm::mat4 projection) {
    activeTab->update(projection);
}

