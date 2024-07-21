//
//  particle.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#include <CampEngine/Graphics/Scene/Particle.h>

#include <CampEngine/Graphics/Level.h>


Particle::Particle(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, long lifetime) : Sprite(window, shader, texture, xpos, ypos, 0, xscale, yscale, 0, 0, 0) {
    this->lifetime = lifetime;
}

Particle::Particle(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, long lifetime) : Particle(window, shader, texture, xpos, ypos, scale, scale, lifetime) {
    
}

Particle::Particle(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, long lifetime) : Particle(window, shader, texture, xpos, ypos, 1, lifetime) {
    
}

Particle::Particle(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 pos, float xscale, float yscale, long lifetime) : Particle(window, shader, texture, pos.x, pos.y, xscale, yscale, lifetime) {
    
}

Particle::Particle(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 pos, float scale, long lifetime) : Particle(window, shader, texture, pos, scale, scale, lifetime) {
    
}

Particle::Particle(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 pos, long lifetime) : Particle(window, shader, texture, pos, 1, lifetime) {
    
}

void Particle::update(Camera camera, glm::mat4 projection) {
    if(lifetime <= 0) {
        Level::active->removeObject(index);
        return;
    }
    lifetime--;
    
    Sprite::update(camera, projection);
}
