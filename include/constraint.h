#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <climits>
#include <cmath>

#include "common.h"
#include "particle.h"

class Constraint {
public:
    Constraint(ptr<Particle> pt1, ptr<Particle> pt2);

    void satisfy();

public:
    ptr<Particle> pt1;
    ptr<Particle> pt2;
    float         initDist;
};

#endif
