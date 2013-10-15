#ifndef MAP_H
#define MAP_H

#include <vector>
#include "ant.h"

class map
{
public:
    int width, height;
    int **antMap;
    bool isInitialized;
    std::vector<ant> ants;

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

    void addAnt(ant sample)
    {
        if(this->isInitialized)
            this->ants.push_back(sample);
        return;
    }

};


#endif // MAP_H
