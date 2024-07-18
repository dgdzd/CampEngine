//
//  input.cpp
//  CampEngine++
//
//  Created by Noah Campagne on 01/05/2024.
//

#include <CampEngine/Game/Input/Input.h>

InputAction::InputAction(int key, float value, bool isContinuous) {
    this->key = key;
    this->value = value;
    this->isContinuous = isContinuous;
}

ActionMapper::ActionMapper() {
    ADD_LISTENER(KeyPressEvent(), ActionMapper::onKeyPress, this);
    ADD_LISTENER(KeyReleaseEvent(), ActionMapper::onKeyRelease, this);
}

void ActionMapper::update() {
    for(auto i = inputActions.begin(); i != inputActions.end(); i++) {
        for(auto key : activeKeys) {
            if(std::find_if(i->second.begin(), i->second.end(), [&key](InputAction& key_) { return key.key == key_.key; }) == i->second.end()) {
                
            } else {
                if(!key.isContinuous) {
                    
                } else {
                    InputActionEvent event(i->first);
                    event.actionName = i->first;
                    event.key = key.key;
                    event.value = key.value;
                    SEND_EVENT(event);
                }
            }
        }
    }
}

void ActionMapper::onKeyPress(const Event &e) {
    auto event = e.as<KeyPressEvent>();
    
    if(event.action == GLFW_PRESS) {
        for(auto i = inputActions.begin(); i != inputActions.end(); i++) {
            for(auto key : i->second) {
                if(key.key == event.key) {
                    activeKeys.push_back(key);
                    InputActionEvent event_(i->first);
                    event_.actionName = i->first;
                    event_.key = event.key;
                    event_.value = key.value;
                    SEND_EVENT(event_);
                }
            }
        }
    }
}

void ActionMapper::onKeyRelease(const Event &e) {
    auto event = e.as<KeyReleaseEvent>();
    auto element = std::find_if(activeKeys.begin(), activeKeys.end(), [event](InputAction& key_) { return event.key == key_.key; });
    if(element != activeKeys.end()) activeKeys.erase(element);
}

void ActionMapper::addInputAction(std::string name, int input, float scale, bool isContinuous) {
    inputActions[name].push_back(InputAction(input, scale, isContinuous));
}

void ActionMapper::addAxisAction(std::string name, int axis, float scale, bool isContinuous) {
    axisActions[name] = { axis, scale };
}

void ActionMapper::removeInputAction(std::string name, int input) {
    for(auto input_ : inputActions[name]) {
        auto index = std::find_if(inputActions[name].begin(), inputActions[name].end(), [input_](InputAction& input__) { return input_.key == input__.key; });
        if(index != inputActions[name].end()) inputActions[name].erase(index);
    }
}

void ActionMapper::removeAxisAction(std::string name) {
    axisActions.erase(name);
}
