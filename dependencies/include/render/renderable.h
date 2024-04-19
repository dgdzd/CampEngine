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

class Renderable {
    public:
    unsigned int VBO, VAO, EBO;
    GLFWwindow* window;
    Texture texture;
    Shader shader;
    glm::vec3 transform;
    std::list<float> vertices;
    std::list<int> indices;

    Renderable(GLFWwindow* window, std::list<float> vertices, std::list<int> indices, Texture texture, Shader shader, glm::vec3 transform);

    void render(Camera camera);
    
    protected:
    Renderable();
};

class Sprite : public Renderable {
    public:
    glm::vec2 position;
    Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale);
    Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 position, float scale);
};

class Tile : public Sprite {
    public:

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
