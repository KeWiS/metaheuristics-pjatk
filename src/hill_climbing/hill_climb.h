#ifndef METAHEURISTICS_PJATK_HILL_CLIMB_H
#define METAHEURISTICS_PJATK_HILL_CLIMB_H

#include "../knapsack.h"
#include "../problem.h"

class HillClimb {
public:
    static Knapsack *generateRandomSolution(Problem &problem);

    static Knapsack *generateDeterministicSolution(Problem &problem);

private:
    static Knapsack getRandomNeighbor(Problem &problem);

    static Knapsack getBestNeighbor(Problem &problem);
};

#endif //METAHEURISTICS_PJATK_HILL_CLIMB_H
