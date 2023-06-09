#include <algorithm>
#include <iostream>
#include "problem.h"
#include "../hill_climbing/hill_climb.h"
#include "../tabu_search/tabu_search.h"
#include "../simulated_annealing/simulated_annealing.h"
#include "../genetic/genetic.h"

Problem::Problem() {
    this->randomizer = Randomizer();
    // Creating manually box range
//    this->possibleBoxRange = {Box(1, 1), Box(1, 2), Box(2, 3),
//                              Box(3, 6), Box(3, 7)};
//    this->knapsack = Knapsack(7, {Box(1, 1)});
//    globalKnapsackCapacity = 7;
    // Generating random box range and knapsack
    this->possibleBoxRange = generatePossibleBoxRange();
    this->knapsack = generateInitialKnapsack();
    knapsack.printKnapsack();

    // Hill-climb algorithm
    //  Random solution
    std::cout << "\n\nRandom hill-climb solution: " << std::endl;
    HillClimb::setDebug(false);
    HillClimb::generateRandomSolution(*this, 10000)->printKnapsack();
    //  Deterministic solution
    std::cout << "\n\nDeterministic hill-climb solution: " << std::endl;
    HillClimb::setDebug(false);
    HillClimb::generateDeterministicSolution(*this, 10000)->printKnapsack();

    // Tabu search algorithm
    std::cout << "\n\nTabu search solution: " << std::endl;
    TabuSearch::setDebug(false);
    TabuSearch::performTabuSearch(*this, 100000).printKnapsack();

    // Simulated annealing algorithm
    std::cout << "\n\nSimulated annealing solution: " << std::endl;
    SimulatedAnnealing::setDebug(false);
    SimulatedAnnealing::performSimulatedAnnealing(*this, 0, 5000).printKnapsack();

    // Genetic algorithm
    std::cout << "\n\nGenetic algorithm solution: " << std::endl;
    Genetic::setDebug(false);
    Genetic::performGeneticAlgorithm(*this, 32, 5000, 70).printKnapsack();
}

std::vector<Box> Problem::generatePossibleBoxRange() {
    std::vector<Box> boxRange = std::vector<Box>();
    int amountOfBoxes = randomizer.generateIntegerNumberFromRange(3, 6);

    for (int i = 1; i <= amountOfBoxes; i++) {
        int boxWeight = randomizer.generateIntegerNumberFromRange(5, 15);
        // Preventing from identical size of the box
        while (std::find_if(boxRange.begin(), boxRange.end(), [boxWeight](Box &box) {
            return box.getWeight() == boxWeight;
        }) != boxRange.end()) {
            boxWeight = randomizer.generateIntegerNumberFromRange(5, 15);
        }
        int boxPrice = randomizer.generateIntegerNumberFromRange(1, 10);

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

Knapsack Problem::generateInitialKnapsack() {
    int knapsackCapacity = randomizer.generateIntegerNumberFromRange(25, 75);

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
