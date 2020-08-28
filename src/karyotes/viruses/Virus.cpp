//
// Created by bparsy on 8/26/20.
//

#include "../../engine/Engine.h"
#include "Virus.h"

cell_ptr Virus::collides() const {
    for (auto& cell : e_.get_cells())
        if ((pos_ - cell->pos()).sqrMagnitude() < std::pow(0.75f * cell->radius() + radius_, 2))
            return cell;
    return cell_ptr();
}

viruses::const_iterator Virus::update(viruses::const_iterator cur, float dt) {
    pos_ += vel_ * dt * 5.f;
    static auto high = 1.0;
    static auto low = 1.0 - high;

    static auto const& dim = e_.dim();
    if (pos_.x() < dim.x() * low) {
        vel_[0] = -vel_.x();
        pos_[0] = dim.x() * low;
    }
    if (pos_.x() >= dim.x() * high) {
        vel_[0] = -vel_.x();
        pos_[0] = dim.x() * high;
    }
    if (pos_.y() < dim.y() * low) {
        vel_[1] = -vel_.y();
        pos_[1] = dim.y() * low;
    }
    if (pos_.y() >= dim.y() * high) {
        vel_[1] = -vel_.y();
        pos_[1] = dim.y() * high;
    }

    if (auto cell = collides(); cell)
        return infect(std::move(cell));
    return ++cur;
}

viruses::const_iterator Virus::infect(cell_ptr cell) {
    auto& viruses = e_.get_viruses();
    for (auto v = viruses.cbegin(); v != viruses.cend(); ++v) {
        if (v->get() == this) {
            std::dynamic_pointer_cast<LoopCell>(cell)->inject_codons(std::move(codons_));
            return viruses.erase(v);
        }
    }
    return viruses.cend();
}


void Virus::draw(sf::RenderWindow& w) {
    static sf::CircleShape circle{};
    circle.setPointCount(codons_.size());
    circle.setRadius(radius_);
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

