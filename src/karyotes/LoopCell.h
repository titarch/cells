//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_LOOPCELL_H
#define CELLS_LOOPCELL_H


#include <iostream>
#include "Cell.h"
#include "codons/LoopCodon.h"

struct Hand {
    float radius;
    bool inward;
    size_t pos;

    explicit Hand(float radius) : radius(radius), inward(true), pos(0) {}

    void set_inwards(bool inwards = true) { inward = inwards; }

    void set_outwards() { set_inwards(false); }

    sf::CircleShape circle() const {
        sf::CircleShape c(radius + radius / 2);
        c.setOutlineColor(sf::Color::Cyan);
        c.setOutlineThickness(radius / 10);
        c.setFillColor({0, 0, 0, 0});
        return c;
    }
};

class LoopCell : public Cell {
public:
    LoopCell(float radius, Vec2f const& pos, int energy) : Cell(radius, pos), hand_(radius), energy_(energy),
                                                           codon_idx_(0) {}

    LoopCell clone() {
        LoopCell copy(radius_, pos_, energy_);
        copy.codons_.reserve(codons_.size());
        std::transform(codons_.begin(), codons_.end(), std::back_inserter(copy.codons_),
                       [](codon_ptr const& cp) -> codon_ptr { return cp->clone(); });
        return copy;
    }

    const loop_codon_ptr codon(size_t idx) const {
        return std::static_pointer_cast<LoopCodon>(codons_[idx]);
    }

    loop_codon_ptr codon(size_t idx) {
        return std::static_pointer_cast<LoopCodon>(codons_[idx]);
    }

    loop_codon_ptr current_codon() {
        return codon(codon_idx_);
    }

    loop_codon_ptr targeted_codon() {
        return hand_.inward ? codon(hand_.pos) : nullptr;
    }

    void move_codon() { codon_idx_ = (codon_idx_ + 1) % codons_.size(); }

    void die() {
        std::cout << "Please implement dying..." << std::endl;
    }

    void push_codons(action_funcs const& actions, int durability) {
        for (auto const& f : actions)
            emplace_codon<LoopCodon>(durability, f);
    }

    void update() override;

    Vec2f codon_draw_pos(size_t idx, float dist) const;
    void draw_cursor(sf::RenderWindow& w) const;
    void draw(sf::RenderWindow& w) const override;

    static LoopCell classic(Vec2f const& pos) {
        LoopCell c(50, pos, 50);
        c.push_codons({
                              LoopCodon::hand_outwards(2),
                              LoopCodon::eat(15),
                              LoopCodon::hand_inwards(2),
                              LoopCodon::locate_weak(3),
                              LoopCodon::repair(5, 10)
                      }, 100);
        return c;
    }

    static LoopCell dividable(Vec2f const& pos, Engine& e) {
        LoopCell c = classic(pos);
        c.push_codons({LoopCodon::divide(e, 90)}, 100);
        return c;
    }

protected:
    Hand hand_;
    int energy_;
    size_t codon_idx_;

    friend class LoopCodon;
};

#endif //CELLS_LOOPCELL_H
