//
// Created by bparsy on 4/28/20.
//

#include "../LoopCell.h"
#include "../../engine/Engine.h"
#include "LoopCodon.h"

action_func LoopCodon::noop(int cost) {
    return [cost](LoopCell& c) {
        c.energy_ -= cost;
    };
}

action_func LoopCodon::hand_inwards(int cost) {
    return [cost](LoopCell& c) {
        c.hand_.set_inwards();
        c.energy_ -= cost;
    };
}

action_func LoopCodon::hand_outwards(int cost) {
    return [cost](LoopCell& c) {
        c.hand_.set_outwards();
        c.energy_ -= cost;
    };
}

action_func LoopCodon::eat(int reward) {
    return [reward](LoopCell& c) {
        if (c.hand_.inward) return;
        c.energy_ += reward;
    };
}

action_func LoopCodon::locate_weak(int cost) {
    return [cost](LoopCell& c) {
        if (!c.hand_.inward) return;
        int min_dur = c.codon(0)->durability();
        size_t min_idx = 0u;
        for (auto i = 1u; i < c.codons_.size(); ++i) {
            auto tmp_dur = c.codon(i)->durability();
            if (tmp_dur < min_dur) {
                min_dur = tmp_dur;
                min_idx = i;
            }
        }
        c.hand_.pos = min_idx;
        c.energy_ -= cost;
    };
}

action_func LoopCodon::repair(int cost) {
    return [cost](LoopCell& c) {
        if (!c.hand_.inward) return;
        c.targeted_codon()->self_repair();
        c.energy_ -= cost;
    };
}

sf::CircleShape LoopCodon::circle(float radius) const {
    sf::CircleShape c(radius * vitality() / 5);
    c.setFillColor(sf::Color::Blue);
    return c;
}

action_func LoopCodon::divide(Engine& e, int threshold) {
    return [threshold, &e](LoopCell& c) {
        if (c.energy_ < threshold) return;
        c.energy_ /= 2;
        e.push_cell(c.clone());
    };
}
