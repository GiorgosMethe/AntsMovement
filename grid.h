#ifndef GRID_H
#define GRID_H

#include <vector>
#include "sample.h"

class grid
{
public:
    int width, height;
    int **antMap;
    bool isInitialized;
    std::vector<sample> sampleSet;
    double **home_pheromone;
    double **food_pheromone;

    void initializeMap(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->antMap = new int*[width];
        this->food_pheromone = new double*[width];
        this->home_pheromone = new double*[width];
        for(int i = 0; i < width; ++i)
        {
            this->antMap[i] = new int[height];
            this->food_pheromone[i] = new double[height];
            this->home_pheromone[i] = new double[height];
        }
        this->isInitialized = true;
        return;
    }

    void destroyMap()
    {
        for (int i = 0; i < this->width; ++i)
        {
            delete [] this->antMap[i];
            delete [] this->food_pheromone[i];
            delete [] this->home_pheromone[i];
        }
        delete [] this->antMap;
        delete [] this->food_pheromone;
        delete [] this->home_pheromone;
        this->isInitialized = false;
        return;
    }

    void addSample(sample a)
    {
        if(this->isInitialized)
            this->sampleSet.push_back(a);
        return;
    }

};


#endif // GRID_H
