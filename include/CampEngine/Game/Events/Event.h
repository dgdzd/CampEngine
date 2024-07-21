#ifndef CE_EVENT_H
#define CE_EVENT_H

#include <string>
#include <vector>
#include <map>
#include <functional>

class Event {
protected:
    std::string name;
    bool handled = false;

public:
    Event() = default;
    virtual ~Event() = default;
    Event(const std::string& name) {
        this->name = name;
    }
    
    template<typename EventType>
    inline EventType as() const {
        return *dynamic_cast<const EventType*>(this);
    }
    inline std::string& getName() {
        return name;
    }
    virtual bool wasHandled() const {
        return handled;
    }
};

class EventDispatcher {
private:
    using Func = std::function<void(const Event&)>;
    std::map<std::string, std::vector<Func>> listeners;
    
public:
    void addListener(Event event, const Func& func) {
        listeners[event.getName()].push_back(func);
    }
    
    void propagateEvent(Event& event) {
        if(!listeners.contains(event.getName())) return;
        
        for(auto&& listener : listeners[event.getName()]) {
            if(!event.wasHandled()) listener(event);
        }
    }
};

#endif
