//
//  event_handler.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#ifndef CE_EVENT_HANDLER_H
#define CE_EVENT_HANDLER_H

#include <CampEngine/Game/Events/Categories/MouseEvents.h>
#include <CampEngine/Game/Events/Categories/KeyboardEvents.h>
#include <CampEngine/Game/Events/Categories/ActionEvents.h>
#include <CampEngine/Game/Events/Categories/WidgetEvents.h>

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
    #define ADD_STATIC_LISTENER(name, func) EventHandler::getInstance()->dispatcher.addListener(name, func)
    #define SEND_EVENT(event) EventHandler::getInstance()->dispatcher.propagateEvent(event)
};

#endif
