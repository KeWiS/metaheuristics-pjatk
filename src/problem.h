#ifndef METAHEURISTICS_PJATK_PROBLEM_H
#define METAHEURISTICS_PJATK_PROBLEM_H

#include <vector>
#include "randomizer.h"
#include "knapsack.h"

class Problem {
public:
    Problem();

    std::vector<Box> generatePossibleBoxRange();

    Knapsack generateKnapsack();

    std::vector<Box> generateRandomBoxesCollection(int maxWeight);

    std::vector<Knapsack> generateNeighbors();

    Knapsack *getKnapsack();

    Randomizer *getRandomizer();

private:
    Randomizer randomizer;
    Knapsack knapsack;

    std::vector<Box> possibleBoxRange;
};

#endif //METAHEURISTICS_PJATK_PROBLEM_H
