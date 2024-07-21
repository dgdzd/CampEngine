//
// Created by Noah Campagne on 19/07/2024.
//

#include <CampEngine/Graphics/Core/IWidget.h>

IWidget::IWidget(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, Action action) : IWidget(window, shader, xpos, ypos, texture.width, texture.height, xscale, yscale, action) {

}

IWidget::IWidget(GLFWwindow* window, Shader shader, float xpos, float ypos, float xsize, float ysize, float xscale, float yscale, Action action) : Renderable(window, shader, Texture(xsize, ysize), xpos, ypos, xscale, yscale) {

}

IWidget::IWidget(GLFWwindow* window, float xpos, float ypos) : IWidget(window, Shader(), xpos, ypos, 0, 0, 0, 0, Action())  {

}


void IWidget::update(glm::mat4 projection) {

}

void IWidget::onMouseClick(const Event &e) {

}

void IWidget::onMouseRelease(const Event &e) {

}

void IWidget::onMouseMove(const Event &e) {

}

void IWidget::onKeyPress(const Event &e) {

}

void IWidget::onCharInput(const Event &e) {

}

void IWidget::onWidgetClick(const Event &e) {

}

void IWidget::onWidgetRelease(const Event &e) {

}
