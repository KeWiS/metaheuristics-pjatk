#include <algorithm>
#include <iostream>
#include "problem.h"

Problem::Problem() {
    this->randomizer = Randomizer();
    this->possibleBoxRange = generatePossibleBoxRange();
    this->knapsack = generateKnapsack();

    this->knapsack.printKnapsack();
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

    for(std::vector<Box>::size_type i = 0; i != possibleBoxRange.size(); i++) {
        std::cout << "Box " << i << " weight: " << possibleBoxRange[i].getWeight() << "kg" << std::endl;
    }

    while (maxWeight >= currentBoxesWeight + possibleBoxRange[0].getWeight()) {
        int boxIndex = randomizer.generateIntegerNumberFromRange(0, possibleBoxRange.size() - 1);

        if (maxWeight >= currentBoxesWeight + possibleBoxRange[boxIndex].getWeight()) {
            boxesCollection.push_back(possibleBoxRange[boxIndex]);
            currentBoxesWeight += possibleBoxRange[boxIndex].getWeight();

            continue;
        }
        else if (maxWeight >= currentBoxesWeight + possibleBoxRange[0].getWeight()) {
            boxesCollection.push_back(possibleBoxRange[0]);
            currentBoxesWeight += possibleBoxRange[0].getWeight();

            continue;
        }
        break;
    }

    return boxesCollection;
}
