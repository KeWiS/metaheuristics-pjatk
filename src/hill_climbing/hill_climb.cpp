#include "hill_climb.h"
#include <iostream>

Knapsack *HillClimb::generateRandomSolution(Problem problem) {
    auto bestKnapsack = problem.getKnapsack();

    for (int i = 0; i < 10000; i++) {
        auto neighbors = problem.generateNeighbors();
        if (neighbors.size() == 0) {
            break;
        }

        auto newKnapsack = getRandomNeighbor(problem, neighbors);

        newKnapsack.recalculateSummedValues();

        if (newKnapsack.getSummedPrice() >= bestKnapsack->getSummedPrice()) {
            if (debug) {
                std::cout << "Best knapsack price: " << bestKnapsack->getSummedPrice() << " | new best price: " <<
                          newKnapsack.getSummedPrice() << std::endl;
            }

            *bestKnapsack = Knapsack(newKnapsack);
        }
        else break;
    }

    return bestKnapsack;
}

Knapsack *HillClimb::generateDeterministicSolution(Problem problem) {
    auto bestKnapsack = problem.getKnapsack();

    for (int i = 0; i < 10000; i++) {
        auto neighbors = problem.generateNeighbors();
        if (neighbors.size() == 0) {
            break;
        }

        auto newKnapsack = getBestNeighbor(neighbors);

        newKnapsack.recalculateSummedValues();

        if (newKnapsack.getSummedPrice() >= bestKnapsack->getSummedPrice()) {
            if (debug) {
                std::cout << "Best knapsack price: " << bestKnapsack->getSummedPrice() << " | new best price: " <<
                          newKnapsack.getSummedPrice() << std::endl;
            }
            *bestKnapsack = Knapsack(newKnapsack);
        }
        else break;
    }

    return bestKnapsack;
}

void HillClimb::setDebug(bool debugged) {
    debug = debugged;
}
