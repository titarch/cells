//
// Created by bparsy on 4/28/20.
//

#include <cmath>
#include "LoopCell.h"



void LoopCell::update() {
    if (energy_ <= 0) die();
    current_codon()->action()(*this);
    energy_ = std::clamp(energy_, 0, 100);
    move_codon();
}

Coord<float> LoopCell::codon_draw_pos(size_t idx) const {
    auto angle = (float) idx * 2 * M_PI / codons_.size();
    return {pos_.x + 3.f * cosf(angle) * RADIUS / 5, pos_.y + 3.f * sinf(angle) * RADIUS / 5};
}

void LoopCell::draw_cursor(sf::RenderWindow& w) const {
    static sf::CircleShape circle(RADIUS / 5);
    circle.setOutlineThickness(OUTLINE / 5);
    circle.setOutlineColor(sf::Color::Magenta);
    circle.setFillColor(sf::Color::Black);
    auto pos = codon_draw_pos(codon_idx_);
    circle.setPosition(pos.x - RADIUS / 5, pos.y - RADIUS / 5);
    w.draw(circle);
}

void LoopCell::draw(sf::RenderWindow& w) const {
    static sf::CircleShape circle(RADIUS);
    circle.setPosition(pos_.x - RADIUS, pos_.y - RADIUS);
    float status = std::clamp((float) energy_ / 100, 0.f, 1.f);
    sf::Color statcolor(255.f * (1.0 - status), 255.f * status, 0);
    circle.setOutlineThickness(OUTLINE);
    circle.setOutlineColor(statcolor);
    circle.setFillColor(sf::Color::Black);
    w.draw(circle);
    draw_cursor(w);
    for (size_t i = 0u; i < codons_.size(); ++i) {
        auto codon_circle = codon(i)->circle();
        auto pos = codon_draw_pos(i);
        codon_circle.setPosition(pos.x - RADIUS / 5, pos.y - RADIUS / 5);
        w.draw(codon_circle);
    }
}

