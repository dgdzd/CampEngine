//
//  physics_object.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_PHYSICS_OBJECT_H
#define CE_PHYSICS_OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <physics/physics_environment.h>

class PhysicsObject {
    glm::vec2 linearVelocity;
    glm::vec2 rotationalVelocity;
}

#endif
