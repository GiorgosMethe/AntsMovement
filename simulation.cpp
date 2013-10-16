#include "simulation.h"
#include "omp.h"
simulation::simulation()
{
    this->world.isInitialized = false;
}

simulation::~simulation()
{

}

void simulation::init()
{
    seed();
    this->world.initializeMap(2 * this->worldWidth + 1, 2* this->worldHeight + 1);
    for(int i = 0; i < this->sampleNum; ++i)
    {
        sample tmp;
        tmp.id = i;
        tmp.position = this->nest;
        tmp.hungry = 0.0;
        this->world.addSample(tmp);
    }
    this->max_food_pheromone = 1000.0;
    this->min_food_pheromone = 0.0;
    this->max_home_pheromone = 1000.0;
    this->min_home_pheromone = 0.0;
}

void simulation::step()
{
    this->stepCount++;
    int moveX [3] = { -1, 0, 1};
    int moveY [3] = { -1, 0, 1};
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
        this->world.explored[this->world.sampleSet.at(i).position.x() + this->worldWidth][this->world.sampleSet.at(i).position.y() + this->worldHeight] = true;
    }

    this->updatePheromone();

    return;
}

void simulation::updatePheromone()
{
    std::vector<change> temp;
#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(int i = 1; i < 2 * this->worldWidth; i++){
            for(int j = 1; j < 2 * this->worldHeight; j++){
                double oldFoodValue = this->world.food_pheromone[i][j];
                double newFoodValue = this->world.food_pheromone[i][j];
                double max = 0.0;
                for(int x = -1; x < 2; x++)
                    for(int y = -1; y < 2; y++)
                        if(y!=0 && x!=0 && this->world.food_pheromone[i+x][j+y] > max){
                            max = this->world.food_pheromone[i+x][j+y];
                        }
                newFoodValue = diffusion * max;
                if(oldFoodValue < newFoodValue){
                    change tmp;
                    tmp.pos.setX(i);
                    tmp.pos.setY(j);
                    tmp.newValue = newFoodValue;
                    temp.push_back(tmp);
                }
            }
        }
    }
#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(unsigned int c = 0; c < temp.size(); c++)
            this->world.food_pheromone[temp.at(c).pos.x()][temp.at(c).pos.y()] = temp.at(c).newValue;
    }

#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(int i = 0; i < 2 * this->worldWidth + 1; i++)
            for(int j = 0; j < 2 * this->worldHeight + 1; j++)
                if(this->world.food_pheromone[i][j] != 0.0)
                    this->world.food_pheromone[i][j] *= evaporation;
    }
    temp.clear();

#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(int i = 1; i < 2 * this->worldWidth; i++){
            for(int j = 1; j < 2 * this->worldHeight; j++){
                double oldFoodValue = this->world.home_pheromone[i][j];
                double newFoodValue = this->world.home_pheromone[i][j];
                double max = 0.0;
                for(int x = -1; x < 2; x++)
                    for(int y = -1; y < 2; y++)
                        if(y!=0 && x!=0 && this->world.home_pheromone[i+x][j+y] > max){
                            max = this->world.home_pheromone[i+x][j+y];
                        }
                newFoodValue = diffusion * max;
                if(oldFoodValue < newFoodValue){
                    change tmp;
                    tmp.pos.setX(i);
                    tmp.pos.setY(j);
                    tmp.newValue = newFoodValue;
                    temp.push_back(tmp);
                }
            }
        }
    }

#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(unsigned int c = 0; c < temp.size(); c++)
            this->world.home_pheromone[temp.at(c).pos.x()][temp.at(c).pos.y()] = temp.at(c).newValue;
    }

#pragma omp parallel private(8)
    {
#pragma omp for schedule(static) nowait
        for(int i = 0; i < 2 * this->worldWidth + 1; i++)
            for(int j = 0; j < 2 * this->worldHeight + 1; j++)
                if(this->world.home_pheromone[i][j] != 0.0)
                    this->world.home_pheromone[i][j] *= evaporation;
    }
    temp.clear();
    return;
}
