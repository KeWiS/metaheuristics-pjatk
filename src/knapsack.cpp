#include <iostream>
#include "knapsack.h"

Knapsack::Knapsack() {}

Knapsack::Knapsack(int capacity) {
    this->capacity = capacity;
}

void Knapsack::printKnapsack() {
    std::cout << "Knapsack capacity: " << capacity << "kg";
}
