#include <iostream>
#include "engine/Engine.h"
#include "karyotes/particles/Food.h"

int main() {
    Engine e(1920, 1080, 10);
    e.push_cell(LoopCell::dividable(e, {{1920 / 2, 1080 / 2}}));
    e.push_virus(Virus::replicator(e, {{0, 0}}, {{40, 60}}));
//    e.push_virus(Virus::efficient_cancer_inducer(e, {{0, 0}}, {{40, 60}}));
//    e.push_virus(Virus::cancer_inducer(e, {{0, 0}}, {{60, 40}}));
    e.add_particles<Food>(2000, Vec2f{{1920, 1080}}, 50, 15);
    e.run();
}
