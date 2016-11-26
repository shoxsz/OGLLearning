#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <SDL_opengl.h>

#include "enums.hpp"
#include "utils/size.hpp"

class Texture2D{
public:
    friend class TextureManager;

    Texture2D():hasMipmap(false), created(false), unit(0), id(0){}
    Texture2D(const Size& size, ImageFormat format);
    ~Texture2D();

    void dispose();

    void bind();

    void setWrapping(Wrapping wrap);
    void setFiltering(Filtering filter);
    void write(void* pixels, Size& size, bool mipmaps = true);
    void buildMipmaps(unsigned min, unsigned int max);

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
    void updatePixels(void* pixels, Size& size, ImageFormat format);

    Size size;
    bool hasMipmap;
    bool created;
    Wrapping wrap;
    Filtering minFilter;
    Filtering magFilter;
    unsigned int unit;
    unsigned int id;
};

typedef std::shared_ptr<Texture2D> Texture2DPtr;

#endif