#include "texture.hpp"

Texture2D::Texture2D(const Size& size, ImageFormat format){
    updatePixels(size, nullptr, format);
}

Texture2D::~Texture2D(){
    dispose();
}

void Texture2D::dispose(){
    if(created){
        glDeleteTextures(1, id);
        created = false;
    }
}

void Texture2D::bind(){
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::setWrapping(Wrapping wrap){
    this->wrap = wrap;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
}

void Texture2D::setFiltering(Filtering minFilter, Filtering magFilter){
    this->minFilter = minFilter;
    this->magFilter = magFilter;

    if(hasMipmap){
        minFilter = (minFilter == Nearest ? NearestMipmap : LinearMipmap);
        magFilter = (magFilter == Nearest ? NearestMipmap : LinearMipmap);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    }
}

void Texture2D::write(void* pixels, Size& size){
    updatePixels(size, pixels);
}

void Texture2D::buildMipmaps(unsigned int min, unsigned int max){
    glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, min);
    glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, max);

    setFiltering(minFilter, magFilter);

    glGenerateMipmap(GL_TEXTURE_2D);

    hasMipmap = true;
}

void Texture2D::updatePixels(Size& size, void* pixels, ImageFormat format){
    if(!created){
        glGenTextures(1, &id);
        created = true;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.width(), size.height(), 0, format, GL_UNSIGNED_BYTE, pixels);
    this->size = size;
}