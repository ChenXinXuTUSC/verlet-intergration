#include <particle.h>

void Particle::applyForce(const sf::Vector2f& force) {
    if (!this->movable) return;
    this->acc += force;
}

void Particle::updatePos(const float& dT) {
    if (!this->movable) return;
    
    sf::Vector2f velocity = this->currPos - this->prevPos;

    this->prevPos = this->currPos;
    this->currPos += velocity + this->acc * dT * dT;
    this->acc = sf::Vector2f(0.0f, 0.0f); // reset after update
}

void Particle::constrainedBox(const float& width, const float& height, const float& radius) {
    if (this->currPos.x < radius)
        this->currPos.x = radius;
    if (this->currPos.x > width - radius)
        this->currPos.x = width - radius;
    if (this->currPos.y < radius)
        this->currPos.y = radius;
    if (this->currPos.y > height - radius)
        this->currPos.y = height - radius;
}
