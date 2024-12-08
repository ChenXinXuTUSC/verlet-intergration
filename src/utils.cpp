#include "utils.h"

// p: point
// s: segment
float pointToSegmentDist(
    const float& px,
    const float& py,
    const float& ax,
    const float& ay,
    const float& bx,
    const float& by
) {
    // dot product vec1(x1, y1) · vec2(x2, y2) = x1x2 + y1y2
    float vecABdx = bx - ax;
    float vecABdy = by - ay;

    float vecAPdx = px - ax;
    float vecAPdy = py - ay;

    float vecBPdx = px - bx;
    float vecBPdy = py - by;

    float lenABAP = vecAPdx * vecABdx + vecAPdy * vecABdy;
    float lenABAB = vecABdx * vecABdx + vecABdy * vecABdy;

    float t = lenABAP / lenABAB;

    float dist = 0.0f;

    if (t < 0.0f || t > 1.0f) {
        // projection point p outside the segment AB
        if (t < 0.0f) {
            dist = std::sqrt(vecAPdx * vecAPdx + vecAPdy * vecAPdy);
        }
        if (t > 1.0f) {
            dist = std::sqrt(vecBPdx * vecBPdx + vecBPdy * vecBPdy);
        }
    } else {
        // projection point p inside the segment AB
        float projx = ax + t * vecABdx;
        float projy = ay + t * vecABdy;

        dist        = std::sqrt((projx - px) * (projx - px) + (projy - py) * (projy - py));
    }

    return dist;
}
