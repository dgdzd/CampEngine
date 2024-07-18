#include <CampEngine/Graphics/Level.h>

Level* Level::active;

Level::Level(const char* name, Camera &activeCamera) : activeCamera(&activeCamera) {
    this->name = name;
}

void Level::update(glm::mat4 projection) {
    this->render(projection);
}

void Level::render(glm::mat4 projection) {
    for(int i = 0; i < objects.size(); i++) {
        if(objects.at(i).get()) {
            objects.at(i).get()->update(*activeCamera, projection);
        }
    }
}

void Level::addObject(Renderable* obj) {
    std::shared_ptr<Renderable> ptr = std::shared_ptr<Renderable>(obj);
    obj->index = objects.size();
    objects.push_back(ptr);
}

void Level::removeObject(long index) {
    objects.erase(objects.begin() + index);
    
    for(long i = index; i < objects.size(); i++) {
        objects[i].get()->index--;
    }
}

void Level::removeObject(Renderable* obj) {
    objects.erase(std::find(objects.begin(), objects.end(), std::shared_ptr<Renderable>(obj)));
}

void Level::setActiveCamera(Camera *newCamera) {
    this->activeCamera = newCamera;
}

Camera* Level::getActiveCamera() {
    return this->activeCamera;
}
