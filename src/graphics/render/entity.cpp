//
//  entity.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#include <graphics/render/entity.h>

Entity::Entity(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, bool hasGravity) : Sprite(window, shader, texture, xpos, ypos, 0, scale), RigidBody2D(PhysicsEnvironment::getInstance(), this, 10, false, hasGravity) {
    collision = Collidable(vertices);
    CollisionsHandler::bodies.push_back(this);
}

Entity::Entity(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 position, float scale, bool hasGravity) : Entity(window, shader, texture, position.x, position.y, scale, hasGravity) {
    
}
