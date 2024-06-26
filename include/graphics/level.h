#ifndef CE_LEVEL_H
#define CE_LEVEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <graphics/core/renderable.h>
#include <graphics/camera.h>

#include <vector>

class Level {
public:
    const char* name;
    std::vector<Renderable> objects;
    Camera* activeCamera;

    Level(const char* name, Camera &activeCamera);
    
    void update(glm::mat4 projection);
    void render(glm::mat4 projection);
    void addObject(Renderable obj);
    void removeObject(int index);
    void setActiveCamera(Camera* newCamera);
    Camera* getActiveCamera();
};

#endif
