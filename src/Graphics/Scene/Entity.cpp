//
//  entity.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#include <CampEngine/Graphics/Scene/Entity.h>

#include <CampEngine/Physics/CollisionsHandler.h>

Entity::Entity(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, bool isStatic, bool hasGravity) : Sprite(window, shader, texture, xpos, ypos, 0, xscale, yscale, 0, 0, 0), RigidBody2D(PhysicsEnvironment::getInstance(), this, 1, Collidable(vertices), isStatic, hasGravity) {
    CollisionsHandler::bodies.push_back(this);
}

Entity::Entity(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, bool isStatic, bool hasGravity) : Entity(window, shader, texture, xpos, ypos, scale, scale, isStatic, hasGravity) {
    
}

Entity::Entity(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 position, float scale, bool isStatic, bool hasGravity) : Entity(window, shader, texture, position.x, position.y, scale, isStatic, hasGravity) {
    
}
