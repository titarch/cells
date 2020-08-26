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

    virtual void update(float dt) {
        pos_ += speed_ * dt;

        static auto high = 1.0;
        static auto low = 1.0 - high;

        if (pos_.x() < dim_.x() * low) {
            speed_[0] = -speed_.x();
            pos_[0] = dim_.x() * low;
        }
        if (pos_.x() >= dim_.x() * high) {
            speed_[0] = -speed_.x();
            pos_[0] = dim_.x() * high;
        }
        if (pos_.y() < dim_.y() * low) {
            speed_[1] = -speed_.y();
            pos_[1] = dim_.y() * low;
        }
        if (pos_.y() >= dim_.y() * high) {
            speed_[1] = -speed_.y();
            pos_[1] = dim_.y() * high;
        }
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
