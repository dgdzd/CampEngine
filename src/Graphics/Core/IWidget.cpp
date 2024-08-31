//
// Created by Noah Campagne on 19/07/2024.
//

#include <CampEngine/Graphics/Core/IWidget.h>

#include <CampEngine/Graphics/Widgets/ITooltip.h>

IWidget::IWidget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float z_depth, float xscale, float yscale, Action action, AnchorPoint anchor) : IWidget(window, shader, xpos, ypos, z_depth, texture.width, texture.height, xscale, yscale, action, anchor) {

}

IWidget::IWidget(GLFWwindow* window, Shader shader, float xpos, float ypos, float z_depth, float xsize, float ysize, float xscale, float yscale, Action action, AnchorPoint anchor) : Renderable(window, shader, Texture(xsize, ysize), xpos, ypos, z_depth, xscale, yscale, anchor) {

}

IWidget::IWidget(GLFWwindow* window, float xpos, float ypos, float z_depth, AnchorPoint anchor) : IWidget(window, Shader(), xpos, ypos, z_depth, 0, 0, 0, 0, Action(), anchor)  {

}


void IWidget::update(glm::mat4 projection) {

}

void IWidget::onMouseClick(const Event &e) {

}

void IWidget::onMouseRelease(const Event &e) {

}

void IWidget::onMouseMove(const Event &e) {

}

void IWidget::onStartHovering(const Event &e) {

}

void IWidget::onStopHovering(const Event &e) {

}

void IWidget::onKeyPress(const Event &e) {

}

void IWidget::onCharInput(const Event &e) {

}

void IWidget::onWidgetClick(const Event &e) {

}

void IWidget::onWidgetRelease(const Event &e) {

}

void IWidget::addTooltip(ITooltip* tooltip) {
    std::shared_ptr<ITooltip> ptr = std::shared_ptr<ITooltip>(tooltip);
    tooltip->parent = this;
    children.push_back(ptr);
}
