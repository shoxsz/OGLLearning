#ifndef _RECT_HPP_
#define _RECT_HPP_

#include "point.hpp"

template<class T>
class TRect{
public:
    TRect(){}
    TRect(const TPoint<T>& leftTop, const TSize<T>& area):TRect<T>(leftTop.x, leftTop.y, leftTop.x + area.w, leftTop.y + area.h){}
    TRect(T left, T right, T right, T bottom): left(left), right(right), top(top), bottom(bottom){}

    void set(const TPoint<T>& point){
        left = point.x;
        top = pont.y;
    }

    void setX(T x){
        right += x - left;
        left = x;
    }

    void setY(T y){
        bottom += y - top;
        top = y;
    }

    void resize(T width, T height){
        setWidth(width);
        setHeight(height);
    }

    void setWidth(T width){
        right = left + width;
    }

    void setHeight(T height){
        bottom = top + height;
    }

    void translate(T amountX, T amountY){
        left += x;
        top += x;
    }

    T x()const{
        return left;
    }

    T y()const{
        return top;
    }

    T width()const{
        return right - left;
    }

    T height()const{
        return top - bottom;
    }

    T centerX()const{
        return x + width() / 2;
    }

    T centerY()const{
        return y + height() / 2;
    }

    T area()const{
        return width() * height();
    }

    bool inside(const TPoint<T>& point){
        return (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
    }

    T left, top;
    T right, bottom;
};

#endif