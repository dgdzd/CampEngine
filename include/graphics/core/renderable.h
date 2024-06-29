#ifndef CE_RENDERABLE_H
#define CE_RENDERABLE_H

#include <game/constants.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <graphics/texture.h>
#include <graphics/shader.h>
#include <graphics/camera.h>

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
    glm::vec3 rotation;
    glm::vec4 color;
    std::vector<float> vertices;
    std::vector<int> indices;
    bool enabled;
    
    Renderable(GLFWwindow* window, std::vector<float> vertices, std::vector<int> indices, Texture texture, Shader shader, glm::vec3 transform, glm::vec3 rotation);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale);
    Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, float xrot, float yrot, float zrot);

    virtual void update(Camera camera, glm::mat4 projection);
    virtual void update();
    void render(Camera camera, glm::mat4 projection);
    void render(glm::mat4 projection);
    void render();
    
    
private:
    void gen_buffers();
};

#endif
