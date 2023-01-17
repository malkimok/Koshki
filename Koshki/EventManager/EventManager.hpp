#pragma once

#include <iostream>
#include <map>
#include <string>
#include <functional>

using namespace std;

class EventHandlerBase{
public:
    EventHandlerBase(){}
    virtual string getKey() = 0;
};


class EventHandler : public EventHandlerBase{
private:
    string key;
public:
    string getKey(){return key;}
    EventHandler(string newKey){
        key = newKey;
    }
};

class EventManager{
public:
    static void signToEvent(string key, function<void()> func);
    static void fireEvent(string key);

private:
    static multimap<EventHandlerBase*, function<void()>> eventMap;
};
