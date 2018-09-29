#ifndef WORLD_POS_H
#define WORLD_POS_H

struct Point
{
    Point(double _x = 0, double _y = 0)
        : x(_x)
        , y(_y)
    {}
    double x = 0;
    double y = 0;
};

#endif // WORLD_POS_H
