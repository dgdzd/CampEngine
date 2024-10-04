//
// Created by Noah Campagne on 25/09/2024.
//

#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <CampEngine/Graphics/Widgets/Internal/Rectangle.h>
#include <CampEngine/Graphics/Core/RenderObject.h>

class GL_Renderer {
public:
    static std::list<RenderObject> objs;

    static void pushRectangle(Rectangle rect);
    static void pushRectangle(float xpos, float ypos, float xsize, float ysize, glm::vec4 color, float outlineThickness, glm::vec4 outlineColor);

};

#endif
