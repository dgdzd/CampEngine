#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
class Camera {
    public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    Camera(glm::vec3 pos);
    Camera(float x, float y, float z);
};