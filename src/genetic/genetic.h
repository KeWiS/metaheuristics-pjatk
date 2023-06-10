#ifndef METAHEURISTICS_PJATK_GENETIC_H
#define METAHEURISTICS_PJATK_GENETIC_H

#include "../algorithms_core/algorithms_core.h"

class Genetic : public AlgorithmsCore {
public:
    static Knapsack performGeneticAlgorithm(Problem problem, int populationCount, int iterationCount,
                                            double maxVarietyPercentage, int crossingMethod, int mutationMethod);

    static void setDebug(bool debugged);

private:
    inline static bool debug = false;
    // Setting to -1 due to condition checking characteristics (incrementing before checking index)
    inline static int i = -1;

    inline static int maxVarietyTerminationPercentage = 70;

    inline static std::vector<Knapsack> population = std::vector<Knapsack>{};

    static void generateInitialPopulation(Problem &problem, int populationCount);

    static bool terminalCondition(int iterationCount);

    static bool checkIfPopulationIsVaried();

    static void performFitnessRecalculations();

    static std::vector<Knapsack> performParentsSelection(Problem &problem);

    static std::vector<Knapsack> performCrossover(Problem &problem, std::vector<Knapsack> parents, int crossingMethod);

    static std::pair<Knapsack, Knapsack> crossKnapsacks(Problem &problem, Knapsack parent1, Knapsack parent2,
                                                        int crossingMethod);

    static void fixKnapsackBoxCollectionsAfterCrossover(Problem &problem, Knapsack &offspringKnapsack);

    static std::vector<Knapsack> performRandomMutations(Problem &problem, std::vector<Knapsack> offspring, int mutationMethod);
};

#endif //METAHEURISTICS_PJATK_GENETIC_H
