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

/* This is an interface class from which any class can herit */
class EventHandler {
private:
    static std::unique_ptr<EventHandler> inst;
    std::map<std::any, EventDispatcher<std::any>> dispatchers;
    
public:
    EventDispatcher<MouseEvent> mouseEventDispatcher;
    EventDispatcher<KeyboardEvent> keyboardEventDispatcher;
    
    static EventHandler* getInstance();
    
    std::map<std::any, EventDispatcher<std::any>> getDispatchers();
    
    template<typename EventType>
    void registerEvents() {
        
    }
    
#define ADD_MOUSE_LISTENER(type, func, arg) EventHandler::getInstance()->mouseEventDispatcher.addListener(type, std::bind(&func, arg, std::placeholders::_1))
#define ADD_KEYBOARD_LISTENER(type, func, arg) EventHandler::getInstance()->keyboardEventDispatcher.addListener(type, std::bind(&func, arg, std::placeholders::_1))
    
#define SEND_MOUSE_EVENT(event) EventHandler::getInstance()->mouseEventDispatcher.propagateEvent(event)
#define SEND_KEYBOARD_EVENT(event) EventHandler::getInstance()->keyboardEventDispatcher.propagateEvent(event)
};

#endif /* event_handler_h */
