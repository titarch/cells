//
// Created by bparsy on 4/28/20.
//

#include <thread>
#include "Engine.h"

void Engine::update_cells() {
    for (auto const& c : cells_)
        c->update();
}

void Engine::draw_cells(sf::RenderWindow& w) {
    for (auto const& c : cells_)
        c->draw(w);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
