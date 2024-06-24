#include <game/constants.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <utils/filereader.h>
#include <utils/resource_manager.h>
#include <utils/logger.h>
#include <shaders/shader.h>
#include <textures/texture.h>
#include <view/camera.h>
#include <view/level.h>
#include <game/game.h>
#include <render/text/text_renderer.h>

#include <iostream>


#define GET_RESOURCE(path) "/Applications/projets/projets_programmation/projets_C++/CampEngine++/resources/" #path
#define GET_SYSTEM_FONT(path) "/System/Library/Fonts/" #path

FT_Library lib;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Game::activeGame->projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    Game::activeGame->frame = {
        CE_WINDOW_WIDTH,
        CE_WINDOW_HEIGHT
    };
}

void processInput(GLFWwindow* window, Camera &camera) {
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera.position.x += 1.0;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera.position.x -= 1.0;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.position.y += 1.0;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.position.y -= 1.0;
    }
}

int init() {
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_DECORATED, false);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    if (FT_Init_FreeType(&lib)) {
        Logger::CampEngine.error("Failed to initialize FreeType Library");
        return -1;
    }

    return 0;
}

int main(void) {
    TextRenderer tr(&lib);
    if(init() != 0) {
        return -1;
    }
    
    /* Create a window and it's OpenGL context */
    GLFWwindow* window = glfwCreateWindow(CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT, CE_WINDOW_TITLE, glfwGetPrimaryMonitor(), NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Checks if GLAD loaded well */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::CampEngine.error("Failed to initialize GLAD");
        return -1;
    }  

    /* Initializes the viewport */
    glViewport(0, 0, CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);

    /* Update the viewport size when window is resized */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    /* Loading font */
    tr.loadFont(GET_RESOURCE(fonts/helveticaLight.ttf), 48);

    /* Setting up the objects */
    ResourceManager &rm = ResourceManager::standard;
    Shader shader = *rm.loadShader("unlitShader", GET_RESOURCE(shaders/unlitShader.vs), GET_RESOURCE(shaders/unlitShader.fs));
    rm.loadShader("litShader", GET_RESOURCE(shaders/lit/defaultLitShader.vs), GET_RESOURCE(shaders/lit/defaultLitShader.fs));
    rm.loadShader("text", GET_RESOURCE(shaders/text.vs), GET_RESOURCE(shaders/text.fs));
    
    /* Loading post-processing effect shaders */
    rm.loadShader("pp.none", GET_RESOURCE(shaders/screen/screen.vs), GET_RESOURCE(shaders/screen/screen.fs));
    rm.loadShader("pp.reverse_colors", GET_RESOURCE(shaders/screen/screen.vs), GET_RESOURCE(shaders/screen/post_processing/reverse_colors.fs));
    rm.loadShader("pp.grayscale", GET_RESOURCE(shaders/screen/screen.vs), GET_RESOURCE(shaders/screen/post_processing/grayscale.fs));
    
    rm.loadPostProcessor("basic", *rm.getShader("pp.none"), CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);
    rm.loadPostProcessor("reverse_colors", *rm.getShader("pp.reverse_colors"), CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);
    rm.loadPostProcessor("grayscale", *rm.getShader("pp.grayscale"), CE_WINDOW_WIDTH, CE_WINDOW_HEIGHT);
    
    /* Loading widget shader */
    rm.loadShader("widget", GET_RESOURCE(shaders/widget/widget.vs), GET_RESOURCE(shaders/widget/widget.fs));
    
    Texture diamond_ore_texture = *rm.loadTexture("diamond_ore", GET_RESOURCE(textures/diamond_ore.png));
    Texture quartz_texture = *rm.loadTexture("quartz_pillar_top", GET_RESOURCE(textures/quartz_pillar_top.png));
    Texture button_idle_texture = *rm.loadTexture("buttonIdle", GET_RESOURCE(textures/button/idle.png));
    Texture button_hover_texture = *rm.loadTexture("buttonHover", GET_RESOURCE(textures/button/hover.png));
    
    TestScreen ts(window);
    
    Camera camera(0.0f, 0.0f, 0.0f);
    
    Level level("MyLevel", camera);
    
    Game game(window, &ts, &level, GAME_MENU);
    game.tr = &tr;
    game.actions.addInputAction("pause", GLFW_KEY_ESCAPE, 1.0);
    
    TextRenderer::common = &tr;
    
    Tile tile(window, shader, diamond_ore_texture, 0, 0);
    Tile tile1(window, shader, diamond_ore_texture, 1, 0);
    Tile tile2(window, shader, quartz_texture, 0, 1);
    Tile tile3(window, shader, diamond_ore_texture, 1, 1);
    
    level.addObject(tile);
    level.addObject(tile1);
    level.addObject(tile2);
    level.addObject(tile3);
    level.setActiveCamera(&camera);

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
    while(!glfwWindowShouldClose(window)) {
        processInput(window, camera);
        
        game.update();
    }

    glfwTerminate();
    return 0;
}
