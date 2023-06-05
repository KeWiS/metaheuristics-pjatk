#include <algorithm>
#include <iostream>
#include "problem.h"
#include "hill_climbing/hill_climb.h"

Problem::Problem() {
    this->randomizer = Randomizer();
    this->possibleBoxRange = generatePossibleBoxRange();
    this->knapsack = generateKnapsack();
    knapsack.printKnapsack();

    // Hill-climb algorithm
    //  Random solution
    std::cout << "\n\nRandom hill-climb solution: " << std::endl;
    HillClimb::generateRandomSolution(*this)->printKnapsack();
    //  Deterministic solution
    std::cout << "\n\nDeterministic hill-climb solution: " << std::endl;
    HillClimb::generateDeterministicSolution(*this)->printKnapsack();
}

std::vector<Box> Problem::generatePossibleBoxRange() {
    std::vector<Box> boxRange = std::vector<Box>();
    int amountOfBoxes = randomizer.generateIntegerNumberFromRange(3, 5);

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

    return boxRange;
}

Knapsack Problem::generateKnapsack() {
    int knapsackCapacity = randomizer.generateIntegerNumberFromRange(25, 55);

    return Knapsack(knapsackCapacity, generateRandomBoxesCollection(knapsackCapacity));
}

std::vector<Box> Problem::generateRandomBoxesCollection(int maxWeight) {
    std::vector<Box> boxesCollection = std::vector<Box>();
    int currentBoxesWeight = 0;

    // Printing generated boxes range
    std::cout << "Generated boxes range:" << std::endl;
    for (std::vector<Box>::size_type i = 0; i != possibleBoxRange.size(); i++) {
        std::cout << "\tBox " << i << " weight: " << possibleBoxRange[i].getWeight() << "kg" <<
                  " | price: " << possibleBoxRange[i].getPrice() << "$" << std::endl;
    }

    std::cout << std::endl;

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

                while (copiedKnapsack.getSummedWeight() + boxOption.getWeight() < copiedKnapsack.getCapacity()) {
                    copiedKnapsack.addBox(boxOption);
                    copiedKnapsack.recalculateSummedValues();
                }

                neighbors.push_back(copiedKnapsack);
            }
        }
    }

    return neighbors;
}

Knapsack *Problem::getKnapsack() {
    return &knapsack;
}

Randomizer *Problem::getRandomizer() {
    return &randomizer;
}
