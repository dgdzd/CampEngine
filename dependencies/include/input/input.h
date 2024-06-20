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
    std::map<std::string, std::map<int, float>> inputActions;
    std::map<std::string, int, float> axisActions;
};

#endif /* input_h */
