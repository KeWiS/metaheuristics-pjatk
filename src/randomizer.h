#ifndef METAHEURISTICS_PJATK_RANDOMIZER_H
#define METAHEURISTICS_PJATK_RANDOMIZER_H

#include <random>

class Randomizer {
public:
    Randomizer();

    int generateIntegerNumberFromRange(int beginNumber, int endNumber);

private:
    std::mt19937 generator;
};

#endif //METAHEURISTICS_PJATK_RANDOMIZER_H
