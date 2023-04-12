#include "problem.h"

Problem::Problem() {
    this->randomizer = Randomizer();
    this->knapsack = generateKnapsack();

    this->knapsack.printKnapsack();
}

Knapsack Problem::generateKnapsack() {
    int knapsackCapacity = randomizer.generateIntegerNumberFromRange(10, 25);

    return Knapsack(knapsackCapacity);
}
