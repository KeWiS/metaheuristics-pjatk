#ifndef METAHEURISTICS_PJATK_BOX_H
#define METAHEURISTICS_PJATK_BOX_H

class Box {
public:
    Box();

    Box(int weight, int price);

    // Copy constructor
    Box(const Box &box);

    int getWeight();

    int getPrice();

private:
    int weight;
    int price;
};

#endif //METAHEURISTICS_PJATK_BOX_H
