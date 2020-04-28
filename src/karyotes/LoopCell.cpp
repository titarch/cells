//
// Created by bparsy on 4/28/20.
//

#include "LoopCell.h"

void LoopCell::update() {
    if (energy_ <= 0) die();
    current_codon()->action()(*this);
    move_codon();
}

void LoopCell::draw(sf::RenderWindow &w) const {
    static sf::CircleShape circle(50);
    circle.setPosition(pos_.x, pos_.y);
    float status = std::clamp((float)energy_ / 100, 0.f, 1.f);
    sf::Color statcolor(255.f * (1.0 - status), 255.f * status, 0);
    circle.setFillColor(statcolor);
    w.draw(circle);
}
