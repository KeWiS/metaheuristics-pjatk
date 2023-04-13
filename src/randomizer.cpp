#include <iostream>
#include "randomizer.h"

Randomizer::Randomizer() {
    std::random_device randomDevice;
    this->generator = (std::mt19937) randomDevice();
}

int Randomizer::generateIntegerNumberFromRange(int beginNumber, int endNumber) {
    std::uniform_int_distribution<> distribution(beginNumber, endNumber);

    return distribution(this->generator);
}
