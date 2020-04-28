//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_LOOPCELL_H
#define CELLS_LOOPCELL_H


#include <iostream>
#include "Cell.h"
#include "codons/LoopCodon.h"

inline constexpr float RADIUS = 50;
inline constexpr float OUTLINE = RADIUS / 5;

struct Hand {
    bool inward;
    size_t pos;

    explicit Hand() : inward(true), pos(0) {}

    void set_inwards(bool inwards = true) { inward = inwards; }

    void set_outwards() { set_inwards(false); }

    sf::CircleShape circle() const {
        sf::CircleShape c(RADIUS + RADIUS / 2);
        c.setOutlineColor(sf::Color::Cyan);
        c.setOutlineThickness(OUTLINE / 2);
        c.setFillColor({0, 0, 0, 0});
        return c;
    }
};

class LoopCell : public Cell {
public:
    explicit LoopCell(Coord<float> const& pos, int energy) : Cell(pos), hand_(), energy_(energy), codon_idx_(0) {}

    LoopCell(LoopCell const& other) = default;

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

    Coord<float> codon_draw_pos(size_t idx, float dist) const;
    void draw_cursor(sf::RenderWindow& w) const;
    void draw(sf::RenderWindow& w) const override;

    static LoopCell classic(Coord<float> const& pos) {
        LoopCell c(pos, 50);
        c.push_codons({
                              LoopCodon::hand_outwards(2),
                              LoopCodon::eat(15),
                              LoopCodon::hand_inwards(2),
                              LoopCodon::locate_weak(3),
                              LoopCodon::repair(5)
                      }, 100);
        return c;
    }

    static LoopCell dividable(Coord<float> const& pos, Engine& e) {
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
