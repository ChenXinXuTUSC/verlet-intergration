#include "constraint.h"
#include <cmath>

Constraint::Constraint(ptr<Particle> pt1, ptr<Particle> pt2) : pt1(pt1), pt2(pt2) {
    sf::Vector2f delta = this->pt2->currPos - this->pt1->currPos;
    this->initDist     = std::hypot(delta.x, delta.y);
}

void Constraint::satisfy() {
    sf::Vector2f delta = this->pt2->currPos - this->pt1->currPos;

    float currDist  = std::hypot(delta.x, delta.y);
    float diffRatio = (currDist - this->initDist) / this->initDist;

    sf::Vector2f correction = delta * 0.5f * diffRatio;
    if (this->pt1->movable) this->pt1->currPos += correction;
    if (this->pt2->movable) this->pt2->currPos -= correction;
}
