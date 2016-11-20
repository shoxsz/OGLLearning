#ifndef _COLOR_HPP_
#define _COLOR_HPP_

class Color{
public:
    Color():r(0), g(0), b(0), a(0){}
    Color(float r, float g, float b, float a): r(r), g(g), b(b), a(a){}

    float r, g, b, a;
};

#endif