#include <render/renderable.h>

Renderable::Renderable(GLFWwindow* window, std::list<float> vertices, std::list<int> indices, Texture texture, Shader shader, glm::vec3 transform) : texture(texture), shader(shader), transform(transform) {
    this->window = window;
    this->vertices = vertices;
    this->texture = texture;
    this->shader = shader;
    this->transform = transform;
    
    float* arr_vertices = listToArray(vertices);
    int* arr_indices = listToArray(indices);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr_vertices), arr_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arr_indices), arr_indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderable::render(Camera camera) {
    shader.use();
    shader.setVec3("camera.position", camera.position);
    shader.setVec3("object.position", transform);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
}

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale) {
    glm::vec2 texSizes(static_cast<float>(texture.width), static_cast<float>(texture.height));
    int width, height;
    float aWidth, aHeight;
    glfwGetWindowSize(window, &width, &height);
    aWidth = texture.width / width;
    aHeight = texture.height / height;
    
    this->vertices = {
        // position                           // Texture coordinates
        -(aWidth/2)*scale, -(aHeight/2)*scale, 0.0f, 0.0f, // Bottom-left
        (aWidth/2)*scale, -(aHeight/2)*scale, 0.0f, 1.0f, // Bottom-right
        (aWidth/2)*scale, (aHeight/2)*scale, 1.0f, 1.0f, // Top-right
        -(aWidth/2)*scale, (aHeight/2)*scale, 1.0f, 0.0f, // Top-left
    };

    this->indices = {
        2, 1, 3,
        1, 0, 3
    };
}

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec2 position, float scale) {
    glm::vec2 texSizes(static_cast<float>(texture.width), static_cast<float>(texture.height));
    int width, height;
    float aWidth, aHeight;
    glfwGetWindowSize(window, &width, &height);
    aWidth = texture.width / width;
    aHeight = texture.height / height;
    
    vertices = {
        // position               // Texture coordinates
        -(aWidth/2)*scale, -(aHeight/2)*scale, 0.0f, 0.0f, // Bottom-left
        (aWidth/2)*scale, -(aHeight/2)*scale, 1.0f, 0.0f, // Bottom-right
        (aWidth/2)*scale, (aHeight/2)*scale, 1.0f, 1.0f, // Top-right
        -(aWidth/2)*scale, (aHeight/2)*scale, 0.0f, 1.0f, // Top-left
    };

    indices = {
        0, 1, 2,
        3, 0, 1
    };
}
