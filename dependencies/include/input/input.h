//
//  input.h
//  CampEngine++
//
//  Created by Noah Campagne on 01/05/2024.
//

#ifndef input_h
#define input_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>
#include <string>

class ActionMapper {
private:
    std::map<std::string, std::map<int, float>> inputActions;
    std::map<std::string, std::pair<int, float>> axisActions;
    
public:
    ActionMapper() = default;
    
    void addInputAction(std::string name, int input, float scale);
    void addAxisAction(std::string name, int axis, float scale);
    
    void removeInputAction(std::string, int input, float scale);
    void removeAxisAction(std::string, int axis, float scale);
    
    
};

#endif
