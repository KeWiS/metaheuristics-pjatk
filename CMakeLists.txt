cmake_minimum_required(VERSION 3.24)
project(metaheuristics_pjatk)

set(CMAKE_CXX_STANDARD 17)

add_executable(metaheuristics_pjatk src/main.cpp src/knapsack_problem/knapsack.h src/knapsack_problem/knapsack.cpp src/utility/randomizer.h src/utility/randomizer.cpp src/knapsack_problem/problem.h src/knapsack_problem/problem.cpp src/knapsack_problem/box.h src/knapsack_problem/box.cpp src/hill_climbing/hill_climb.h src/hill_climbing/hill_climb.cpp src/tabu_search/tabu_search.h src/tabu_search/tabu_search.cpp src/algorithms_core/algorithms_core.h src/simulated_annealing/simulated_annealing.h src/simulated_annealing/simulated_annealing.cpp src/genetic/genetic.h src/genetic/genetic.cpp)
