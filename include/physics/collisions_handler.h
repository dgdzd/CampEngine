//
//  collisions_handler.h
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#ifndef CE_COLLISIONS_HANDLER_H
#define CE_COLLISIONS_HANDLER_H

#include <physics/collidable.h>
#include <physics/rigid_body.h>
#include <physics/maths.h>
#include <physics/collision_manifold.h>

#include <vector>
#include <limits>
#include <math.h>

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
    static void findCirclePolygonContactPoint(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount);
    static void resolveCollision(CollisionManifold contact);
    
public:
    static std::vector<RigidBody2D*> bodies;
    
    static void step();
    static void fixCollisions();
};

#endif
