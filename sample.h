#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPoint>

class sample
{
public:
    // id
    int id;
    // position in the grid
    QPoint position;
    //previous
    QPoint previousPosition;
    // hunger level
    double hungry;
    // life remaining, not used yet
    double life;
    sample();
    void action();
};

#endif // SAMPLE_H
