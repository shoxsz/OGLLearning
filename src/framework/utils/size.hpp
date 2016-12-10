#ifndef _SIZE_HPP_
#define _SIZE_HPP_

template<class T>
class TSize{
public:
    TSize():width(0), height(0){}
    TSize(T width, T height): width(width), height(height){}

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

    void scale(T scale){
        width *= scale;
        height *= scale;
    }

    T width, height;
};

typedef TSize<int> Size;
typedef TSize<float> SizeF;

#endif