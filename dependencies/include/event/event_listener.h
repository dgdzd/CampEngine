//
//  event_listener.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#ifndef CE_EVENT_LISTENER_H
#define CE_EVENT_LISTENER_H

#include <event/event_handler.h>

#include <vector>
#include <functional>

/* This is an interface class from which any class can herit */
class EventListener {
private:
    static std::vector<EventListener*> m_EventListeners;
    
public:
    void addListener(Event type, std::function<void(const Event&)> func);
};

#endif
