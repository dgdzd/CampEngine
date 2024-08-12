//
//  gui_helper.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/05/2024.
//

#ifndef GUI_HELPER_H
#define GUI_HELPER_H

#include <CampEngine/Graphics/Widgets/Button.h>
#include <CampEngine/Graphics/Widgets/ProgressBar.h>
#include <CampEngine/Graphics/Widgets/TextBox.h>
#include <CampEngine/Graphics/Widgets/TextInput.h>
#include <CampEngine/Graphics/Widgets/TexturedButton.h>
#include <CampEngine/Graphics/Screen.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <string>
#include <cstdlib>

#include "CampEngine/Graphics/Widgets/Slider.h"

/*---- Forward Declaration ----*/
class Screen;
class Widget;
/*-----------------------------*/

class GuiHelper {
public:
    GLFWwindow* window;
    Screen* screen;
    int padding;
    int margin;
    glm::vec2 pos;
    
    GuiHelper(GLFWwindow* window, glm::vec2 startPosition, Screen* screen);
    
    void setPadding(int padding);
    void setMargin(int margin);
    
    Button* createButton(std::string label, int textSize);
    Button* createButton(std::string label, int textSize, float width, float height);
    TexturedButton* createTexturedButton(Shader shader, Texture idle, Texture hover, std::string label);
    TexturedButton* createTexturedButton(Shader shader, std::string pathToImages, std::string label);
    TextBox* createTextBox(std::wstring text, int boundX, int boundY);
    TextInput* createTextInput(float width, float height);
    ProgressBar* createProgressBar(float width, float height, float value);
    Slider* createSlider(float width, float height, float value, int direction=0x1);
    
private:
    int textLength(std::string text);
    int textLength(std::wstring text);
};

#endif /* gui_helper_h */
