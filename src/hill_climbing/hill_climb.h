#ifndef METAHEURISTICS_PJATK_HILL_CLIMB_H
#define METAHEURISTICS_PJATK_HILL_CLIMB_H

#include "../algorithms_core/algorithms_core.h"

class HillClimb : public AlgorithmsCore {
public:
    static Knapsack *generateRandomSolution(Problem problem);

    static Knapsack *generateDeterministicSolution(Problem problem);
};

#endif //METAHEURISTICS_PJATK_HILL_CLIMB_H
