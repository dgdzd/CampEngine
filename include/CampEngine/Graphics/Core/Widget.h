#ifndef CE_WIDGET_H
#define CE_WIDGET_H

#include <CampEngine/Graphics/Core/IWidget.h>

class Widget : public IWidget {
public:
    Widget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action, AnchorPoint anchor=CENTER);
    Widget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xsize, float ysize, float xscale, float yscale, Action action, AnchorPoint anchor=CENTER);
    Widget(GLFWwindow* window, float xpos, float ypos, AnchorPoint anchor=CENTER);
    
    virtual void update(glm::mat4 projection);
    virtual void onMouseClick(const Event &e);
    virtual void onMouseRelease(const Event &e);
    virtual void onMouseMove(const Event &e);
    virtual void onStartHovering(const Event &e);
    virtual void onStopHovering(const Event &e);
    virtual void onKeyPress(const Event &e);
    virtual void onCharInput(const Event &e);
};

#endif
