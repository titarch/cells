//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_CELL_H
#define CELLS_CELL_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "codons/Codon.h"
#include "../utils/Vector.h"

class Cell {
public:
    Cell(float radius, Vec2f const& pos) : radius_(radius), pos_(pos), vel_() {};

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

    [[nodiscard]] float radius() const { return radius_; }

    [[nodiscard]] Vec2f pos() const { return pos_; }

    void set_pos(Vec2f const& p) { pos_ = p; }

    void add_pos(Vec2f const& p) { pos_ += p; }

    [[nodiscard]] Vec2f vel() const { return vel_; }

    void set_vel(Vec2f const& v) { vel_ = v; }

    void add_vel(Vec2f const& v) { vel_ += v; }

    void brake(float frot = 0.5) { vel_ *= frot; }

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& w) const = 0;

protected:
    float radius_;
    Vec2f pos_, vel_;
    codons codons_;

    friend class Codon;
};

using cell_ptr = std::unique_ptr<Cell>;
using cells = std::vector<cell_ptr>;


#endif //CELLS_CELL_H
