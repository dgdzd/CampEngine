//
//  widget_events.h
//  CampEngine++
//
//  Created by Noah Campagne on 19/06/2024.
//

#ifndef widget_events_h
#define widget_events_h

#include <event/events.h>
#include <render/widget.h>

class Widget;

class WidgetEvent : public Event {
public:
    WidgetEvent(std::string name) : Event(name) {}
    virtual ~WidgetEvent() {}
    
    Widget* widget = nullptr;
};

class WidgetClickEvent : public WidgetEvent {
public:
    WidgetClickEvent() : WidgetEvent("WidgetEvent") {}
    virtual ~WidgetClickEvent() {}
    
    double mouseX = 0, mouseY = 0;
    int mouseButton = -1;
};

class WidgetReleaseEvent : public WidgetEvent {
public:
    WidgetReleaseEvent() : WidgetEvent("WidgetReleaseEvent") {}
    virtual ~WidgetReleaseEvent() {}
    
    double mouseX = 0, mouseY = 0;
    int mouseButton = -1;
};

class WidgetStartHoveringEvent : public WidgetEvent {
public:
    WidgetStartHoveringEvent() : WidgetEvent("WidgetStartHoveringEvent") {}
    virtual ~WidgetStartHoveringEvent() {}
    
    double mouseX = 0, mouseY = 0;
};

class WidgetStopHoveringEvent : public WidgetEvent {
public:
    WidgetStopHoveringEvent() : WidgetEvent("WidgetStopHoveringEvent") {}
    virtual ~WidgetStopHoveringEvent() {}
    
    double mouseX = 0, mouseY = 0;
};

class WidgetSubmitEvent : public WidgetEvent {
public:
    WidgetSubmitEvent() : WidgetEvent("WidgetSubmitEvent") {}
    virtual ~WidgetSubmitEvent() {}
    
    std::wstring input;
};

#endif /* widget_events_h */
