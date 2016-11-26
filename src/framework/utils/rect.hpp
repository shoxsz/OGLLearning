#ifndef _RECT_HPP_
#define _RECT_HPP_

class Rect{
public:
    Rect():x(0), y(0), w(0), h(0){}
    Rect(float x, float y, float w, float h): x(x), y(y), w(w), h(h){}

    float left()const{
        return (x - w / 2);
    }

    float right()const{
        return (x + w / 2);
    }

    float top()const{
        return (x - h / 2);
    }

    float bottom()const{
        return (x + h / 2);
    }

    float x, y;
    float w, h;
};

#endif