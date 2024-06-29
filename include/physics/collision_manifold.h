//
//  collision_manifold.h
//  CampEngine++
//
//  Created by Noah Campagne on 29/06/2024.
//

#ifndef CE_COLLISION_MANIFOLD_H
#define CE_COLLISION_MANIFOLD_H

#include <glm/glm.hpp>

#include <physics/rigid_body.h>

struct CollisionManifold {
    RigidBody2D* bodyA;
    RigidBody2D* bodyB;
    
    glm::vec2 normal;
    float depth;
    
    glm::vec2 contact1;
    glm::vec2 contact2;
    int contactCount;
    
    CollisionManifold(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2 normal, float depth, glm::vec2 contact1, glm::vec2 contact2, int contactCount);
};

#endif
