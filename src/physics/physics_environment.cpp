//
//  physics_environment.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#include <physics/physics_environment.h>

PhysicsEnvironment* PhysicsEnvironment::instance;

PhysicsEnvironment::PhysicsEnvironment() {
    
}

PhysicsEnvironment::PhysicsEnvironment(int substeps, glm::vec2 gravity) {
    this->substeps = substeps;
    this->g = gravity;
    this->deltaTime = 0.008;
    this->pixelPerMeter = 32;
}

PhysicsEnvironment* PhysicsEnvironment::getInstance() {
    if(!instance) {
        instance = new PhysicsEnvironment(1, glm::vec2(0, -9.81));
    }
    return instance;
}
