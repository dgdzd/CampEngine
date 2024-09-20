#include <CampEngine/Initialize.h>

#include <CampEngine/Game/Constants.h>
#include <CampEngine/Game/Game.h>
#include <CampEngine/Game/Events/Categories/ActionEvents.h>
#include <CampEngine/Game/Events/Categories/MouseEvents.h>
#include <CampEngine/Graphics/Camera.h>
#include <CampEngine/Graphics/Level.h>
#include <CampEngine/Graphics/Shader.h>
#include <CampEngine/Graphics/Texture.h>
#include <CampEngine/Graphics/Scene/Entity.h>
#include <CampEngine/Graphics/Scene/Tile.h>
#include <CampEngine/Graphics/Screens/DebugScreen.h>
#include <CampEngine/Graphics/Screens/TestScreen.h>
#include <CampEngine/Utils/ResourceManager.h>

#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path
#define GET_SYSTEM_FONT(path) "/System/Library/Fonts/" #path

Game game;
Camera camera;
Entity* mtile;

void onPause(const Event& e) {
    auto event = e.as<InputActionEvent>();
    if(game.status == GAME_PLAYING) game.pause();
    else game.resume();
}

void onCamMoveRight(const Event& e) {
    auto event = e.as<InputActionEvent>();
    camera.position.x += 1.0f * event.value;
}

void onCamMoveUp(const Event& e) {
    auto event = e.as<InputActionEvent>();
    camera.position.y += 1.0f * event.value;
}

void onTileMoveRight(const Event& e) {
    auto event = e.as<InputActionEvent>();
    mtile->applyForce(glm::vec2(100.0f * event.value, 0.0f));
}

void onTileMoveUp(const Event& e) {
    auto event = e.as<InputActionEvent>();
    mtile->applyForce(glm::vec2(0.0f, 100.0f * event.value));
}

void onClick(const Event& e) {
    auto event = e.as<MouseClickEvent>();
    Entity* etile = new Entity(game.window, *ResourceManager::standard.getShader("unlitShader"), *ResourceManager::standard.getTexture("diamond_ore"), event.mouseX, CE_WINDOW_HEIGHT-event.mouseY, 4);
    Level::active->addObject(etile);
}

int main() {
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
    ADD_STATIC_LISTENER(MouseClickEvent(), onClick);
    
    Texture diamond_ore_texture = *rm.loadTexture("diamond_ore", GET_RESOURCE(textures/diamond_ore.png));
    Texture quartz_texture = *rm.loadTexture("quartz_pillar_top", GET_RESOURCE(textures/quartz_pillar_top.png));
    Texture button_idle_texture = *rm.loadTexture("buttonIdle", GET_RESOURCE(textures/button/idle.png));
    Texture button_hover_texture = *rm.loadTexture("buttonHover", GET_RESOURCE(textures/button/hover.png));
    Texture marker_texture = *rm.loadTexture("marker", GET_RESOURCE(textures/marker.png));
    
    TestScreen ts(game.window);
    DebugScreen ds(game.window);
    camera = Camera(0.0f, 0.0f, 0.0f);
    Level* level = rm.loadLevel("MyLevel", camera);
    
    const Shader shader = *rm.getShader("unlitShader");
    
    mtile = new Entity(game.window, shader, diamond_ore_texture, 500, 640, 4);
    mtile->rotation = 45;
    level->addObject(new Tile(game.window, shader, quartz_texture, 0, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 0, 1));
    level->addObject(new Tile(game.window, shader, quartz_texture, 1, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 2, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 3, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 4, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 5, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 6, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 7, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 8, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 9, 0));
    level->addObject(new Tile(game.window, shader, quartz_texture, 9, 1));
    level->addObject(new Entity(game.window, shader, quartz_texture, 700, 200, 5, 5, true, false));
    
    level->addObject(mtile);
    
    /* Set active screen and level */
    game.activeScreen = &ds;
    game.activeLevel = level;
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
