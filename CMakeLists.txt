cmake_minimum_required(VERSION 3.24)
project(metaheuristics_pjatk)

set(CMAKE_CXX_STANDARD 17)

add_executable(metaheuristics_pjatk src/main.cpp src/knapsack.h src/knapsack.cpp src/randomizer.h src/randomizer.cpp src/problem.h src/problem.cpp src/box.h src/box.cpp src/hill_climbing/hill_climb.h src/hill_climbing/hill_climb.cpp src/tabu_search/tabu_search.h src/tabu_search/tabu_search.cpp src/algorithms_core/algorithms_core.h)
