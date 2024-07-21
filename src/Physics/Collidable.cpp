//
//  collidable.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#include <CampEngine/Physics/Collidable.h>

#include <CampEngine/Utils/Logger.h>

Collidable::Collidable() {
    
}

Collidable::Collidable(float radius) {
    this->type = CIRCLE_COLLIDABLE;
    this->radius = radius;
}

Collidable::Collidable(std::vector<float> vertices) {
    this->type = POLYGON_COLLIDABLE;
    for(int i = 0; i < vertices.size(); i += 5) {
        this->corners.push_back(glm::vec2(vertices[i], vertices[i+1]));
    }
}

std::vector<glm::vec2> Collidable::getRotatedCorners(glm::vec2 origin, float angle, int coordsType) {
    std::vector<glm::vec2> rotated;
    float rad = glm::radians(angle);
    float cos_a = cos(rad);
    float sin_a = sin(rad);
    for(glm::vec2 vec : corners) {
        if(coordsType == COORDS_RELATIVE) rotated.push_back(glm::vec2(vec.x * cos_a - vec.y * sin_a, vec.x * sin_a + vec.y * cos_a));
        else if(coordsType == COORDS_WORLD) rotated.push_back(origin + glm::vec2(vec.x * cos_a - vec.y * sin_a, vec.x * sin_a + vec.y * cos_a));
    }
    
    return rotated;
}

float Collidable::getWidth() {
    return corners[2].x * 2; // get top-right corner relative to center;
}

float Collidable::getHeight() {
    return corners[2].y * 2; // get top-right corner relative to center;
}

AABB Collidable::getAABB(glm::vec2 origin, float rotation) {
    std::vector<glm::vec2> _corners = getRotatedCorners(origin, rotation, COORDS_WORLD);
    auto limits = std::numeric_limits<float>();
    float minWidth = limits.max();
    float maxWidth = limits.min();
    float minHeight = limits.max();
    float maxHeight = limits.min();
    
    for(auto corner : _corners) {
        if(corner.x < minWidth) minWidth = corner.x;
        if(corner.x > maxWidth) maxWidth = corner.x;
        
        if(corner.y < minHeight) minHeight = corner.y;
        if(corner.y > maxHeight) maxHeight = corner.y;
    }
    
    return AABB(glm::vec2(minWidth, minHeight), glm::vec2(maxWidth, maxHeight));
}
