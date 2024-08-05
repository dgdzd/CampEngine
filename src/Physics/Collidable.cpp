//
//  collidable.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 28/06/2024.
//

#include <CampEngine/Physics/Collidable.h>

#include <CampEngine/Graphics/Scene/Sprite.h>
#include <CampEngine/Utils/Logger.h>

Collidable::Collidable() {
    
}

Collidable::Collidable(Sprite* parent, int type) {
    this->parent = parent;
    this->type = type;

    if(type == CIRCLE_COLLIDABLE) {
        this->radius = parent->texture.width;
    } else if(type == POLYGON_COLLIDABLE) {
        for(int i = 0; i < parent->vertices.size(); i += 5) {
            this->corners.push_back(glm::vec2(parent->vertices[i], parent->vertices[i+1]));
        }
    }
}

std::vector<glm::vec2> Collidable::getRotatedCorners(int coordsType) {
    std::vector<glm::vec2> rotated;
    const float angle = parent->rotation;
    const auto origin = glm::vec2(parent->position.x, parent->position.y);
    const float rad = glm::radians(angle);
    const float cos_a = cos(rad);
    const float sin_a = sin(rad);
    for(glm::vec2 vec : corners) {
        vec = glm::vec2(vec.x * parent->scale.x, vec.y * parent->scale.y);
        if(coordsType == COORDS_RELATIVE) rotated.push_back(glm::vec2(vec.x * cos_a - vec.y * sin_a, vec.x * sin_a + vec.y * cos_a));
        else if(coordsType == COORDS_WORLD) rotated.push_back(origin + glm::vec2(vec.x * cos_a - vec.y * sin_a, vec.x * sin_a + vec.y * cos_a));
    }
    
    return rotated;
}

float Collidable::getWidth() {
    return corners[2].x * 2 * parent->scale.x; // get top-right corner relative to center;
}

float Collidable::getHeight() {
    return corners[2].y * 2 * parent->scale.y; // get top-right corner relative to center;
}

AABB Collidable::getAABB() {
    std::vector<glm::vec2> _corners = getRotatedCorners(COORDS_WORLD);
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
