//
//  physics_environment.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_PHYSICS_ENVIRONMENT_H
#define CE_PHYSICS_ENVIRONMENT_H

#include <glm/glm.hpp>

#include <CampEngine/Physics/Maths.h>

class PhysicsEnvironment {
private:
    static PhysicsEnvironment* instance;
public:
    float deltaTime;
    int substeps;
    float fpsCount;
    glm::vec2 g;
    float pixelPerMeter;
    
    PhysicsEnvironment();
    PhysicsEnvironment(int substeps, glm::vec2 gravity);
    
    static PhysicsEnvironment* getInstance();
};

#endif
