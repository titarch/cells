//
// Created by bparsy on 4/30/20.
//

#ifndef CELLS_PARTICLE_H
#define CELLS_PARTICLE_H


#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <unordered_set>
#include "../../utils/Vector.h"

class Particle {
public:
    explicit Particle(Vec2f const& dim, float speed) : dim_(dim), pos_(dim % Vec2f::random()),
                                                       speed_(Vec2f::signed_random().normalized() * speed) {}
    virtual ~Particle() = default;

    virtual void update() {
        pos_ += speed_;
        if (pos_.x() < 0) speed_[0] = -speed_.x();
        if (pos_.x() >= dim_.x()) speed_[0] = -speed_.x();
        if (pos_.y() < 0) speed_[1] = -speed_.y();
        if (pos_.y() >= dim_.y()) speed_[1] = -speed_.y();
    }

    virtual sf::Color color() = 0;

    void draw(sf::RenderWindow& w, float radius) {
        sf::CircleShape c(radius);
        c.setPosition(pos_ - Vec2f::fill(radius));
        c.setFillColor(color());
        w.draw(c);
    }

    [[nodiscard]] Vec2f pos() const { return pos_; }

protected:
    Vec2f dim_, pos_, speed_;
};

using particle_ptr = std::unique_ptr<Particle>;
using particles = std::unordered_set<particle_ptr>;

#endif //CELLS_PARTICLE_H
