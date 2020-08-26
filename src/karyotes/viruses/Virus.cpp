//
// Created by bparsy on 8/26/20.
//

#include "../../engine/Engine.h"
#include "Virus.h"

cell_ptr Virus::collides() const {
    for (auto& cell : e_.get_cells())
        if ((pos_ - cell->pos()).sqrMagnitude() < 3 * cell->radius() * radius_)
            return cell;
    return cell_ptr();
}

viruses::const_iterator Virus::update(viruses::const_iterator cur, float dt) {
    pos_ += vel_ * dt;
    if (auto cell = collides(); cell)
        return infect(std::move(cell));
    return ++cur;
}

viruses::const_iterator Virus::infect(cell_ptr cell) {
    auto& viruses = e_.get_viruses();
    for (auto v = viruses.cbegin(); v != viruses.cend(); ++v) {
        if (v->get() == this) {
            cell->inject_codons(std::move(codons_));
            return viruses.erase(v);
        }
    }
    return viruses.cend();
}


void Virus::draw(sf::RenderWindow& w) {
    static sf::CircleShape circle(radius_);
    circle.setPosition(pos_.x() - radius_, pos_.y() - radius_);
    circle.setOutlineThickness(radius_ / 5.f);
    circle.setOutlineColor(sf::Color::Blue);
    circle.setFillColor(sf::Color::Transparent);
    w.draw(circle);
    for (size_t i = 0u; i < codons_.size(); ++i) {
        auto codon_circle = codon(i)->circle(radius_);
        auto pos = codon_draw_pos(i, 0.7);
        codon_circle.setPosition(pos.x() - radius_ / 5.f, pos.y() - radius_ / 5.f);
        w.draw(codon_circle);
    }
}

