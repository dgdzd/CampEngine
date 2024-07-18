//
//  tile.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 27/06/2024.
//

#include <CampEngine/Graphics/Scene/Tile.h>

Tile::Tile(GLFWwindow* window, Shader shader, Texture texture, float xtile, float ytile) : Sprite(window, shader, texture, (xtile+0.5)*CE_TILE_SIZE, (ytile+0.5)*CE_TILE_SIZE, 0.0f, CE_TILE_SIZE/texture.width), RigidBody2D(PhysicsEnvironment::getInstance(), this, 10, Collidable(vertices), true) {
    CollisionsHandler::bodies.push_back(this);
}

void Tile::update(Camera camera, glm::mat4 projection) {
    RigidBody2D::step();
    
    Sprite::update(camera, projection);
}

glm::vec2 Tile::getTilePosition() {
    return glm::vec2(position.x/CE_TILE_SIZE-0.5, position.y/CE_TILE_SIZE-0.5);
}
