//
// Created by Noah Campagne on 20/07/2024.
//

#ifndef TAB_BUTTON_H
#define TAB_BUTTON_H

#include <CampEngine/Graphics/Widgets/Button.h>
#include <CampEngine/Graphics/Widgets/Tab.h>

class TabButton : public Button {
public:
    Tab* tab;

    TabButton(GLFWwindow* window, float xpos, float ypos, float xsize, float ysize, std::string label);

    TabButton* with_tab(Tab* tab);
    virtual void onWidgetClick(const Event &e);
};

#endif
