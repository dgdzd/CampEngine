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
