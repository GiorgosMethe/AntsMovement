#ifndef SIMULATION_H
#define SIMULATION_H

#include "grid.h"
#include "QPoint"

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
    int sampleNum;
    int worldWidth;
    int worldHeight;

    QPoint world2table(QPoint wP)
    {
        QPoint tmp;
        tmp.setX(wP.x() + this->worldWidth);
        tmp.setY(wP.y() + this->worldHeight);
        return tmp;
    }
};

#endif // SIMULATION_H
