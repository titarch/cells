//
// Created by bparsy on 4/28/20.
//

#include <cmath>
#include "LoopCell.h"


void LoopCell::update() {
    if (energy_ <= 0) return;
    current_codon()->action()(*this);
    energy_ = std::clamp(energy_, 0, 100);
    move_codon();
}

Coord<float> LoopCell::codon_draw_pos(size_t idx, float dist) const {
    auto angle = (float) idx * 2 * M_PI / codons_.size();
    return {pos_.x + cosf(angle) * RADIUS * dist, pos_.y + sinf(angle) * RADIUS * dist};
}

void LoopCell::draw_cursor(sf::RenderWindow& w) const {
    static sf::CircleShape circle(RADIUS / 5);
    circle.setOutlineThickness(OUTLINE / 5);
    circle.setOutlineColor(sf::Color::Magenta);
    circle.setFillColor(sf::Color::Black);
    auto pos = codon_draw_pos(codon_idx_, 0.7);
    circle.setPosition(pos.x - RADIUS / 5, pos.y - RADIUS / 5);
    w.draw(circle);
}

void LoopCell::draw(sf::RenderWindow& w) const {
    static sf::CircleShape circle(RADIUS);
    circle.setPosition(pos_.x - RADIUS, pos_.y - RADIUS);
    float status = std::clamp((float) energy_ / 100, 0.f, 1.f);
    sf::Color stat_color(255.f * (1.0 - status), 255.f * status, 0);
    circle.setOutlineThickness(OUTLINE);
    circle.setOutlineColor(stat_color);
    circle.setFillColor(sf::Color::Black);
    w.draw(circle);
    draw_cursor(w);
    for (size_t i = 0u; i < codons_.size(); ++i) {
        auto codon_circle = codon(i)->circle();
        auto pos = codon_draw_pos(i, 0.7);
        codon_circle.setPosition(pos.x - RADIUS / 5, pos.y - RADIUS / 5);
        w.draw(codon_circle);
    }
    auto hand_circle = hand_.circle();
    hand_circle.setPosition(pos_.x - RADIUS - RADIUS / 2, pos_.y - RADIUS - RADIUS / 2);
    w.draw(hand_circle);
    auto head_circle = sf::CircleShape(RADIUS / 5, 3);
    auto head_pos = codon_draw_pos(hand_.pos, 1.5);
    head_circle.setPosition(head_pos.x, head_pos.y);
    head_circle.setFillColor(sf::Color::Magenta);
    head_circle.rotate((float)hand_.pos * 360.f / codons_.size() - 30.f + (hand_.inward ? 180.f : 0.f));
    w.draw(head_circle);
}

