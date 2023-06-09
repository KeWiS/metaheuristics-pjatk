#ifndef METAHEURISTICS_PJATK_SIMULATED_ANNEALING_H
#define METAHEURISTICS_PJATK_SIMULATED_ANNEALING_H

#include <map>
#include "../algorithms_core/algorithms_core.h"

class SimulatedAnnealing : public AlgorithmsCore {
public:
    static Knapsack performSimulatedAnnealing(Problem problem, int temperatureFunctionVariant, int iterationCount);

    static void setDebug(bool debugged);

private:
    inline static bool debug = false;
    // Temperature function variants
    inline static std::map<int, std::function<double(int)>> temperatureFunctionVariants {
        {0, [](int k) { return 1000.0 / k; }},
        {1, [](int k) { return 1000.0 / std::log10(k); }},
        {2, [](int k) { return std::pow(0.6, k); }}
    };
};

#endif //METAHEURISTICS_PJATK_SIMULATED_ANNEALING_H
