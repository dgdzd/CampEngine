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

float distanceSquared(glm::vec2 a, glm::vec2 b) {
    return pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
}

float length(glm::vec2 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float lengthSquared(glm::vec2 vec) {
    return vec.x * vec.x + vec.y * vec.y;
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

void pointSegmentDistance(glm::vec2 p, glm::vec2 a, glm::vec2 b, float& distSquared, glm::vec2& cp) {
    glm::vec2 ab = b - a;
    glm::vec2 ap = p - a;
    
    float proj = dot(ap, ab);
    float abLen = lengthSquared(ab);
    float d = proj / abLen;
    
    if(d <= 0) {
        cp = a;
    } if(d >= 1) {
        cp = b;
    } else {
        cp = a + ab * d;
    }
    
    distSquared = distanceSquared(p, cp);
}

bool nearlyEqual(float a, float b) {
    float dist = abs(b - a);
    return dist < 0.0005;
}

bool nearlyEqual(glm::vec2 a, glm::vec2 b) {
    return nearlyEqual(a.x, b.x) && nearlyEqual(a.y, b.y);
}
