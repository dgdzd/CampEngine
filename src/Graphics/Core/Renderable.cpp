#include <CampEngine/Graphics/Core/Renderable.h>

#include <glm/gtc/matrix_transform.hpp>

/*---- Forward Declaration ----*/
class Game;
/*-----------------------------*/

Renderable::Renderable(GLFWwindow* window, std::vector<float> vertices, std::vector<int> indices, Texture texture, Shader shader, glm::vec3 transform, glm::vec3 rotation) : texture(texture), shader(shader), transform(transform), rotation(rotation) {
    this->enabled = true;
    this->window = window;
    this->vertices = vertices;
    this->texture = texture;
    this->shader = shader;
    this->transform = transform;
    this->rotation = rotation;
    this->scale = glm::vec3(1.0f);

    gen_buffers();
}

Renderable::Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, float xrot, float yrot, float zrot, AnchorPoint anchor) : shader(shader), texture(texture) {
    this->enabled = true;
    this->window = window;
    this->anchor = anchor;
    this->transform = glm::vec3(xpos, ypos, 0.0f);
    this->rotation = glm::vec3(xrot, yrot, zrot);
    this->scale = glm::vec3(xscale, yscale, 1.0f);

    gen_vertices();
    gen_buffers();
}

Renderable::Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale, AnchorPoint anchor) : Renderable(window, shader, texture, xpos, ypos, xscale, yscale, 0, 0, 0) {
    
}

Renderable::Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale, AnchorPoint anchor) : Renderable(window, shader, texture, xpos, ypos, scale, scale) {
    
}

void Renderable::update(Camera camera, glm::mat4 projection) {
    if(this->enabled && this->shader.id != -1) this->render(camera, projection);
}

void Renderable::update() {
    if(this->enabled && this->shader.id != -1) this->render();
}

void Renderable::render(Camera camera, glm::mat4 projection) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, transform - camera.position);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("projection", projection);
    shader.setInt("aTexture", 0);
    shader.setVec4("color", color);
    glActiveTexture(GL_TEXTURE0);
    texture.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderable::render(glm::mat4 projection) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, transform);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("projection", projection);
    shader.setInt("aTexture", 0);
    shader.setVec4("color", color);
    glActiveTexture(GL_TEXTURE0);
    texture.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderable::render() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, transform);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    
    shader.use();
    shader.setMat4("model", model);
    shader.setMat4("projection", projection);
    shader.setInt("aTexture", 0);
    shader.setVec4("color", color);
    glActiveTexture(GL_TEXTURE0);
    texture.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderable::gen_buffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Texture coordinates attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderable::gen_vertices() {
    switch(anchor) {
        case TOP_LEFT: {
            float w = texture.width;
            float h = texture.height;
            this->vertices = {
                // position     // Texture coordinates
                0, -h, 0.0f, 0.0f, 0.0f, // Bottom-left
                w, -h, 0.0f, 1.0f, 0.0f, // Bottom-right
                w, 0, 0.0f, 1.0f, 1.0f, // Top-right
                0, 0, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case TOP: {
            float halfw = texture.width/2;
            float h = texture.height;
            this->vertices = {
                // position     // Texture coordinates
                -halfw, -h, 0.0f, 0.0f, 0.0f, // Bottom-left
                halfw, -h, 0.0f, 1.0f, 0.0f, // Bottom-right
                halfw, 0, 0.0f, 1.0f, 1.0f, // Top-right
                -halfw, 0, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case TOP_RIGHT: {
            float w = texture.width;
            float h = texture.height;
            this->vertices = {
                // position     // Texture coordinates
                -w, -h, 0.0f, 0.0f, 0.0f, // Bottom-left
                0, -h, 0.0f, 1.0f, 0.0f, // Bottom-right
                0, 0, 0.0f, 1.0f, 1.0f, // Top-right
                -w, 0, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case LEFT: {
            float w = texture.width;
            float halfh = texture.height/2;
            this->vertices = {
                // position     // Texture coordinates
                0, -halfh, 0.0f, 0.0f, 0.0f, // Bottom-left
                w, -halfh, 0.0f, 1.0f, 0.0f, // Bottom-right
                w, halfh, 0.0f, 1.0f, 1.0f, // Top-right
                0, halfh, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case CENTER: {
            float halfw = texture.width/2;
            float halfh = texture.height/2;
            this->vertices = {
                // position     // Texture coordinates
                -halfw, -halfh, 0.0f, 0.0f, 0.0f, // Bottom-left
                halfw, -halfh, 0.0f, 1.0f, 0.0f, // Bottom-right
                halfw, halfh, 0.0f, 1.0f, 1.0f, // Top-right
                -halfw, halfh, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case RIGHT: {
            float w = texture.width;
            float halfh = texture.height/2;
            this->vertices = {
                // position     // Texture coordinates
                -w, -halfh, 0.0f, 0.0f, 0.0f, // Bottom-left
                0, -halfh, 0.0f, 1.0f, 0.0f, // Bottom-right
                0, halfh, 0.0f, 1.0f, 1.0f, // Top-right
                -w, halfh, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case BOTTOM_LEFT: {
            float w = texture.width;
            float h = texture.height;
            this->vertices = {
                // position     // Texture coordinates
                0, 0, 0.0f, 0.0f, 0.0f, // Bottom-left
                w, 0, 0.0f, 1.0f, 0.0f, // Bottom-right
                w, h, 0.0f, 1.0f, 1.0f, // Top-right
                0, h, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case BOTTOM: {
            float halfw = texture.width/2;
            float h = texture.height;
            this->vertices = {
                // position     // Texture coordinates
                -halfw, 0, 0.0f, 0.0f, 0.0f, // Bottom-left
                halfw, 0, 0.0f, 1.0f, 0.0f, // Bottom-right
                halfw, h, 0.0f, 1.0f, 1.0f, // Top-right
                -halfw, h, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
        case BOTTOM_RIGHT: {
            float w = texture.width;
            float h = texture.height;
            this->vertices = {
                // position     // Texture coordinates
                -w, 0, 0.0f, 0.0f, 0.0f, // Bottom-left
                0, 0, 0.0f, 1.0f, 0.0f, // Bottom-right
                0, h, 0.0f, 1.0f, 1.0f, // Top-right
                -w, h, 0.0f, 0.0f, 1.0f, // Top-left
            };
            break;
        }
    }

    this->indices = {
        2, 1, 3,
        1, 0, 3
    };
}

