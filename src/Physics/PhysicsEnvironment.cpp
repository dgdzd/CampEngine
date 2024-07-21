//
//  physics_environment.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#include <CampEngine/Physics/PhysicsEnvironment.h>

#include <CampEngine/Physics/Maths.h>

PhysicsEnvironment* PhysicsEnvironment::instance;

PhysicsEnvironment::PhysicsEnvironment() {
    
}

PhysicsEnvironment::PhysicsEnvironment(int substeps, glm::vec2 gravity) {
    this->substeps = substeps;
    this->g = gravity;
    this->deltaTime = 1.0f/60.0f;
    this->pixelPerMeter = 64;
}

PhysicsEnvironment* PhysicsEnvironment::getInstance() {
    if(!instance) {
        instance = new PhysicsEnvironment(1, glm::vec2(0, -9.81));
    }
    return instance;
}
