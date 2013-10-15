#ifndef SIMULATION_H
#define SIMULATION_H

#include "grid.h"
#include "QPoint"

class simulation
{
public:
    simulation();
    void init(unsigned int number, int width, int height, QPoint initialPoint);
    ~simulation();
    void step();
    grid world;
};

#endif // SIMULATION_H
