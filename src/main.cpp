#include <iostream>
#include "engine/Engine.h"
#include "karyotes/particles/Food.h"

int main() {
    Engine e(1920, 1080, 25);
    e.push_cell(LoopCell::dividable(e, e.dim() / 2.f));
    e.push_virus(Virus::efficient_cancer_inducer(e, {{0, 0}}, {{40, 60}}));
    e.add_particles<Food>(2000, Vec2f{{1920, 1080}}, 50, 15);
    e.run();
}
