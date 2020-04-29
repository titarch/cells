//
// Created by bparsy on 4/28/20.
//

#include <thread>
#include <cmath>
#include "Engine.h"

void Engine::update_cells() {
    for (size_t i = 0u; i < cells_.size(); ++i)
        cells_[i]->update();
}

void Engine::draw_cells(sf::RenderWindow& w) {
    for (auto const& c : cells_)
        c->draw(w);
}

void Engine::update_physics() {
    for (size_t i = 0u; i < cells_.size(); ++i) {
        auto& ci = cells_[i];
        for (size_t j = i + 1; j < cells_.size(); ++j) {
            auto& cj = cells_[j];
            if ((ci->pos() - cj->pos()).sqrMagnitude() < 9 * ci->radius() * cj->radius()) {
                auto n = (cj->pos() - ci->pos()).normalized();
                if (std::isnan(n.sqrMagnitude()))
                    n = Vec2f::random().normalized();
                ci->add_vel(-n);
                cj->add_vel(n);
            }
        }
        ci->add_pos(ci->vel());
        ci->brake(0.5);
    }
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
        draw_cells(window);
        window.display();
        update_cells();
        update_physics();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
