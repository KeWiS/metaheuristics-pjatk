#include "box.h"

Box::Box() {}

Box::Box(int weight, int price) {
    this->weight = weight;
    this->price = price;
}

// Copy constructor
Box::Box(const Box &box) {
    this->weight = box.weight;
    this->price = box.price;
}

int Box::getWeight() {
    return this->weight;
}

int Box::getPrice() {
    return this->price;
}
