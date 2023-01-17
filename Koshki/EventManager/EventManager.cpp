#include "EventManager.hpp"

multimap<EventHandlerBase*, function<void()>> EventManager::eventMap = {};

void EventManager::fireEvent(string key){
    std::cout << key << std::endl;
    for (const auto& [event, callback] : eventMap){
        if(key == event->getKey()){
            callback();
        }
    }
}

void EventManager::signToEvent(string key, function<void()> func){
    EventHandler* newEvent = new EventHandler(key);
    eventMap.insert({newEvent, func});
}
