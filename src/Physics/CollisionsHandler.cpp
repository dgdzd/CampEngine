//
//  collisions_handler.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#include <CampEngine/Physics/CollisionsHandler.h>

#include <CampEngine/Physics/Collidable.h>
#include <CampEngine/Physics/Maths.h>

#include <limits>
#include <math.h>

std::vector<RigidBody2D*> CollisionsHandler::bodies;
std::vector<glm::vec2> CollisionsHandler::totalContacts;
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
    
    if(dist >= radii || dist == 0.0f) {
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
    std::vector<glm::vec2> cornersA = bodyA->collision.getRotatedCorners(COORDS_WORLD);
    std::vector<glm::vec2> cornersB = bodyB->collision.getRotatedCorners(COORDS_WORLD);
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
    std::vector<glm::vec2> corners = polygon->collision.getRotatedCorners();
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
            findCirclePolygonContactPoint(bodyA, bodyB, contact1, contact2, contactCount);
        }
    } else if(bodyA->collision.type == POLYGON_COLLIDABLE) {
        if(bodyB->collision.type == CIRCLE_COLLIDABLE) {
            findCirclePolygonContactPoint(bodyB, bodyA, contact1, contact2, contactCount);
        } else if(bodyB->collision.type == POLYGON_COLLIDABLE) {
            findPolygonContactPoint(bodyA, bodyB, contact1, contact2, contactCount);
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

void CollisionsHandler::findPolygonContactPoint(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2& contact1, glm::vec2& contact2, int& contactCount) {
    glm::vec2 positionA = glm::vec2(bodyA->parent->position.x, bodyA->parent->position.y);
    glm::vec2 positionB = glm::vec2(bodyB->parent->position.x, bodyB->parent->position.y);
    std::vector<glm::vec2> cornersA = bodyA->collision.getRotatedCorners(COORDS_WORLD);
    std::vector<glm::vec2> cornersB = bodyB->collision.getRotatedCorners(COORDS_WORLD);
    float minDistSquared = std::numeric_limits<float>::max();
    
    for(glm::vec2 p : cornersA) {
        for(int i = 0; i < cornersB.size(); i++) {
            float distSquared;
            glm::vec2 contact;
            glm::vec2 va = cornersB[i];
            glm::vec2 vb = cornersB[(i + 1) % cornersB.size()];
            
            pointSegmentDistance(p, va, vb, distSquared, contact);
            
            if(nearlyEqual(distSquared, minDistSquared)) {
                if(!nearlyEqual(contact, contact1)) {
                    minDistSquared = distSquared;
                    contact2 = contact;
                    contactCount = 2;
                }
            } else if(distSquared < minDistSquared) {
                minDistSquared = distSquared;
                contact1 = contact;
                contactCount = 1;
            }
        }
    }
    
    for(glm::vec2 p : cornersB) {
        for(int i = 0; i < cornersA.size(); i++) {
            float distSquared;
            glm::vec2 contact;
            glm::vec2 va = cornersA[i];
            glm::vec2 vb = cornersA[(i + 1) % cornersA.size()];
            
            pointSegmentDistance(p, va, vb, distSquared, contact);
            
            if(nearlyEqual(distSquared, minDistSquared)) {
                if(!nearlyEqual(contact, contact1)) {
                    contact2 = contact;
                    contactCount = 2;
                }
            } else if(distSquared < minDistSquared) {
                minDistSquared = distSquared;
                contact1 = contact;
                contactCount = 1;
            }
        }
    }
}

void CollisionsHandler::findCirclePolygonContactPoint(RigidBody2D* circle, RigidBody2D* polygon, glm::vec2& contact1, glm::vec2& contact2, int& contactCount) {
    glm::vec2 positionA = glm::vec2(circle->parent->position.x, circle->parent->position.y);
    glm::vec2 positionB = glm::vec2(polygon->parent->position.x, polygon->parent->position.y);
    std::vector<glm::vec2> corners = polygon->collision.getRotatedCorners(COORDS_WORLD);
    float minDistSquared = std::numeric_limits<float>().max();
    
    for(int i = 0; i < corners.size(); i++) {
        float distSquared;
        glm::vec2 contact;
        glm::vec2 va = corners[i];
        glm::vec2 vb = corners[(i + 1) % corners.size()];
        
        pointSegmentDistance(positionA, va, vb, distSquared, contact);
        
        if(distSquared < minDistSquared) {
            minDistSquared = distSquared;
            contact1 = contact;
        }
    }
    
    contactCount = 1;
}

void CollisionsHandler::step() {
    totalContacts.clear();
    if(lastUpdate == 0) {
        lastUpdate = glfwGetTime();
    } else {
        double now = glfwGetTime();
        env->deltaTime = (now - lastUpdate);
        env->fpsCount = 1.0f / env->deltaTime;
        lastUpdate = now;
    }
    
    for(int i = 0; i <= env->substeps; i++) {
        for(RigidBody2D* body : bodies) {
            body->step();
            fixCollisions();
        }
    }
}

void CollisionsHandler::fixCollisions() {
    std::vector<std::pair<int, int>> contactPairs;
    broadPhase(contactPairs);
    narrowPhase(contactPairs);
}

void CollisionsHandler::broadPhase(std::vector<std::pair<int, int>>& contactPairs) {
    for(int i = 0; i < bodies.size() - 1; i++) {
        RigidBody2D* bodyA = bodies.at(i);
        for(int j = i+1; j < bodies.size(); j++) {
            RigidBody2D* bodyB = bodies.at(j);
            
            if(bodyA->isStatic && bodyB->isStatic) continue;
            if(!intersectAABB(bodyA, bodyB)) continue;
            
            contactPairs.push_back(std::pair(i, j));
        }
    }
}

bool CollisionsHandler::intersectAABB(RigidBody2D* bodyA, RigidBody2D* bodyB) {
    glm::vec2 positionA = bodyA->parent->position;
    glm::vec2 positionB = bodyB->parent->position;
    AABB a = bodyA->collision.getAABB();
    AABB b = bodyB->collision.getAABB();
    
    if(a.max.x <= b.min.x || b.max.x <= a.min.x ||
       a.max.y <= b.min.y || b.max.y <= a.min.y) {
        return false;
    }
    return true;
}

void CollisionsHandler::narrowPhase(std::vector<std::pair<int, int>> contactPairs) {
    glm::vec2 normal;
    float depth;
    
    for(std::pair<int, int> contactPair : contactPairs) {
        RigidBody2D* bodyA = bodies[contactPair.first];
        RigidBody2D* bodyB = bodies[contactPair.second];
        
        if(collide(bodyA, bodyB, normal, depth)) {
            glm::vec2 contact1, contact2;
            int contactCount;
            
            separateBodies(bodyA, bodyB, normal, depth);
            findContactPoints(bodyA, bodyB, contact1, contact2, contactCount);
            
//            totalContacts.push_back(contact1);
//            if(contactCount == 2) totalContacts.push_back(contact2);
            
            CollisionManifold contact(bodyA, bodyB, normal, depth, contact1, contact2, contactCount);
            resolveCollisionWithRotationAndFriction(contact);
        }
    }
}

void CollisionsHandler::separateBodies(RigidBody2D* bodyA, RigidBody2D* bodyB, glm::vec2 normal, float depth) {
    if(bodyA->isStatic) bodyB->parent->position += glm::vec3(normal.x, normal.y, 0) * depth;
    else if(bodyB->isStatic) bodyA->parent->position -= glm::vec3(normal.x, normal.y, 0) * depth;
    else {
        bodyA->parent->position -= glm::vec3(normal.x, normal.y, 0) * depth / 2.0f;
        bodyB->parent->position += glm::vec3(normal.x, normal.y, 0) * depth / 2.0f;
    }
}

void CollisionsHandler::resolveCollision(CollisionManifold contact) {
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

void CollisionsHandler::resolveCollisionWithRotation(CollisionManifold contact) {
    RigidBody2D* bodyA = contact.bodyA;
    RigidBody2D* bodyB = contact.bodyB;
    glm::vec2 positionA = glm::vec2(bodyA->parent->position.x, bodyA->parent->position.y);
    glm::vec2 positionB = glm::vec2(bodyB->parent->position.x, bodyB->parent->position.y);
    glm::vec2 normal = contact.normal;
    glm::vec2 contact1 = contact.contact1;
    glm::vec2 contact2 = contact.contact2;
    int contactCount = contact.contactCount;
    std::vector contacts = { contact1, contact2 };
    std::vector<glm::vec2> impulses;
    std::vector<glm::vec2> frictionImpulses;
    std::vector<float> js;
    std::vector<glm::vec2> ras;
    std::vector<glm::vec2> rbs;
    float e = std::min(bodyA->restitution, bodyB->restitution);
    
    for(int i = 0; i < contactCount; i++) {
        glm::vec2 contactPoint = contacts[i];
        glm::vec2 ra = contactPoint - positionA;
        glm::vec2 rb = contactPoint - positionB;
        glm::vec2 raP = glm::vec2(-ra.y, ra.x);
        glm::vec2 rbP = glm::vec2(-rb.y, rb.x);
        glm::vec2 angularLinearVelA = raP * bodyA->angularVelocity;
        glm::vec2 angularLinearVelB = rbP * bodyB->angularVelocity;
        
        glm::vec2 relativeVel = (bodyB->linearVelocity + angularLinearVelB) - (bodyA->linearVelocity + angularLinearVelA);
        float contactVelMag = dot(relativeVel, normal);
        
        if(contactVelMag > 0.0f) continue;
        
        float raPdotN = dot(raP, normal);
        float rbPdotN = dot(rbP, normal);
        
        float invMassA = bodyA->getInverseMass();
        float invMassB = bodyB->getInverseMass();
        float invInertA = bodyA->getInverseInertia();
        float invInertB = bodyB->getInverseInertia();
        
        float j = -(1.0f + e) * contactVelMag;
        j /= invMassA + invMassB + (raPdotN * raPdotN) * invInertA + (rbPdotN * rbPdotN) * invInertB;
        j /= (float)contactCount;
        glm::vec2 impulse = j * normal;
        
        js.push_back(j);
        impulses.push_back(impulse);
        ras.push_back(ra);
        rbs.push_back(rb);
    }
    
    for(int i = 0; i < impulses.size(); i++) {
        glm::vec2 impulse = impulses[i];
        glm::vec2 ra = ras[i];
        glm::vec2 rb = rbs[i];
        
        bodyA->linearVelocity += -impulse * bodyA->getInverseMass();
        bodyB->linearVelocity += impulse * bodyB->getInverseMass();
        
        bodyA->angularVelocity += -cross(ra, impulse) * bodyA->getInverseInertia();
        bodyB->angularVelocity += cross(rb, impulse) * bodyB->getInverseInertia();
    }
}

void CollisionsHandler::resolveCollisionWithRotationAndFriction(CollisionManifold contact) {
    RigidBody2D* bodyA = contact.bodyA;
    RigidBody2D* bodyB = contact.bodyB;
    glm::vec2 positionA = glm::vec2(bodyA->parent->position.x, bodyA->parent->position.y);
    glm::vec2 positionB = glm::vec2(bodyB->parent->position.x, bodyB->parent->position.y);
    glm::vec2 normal = contact.normal;
    glm::vec2 contact1 = contact.contact1;
    glm::vec2 contact2 = contact.contact2;
    int contactCount = contact.contactCount;
    std::vector<glm::vec2> contacts = { contact1, contact2 };
    std::vector<glm::vec2> impulses;
    std::vector<glm::vec2> frictionImpulses;
    std::vector<float> js;
    std::vector<glm::vec2> ras;
    std::vector<glm::vec2> rbs;
    float e = std::min(bodyA->restitution, bodyB->restitution);
    
    for(int i = 0; i < contactCount; i++) {
        glm::vec2 contactPoint = contacts[i];
        glm::vec2 ra = contactPoint - positionA;
        glm::vec2 rb = contactPoint - positionB;
        glm::vec2 raP = glm::vec2(-ra.y, ra.x);
        glm::vec2 rbP = glm::vec2(-rb.y, rb.x);
        glm::vec2 angularLinearVelA = raP * bodyA->angularVelocity;
        glm::vec2 angularLinearVelB = rbP * bodyB->angularVelocity;
        
        glm::vec2 relativeVel = (bodyB->linearVelocity + angularLinearVelB) - (bodyA->linearVelocity + angularLinearVelA);
        float contactVelMag = dot(relativeVel, normal);
        
        if(contactVelMag > 0.0f) continue;
        
        float raPdotN = dot(raP, normal);
        float rbPdotN = dot(rbP, normal);
        
        float invMassA = bodyA->getInverseMass();
        float invMassB = bodyB->getInverseMass();
        float invInertA = bodyA->getInverseInertia();
        float invInertB = bodyB->getInverseInertia();
        
        float j = -(1.0f + e) * contactVelMag;
        j /= invMassA + invMassB + (raPdotN * raPdotN) * invInertA + (rbPdotN * rbPdotN) * invInertB;
        j /= (float)contactCount;
        glm::vec2 impulse = j * normal;
        
        js.push_back(j);
        impulses.push_back(impulse);
        ras.push_back(ra);
        rbs.push_back(rb);
    }
    
    for(int i = 0; i < impulses.size(); i++) {
        glm::vec2 impulse = impulses[i];
        glm::vec2 ra = ras[i];
        glm::vec2 rb = rbs[i];
        
        bodyA->linearVelocity += -impulse * bodyA->getInverseMass();
        bodyA->angularVelocity += -cross(ra, impulse) * bodyA->getInverseInertia();
        bodyB->linearVelocity += impulse * bodyB->getInverseMass();
        bodyB->angularVelocity += cross(rb, impulse) * bodyB->getInverseInertia();
    }
    
    for(int i = 0; i < js.size(); i++) {
        glm::vec2 contact = contacts[i];
        glm::vec2 ra = contact - positionA;
        glm::vec2 rb = contact - positionB;
        glm::vec2 raP = glm::vec2(-ra.y, ra.x);
        glm::vec2 rbP = glm::vec2(-rb.y, rb.x);
        glm::vec2 angularLinearVelA = raP * bodyA->angularVelocity;
        glm::vec2 angularLinearVelB = rbP * bodyB->angularVelocity;
        float sf = (bodyA->staticFriction + bodyB->staticFriction) * 0.5f;
        float df = (bodyA->dynamicFriction + bodyB->dynamicFriction) * 0.5f;
        
        glm::vec2 relativeVel = (bodyB->linearVelocity + angularLinearVelB) - (bodyA->linearVelocity + angularLinearVelA);
        glm::vec2 tangent = relativeVel - dot(relativeVel, normal) * normal;
        
        if(nearlyEqual(tangent, glm::vec2(0.0f))) continue;
        tangent = normalize(tangent);
        
        float raPdotT = dot(raP, tangent);
        float rbPdotT = dot(rbP, tangent);
        
        float invMassA = bodyA->getInverseMass();
        float invInertA = bodyA->getInverseInertia();
        float invMassB = bodyB->getInverseMass();
        float invInertB = bodyB->getInverseInertia();
        
        float jt = -dot(relativeVel, tangent);
        jt /= invMassA + invMassB + (raPdotT * raPdotT) * invInertA + (rbPdotT * rbPdotT) * invInertB;
        jt /= (float)contactCount;
        
        float j = js[i];
        glm::vec2 frictionImpulse;
        if(abs(jt) <= j * sf) {
            frictionImpulse = jt * tangent;
        } else {
            frictionImpulse = -j * tangent * df;
        }
        
        frictionImpulses.push_back(frictionImpulse);
        ras.push_back(ra);
        rbs.push_back(rb);
    }
    
    for(int i = 0; i < frictionImpulses.size(); i++) {
        glm::vec2 frictionImpulse = frictionImpulses[i];
        glm::vec2 ra = ras[i];
        glm::vec2 rb = rbs[i];
        
        bodyA->linearVelocity += -frictionImpulse * bodyA->getInverseMass();
        bodyA->angularVelocity += -cross(ra, frictionImpulse) * bodyA->getInverseInertia();
        bodyB->linearVelocity += frictionImpulse * bodyB->getInverseMass();
        bodyB->angularVelocity += cross(rb, frictionImpulse) * bodyB->getInverseInertia();
    }
}
