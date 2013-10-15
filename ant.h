#ifndef ANT_H
#define ANT_H

class ant
{
public:
    ant();
    ~ant();
    int x;
    int y;
    double direction;
private:
    void chooseMove(int x, int y, double theta);
};

#endif // ANT_H
