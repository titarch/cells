//
// Created by bparsy on 4/28/20.
//

#include <thread>
#include <cmath>
#include "Engine.h"
#include "GUI.hh"

void Engine::update_time() {
    dt_ = clock_.restart();
}

float Engine::dt() const {
    return dt_.asSeconds();
}

void Engine::update_cells() {
    static const auto idle_time = 1.f / (float) ups_;
    static auto elapsed_time = 0.f;
    elapsed_time += dt();

    while (elapsed_time >= idle_time) {
        elapsed_time -= idle_time;
        for (auto it = cells_.cbegin(); it != cells_.cend();)
            it = it->get()->update(it);
    }
}


void Engine::draw_scene(sf::RenderWindow& w) {
    for (auto const& c : cells_)
        c->draw(w);
    for (auto const& v : viruses_)
        v->draw(w);
    for (auto const& p : particles_)
        p->draw(w, 2);
}

void Engine::update_physics() {
    for (auto const& ci : cells_) {
        for (auto const& cj : cells_) {
            if (ci == cj || (ci->pos() - cj->pos()).sqrMagnitude() >= 2.25f * std::pow(ci->radius() + cj->radius(), 2))
                continue;
            auto n = (ci->pos() - cj->pos()).normalized();
            if (std::isnan(n.sqrMagnitude()))
                n = Vec2f::random().normalized();
            ci->add_vel(n);
        }
        ci->add_pos(ci->vel() * 25.f * dt());
        ci->brake(std::clamp(1.f - dt() * 25.f, 0.f, 1.f));
    }
    for (auto it = viruses_.cbegin(); it != viruses_.cend();)
        it = it->get()->update(it, dt());
    for (auto& particle : particles_)
        particle->update(dt());
}

void Engine::run() {
    sf::RenderWindow window(sf::VideoMode(w_, h_), "sfml-cells");
    GUI gui{*this, window};
    gui.add_event(sf::Event::Closed, [&window]() { window.close(); })
            .add_key_event(sf::Event::KeyPressed, sf::Keyboard::Escape, [&window]() { window.close(); });

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e))
            gui.handle_events(e);
        window.clear();
        draw_scene(window);
        gui.draw();
        window.display();
        update_cells();
        update_physics();
        update_time();
    }
}
