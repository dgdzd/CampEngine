#ifndef CE_LEVEL_H
#define CE_LEVEL_H

#include <glm/glm.hpp>

#include <CampEngine/Graphics/Camera.h>
#include <CampEngine/Graphics/Core/Renderable.h>

#include <memory>
#include <vector>

class Level {
public:
    std::string name;
    std::vector<std::shared_ptr<Renderable>> objects;
    Camera* activeCamera;
    static Level* active;

    Level() = default;
    Level(std::string name, Camera &activeCamera);
    
    void update(glm::mat4 projection);
    void render(glm::mat4 projection);
    void addObject(Renderable* obj);
    void removeObject(long index);
    void removeObject(Renderable* obj);
    void setActiveCamera(Camera* newCamera);
    Camera* getActiveCamera();
};

#endif
