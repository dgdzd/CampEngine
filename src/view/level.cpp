#include <view/level.h>

Level::Level(const char* name, Camera &activeCamera) : activeCamera(activeCamera) {
    this->name = name;
}

void Level::render() {
    for(int i = 0; i < objects.size(); i++) {
        objects.at(i).render(activeCamera);
    }
}

void Level::addObject(Renderable obj) {
    objects.push_back(obj);
}

void Level::removeObject(int index) {
    objects.erase(objects.begin() + index);
}
