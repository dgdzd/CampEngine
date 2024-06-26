#include <graphics/core/renderable.h>

/*---- Forward Declaration ----*/
class Game;
/*-----------------------------*/

Renderable::Renderable(GLFWwindow* window, std::vector<float> vertices, std::vector<int> indices, Texture texture, Shader shader, glm::vec3 transform) : texture(texture), shader(shader), transform(transform) {
    this->window = window;
    this->vertices = vertices;
    this->texture = texture;
    this->shader = shader;
    this->transform = transform;

    gen_buffers();
}

Renderable::Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float xscale, float yscale) : shader(shader), texture(texture) {
    this->transform = glm::vec3(xpos, ypos, 0.0f);
    this->vertices = {
        // position                                 // Texture coordinates
        -texture.width/2*xscale, -texture.height/2*yscale, 0.0f, 0.0f, 0.0f, // Bottom-left
        texture.width/2*xscale, -texture.height/2*yscale, 0.0f, 1.0f, 0.0f, // Bottom-right
        texture.width/2*xscale, texture.height/2*yscale, 0.0f, 1.0f, 1.0f, // Top-right
        -texture.width/2*xscale, texture.height/2*yscale, 0.0f, 0.0f, 1.0f, // Top-left
    };

    this->indices = {
        2, 1, 3,
        1, 0, 3
    };
    
    gen_buffers();
}

Renderable::Renderable(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float scale) : Renderable(window, shader, texture, xpos, ypos, scale, scale) {
    
}

void Renderable::update(Camera camera, glm::mat4 projection) {
    this->render(camera, projection);
}

void Renderable::update() {
    this->render();
}

void Renderable::render(Camera camera, glm::mat4 projection) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, transform - camera.position);
    
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

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, float xpos, float ypos, float zpos, float scale) : Renderable(window, shader, texture, xpos, ypos, scale) {
    this->position = glm::vec3(xpos, ypos, zpos);
}

Sprite::Sprite(GLFWwindow* window, Shader shader, Texture texture, glm::vec3 position, float scale) : Sprite(window, shader, texture, position.x, position.y, position.z, scale) {
    this->position = position;
}

Tile::Tile(GLFWwindow* window, Shader shader, Texture texture, float xtile, float ytile) : Sprite(window, shader, texture, (xtile+0.5)*CE_TILE_SIZE, (ytile+0.5)*CE_TILE_SIZE, 0.0f, CE_TILE_SIZE/texture.width) {
    this->tilePosition = glm::vec2(xtile, ytile);
    //Game::activeGame->activeLevel->addObject(this);
}
