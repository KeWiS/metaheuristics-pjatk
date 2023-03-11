cmake_minimum_required(VERSION 3.24)
project(metaheuristics_pjatk)

set(CMAKE_CXX_STANDARD 17)

add_executable(metaheuristics_pjatk src/main.cpp src/knapsack.h src/knapsack.cpp)
