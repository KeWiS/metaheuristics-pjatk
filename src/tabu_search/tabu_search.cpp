#include "tabu_search.h"
#include <iostream>

Knapsack TabuSearch::performTabuSearch(Problem problem, int iterationCount, int maxTabuSize) {
    auto bestKnapsack = problem.getKnapsackCopy();

    tabu.push_back(bestKnapsack);

    for (int i = 0; i < iterationCount; i++) {
        auto neighbors = problem.generateNeighbors();

        for (std::vector<Knapsack>::size_type j = 0; j != tabu.size(); j++) {
            auto tabuEntry = tabu[j];
            tabuEntry.sortBoxesInside();

            auto foundInTabu = std::find(neighbors.begin(), neighbors.end(), tabuEntry);

            if (foundInTabu != neighbors.end()) {
                neighbors.erase(foundInTabu);

                if (neighbors.size() == 0) {
                    std::cout << "Tabu ate it's own tail :(" << std::endl;

                    return bestKnapsack;
                }
            }
        }

        if (neighbors.size() == 0) {
            return bestKnapsack;
        }

        auto newKnapsack = getBestNeighbor(neighbors);

        newKnapsack.recalculateSummedValues();

        if (newKnapsack.getSummedPrice() >= bestKnapsack.getSummedPrice()) {
            if (debug) {
                std::cout << "Best knapsack price: " << bestKnapsack.getSummedPrice() << " | new best price: " <<
                          newKnapsack.getSummedPrice() << std::endl;
            }

            bestKnapsack = Knapsack(newKnapsack);
        }

        // Deleting tabu from the front
        if (maxTabuSize != -1 && tabu.size() >= maxTabuSize) {
            tabu.erase(tabu.begin());
        }

        tabu.push_back(newKnapsack);
        problem.swapKnapsack(tabu[tabu.size() - 1]);
    }

    return bestKnapsack;
}

void TabuSearch::setDebug(bool debugged) {
    debug = debugged;
}
