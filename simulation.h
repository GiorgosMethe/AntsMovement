#ifndef SIMULATION_H
#define SIMULATION_H

#include "grid.h"
#include "QPoint"
#include <math.h>
#include <iostream>
#include "randomGenerator.h"
#include <string.h>
#include "simulationVariables.h"

class simulation
{
public:

    simulation();
    /*
     * @return: initialize the simulation
     */
    void init();

    ~simulation();

    /*
     * @return: runs a step of the simulation
     */
    void step();

    grid world;

    int stepCount;

    QPoint food;
    QPoint nest;

    double exploreRatio;
    double hungerLevel;

    void evaporation();
    void diffusion();

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

    /*
     * @params: point in the world
     * @return: point in the array
     */
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

    /*
     * @params: position of the ant
     * @return: drops pheromone to the specific array cell
     */
    void droppingPheromone(QPoint position);
    /*
     * @params: agent
     * @return: changes the position of the agent
     */
    void agentAction(sample &agent);
    /*
     * @params: agent
     * @return: random action
     */
    void randomAgentAction(sample &agent);
    /*
     * @params: agent
     * @return: greedy action selection
     */
    void agentActionSelection(sample &tmp);
    /*
     * @params: agent
     * @return: updates pheromone on agent's trails
     */
    void agentPheromoneUpdate(sample tmp);
    /*
     * @params: agent
     * @return: updates the hunger levels
     */
    void updateHunger(sample &tmp);
    /*
     * @params: agent
     * @return: greedy action selection
     */
    void greedyAgentAction(sample &tmp);
};

#endif // SIMULATION_H
