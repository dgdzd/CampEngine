//
// Created by Noah Campagne on 20/07/2024.
//

#ifndef CE_TAB_H
#define CE_TAB_H

#include <CampEngine/Graphics/Core/Widget.h>

class TabGroup;

class Tab : public Widget {
public:
    TabGroup* group;

    Tab(GLFWwindow* window);

    virtual void update(glm::mat4 projection);
};

#endif
