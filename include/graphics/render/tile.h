//
//  tile.h
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#ifndef CE_TILE_H
#define CE_TILE_H

#include <graphics/render/sprite.h>
#include <physics/rigid_body.h>
#include <physics/collisions_handler.h>

class Tile : public Sprite, public RigidBody2D {
public:
    Tile(GLFWwindow* window, Shader shader, Texture texture, float xtile, float ytile);
    Tile(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 tilePosition);
    
    virtual void update(Camera camera, glm::mat4 projection);
    glm::vec2 getTilePosition();
};

#endif
