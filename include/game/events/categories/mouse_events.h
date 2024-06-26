//
//  mouse_events.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#ifndef CE_MOUSE_EVENTS_H
#define CE_MOUSE_EVENTS_H

#include <game/events/event.h>

#include <string>

class MouseEvent : public Event {
public:
    MouseEvent(std::string name) : Event(name) {}
    virtual ~MouseEvent() {}
    
    double mouseX = 0, mouseY = 0;
};

class MouseClickEvent : public MouseEvent {
public:
    MouseClickEvent() : MouseEvent("MouseClickEvent") {}
    virtual ~MouseClickEvent() {}
    
    int mouseButton = -1;
};

class MouseReleaseEvent : public MouseEvent {
public:
    MouseReleaseEvent() : MouseEvent("MouseReleaseEvent") {}
    virtual ~MouseReleaseEvent() {}
    
    int mouseButton = -1;
};

class MouseMoveEvent : public MouseEvent {
public:
    MouseMoveEvent() : MouseEvent("MouseMoveEvent") {}
    virtual ~MouseMoveEvent() {}
};

#endif
