//
//  rigid_body.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#include <CampEngine/Physics/RigidBody.h>

RigidBody2D::RigidBody2D(PhysicsEnvironment* env, Sprite* parent, float mass, Collidable collision, bool isStatic, bool hasGravity) {
    this->env = env;
    this->parent = parent;
    this->mass = mass;
    this->restitution = 0.0f;
    this->isStatic = isStatic;
    this->hasGravity = hasGravity;
    this->force = glm::vec2(0.0f);
    this->collision = collision;
    this->staticFriction = 0.6f;
    this->dynamicFriction = 0.3f;
    this->rotationalInertia = calculateRotationalInertia();
}

float RigidBody2D::calculateRotationalInertia() {
    if(collision.type == CIRCLE_COLLIDABLE) {
        return (mass * collision.radius * collision.radius)/2;
    } else if(collision.type == POLYGON_COLLIDABLE) {
        float width = collision.getWidth();
        float height = collision.getHeight();
        return 1.0f/12.0f * mass * (width * width + height * height);
    }
    
    return -1;
}

void RigidBody2D::step() {
    if(!isStatic) {
        float dt = env->deltaTime;
        if(hasGravity) applyForce(env->g * mass / (float)env->substeps);
        glm::vec2 acceleration = force / mass;
        linearVelocity += acceleration;
        parent->position += glm::vec3(linearVelocity.x, linearVelocity.y, 0) * dt;
        parent->rotation += glm::degrees(angularVelocity) * dt;
        force = glm::vec2(0.0f);
    }
}

void RigidBody2D::applyForce(glm::vec2 force) {
    float dt = env->deltaTime;
    this->force += force * env->pixelPerMeter * dt;
}

float RigidBody2D::getInverseMass() {
    if(isStatic) return 0;
    return 1.0f / mass;
}

float RigidBody2D::getInverseInertia() {
    if(isStatic) return 0;
    
    return 1.0f / rotationalInertia;
}
