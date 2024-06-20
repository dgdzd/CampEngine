//
//  event_handler.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#ifndef CE_EVENT_HANDLER_H
#define CE_EVENT_HANDLER_H

#include <event/categories/mouse_events.h>
#include <event/categories/keyboard_events.h>
#include <event/categories/widget_events.h>


#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <any>

/* Just a wrapper class for EventDispatcher */
class EventHandler {
private:
    static std::unique_ptr<EventHandler> inst;
    
public:
    EventDispatcher dispatcher;
    
    static EventHandler* getInstance();
    
    #define ADD_LISTENER(name, func, arg) EventHandler::getInstance()->dispatcher.addListener(name, std::bind(&func, arg, std::placeholders::_1))
    #define SEND_EVENT(event) EventHandler::getInstance()->dispatcher.propagateEvent(event)
};

#endif /* event_handler_h */
