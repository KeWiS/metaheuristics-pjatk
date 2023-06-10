#include <iostream>
#include <algorithm>
#include "knapsack_problem/problem.h"

int main(int argc, char *argv[]) {
    std::vector<char *> availableAlgorithms = {
            "hill-climbing",
            "tabu-searching",
            "simulated-annealing",
            "genetic"
    };

    // Default values
    auto algorithmType = availableAlgorithms[0];
    auto iterationCount = 1000;
    auto knapsackCapacity = 40;
    auto boxAmount = 6;
    auto minBoxPrice = 1;
    auto maxBoxPrice = 10;
    auto minBoxWeight = 5;
    auto maxBoxWeight = 15;
    auto debug = true;
    // For tabu \/
    auto maxTabuSize = 100;
    // For simulated annealing \/
    auto temperatureFunctionVariant = 0;
    // For genetic \/
    auto populationCount = 32;
    auto maxVarietyPercentage = 70;
    // Reading arguments
    if (argc >= 2) {
        // Algorithm type
        algorithmType = argv[1];
        if (std::find(availableAlgorithms.begin(), availableAlgorithms.end(), "algorithmType") !=
            availableAlgorithms.end()) {
            std::cout << "Invalid algorithm argument, hill-climb chosen" << std::endl;
            algorithmType = availableAlgorithms[0];
        }
        // Iteration count
        std::string iterationCountString = argv[2];
        iterationCount = std::stoi(iterationCountString);
        // Knapsack capacity
        std::string knapsackCapacityString = argv[3];
        knapsackCapacity = std::stoi(knapsackCapacityString);
        // Box amount
        std::string boxAmountString = argv[4];
        boxAmount = std::stoi(boxAmountString);
        // Min box price
        std::string minBoxPriceString = argv[5];
        minBoxPrice = std::stoi(minBoxPriceString);
        // Max box price
        std::string maxBoxPriceString = argv[6];
        maxBoxPrice = std::stoi(maxBoxPriceString);
        // Min box weight
        std::string minBoxWeightString = argv[7];
        minBoxWeight = std::stoi(minBoxWeightString);
        // Max box weight
        std::string maxBoxWeightString = argv[8];
        maxBoxWeight = std::stoi(maxBoxWeightString);
        // Debug
        std::string debugString = argv[9];
        debug = std::stoi(debugString);
        // For tabu
        if (algorithmType == "tabu-searching") {
            std::string maxTabuSizeString = argv[10];
            maxTabuSize = std::stoi(maxTabuSizeString);
        }
        // For simulated annealing
        if (algorithmType == "simulated-annealing") {
            std::string temperatureFunctionVariantString = argv[10];
            temperatureFunctionVariant = std::stoi(temperatureFunctionVariantString);
        }
        // For genetic
        if (algorithmType == "genetic") {
            std::string populationCountString = argv[10];
            populationCount = std::stoi(populationCountString);
            std::string maxVarietyPercentageString = argv[11];
            maxVarietyPercentage = std::stoi(maxVarietyPercentageString);
        }
    }

    Problem problem(algorithmType, iterationCount, knapsackCapacity, boxAmount, minBoxPrice, maxBoxPrice, minBoxWeight,
                    maxBoxWeight, debug, maxTabuSize, temperatureFunctionVariant, populationCount, maxVarietyPercentage);

    return 0;
}
