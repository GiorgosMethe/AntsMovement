#include "simulation.h"

simulation::simulation()
{

}

simulation::~simulation()
{

}

void simulation::init(unsigned int number, int width, int height, QPoint initialPoint)
{
    this->world.initializeMap(2*width, 2*height);
    for(unsigned int i = 0; i < number; ++i)
    {
        sample tmp;
        tmp.id = i;
        tmp.position = initialPoint;
        tmp.hungry = 0.0;
        this->world.addSample(tmp);
    }
}

void simulation::step()
{
    for(unsigned int i = 0; i < this->world.sampleSet.size(); ++i)
    {
    }
}
