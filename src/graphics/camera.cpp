#include <graphics/camera.h>

Camera::Camera() {
    position = glm::vec3(0.0f);
}

Camera::Camera(glm::vec3 pos) {
    position = pos;
};

Camera::Camera(float x, float y, float z) {
    position = glm::vec3(x, y, z);
};
