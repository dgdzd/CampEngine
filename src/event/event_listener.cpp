//
//  event_listener.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#include <event/event_listener.h>

void onEvent(const Event&) {
    
}

void EventListener::addListener(Event type, std::function<void(const Event&)> func) {
    EventHandler::getInstance()->dispatcher.addListener(type, func);
}
