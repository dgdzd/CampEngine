//
//  gui_helper.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/05/2024.
//

#ifndef gui_helper_h
#define gui_helper_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <graphics/core/widget.h>

#include <string>
#include <cstdlib>

/*---- Forward Declaration ----*/
class Widget;
class Button;
class TexturedButton;
class TextBox;
class TextInput;
/*-----------------------------*/

class GuiHelper {
public:
    GLFWwindow* window;
    int padding;
    int margin;
    glm::vec2 pos;
    
    GuiHelper(GLFWwindow* window, glm::vec2 startPosition);
    
    void setPadding(int padding);
    void setMargin(int margin);
    
    Button* createButton(std::string label, int textSize);
    Button* createButton(std::string label, int textSize, float width, float height);
    TexturedButton* createTexturedButton(Shader shader, Texture idle, Texture hover, std::string label);
    TexturedButton* createTexturedButton(Shader shader, std::string pathToImages, std::string label);
    TextBox* createTextBox(std::wstring text);
    TextInput* createTextInput(float width, float height);
    
private:
    int textLength(std::string text);
    int textLength(std::wstring text);
};

#endif /* gui_helper_h */
