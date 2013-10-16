#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <iostream>
#include <ctime>

using namespace std;

//
// Generate a random number between 0 and 1
// return a uniform number in [0,1].
inline double unifRand()
{
    return rand() / double(RAND_MAX);
}

// Reset the random number generator with the system clock.
inline void seed()
{
    srand(time(0));
}

#endif // RANDOMGENERATOR_H
