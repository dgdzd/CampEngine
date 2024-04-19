#include <render/renderable.h>
#include <view/camera.h>
#include <vector>

class Level {
    public:
    const char* name;
    std::vector<Renderable> objects;
    Camera activeCamera;

    Level(const char* name, Camera &activeCamera);

    void render();
    void addObject(Renderable obj);
    void removeObject(int index);
};
