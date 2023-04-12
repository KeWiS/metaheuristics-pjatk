#ifndef METAHEURISTICS_PJATK_PROBLEM_H
#define METAHEURISTICS_PJATK_PROBLEM_H
#include "randomizer.h"
#include "knapsack.h"

class Problem{
private:
    Randomizer randomizer;
    Knapsack knapsack;

public:
    Problem();

    Knapsack generateKnapsack();
};

#endif //METAHEURISTICS_PJATK_PROBLEM_H
