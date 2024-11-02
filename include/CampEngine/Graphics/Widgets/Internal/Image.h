//
// Created by Noah Campagne on 04/10/2024.
//

#ifndef CE_IMAGE_H
#define CE_IMAGE_H

#include <CampEngine/Graphics/Core/Widget.h>

class Image : public Widget {
public:
    Image(GLFWwindow* window, Texture texture, float xpos, float ypos, float xscale, float yscale);

    virtual void update(glm::mat4 projection);
};

#endif
