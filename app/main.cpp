#include "common.h"

#include "SFML/Graphics.hpp"

#include "constraint.h"
#include "particle.h"
#include "eventhandler.h"

const int   WINDOW_WID = 1024;
const int   WINDOW_HEI = 768;
const float INTERVAL   = 5.0f;

const int CLOTH_ROW = 20;
const int CLOTH_COL = 20;

const sf::Vector2f G(0.0f, 100.0f);

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WID, WINDOW_HEI), "cloth sim");
    window.setFramerateLimit(60);

    std::vector<ptr<Particle>> particles(CLOTH_ROW * CLOTH_COL);
    for (int i = 0; i < CLOTH_ROW; ++i) {
        for (int j = 0; j < CLOTH_COL; ++j) {
            particles[i * CLOTH_COL + j] = std::make_shared<Particle>(
                WINDOW_HEI / 2 + INTERVAL * 3 * j, // row pos
                WINDOW_WID / 4 + INTERVAL * 3 * i, // col pos
                i ^ 0
            );
        }
    }

    std::vector<ptr<Constraint>> constraints;
    for (int i = 0; i < CLOTH_ROW; ++i) {
        for (int j = 0; j < CLOTH_COL; ++j) {
            // vertical constraint
            if (i < CLOTH_ROW - 1)
                constraints.emplace_back(std::make_shared<Constraint>(
                    particles[i * CLOTH_COL + j],
                    particles[(i + 1) * CLOTH_COL + j], 0.2f
                    // randomNum(0.45f, 0.55f)
                ));
            // horizontal constraint
            if (j < CLOTH_COL - 1)
                constraints.emplace_back(std::make_shared<Constraint>(
                    particles[i * CLOTH_COL + j],
                    particles[i * CLOTH_COL + (j + 1)], 0.2f
                    // randomNum(0.45f, 0.55f)
                ));
            // diagnal constraint
            // if (i < CLOTH_ROW - 1 && j < CLOTH_COL - 1)
            //     constraints.emplace_back(
            //         std::make_shared<Constraint>(
            //             particles[i * CLOTH_COL + j],
            //             particles[(i + 1) * CLOTH_COL + j + 1]
            //         )
            //     );
        }
    }

    // main loop
    sf::Clock timer;
    while (window.isOpen()) {
        sf::Time dT = timer.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseButtonPressed:
                    EventHandler::MouseHandler(event, particles, constraints);
                    break;


                default:
                    break;
            }
        }

        // physical update

        // particle position
        for (auto pt : particles) {
            pt->applyForce(G);
            pt->updatePos(dT.asSeconds());
            pt->constrainedBox(WINDOW_WID, WINDOW_HEI, INTERVAL);
        }

        // particle constraint
        for (auto ct : constraints) { ct->satisfy(); }

        // render update
        window.clear(sf::Color::Black);

        // draw joints
        for (auto pt : particles) {
            sf::Vertex ptpos(pt->currPos, sf::Color::White);
            window.draw(&ptpos, 1, sf::Points);
        }

        // draw constraints
        for (auto ct : constraints) {
            if (!ct->isActive) continue;

            sf::Vertex vtxArr[] {
                sf::Vertex(ct->pt1->currPos, sf::Color(ct->currInts * 255, 100, 50)),
                sf::Vertex(ct->pt2->currPos, sf::Color(ct->currInts * 255, 100, 50)),
            };
            window.draw(vtxArr, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
