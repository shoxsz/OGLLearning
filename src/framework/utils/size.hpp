#ifndef _SIZE_HPP_
#define _SIZE_HPP_

class Size{
public:
    Size():w(0), h(0){}

    Size(float width, float height){
        this->w = width;
        this->h = height;
    }

    float w, h;
};

#endif