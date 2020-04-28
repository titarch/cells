//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_ENGINE_H
#define CELLS_ENGINE_H

#include <SFML/Graphics.hpp>
#include "../karyotes/LoopCell.h"

class Engine {
public:
    Engine(size_t w, size_t h) : w_(w), h_(h) {}

    template<typename C>
    Engine& push_cell(C const& c) {
        cells_.push_back(std::make_unique<C>(c));
        return *this;
    }

    template<typename C, typename ...Args>
    Engine& emplace_cell(Args ...args) {
        cells_.push_back(std::make_unique<C>(args...));
        return *this;
    }

    void draw_cells(sf::RenderWindow& w);
    void update_cells();
    void run();

protected:
    size_t w_, h_;
    cells cells_;
};


#endif //CELLS_ENGINE_H
