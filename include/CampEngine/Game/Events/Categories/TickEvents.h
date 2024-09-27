//
// Created by Noah Campagne on 15/09/2024.
//

#ifndef CE_TICK_EVENTS_H
#define CE_TICK_EVENTS_H

#include <CampEngine/Game/Events/Event.h>

class TickEvent : Event {
public:
    TickEvent(int rate) : Event("TickEvent"+std::to_string(tickDelay)) {}
    virtual ~TickEvent() = default;

    int tick;
};

#endif
