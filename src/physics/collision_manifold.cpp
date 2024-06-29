//
//  collision_manifold.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 29/06/2024.
//

#include <physics/collision_manifold.h>

CollisionManifold::CollisionManifold(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2 normal, float depth, glm::vec2 contact1, glm::vec2 contact2, int contactCount) {
    this->bodyA = bodyA;
    this->bodyB = bodyB;
    this->normal = normal;
    this->depth = depth;
    this->contact1 = contact1;
    this->contact2 = contact2;
    this->contactCount = contactCount;
}
