//
//  aabb.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 03/07/2024.
//

#include <algorithm>
#include <physics/aabb.h>

AABB::AABB(glm::vec2 min, glm::vec2 max) {
    this->min = min;
    this->max = max;
}

AABB::AABB(float x1, float x2, float y1, float y2) {
    this->min = glm::vec2(std::min(x1, x2), std::min(y1, y2));
    this->max = glm::vec2(std::max(x1, x2), std::max(y1, y2));
}
