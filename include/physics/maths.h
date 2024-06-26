//
//  maths.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_MATHS_H
#define CE_MATHS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

float distance(glm::vec2 a, glm::vec2 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2))
}

float length(glm::vec2 vec) {
    return vec.x * vec.x + vec.y * vec.y
}

float clamp(float value, float min, float max);
float dot(glm::vec2 a, glm::vec2 b);
float cross(glm::vec2 a, glm::vec2 b);

glm::vec2 normalize(glm::vec2 vec);

#endif /* maths_h */
