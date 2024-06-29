//
//  collisions_handler.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#include <physics/collisions_handler.h>

std::vector<RigidBody2D*> CollisionsHandler::bodies;
double CollisionsHandler::lastUpdate = 0.0;
PhysicsEnvironment* CollisionsHandler::env = PhysicsEnvironment::getInstance();

bool CollisionsHandler::collide(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& normal, float& depth) {
    switch(bodyA->collision.type) {
        case CIRCLE_COLLIDABLE: {
            switch(bodyB->collision.type) {
                case CIRCLE_COLLIDABLE: {
                    return intersectCircles(bodyA, bodyB, normal, depth);
                }
                case POLYGON_COLLIDABLE: {
                    return intersectCirclePolygon(bodyA, bodyB, normal, depth);
                }
                    
                default:
                    break;
            }
            break;
        }
            
        case POLYGON_COLLIDABLE: {
            switch (bodyB->collision.type) {
                case POLYGON_COLLIDABLE: {
                    return intersectPolygons(bodyA, bodyB, normal, depth);
                }
                case CIRCLE_COLLIDABLE: {
                    return intersectCirclePolygon(bodyB, bodyA, normal, depth);
                }
                    
                default:
                    break;
            }
        }
            
        default:
            break;
    }
    
    return false;
}

bool CollisionsHandler::intersectCircles(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& normal, float& depth) {
    glm::vec2 centerA = glm::vec2(bodyA->parent->position.x, bodyA->parent->position.y);
    glm::vec2 centerB = glm::vec2(bodyB->parent->position.x, bodyB->parent->position.y);
    float radiusA = bodyA->collision.radius;
    float radiusB = bodyB->collision.radius;
    normal = glm::vec2(0.0f);
    depth = 0.0f;
    
    glm::vec2 dir = centerB - centerA;
    float dist = length(dir);
    float radii = radiusA + radiusB;
    
    if(dist > radii || dist == 0.0f) {
        return false;
    }
    
    normal = normalize(dir);
    depth = radii - dist;
    
    Logger::CampEngine.info("Circle intersect!");
    return true;
}

bool CollisionsHandler::intersectPolygons(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& normal, float& depth) {
    glm::vec2 positionA = glm::vec2(bodyA->parent->position.x, bodyA->parent->position.y);
    glm::vec2 positionB = glm::vec2(bodyB->parent->position.x, bodyB->parent->position.y);
    glm::vec2 dir = positionB - positionA;
    std::vector<glm::vec2> cornersA = bodyA->collision.getRotatedCorners(positionA, bodyA->parent->rotation, COORDS_WORLD);
    std::vector<glm::vec2> cornersB = bodyB->collision.getRotatedCorners(positionB, bodyB->parent->rotation, COORDS_WORLD);
    normal = glm::vec2(0.0f);
    depth = 0.0f;
    
    if(positionA == positionB) return false;
    
    for(int i = 0; i < cornersA.size(); i++) {
        float minA, maxA, minB, maxB;
        glm::vec2 va = cornersA[i];
        glm::vec2 vb = cornersA[(i + 1) % cornersA.size()];
        
        glm::vec2 edge = vb - va;
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);
        axis = normalize(axis);
        
        projectVertices(cornersA, axis, minA, maxA);
        projectVertices(cornersB, axis, minB, maxB);
        
        if(minA >= maxB || minB >= maxA) {
            return false;
        }
        
        float axisDepth = std::min(maxB - minA, maxA - minB);
        if(axisDepth < depth || depth == 0.0f) {
            depth = axisDepth;
            normal = axis;
        }
    }
    
    for(int i = 0; i < cornersB.size(); i++) {
        float minA, maxA, minB, maxB;
        glm::vec2 va = cornersB[i];
        glm::vec2 vb = cornersB[(i + 1) % cornersB.size()];
        
        glm::vec2 edge = vb - va;
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);
        axis = normalize(axis);
        
        projectVertices(cornersB, axis, minB, maxB);
        projectVertices(cornersA, axis, minA, maxA);
        
        if(minA >= maxB || minB >= maxA) {
            return false;
        }
        
        float axisDepth = std::min(maxB - minA, maxA - minB);
        if(axisDepth < depth || depth == 0.0f) {
            depth = axisDepth;
            normal = axis;
        }
    }
    
    depth /= length(normal);
    normal = normalize(normal);
    
    if(dot(dir, normal) < 0.0f) {
        normal = -normal;
    }
    
    return true;
}

