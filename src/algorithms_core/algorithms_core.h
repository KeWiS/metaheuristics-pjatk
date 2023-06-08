#ifndef METAHEURISTICS_PJATK_ALGORITHMS_CORE_H
#define METAHEURISTICS_PJATK_ALGORITHMS_CORE_H

#include <algorithm>
#include "../knapsack.h"
#include "../problem.h"

class AlgorithmsCore {
protected:
    static Knapsack getRandomNeighbor(Problem &problem, std::vector<Knapsack> &neighbors) {
        return neighbors[problem.getRandomizer()->generateIntegerNumberFromRange(0, neighbors.size() - 1)];
    }

    static Knapsack getBestNeighbor(std::vector<Knapsack> &neighbors) {
        return *std::max_element(neighbors.begin(), neighbors.end(),
                                 [](auto neighbor1, auto neighbor2) {

                                     return neighbor1.getSummedPrice() <= neighbor2.getSummedPrice();
                                 });
    }
};

#endif //METAHEURISTICS_PJATK_ALGORITHMS_CORE_H
