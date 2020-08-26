//
// Created by bparsy on 8/26/20.
//

#ifndef CELLS_VIRUS_H
#define CELLS_VIRUS_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_set>
#include <utility>
#include "../codons/LoopCodon.h"
#include "../../utils/Vector.h"
#include "../Cell.h"

class Engine;

class Virus;

using virus_ptr = std::unique_ptr<Virus>;
using viruses = std::unordered_set<virus_ptr>;


class Virus {
public:
    Virus(Engine& e, Vec2f pos, Vec2f vel) : e_(e), radius_(10.f), pos_(pos), vel_(vel) {}

    template<typename C>
    Virus& push_codon(C const& codon) {
        codons_.push_back(std::make_shared<C>(codon));
        return *this;
    }

    template<typename C, typename ...Args>
    Virus& emplace_codon(Args... args) {
        codons_.push_back(std::make_shared<C>(args...));
        return *this;
    }

    [[nodiscard]] float radius() const { return radius_; }

    [[nodiscard]] Vec2f pos() const { return pos_; }

    void set_pos(Vec2f const& p) { pos_ = p; }

    void add_pos(Vec2f const& p) { pos_ += p; }

    [[nodiscard]] Vec2f vel() const { return vel_; }

    void set_vel(Vec2f const& v) { vel_ = v; }

    void add_vel(Vec2f const& v) { vel_ += v; }

    void brake(float frot = 0.5) { vel_ *= frot; }

    [[nodiscard]] loop_codon_ptr codon(size_t idx) const {
        return std::static_pointer_cast<LoopCodon>(codons_[idx]);
    }

    [[nodiscard]] Vec2f codon_draw_pos(size_t idx, float dist) const {
        auto angle = (float) idx * 2 * M_PI / codons_.size();
        return {{pos_.x() + cosf(angle) * radius_ * dist, pos_.y() + sinf(angle) * radius_ * dist}};
    }

    [[nodiscard]] cell_ptr collides() const;
    viruses::const_iterator update(viruses::const_iterator cur, float dt);
    viruses::const_iterator infect(cell_ptr cell);
    void draw(sf::RenderWindow& w);

    void push_codons(action_funcs const& actions) {
        for (auto const& f : actions)
            emplace_codon<LoopCodon>(100, f);
    }

    static Virus simple_killer(Engine& e, Vec2f const& pos, Vec2f const& vel) {
        Virus v(e, pos, vel);
        v.push_codons({
                              LoopCodon::hand_outwards(50)
                      });
        return v;
    }

protected:
    Engine& e_;
    float radius_;
    Vec2f pos_, vel_;
    codons codons_;
};

#endif //CELLS_VIRUS_H
