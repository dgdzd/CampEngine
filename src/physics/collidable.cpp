//
//  collidable.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#include <physics/collidable.h>

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
    for(glm::vec2 vec : corners) {
        if(coordsType == COORDS_RELATIVE) rotated.push_back(glm::vec2(vec.x * cos(rad) - vec.y * sin(rad), vec.x * sin(rad) + vec.y * cos(rad)));
        else if(coordsType == COORDS_WORLD) rotated.push_back(origin + glm::vec2(vec.x * cos(rad) - vec.y * sin(rad), vec.x * sin(rad) + vec.y * cos(rad)));
    }
    
    return rotated;
}

float Collidable::getWidth() {
    return corners[2].x * 2; // get top-right corner relative to center;
}

float Collidable::getHeight() {
    return corners[2].y * 2; // get top-right corner relative to center;
}
