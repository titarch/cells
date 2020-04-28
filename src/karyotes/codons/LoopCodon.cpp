//
// Created by bparsy on 4/28/20.
//

#include "LoopCodon.h"
#include "../LoopCell.h"

void LoopCodon::noop(LoopCell& c) {
    c.energy_ -= 1;
}

void LoopCodon::hand_inwards(LoopCell& c) {
    c.hand_.set_inwards();
    c.energy_ -= 3;
}

void LoopCodon::hand_outwards(LoopCell& c) {
    c.hand_.set_outwards();
    c.energy_ -= 3;
}

void LoopCodon::eat(LoopCell& c) {
    if (c.hand_.inward) return;
    c.energy_ += 5;
}

void LoopCodon::locate_weak(LoopCell& c) {
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
    c.energy_ -= 3;
}

void LoopCodon::repair(LoopCell& c) {
    if (!c.hand_.inward) return;
    c.targeted_codon()->self_repair();
    c.energy_ -= 10;
}
