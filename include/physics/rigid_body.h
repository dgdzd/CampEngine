//
//  physics_object.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_PHYSICS_OBJECT_H
#define CE_PHYSICS_OBJECT_H

#include <glm/glm.hpp>

#include <physics/physics_environment.h>
#include <physics/collidable.h>
#include <utils/logger.h>
#include <graphics/render/sprite.h>

class Sprite;

class RigidBody2D {
private:
    float calculateRotationalInertia();
    glm::vec2 force;
    
public:
    PhysicsEnvironment* env;
    Sprite* parent;
    Collidable collision;
    float mass;
    float restitution;
    float rotationalInertia;
    bool isStatic;
    bool hasGravity;
    glm::vec2 linearVelocity;
    glm::vec2 rotationalVelocity;
    
    RigidBody2D(PhysicsEnvironment* env, Sprite* parent, float mass, bool isStatic=false, bool hasGravity=true);
    
    void step();
    void applyForce(glm::vec2 force);
    float getInverseMass();
};

#endif
