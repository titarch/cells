//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_ENGINE_H
#define CELLS_ENGINE_H

#include <SFML/Graphics.hpp>
#include "../karyotes/LoopCell.h"
#include "../karyotes/particles/Particle.h"

class Engine {
public:
    Engine(size_t w, size_t h, unsigned ups) : w_(w), h_(h), ups_(ups), cells_(), particles_(), clock_{}, dt_() {
        std::srand(0);
    }

    template<typename C>
    Engine& push_cell(C const& c) {
        cells_.insert(std::make_unique<C>(c));
        return *this;
    }

    template<typename C, typename ...Args>
    Engine& emplace_cell(Args ...args) {
        cells_.insert(std::make_unique<C>(args...));
        return *this;
    }

    template<typename P>
    Engine& push_particle(P const& p) {
        particles_.insert(std::make_unique<P>(p));
        return *this;
    }

    template<typename P, typename ...Args>
    Engine& emplace_particle(Args ...args) {
        particles_.insert(std::make_unique<P>(args...));
        return *this;
    }

    template<typename P, typename ...Args>
    Engine& add_particles(size_t n, Args ...args) {
        for (size_t i = 0u; i < n; ++i)
            emplace_particle<P>(args...);
        return *this;
    }

    particles& get_particles() { return particles_; }

    cells& get_cells() { return cells_; }

    void update_time();
    float dt() const;
    void draw_scene(sf::RenderWindow& w);
    void update_cells();
    void update_physics();
    void run();

protected:
    size_t w_, h_;
    unsigned ups_;
    cells cells_;
    particles particles_;
    sf::Clock clock_;
    sf::Time dt_;
};


#endif //CELLS_ENGINE_H
