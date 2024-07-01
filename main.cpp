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
    mtile->applyForce(glm::vec2(100.0f * event.value, 0.0f));
}

void onTileMoveUp(const Event& e) {
    auto event = e.as<InputActionEvent>();
    mtile->applyForce(glm::vec2(0.0f, 100.0f * event.value));
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
    Texture marker_texture = *rm.loadTexture("marker", GET_RESOURCE(textures/marker.png));
    
    TestScreen ts(game.window);
    DebugScreen ds(game.window);
    camera = Camera(0.0f, 0.0f, 0.0f);
    Level level("MyLevel", camera);
    
    Shader shader = *rm.getShader("unlitShader");
    
    mtile = new Entity(game.window, shader, diamond_ore_texture, 640, 640, 4);
//    Entity* etile = new Entity(game.window, shader, diamond_ore_texture, 352, 544, 4);
    Entity* etile1 = new Entity(game.window, shader, diamond_ore_texture, 340, 400, 4);
    level.addObject(new Tile(game.window, shader, quartz_texture, 0, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 0, 1));
    level.addObject(new Tile(game.window, shader, quartz_texture, 1, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 2, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 3, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 4, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 5, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 6, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 7, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 8, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 9, 0));
    level.addObject(new Tile(game.window, shader, quartz_texture, 9, 1));
    
    level.addObject(mtile);
//    level.addObject(etile);
    level.addObject(etile1);
    
    level.setActiveCamera(&camera);
    
    /* Set active screen and level */
    game.activeScreen = &ds;
    game.activeLevel = &level;
    Level::active = game.activeLevel;

    /* Textures options */
    diamond_ore_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    quartz_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    button_idle_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    button_hover_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    marker_texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* The window loop */
    while(!glfwWindowShouldClose(game.window)) {
        game.update();
    }

    glfwTerminate();
    return 0;
}
