#include <iostream>
#include "engine/Engine.h"
#include "karyotes/particles/Food.h"

int main() {
    Engine e(1920, 1080);
    e.push_cell(LoopCell::dividable(e, {{500, 500}}));
    e.add_particles<Food>(2000, Vec2f{{1920, 1080}}, 5, 15);
    e.run();
}
