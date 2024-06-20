//
//  widget_events.h
//  CampEngine++
//
//  Created by Noah Campagne on 19/06/2024.
//

#ifndef widget_events_h
#define widget_events_h

#include <event/events.h>

enum WidgetEvent {
    WidgetClick,
    WidgetRelease,
    WidgetStartHovering,
    WidgetStopHovering,
    WidgetSubmit
};

class WidgetClickEvent : Event<WidgetEvent> {
    WidgetClickEvent() : Event<WidgetEvent>(WidgetEvent::WidgetClick, "WidgetClick") {}
    virtual ~WidgetClickEvent() {}
};

#endif /* widget_events_h */