bool CollisionsHandler::intersectCirclePolygon(RigidBody2D* circle, RigidBody2D* polygon, glm::vec2& normal, float& depth) {
    glm::vec2 positionA = glm::vec2(circle->parent->position.x, circle->parent->position.y);
    glm::vec2 positionB = glm::vec2(polygon->parent->position.x, polygon->parent->position.y);
    glm::vec2 dir = positionB - positionA;
    std::vector<glm::vec2> corners = polygon->collision.getRotatedCorners(positionB, polygon->parent->rotation);
    normal = glm::vec2(0.0f);
    depth = 0.0f;
    
    for(int i = 0; i < corners.size(); i++) {
        float minA, maxA, minB, maxB;
        glm::vec2 va = corners[i];
        glm::vec2 vb = corners[(i + 1) % corners.size()];
        
        glm::vec2 edge = vb - va;
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);
        axis = normalize(axis);
        
        projectVertices(corners, axis, minA, maxA);
        projectCircle(positionA, circle->collision.radius, axis, minB, maxB);
        
        if(minA >= maxB || minB >= maxA) {
            return false;
        }
        
        float axisDepth = std::min(maxB - minA, maxA - minB);
        if(axisDepth < depth || depth == 0.0f) {
            depth = axisDepth;
            normal = axis;
        }
    }
    
    float minA, maxA, minB, maxB;
    
    glm::vec2 cp = closestPointOnPolygon(positionA, corners);
    glm::vec2 axis = cp - positionA;
    
    projectVertices(corners, axis, minA, maxA);
    projectCircle(positionA, circle->collision.radius, axis, minB, maxB);
    
    if(minA >= maxB || minB >= maxA) {
        return false;
    }
    
    float axisDepth = std::min(maxB - minA, maxA - minB);
    if(axisDepth < depth || depth == 0.0f) {
        depth = axisDepth;
        normal = axis;
    }
    
    depth = length(normal);
    normal = normalize(normal);
    
    if(dot(dir, normal) < 0.0f) {
        normal = -normal;
    }
    
    return true;
}

void CollisionsHandler::projectVertices(std::vector<glm::vec2> vertices, glm::vec2 axis, float& min, float& max) {
    min = std::numeric_limits<float>().max();
    max = std::numeric_limits<float>().min();
    
    for(int i = 0; i < vertices.size(); i++) {
        glm::vec2 v = vertices[i];
        float projected = dot(v, axis);
        
        if(projected < min) min = projected;
        if(projected > max) max = projected;
    }
}

void CollisionsHandler::projectCircle(glm::vec2 center, float radius, glm::vec2 axis, float& min, float& max) {
    min = std::numeric_limits<float>().max();
    max = std::numeric_limits<float>().min();
    
    glm::vec2 dir = normalize(axis);
    glm::vec2 dirAndRad = dir * radius;
    
    glm::vec2 p1 = center + dirAndRad;
    glm::vec2 p2 = center - dirAndRad;
    
    min = dot(p1, axis);
    max = dot(p2, axis);
    
    if(min > max) {
        float temp = min;
        min = max;
        max = temp;
    }
}

glm::vec2 CollisionsHandler::closestPointOnPolygon(glm::vec2 target, std::vector<glm::vec2> vertices) {
    float minDist = std::numeric_limits<float>().max();
    glm::vec2 result = glm::vec2(minDist);
    for(glm::vec2 v : vertices) {
        if(distance(target, v) < minDist) {
            minDist = length(v);
            result = v;
        }
    }
    
    return result;
}

void CollisionsHandler::findContactPoints(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount) {
    contact1 = glm::vec2(0);
    contact2 = glm::vec2(0);
    contactCount = 0;
    
    if(bodyA->collision.type == CIRCLE_COLLIDABLE) {
        if(bodyB->collision.type == CIRCLE_COLLIDABLE) {
            findCircleContactPoint(bodyA, bodyB, contact1, contact2, contactCount);
        } else if(bodyB->collision.type == POLYGON_COLLIDABLE) {
            
        }
    } else if(bodyA->collision.type == POLYGON_COLLIDABLE) {
        if(bodyB->collision.type == CIRCLE_COLLIDABLE) {
            
        }
    }
}

