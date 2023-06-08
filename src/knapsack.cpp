#include <iostream>
#include <algorithm>
#include "knapsack.h"

Knapsack::Knapsack() {}

Knapsack::Knapsack(int capacity, std::vector<Box> boxes) {
    this->capacity = capacity;
    this->boxes = boxes;

    for (std::vector<Box>::size_type i = 0; i != boxes.size(); i++) {
        summedWeight += boxes[i].getWeight();
        summedPrice += boxes[i].getPrice();
    }
}

// Copy constructor
Knapsack::Knapsack(const Knapsack &knapsack) {
    this->capacity = knapsack.capacity;
    this->boxes = knapsack.boxes;
    this->summedPrice = knapsack.summedPrice;
    this->summedWeight = knapsack.summedWeight;
}

void Knapsack::swapBoxAtIndex(int index, Box box) {
    boxes.at(index) = box;
}

void Knapsack::addBox(Box &box) {
    boxes.push_back(box);
}

void Knapsack::recalculateSummedValues() {
    summedWeight = 0;
    summedPrice = 0;

    for (std::vector<Box>::size_type i = 0; i != boxes.size(); i++) {
        summedWeight += boxes[i].getWeight();
        summedPrice += boxes[i].getPrice();
    }
}

int Knapsack::getCapacity() {
    return capacity;
}

int Knapsack::getSummedPrice() {
    return summedPrice;
}

int Knapsack::getSummedWeight() {
    return summedWeight;
}

std::vector<Box> &Knapsack::getBoxes() {
    return boxes;
}

std::vector<Box> Knapsack::getConstBoxes() const {
    return boxes;
}

void Knapsack::sortBoxesInside() {
    std::sort(boxes.begin(), boxes.end(), [](Box box1, Box box2) {
        return box1.getWeight() < box2.getWeight();
    });
}

void Knapsack::printKnapsack() {
    std::cout << "Current knapsack data:" << std::endl;
    // Knapsack capacity
    std::cout << "\tKnapsack capacity: " << capacity << "kg" << std::endl;
    // Variables for sum of weight and price
    int summedWeight = 0;
    int summedPrice = 0;
    // Boxes inside knapsack
    for (std::vector<Box>::size_type i = 0; i != boxes.size(); i++) {
        std::cout << "\tBox " << i << " weight: " << boxes[i].getWeight() << "kg" <<
                  " | price: " << boxes[i].getPrice() << "$" << std::endl;
        summedWeight += boxes[i].getWeight();
        summedPrice += boxes[i].getPrice();
    }
    // Printing summed weight and price
    std::cout << std::endl << "\tTotal weight: " << summedWeight << "kg" << std::endl;
    std::cout << "\tTotal price: " << summedPrice << "$" << std::endl;
}

void Knapsack::compactPrintKnapsack() {
    std::cout << "Knapsack data:" << std::endl;
    // Knapsack capacity
    // Variables for sum of weight and price
    int summedWeight = 0;
    int summedPrice = 0;
    // Boxes inside knapsack
    for (std::vector<Box>::size_type i = 0; i != boxes.size(); i++) {
        std::cout << "\tBox " << i << " weight: " << boxes[i].getWeight() << "kg" <<
                  " | price: " << boxes[i].getPrice() << "$" << std::endl;
        summedWeight += boxes[i].getWeight();
        summedPrice += boxes[i].getPrice();
    }
    // Printing summed weight and price
    std::cout << std::endl << "\tTotal weight: " << summedWeight << "kg" << std::endl;
    std::cout << "\tTotal price: " << summedPrice << "$" << std::endl;
}
