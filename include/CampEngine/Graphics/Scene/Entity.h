//
//  entity.h
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#ifndef CE_ENTITY_H
#define CE_ENTITY_H

#include <CampEngine/Graphics/Scene/Sprite.h>
#include <CampEngine/Physics/RigidBody.h>
#include <CampEngine/Physics/CollisionsHandler.h>

class Entity : public Sprite, public RigidBody2D {
public:
    Entity(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, bool isStatic=false, bool hasGravity=true);
    Entity(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, bool isStatic=false, bool hasGravity=true);
    Entity(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 position, float scale, bool isStatic=false, bool hasGravity=true);
};

#endif
