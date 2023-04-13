#ifndef METAHEURISTICS_PJATK_PROBLEM_H
#define METAHEURISTICS_PJATK_PROBLEM_H
#include <vector>
#include "randomizer.h"
#include "knapsack.h"

class Problem{
private:
    Randomizer randomizer;
    Knapsack knapsack;

    std::vector<Box> possibleBoxRange;

public:
    Problem();

    std::vector<Box> generatePossibleBoxRange();
    Knapsack generateKnapsack();
    std::vector<Box> generateRandomBoxesCollection(int maxWeight);
};

#endif //METAHEURISTICS_PJATK_PROBLEM_H
