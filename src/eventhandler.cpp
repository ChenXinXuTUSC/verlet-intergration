#include "eventhandler.h"

void EventHandler::MouseHandler(
    const sf::Event&              event,
    std::vector<ptr<Particle>>&   particles,
    std::vector<ptr<Constraint>>& constraints
) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        float mouseX = static_cast<float>(event.mouseButton.x);
        float mouseY = static_cast<float>(event.mouseButton.y);

        ptr<Constraint> constraint = Constraint::findNearestConstraint(
            mouseX, mouseY,
            5.0f, constraints
        );

        if (constraint != nullptr) {
            constraint->setActive(false);
        }
    }
}
