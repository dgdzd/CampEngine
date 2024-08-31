//
//  sprite.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#include <CampEngine/Graphics/Scene/Sprite.h>

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float zpos, float xscale, float yscale, float xrot, float yrot, float zrot) : Renderable(window, shader, texture, xpos, ypos, zpos, xscale, yscale, xrot, yrot, zrot), rotation(Renderable::rotation.z) {
    
}

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float zpos, float scale) : Renderable(window, shader, texture, xpos, ypos, zpos, scale), rotation(Renderable::rotation.z) {
    
}

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec3 position, float scale) : Sprite(window, shader, texture, position.x, position.y, position.z, scale) {
    
}
