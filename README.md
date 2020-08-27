# Principle

Fun little cellular automata simulation with cells, viruses and food particles.
This project is highly inspired from [carykh](https://www.youtube.com/watch?v=o1IheoDRdGE)'s virus simulator,
except that cells are round, move, can divide (and some other things). Also this is optimized to allow simulations
to run very fast (with a reasonable number of objects).

Quick explanation:
- Cells have codons which are all describing an action like eat, move hand or repair itself.
They repeat all their codons in circle and eventually divide or die whether they were able to get enough
energy (mainly from food) or not.
- Viruses are inactive packs of codons floating in space forever until they meet a cell in which case they
infect them by injecting all the codons they contain. With the right codons, you can make a virus that exploits
a cell into making more viruses.
- Food particles are very simple, they wander in space and can be eaten by cells when they are in range. Cells and
viruses keep track of the food that was eaten by them (cells) or put into them (viruses) such that when they disappear
they give back to the space to amount of food they took, thus allowing to maintain conservation of energy and not
making the simulation go too much crazy.

# Build
## Requirements
- cmake
- sfml

## Instructions
```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
./cells
```
