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
    this->world.initializeMap(this->worldWidth, this->worldHeight);
    for(int i = 0; i < this->sampleNum; ++i)
    {
        sample tmp;
        tmp.id = i;
        tmp.position = this->nest;
        tmp.hungry = 1.0;
        this->world.addSample(tmp);
    }
    this->max_food_pheromone = 1000.0;
    this->max_home_pheromone = 1000.0;
}

void simulation::step()
{
    this->stepCount++;
    for(unsigned int i = 0; i < this->world.sampleSet.size(); ++i)
    {
        this->agentAction(this->world.sampleSet.at(i));
    }
    return;
}

void simulation::agentAction(sample &tmp)
{
    this->updateHunger(tmp);
    this->droppingPheromone(tmp.position);
    this->agentActionSelection(tmp);
    this->agentPheromoneUpdate(tmp);
    this->world.explored[tmp.position.x()][tmp.position.y()] = true;

    double a = sqrt(pow(tmp.position.x() - tmp.previousPosition.x(),2) + pow(tmp.position.y() - tmp.previousPosition.y(),2));
    if(a > 1.41422){
        std::cout << "ERROR " << a <<std::endl;
    }
    return;
}

void simulation::updateHunger(sample &tmp)
{
    if(tmp.position.x() >= foodX && tmp.position.x() <= foodX + foodSize && tmp.position.y() >= foodY && tmp.position.y() <= foodY + foodSize)
        tmp.hungry = 0.0;
    else
        tmp.hungry = min(tmp.hungry + hungry_step, 1.0);

}

void simulation::agentActionSelection(sample &tmp)
{
    if(unifRand() > 0.8)
        this->randomAgentAction(tmp);
    else
        this->greedyAgentAction(tmp);
    return;
}

void simulation::greedyAgentAction(sample &tmp)
{
//    double max = 0.0;
//    int dx = 0, dy = 0;
//    if(tmp.hungry > hungry_threshold)
//    {
//        for(int x = -1; x < 2; x++)
//            for(int y = -1; y < 2; y++)
//                if(y!=0 && x!=0 && this->world.food_pheromone[tmp.position.x()+x][tmp.position.y()+y] > max){
//                    max = this->world.food_pheromone[tmp.position.x()+x][tmp.position.y()+y];
//                    dx = x;
//                    dy = y;
//                }
//    }
//    else
//    {
//        for(int x = -1; x < 2; x++)
//            for(int y = -1; y < 2; y++)
//                if(y!=0 && x!=0 && this->world.home_pheromone[tmp.position.x()+x][tmp.position.y()+y] > max){
//                    max = this->world.home_pheromone[tmp.position.x()+x][tmp.position.y()+y];
//                    dx = x;
//                    dy = y;
//                }
//    }
//    if(max != 0.0)
//    {
//        tmp.previousPosition.setX(tmp.position.x());
//        tmp.previousPosition.setY(tmp.position.y());
//        if(tmp.position.x() + dx < this->worldWidth - 5 && tmp.position.x() + dx > 5)
//            tmp.position.setX(tmp.position.x() + dx);
//        if(tmp.position.y() + dy < this->worldHeight - 5 && tmp.position.y() + dy > 5)
//            tmp.position.setY(tmp.position.y() + dy);
//    }
//    else
//    {
        int x = floor(unifRand() / (1.00 / 3.00));
        int y = floor(unifRand() / (1.00 / 3.00));
        tmp.previousPosition.setX(tmp.position.x());
        tmp.previousPosition.setY(tmp.position.y());
        if(tmp.position.x() + x - 1 < this->worldWidth - 5 && tmp.position.x() + x - 1 > 5)
            tmp.position.setX(tmp.position.x() + x - 1);
        if(tmp.position.y() + y - 1 < this->worldHeight - 5 && tmp.position.y() + y - 1 > 5)
            tmp.position.setY(tmp.position.y() + y - 1);

        std::cout << x << "," << y << std::endl;
//    }
//    return;
}

void simulation::randomAgentAction(sample &tmp)
{
    int x = floor(unifRand() / (1.00 / 3.00));
    int y = floor(unifRand() / (1.00 / 3.00));
    tmp.previousPosition.setX(tmp.position.x());
    tmp.previousPosition.setY(tmp.position.y());
    if(tmp.position.x() + x - 1 < this->worldWidth - 5 && tmp.position.x() + x - 1 > 5)
        tmp.position.setX(tmp.position.x() + x - 1);
    if(tmp.position.y() + y - 1 < this->worldHeight - 5 && tmp.position.y() + y - 1 > 5)
        tmp.position.setY(tmp.position.y() + y - 1);
}

