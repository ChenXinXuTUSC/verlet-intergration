#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <climits>
#include <cmath>

#include "common.h"
#include "particle.h"

class Constraint {
public:
    Constraint(ptr<Particle> pt1, ptr<Particle> pt2, float rigid = 0.5f, bool active = true);

    void satisfy();

    static ptr<Constraint> findNearestConstraint(
        float x, float y,
        float r, const std::vector<ptr<Constraint>> constraints
    );

    void setActive(bool active);

public:
    ptr<Particle> pt1;
    ptr<Particle> pt2;
    float         initDist;
    float         rigidity;
    float         currInts;
    bool          isActive;
};

#endif
