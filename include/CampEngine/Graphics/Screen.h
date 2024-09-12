#ifndef CE_SCREEN_H
#define CE_SCREEN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/detail/type_mat.hpp>

#include <CampEngine/Graphics/Core/IWidget.h>

#include <vector>
#include <cstdlib>

#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path

/// This is the base class from which other sample screens class will inherit.
class Screen {
public:
    Screen* lastScreen = nullptr;
    const char* name;
    std::vector<std::shared_ptr<IWidget>> widgets;
    GLFWwindow* window;
    
    Screen(GLFWwindow* window);
    
    virtual void init();
    void render(glm::mat4 projection);
    void addRenderableWidget(IWidget* widget);

private:
    std::vector<std::shared_ptr<IWidget>> sortWidgets();
};

#endif
