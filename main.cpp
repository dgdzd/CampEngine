#include <game/constants.h>
#include <game/game.h>

#include <utils/resource_manager.h>
#include <utils/logger.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <graphics/camera.h>
#include <graphics/level.h>

#include <iostream>


#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path
#define GET_SYSTEM_FONT(path) "/System/Library/Fonts/" #path

Game game;
Camera camera;

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

void onMoveRight(const Event& e) {
    auto event = e.as<InputActionEvent>();
    camera.position.x += 1.0 * event.value;
}

void onMoveUp(const Event& e) {
    auto event = e.as<InputActionEvent>();
    camera.position.y += 1.0 * event.value;
}

int main(void) {
    ResourceManager &rm = ResourceManager::standard;
    game = Game();
    game.initialize();
    
    game.actions->addInputAction("pause", GLFW_KEY_ESCAPE, 1.0f, false);
    game.actions->addInputAction("moveRight", GLFW_KEY_RIGHT, 1.0f, true);
    game.actions->addInputAction("moveRight", GLFW_KEY_LEFT, -1.0f, true);
    game.actions->addInputAction("moveUp", GLFW_KEY_UP, 1.0f, true);
    game.actions->addInputAction("moveUp", GLFW_KEY_DOWN, -1.0f, true);
    
    ADD_STATIC_LISTENER(InputActionEvent("pause"), onPause);
    ADD_STATIC_LISTENER(InputActionEvent("moveRight"), onMoveRight);
    ADD_STATIC_LISTENER(InputActionEvent("moveUp"), onMoveUp);
    
    Texture diamond_ore_texture = *rm.loadTexture("diamond_ore", GET_RESOURCE(textures/diamond_ore.png));
    Texture quartz_texture = *rm.loadTexture("quartz_pillar_top", GET_RESOURCE(textures/quartz_pillar_top.png));
    Texture button_idle_texture = *rm.loadTexture("buttonIdle", GET_RESOURCE(textures/button/idle.png));
    Texture button_hover_texture = *rm.loadTexture("buttonHover", GET_RESOURCE(textures/button/hover.png));
    
    TestScreen ts(game.window);
    camera = Camera(0.0f, 0.0f, 0.0f);
    Level level("MyLevel", camera);
    
    Shader shader = *rm.getShader("unlitShader");
    
    Tile tile(game.window, shader, diamond_ore_texture, 0, 0);
    Tile tile1(game.window, shader, diamond_ore_texture, 1, 0);
    Tile tile2(game.window, shader, quartz_texture, 0, 1);
    Tile tile3(game.window, shader, diamond_ore_texture, 1, 1);
    
    level.setActiveCamera(&camera);
    
    /* Set active screen and level */
    game.activeScreen = &ts;
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
