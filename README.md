# metaheuristics-pjatk - Knapsack problem
The knapsack problem is the following problem in combinatorial optimization:

Given a set of items, each with a weight and a value, determine which items to include in the collection so that the total weight is less than or equal to a given limit and the total value is as large as possible. (source: wikipedia)

Default required parameters, brief explanation and example values:
- algorithmType - One of available algorithms;
  1. hill-climbing
  2. tabu-searching
  3. simulated-annealing
  4. genetic
  5. all - this one is special, it calls all algorithms with default parameters but for same knapsack, when calling this leave additional parameters empty, they will run on default
- iterationCount - Amount of program iterations; 1000
- knapsackCapacity - Capacity of generated knapsack (shared with all of them); 40
- boxAmount - Amount of boxes for possible box range; 6
- minBoxPrice - Min. price of the box generated for possible box range; 1
- maxBoxPrice - Max. price of the box generated for possible box range; 10
- minBoxWeight - Min. weight of the box generated for possible box range; 1
- maxBoxWeight - Max. weight of the box generated for possible box range; 10
- debug - Determine if program should show debug information (0 - no, everything else - yes); 0

Below you can find parameters for specific algorithms (insert them in order after required parameters)<br><br>
Parameters for tabu-search algorithm:
- maxTabuSize - Max. tabu size (if -1 is given it will be unlimited); 100

Parameters for simulated annealing algorithm:
- temperatureFunctionVariant - Variant of temperature function (0, 1, 2 values only); 0
  - 0 | 1000.0 / k
  - 1 | 1000.0 / log10(k)
  - 2 | 0.6^k


Parameters for genetic algorithm:
- populationCount - Population count of genetic algorithm; 32
- maxVarietyPercentage - Max. percentage value for terminal condition of main loop; 70
- crossingMethod - Crossing method (0, 1), when other value is inserted it is defaulted to 0; 0
  - 0 - Crossing with single cut
  - 1 - Crossing with two cuts (PMX), (0, 1), when other value is inserted it is defaulted to 0; 0
- mutationMethod - Mutation method; 0
  - 0 - This mutation changes the heaviest box to the different one
  - 1 - This mutation changes one or few the lightest box to one heavier