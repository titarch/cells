#include <iostream>
#include "engine/Engine.h"
#include "karyotes/particles/Food.h"

int main() {
    Engine e(1920, 1080, 15);
    e.push_cell(LoopCell::dividable(e, {{1920 / 2, 1080 / 2}}));
    e.push_virus(Virus::simple_killer(e, {{0, 0}}, {{60, 40}}));
    e.add_particles<Food>(2000, Vec2f{{1920, 1080}}, 50, 15);
    e.run();
}
