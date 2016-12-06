#ifndef _SIZE_HPP_
#define _SIZE_HPP_

template<class T>
class TSize{
public:
    TSize():width(0), height(0){}
    TSize(T width, T size): width(width), height(height){}

    void resize(T width, T height){
        this->width = width;
        this->height = height;
    }

    void setWidth(T width){
        this->width = width;
    }

    void setHeight(T height){
        this->height = height;
    }

    T area()const{
        return width * height;
    }

    T width, height;
};

#endif