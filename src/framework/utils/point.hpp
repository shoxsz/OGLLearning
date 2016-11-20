#ifndef _POINT_HPP_
#define _POINT_HPP_

class Point{
public:
    Point():x(0), y(0), z(0){}
    Point(float x, float y, float z):x(x), y(y), z(z){}

    float x, y, z;
};

#endif