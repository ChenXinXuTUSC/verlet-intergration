#include <cmath>

#include "constraint.h"
#include "utils.h"

Constraint::Constraint(ptr<Particle> pt1, ptr<Particle> pt2, bool active)
    : pt1(pt1), pt2(pt2), isActive(active) {
    sf::Vector2f delta = this->pt2->currPos - this->pt1->currPos;
    this->initDist     = std::hypot(delta.x, delta.y);
}

void Constraint::satisfy() {
    if (!this->isActive) return;
    
    sf::Vector2f delta = this->pt2->currPos - this->pt1->currPos;

    float currDist  = std::hypot(delta.x, delta.y);
    float diffRatio = (currDist - this->initDist) / this->initDist;

    sf::Vector2f correction = delta * 0.5f * diffRatio;
    if (this->pt1->movable) this->pt1->currPos += correction;
    if (this->pt2->movable) this->pt2->currPos -= correction;
}

ptr<Constraint> Constraint::findNearestConstraint(
    float x, float y, float r, const std::vector<ptr<Constraint>> constraints
) {
    ptr<Constraint> nearestCons; // nullptr
    float nearestDist = r;
    for (const ptr<Constraint>& constraint : constraints) {
        float dist = pointToSegmentDist(
            x, y,
            constraint->pt1->currPos.x,
            constraint->pt1->currPos.y,
            constraint->pt2->currPos.x,
            constraint->pt2->currPos.y
        );

        if (dist < nearestDist) {
            nearestDist = dist;
            nearestCons = constraint;
        }
    }

    return nearestCons;
}

void Constraint::setActive(bool active) {
    this->isActive = active;
}
