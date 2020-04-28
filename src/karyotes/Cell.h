//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_CELL_H
#define CELLS_CELL_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "codons/Codon.h"

template<typename T>
struct Coord {
    T x, y;

    Coord(T x, T y) : x(x), y(y) {}
};

class Cell {
public:
    Cell(Coord<float> const& pos) : pos_(pos) {};

    template<typename C>
    Cell& push_codon(C const& codon) {
        codons_.push_back(std::make_shared<C>(codon));
        return *this;
    }

    template<typename C, typename ...Args>
    Cell& emplace_codon(Args... args) {
        codons_.push_back(std::make_shared<C>(args...));
        return *this;
    }

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& w) const = 0;

protected:
    Coord<float> pos_;
    codons codons_;

    friend class Codon;
};

using cell_ptr = std::unique_ptr<Cell>;
using cells = std::vector<cell_ptr>;


#endif //CELLS_CELL_H
