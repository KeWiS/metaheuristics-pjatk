#ifndef METAHEURISTICS_PJATK_KNAPSACK_H
#define METAHEURISTICS_PJATK_KNAPSACK_H

#include <vector>
#include "box.h"

class Knapsack {
private:
    int capacity;
    std::vector<Box> boxes;

public:
    Knapsack();

    Knapsack(int capacity, std::vector<Box> boxes);

    void printKnapsack();
};

#endif //METAHEURISTICS_PJATK_KNAPSACK_H
