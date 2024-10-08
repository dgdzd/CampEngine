//
//  collidable.h
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#ifndef CE_COLLIDABLE_H
#define CE_COLLIDABLE_H

#define CIRCLE_COLLIDABLE 0
#define POLYGON_COLLIDABLE 1

#define COORDS_RELATIVE 0
#define COORDS_WORLD 1

#include <glm/glm.hpp>

#include <CampEngine/Physics/AABB.h>

#include <vector>

class Sprite;

class Collidable {
public:
    int type;
    float radius;
    std::vector<glm::vec2> corners;
    Sprite* parent;
    
    Collidable();
    Collidable(Sprite* parent, int type);
    
    void init();
    std::vector<glm::vec2> getRotatedCorners(int coordsType=0);
    float getWidth();
    float getHeight();

    /*!
     * @brief Gets the current relative bouding box of the collider, based on the current rotation.
     *
     * @param[in] origin Center of the body.
     * @param[in] rotation Rotation of the body.
     *
     * @returns A axis-aligned bounding box (AABB).
     */
    AABB getAABB();
};

#endif
