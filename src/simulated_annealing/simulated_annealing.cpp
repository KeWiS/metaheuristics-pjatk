#include <iostream>
#include "simulated_annealing.h"

Knapsack SimulatedAnnealing::performSimulatedAnnealing(Problem problem, int temperatureFunctionVariant, int iterationCount) {
    auto randomGenerator = problem.getRandomizer()->getGenerator();
    auto bestKnapsack = problem.getKnapsackCopy();
    auto currentKnapsack = problem.getKnapsackCopy();

    for (int i = 1; i < iterationCount; i++) {
        // Problem will contain current solution
        auto neighbors = problem.generateNeighbors();
        if (neighbors.size() == 0) {
            break;
        }

        auto newKnapsack = getRandomNeighbor(problem, neighbors);

        newKnapsack.recalculateSummedValues();

        if (newKnapsack.getSummedPrice() >= currentKnapsack.getSummedPrice()) {
            if (debug) {
                std::cout << "\tCurrent knapsack price: " << currentKnapsack.getSummedPrice() <<
                          " | new curret price: " << newKnapsack.getSummedPrice() << std::endl;
            }

            currentKnapsack = Knapsack(newKnapsack);
            problem.swapKnapsack(currentKnapsack);

            if (newKnapsack.getSummedPrice() >= bestKnapsack.getSummedPrice()) {
                if (debug) {
                    std::cout << "Best knapsack price: " << currentKnapsack.getSummedPrice() << " | new best price: " <<
                              newKnapsack.getSummedPrice() << std::endl;
                }

                bestKnapsack = Knapsack(currentKnapsack);
            }
        } else {
            std::uniform_real_distribution<double> u(0.0, 1.0);
            auto uk = u(randomGenerator);
            auto expo = std::exp(
                    -std::abs(newKnapsack.getSummedPrice() - currentKnapsack.getSummedPrice()) /
                    temperatureFunctionVariants[temperatureFunctionVariant](i));
            if (uk < expo) {
                if (debug) {
                    std::cout << "\tCurrent knapsack price: " << currentKnapsack.getSummedPrice() <<
                              " | new curret price: " << newKnapsack.getSummedPrice() << std::endl;
                }

                currentKnapsack = Knapsack(newKnapsack);
                problem.swapKnapsack(currentKnapsack);
            }
        }
    }

    return bestKnapsack;
}

void SimulatedAnnealing::setDebug(bool debugged) {
    debug = debugged;
}
