//
//  input.h
//  CampEngine++
//
//  Created by Noah Campagne on 01/05/2024.
//

#ifndef CE_INPUT_H
#define CE_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <CampEngine/Game/Events/EventHandler.h>

#include <map>
#include <vector>
#include <string>

class InputAction {
public:
    InputAction(int key, float value, bool isContinuous);
    
    int key;
    float value;
    bool isContinuous;
};

class ActionMapper {
private:
    std::map<std::string, std::vector<InputAction>> inputActions;
    std::map<std::string, std::pair<int, float>> axisActions;
    std::vector<InputAction> activeKeys;
    
public:
    ActionMapper();
    
    void update();
    void onKeyPress(const Event& e);
    void onKeyRelease(const Event& e);
    
    void addInputAction(std::string name, int input, float scale, bool isContinuous);
    void addAxisAction(std::string name, int axis, float scale, bool isContinuous);
    
    void removeInputAction(std::string name, int input);
    void removeAxisAction(std::string name);
    
    
};

#endif
