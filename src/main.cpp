#include <iostream>
#include "engine/Engine.h"

int main() {
    std::srand(std::time(nullptr));
    Engine e(1920, 1080);
    e.push_cell(LoopCell::dividable({{500, 500}}, e));
    e.run();
}
