//
// Created by Noah Campagne on 14/07/2024.
//

#ifndef CE_TEST_SCREEN_H
#define CE_TEST_SCREEN_H

#include <CampEngine/Graphics/Screen.h>

class TestScreen : public Screen {
public:
    float scaleSetting;

    TestScreen(GLFWwindow* window);

    virtual void init();
};

#endif
