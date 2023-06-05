#include "hill_climb.h"
#include <algorithm>
#include <iostream>

Knapsack *HillClimb::generateRandomSolution(Problem &problem) {
    auto bestKnapsack = problem.getKnapsack();

    for (int i = 0; i < 100000; i++) {
        auto newKnapsack = getRandomNeighbor(problem);



        newKnapsack.recalculateSummedValues();

        if (newKnapsack.getSummedPrice() >= bestKnapsack->getSummedPrice()) *bestKnapsack = Knapsack(newKnapsack);
        else break;
    }

    return bestKnapsack;
}

Knapsack *HillClimb::generateDeterministicSolution(Problem &problem) {
    auto bestKnapsack = problem.getKnapsack();

    for (int i = 0; i < 100000; i++) {
        auto newKnapsack = getBestNeighbor(problem);

        newKnapsack.recalculateSummedValues();

        if (newKnapsack.getSummedPrice() >= bestKnapsack->getSummedPrice()) *bestKnapsack = Knapsack(newKnapsack);
        else break;
    }

    return bestKnapsack;
}

Knapsack HillClimb::getRandomNeighbor(Problem &problem) {
    auto neighbors = problem.generateNeighbors();

    if (neighbors.empty()) return *problem.getKnapsack();

    return neighbors[problem.getRandomizer()->generateIntegerNumberFromRange(0, neighbors.size() - 1)];
}

Knapsack HillClimb::getBestNeighbor(Problem &problem) {
    auto neighbors = problem.generateNeighbors();

    if (neighbors.empty()) return *problem.getKnapsack();

    return *std::max_element(neighbors.begin(), neighbors.end(),
                            [](auto neighbor1, auto neighbor2) {

                                return neighbor1.getSummedPrice() < neighbor2.getSummedPrice();
                            });
}
