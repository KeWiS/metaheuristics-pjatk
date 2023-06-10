#include <iostream>
#include <map>
#include "genetic.h"

Knapsack Genetic::performGeneticAlgorithm(Problem problem, int populationCount, int iterationCount,
                                          double maxVarietyPercentage, int crossingMethod, int mutationMethod) {
    maxVarietyTerminationPercentage = maxVarietyPercentage;

    generateInitialPopulation(problem, populationCount);

    while (terminalCondition(iterationCount)) {
        performFitnessRecalculations();
        auto parents = performParentsSelection(problem);
        auto offspring = performCrossover(problem, parents, crossingMethod);
        // Mutated offspring below
        offspring = performRandomMutations(problem, offspring, mutationMethod);
        // Replacing current population with created offspring
        population = offspring;
    }
    // Returning the most valuable knapsack in population
    return *std::max_element(population.begin(), population.end(), [](Knapsack knapsack1, Knapsack knapsack2) {
        return knapsack1.getSummedPrice() < knapsack2.getSummedPrice();
    });
}

void Genetic::generateInitialPopulation(Problem &problem, int populationCount) {
    auto knapsackCapacity = problem.getGlobalKnapsackCapacity();

    for (int i = 1; i <= populationCount; i++) {
        population.push_back(Knapsack(knapsackCapacity,
                                      problem.generateRandomBoxesCollection(knapsackCapacity)));
    }
}

bool Genetic::terminalCondition(int iterationCount) {
    // First terminal condition: iteration count
    // Second terminal condition:
    return iterationCount > i++ && checkIfPopulationIsVaried();
}

bool Genetic::checkIfPopulationIsVaried() {
    if (maxVarietyTerminationPercentage == -1) {
        return true;
    }
    auto lackOfVarietyMarker = population.size() * maxVarietyTerminationPercentage / 100;
    auto knapsackSamenessMap = std::map<int, int>{};

    for (auto &knapsack : population) {
        auto knapsackSummedPrice = knapsack.getSummedPrice();

        if (knapsackSamenessMap.count(knapsackSummedPrice)) {
            knapsackSamenessMap[knapsackSummedPrice] += 1;
        } else {
            knapsackSamenessMap[knapsackSummedPrice] = 1;
        }

        if (knapsackSamenessMap[knapsackSummedPrice] >= lackOfVarietyMarker) {
            std::cout << "End due to lack of population variety" << std::endl;

            return false;
        }
    }

    return true;
}

void Genetic::performFitnessRecalculations() {
    for (std::vector<Knapsack>::size_type j = 0; j != population.size(); j++) {
        population[j].recalculateSummedValues();
        population[j].sortBoxesInside();
    }
}

std::vector<Knapsack> Genetic::performParentsSelection(Problem &problem) {
    // Tournament selection is performed
    std::vector<Knapsack> parents = std::vector<Knapsack>{};

    while (parents.size() < population.size()) {
        auto knapsack1 = population[problem.getRandomizer()->generateIntegerNumberFromRange(0,
                                                                                            population.size() - 1)];
        auto knapsack2 = population[problem.getRandomizer()->generateIntegerNumberFromRange(0,
                                                                                            population.size() - 1)];

        if (knapsack1.getSummedPrice() >= knapsack2.getSummedPrice()) parents.push_back(knapsack1);
        else parents.push_back(knapsack2);
    }

    return parents;
}

std::vector<Knapsack> Genetic::performCrossover(Problem &problem, std::vector<Knapsack> parents, int crossingMethod) {
    std::vector<Knapsack> offspring = std::vector<Knapsack>{};

    for (std::vector<Knapsack>::size_type j = 0; j != population.size(); j += 2) {
        auto crossedKnapsacks = crossKnapsacks(problem, population[j],
                                               population[j + 1], crossingMethod);

        offspring.push_back(crossedKnapsacks.first);
        offspring.push_back(crossedKnapsacks.second);
    }

    return offspring;
}

