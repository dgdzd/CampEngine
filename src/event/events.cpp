#include <event/events.h>

Event::Event() {
    // TODO
}

void Event::call() {
    // TODO
}

CursorMovedEvent::CursorMovedEvent(double xpos, double ypos) {
    this->mouseX = xpos;
    this->mouseY = ypos;
}

MouseClickEvent::MouseClickEvent(int input, double xpos, double ypos) {
    this->mouseButton = input;
    this->mouseX = xpos;
    this->mouseY = ypos;
}

MouseReleaseEvent::MouseReleaseEvent(int input, double xpos, double ypos) {
    this->mouseButton = input;
    this->mouseX = xpos;
    this->mouseY = ypos;
}

CharacterTypeEvent::CharacterTypeEvent(unsigned int codepoint) {
    this->codepoint = codepoint;
}

KeyTypeEvent::KeyTypeEvent(int key, int scancode, int action, int mods) {
    this->key = key;
    this->scancode = scancode;
    this->action = action;
    this->mods = mods;
}
