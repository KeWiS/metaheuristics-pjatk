#include <algorithm>
#include <iostream>
#include "problem.h"
#include "../hill_climbing/hill_climb.h"
#include "../tabu_search/tabu_search.h"
#include "../simulated_annealing/simulated_annealing.h"
#include "../genetic/genetic.h"

Problem::Problem(std::string algorithmType, int iterationCount, int knapsackCapacity, int boxAmount, int minBoxPrice,
                 int maxBoxPrice, int minBoxWeight, int maxBoxWeight, bool debug, int maxTabuSize,
                 int temperatureFunctionVariant, int populationCount, int maxVarietyPercentage, int crossingMethod,
                 int mutationMethod) {
    this->randomizer = Randomizer();
    // Generating random box range and knapsack
    this->possibleBoxRange = generatePossibleBoxRange(boxAmount, minBoxPrice, maxBoxPrice, minBoxWeight, maxBoxWeight);
    this->knapsack = generateInitialKnapsack(knapsackCapacity);
    knapsack.printKnapsack();

    // Hill-climb algorithm
    if (algorithmType == "hill-climbing") {
        //  Random solution
        std::cout << "\n\nRandom hill-climb solution: " << std::endl;
        HillClimb::setDebug(debug);
        HillClimb::generateRandomSolution(*this, iterationCount)->printKnapsack();
        //  Deterministic solution
        std::cout << "\n\nDeterministic hill-climb solution: " << std::endl;
        HillClimb::setDebug(debug);
        HillClimb::generateDeterministicSolution(*this, iterationCount)->printKnapsack();
    }

    // Tabu search algorithm
    if (algorithmType == "tabu-searching") {
        std::cout << "\n\nTabu search solution: " << std::endl;
        TabuSearch::setDebug(debug);
        TabuSearch::performTabuSearch(*this, iterationCount, maxTabuSize).printKnapsack();
    }

    // Simulated annealing algorithm
    if (algorithmType == "simulated-annealing") {
        std::cout << "\n\nSimulated annealing solution: " << std::endl;
        SimulatedAnnealing::setDebug(debug);
        SimulatedAnnealing::performSimulatedAnnealing(*this, temperatureFunctionVariant, iterationCount).printKnapsack();
    }

    // Genetic algorithm
    if (algorithmType == "genetic") {
        std::cout << "\n\nGenetic algorithm solution: " << std::endl;
        Genetic::setDebug(debug);
        Genetic::performGeneticAlgorithm(*this, populationCount, iterationCount, maxVarietyPercentage, crossingMethod, mutationMethod).printKnapsack();
    }
}

std::vector<Box> Problem::generatePossibleBoxRange(int boxAmount, int minBoxPrice, int maxBoxPrice, int minBoxWeight,
                                                   int maxBoxWeight) {
    std::vector<Box> boxRange = std::vector<Box>();
    for (int i = 1; i <= boxAmount; i++) {
        int boxWeight = randomizer.generateIntegerNumberFromRange(minBoxWeight, maxBoxWeight);
        // Preventing from identical size of the box
        while (std::find_if(boxRange.begin(), boxRange.end(), [boxWeight](Box &box) {
            return box.getWeight() == boxWeight;
        }) != boxRange.end()) {
            boxWeight = randomizer.generateIntegerNumberFromRange(minBoxWeight, maxBoxWeight);
        }
        int boxPrice = randomizer.generateIntegerNumberFromRange(minBoxPrice, maxBoxPrice);

        boxRange.push_back(Box(boxWeight, boxPrice));
    }

    // Sorting box range from the heaviest to the lightest
    std::sort(boxRange.begin(), boxRange.end(), [](Box &box1, Box &box2) {
        return (box1.getWeight() < box2.getWeight());
    });

    // Printing generated boxes range
    std::cout << "Generated boxes range:" << std::endl;
    for (std::vector<Box>::size_type i = 0; i != boxRange.size(); i++) {
        std::cout << "\tBox " << i << " weight: " << boxRange[i].getWeight() << "kg" <<
                  " | price: " << boxRange[i].getPrice() << "$" << std::endl;
    }

    std::cout << std::endl;

    return boxRange;
}

Knapsack Problem::generateInitialKnapsack(int knapsackCapacity) {
    globalKnapsackCapacity = knapsackCapacity;

    return Knapsack(knapsackCapacity, generateRandomBoxesCollection(knapsackCapacity));
}

std::vector<Box> Problem::generateRandomBoxesCollection(int maxWeight) {
    std::vector<Box> boxesCollection = std::vector<Box>();
    int currentBoxesWeight = 0;

    while (maxWeight >= currentBoxesWeight + possibleBoxRange[0].getWeight()) {
        int boxIndex = randomizer.generateIntegerNumberFromRange(0, possibleBoxRange.size() - 1);

        if (maxWeight >= currentBoxesWeight + possibleBoxRange[boxIndex].getWeight()) {
            boxesCollection.push_back(possibleBoxRange[boxIndex]);
            currentBoxesWeight += possibleBoxRange[boxIndex].getWeight();

            continue;
        } else if (maxWeight >= currentBoxesWeight + possibleBoxRange[0].getWeight()) {
            boxesCollection.push_back(possibleBoxRange[0]);
            currentBoxesWeight += possibleBoxRange[0].getWeight();

            continue;
        }
        break;
    }

    return boxesCollection;
}

std::vector<Knapsack> Problem::generateNeighbors() {
    auto neighbors = std::vector<Knapsack>{};

    for (std::vector<Box>::size_type i = 0; i != knapsack.getBoxes().size(); i++) {
        for (auto boxOption : possibleBoxRange) {
            if (knapsack.getBoxes()[i].getWeight() == boxOption.getWeight()) continue;
            if (knapsack.getCapacity() >=
                knapsack.getSummedWeight() - knapsack.getBoxes()[i].getWeight() + boxOption.getWeight()) {
                Knapsack copiedKnapsack = Knapsack(knapsack);

                copiedKnapsack.swapBoxAtIndex(i, boxOption);
                copiedKnapsack.recalculateSummedValues();

                while (copiedKnapsack.getSummedWeight() + boxOption.getWeight() <= copiedKnapsack.getCapacity()) {
                    copiedKnapsack.addBox(boxOption);
                    copiedKnapsack.recalculateSummedValues();
                }

                copiedKnapsack.sortBoxesInside();

                neighbors.push_back(copiedKnapsack);
            }
        }
    }

    removeDuplicateNeighbours(neighbors);

    return neighbors;
}

void Problem::removeDuplicateNeighbours(std::vector<Knapsack> &neighbors) {
    std::vector<Knapsack>::iterator it = neighbors.begin();

    while (it != neighbors.end()) {
        if (checkIfDuplicateNeighborExists(neighbors, *it, it - neighbors.begin())) it = neighbors.erase(it);
        else ++it;
    }
}

bool Problem::checkIfDuplicateNeighborExists(std::vector<Knapsack> &neighbors, Knapsack &knapsack, int currentIndex) {
    return std::find(neighbors.begin() + currentIndex + 1, neighbors.end(), knapsack) != neighbors.end();
}

Randomizer *Problem::getRandomizer() {
    return &randomizer;
}

Knapsack *Problem::getKnapsack() {
    return &knapsack;
}

Knapsack Problem::getKnapsackCopy() {
    return knapsack;
}

int Problem::getGlobalKnapsackCapacity() {
    return globalKnapsackCapacity;
}

std::vector<Box> Problem::getPossibleBoxRange() {
    return possibleBoxRange;
}

void Problem::swapKnapsack(Knapsack &knapsack) {
    this->knapsack = knapsack;
}
