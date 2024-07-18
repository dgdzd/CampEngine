//
// Created by Noah Campagne on 14/07/2024.
//

#include <CampEngine/Graphics/Screens/DebugScreen.h>

DebugScreen::DebugScreen(GLFWwindow* window) : Screen(window) {
    this->init();
}

void DebugScreen::init() {
    Screen::init();

    GuiHelper gh(window, glm::vec2(0.0, 1070.0), this);
    gh.setPadding(0);
    gh.setMargin(0);

    textFPS = gh.createTextBox(L"FPS: ", 0, 20);
    textDeltaTime = gh.createTextBox(L"DeltaTime: ", 0, 20);
}