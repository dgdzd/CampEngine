//
// Created by Noah Campagne on 21/09/2024.
//

#ifndef CE_SCHEDULED_EXECUTOR_H
#define CE_SCHEDULED_EXECUTOR_H

#include <GLFW/glfw3.h>

class ScheduledExecutor {
public:
    double beginTime;
    ScheduledExecutor() {
        this->beginTime = glfwGetTime();
    }
};

#endif
