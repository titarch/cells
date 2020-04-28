//
// Created by bparsy on 4/28/20.
//

#ifndef CELLS_LOOPCODON_H
#define CELLS_LOOPCODON_H


#include <memory>
#include "Codon.h"

class LoopCell;

using action_func = std::function<void(LoopCell&)>;
using action_funcs = std::vector<action_func>;

class LoopCodon : public Codon {
public:
    explicit LoopCodon(int durability, action_func action = noop)
            : Codon(), max_durability_(durability), durability_(durability), action_(std::move(action)) {}

    action_func action() {
        if (durability_ <= 0) return noop;
        durability_ -= 5;
        return action_;
    }

    void self_repair() { durability_ = max_durability_; }

    [[nodiscard]] int durability() const { return durability_; }

    float vitality() const { return (float) durability_ / max_durability_; }

    sf::CircleShape circle() const;

    static void noop(LoopCell& c);
    static void hand_inwards(LoopCell& c);
    static void hand_outwards(LoopCell& c);
    static void eat(LoopCell& c);
    static void locate_weak(LoopCell& c);
    static void repair(LoopCell& c);
protected:
    int max_durability_, durability_;
    action_func action_;
};

using loop_codon_ptr = std::shared_ptr<LoopCodon>;


#endif //CELLS_LOOPCODON_H
