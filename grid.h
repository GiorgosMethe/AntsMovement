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

    void initializeMap(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->antMap = new int*[width];
        for(int i = 0; i < width; ++i)
        {
            this->antMap[i] = new int[height];
        }
        this->isInitialized = true;
        return;
    }

    void destroyMap()
    {
        for (int i = 0; i < this->width; ++i)
            delete [] this->antMap[i];
        delete [] this->antMap;
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
