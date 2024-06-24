//
//  action_events.h
//  CampEngine++
//
//  Created by Noah Campagne on 23/06/2024.
//

#ifndef ACTION_EVENTS_H
#define ACTION_EVENTS_H

#include <event/events.h>

class InputActionEvent : public Event {
public:
    std::string actionName;
    int key;
    float value;
    
    InputActionEvent(std::string name) : Event("InputActionEvent_"+name) {};
};

class AxisActionEvent : public Event {
public:
    int axis;
    float value;
    
    AxisActionEvent(std::string name) : Event("AxisActionEvent_"+name) {};
};

#endif
