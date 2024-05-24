//
//  actor.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 01/05/2024.
//

#include <render/actor.h>

Actor::Actor(GLFWwindow* window, float xpos, float ypos) : Renderable(window, Shader(), Texture(), xpos, ypos, 0, 0) {
    
}

void Actor::update(Camera camera, glm::mat4 projection) {
    this->update();
}

void Actor::update() {
    
}
