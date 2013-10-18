#ifndef SIMULATION_H
#define SIMULATION_H

#include "grid.h"
#include "QPoint"
#include <math.h>
#include <iostream>
#include "randomGenerator.h"
#include "omp.h"
#include <string.h>
#include "simulationVariables.h"

class simulation
{
public:

    simulation();

    void init();

    ~simulation();

    void step();

    grid world;

    int stepCount;

    QPoint food;
    QPoint nest;

    double max_food_pheromone;
    double min_food_pheromone;

    double max_home_pheromone;
    double min_home_pheromone;

    void setSampleNum(int sN)
    {
        this->sampleNum = sN;
    }

    void setFoodPos(QPoint f)
    {
        this->food = f;
    }

    void setNestPos(QPoint n)
    {
        this->nest = n;
    }

    void setWorldDim(int w, int h)
    {
        this->worldWidth = w;
        this->worldHeight = h;
    }

private:
    // simulation
    int sampleNum;
    int worldWidth;
    int worldHeight;
    void updateHomePheromone();
    void updateFoodPheromone();

    QPoint world2table(QPoint wP)
    {
        QPoint tmp;
        tmp.setX(wP.x() + this->worldWidth);
        tmp.setY(wP.y() + this->worldHeight);
        return tmp;
    }

    struct change
    {
        QPoint pos;
        double newValue;
    };
    std::vector<change> temp;

    // Agent
    void droppingPheromone(QPoint position);
    void agentAction(sample &agent);
    void randomAgentAction(sample &agent);
    void agentActionSelection(sample &tmp);
    void agentPheromoneUpdate(sample tmp);
    void updateHunger(sample &tmp);
    void greedyAgentAction(sample &tmp);
};

#endif // SIMULATION_H
