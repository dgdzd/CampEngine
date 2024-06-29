#include <game/constants.h>
#include <game/game.h>

#include <utils/resource_manager.h>
#include <utils/logger.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <graphics/camera.h>
#include <graphics/level.h>
#include <graphics/render/tile.h>
#include <graphics/render/entity.h>

#include <iostream>
#include <memory>


#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path
#define GET_SYSTEM_FONT(path) "/System/Library/Fonts/" #path

Game game;
Camera camera;
Entity* mtile;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Game::activeGame->projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    Game::activeGame->frame = {
        CE_WINDOW_WIDTH,
        CE_WINDOW_HEIGHT
    };
}

void onPause(const Event& e) {
    auto event = e.as<InputActionEvent>();
    if(game.status == GAME_PLAYING) game.pause();
    else game.resume();
}

void onCamMoveRight(const Event& e) {
    auto event = e.as<InputActionEvent>();
    camera.position.x += 1.0 * event.value;
}

void onCamMoveUp(const Event& e) {
    auto event = e.as<InputActionEvent>();
    camera.position.y += 1.0 * event.value;
}

void onTileMoveRight(const Event& e) {
    auto event = e.as<InputActionEvent>();
    mtile->applyForce(glm::vec2(240.0f * event.value, 0.0f));
}

void onTileMoveUp(const Event& e) {
    auto event = e.as<InputActionEvent>();
    mtile->applyForce(glm::vec2(0.0f, 240.0f * event.value));
}

int main(void) {
    ResourceManager &rm = ResourceManager::standard;
    game = Game();
    game.initialize();
    
    game.actions->addInputAction("pause", GLFW_KEY_ESCAPE, 1.0f, false);
    game.actions->addInputAction("tile_moveRight", GLFW_KEY_RIGHT, 1.0f, true);
    game.actions->addInputAction("tile_moveRight", GLFW_KEY_LEFT, -1.0f, true);
    game.actions->addInputAction("tile_moveUp", GLFW_KEY_UP, 1.0f, true);
    game.actions->addInputAction("tile_moveUp", GLFW_KEY_DOWN, -1.0f, true);
//    game.actions->addInputAction("camera_moveRight", GLFW_KEY_RIGHT, 1.0f, true);
//    game.actions->addInputAction("camera_moveRight", GLFW_KEY_LEFT, -1.0f, true);
//    game.actions->addInputAction("camera_moveUp", GLFW_KEY_UP, 1.0f, true);
//    game.actions->addInputAction("camera_moveUp", GLFW_KEY_DOWN, -1.0f, true);
    
    
    ADD_STATIC_LISTENER(InputActionEvent("pause"), onPause);
    ADD_STATIC_LISTENER(InputActionEvent("camera_moveRight"), onCamMoveRight);
    ADD_STATIC_LISTENER(InputActionEvent("camera_moveUp"), onCamMoveUp);
    ADD_STATIC_LISTENER(InputActionEvent("tile_moveRight"), onTileMoveRight);
    ADD_STATIC_LISTENER(InputActionEvent("tile_moveUp"), onTileMoveUp);
    
    Texture diamond_ore_texture = *rm.loadTexture("diamond_ore", GET_RESOURCE(textures/diamond_ore.png));
    Texture quartz_texture = *rm.loadTexture("quartz_pillar_top", GET_RESOURCE(textures/quartz_pillar_top.png));
    Texture button_idle_texture = *rm.loadTexture("buttonIdle", GET_RESOURCE(textures/button/idle.png));
    Texture button_hover_texture = *rm.loadTexture("buttonHover", GET_RESOURCE(textures/button/hover.png));
    
    TestScreen ts(game.window);
    DebugScreen ds(game.window);
    camera = Camera(0.0f, 0.0f, 0.0f);
    Level level("MyLevel", camera);
    
    Shader shader = *rm.getShader("unlitShader");
    
    mtile = new Entity(game.window, shader, diamond_ore_texture, 640, 640, 4, false);
    Entity* tile = new Entity(game.window, shader, quartz_texture, 352, 544, 4);
    Tile* tile1 = new Tile(game.window, shader, quartz_texture, 1, 0);
    Tile* tile2 = new Tile(game.window, shader, quartz_texture, 2, 0);
    Tile* tile3 = new Tile(game.window, shader, quartz_texture, 3, 0);
    Tile* tile4 = new Tile(game.window, shader, quartz_texture, 4, 0);
    Tile* tile5 = new Tile(game.window, shader, quartz_texture, 5, 0);
    Tile* tile6 = new Tile(game.window, shader, quartz_texture, 6, 0);
    
    std::shared_ptr<Entity> mtile_ = std::shared_ptr<Entity>(mtile);
    std::shared_ptr<Entity> tile_ = std::shared_ptr<Entity>(tile);
    std::shared_ptr<Tile> tile1_ = std::shared_ptr<Tile>(tile1);
    std::shared_ptr<Tile> tile2_ = std::shared_ptr<Tile>(tile2);
    std::shared_ptr<Tile> tile3_ = std::shared_ptr<Tile>(tile3);
    std::shared_ptr<Tile> tile4_ = std::shared_ptr<Tile>(tile4);
    std::shared_ptr<Tile> tile5_ = std::shared_ptr<Tile>(tile5);
    std::shared_ptr<Tile> tile6_ = std::shared_ptr<Tile>(tile6);
    
    level.addObject(mtile_);
    level.addObject(tile_);
    level.addObject(tile1_);
    level.addObject(tile2_);
    level.addObject(tile3_);
    level.addObject(tile4_);
    level.addObject(tile5_);
    level.addObject(tile6_);
    level.setActiveCamera(&camera);
    
    /* Set active screen and level */
    game.activeScreen = &ds;
    game.activeLevel = &level;

    /* Textures options */
    diamond_ore_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    button_idle_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    button_hover_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* The window loop */
    while(!glfwWindowShouldClose(game.window)) {
        game.update();
    }

    glfwTerminate();
    return 0;
}
