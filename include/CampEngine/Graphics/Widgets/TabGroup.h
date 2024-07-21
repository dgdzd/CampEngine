//
// Created by Noah Campagne on 20/07/2024.
//

#ifndef CE_TAB_GROUP_H
#define CE_TAB_GROUP_H

#define ALIGN_HORIZONTAL 0;
#define ALIGN_VERTICAL 1;

#include <CampEngine/Graphics/Core/Widget.h>
#include <CampEngine/Graphics/Widgets/Tab.h>

class TabGroup : public Widget {
public:
    int alignment;
    Tab* activeTab;

    TabGroup(GLFWwindow* window, int alignment, float xpos, float ypos);

    virtual void update(glm::mat4 projection);
    TabGroup* with_color(glm::vec4 color);
    TabGroup* with_theme(Color color);
    TabGroup* with_outline(float thickness=0.05, glm::vec4 color=glm::vec4(0.4, 0.4, 0.4, 1.0));
};

#endif