std::pair<Knapsack, Knapsack> Genetic::crossKnapsacks(Problem &problem, Knapsack parent1, Knapsack parent2,
                                                      int crossingMethod) {
    auto offspringPair = std::make_pair(parent1, parent2);

    // Selecting random crossing method
    if (crossingMethod == 0) {
        // One crossing point in the middle
        auto parentBoxesCount = parent1.getBoxes().size();
        if (parentBoxesCount > parent2.getBoxes().size()) parentBoxesCount = parent2.getBoxes().size();
        auto crossingPoint = parentBoxesCount / 2;
        // Creating a pair of boxes sets for crossing purposes
        std::pair<std::vector<Box>, std::vector<Box>> parent1Boxes = {
                std::vector<Box>(parent1.getBoxes().begin(), parent1.getBoxes().begin() + crossingPoint),
                std::vector<Box>(parent1.getBoxes().begin() + crossingPoint, parent1.getBoxes().end())
        };
        std::pair<std::vector<Box>, std::vector<Box>> parent2Boxes = {
                std::vector<Box>(parent2.getBoxes().begin(), parent2.getBoxes().begin() + crossingPoint),
                std::vector<Box>(parent2.getBoxes().begin() + crossingPoint, parent2.getBoxes().end())
        };
        // Creating new box vectors for offspring
        parent1Boxes.first.insert(parent1Boxes.first.end(),
                                  parent2Boxes.second.begin(),
                                  parent2Boxes.second.end());
        std::vector<Box> offspring1Boxes = parent1Boxes.first;

        parent2Boxes.first.insert(parent2Boxes.first.end(),
                                  parent1Boxes.second.begin(),
                                  parent1Boxes.second.end());
        std::vector<Box> offspring2Boxes = parent2Boxes.first;


        offspringPair.first = Knapsack(problem.getGlobalKnapsackCapacity(), offspring1Boxes);
        offspringPair.second = Knapsack(problem.getGlobalKnapsackCapacity(), offspring2Boxes);
    } else {
        // Two crossing points (PMX)
        auto parentBoxesCount = parent1.getBoxes().size();
        if (parentBoxesCount > parent2.getBoxes().size()) parentBoxesCount = parent2.getBoxes().size();
        auto crossingPoints = parentBoxesCount / 3;
        // Creating a tuple of boxes sets for crossing purposes
        std::tuple<std::vector<Box>, std::vector<Box>, std::vector<Box>> parent1Boxes = {
                std::vector<Box>(parent1.getBoxes().begin(), parent1.getBoxes().begin() + crossingPoints),
                std::vector<Box>(parent1.getBoxes().begin() + crossingPoints,
                                 parent1.getBoxes().end() - crossingPoints),
                std::vector<Box>(parent1.getBoxes().end() - crossingPoints, parent1.getBoxes().end())
        };
        std::tuple<std::vector<Box>, std::vector<Box>, std::vector<Box>> parent2Boxes = {
                std::vector<Box>(parent2.getBoxes().begin(), parent2.getBoxes().begin() + crossingPoints),
                std::vector<Box>(parent2.getBoxes().begin() + crossingPoints,
                                 parent2.getBoxes().end() - crossingPoints),
                std::vector<Box>(parent2.getBoxes().end() - crossingPoints, parent2.getBoxes().end())
        };
        // Creating new box vectors for offspring
        std::get<0>(parent1Boxes).insert(std::get<0>(parent1Boxes).end(),
                                         std::get<1>(parent2Boxes).begin(),
                                         std::get<1>(parent2Boxes).end());
        std::get<0>(parent1Boxes).insert(std::get<0>(parent1Boxes).end(),
                                         std::get<2>(parent1Boxes).begin(),
                                         std::get<2>(parent1Boxes).end());
        std::vector<Box> offspring1Boxes = std::get<0>(parent1Boxes);

        std::get<0>(parent2Boxes).insert(std::get<0>(parent2Boxes).end(),
                                         std::get<1>(parent1Boxes).begin(),
                                         std::get<1>(parent1Boxes).end());
        std::get<0>(parent2Boxes).insert(std::get<0>(parent2Boxes).end(),
                                         std::get<2>(parent2Boxes).begin(),
                                         std::get<2>(parent2Boxes).end());
        std::vector<Box> offspring2Boxes = std::get<0>(parent2Boxes);

        offspringPair.first = Knapsack(problem.getGlobalKnapsackCapacity(), offspring1Boxes);
        offspringPair.second = Knapsack(problem.getGlobalKnapsackCapacity(), offspring2Boxes);
    }

    fixKnapsackBoxCollectionsAfterCrossover(problem, offspringPair.first);
    fixKnapsackBoxCollectionsAfterCrossover(problem, offspringPair.second);

    return offspringPair;
}

