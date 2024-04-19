#ifndef CE_CONVERSIONS_H
#define CE_CONVERSIONS_H
#endif /* conversions_h */

#include <list>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once

template<typename T> T* listToArray(std::list<T> ls) {
    T arr[ls.size()];
    std::copy(ls.begin(), ls.end(), arr);
    return arr;
};

glm::vec3 toWorldSpace(GLFWwindow* window, glm::vec3 position);
glm::vec3 toScreenSpace(GLFWwindow* window, glm::vec3 position);
float normalizedWidth(GLFWwindow* window, int width);
float normalizedHeight(GLFWwindow* window, int height);
int getWidth(GLFWwindow* window);
int getHeight(GLFWwindow* window);

template<typename Base, typename T> bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr);
}
