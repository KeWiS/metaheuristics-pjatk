#include <iostream>
#include <algorithm>
#include "knapsack_problem/problem.h"

int main(int argc, char *argv[]) {
    std::vector<char *> availableAlgorithms = {
            "hill-climbing",
            "tabu-searching",
            "simulated-annealing",
            "genetic",
            "all"
    };

    // Default values
    auto algorithmType = availableAlgorithms[4];
    auto iterationCount = 1000;
    auto knapsackCapacity = 500;
    auto boxAmount = 25;
    auto minBoxPrice = 1;
    auto maxBoxPrice = 100;
    auto minBoxWeight = 1;
    auto maxBoxWeight = 100;
    auto debug = false;
    // For tabu \/
    auto maxTabuSize = -1;
    // For simulated annealing \/
    auto temperatureFunctionVariant = 0;
    // For genetic \/
    auto populationCount = 500;
    auto maxVarietyPercentage = 80;
    auto crossingMethod = 0;
    auto mutationMethod = 0;
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
        if (debug != 0 && debug != 1) {
            std::cout << "Invalid debug argument, debug = true chosen" << std::endl;
            debug = true;
        }
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
            std::string crossingMethodString = argv[12];
            crossingMethod = std::stoi(crossingMethodString);
            if (crossingMethod != 0 && crossingMethod != 1) {
                std::cout << "Invalid crossingMethod argument, chosen" << std::endl;
                crossingMethod = 0;
            }
            std::string mutationMethodString = argv[13];
            mutationMethod = std::stoi(mutationMethodString);
            if (mutationMethod != 0 && mutationMethod != 1) {
                std::cout << "Invalid mutationMethod argument, chosen" << std::endl;
                mutationMethod = 0;
            }
        }
    }

    Problem problem(algorithmType, iterationCount, knapsackCapacity, boxAmount, minBoxPrice, maxBoxPrice, minBoxWeight,
                    maxBoxWeight, debug, maxTabuSize, temperatureFunctionVariant, populationCount, maxVarietyPercentage,
                    crossingMethod, mutationMethod);

    return 0;
}
