#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include <functional>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "particle.h"
#include "constraint.h"

#include "common.h"
#include "utils.h"

class EventHandler {
public:
    static void MouseHandler(
        const sf::Event&              event,
        std::vector<ptr<Particle>>&   particles,
        std::vector<ptr<Constraint>>& constraints
    );
};

#endif
