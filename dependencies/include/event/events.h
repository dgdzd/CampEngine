#ifndef CE_EVENTS_H
#define CE_EVENTS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma once

class Event {
    public:
    
    Event();
    virtual ~Event() = default;
    
    static void call();
};


class CursorMovedEvent : public Event {
    public:
    double mouseX;
    double mouseY;
    
    CursorMovedEvent(double xpos, double ypos);
};

class MouseClickEvent : public Event {
    public:
    double mouseX;
    double mouseY;
    int mouseButton;
    
    MouseClickEvent(int input, double xpos, double ypos);
};

class MouseReleaseEvent : public Event {
    public:
    double mouseX;
    double mouseY;
    int mouseButton;
    
    MouseReleaseEvent(int input, double xpos, double ypos);
};  

#endif