void simulation::agentPheromoneUpdate(sample tmp)
{
    double max = this->world.food_pheromone[tmp.previousPosition.x()][tmp.previousPosition.y()];

    double discounted = max - discount;
    if(discounted > this->world.food_pheromone[tmp.position.x()][tmp.position.y()])
        this->world.food_pheromone[tmp.position.x()][tmp.position.y()] = discounted;

    max = this->world.home_pheromone[tmp.previousPosition.x()][tmp.previousPosition.y()];

    discounted = max - discount;
    if(discounted > this->world.home_pheromone[tmp.position.x()][tmp.position.y()])
        this->world.home_pheromone[tmp.position.x()][tmp.position.y()] = discounted;
}

void simulation::droppingPheromone(QPoint position)
{
    if(position.x() >= this->nest.x() && position.x() <= this->nest.x() + nestSize && position.y() >= this->nest.y() && position.y() <= this->nest.y() + nestSize)
        this->world.home_pheromone[position.x()][position.y()] = this->max_home_pheromone;

    if(position.x() >= this->food.x() && position.x() <= this->food.x() + foodSize && position.y() >= this->food.y() && position.y() <= this->food.y() + foodSize)
        this->world.food_pheromone[position.x()][position.y()] = this->max_food_pheromone;
}

void simulation::diffusion()
{
    std::vector<change> temp;

    for(int i = 1; i < this->worldWidth - 1; i++){
        for(int j = 1; j < this->worldHeight - 1; j++){
            double oldFoodValue = this->world.food_pheromone[i][j];
            double newFoodValue = this->world.food_pheromone[i][j];
            double max = 0.0;
            for(int x = -1; x < 2; x++)
                for(int y = -1; y < 2; y++)
                    if(y!=0 && x!=0 && this->world.food_pheromone[i+x][j+y]  / sqrt(x*x + y*y)> max){
                        max = this->world.food_pheromone[i+x][j+y] / sqrt(x*x + y*y);
                    }
            newFoodValue = diffusion_const * max;
            if(oldFoodValue < newFoodValue || oldFoodValue == 0.0){
                change tmp;
                tmp.pos.setX(i);
                tmp.pos.setY(j);
                tmp.newValue = newFoodValue;
                temp.push_back(tmp);
            }
        }
    }

    for(unsigned int c = 0; c < temp.size(); c++)
        this->world.food_pheromone[temp.at(c).pos.x()][temp.at(c).pos.y()] = temp.at(c).newValue;

    temp.clear();

    for(int i = 1; i < this->worldWidth - 1; i++){
        for(int j = 1; j < this->worldHeight - 1; j++){
            double oldHomeValue = this->world.home_pheromone[i][j];
            double newHomeValue = this->world.home_pheromone[i][j];
            double max = 0.0;
            for(int x = -1; x < 2; x++)
                for(int y = -1; y < 2; y++)
                    if(y!=0 && x!=0 && this->world.home_pheromone[i+x][j+y]  / sqrt(x*x + y*y)> max){
                        max = this->world.home_pheromone[i+x][j+y] / sqrt(x*x + y*y);
                    }
            newHomeValue = diffusion_const * max;
            if(oldHomeValue < newHomeValue || oldHomeValue == 0.0){
                change tmp;
                tmp.pos.setX(i);
                tmp.pos.setY(j);
                tmp.newValue = newHomeValue;
                temp.push_back(tmp);
            }
        }
    }

    for(unsigned int c = 0; c < temp.size(); c++)
        this->world.home_pheromone[temp.at(c).pos.x()][temp.at(c).pos.y()] = temp.at(c).newValue;

    temp.clear();
    return;
}

void simulation::evaporation()
{
    for(int i = 0; i < this->worldWidth; i++)
    {
        for(int j = 0; j < this->worldHeight; j++)
        {
            if(this->world.home_pheromone[i][j] != 0.0)
                this->world.home_pheromone[i][j] *= evaporation_const;
            if(this->world.food_pheromone[i][j] != 0.0)
                this->world.food_pheromone[i][j] *= evaporation_const;
        }
    }
    return;
}
