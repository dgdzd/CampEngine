#ifndef CE_RENDERABLE_H
#define CE_RENDERABLE_H

#include <CampEngine/Game/Constants.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <CampEngine/Graphics/Camera.h>
#include <CampEngine/Graphics/Shader.h>
#include <CampEngine/Graphics/Texture.h>

#include <list>
#include <vector>

constexpr int TILE_SIZE = 32;

enum AnchorPoint {
    TOP_LEFT, TOP, TOP_RIGHT,
    LEFT, CENTER, RIGHT,
    BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT
};

class Renderable {
public:
    unsigned int VBO, VAO, EBO;
    GLFWwindow* window;
    Texture texture;
    Shader shader;
    AnchorPoint anchor;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec4 color;
    std::vector<float> vertices;
    std::vector<int> indices;
    bool enabled;
    long index;
    
    Renderable(GLFWwindow* window, std::vector<float> vertices, std::vector<int> indices, Texture texture, Shader shader, glm::vec3 transform, glm::vec3 rotation);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, AnchorPoint anchor=CENTER);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, AnchorPoint anchor=CENTER);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, float xrot, float yrot, float zrot, AnchorPoint anchor=CENTER);

    virtual void update(Camera camera, glm::mat4 projection);
    virtual void update();
    void render(Camera camera, glm::mat4 projection);
    void render(glm::mat4 projection);
    void render();

    template<typename T>
    T* as() {
        return dynamic_cast<T*>(this);
    }
    
    
private:
    void gen_buffers();
    void gen_vertices();
};

#endif
