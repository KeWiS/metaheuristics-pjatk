#ifndef METAHEURISTICS_PJATK_RANDOMIZER_H
#define METAHEURISTICS_PJATK_RANDOMIZER_H

#include <random>

class Randomizer {
private:
    std::mt19937 generator;

public:
    Randomizer();

    int generateIntegerNumberFromRange(int beginNumber, int endNumber);
};

#endif //METAHEURISTICS_PJATK_RANDOMIZER_H
