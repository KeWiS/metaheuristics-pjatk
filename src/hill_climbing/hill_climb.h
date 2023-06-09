#ifndef METAHEURISTICS_PJATK_HILL_CLIMB_H
#define METAHEURISTICS_PJATK_HILL_CLIMB_H

#include "../algorithms_core/algorithms_core.h"

class HillClimb : public AlgorithmsCore {
public:
    static Knapsack *generateRandomSolution(Problem problem);

    static Knapsack *generateDeterministicSolution(Problem problem);

    static void setDebug(bool debugged);

private:
    inline static bool debug = false;
};

#endif //METAHEURISTICS_PJATK_HILL_CLIMB_H
