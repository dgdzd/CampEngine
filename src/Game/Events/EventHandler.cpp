//
//  event_handler.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#include <CampEngine/Game/Events/EventHandler.h>

std::unique_ptr<EventHandler> EventHandler::inst = nullptr;

EventHandler* EventHandler::getInstance() {
    if(!inst) {
        inst = std::make_unique<EventHandler>();
    }
    
    return inst.get();
}
