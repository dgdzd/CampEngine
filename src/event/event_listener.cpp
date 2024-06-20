//
//  event_listener.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#include <event/event_listener.h>

void onEvent(const Event<MouseEvent>&) {
    
}

void EventListener::addMouseListener(MouseEvent type, std::function<void(const Event<MouseEvent>&)> func) {
    EventHandler::getInstance()->mouseEventDispatcher.addListener(type, func);
}
