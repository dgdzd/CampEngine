//
//  physics_object.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_PHYSICS_OBJECT_H
#define CE_PHYSICS_OBJECT_H

#include <glm/glm.hpp>

#include <CampEngine/Physics/PhysicsEnvironment.h>
#include <CampEngine/Physics/Collidable.h>
#include <CampEngine/Utils/logger.h>
#include <CampEngine/Graphics/Scene/Sprite.h>

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
    float angularVelocity;
    float staticFriction;
    float dynamicFriction;
    
    RigidBody2D(PhysicsEnvironment* env, Sprite* parent, float mass, Collidable collision, bool isStatic=false, bool hasGravity=true);
    
    void step();
    void applyForce(glm::vec2 force);
    float getInverseMass();
    float getInverseInertia();
};

#endif
