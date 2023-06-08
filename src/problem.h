#ifndef METAHEURISTICS_PJATK_PROBLEM_H
#define METAHEURISTICS_PJATK_PROBLEM_H

#include <vector>
#include "randomizer.h"
#include "knapsack.h"

class Problem {
public:
    Problem(bool debug);

    std::vector<Box> generatePossibleBoxRange();

    Knapsack generateKnapsack();

    std::vector<Box> generateRandomBoxesCollection(int maxWeight);

    std::vector<Knapsack> generateNeighbors();

    void removeDuplicateNeighbours(std::vector<Knapsack> &neighbors);

    bool checkIfDuplicateNeighborExists(std::vector<Knapsack> &neighbors, Knapsack &knapsack, int currentIndex);

    static bool isDebug();

    Knapsack *getKnapsack();

    Knapsack getKnapsackCopy();

    Randomizer *getRandomizer();

    void swapKnapsack(Knapsack &knapsack);

private:
    inline static bool debug = false;
    Randomizer randomizer;
    Knapsack knapsack;

    std::vector<Box> possibleBoxRange;
};

#endif //METAHEURISTICS_PJATK_PROBLEM_H