void CollisionsHandler::findCircleContactPoint(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount) {
    glm::vec2 positionA = glm::vec2(bodyA->parent->position.x, bodyA->parent->position.y);
    glm::vec2 positionB = glm::vec2(bodyB->parent->position.x, bodyB->parent->position.y);
    glm::vec2 dir = normalize(positionB - positionA);
    
    contact1 = positionA + dir * bodyA->collision.radius;
    contactCount = 1;
}

void CollisionsHandler::findCirclePolygonContactPoint(RigidBody2D* circle, RigidBody2D* polygon, glm::vec2& contact1, glm::vec2& contact2, int& contactCount) {
    glm::vec2 positionA = glm::vec2(circle->parent->position.x, circle->parent->position.y);
    glm::vec2 positionB = glm::vec2(polygon->parent->position.x, polygon->parent->position.y);
    std::vector<glm::vec2> corners = polygon->collision.getRotatedCorners(positionB, polygon->parent->rotation, COORDS_WORLD);
    
    for(int i = 0; i < corners.size(); i++) {
        glm::vec2 va = corners[i];
        glm::vec2 vb = corners[(i + 1) % corners.size()];
        
    }
}

void CollisionsHandler::step() {
    if(lastUpdate == 0) {
        lastUpdate = glfwGetTime();
    } else {
        double now = glfwGetTime();
        env->deltaTime = now - lastUpdate;
        env->fpsCount = 1.0f / env->deltaTime;
        lastUpdate = now;
    }
    
    for(int i = 0; i <= env->substeps; i++) {
        for(RigidBody2D* body : bodies) {
            body->step();
        }
        fixCollisions();
    }
}

void CollisionsHandler::fixCollisions() {
    std::vector<CollisionManifold> contacts;
    glm::vec2 normal;
    float depth;
    
    for(int i = 0; i < bodies.size() - 1; i++) {
        RigidBody2D* bodyA = bodies.at(i);
        for(int j = i+1; j < bodies.size(); j++) {
            RigidBody2D* bodyB = bodies.at(j);
            if(collide(bodyA, bodyB, normal, depth)) {
                if(bodyA->isStatic && bodyB->isStatic) continue;
                glm::vec2 contact1, contact2;
                int contactCount;
                findContactPoints(bodyA, bodyB, contact1, contact2, contactCount);
                contacts.push_back(CollisionManifold(bodyA, bodyB, normal, depth, contact1, contact2, contactCount));
            }
        }
    }
    
    for(CollisionManifold contact : contacts) {
        resolveCollision(contact);
    }
}

void CollisionsHandler::resolveCollision(CollisionManifold contact) {
    if(contact.bodyA->isStatic) contact.bodyB->parent->position += glm::vec3(contact.normal.x, contact.normal.y, 0) * contact.depth;
    else if(contact.bodyB->isStatic) contact.bodyA->parent->position -= glm::vec3(contact.normal.x, contact.normal.y, 0) * contact.depth;
    else {
        contact.bodyA->parent->position -= glm::vec3(contact.normal.x, contact.normal.y, 0) * contact.depth / 2.0f;
        contact.bodyB->parent->position += glm::vec3(contact.normal.x, contact.normal.y, 0) * contact.depth / 2.0f;
    }
    
    glm::vec2 relativeVel = contact.bodyB->linearVelocity - contact.bodyA->linearVelocity;
    if(dot(relativeVel, contact.normal) > 0.0f) return;
    
    float invMassA = contact.bodyA->getInverseMass();
    float invMassB = contact.bodyB->getInverseMass();
    
    float e = std::min(contact.bodyA->restitution, contact.bodyB->restitution);
    float j = -(1 + e) * dot(relativeVel, contact.normal);
    j /= invMassA + invMassB;
    glm::vec2 impulse = j * contact.normal;
    
    contact.bodyA->linearVelocity -= impulse * invMassA;
    contact.bodyB->linearVelocity += impulse * invMassB;
}
