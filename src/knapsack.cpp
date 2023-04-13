#include <iostream>
#include "knapsack.h"

Knapsack::Knapsack() {}

Knapsack::Knapsack(int capacity, std::vector<Box> boxes) {
    this->capacity = capacity;
    this->boxes = boxes;
}

void Knapsack::printKnapsack() {
    // Knapsack capacity
    std::cout << "Knapsack capacity: " << capacity << "kg" << std::endl;
    // Boxes inside knapsack
    for(std::vector<Box>::size_type i = 0; i != boxes.size(); i++) {
        std::cout << "Box " << i << " weight: " << boxes[i].getWeight() << "kg" << std::endl;
        std::cout << "Box " << i << " price: " << boxes[i].getPrice() << "$" << std::endl;
    }
}
