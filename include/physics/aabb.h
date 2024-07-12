//
//  aabb.h
//  CampEngine++
//
//  Created by Noah Campagne on 03/07/2024.
//

#ifndef CE_AABB_H
#define CE_AABB_H

#include <glm/glm.hpp>

struct AABB {
    glm::vec2 min;
    glm::vec2 max;
    
    AABB(glm::vec2 min, glm::vec2 max);
    AABB(float x1, float x2, float y1, float y2);
};

#endif
