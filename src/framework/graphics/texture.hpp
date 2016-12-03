#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <memory>

#include <gl/glew.h>

#include "enums.hpp"
#include "utils/size.hpp"

class Texture2D{
public:
    friend class TextureManager;

    Texture2D():hasMipmap(false), created(false), unit(0), id(0){}
    Texture2D(const Size& size, PixelFormat format);
    ~Texture2D();

    void dispose();

    void bind();

    void setWrapping(Wrapping wrap);
    void setFiltering(Filtering minFilter, Filtering magFilter);
    void write(void* pixels, const Size& size, PixelFormat format);
    void buildMipmaps(unsigned min, unsigned int max);

    //set the image unit that the texture will be attached to before binding
    void setUnit(unsigned int unit){
        this->unit = unit;
    }

    const Size& getSize()const{ 
        return size; 
    }

    unsigned int getUnit()const{
        return unit;
    }

private:
    void updatePixels(void* pixels, const Size& size, PixelFormat format);

    Size size;
    bool hasMipmap;
    bool created;
    Wrapping wrap;
    Filtering minFilter;
    Filtering magFilter;
    unsigned int unit;
    unsigned int id;
};

#endif