//
// Created by Noah Campagne on 21/07/2024.
//

#ifndef CE_CANVAS_H
#define CE_CANVAS_H

#include <CampEngine/Graphics/Core/Widget.h>

class Canvas : public Widget {
public:
    Canvas(GLFWwindow* window);

    virtual void update(glm::mat4 projection);
};

#endif
