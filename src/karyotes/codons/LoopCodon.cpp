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
        size_t cur_pos = c.hand_.pos;
        for (auto i = 1u; i < c.codons_.size(); ++i) {
            auto tmp_dur = c.codon(i)->durability();
            if (tmp_dur < min_dur) {
                min_dur = tmp_dur;
                min_idx = i;
            }
        }
        if (min_idx == cur_pos) return;
        c.hand_.pos = min_idx;
        c.energy_ -= cost;
    };
}

action_func LoopCodon::repair(int cost, int threshold) {
    return [cost, threshold](LoopCell& c) {
        if (!c.hand_.inward || c.energy_ < threshold) return;
        c.targeted_codon()->self_repair();
        c.energy_ -= cost;
    };
}

static sf::Color hsv(int hue, float sat, float val) {
    hue %= 360;
    while (hue < 0) hue += 360;

    if (sat < 0.f) sat = 0.f;
    if (sat > 1.f) sat = 1.f;

    if (val < 0.f) val = 0.f;
    if (val > 1.f) val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - (float)h;
    float p = val * (1.f - sat);
    float q = val * (1.f - sat * f);
    float t = val * (1.f - sat * (1 - f));

    switch (h) {
        default:
        case 0:
        case 6:
            return sf::Color(val * 255, t * 255, p * 255);
        case 1:
            return sf::Color(q * 255, val * 255, p * 255);
        case 2:
            return sf::Color(p * 255, val * 255, t * 255);
        case 3:
            return sf::Color(p * 255, q * 255, val * 255);
        case 4:
            return sf::Color(t * 255, p * 255, val * 255);
        case 5:
            return sf::Color(val * 255, p * 255, q * 255);
    }
}

sf::CircleShape LoopCodon::circle(float radius) const {
    sf::CircleShape c(radius * vitality() / 5);
    static std::hash<const char*> hash;
    auto hue = hash(reinterpret_cast<const char*>(&action_)) % 360;
    c.setFillColor(hsv(hue, 1, 1));
    return c;
}

action_func LoopCodon::divide(Engine& e, int threshold) {
    return [threshold, &e](LoopCell& c) {
        if (c.energy_ < threshold) return;
        c.energy_ /= 2;
        e.push_cell(c.clone());
    };
}
