//
// Created by bparsy on 4/30/20.
//

#ifndef CELLS_FOOD_H
#define CELLS_FOOD_H


#include "Particle.h"

class Food : public Particle {
public:
    Food(const Vec2f& dim, const Vec2f& pos, float speed, int reward) : Particle(dim, pos, speed), reward_(reward) {}

    Food(const Vec2f& dim, float speed, int reward) : Particle(dim, speed), reward_(reward) {}

    ~Food() override = default;

    sf::Color color() override {
        return sf::Color::Green;
    }

    void update(float dt) override;

    [[nodiscard]] int reward() const { return reward_; };

protected:
    int reward_;
};

using food_ptr = std::unique_ptr<Food>;


#endif //CELLS_FOOD_H
