//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_LOOPCELL_H
#define CELLS_LOOPCELL_H


#include <iostream>
#include "Cell.h"
#include "codons/LoopCodon.h"

struct Hand {
    bool inward;
    size_t pos;

    explicit Hand() : inward(true), pos(0) {}

    void set_inwards(bool inwards = true) { inward = inwards; }

    void set_outwards() { set_inwards(false); }
};

class LoopCell : public Cell {
public:
    explicit LoopCell(Coord<float> const& pos, int energy) : Cell(pos), hand_(), energy_(energy), codon_idx_(0) {}

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
    void draw(sf::RenderWindow& w) const override;

    static LoopCell classic(Coord<float> const& pos) {
        LoopCell c(pos, 100);
        c.push_codons({
                              LoopCodon::hand_outwards,
                              LoopCodon::eat,
                              LoopCodon::hand_inwards,
                              LoopCodon::locate_weak,
                              LoopCodon::repair
                      }, 100);
        return c;
    }

protected:
    Hand hand_;
    int energy_;
    size_t codon_idx_;

    friend class LoopCodon;
};

#endif //CELLS_LOOPCELL_H
