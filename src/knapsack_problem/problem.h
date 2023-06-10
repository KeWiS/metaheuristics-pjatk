#ifndef METAHEURISTICS_PJATK_PROBLEM_H
#define METAHEURISTICS_PJATK_PROBLEM_H

#include <vector>
#include "../utility/randomizer.h"
#include "knapsack.h"

class Problem {
public:
    Problem(std::string algorithmType, int iterationCount, int knapsackCapacity, int boxAmount, int minBoxPrice,
            int maxBoxPrice, int minBoxWeight, int maxBoxWeight, bool debug, int maxTabuSize,
            int temperatureFunctionVariant, int populationCount, int maxVarietyPercentage);

    std::vector<Box> generatePossibleBoxRange(int boxAmount, int minBoxPrice, int maxBoxPrice, int minBoxWeight,
                                              int maxBoxWeight);

    Knapsack generateInitialKnapsack(int knapsackCapacity);

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
