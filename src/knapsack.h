#ifndef METAHEURISTICS_PJATK_KNAPSACK_H
#define METAHEURISTICS_PJATK_KNAPSACK_H

#include <vector>
#include "box.h"

class Knapsack {
public:
    Knapsack();

    Knapsack(int capacity, std::vector<Box> boxes);

    // Copy constructor
    Knapsack(const Knapsack &knapsack);

    void swapBoxAtIndex(int index, Box box);

    void addBox(Box &box);

    void recalculateSummedValues();

    int getCapacity();

    int getSummedPrice();

    int getSummedWeight();

    std::vector<Box> getBoxes();

    void printKnapsack();

private:
    int capacity;
    int summedPrice = 0;
    int summedWeight = 0;
    std::vector<Box> boxes;
};

#endif //METAHEURISTICS_PJATK_KNAPSACK_H
