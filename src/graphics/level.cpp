#include <graphics/level.h>

Level::Level(const char* name, Camera &activeCamera) : activeCamera(&activeCamera) {
    this->name = name;
}

void Level::update(glm::mat4 projection) {
    this->render(projection);
}

void Level::render(glm::mat4 projection) {
    for(int i = 0; i < objects.size(); i++) {
        objects.at(i).update(*activeCamera, projection);
    }
}

void Level::addObject(Renderable obj) {
    objects.push_back(obj);
}

void Level::removeObject(int index) {
    objects.erase(objects.begin() + index);
}

void Level::setActiveCamera(Camera *newCamera) {
    this->activeCamera = newCamera;
}

Camera* Level::getActiveCamera() {
    return this->activeCamera;
}
