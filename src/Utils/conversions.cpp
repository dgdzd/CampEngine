#include <CampEngine/Utils/conversions.h>

glm::vec3 toWorldSpace(GLFWwindow* window, glm::vec3 position) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    position.x *= width;
    position.y *= height;
    
    return position;
}

glm::vec3 toScreenSpace(GLFWwindow* window, glm::vec3 position) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    position.x /= width;
    position.y /= height;
    
    return position;
}

float normalizedWidth(GLFWwindow* window, int width) {
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    
    return width / static_cast<float>(w);
}

float normalizedHeight(GLFWwindow* window, int height) {
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    
    return height / static_cast<float>(h);
}

int getWidth(GLFWwindow* window) {
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    
    return w;
}

int getHeight(GLFWwindow* window) {
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    
    return h;
}
