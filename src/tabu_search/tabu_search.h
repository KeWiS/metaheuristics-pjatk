#ifndef METAHEURISTICS_PJATK_TABU_SEARCH_H
#define METAHEURISTICS_PJATK_TABU_SEARCH_H

#include <vector>
#include "../algorithms_core/algorithms_core.h"

class TabuSearch : public AlgorithmsCore {
public:
    inline static std::vector<Knapsack> tabu = std::vector<Knapsack>{};

    static Knapsack performTabuSearch(Problem problem, int iterationCount, int maxTabuSize);

    static void setDebug(bool debugged);

private:
    inline static bool debug = false;
};

#endif //METAHEURISTICS_PJATK_TABU_SEARCH_H