void Genetic::fixKnapsackBoxCollectionsAfterCrossover(Problem &problem, Knapsack &offspringKnapsack) {
    // Checking if crossover caused knapsack overload and fixing if it did
    if (offspringKnapsack.getSummedWeight() > problem.getGlobalKnapsackCapacity()) {
        auto currentBoxBeingFixed = offspringKnapsack.getBoxes().size() - 1;
        auto indexOfBoxRangeToBeReplaced = problem.getPossibleBoxRange().size() - 1;

        while (offspringKnapsack.getSummedWeight() > problem.getGlobalKnapsackCapacity()) {
            offspringKnapsack.swapBoxAtIndex(currentBoxBeingFixed,
                                             problem.getPossibleBoxRange()[indexOfBoxRangeToBeReplaced]);
            offspringKnapsack.recalculateSummedValues();

            if (indexOfBoxRangeToBeReplaced > 0) {
                indexOfBoxRangeToBeReplaced--;
            } else {
                currentBoxBeingFixed--;
                indexOfBoxRangeToBeReplaced = problem.getPossibleBoxRange().size() - 1;
            }
        }
    }
}

std::vector<Knapsack> Genetic::performRandomMutations(Problem &problem, std::vector<Knapsack> offspring,
                                                      int mutationMethod) {
    for (auto &knapsack : offspring) {
        // Checking if mutation should occur, there is 1% chance for mutation
        if (problem.getRandomizer()->generateIntegerNumberFromRange(1, 100) == 100) {
            if (debug) {
                std::cout << "Mutation on knapsack:" << std::endl;
                knapsack.compactPrintKnapsack();
            }
            // Making sure boxes are sorted inside knapsack
            knapsack.sortBoxesInside();
            // Select random mutation method
            if (mutationMethod == 0) {
                // Changing the heaviest box to the different one
                auto heaviestBoxIndex = knapsack.getBoxes().size() - 1;

                while (heaviestBoxIndex > 0) {
                    for (int j = problem.getPossibleBoxRange().size() - 1; j > 0; j--) {
                        if (knapsack.getCapacity() >= knapsack.getSummedWeight() -
                                                      knapsack.getBoxes()[heaviestBoxIndex].getWeight() +
                                                      problem.getPossibleBoxRange()[j].getWeight()
                            && problem.getPossibleBoxRange()[j].getWeight() !=
                               knapsack.getBoxes()[heaviestBoxIndex].getWeight()) {
                            knapsack.swapBoxAtIndex(heaviestBoxIndex, problem.getPossibleBoxRange()[j]);
                            knapsack.recalculateSummedValues();
                            knapsack.sortBoxesInside();
                            // Stopping mutation on knapsack
                            heaviestBoxIndex = 1;
                            break;
                        }
                    }
                    heaviestBoxIndex--;
                }
            } else {
                // Changing few of the lightest boxes to the one with higher weight
                auto amountOfBoxesToReplace = 1;

                while (amountOfBoxesToReplace < knapsack.getBoxes().size() / 2) {
                    auto summedBoxesToReplaceWeight = 0;
                    for (int j = 0; j < amountOfBoxesToReplace; j++) {
                        summedBoxesToReplaceWeight += knapsack.getBoxes()[j].getWeight();
                    }

                    for (int k = problem.getPossibleBoxRange().size() - 1; k > 0; k--) {
                        if (knapsack.getCapacity() >= knapsack.getSummedWeight() - summedBoxesToReplaceWeight +
                                                      problem.getPossibleBoxRange()[k].getWeight()) {
                            knapsack.getBoxes().erase(knapsack.getBoxes().begin(), knapsack.getBoxes().begin() +
                                                                                   amountOfBoxesToReplace);
                            knapsack.getBoxes().push_back(problem.getPossibleBoxRange()[k]);
                            knapsack.recalculateSummedValues();
                            knapsack.sortBoxesInside();
                            // Stopping mutation on knapsack
                            amountOfBoxesToReplace = knapsack.getBoxes().size();
                            break;
                        }
                    }
                    amountOfBoxesToReplace++;
                }
            }
        }
    }

    return offspring;
}

void Genetic::setDebug(bool debugged) {
    debug = debugged;
}
