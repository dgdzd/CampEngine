//
//  actor.h
//  CampEngine++
//
//  Created by Noah Campagne on 01/05/2024.
//

#ifndef actor_h
#define actor_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <render/renderable.h>
#include <view/camera.h>

class Actor : Renderable {
public:
    Actor(GLFWwindow* window, float xpos, float ypos);
    
    virtual void update(Camera camera, glm::mat4 projection);
    virtual void update();
};

#endif /* actor_h */
