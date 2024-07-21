//
//  collisions_handler.h
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#ifndef CE_COLLISIONS_HANDLER_H
#define CE_COLLISIONS_HANDLER_H

#include <CampEngine/Physics/RigidBody.h>
#include <CampEngine/Physics/CollisionManifold.h>

#include <vector>

class RigidBody2D;

class CollisionsHandler {
private:
    static double lastUpdate;
    static PhysicsEnvironment* env;
    
    static bool collide(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& normal, float& depth);
    static bool intersectCircles(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& normal, float& depth);
    static bool intersectPolygons(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& normal, float& depth);
    static bool intersectCirclePolygon(RigidBody2D* circle, RigidBody2D* polygon, glm::vec2& normal, float& depth);
    static void projectVertices(std::vector<glm::vec2> vertices, glm::vec2 axis, float& min, float& max);
    static void projectCircle(glm::vec2 center, float radius, glm::vec2 axis, float& min, float& max);
    static glm::vec2 closestPointOnPolygon(glm::vec2 target, std::vector<glm::vec2> vertices);
    static void findContactPoints(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount);
    static void findCircleContactPoint(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount);
    static void findPolygonContactPoint(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount);
    static void findCirclePolygonContactPoint(RigidBody2D* circle, RigidBody2D* polygon, glm::vec2& contact1, glm::vec2& contact2, int& contactCount);
    static void broadPhase(std::vector<std::pair<int, int>>& contactPairs);
    static bool intersectAABB(RigidBody2D* bodyA, RigidBody2D* bodyB);
    static void narrowPhase(std::vector<std::pair<int, int>> contactPairs);
    static void separateBodies(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2 normal, float depth);
    static void resolveCollision(CollisionManifold contact);
    static void resolveCollisionWithRotation(CollisionManifold contact);
    static void resolveCollisionWithRotationAndFriction(CollisionManifold contact);
    
    
public:
    static std::vector<RigidBody2D*> bodies;
    static std::vector<glm::vec2> totalContacts;
    
    static void step();
    static void fixCollisions();
};

#endif
