#ifndef CE_SCREEN_H
#define CE_SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <render/renderable.h>
#include <render/widget.h>
#include <utils/resource_manager.h>
#include <utils/gui_helper.h>
#include <game/game.h>

#include <vector>
#include <cstdlib>

#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path

class GuiHelper;
class Widget;

/// This is the base class from which other sample screens class will inherit.
class Screen {
public:
    Screen* lastScreen = nullptr;
    const char* name;
    std::vector<std::shared_ptr<Widget>> widgets;
    GLFWwindow* window;
    
    Screen(GLFWwindow* window);
    
    virtual void init();
    void render(glm::mat4 projection);
    void addRenderableWidget(Widget* widget);
};

class TestScreen : public Screen {
public:
    TestScreen(GLFWwindow* window);
    
    virtual void init();
};

#endif /* screen_h */
