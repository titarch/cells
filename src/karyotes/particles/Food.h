//
// Created by bparsy on 4/30/20.
//

#ifndef CELLS_FOOD_H
#define CELLS_FOOD_H


#include "Particle.h"

class Food : public Particle {
public:
    Food(const Vec2f& dim, float speed, int reward) : Particle(dim, speed), reward_(reward) {}

    sf::Color color() override {
        return sf::Color::Green;
    }

    void update() override;

protected:
    int reward_;
};


#endif //CELLS_FOOD_H
