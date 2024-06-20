#ifndef CE_EVENTS_H
#define CE_EVENTS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <map>
#include <functional>

/*
 * Here T must be an enum
 */

template<typename T>
class Event {
protected:
    T type;
    std::string name;
    bool handled = false;

public:
    Event() = default;
    virtual ~Event() = default;
    Event(T type, const std::string& name) {
        this->type = type;
        this->name = name;
    }
    
    template<typename EventType>
    inline EventType as() const {
        return static_cast<const EventType&>(*this);
    }
    
    inline T getType() const {
        return type;
    }
    inline std::string& getName() const {
        return name;
    }
    virtual bool wasHandled() const {
        return handled;
    }
};

template<typename T>
class EventDispatcher {
private:
    using Func = std::function<void(const Event<T>&)>;
    std::map<T, std::vector<Func>> listeners;
    
public:
    void addListener(T type, const Func& func) {
        listeners[type].push_back(func);
    }
    
    void propagateEvent(const Event<T>& event) {
        if(listeners.find(event.getType()) == listeners.end()) return;
        
        for(auto&& listener : listeners.at(event.getType())) {
            if(!event.wasHandled()) listener(event);
        }
    }
};

class InputActionEvent {
public:
    std::string name;
    int key;
    float value;
    
    InputActionEvent(std::string name, int key, int value);
};

class AxisActionEvent {
public:
    int axis;
    float value;
};

#endif
