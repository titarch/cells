//
// Created by bparsy on 4/28/20.
//

#include <thread>
#include <cmath>
#include "Engine.h"

void Engine::update_cells() {
    for (auto const& cell : cells_)
        cell->update();
}

void Engine::draw_scene(sf::RenderWindow& w) {
    for (auto const& c : cells_)
        c->draw(w);
    for (auto const& p : particles_)
        p->draw(w, 2);
}

void Engine::update_physics() {
    for (auto const& ci : cells_) {
        for (auto const& cj : cells_) {
            if (ci == cj || (ci->pos() - cj->pos()).sqrMagnitude() >= 9 * ci->radius() * cj->radius())
                continue;
            auto n = (ci->pos() - cj->pos()).normalized();
            if (std::isnan(n.sqrMagnitude()))
                n = Vec2f::random().normalized();
            ci->add_vel(n);
        }
        ci->add_pos(ci->vel());
        ci->brake(0.5);
    }
    for (auto& particle : particles_)
        particle->update();
}

void Engine::run() {
    sf::RenderWindow window(sf::VideoMode(w_, h_), "sfml-cells");
    while (window.isOpen()) {
        sf::Event e{};

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }
        window.clear();
        draw_scene(window);
        window.display();
        update_cells();
        update_physics();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
