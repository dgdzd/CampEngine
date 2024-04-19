#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utils/filereader.h>
#include <shaders/shader.h>
#include <textures/texture.h>
#include <view/camera.h>
#include <view/level.h>

#include <iostream>

const char* WINDOW_TITLE = "Hello World";
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;

const char* vertexShaderSource = getFileContent("resources/shaders/vertexShader.glsl");
const char* fragmentShaderSource = getFileContent("resources/shaders/fragmentShader.glsl");

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Camera &camera) {
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera.position.x += 0.05;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera.position.x -= 0.05;
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.position.y += 0.05;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.position.y -= 0.05;
    }
}

int main(void) {
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Checks if GLAD loaded well */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    /* Initializes the viewport */
    glViewport(0, 0, 640, 640);

    /* Update the viewport size when window is resized */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Setting up the objects */
    Shader shader("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");
    Texture texture("resources/textures/quartz_pillar_top.png");
    Camera camera(0.0f, 0.0f, 0.0f);
    Level level("MyLevel", camera);
    Sprite sprite(window, shader, texture, 0.0f, 0.0f, 1.0f);
    level.addObject(sprite);
    level.activeCamera = camera;

    /* Texture options */
    texture.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* The window loop */
    while(!glfwWindowShouldClose(window)) {
        /* Input */
        processInput(window, camera);

        /* Rendering functions here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Render the entire level */
        level.render();

        /* Events and buffer swap */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
