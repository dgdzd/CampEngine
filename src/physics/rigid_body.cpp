//
//  rigid_body.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#include <physics/rigid_body.h>

RigidBody2D::RigidBody2D(PhysicsEnvironment* env, Sprite* parent, float mass, bool isStatic, bool hasGravity) {
    this->env = env;
    this->parent = parent;
    this->mass = mass;
    this->restitution = 0.2f;
    this->isStatic = isStatic;
    this->hasGravity = hasGravity;
    this->force = glm::vec2(0.0f);
    this->rotationalInertia = calculateRotationalInertia();
}

float RigidBody2D::calculateRotationalInertia() {
    if(collision.type == CIRCLE_COLLIDABLE) {
        return (mass * collision.radius * collision.radius)/2;
    } else if(collision.type == POLYGON_COLLIDABLE) {
        float width = collision.getWidth();
        float height = collision.getHeight();
        return (mass * (width * width + height * height))/12.0f;
    }
    
    return -1;
}

void RigidBody2D::step() {
    if(!isStatic) {
        if(hasGravity) applyForce(env->g * mass);
        glm::vec2 acceleration = force / mass;
        linearVelocity += acceleration;
        parent->position += glm::vec3(linearVelocity.x, linearVelocity.y, 0) * (env->deltaTime / (float)env->substeps);
        force = glm::vec2(0.0f);
    }
}

void RigidBody2D::applyForce(glm::vec2 force) {
    this->force += force * env->pixelPerMeter * env->deltaTime;
}

float RigidBody2D::getInverseMass() {
    if(isStatic) return 0;
    return 1.0f / mass;
}
