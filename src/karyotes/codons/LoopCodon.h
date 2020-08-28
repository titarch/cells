//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_LOOPCODON_H
#define CELLS_LOOPCODON_H


#include <memory>
#include "Codon.h"
#include "../particles/Particle.h"

class LoopCell;

class Engine;

using action_func = std::function<void(LoopCell&)>;
using action_funcs = std::vector<action_func>;

class LoopCodon : public Codon {
public:
    explicit LoopCodon(int durability, action_func action = noop(1))
            : Codon(), max_durability_(durability), durability_(durability), action_(std::move(action)) {}

    ~LoopCodon() override = default;

    codon_ptr clone() const override {
        return std::make_shared<LoopCodon>(*this);
    }

    action_func action() {
        if (durability_ <= 0) return noop(1);
        durability_ -= 5;
        return action_;
    }

    void self_repair() { durability_ = max_durability_; }

    [[nodiscard]] int durability() const { return durability_; }

    float vitality() const { return (float) durability_ / max_durability_; }

    sf::CircleShape circle(float radius) const;

    static action_func noop(int cost);
    static action_func hand_inwards(int cost);
    static action_func hand_outwards(int cost);
    static action_func eat();
    static action_func locate_weak(int cost);
    static action_func repair(int cost, int threshold);
    static action_func active_loc(int cost);
    static action_func read(int cost, int start, int end);
    static action_func write(int cost);
    static action_func clear_mem();
    static action_func mem_codon(int cost, const action_func& action);
    static action_func divide(Engine& e, int threshold);
protected:
    int max_durability_, durability_;
    action_func action_;
};

using loop_codon_ptr = std::shared_ptr<LoopCodon>;


#endif //CELLS_LOOPCODON_H
