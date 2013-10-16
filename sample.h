#ifndef SAMPLE_H
#define SAMPLE_H

#include <QPoint>

class sample
{
public:
    int id;
    QPoint position;
    QPoint previousPosition;
    double hungry;
    sample();
    void action();
};

#endif // SAMPLE_H
