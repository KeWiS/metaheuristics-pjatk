#ifndef METAHEURISTICS_PJATK_PROBLEM_H
#define METAHEURISTICS_PJATK_PROBLEM_H

#include <vector>
#include "../utility/randomizer.h"
#include "knapsack.h"

class Problem {
public:
    Problem();

    std::vector<Box> generatePossibleBoxRange();

    Knapsack generateInitialKnapsack();

    std::vector<Box> generateRandomBoxesCollection(int maxWeight);

    std::vector<Knapsack> generateNeighbors();

    void removeDuplicateNeighbours(std::vector<Knapsack> &neighbors);

    bool checkIfDuplicateNeighborExists(std::vector<Knapsack> &neighbors, Knapsack &knapsack, int currentIndex);

    Randomizer *getRandomizer();

    Knapsack *getKnapsack();

    Knapsack getKnapsackCopy();

    int getGlobalKnapsackCapacity();

    std::vector<Box> getPossibleBoxRange();

    void swapKnapsack(Knapsack &knapsack);

private:
    Randomizer randomizer;
    Knapsack knapsack;

    int globalKnapsackCapacity = 0;

    std::vector<Box> possibleBoxRange;
};

#endif //METAHEURISTICS_PJATK_PROBLEM_H
