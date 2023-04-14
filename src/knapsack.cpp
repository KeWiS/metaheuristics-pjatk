#include <iostream>
#include "knapsack.h"

Knapsack::Knapsack() {}

Knapsack::Knapsack(int capacity, std::vector<Box> boxes) {
    this->capacity = capacity;
    this->boxes = boxes;
}

void Knapsack::printKnapsack() {
    // Knapsack capacity
    std::cout << std::endl << "Knapsack capacity: " << capacity << "kg" << std::endl;
    // Variables for sum of weight and price
    int summedWeight = 0;
    int summedPrice = 0;
    // Boxes inside knapsack
    for(std::vector<Box>::size_type i = 0; i != boxes.size(); i++) {
        std::cout << "Box " << i << " weight: " << boxes[i].getWeight() << "kg" <<
        " | price: " << boxes[i].getPrice() << "$" << std::endl;
        summedWeight += boxes[i].getWeight();
        summedPrice += boxes[i].getPrice();
    }
    // Printing summed weight and price
    std::cout << std::endl << "Total weight: " << summedWeight << "kg" << std::endl;
    std::cout << "Total price: " << summedPrice << "$";
}
