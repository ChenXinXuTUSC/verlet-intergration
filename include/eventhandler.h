#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "SFML/System.hpp"

#include <functional>

class EventHandler {
public:
    template<typename Func, typename... Args>
    void setHandler(Func&& func, Args... args) {
        using returnType = typename std::result_of<func(args...)>::type;
        handler = []() {
            func(args...);
        };
    }

private:
    std::function<void()> handler;
};

#endif
