#ifndef CE_RENDERABLE_H
#define CE_RENDERABLE_H

#include <game/constants.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <textures/texture.h>
#include <shaders/shader.h>
#include <view/camera.h>
#include <utils/conversions.h>

#include <list>
#include <vector>

const int TILE_SIZE = 32;

class Renderable {
public:
    unsigned int VBO, VAO, EBO;
    GLFWwindow* window;
    Texture texture;
    Shader shader;
    glm::vec3 transform;
    glm::vec4 color;
    std::vector<float> vertices;
    std::vector<int> indices;
    
    Renderable(GLFWwindow* window, std::vector<float> vertices, std::vector<int> indices, Texture texture, Shader shader, glm::vec3 transform);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale);

    virtual void update(Camera camera, glm::mat4 projection);
    virtual void update();
    void render(Camera camera, glm::mat4 projection);
    void render(glm::mat4 projection);
    void render();
    
    
private:
    void gen_buffers();
};

class Sprite : public Renderable {
public:
    glm::vec3 position;
    Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float zpos, float scale);
    Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec3 position, float scale);
};

class Tile : public Sprite {
public:
    glm::vec2 tilePosition;
    
    Tile(GLFWwindow* window, Shader shader, Texture texture, float xtile, float ytile);
    Tile(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 tilePosition);
};

class Decoration : public Sprite {
    // TODO
};

class Particle : public Sprite {
    // TODO
};

class Entity : public Sprite {
public:
    glm::vec2 velocity;
    glm::vec2 acceleration;

    Entity(Shader shader, Texture texture, float xpos, float ypos, float xvel=0.0f, float yvel=0.0f, float xaccel=0.0f, float yaccel=0.0f);
    Entity(Shader shader, Texture texture, glm::vec2 position, glm::vec2 velocity=glm::vec2(0.0f), glm::vec2 acceleration=glm::vec2(0.0f));
};

#endif
