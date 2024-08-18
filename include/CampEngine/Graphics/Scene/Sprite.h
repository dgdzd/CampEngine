//
//  sprite.h
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#ifndef CE_SPRITE_H
#define CE_SPRITE_H

#include <CampEngine/Graphics/Core/Renderable.h>

class Sprite : public Renderable {
public:
    float& rotation;
    Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float zpos, float xscale, float yscale, float xrot, float yrot, float zrot);
    Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float zpos, float scale);
    Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec3 position, float scale);
    Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec3 position, glm::vec2 scale, glm::vec3 rotation);
};

#endif
