//
//  maths.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#include <physics/maths.h>

float distance(glm::vec2 a, glm::vec2 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float length(glm::vec2 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float clamp(float value, float min, float max) {
    if(value < min) return min;
    if(value > max) return max;
    return value;
}

float dot(glm::vec2 a, glm::vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float cross(glm::vec2 a, glm::vec2 b) {
    return a.x * b.y - a.y * b.x;
}

glm::vec2 normalize(glm::vec2 vec) {
    float len = length(vec);
    return vec / len;
}

