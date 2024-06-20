//
//  keyboard_events.h
//  CampEngine++
//
//  Created by Noah Campagne on 18/06/2024.
//

#ifndef CE_KEY_EVENTS_H
#define CE_KEY_EVENTS_H

#include <event/events.h>

#include <string>

enum KeyboardEvent {
    KeyPress,
    CharacterInput,
};

class KeyPressEvent : public Event<KeyboardEvent> {
public:
    KeyPressEvent() : Event<KeyboardEvent>(KeyboardEvent::KeyPress, "KeyPress") {}
    virtual ~KeyPressEvent() {}
    
    int key = -1, scancode = -1, action = -1, mods = -1;
};

class CharacterInputEvent : public Event<KeyboardEvent> {
public:
    CharacterInputEvent() : Event<KeyboardEvent>(KeyboardEvent::CharacterInput, "CharacterInput") {}
    virtual ~CharacterInputEvent() {}
    
    unsigned int codepoint = -1;
};

#endif
