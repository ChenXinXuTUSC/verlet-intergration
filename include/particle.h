#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <memory>

#include "SFML/Graphics.hpp"

#include "commapi.h"

class Particle {
public:
    Particle(float x, float y, bool movable = true)
        : currPos(x, y), prevPos(x, y), acc(x, y), movable(movable) {}

    void applyForce(const sf::Vector2f& force);

    void updatePos(const float& dT);

    void constrainedBox(const float& width, const float& height, const float& radius);

public:
    sf::Vector2f currPos;
    sf::Vector2f prevPos;
    sf::Vector2f acc;
    bool         movable;
};

#endif
