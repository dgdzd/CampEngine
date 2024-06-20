//
//  mouse_events.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#ifndef CE_MOUSE_EVENTS_H
#define CE_MOUSE_EVENTS_H

#include <event/events.h>

#include <string>

enum MouseEvent {
    MouseClick,
    MouseRelease,
    MouseMove
};

class MouseClickEvent : public Event<MouseEvent> {
public:
    MouseClickEvent() : Event<MouseEvent>(MouseEvent::MouseClick, "MouseClick") {}
    virtual ~MouseClickEvent() {}
    
    double mouseX = 0, mouseY = 0;
    int mouseButton = -1;
};

class MouseReleaseEvent : public Event<MouseEvent> {
public:
    MouseReleaseEvent() : Event<MouseEvent>(MouseEvent::MouseRelease, "MouseRelease") {}
    virtual ~MouseReleaseEvent() {}
    
    double mouseX = 0, mouseY = 0;
    int mouseButton = -1;
};

class MouseMoveEvent : public Event<MouseEvent> {
public:
    MouseMoveEvent() : Event<MouseEvent>(MouseEvent::MouseMove, "MouseMove") {}
    virtual ~MouseMoveEvent() {}
    
    double mouseX = 0, mouseY = 0;
    int mouseButton = -1;
};

#endif
