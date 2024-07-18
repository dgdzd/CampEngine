//
//  particle.h
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#ifndef CE_PARTICLE_H
#define CE_PARTICLE_H

#include <CampEngine/Graphics/Scene/Sprite.h>
#include <CampEngine/Graphics/Level.h>

class Particle : public Sprite {
public:
    long lifetime;
    
    Particle(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, long lifetime);
    Particle(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, long lifetime);
    Particle(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, long lifetime);
    Particle(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 pos, float xscale, float yscale, long lifetime);
    Particle(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 pos, float scale, long lifetime);
    Particle(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 pos, long lifetime);
    
    virtual void update(Camera camera, glm::mat4 projection);
};

#endif
