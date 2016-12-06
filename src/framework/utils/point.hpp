#ifndef _POINT_HPP_
#define _POINT_HPP_

template<class T>
class TPoint{
public:
    TPoint():x(0), y(0){}
    TPoint(T x, T y): x(x), y(y){} 

    void set(T x, T y){
        this->x = x;
        this->y = y;
    }

    void setX(T x){
        this->x = x;
    }

    void setY(T y){
        this->y = y;
    }

    T x, y;
};

#endif