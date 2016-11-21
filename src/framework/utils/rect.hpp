#ifndef _RECT_HPP_
#define _RECT_HPP_

class Rect{
public:
    Rect():x(0), y(0), w(0), h(0){}
    Rect(float x, float y, float w, float h): x(x), y(y), w(w), h(h){}

    float x, y;
    float w, h;
};

#endif