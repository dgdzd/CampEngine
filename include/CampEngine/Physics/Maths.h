//
//  maths.h
//  CampEngine++
//
//  Created by Noah Campagne on 26/06/2024.
//

#ifndef CE_MATHS_H
#define CE_MATHS_H

#include <glm/glm.hpp>

extern float distance(glm::vec2 a, glm::vec2 b);
extern float distanceSquared(glm::vec2 a, glm::vec2 b);
extern float length(glm::vec2 vec);
extern float lengthSquared(glm::vec2 vec);
extern float clamp(float value, float min, float max);
extern float dot(glm::vec2 a, glm::vec2 b);
extern float cross(glm::vec2 a, glm::vec2 b);
extern glm::vec2 normalize(glm::vec2 vec);
extern void pointSegmentDistance(glm::vec2 p, glm::vec2 a, glm::vec2 b, float& distSquared, glm::vec2& cp);
extern bool nearlyEqual(float a, float b);
extern bool nearlyEqual(glm::vec2 a, glm::vec2 b);

#endif
