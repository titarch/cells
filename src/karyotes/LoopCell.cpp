//
// Created by bparsy on 4/28/20.
//

#include <cmath>
#include "../engine/Engine.h"
#include "LoopCell.h"
#include "particles/Food.h"

std::ostream& operator<<(std::ostream& os, LoopCell const& lp) {
    return os
            << "Position: " << lp.pos_
            << "\nCodon number: " << lp.codons_.size()
            << std::endl;
}

std::string LoopCell::info() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

cells::const_iterator LoopCell::update(cells::const_iterator cur) {
    if (energy_ <= 0) return die();
    current_codon()->action()(*this);
    energy_ = std::clamp(energy_, 0, 100);
    move_codon();
    return ++cur;
}

cells::const_iterator LoopCell::die() {
    auto& cells = e_.get_cells();
    for (auto c = cells.cbegin(); c != cells.cend(); ++c) {
        if (c->get() == this) {
            e_.add_particles<Food>(food_accumulated_, Vec2f{{1920, 1080}}, 50, 15);
            return cells.erase(c);
        }
    }
    return cells.cend();
}

Vec2f LoopCell::codon_draw_pos(size_t idx, float dist) const {
    auto angle = (float) idx * 2 * M_PI / codons_.size();
    return {{pos_.x() + cosf(angle) * radius_ * dist, pos_.y() + sinf(angle) * radius_ * dist}};
}

void LoopCell::draw_cursor(sf::RenderWindow& w) const {
    static sf::CircleShape circle(radius_ / 5);
    circle.setOutlineThickness(radius_ / 25);
    circle.setOutlineColor(sf::Color::Magenta);
    circle.setFillColor(sf::Color::Black);
    auto pos = codon_draw_pos(codon_idx_, 0.7);
    circle.setPosition(pos.x() - radius_ / 5, pos.y() - radius_ / 5);
    w.draw(circle);
}

void LoopCell::draw(sf::RenderWindow& w) const {
    static sf::CircleShape circle{};
    circle.setRadius(radius_);
    circle.setPosition(pos_.x() - radius_, pos_.y() - radius_);
    float status = std::clamp((float) energy_ / 100, 0.f, 1.f);
    sf::Color stat_color(255.f * (1.0 - status), 255.f * status, 0);
    circle.setOutlineThickness(radius_ / 5);
    circle.setOutlineColor(stat_color);
    circle.setFillColor(sf::Color::Transparent);
    w.draw(circle);
    draw_cursor(w);
    for (size_t i = 0u; i < codons_.size(); ++i) {
        auto codon_circle = codon(i)->circle(radius_);
        auto pos = codon_draw_pos(i, 0.7);
        codon_circle.setPosition(pos.x() - radius_ / 5, pos.y() - radius_ / 5);
        w.draw(codon_circle);
    }
    auto hand_circle = hand_.circle(infected_ ? sf::Color::Yellow : sf::Color::Cyan);
    hand_circle.setPosition(pos_.x() - radius_ - radius_ / 2, pos_.y() - radius_ - radius_ / 2);
    w.draw(hand_circle);
    auto head_circle = sf::CircleShape(radius_ / 5, 3);
    auto head_pos = codon_draw_pos(hand_.pos, 1.5);
    head_circle.setPosition(head_pos.x(), head_pos.y());
    head_circle.setFillColor(sf::Color::Magenta);
    head_circle.rotate((float) hand_.pos * 360.f / codons_.size() - 30.f + (hand_.inward ? 180.f : 0.f));
    w.draw(head_circle);
}
