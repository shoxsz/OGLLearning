#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <cmath>

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

    float distance(const TPoint<T>& point){
        T diffx = point.x - x;
        T diffy = point.y - y;
        return sqrt(diffx*diffx, diffy*diffy);
    }

    TPoint<T> operator+(const TPoint<T>& point)const{
        return TPoint<T>(x + point.x, y + point.y);
    }

    void operator+(const TPoint<T>& point){
        x += point.x;
        y += point.y;
    }

    TPoint<T> operator-(const TPoint<T>& point)const{
        return TPoint<T>(x - point.x, y - point.y);
    }

    void operator-(const TPoint<T>& point){
        x -= point.x;
        y -= point.y;
    }

    T x, y;
};

typedef TPoint<int> Point;
typedef TPoint<float> PointF;

#endif