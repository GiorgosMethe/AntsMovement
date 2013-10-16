#include "simulation.h"
#include <math.h>
#include <iostream>
#include "randomGenerator.h"
#include "omp.h"

simulation::simulation()
{

}

simulation::~simulation()
{

}

void simulation::init()
{
    seed();
    this->world.initializeMap(2 * this->worldWidth, 2* this->worldHeight);
    for(unsigned int i = 0; i < this->sampleNum; ++i)
    {
        sample tmp;
        tmp.id = i;
        tmp.position = this->nest;
        tmp.position = this->nest;
        tmp.hungry = 0.0;
        this->world.addSample(tmp);
    }
}

void simulation::step()
{
    this->stepCount++;
    int moveX [3] = { -1, 0, 1};
    int moveY [3] = { -1, 0, 1};
#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(unsigned int i = 0; i < this->world.sampleSet.size(); ++i)
        {
            sample tmp = this->world.sampleSet.at(i);
            bool sameDir = false;
            if(unifRand() < 0.76)
            {
                int x = tmp.position.x() - tmp.previousPosition.x();
                int y = tmp.position.y() - tmp.previousPosition.y();
                if(x == 0 && y == 0)
                {
                    tmp.previousPosition = tmp.position;
                    if(abs(this->world.sampleSet.at(i).position.x() + x) < this->worldWidth - 5)
                        this->world.sampleSet.at(i).position.setX(this->world.sampleSet.at(i).position.x() + x);
                    if(abs(this->world.sampleSet.at(i).position.y() + y) < this->worldHeight - 5)
                        this->world.sampleSet.at(i).position.setY(this->world.sampleSet.at(i).position.y() + y);
                    sameDir = true;
                }
            }
            if(!sameDir)
            {
                int x = floor(unifRand() / (1.00 / 3.00));
                int y = floor(unifRand() / (1.00 / 3.00));
                tmp.previousPosition = tmp.position;
                if(abs(this->world.sampleSet.at(i).position.x() + moveX[x]) < this->worldWidth - 5)
                    this->world.sampleSet.at(i).position.setX(this->world.sampleSet.at(i).position.x() + moveX[x]);
                if(abs(this->world.sampleSet.at(i).position.y() + moveY[y]) < this->worldHeight - 5)
                    this->world.sampleSet.at(i).position.setY(this->world.sampleSet.at(i).position.y() + moveY[y]);
            }
        }
    }
    return;
}
