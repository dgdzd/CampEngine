//
//  gui_helper.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 18/05/2024.
//

#include <CampEngine/Utils/GuiHelper.h>

#include <CampEngine/Graphics/Core/Text/Character.h>

#include <codecvt>

GuiHelper::GuiHelper(GLFWwindow* window, glm::vec2 startPosition, Screen* screen) {
    this->window = window;
    this->screen = screen;
    this->pos = startPosition;
    this->margin = 10;
    this->padding = 0;
}

int GuiHelper::textLength(std::string text) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wtext = converter.from_bytes(text);
    return textLength(wtext);
}

int GuiHelper::textLength(std::wstring text) {
    int size = 0;
    std::wstring::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Character ch = Character::characters[*c];
        size += (ch.advance >> 6);
    }
    return size;
}

void GuiHelper::setPadding(int padding) {
    this->padding = padding;
}

void GuiHelper::setMargin(int margin) {
    this->margin = margin;
}

Button* GuiHelper::createButton(std::string label, int textSize) {
    pos.y -= padding+(textSize+6)/2;
    
    int length = textLength(label);
    float scale = textSize/48.0f;
    float width = length*scale;
    
    Button* result = new Button(window, pos.x + margin + (width+textSize/2.0)/2, pos.y, width+textSize/2.0, textSize+6, label);
    result->with_textSize(textSize);
    
    pos.y -= (textSize+6)/2;
    
    std::shared_ptr<Button> ptr = std::shared_ptr<Button>(result);
    screen->widgets.push_back(ptr);
    return result;
}

Button* GuiHelper::createButton(std::string label, int textSize, float width, float height) {
    pos.y -= padding+height/2;
    
    Button* result = new Button(window, pos.x + margin + width/2, pos.y, width, height, label);
    result->with_textSize(textSize);
    
    pos.y -= height/2;
    
    std::shared_ptr<Button> ptr = std::shared_ptr<Button>(result);
    screen->widgets.push_back(ptr);
    return result;
}

TextBox* GuiHelper::createTextBox(std::wstring text, int boundX, int boundY) {
    pos.y -= padding+boundY/2;
    
    TextBox* result = new TextBox(window, *ResourceManager::standard.getShader("text"), Texture(boundX, boundY), pos.x + margin + boundX/2, pos.y, boundX, boundY, text);
    
    pos.y -= padding+boundY/2;
    
    std::shared_ptr<TextBox> ptr = std::shared_ptr<TextBox>(result);
    screen->widgets.push_back(ptr);
    return result;
}

TextInput* GuiHelper::createTextInput(float width, float height) {
    pos.y -= padding+height/2;
    
    TextInput* result = new TextInput(window, pos.x + margin + width/2, pos.y, width, height);
    
    pos.y -= height;
    
    std::shared_ptr<TextInput> ptr = std::shared_ptr<TextInput>(result);
    screen->widgets.push_back(ptr);
    return result;
}

ProgressBar* GuiHelper::createProgressBar(float width, float height, float value) {
    pos.y -= padding+height/2;

    ProgressBar* result = new ProgressBar(window, value, pos.x + margin + width/2, pos.y, width, height);

    pos.y -= height;

    std::shared_ptr<ProgressBar> ptr = std::shared_ptr<ProgressBar>(result);
    screen->widgets.push_back(ptr);
    return result;
}

Slider* GuiHelper::createSlider(float width, float height, float value, int direction) {
    pos.y -= padding+height/2;

    Slider* result = new Slider(window, value, pos.x + margin + width/2, pos.y, width, height, direction);

    pos.y -= height;
    std::shared_ptr<Slider> ptr = std::shared_ptr<Slider>(result);
    screen->widgets.push_back(ptr);
    return result;
}

Tooltip* GuiHelper::createTooltip(std::string text, int textSize) {
    int length = textLength(text);
    float scale = textSize/48.0f;
    float width = length*scale;

    Tooltip* result = new Tooltip(window, 0, 0, width+textSize/2.0, textSize+6, text);
    result->tb->textSize = textSize;

    return result;
}


Tooltip* GuiHelper::createTooltip(float width, float height, std::string text) {
    Tooltip* result = new Tooltip(window, 0, 0, width, height, text);
    //std::shared_ptr<Tooltip> ptr = std::shared_ptr<Tooltip>(result);
    return result;
}
