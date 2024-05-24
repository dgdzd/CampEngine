//
//  gui_helper.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 18/05/2024.
//

#include <utils/gui_helper.h>

GuiHelper::GuiHelper(GLFWwindow* window, glm::vec2 startPosition) {
    this->window = window;
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
    
    return result;
}

Button* GuiHelper::createButton(std::string label, int textSize, float width, float height) {
    pos.y -= padding+height/2;
    
    Button* result = new Button(window, pos.x + margin + width/2, pos.y, width, height, label);
    result->with_textSize(textSize);
    
    pos.y -= height/2;
    
    return result;
}

TextInput* GuiHelper::createTextInput(float width, float height) {
    pos.y -= padding+height/2;
    
    TextInput* result = new TextInput(window, pos.x + margin + width/2, pos.y, width, height);
    
    pos.y -= height;
    
    return result;
}
