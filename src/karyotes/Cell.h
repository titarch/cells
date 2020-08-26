//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_CELL_H
#define CELLS_CELL_H


#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "codons/Codon.h"
#include "../utils/Vector.h"

class Engine;

class Cell;

using cell_ptr = std::shared_ptr<Cell>;
using cells = std::unordered_set<cell_ptr>;

class Cell {
public:
    Cell(Engine& e, float radius, Vec2f const& pos) : e_(e), radius_(radius), pos_(pos), vel_(), codons_() {};
    virtual ~Cell() = default;

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

    Cell& inject_codons(codons&& foreign_codons) {
        codons_.reserve(codons_.size() + foreign_codons.size());
        std::move(foreign_codons.begin(), foreign_codons.end(), std::back_inserter(codons_));
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

    virtual cells::const_iterator update(cells::const_iterator cur) = 0;
    virtual void draw(sf::RenderWindow& w) const = 0;

protected:
    Engine& e_;
    float radius_;
    Vec2f pos_, vel_;
    codons codons_;

    friend class Codon;
};


#endif //CELLS_CELL_H
