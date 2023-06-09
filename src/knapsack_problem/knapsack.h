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

    bool operator==(const Knapsack &knapsack2) {
        if (this->getConstBoxes().size() != knapsack2.getConstBoxes().size()) return false;

        for (std::vector<Box>::size_type i = 0; i != this->getConstBoxes().size(); i++) {
            if (this->getConstBoxes()[i].getWeight() != knapsack2.getConstBoxes()[i].getWeight()) return false;
        }

        return true;
    }

    void swapBoxAtIndex(int index, Box box);

    void addBox(Box &box);

    void recalculateSummedValues();

    int getCapacity();

    int getSummedPrice();

    int getSummedWeight();

    std::vector<Box> &getBoxes();

    std::vector<Box> getConstBoxes() const;

    void sortBoxesInside();

    void printKnapsack();

    void compactPrintKnapsack();

private:
    int capacity;
    int summedPrice = 0;
    int summedWeight = 0;

    std::vector<Box> boxes;
};

#endif //METAHEURISTICS_PJATK_KNAPSACK_H
