#include <algorithm>
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
        int boxWeight = randomizer.generateIntegerNumberFromRange(5, 10);
        int boxPrice = randomizer.generateIntegerNumberFromRange(1, 5);

        boxRange.push_back(Box(boxWeight, boxPrice));
    }

    // Sorting box range from the heaviest to the lightest
    std::sort(boxRange.begin(), boxRange.end(), [](Box& box1, Box& box2) -> bool {
        return (box1.getWeight() > box2.getWeight());
    });

    return boxRange;
}

Knapsack Problem::generateKnapsack() {
    int knapsackCapacity = randomizer.generateIntegerNumberFromRange(10, 25);

    return Knapsack(knapsackCapacity, generateRandomBoxesCollection(knapsackCapacity));
}

std::vector<Box> Problem::generateRandomBoxesCollection(int maxWeight) {
    std::vector<Box> boxesCollection = std::vector<Box>();

    for(std::vector<Box>::size_type i = 0; i != possibleBoxRange.size(); i++) {
        
    }

    return boxesCollection;
}
