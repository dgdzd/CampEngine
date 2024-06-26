//
//  physics_environment.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_PHYSICS_ENVIRONMENT_H
#define CE_PHYSICS_ENVIRONMENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <physics/maths.h>

class PhysicsEnvironment {
    float deltaTime;
    float fpsCount;
    glm::vec2 gravity;
};

#endif
