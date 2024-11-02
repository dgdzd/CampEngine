//
// Created by Noah Campagne on 04/10/2024.
//

#include <CampEngine/Graphics/Widgets/Internal/Image.h>
#include <CampEngine/Utils/ResourceManager.h>

Image::Image(GLFWwindow* window, Texture texture, float xpos, float ypos, float xscale, float yscale) : Widget(window, CE_UNLIT_SHADER, texture, xpos, ypos, 127.0f, xscale, yscale, Action()) {

}

void Image::update(glm::mat4 projection) {
    Widget::update(projection);
}

