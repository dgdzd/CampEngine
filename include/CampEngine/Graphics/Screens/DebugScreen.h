//
// Created by Noah Campagne on 14/07/2024.
//

#ifndef CE_DEBUG_SCREEN_H
#define CE_DEBUG_SCREEN_H

#include <CampEngine/Graphics/Screen.h>

class Button;
class TexturedButton;
class TextBox;
class TextInput;

class DebugScreen : public Screen {
public:
    TextBox* textFPS;
    TextBox* textDeltaTime;
    DebugScreen(GLFWwindow* window);

    virtual void init();
};

#endif
